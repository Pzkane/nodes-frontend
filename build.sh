if [ $# -eq 0 ] || [ $1 != "--run" ]; then
    if cmake --build ./build/ ; then
        cmake --install ./build/
    else
        exit -1;
    fi
fi
/d/disk_backup/C++/libraries/SFML-2.5.1/bin/tree_visualizer.exe
