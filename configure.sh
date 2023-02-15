if [ $# -ne 0 ] ; then
    if [ $1 == "dbg" ] ; then
        if cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -DCMAKE_BUILD_TYPE=Debug -DDEBUG=1 -DEXAMPLE=1 -DCXXFLAGS=-g -S ./ -B ./build/ -G "MSYS Makefiles" ; then
            echo -n  $(tput setaf 255;tput setab 0)DEFAULT $(tput setaf 0;tput setab 3) DEBUG $(tput setaf 255;tput setab 0) CONFIGURATION
        fi
    else
        params=""
        for param in $@ ; do
            params="$params -D$param"
        done
        cmake -DCMAKE_BUILD_TYPE=Debug -DDEBUG=1 $params -S ./ -B ./build/ -G "MSYS Makefiles"
        echo $(tput setaf 0;tput setab 3) cmake -DCMAKE_BUILD_TYPE=Debug -DDEBUG=1 $params -S ./ -B ./build/ -G "MSYS Makefiles" $(tput setab 0)
    fi
else
    if cmake -DCMAKE_BUILD_TYPE=Release -DCXXFLAGS=-O3 -S ./ -B ./build/ -G "MSYS Makefiles" ; then
        echo -n $(tput setaf 255;tput setab 0)DEFAULT $(tput setaf 0;tput setab 2) RELEASE $(tput setaf 255;tput setab 0) CONFIGURATION
    fi
fi
