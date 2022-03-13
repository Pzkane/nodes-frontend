cd build
echo -e "\
create libnv.a
addlib libentitiesLib.a
addlib libhelpersLib.a
addlib libnodes_frontend.a
addlib libpropertiesLib.a
addlib libscenesLib.a
addlib libshapesLib.a
save
end" | ar -M