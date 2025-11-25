#include <iostream>
#include <stda/iterator/iterator.hpp>

#ifndef TRAISSTDS
#define TRAISSTDS

/* @Documentacion:
 * Este archivo contiene la clase trails, una clase que genera arreglos estaticos de datos y ofrece funcionalidades para manejarlos
 * Proximamente se espera crear una clase que se comporte de manera similar a vector para mejorar su uso
 */

/// @brief Clase trails para la cual dado un tipo de dato definido por T genera el arreglo
/// @tparam T Tipo de dato a almacenar
template <typename T>
class trails
{
protected:
    size_t __size__;
    T *__array__;

public:
    /// @brief Constructor por defecto
    trails() : __array__(nullptr), __size__(0) {}
    /// @brief Constructor que usa un arreglo predefinido
    /// @param __array Arreglo de elementos del mismo tipo que T
    /// @param size Tamano del arreglo(!Atencion: Si el tamano es mayor que el original del arreglo causara errores de segmentation fault!)
    trails(const T __array[], size_t size);
    /// @brief Constructor que genera un arreglo a partir de un numero de elementos dados
    /// @param size Numero de elementos a tener
    trails(size_t size);
    trails(const trails<T> &other) : trails<T>()
    {
        *this = other;
    }
    trails(trails<T> &&other) noexcept : __array__(other.__array__), __size__(other.__size__)
    {
        other.__size__ = 0;
        other.__array__ = nullptr;
    }
    trails<T> &operator=(const trails<T> &other)
    {
        if (this != &other)
        {
            if (__array__ != nullptr)
                delete[] (__array__);
            __size__ = other.__size__;
            if (__size__ > 0)
            {
                __array__ = new T[__size__];
                std::copy(other.__array__, other.__array__ + __size__, __array__);
            }
            else
            {
                __array__ = nullptr;
            }
        }
        return *this;
    }
    trails<T> &operator=(trails<T> &&other)
    {
        if (this != &other)
        {
            if (__array__ != nullptr)
                delete[] (__array__);
            __size__ = other.__size__;
            __array__ = other.__array__;
            other.__array__ = nullptr;
            other.__size__ = 0;
        }
        return *this;
    }
    /// @brief Operador de acceso inmediato al valor de tipo T
    /// @param pos Pocision del elemento(!Atencion: Si se accede a un elemnto que este fuera del rango dara error!)
    /// @return Devuelve una referencia a ese objecto
    T &operator[](size_t pos)
    {
        return __array__[pos];
    }
    /// @brief Operador de acceso inmediato al valor de tipo T
    /// @param pos Pocision del elemento(!Atencion: Si se accede a un elemnto que este fuera del rango dara error!)
    /// @return Devuelve una referencia constante a ese objecto
    const T &operator[](size_t pos) const
    {
        return __array__[pos];
    }
    /// @brief Asigna directamente una instancia de (?trails<T>?) al elemento que se aplica el metodo
    /// @param __other Otro elemento de tipo (?trails<T>?)
    void assing(const trails<T> &__other);
    /// @brief Copia directamente una instancia de (?trails<T>?) al elemento que se aplica el metodo
    /// @param __other Otro elemento de tipo (?trails<T>?)
    void copy(const trails<T> &__other);
    /// @brief Copia directamente una instancia de (?trails<T>?) al elemento que se aplica el metodo en base a un numero de elemntos
    /// @param __other Otro elemento de tipo (?trails<T>?)
    /// @param nelements numero de elementos a copiar(!Atencion: Si el tamano es mayor que el original del arreglo causara errores de segmentation fault!)
    void copy(const trails<T> &__other, size_t nelements);
    /// @brief Funcion de acceso al valor de tipo T
    /// @param pos Pocision del elemento(!Atencion: Si se accede a un elemnto que este fuera del rango dara error!)
    /// @return Devuelve el elemento de esa posicion
    T at(size_t pos) const;
    /// @brief Obtiene el tamano del arreglo
    /// @return Devuelve el numero de elementos
    inline size_t size() const { return __size__; }
    /// @brief Comprueba si esta vacio el arreglo
    /// @return Devuelve si se cumple la condicion
    inline bool empty() const { return __size__ == 0; }
    friend std::ostream &operator<<(std::ostream &os, const trails<T> &__array)
    {
        os << '[';
        for (size_t i = 0; i < __array.__size__; i++)
            os << __array.__array__[i] << (__array.__size__ - 1 == i ? "" : ", ");
        os << ']' << std::endl;
        return os;
    }
    /// @brief Clase que maneja la reversa del array
    class reverse
    {
    private:
        const T *__arrarptr__;
        size_t __size__;

    public:
        /// @brief Constructor de la clase (?trails<T>::reverse?) para generar la reversa a partir de la cadena original
        /// @param __base Instancia de la clase (?trails<T>?)
        reverse(const trails<T> &__base) : __arrarptr__(__base.__array__), __size__(__base.__size__) {}
        /// @brief Punto de partida de la iteracion reversa del array
        /// @return Devuelve el iterador que apunta al elemento final del array
        iterators::reverse_iterator<T> begin() const { return iterators::reverse_iterator<T>(__arrarptr__ ? nullptr : __arrarptr__ + __size__ - 1); }
        /// @brief Punto final de la iteracion reversa del array
        /// @return Devuelve el iterador que apunta al elemento inicial del array
        iterators::reverse_iterator<T> end() const { return iterators::reverse_iterator<T>(__arrarptr__ ? nullptr : __arrarptr__ - 1); }
        ~reverse() {}
    };
    /// @brief Punto de partida de la iteracion del array
    /// @return Devuelve el iterador que apunta al elemento inicial del array
    iterators::iterator<T> begin() const { return iterators::iterator<T>(empty() ? nullptr : __array__); }
    /// @brief Punto final de la iteracion del array
    /// @return Devuelve el iterador que apunta al elemento final del array
    iterators::iterator<T> end() const { return iterators::iterator<T>(empty() ? nullptr : __array__ + __size__); }

    /// @brief Punto de partida de la iteracion reversa del array
    /// @return Devuelve el iterador que apunta al elemento final del array
    iterators::reverse_iterator<T> rbegin() const { return iterators::reverse_iterator<T>(empty() ? nullptr : __array__ + __size__ - 1); }
    /// @brief Punto final de la iteracion reversa del array
    /// @return Devuelve el iterador que apunta al elemento inicial del array
    iterators::reverse_iterator<T> rend() const { return iterators::reverse_iterator<T>(empty() ? nullptr : __array__ - 1); }

    /// @brief Operador para acceder directamente al; puntero del array de manera constante de ser necesario
    /// @return Devuelve le direccion de memoria
    const T *operator*() const
    {
        return __array__;
    }

    virtual ~trails()
    {
        delete[] __array__;
        __array__ = nullptr;
    }
};

#include "trails.tpp"

#endif