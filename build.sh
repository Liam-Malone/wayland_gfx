for arg in "$@"; do
    declare $arg='1'
done

if [ -v release ]; then
    echo "[ Release Mode ]"
else
    echo "[ Debug Mode ]"
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
cflags='-std=c23'
libs='-lwayland-client -lc'

if [ -v e ]; then
    cflags="$cflags"
else
    cflags="$cflags -Werror -Wall -Wextra -pedantic"
fi

defines='-D_wayland_'

debug_flags='-g -D_debug_'
release_flags='-O3 -D_release_'

built=0
compile="$compiler -o $out $cflags $defines"
$compile src/main.c $libs && built=1

if [ -v run ] && [[ $built == 1 ]]; then
    ./$out
fi
