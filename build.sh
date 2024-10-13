for arg in "$@"; do
    declare $arg='1'
done

mkdir -p bin

out=bin/simp

compiler='zig cc'
cflags='-std=c23'
libs='-lwayland-client -lc'

if [ -v exeriment ]; then
    cflags="$cflags -Wno-unused-parameter -Wno-unused-function"
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
