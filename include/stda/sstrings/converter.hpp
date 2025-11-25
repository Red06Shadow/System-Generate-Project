#include <iostream>
#include <cstring>
#include <string>
#include "stringbuffer.hpp"

#ifndef FORMATSTRING
#define FORMATSTRING

/* @Documentacion:
 * Este archivo presenta las instrucciones para convertir cadenas de caracteres de 1byte a 2byte y viceversa
 */

namespace stringconverter
{
    /// @brief Convierte una cadena de caractres de tipo(?const char*?) a una de tipo (?const wchar_t*?)
    /// @param str Cadena de entrada
    /// @param freeMemory Si se liberara la memoria de esa cadena de entrada o no
    /// @return Devuelve una cadena de tipo (?const wchar_t*?)
    wchar_t *convert_ascii_to_uft8(const char *str, bool freeMemory = false);
    /// @brief Convierte una cadena de caractres de tipo(?std::string*?) a una de tipo (?std::wstring*?)
    /// @param str Cadena de entrada
    /// @return Devuelve una cadena de tipo (?std::wstring*?)
    std::wstring convert_string_to_wstring(const std::string &str);
    /// @brief Convierte una cadena de caractres de tipo(?stringbuffer*?) a una de tipo (?wstringbuffer*?)
    /// @param str Cadena de entrada
    /// @return Devuelve una cadena de tipo (?wstringbuffer*?)
    wstringbuffer convert_stringbuffer_to_wstringbuffer(const stringbuffer&);
    //////////////////////////////////////////////////////////////////////////
    /// @brief Convierte una cadena de caractres de tipo(?const wchar_t*?) a una de tipo (?const char*?)
    /// @param str Cadena de entrada
    /// @param freeMemory Si se liberara la memoria de esa cadena de entrada o no
    /// @return Devuelve una cadena de tipo (?const char*?)
    char *convert_utf8_to_ascii(const wchar_t *wstr, bool freeMemory = false);
    /// @brief Convierte una cadena de caractres de tipo(?std::wstring?) a una de tipo (?std::string?)
    /// @param str Cadena de entrada
    /// @param freeMemory Si se liberara la memoria de esa cadena de entrada o no
    /// @return Devuelve una cadena de tipo (?std::string?)
    std::string convert_wstring_to_string(const std::wstring &str);
    /// @brief Convierte una cadena de caractres de tipo(?wstringbuffer?) a una de tipo (?stringbuffer?)
    /// @param str Cadena de entrada
    /// @param freeMemory Si se liberara la memoria de esa cadena de entrada o no
    /// @return Devuelve una cadena de tipo (?stringbuffer?)
    stringbuffer convert_wstringbuffer_to_stringbuffer(const wstringbuffer&);
}
#endif