#include <global/global.hpp>

/// @brief Ruta de instalacion del programa
systems::Url installed_program = systems::Url();
/// @brief Ruta de archivo .csg
systems::Url sources_configs = systems::Url();
/// @brief Ruta de la carpeta de proyecto
systems::Url sources_proyect = systems::Url();
/// @brief Nombre del proyecto
std::string name_proyect = "\0";

/// @brief Lexer del lenguaje
slfbp::lexer lex = slfbp::lexer({"@", ":", "[", "]", "(", ")", ","});


/// @brief lector del archivo
systems::ios::ifstream sources = systems::ios::ifstream();