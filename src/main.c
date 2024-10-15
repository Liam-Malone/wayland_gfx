/* BEGIN Suggested Boilerplate from wayland-book.com */
/* TODO: Write my own code for this */
#define _POSIX_C_SOURCE 200112L
#include <errno.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <time.h>
#include <unistd.h>

static void
randname(char *buf)
{
	struct timespec ts;
	clock_gettime(CLOCK_REALTIME, &ts);
	long r = ts.tv_nsec;
	for (int i = 0; i < 6; ++i) {
		buf[i] = 'A'+(r&15)+(r&16)*2;
		r >>= 5;
	}
}

static int
create_shm_file(void)
{
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

int
allocate_shm_file(size_t size)
{
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

typedef uint32_t u32;

#define _global static
#define _internal static

struct client_state {
    /* globals */
    struct wl_display*    _wl_display;
    struct wl_registry*   _wl_registry;
    struct wl_shm*        _wl_shm;
    struct wl_compositor* _wl_compositor;
    struct xdg_wm_base*     _xdg_wm_base;
    /* objects */
    struct wl_surface*    _wl_surface;
    struct xdg_surface*   _xdg_surface;
    struct xdg_toplevel*  _xdg_toplevel;
};

_global void wl_buffer_release(void *data, struct wl_buffer *wl_buffer) {
    /* Sent by the compositor when it's no longer using this buffer */
    printf("  :: Releasing buffer:\n   > data: %p\n   > buffer: %p\n", data, (void*) wl_buffer);
    wl_buffer_destroy(wl_buffer);
}

_global const struct wl_buffer_listener wl_buffer_listener = {
    .release = wl_buffer_release,
};

_global struct wl_buffer* draw_frame(struct client_state *state) {
    const int width = 960, height = 540;
    const int stride = width * 4;
    const int size = height * stride;
    
    int fd = allocate_shm_file(size);
    if (fd == -1) {
        return nullptr;
    }

    u32* data = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    
    if (data == MAP_FAILED) {
        close(fd);
        return nullptr;
    }

    struct wl_shm_pool* pool = wl_shm_create_pool(state->_wl_shm, fd, size);

    struct wl_buffer* buffer = wl_shm_pool_create_buffer(pool, 0, width, height, stride, WL_SHM_FORMAT_XRGB8888);

    /* Checkerboard background */
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if ((x + y / 8 * 8) % 16 < 8) {
                data[y * width + x] = 0xFF666666;
            } else {
                data[y * width + x] = 0xFFEEEEEE;
            }
        }
    }
    munmap(data, size);
    wl_buffer_add_listener(buffer, &wl_buffer_listener, NULL);
    return buffer;
}

_global void xdg_surface_configure(void* data, struct xdg_surface* xdg_surface, u32 serial) {
    struct client_state* state = data;
    xdg_surface_ack_configure(xdg_surface, serial);
    
    struct wl_buffer* buffer = draw_frame(state);
    wl_surface_attach(state->_wl_surface, buffer, 0, 0);
    wl_surface_commit(state->_wl_surface);
}

_global const struct xdg_surface_listener _xdg_surface_listener = {
    .configure = xdg_surface_configure,
};

_global void xdg_wm_base_ping(void* data, struct xdg_wm_base* xdg_wm_base, u32 serial) {
    printf("  > LOG: xdg_wm_base pinging from data at: %p ", data);
    xdg_wm_base_pong(xdg_wm_base, serial);
}

_global const struct xdg_wm_base_listener _xdg_wm_base_listener = {
    .ping = xdg_wm_base_ping,
};

_global void registry_global(void* data, struct wl_registry* wl_registry, u32 name, const char* interface, u32 version) {
    struct client_state* state = data;
    if (!strcmp(interface, wl_shm_interface.name)) {
        state->_wl_shm = wl_registry_bind(wl_registry, name, &wl_shm_interface, 1);
    } else if (!strcmp(interface, wl_compositor_interface.name)) {
        state->_wl_compositor = wl_registry_bind(wl_registry, name, &wl_compositor_interface, 4);
    } else if (!strcmp(interface, "xdg_wm_base")) {
        state->_xdg_wm_base = wl_registry_bind(wl_registry, name, &xdg_wm_base_interface, 1);
        xdg_wm_base_add_listener(state->_xdg_wm_base, &_xdg_wm_base_listener, state);
    }
    printf("Interface: %s, version: %d, name: %d\n", interface, version, name);
}

_global void registry_global_remove(void* data, struct wl_registry* wl_registry, u32 name) {
    printf("Name: %d, Data ptr: %p, Reg ptr: %p\n", name, data, (void*) wl_registry);
}

_global const struct wl_registry_listener wl_registry_listener = {
    .global = registry_global,
    .global_remove = registry_global_remove,
};

int main(void) {
    struct client_state state = {};

    state._wl_display = wl_display_connect(NULL);
    if (!state._wl_display) {
        fprintf(stderr, "Could not find a display to connect to!!\n");
        goto exit;
    }
    printf("Connected to a display!\n");

    state._wl_registry = wl_display_get_registry(state._wl_display);
    if (!state._wl_registry) {
        fprintf(stderr, "Failed to get display's registry!!\n");
        goto display_cleanup;
    }

    wl_registry_add_listener(state._wl_registry, &wl_registry_listener, &state);
    wl_display_roundtrip(state._wl_display);

    state._wl_surface = wl_compositor_create_surface(state._wl_compositor);
    state._xdg_surface = xdg_wm_base_get_xdg_surface(state._xdg_wm_base, state._wl_surface);
    state._xdg_toplevel = xdg_surface_get_toplevel(state._xdg_surface);

    xdg_surface_add_listener(state._xdg_surface, &_xdg_surface_listener, &state);
    xdg_toplevel_set_title(state._xdg_toplevel, "Simp Client");

    wl_surface_commit(state._wl_surface);

    while (wl_display_dispatch(state._wl_display)) {
        /* Await input */
        draw_frame(&state);
    }

display_cleanup:
    wl_display_disconnect(state._wl_display);
    printf("Disconnected from display!\n");

exit:
    return 0;
}
