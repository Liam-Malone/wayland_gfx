for arg in "$@"; do
    declare $arg='1'
done

cflags='-std=c23'
debug_flags='-g -D_debug_'
release_flags='-O3 -D_release_'

if [ -v release ]; then
    echo "[ Release Mode ]"
    cflags="$cflags $release_flags"
else
    echo "[ Debug Mode ]"
    cflags="$cflags $debug_flags"
fi

mkdir -p bin

# :: BEGIN Wayland Codegen ::
# Wayland Protocol Header Generation
if [ -v gen ] || ! [ -f src/generated/xdg-client.h ]; then
    echo " :: Generating XDG client header ::"
    wayland-scanner client-header protocols/wayland/xdg-shell.xml src/generated/xdg-shell-client.h
fi
if [ -v gen ] || ! [ -f src/generated/presentation-time.h ]; then
    echo " :: Generating presentation-time header ::"
    wayland-scanner client-header protocols/wayland/xdg-shell.xml src/generated/presentation-time.h
fi


# Wayland Protocol Source Generation
if [ -v gen ] || ! [ -f src/generated/xdg-client.c ]; then
    echo " :: Generating XDG client source ::"
    wayland-scanner private-code protocols/wayland/xdg-shell.xml src/generated/xdg-shell-client.c
fi
if [ -v gen ] || ! [ -f src/generated/presentation-time.c ]; then
        echo " :: Generating presentation-time source ::"
        wayland-scanner private-code protocols/wayland/xdg-shell.xml src/generated/presentation-time.c
fi
# :: END Wayland Codegen ::

out=bin/simp

compiler='zig cc'
libs=' -lc -lwayland-client -lxkbcommon'

if [ -v e ]; then
    cflags="$cflags"
else
    cflags="$cflags -Werror -Wall -Wextra -pedantic"
fi

defines="\
    -D_wayland_                     \
    -Dwl_shm_interface_ver=2        \
    -Dwl_compositor_interface_ver=5 \
    -Dxdg_wm_base_interface_ver=6   \
    -Dwl_seat_interface_ver=7       
"

built=0
compile="$compiler -o $out $cflags $defines"
$compile src/main.c $libs && built=1

if [ -v run ] && [[ $built == 1 ]]; then
    ./$out
fi
