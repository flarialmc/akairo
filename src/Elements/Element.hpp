#pragma once
#include <vector>
#include <string>
#include "../UI/Components/Position.hpp"

class Element
{
    std::string name; //Element Name/Indentifier
    Element* parent; //Parent Element of this Element
    std::vector<Element*> children; //Child Elements of this Element
};