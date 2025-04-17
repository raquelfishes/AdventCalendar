#include "resources.h"
#include <stdexcept>
#include <filesystem>

std::string getResourcePath(int year, int day, ResourceType type)
{
    // Construimos la ruta inicial
    std::string path = RESOURCES_BASE_PATH + "/" + std::to_string(year) + "/resources/";

    // Agregamos el nombre del archivo basado en el día
    path += "day" + std::to_string(day);

    // Determinamos si es un archivo de prueba o de producción
    if (type == ResourceType::TEST)
    {
        path += "_test.txt";
    }
    else
    {
        path += ".txt";
    }

    // Verificar si el archivo existe
    if (!std::filesystem::exists(path))
    {
        throw std::runtime_error("Resource file does not exist: " + path);
    }

    return path;
}
