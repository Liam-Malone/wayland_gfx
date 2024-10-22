/* TODO: Switch to using memfd on linux, use shm with SHM_ANON on *BSD */
/* BEGIN Suggested Boilerplate from wayland-book.com */
#define _POSIX_C_SOURCE 200112L
#include <errno.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <time.h>
#include <unistd.h>

static void randname(char *buf) {
	struct timespec ts;
	clock_gettime(CLOCK_REALTIME, &ts);
	long r = ts.tv_nsec;
	for (int i = 0; i < 6; ++i) {
		buf[i] = 'A'+(r&15)+(r&16)*2;
		r >>= 5;
	}
}

static int create_shm_file(void) {
	int retries = 100;
	do {
		char name[] = "/wl_shm-XXXXXX";
		randname(name + sizeof(name) - 7);
		--retries;
		int fd = shm_open(name, O_RDWR | O_CREAT | O_EXCL, 0600);
		if (fd >= 0) {
			shm_unlink(name);
			return fd;
		}
	} while (retries > 0 && errno == EEXIST);
	return -1;
}

static int allocate_shm_file(size_t size) {
	int fd = create_shm_file();
	if (fd < 0)
		return -1;
	int ret;
	do {
		ret = ftruncate(fd, size);
	} while (ret < 0 && errno == EINTR);
	if (ret < 0) {
		close(fd);
		return -1;
	}
	return fd;
}
/* END Suggested Boilerplate from wayland-book.com */


/* stdlib includes */
#include <stdint.h>
#include <string.h>
#include <stdio.h>

/* LINUX-specific Includes */
/* wayland */
#include <wayland-client.h>
#include <xkbcommon/xkbcommon.h>
#include "generated/xdg-client.h"
#include "generated/xdg-client.c"
/* #include "generated/presentation-time.h" */
/* #include "generated/presentation-time.c" */
/* TODO: Implement presentation-time for frame-timings */

/* project includes */
/* [h] files */
//#include "base/base.h"

/* [c] files */
// #include "base/base.c"

#define log_info(str, ...) printf("  > LOG :: "); printf(str, __VA_ARGS__)

typedef uint32_t u32;
typedef int32_t  i32;
typedef float    f32;

#define _global static
#define _internal static

struct ClientState {
    /* globals */
    struct wl_display*    wl_display;
    struct wl_registry*   wl_registry;
    struct wl_shm*        wl_shm;
    struct wl_compositor* wl_compositor;
    struct xdg_wm_base*   xdg_wm_base;
    struct wl_seat*       wl_seat;

    /* objects */
    struct wl_surface*    wl_surface;
    struct xdg_surface*   xdg_surface;
    struct xdg_toplevel*  xdg_toplevel;
    struct xdg_keyboard*  xdg_keyboard;
    struct xdg_pointer*   xdg_pointer;
    struct xdg_touch*     xdg_touch;

    /*state */
    f32 offset;
    u32 last_frame;
};

_global void wl_buffer_release(void *data, struct wl_buffer *wl_buffer) {
    /* Sent by the compositor when it's no longer using this buffer */
    #ifdef _debug_
    printf("  :: Releasing buffer:\n   > data: %p\n   > buffer: %p\n", data, (void*) wl_buffer);
    #endif
    wl_buffer_destroy(wl_buffer);
}

_global const struct wl_buffer_listener wl_buffer_listener = {
    .release = wl_buffer_release,
};

_global struct wl_buffer* draw_frame(struct ClientState *state) {
    const i32 width = 960, height = 540;
    const i32 stride = width * 4;
    const i32 size = height * stride;
    
    i32 fd = allocate_shm_file(size);
    if (fd == -1) {
        return nullptr;
    }

    u32* data = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    
    if (data == MAP_FAILED) {
        close(fd);
        return nullptr;
    }
    /* Checkerboard background */
    i32 offset = (int)state->offset % 8;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (((x + offset) + (y + offset) / 8 * 8) % 16 < 8) {
                data[y * width + x] = 0xFF666666;
            } else {
                data[y * width + x] = 0xFFEEEEEE;
            }
        }
    }

    struct wl_shm_pool* pool = wl_shm_create_pool(state->wl_shm, fd, size);
    struct wl_buffer* buffer = wl_shm_pool_create_buffer(pool, 0, width, height, stride, WL_SHM_FORMAT_XRGB8888);

    munmap(data, size);
    wl_buffer_add_listener(buffer, &wl_buffer_listener, NULL);
    return buffer;
}

_global void xdg_surface_configure(void* data, struct xdg_surface* xdg_surface, u32 serial) {
    struct ClientState* state = data;
    xdg_surface_ack_configure(xdg_surface, serial);
    
    struct wl_buffer* buffer = draw_frame(state);
    wl_surface_attach(state->wl_surface, buffer, 0, 0);
    wl_surface_commit(state->wl_surface);
}

_global const struct xdg_surface_listener xdg_surface_listener = {
    .configure = xdg_surface_configure,
};

_global void xdg_wm_base_ping(void* data, struct xdg_wm_base* xdg_wm_base, u32 serial) {
    log_info("  > LOG: xdg_wm_base pinging from data at: %p\n", data);
    xdg_wm_base_pong(xdg_wm_base, serial);
}

_global const struct xdg_wm_base_listener xdg_wm_base_listener = {
    .ping = xdg_wm_base_ping,
};

static const struct wl_callback_listener wl_surface_frame_listener;

static void wl_surface_frame_done(void *data, struct wl_callback *cb, u32 time) {
	/* Destroy this callback */
	wl_callback_destroy(cb);

	/* Request another frame */
	struct ClientState *state = data;
	cb = wl_surface_frame(state->wl_surface);
	wl_callback_add_listener(cb, &wl_surface_frame_listener, state);

	/* Update scroll amount at 24 pixels per second */
	if (state->last_frame != 0) {
		u32 elapsed = time - state->last_frame;
        #ifdef _debug_
        log_info("  FRAME DONE :: time diff: %d\n", elapsed);
        #endif
		state->offset += elapsed / 1000.0 * 24;
	}

	/* Submit a frame for this event */
	struct wl_buffer *buffer = draw_frame(state);
	wl_surface_attach(state->wl_surface, buffer, 0, 0);
	wl_surface_damage_buffer(state->wl_surface, 0, 0, INT32_MAX, INT32_MAX);
	wl_surface_commit(state->wl_surface);

	state->last_frame = time;
}

static const struct wl_callback_listener wl_surface_frame_listener = {
	.done = wl_surface_frame_done,
};

static void wl_seat_capabilities(void *data, struct wl_seat *wl_seat, uint32_t capabilities) {
       struct client_state *state = data;
       /* TODO */
       log_info("state ptr: %p, seat ptr: %p, capabilities: %d\n", (void*) state, (void*)wl_seat, capabilities);
}

static void wl_seat_name(void *data, struct wl_seat *wl_seat, const char *name) {
    struct client_state* state = data;
    fprintf(stderr, "state ptr: %p, seat ptr: %p, seat name: %s\n", (void*) state, (void*)wl_seat, name);
}

static const struct wl_seat_listener wl_seat_listener = {
       .capabilities = wl_seat_capabilities,
       .name = wl_seat_name,
};

_global void registry_global(void* data, struct wl_registry* wl_registry, u32 name, const char* interface, u32 version) {
    struct ClientState* state = data;
    if (!strcmp(interface, wl_shm_interface.name)) {
        state->wl_shm = wl_registry_bind(wl_registry, name, &wl_shm_interface, wl_shm_interface_ver);
    } else if (!strcmp(interface, wl_compositor_interface.name)) {
        state->wl_compositor = wl_registry_bind(wl_registry, name, &wl_compositor_interface, wl_compositor_interface_ver);
    } else if (!strcmp(interface, xdg_wm_base_interface.name)) {
        state->xdg_wm_base = wl_registry_bind(wl_registry, name, &xdg_wm_base_interface, xdg_wm_base_interface_ver);
        xdg_wm_base_add_listener(state->xdg_wm_base, &xdg_wm_base_listener, state);
    } else if (!strcmp(interface, wl_seat_interface.name)) {
        state->wl_seat = wl_registry_bind(wl_registry, name, &wl_seat_interface, wl_seat_interface_ver);
        wl_seat_add_listener(state->wl_seat, &wl_seat_listener, state);
    }
    #ifdef _debug_
    log_info(" GLOBAL REGISTRY :: Interface: %s, version: %d, name: %d\n", interface, version, name);
    #endif
}

_global void registry_global_remove(void* data, struct wl_registry* wl_registry, u32 name) {
    #ifdef _debug_
    log_info("  GLOBAL REGISTRY REMOVE :: Name: %d, Data ptr: %p, Reg ptr: %p\n", name, data, (void*) wl_registry);
    #endif
}

_global const struct wl_registry_listener wl_registry_listener = {
    .global = registry_global,
    .global_remove = registry_global_remove,
};

int main(void) {
    struct ClientState state = {};

    state.wl_display = wl_display_connect(NULL);
    if (!state.wl_display) {
        fprintf(stderr, "Could not find a display to connect to!!\n");
        goto exit;
    }
    printf("Connected to a display!\n");

    state.wl_registry = wl_display_get_registry(state.wl_display);
    if (!state.wl_registry) {
        fprintf(stderr, "Failed to get display's registry!!\n");
        goto display_cleanup;
    }

    wl_registry_add_listener(state.wl_registry, &wl_registry_listener, &state);
    wl_display_roundtrip(state.wl_display);

    state.wl_surface = wl_compositor_create_surface(state.wl_compositor);
    state.xdg_surface = xdg_wm_base_get_xdg_surface(state.xdg_wm_base, state.wl_surface);
    state.xdg_toplevel = xdg_surface_get_toplevel(state.xdg_surface);

    xdg_surface_add_listener(state.xdg_surface, &xdg_surface_listener, &state);
    xdg_toplevel_set_title(state.xdg_toplevel, "Simp Client");

    wl_surface_commit(state.wl_surface);

    struct wl_callback* cb = wl_surface_frame(state.wl_surface);
    wl_callback_add_listener(cb, &wl_surface_frame_listener, &state);

    while (wl_display_dispatch(state.wl_display)) {
        /* Await input */
        draw_frame(&state);
    }

display_cleanup:
    wl_display_disconnect(state.wl_display);
    printf("Disconnected from display!\n");

exit:
    return 0;
}
