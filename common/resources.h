#pragma once

#include <string>

// Ruta base hacia los recursos: Ajusta esto manualmente a tu estructura de proyecto
static const std::string RESOURCES_BASE_PATH = "../events";

// Enum para distinguir entre recursos de producción y de prueba
enum class ResourceType
{
    PRODUCTION, // Por defecto
    TEST
};

// Función para construir la ruta de los recursos
std::string getResourcePath(int year, int day, ResourceType type = ResourceType::PRODUCTION);
