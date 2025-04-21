#pragma once

#include <iostream>
#include <map>
#include <functional>
#include <string>
#include "resources.h"

// Tabla de registro dinámica (global)
inline std::map<std::string, std::function<void(ResourceType)>> problemRegistry;

// Macro para definir un problema (crea y registra automáticamente la función)
#define DEFINE_PROBLEM(year, day, part)                                       \
    void problemEvent##year##Day##day##Part##part(ResourceType resourceType); \
    struct problemEvent##year##Day##day##_Part##part##_Registrar {            \
        problemEvent##year##Day##day##_Part##part##_Registrar() {             \
            const std::string key = #year "_" #day "_" #part;                 \
            problemRegistry[key] = problemEvent##year##Day##day##Part##part;  \
        }                                                                     \
    };                                                                        \
    static problemEvent##year##Day##day##_Part##part##_Registrar registrar##year##Day##day##Part##part; \
    void problemEvent##year##Day##day##Part##part(ResourceType resourceType)


