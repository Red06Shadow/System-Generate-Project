#include <cstring>
#include <iostream>
#include <stdexcept>
#include <stda/trails/trails.hpp>

#ifndef STRINGBUFFER
#define STRINGBUFFER

/* @Documentacion:
 * Este archivo contiene las clases (?stringbuffer?) y (?wstringbuffer?) tipos
 * de cadenas de tamano estatico de manera que no se requiera cambiar tamano
 * pero se puedan aplicar las funcionalidades de (?std::string?) dentro de esta
 */

/// @brief Clase de cadena de caracteres de 1 byte
class stringbuffer
{
private:
    /// @brief Objecto (?trails<char>?) para almacenar elementos
    trails<char> buffer;

public:
    /// @brief Constructor por defecto
    stringbuffer() : buffer() {}
    /// @brief Constructor pra cadenas vacias de tamano fijo
    /// @param size Tamano de la cadena(!Importatnte: El tamano siempre sera sumado en 1 para la definicion del ultimo caracater nulo!)
    stringbuffer(size_t size) : buffer(size + 1) {}
    /// @brief Constructor con parametro (?const char*?)
    /// @param __str Cadena de caracteres (?const char*?)
    stringbuffer(const char *__str);
    /// @brief Constructor con parametro (?const char*?) y parametro de tamano para copiar solo una parte de la cadena
    /// @param __str Cadena de caracteres (?const char*?)
    /// @param size Tmanao de la cadena(!Atencion: Si define el tamano mayor al de la cadena esta generara caracteres vacios!)
    stringbuffer(const char *__str, size_t size);
    stringbuffer(const stringbuffer &other);
    stringbuffer(stringbuffer &&other);
    stringbuffer &operator=(const stringbuffer &other);
    stringbuffer &operator=(stringbuffer &&other);
    /// @brief Obtiene la cadena de caracteres
    /// @return Devuelve el puntero de la cadena de caracteres como un (?const char*?)
    const char *c_str() const { return *buffer; }
    /// @brief Operador de acceso inmediato a un caracter
    /// @param position Posicion del elemento
    /// @return Devuelve una referencia al valor (?char?) de la cadena en dicha pocision
    char &operator[](size_t position);
    /// @brief Funcion de acceso a un caracter
    /// @param position Posicion del elemento
    /// @return Devuelve el valor (?char?) de la cadena en dicha pocision
    const char at(size_t position) const;
    /// @brief Indica si la cadena esta vacia
    /// @return Devuelve verdadero si lo esta
    bool empty() const { return ((buffer.empty()) ? true : !(buffer.size() - 1)); }
    /// @brief Funcion para obtener el tamano de la cadena
    /// @return Devuelve el tamano de la cadena
    size_t size() const { return ((buffer.empty()) ? 0 : buffer.size() - 1); }
    /// @brief Copia la cadena de texto pasada por argumento al interior
    /// @param __str Cadena de caracteres tipo (?const char*?)
    void copy(const char *__str);
    /// @brief Copia la cadena de texto pasada por argumento al interior, en base a un numero de elementos
    /// @param __str Cadena de caracteres tipo (?const char*?)
    /// @param nelements Numero de elementos a copiar
    void copy(const char *__str, size_t nelements);
    /// @brief Copia la cadena de texto pasada por argumento al interior
    /// @param __str Cadena de caracteres tipo (?stringbuffer?)
    void copy(const stringbuffer &str);
    /// @brief Copia la cadena de texto pasada por argumento al interior, en base a un numero de elementos
    /// @param __str Cadena de caracteres tipo (?stringbuffer?)
    /// @param nelements Numero de elementos a copiar
    void copy(const stringbuffer &str, size_t nelements);
    friend std::ostream &operator<<(std::ostream &os, const stringbuffer &str)
    {
        os << *str.buffer;
        return os;
    }
    /// @brief Clase que define la iteracion reversa para (?stringbuffer?)
    class reverse
    {
    private:
        const char *__arrarptr__;
        size_t __size__;

    public:
        /// @brief Constructor de la clase (?stringbuffer::reverse?) para generar la reversa a partir de la cadena original
        /// @param __base Instancia de la clase (?stringbuffer?)
        reverse(const stringbuffer &__base) : __arrarptr__(*__base.buffer), __size__(__base.size()) {}
        /// @brief Punto de partida de la iteracion reversa del array
        /// @return Devuelve el iterador que apunta al elemento final del array
        iterators::reverse_iterator<char> begin() const { return iterators::reverse_iterator<char>(__arrarptr__ ? nullptr : __arrarptr__ + __size__ - 1); }
        /// @brief Punto final de la iteracion reversa del array
        /// @return Devuelve el iterador que apunta al elemento inicial del array
        iterators::reverse_iterator<char> end() const { return iterators::reverse_iterator<char>(__arrarptr__ ? nullptr : __arrarptr__ - 1); }
        ~reverse() {}
    };
    /// @brief Punto de partida de la iteracion del array
    /// @return Devuelve el iterador que apunta al elemento inicial del array
    iterators::iterator<char> begin() const { return iterators::iterator<char>(empty() ? nullptr : *buffer); }
    /// @brief Punto final de la iteracion del array
    /// @return Devuelve el iterador que apunta al elemento final del array
    iterators::iterator<char> end() const { return iterators::iterator<char>(empty() ? nullptr : *buffer + buffer.size()); }

    /// @brief Punto de partida de la iteracion reversa del array
    /// @return Devuelve el iterador que apunta al elemento final del array
    iterators::reverse_iterator<char> rbegin() const { return iterators::reverse_iterator<char>(empty() ? nullptr : *buffer + buffer.size() - 1); }
    /// @brief Punto final de la iteracion reversa del array
    /// @return Devuelve el iterador que apunta al elemento inicial del array
    iterators::reverse_iterator<char> rend() const { return iterators::reverse_iterator<char>(empty() ? nullptr : *buffer - 1); }

    bool operator==(const std::string& str) {
        return std::strcmp(str.c_str(), *buffer) == 0;
    }
    bool operator==(const stringbuffer& str) {
        return std::strcmp(str.c_str(), *buffer) == 0;
    }
    bool operator==(const char* str) {
        return std::strcmp(str, *buffer) == 0;
    }
    bool operator!=(const std::string& str) {
        return std::strcmp(str.c_str(), *buffer) != 0;
    }
    bool operator!=(const stringbuffer& str) {
        return std::strcmp(str.c_str(), *buffer) != 0;
    }
    bool operator!=(const char* str) {
        return std::strcmp(str, *buffer) != 0;
    }

    bool operator>(const std::string& str) {
        return std::strcmp(str.c_str(), *buffer) > 0;
    }
    bool operator>(const stringbuffer& str) {
        return std::strcmp(str.c_str(), *buffer) > 0;
    }
    bool operator>(const char* str) {
        return std::strcmp(str, *buffer) > 0;
    }
    bool operator<(const std::string& str) {
        return std::strcmp(str.c_str(), *buffer) < 0;
    }
    bool operator<(const stringbuffer& str) {
        return std::strcmp(str.c_str(), *buffer) < 0;
    }
    bool operator<(const char* str) {
        return std::strcmp(str, *buffer) < 0;
    }

    bool operator>=(const std::string& str) {
        return std::strcmp(str.c_str(), *buffer) >= 0;
    }
    bool operator>=(const stringbuffer& str) {
        return std::strcmp(str.c_str(), *buffer) >= 0;
    }
    bool operator>=(const char* str) {
        return std::strcmp(str, *buffer) >= 0;
    }
    bool operator<=(const std::string& str) {
        return std::strcmp(str.c_str(), *buffer) <= 0;
    }
    bool operator<=(const stringbuffer& str) {
        return std::strcmp(str.c_str(), *buffer) <= 0;
    }
    bool operator<=(const char* str) {
        return std::strcmp(str, *buffer) <= 0;
    }

    ~stringbuffer() {}
};

/// @brief Clase de cadena de caracteres de 2 byte
class wstringbuffer
{
private:
    /// @brief Objecto (?trails<wchar_t>?) para almacenar elementos
    trails<wchar_t> buffer;

public:
    /// @brief Constructor por defecto
    wstringbuffer() : buffer() {}
    /// @brief Constructor pra cadenas vacias de tamano fijo
    /// @param size Tamano de la cadena(!Importatnte: El tamano siempre sera sumado en 1 para la definicion del ultimo caracater nulo!)
    wstringbuffer(size_t size) : buffer(size + 1) {}
    /// @brief Constructor con parametro (?const wchar_t*?)
    /// @param __str Cadena de caracteres (?const wchar_t*?)
    wstringbuffer(const wchar_t *__str);
    /// @brief Constructor con parametro (?const wchar_t*?) y parametro de tamano para copiar solo una parte de la cadena
    /// @param __str Cadena de caracteres (?const wchar_t*?)
    /// @param size Tmanao de la cadena(!Atencion: Si define el tamano mayor al de la cadena esta generara caracteres vacios!)
    wstringbuffer(const wchar_t *__str, size_t size);
    wstringbuffer(const wstringbuffer &other);
    wstringbuffer(wstringbuffer &&other);
    wstringbuffer &operator=(const wstringbuffer &other);
    wstringbuffer &operator=(wstringbuffer &&other);
    /// @brief Obtiene la cadena de caracteres
    /// @return Devuelve el puntero de la cadena de caracteres como un (?const wchar_t*?)
    const wchar_t *c_str() const { return *buffer; }
    /// @brief Operador de acceso inmediato a un caracter
    /// @param position Posicion del elemento
    /// @return Devuelve una referencia al valor (?wchar_t?) de la cadena en dicha pocision
    wchar_t &operator[](size_t position);
    /// @brief Funcion de acceso a un caracter
    /// @param position Posicion del elemento
    /// @return Devuelve el valor (?wchar_t?) de la cadena en dicha pocision
    const wchar_t at(size_t position) const;
    /// @brief Indica si la cadena esta vacia
    /// @return Devuelve verdadero si lo esta
    bool empty() const { return buffer.empty(); }
    /// @brief Funcion para obtener el tamano de la cadena
    /// @return Devuelve el tamano de la cadena
    size_t size() const { return (buffer.empty() ? 0 : buffer.size() - 1); }
    /// @brief Copia la cadena de texto pasada por argumento al interior
    /// @param __str Cadena de caracteres tipo (?const wchar_t*?)
    void copy(const wchar_t *__str);
    /// @brief Copia la cadena de texto pasada por argumento al interior, en base a un numero de elementos
    /// @param __str Cadena de caracteres tipo (?const wchar_t*?)
    /// @param nelements Numero de elementos a copiar
    void copy(const wchar_t *__str, size_t nelements);
    /// @brief Copia la cadena de texto pasada por argumento al interior
    /// @param __str Cadena de caracteres tipo (?wstringbuffer?)
    void copy(const wstringbuffer &str);
    /// @brief Copia la cadena de texto pasada por argumento al interior, en base a un numero de elementos
    /// @param __str Cadena de caracteres tipo (?wstringbuffer?)
    /// @param nelements Numero de elementos a copiar
    void copy(const wstringbuffer &str, size_t nelements);
    friend std::ostream &operator<<(std::ostream &os, const wstringbuffer &str)
    {
        os << *str.buffer;
        return os;
    }
    /// @brief Clase que define la iteracion reversa para (?stringbuffer?)
    class reverse
    {
    private:
        const wchar_t *__arrarptr__;
        size_t __size__;

    public:
        /// @brief Constructor de la clase (?stringbuffer::reverse?) para generar la reversa a partir de la cadena original
        /// @param __base Instancia de la clase (?stringbuffer?)
        reverse(const wstringbuffer &__base) : __arrarptr__(*__base.buffer), __size__(__base.size()) {}
        /// @brief Punto de partida de la iteracion reversa del array
        /// @return Devuelve el iterador que apunta al elemento final del array
        iterators::reverse_iterator<wchar_t> begin() const { return iterators::reverse_iterator<wchar_t>(__arrarptr__ ? nullptr : __arrarptr__ + __size__ - 1); }
        /// @brief Punto final de la iteracion reversa del array
        /// @return Devuelve el iterador que apunta al elemento inicial del array
        iterators::reverse_iterator<wchar_t> end() const { return iterators::reverse_iterator<wchar_t>(__arrarptr__ ? nullptr : __arrarptr__ - 1); }
        ~reverse() {}
    };
    /// @brief Punto de partida de la iteracion del array
    /// @return Devuelve el iterador que apunta al elemento inicial del array
    iterators::iterator<wchar_t> begin() const { return iterators::iterator<wchar_t>(empty() ? nullptr : *buffer); }
    /// @brief Punto final de la iteracion del array
    /// @return Devuelve el iterador que apunta al elemento final del array
    iterators::iterator<wchar_t> end() const { return iterators::iterator<wchar_t>(empty() ? nullptr : *buffer + buffer.size()); }

    /// @brief Punto de partida de la iteracion reversa del array
    /// @return Devuelve el iterador que apunta al elemento final del array
    iterators::reverse_iterator<wchar_t> rbegin() const { return iterators::reverse_iterator<wchar_t>(empty() ? nullptr : *buffer + buffer.size() - 1); }
    iterators::reverse_iterator<wchar_t> rend() const { return iterators::reverse_iterator<wchar_t>(empty() ? nullptr : *buffer - 1); }

    
    bool operator==(const std::wstring& str) {
        return std::wcscmp(str.c_str(), *buffer) == 0;
    }
    bool operator==(const wstringbuffer& str) {
        return std::wcscmp(str.c_str(), *buffer) == 0;
    }
    bool operator==(const wchar_t* str) {
        return std::wcscmp(str, *buffer) == 0;
    }
    bool operator!=(const std::wstring& str) {
        return std::wcscmp(str.c_str(), *buffer) != 0;
    }
    bool operator!=(const wstringbuffer& str) {
        return std::wcscmp(str.c_str(), *buffer) != 0;
    }
    bool operator!=(const wchar_t* str) {
        return std::wcscmp(str, *buffer) != 0;
    }

    bool operator>(const std::wstring& str) {
        return std::wcscmp(str.c_str(), *buffer) > 0;
    }
    bool operator>(const wstringbuffer& str) {
        return std::wcscmp(str.c_str(), *buffer) > 0;
    }
    bool operator>(const wchar_t* str) {
        return std::wcscmp(str, *buffer) > 0;
    }
    bool operator<(const std::wstring& str) {
        return std::wcscmp(str.c_str(), *buffer) < 0;
    }
    bool operator<(const wstringbuffer& str) {
        return std::wcscmp(str.c_str(), *buffer) < 0;
    }
    bool operator<(const wchar_t* str) {
        return std::wcscmp(str, *buffer) < 0;
    }

    bool operator>=(const std::wstring& str) {
        return std::wcscmp(str.c_str(), *buffer) >= 0;
    }
    bool operator>=(const wstringbuffer& str) {
        return std::wcscmp(str.c_str(), *buffer) >= 0;
    }
    bool operator>=(const wchar_t* str) {
        return std::wcscmp(str, *buffer) >= 0;
    }
    bool operator<=(const std::wstring& str) {
        return std::wcscmp(str.c_str(), *buffer) <= 0;
    }
    bool operator<=(const wstringbuffer& str) {
        return std::wcscmp(str.c_str(), *buffer) <= 0;
    }
    bool operator<=(const wchar_t* str) {
        return std::wcscmp(str, *buffer) <= 0;
    }


    ~wstringbuffer() {}
};

#endif