#pragma once
#include <iostream>
#include <unordered_map>
#include "Renderer/Renderer.hpp"


class akairo {

  std::unordered_map<std::string, Renderer> renderers;

  public:
    static void CreateRenderer(std::string name);
};
