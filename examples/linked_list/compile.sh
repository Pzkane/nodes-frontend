g++ linked_list.cpp -ggdb -o linked_list.exe -I ../../include -I $(cat  ../../.env | awk '{print $2}')/include -L $(cat  ../../.env | awk '{print $2}')/lib ../../libnf.a -lsfml-graphics -lsfml-window -lsfml-system
cp -r linked_list.exe ../../resources $(cat  ../../.env | awk '{print $2}')/bin