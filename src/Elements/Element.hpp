#pragma once
#include <vector>
#include <string>
#include "../Components/PositionComponent.hpp"

class Element
{
    std::string name; //Element Name/Indentifier
    Element* parent;
    std::vector<Element*> children;
};