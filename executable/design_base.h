#pragma once
#include <iostream>
#include <functional>
#include <unordered_map>

// Declaración primaria de la plantilla
template<int Year>
void printDesign();

// Metafunción para generar el mapa
template<int... Years>
auto createDesignMap() {
    return std::unordered_map<int, std::function<void()>>{
        {Years, []{ printDesign<Years>(); }}...
    };
}