if [ $# -ne 0 ] ; then
    cxx_flags=""
    for flag in $@ ; do
        cxx_flags="$cxx_flags $flag"
    done
    cmake -DCMAKE_BUILD_TYPE=Debug -DCXXFLAGS="$cxx_flags" -DDEBUGFLAG=1 -S ./ -B ./build/ -G "MSYS Makefiles"
else
    cmake -DCMAKE_BUILD_TYPE=Release -S ./ -B ./build/ -G "MSYS Makefiles"
fi

