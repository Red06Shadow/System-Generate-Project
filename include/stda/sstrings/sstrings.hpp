#include "stringbuffer.hpp"
#include "converter.hpp"

#ifndef SSTRINGSS
#define SSTRINGSS

/* @Documentacion:
 * Este archivo contiene funciones utiles para el manejo de cadenas de caracteres
 * en proximas actualizaciones se tiene pensado agregar mas de estas funciones pero
 * por el momento solo agregue estas para completar partes imporatntes de mis proyectos
 */

namespace sstring
{
    /// @brief Elimina los caracteres de espacio de la cadena
    /// @param str Cadena que se desea modificar de tipo (?std::string?)
    void removeespaces(std::string &str);
    /// @brief Elimina los caracteres de espacio de la cadena
    /// @param str Cadena que se desea modificar de tipo (?std::wstring?)
    void removeespaces(std::wstring &str);
    /////////////////////////////////////
    /// @brief Elimina los caracteres de espacio del principio de la cadena
    /// @param str Cadena que se desea modificar de tipo (?std::string?)
    void removebeginespaces(std::string &str);
    /// @brief Elimina los caracteres de espacio del principio de la cadena
    /// @param str Cadena que se desea modificar de tipo (?std::wstring?)
    void removebeginespaces(std::wstring &str);
    /////////////////////////////////////
    /// @brief Identifica si el caracter es un numero o una letra
    /// @param caracter Caracter de tipo (?char?)
    /// @return Devuelve verdadero si se cumple
    bool isalfanum(char caracter);
    /// @brief Identifica si el caracter es un numero o una letra
    /// @param caracter Caracter de tipo (?wchar_t?)
    /// @return Devuelve verdadero si se cumple
    bool isalfanum(wchar_t caracter);
    /// @brief Indica si la cadena de caracteres es alfanumerica, o sea si todos los caracteres son o numeros o letras
    /// @param str Cadena de caracteres de tipo (?std::string?)
    /// @return Devuelve verdadero si se cumple
    bool isalfanum(const std::string &str);
    /// @brief Indica si la cadena de caracteres es alfanumerica, o sea si todos los caracteres son o numeros o letras
    /// @param str Cadena de caracteres de tipo (?std::wstring?)
    /// @return Devuelve verdadero si se cumple
    bool isalfanum(const std::wstring &str);
    /////////////////////////////////////
    /// @brief Convierte de minusculas a mayusculas los caracteres
    /// @param str Cadena de caracteres a modificar de tipo (?std::string?)
    void tooper(std::string &str);
    /////////////////////////////////////
    /// @brief Obtiene la primera palabra en la pocision especificada
    /// @param sources Cadena de caracteres de tipo (?const char*?)
    /// @param destine Referencia a una cadena de caracteres de tipo (?char*&?) (!Atencion: La cadena debe ser nullptr ya que dentro de esta se genera el espacio necesario para guardar la palabra!)
    /// @param index Posicion donde se desea buscar
    void word(const char *sources, char *&destine, size_t index = 0);
    /// @brief Obtiene la primera palabra en la pocision especificada
    /// @param sources Cadena de caracteres de tipo (?const wchar_t*?)
    /// @param destine Referencia a una cadena de caracteres de tipo (?wchar_t*&?) (!Atencion: La cadena debe ser nullptr ya que dentro de esta se genera el espacio necesario para guardar la palabra!)
    /// @param index Posicion donde se desea buscar
    void word(const wchar_t *sources, wchar_t *&destine, size_t index = 0);
    /// @brief Obtiene la primera palabra en la pocision especificada
    /// @param sources Cadena de caracteres de tipo (?std::string?)
    /// @param destine Referencia a una cadena de caracteres de tipo (?std::string&?) (!Atencion: La cadena debe estar vacia ya que usa push_back para guardar los caracteres!)
    /// @param index Posicion donde se desea buscar
    void word(const std::string &sources, std::string &destine, size_t index = 0);
    /// @brief Obtiene la primera palabra en la pocision especificada
    /// @param sources Cadena de caracteres de tipo (?std::wstring?)
    /// @param destine Referencia a una cadena de caracteres de tipo (?std::wstring&?) (!Atencion: La cadena debe estar vacia ya que usa push_back para guardar los caracteres!)
    /// @param index Posicion donde se desea buscar
    void word(const std::wstring &sources, std::wstring &destine, size_t index = 0);
    /// @brief Obtiene la primera palabra en la pocision especificada
    /// @param sources Cadena de caracteres de tipo (?stringbuffer?)
    /// @param destine Referencia a una cadena de caracteres de tipo (?stringbuffer&?) (!Atencion: La cadena debe estar vacia ya que dentro de esta se genera el espacio necesario para guardar la palabra!)
    /// @param index Posicion donde se desea buscar
    void word(const stringbuffer &sources, stringbuffer &destine, size_t index = 0);
    /// @brief Obtiene la primera palabra en la pocision especificada
    /// @param sources Cadena de caracteres de tipo (?wstringbuffer?)
    /// @param destine Referencia a una cadena de caracteres de tipo (?wstringbuffer&?) (!Atencion: La cadena debe estar vacia ya que dentro de esta se genera el espacio necesario para guardar la palabra!)
    /// @param index Posicion donde se desea buscar
    void word(const wstringbuffer &sources, wstringbuffer &destine, size_t index = 0);
    /////////////////////////////////////
    /// @brief Genera la cadena inversa a partir de la entrada
    /// @param str Cadena de caracteres de tipo (?const char*?)
    /// @param destine Referencia a una cadena de caracteres de tipo (?char*&?) (!Atencion: La cadena debe ser nullptr ya que dentro de esta se genera el espacio necesario para guardar la palabra!)
    void reverse(const char *str, char *&destine);
    /// @brief Genera la cadena inversa a partir de la entrada
    /// @param str Cadena de caracteres de tipo (?const wchar_t*?)
    /// @param destine Referencia a una cadena de caracteres de tipo (?wchar_t*&?) (!Atencion: La cadena debe ser nullptr ya que dentro de esta se genera el espacio necesario para guardar la palabra!)
    void reverse(const wchar_t *str, wchar_t *&destine);
    /// @brief Genera la cadena inversa a partir de la entrada
    /// @param str Cadena de caracteres de tipo (?std::string?)
    /// @param destine Referencia a una cadena de caracteres de tipo (?std::string&?) (!Atencion: La cadena debe ser nullptr ya que dentro de esta se genera el espacio necesario para guardar la palabra!)
    void reverse(const std::string &str, std::string &destine);
    /// @brief Genera la cadena inversa a partir de la entrada
    /// @param str Cadena de caracteres de tipo (?std::wstring?)
    /// @param destine Referencia a una cadena de caracteres de tipo (?std::wstring&?) (!Atencion: La cadena debe ser nullptr ya que dentro de esta se genera el espacio necesario para guardar la palabra!)
    void reverse(const std::wstring &str, std::wstring &destine);
    /// @brief Genera la cadena inversa a partir de la entrada
    /// @param str Cadena de caracteres de tipo (?stringbuffer?)
    /// @param destine Referencia a una cadena de caracteres de tipo (?stringbuffer&?) (!Atencion: La cadena debe ser nullptr ya que dentro de esta se genera el espacio necesario para guardar la palabra!)
    void reverse(const stringbuffer &str, stringbuffer &destine);
    /// @brief Genera la cadena inversa a partir de la entrada
    /// @param str Cadena de caracteres de tipo (?wstringbuffer?)
    /// @param destine Referencia a una cadena de caracteres de tipo (?wstringbuffer&?) (!Atencion: La cadena debe ser nullptr ya que dentro de esta se genera el espacio necesario para guardar la palabra!)
    void reverse(const wstringbuffer &str, wstringbuffer &destine);
    /////////////////////////////////////

    /// @brief Remplaca todas las referencias de un caracter dentro de la cadena por otro espeficicado
    /// @param str Cadena de caracteres de tipo (?char*?)
    /// @param find Caracter que se va a buscar de tipo (?char?)
    /// @param replacer Caracter que remplazara al buscado de tipo (?char?)
    void replaceAll(char *str, char find, char replacer);
    /// @brief Remplaca todas las referencias de un caracter dentro de la cadena por otro espeficicado
    /// @param str Cadena de caracteres de tipo (?wchar_t*?)
    /// @param find Caracter que se va a buscar de tipo (?wchar_t?)
    /// @param replacer Caracter que remplazara al buscado de tipo (?wchar_t?)
    void replaceAll(wchar_t *str, wchar_t find, wchar_t replacer);
    /// @brief Remplaca todas las referencias de un caracter dentro de la cadena por otro espeficicado
    /// @param str Cadena de caracteres de tipo (?std::string?)
    /// @param find Caracter que se va a buscar de tipo (?char?)
    /// @param replacer Caracter que remplazara al buscado de tipo (?char?)
    void replaceAll(std::string &str, char find, char replacer);
    /// @brief Remplaca todas las referencias de un caracter dentro de la cadena por otro espeficicado
    /// @param str Cadena de caracteres de tipo (?std::wstring?)
    /// @param find Caracter que se va a buscar de tipo (?wchar_t?)
    /// @param replacer Caracter que remplazara al buscado de tipo (?wchar_t?)
    void replaceAll(std::wstring &str, wchar_t find, wchar_t replacer);
    /// @brief Remplaca todas las referencias de un caracter dentro de la cadena por otro espeficicado
    /// @param str Cadena de caracteres de tipo (?stringbuffer?)
    /// @param find Caracter que se va a buscar de tipo (?char?)
    /// @param replacer Caracter que remplazara al buscado de tipo (?char?)
    void replaceAll(stringbuffer &str, char find, char replacer);
    /// @brief Remplaca todas las referencias de un caracter dentro de la cadena por otro espeficicado
    /// @param str Cadena de caracteres de tipo (?wstringbuffer?)
    /// @param find Caracter que se va a buscar de tipo (?wchar_t?)
    /// @param replacer Caracter que remplazara al buscado de tipo (?wchar_t?)
    void replaceAll(wstringbuffer &str, wchar_t find, wchar_t replacer);
    /////////////////////////////////////
    /// @brief Busca el primer elemnto de la cadena de caracteres que coincida con el pasado por parametro
    /// @param str Cadena de caracteres de tipo (?const char*?)
    /// @param caracter Caracter que se va a buscar de tipo (?char?)
    /// @param position Posicion de inicio de ese caracter
    /// @return Devuleve -1 si no lo encuentra si lo envuentra devuleve la pocision
    size_t find_frist_of(const char *str, char caracter, size_t position = 0);
    /// @brief Busca el primer elemnto de la cadena de caracteres que coincida con el pasado por parametro
    /// @param str Cadena de caracteres de tipo (?const char*?)
    /// @param cmp Funcion que debe retornar un (?bool?) en caso de que se cumpla cierta condicion sobre el caracter accedido
    /// @param position Posicion de inicio de ese caracter
    /// @return Devuleve -1 si no lo encuentra si lo envuentra devuleve la pocision
    size_t find_frist_of(const char *str, bool (*cmp)(char), size_t position = 0);
    /// @brief Busca el primer elemnto de la cadena de caracteres que coincida con el pasado por parametro
    /// @param str Cadena de caracteres de tipo (?const wchar_t*?)
    /// @param caracter Caracter que se va a buscar de tipo (?wchar_t?)
    /// @param position Posicion de inicio de ese caracter
    /// @return Devuleve -1 si no lo encuentra si lo envuentra devuleve la pocision
    size_t find_frist_of(const wchar_t *str, wchar_t caracter, size_t position = 0);
    /// @brief Busca el primer elemnto de la cadena de caracteres que coincida con el pasado por parametro
    /// @param str Cadena de caracteres de tipo (?const wchar_t*?)
    /// @param cmp Funcion que debe retornar un (?bool?) en caso de que se cumpla cierta condicion sobre el caracter accedido
    /// @param position Posicion de inicio de ese caracter
    /// @return Devuleve -1 si no lo encuentra si lo envuentra devuleve la pocision
    size_t find_frist_of(const wchar_t *str, bool (*cmp)(wchar_t), size_t position = 0);
    /////////////////////////////////////
    /// @brief Busca el primer elemnto que no sea igual al que se pasa por parametro de la cadena de caracteres
    /// @param str Cadena de caracteres de tipo (?const char*?)
    /// @param caracter Caracter que se va a buscar de tipo (?char?)
    /// @param position Posicion de inicio de ese caracter
    /// @return Devuleve -1 si no lo encuentra si lo envuentra devuleve la pocision
    size_t find_frist_not_of(const char *str, char caracter, size_t position = 0);
    /// @brief Busca el primer elemnto que no sea igual al que se pasa por parametro de la cadena de caracteres
    /// @param str Cadena de caracteres de tipo (?const char*?)
    /// @param cmp Funcion que debe retornar un (?bool?) en caso de que se cumpla cierta condicion sobre el caracter accedido
    /// @param position Posicion de inicio de ese caracter
    /// @return Devuleve -1 si no lo encuentra si lo envuentra devuleve la pocision
    size_t find_frist_not_of(const char *str, bool (*cmp)(char), size_t position = 0);
    /// @brief Busca el primer elemnto que no sea igual al que se pasa por parametro de la cadena de caracteres
    /// @param str Cadena de caracteres de tipo (?const wchar_t*?)
    /// @param caracter Caracter que se va a buscar de tipo (?wchar_t?)
    /// @param position Posicion de inicio de ese caracter
    /// @return Devuleve -1 si no lo encuentra si lo envuentra devuleve la pocision
    size_t find_frist_not_of(const wchar_t *str, wchar_t caracter, size_t position = 0);
    /// @brief Busca el primer elemnto que no sea igual al que se pasa por parametro de la cadena de caracteres
    /// @param str Cadena de caracteres de tipo (?const wchar_t*?)
    /// @param cmp Funcion que debe retornar un (?bool?) en caso de que se cumpla cierta condicion sobre el caracter accedido
    /// @param position Posicion de inicio de ese caracter
    /// @return Devuleve -1 si no lo encuentra si lo envuentra devuleve la pocision
    size_t find_frist_not_of(const wchar_t *str, bool (*cmp)(wchar_t), size_t position = 0);
    /////////////////////////////////////
    /// @brief Busca el ultimo elemnto de la cadena de caracteres que coincida con el pasado por parametro
    /// @param str Cadena de caracteres de tipo (?const char*?)
    /// @param caracter Caracter que se va a buscar de tipo (?char?)
    /// @param position Posicion de inicio de ese caracter
    /// @return Devuleve -1 si no lo encuentra si lo envuentra devuleve la pocision
    size_t find_last_of(const char *str, char caracter, size_t position = size_t(-1));
    /// @brief Busca el ultimo elemnto de la cadena de caracteres que coincida con el pasado por parametro
    /// @param str Cadena de caracteres de tipo (?const char*?)
    /// @param cmp Funcion que debe retornar un (?bool?) en caso de que se cumpla cierta condicion sobre el caracter accedido
    /// @param position Posicion de inicio de ese caracter
    /// @return Devuleve -1 si no lo encuentra si lo envuentra devuleve la pocision
    size_t find_last_of(const char *str, bool (*cmp)(char), size_t position = size_t(-1));
    /// @brief Busca el ultimo elemnto de la cadena de caracteres que coincida con el pasado por parametro
    /// @param str Cadena de caracteres de tipo (?const wchar_t*?)
    /// @param caracter Caracter que se va a buscar de tipo (?wchar_t?)
    /// @param position Posicion de inicio de ese caracter
    /// @return Devuleve -1 si no lo encuentra si lo envuentra devuleve la pocision
    size_t find_last_of(const wchar_t *str, wchar_t caracter, size_t position = size_t(-1));
    /// @brief Busca el ultimo elemnto de la cadena de caracteres que coincida con el pasado por parametro
    /// @param str Cadena de caracteres de tipo (?const wchar_t*?)
    /// @param cmp Funcion que debe retornar un (?bool?) en caso de que se cumpla cierta condicion sobre el caracter accedido
    /// @param position Posicion de inicio de ese caracter
    /// @return Devuleve -1 si no lo encuentra si lo envuentra devuleve la pocision
    size_t find_last_of(const wchar_t *str, bool (*cmp)(wchar_t), size_t position = size_t(-1));
    /////////////////////////////////////
    /// @brief Busca el ultimo elemnto que no sea igual al que se pasa por parametro de la cadena de caracteres
    /// @param str Cadena de caracteres de tipo (?const char*?)
    /// @param caracter Caracter que se va a buscar de tipo (?char?)
    /// @param position Posicion de inicio de ese caracter
    /// @return Devuleve -1 si no lo encuentra si lo envuentra devuleve la pocision
    size_t find_last_not_of(const char *str, char caracter, size_t position = size_t(-1));
    /// @brief Busca el ultimo elemnto que no sea igual al que se pasa por parametro de la cadena de caracteres
    /// @param str Cadena de caracteres de tipo (?const char*?)
    /// @param cmp Funcion que debe retornar un (?bool?) en caso de que se cumpla cierta condicion sobre el caracter accedido
    /// @param position Posicion de inicio de ese caracter
    /// @return Devuleve -1 si no lo encuentra si lo envuentra devuleve la pocision
    size_t find_last_not_of(const char *str, bool (*cmp)(char), size_t position = size_t(-1));
    /// @brief Busca el ultimo elemnto que no sea igual al que se pasa por parametro de la cadena de caracteres
    /// @param str Cadena de caracteres de tipo (?const wchar_t*?)
    /// @param caracter Caracter que se va a buscar de tipo (?wchar_t?)
    /// @param position Posicion de inicio de ese caracter
    /// @return Devuleve -1 si no lo encuentra si lo envuentra devuleve la pocision
    size_t find_last_not_of(const wchar_t *str, wchar_t caracter, size_t position = size_t(-1));
    /// @brief Busca el ultimo elemnto que no sea igual al que se pasa por parametro de la cadena de caracteres
    /// @param str Cadena de caracteres de tipo (?const wchar_t*?)
    /// @param cmp Funcion que debe retornar un (?bool?) en caso de que se cumpla cierta condicion sobre el caracter accedido
    /// @param position Posicion de inicio de ese caracter
    /// @return Devuleve -1 si no lo encuentra si lo envuentra devuleve la pocision
    size_t find_last_not_of(const wchar_t *str, bool (*cmp)(wchar_t), size_t position = size_t(-1));
    /////////////////////////////////////
    /// @brief Busca si existe esa palabra dentro de la cadena sources
    /// @param word Palabra que se desea buscar
    /// @param sources Cadena donde se buscara la palabra
    /// @return Devuleve -1 si no la encuentra, si la encuentra devuleve la pocision dada
    size_t find_word(const std::string& word, const std::string& sources);
} // namespace sstring
#endif