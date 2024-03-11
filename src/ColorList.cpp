#include "ColorList.hpp"

ColorList::ColorList() :
    Colors( { 
            raylib::Color(108, 86, 113), 
            raylib::Color(176, 169, 228), 
            raylib::Color(249, 130, 132), 
            raylib::Color(254, 170, 228), 
            raylib::Color(172, 204, 228), 
            raylib::Color(179, 227, 218), 
            raylib::Color(176, 235, 147), 
            raylib::Color(233, 245, 157) 
        }
    ) {

    }

raylib::Color ColorList::GetColor(int index) {
    return Colors.at(index);
}

raylib::Color ColorList::GetRandomColor() {
    return Colors.at(GetRandomValue(0, Colors.size() - 1));
}
