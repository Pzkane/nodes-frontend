if cmake --build ./build/ ; then
    if ! cmake --install ./build/ ; then
        exit -1;
    fi
else
    exit -1;
fi

RAW_SFML_PREFIX=$(grep "SFML_PREFIX" .env)
IFS=' ' read -r _ SFML_PREFIX <<< ${RAW_SFML_PREFIX}

if [ $# -ne 0 ] ; then
    if [ $1 == "--run" ] ; then
        "$SFML_PREFIX/bin/nodes_frontend_bin.exe"
    fi
fi
