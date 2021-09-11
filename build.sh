if cmake --build ./build/ ; then
    cmake --install ./build/
else
    exit -1;
fi

if [ $# -ne 0 ] ; then
    if [ $1 == "--run" ] ; then
        /d/disk_backup/C++/libraries/SFML-2.5.1/bin/tree_visualizer.exe
    fi
fi
