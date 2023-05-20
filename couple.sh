cd ./build/src
echo -e "\
create ../../libnf.a
addlib libentitiesLib.a
addlib libhelpersLib.a
addlib libnodes_frontend.a
addlib libpropertiesLib.a
addlib libscenesLib.a
addlib libshapesLib.a
addlib libuiLib.a
addlib libmouseLib.a
addlib libstateLib.a
save
end" | ar -M