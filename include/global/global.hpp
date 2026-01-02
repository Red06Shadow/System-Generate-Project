// Definir las variables globales
#include <stda/system/files/filesystem.hpp>
#include <string>
#include <cstring>
#include <map>
#include <lexer/lexer.hpp>

#ifndef GLOBAL
#define GLOBAL

/// @brief Ruta de instalacion del programa
extern systems::Url installed_program;
/// @brief Ruta de archivo .csg
extern systems::Url sources_configs;
/// @brief Ruta de la carpeta de proyecto
extern systems::Url sources_proyect;
/// @brief Nombre del proyecto
extern std::string name_proyect;

/// @brief Lexer del lenguaje
extern slfbp::lexer lex;


/// @brief lector del archivo
extern systems::ios::ifstream sources;

#define _TRUE "true"
#define _FALSE "false"

#endif