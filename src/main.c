/* BEGIN Suggested Boilerplate from wayland-book.com */
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
// #include <xdg-shell.h>

typedef uint32_t u32;

#define _global static
#define _internal static

struct wayland_state {
    struct wl_compositor* compositor;
    struct wl_shm*        shm;
};

_global void registry_handle_global(void* data, struct wl_registry* wl_registry, u32 name, const char* interface, u32 version) {
    struct wayland_state* state = data;
    if (!strcmp(interface, wl_compositor_interface.name)) {
        state->compositor = wl_registry_bind(wl_registry, name, &wl_compositor_interface, 4);
    }
    if (!strcmp(interface, wl_shm_interface.name)) {
        state->shm = wl_registry_bind(wl_registry, name, &wl_shm_interface, 1);
    }
    printf("Interface: %s, version: %d, name: %d\n", interface, version, name);
    printf("\n  ::      ...sup\n\n");
    printf("Data ptr: %p, Reg ptr: %p\n", data, (void*) wl_registry);
    printf("\n  ::      ...o'er dere!!!\n\n");
}

_global void registry_handle_global_remove(void* data, struct wl_registry* wl_registry, u32 name) {
    printf("Name: %d, Data ptr: %p, Reg ptr: %p\n", name, data, (void*) wl_registry);
}

_global const struct wl_registry_listener registry_listener = {
    .global = registry_handle_global,
    .global_remove = registry_handle_global_remove,
};

int main(void) {
    struct wayland_state state = {};
    struct wl_display* display = nullptr;
    display = wl_display_connect(NULL);
    if (!display) {
        fprintf(stderr, "Could not find a display to connect to!!\n");
        goto exit;
    }
    printf("Connected to a display!\n");
    struct wl_registry* registry = nullptr;
    registry = wl_display_get_registry(display);
    if (!registry) {
        fprintf(stderr, "Failed to get display's registry!!\n");
        goto display_cleanup;
    }

    wl_registry_add_listener(registry, &registry_listener, &state);
    wl_display_roundtrip(display);
    struct wl_surface *surface = wl_compositor_create_surface(state.compositor);

    const int width = 1920, height = 1080;
    const int stride = width * 4;
    const int shm_pool_size = height * stride * 2;
    
    int fd = allocate_shm_file(shm_pool_size);
    uint8_t *pool_data = mmap(NULL, shm_pool_size,
        PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    
    struct wl_shm* shm = nullptr; // Bound from registry
    printf("  ::>> Hi there!!!\n\n");
    struct wl_shm_pool* pool = wl_shm_create_pool(shm, fd, shm_pool_size);


    /* white filled buffer */
    int index = 0;
    int offset = height * stride * index;
    struct wl_buffer *buffer = wl_shm_pool_create_buffer(pool, offset, width, height, stride, WL_SHM_FORMAT_XRGB8888);

    uint32_t *pixels = (uint32_t *)&pool_data[offset];
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if ((x + y / 8 * 8) % 16 < 8) {
                pixels[y * width + x] = 0xFF666666;
            } else {
                pixels[y * width + x] = 0xFFEEEEEE;
            }
        }
    }
    
    wl_surface_attach(surface, buffer, 0, 0);
    wl_surface_damage(surface, 0, 0, UINT32_MAX, UINT32_MAX);
    wl_surface_commit(surface);


    // for (;;) {
    //     if (wl_display_dispatch(display) == -1) 
    //         goto display_cleanup;
    // }

display_cleanup:
    wl_display_disconnect(display);
    printf("Disconnected from display!\n");

exit:
    return 0;
}
