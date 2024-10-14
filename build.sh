for arg in "$@"; do
    declare $arg='1'
done

if [ -v release ]; then
    echo "[ Release Mode ]"
else
    echo "[ Debug Mode ]"
fi

mkdir -p bin

if [ -v gen ] || ! [ -f src/generated/xdg-shell-client.h ]; then
    echo " :: Generating XDG client shell header and source ::"
    wayland-scanner client-header protocols/wayland/xdg-shell.xml src/generated/xdg-shell-client.h
    wayland-scanner private-code protocols/wayland/xdg-shell.xml src/generated/xdg-shell-client.c
fi

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
