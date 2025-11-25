
#ifndef ITERATORS
#define ITERATORS

/* @Documentacion:
 * Este archivo debe contiene la clase de iterdores para T tipo para generar iteradores de cualquier objecto
 * Proximamente se introduciran iteradores a base de funciones que no necesiten de memoria si no de cumplimiento de
 * Funciones booleanas para los recorridos co for-each
*/

namespace iterators
{
    /// @brief Clase iteradora
    /// @tparam T Tipo de dato que se desea(!Atencion: debe coincidir con el tipo de dato que guarda el arreglo!)
    template<typename T>
    class iterator
    {
    private:
        /// @brief Puntero al elemento iterado
        const T *__arrarptr__;

    public:
        /// @brief Contructor de la clase ieradora
        /// @param __arrarptr Direccion de memoria
        explicit iterator(const T *__arrarptr);
        bool operator==(const iterator &otro) const;
        bool operator!=(const iterator &otro) const;
        T &operator*();
        T *operator->();
        iterator operator++()
        {
            this->__arrarptr__++;
            return *this;
        }
        iterator operator++(int)
        {
            iterator temp(*this);
            ++(*this);
            return temp;
        }
        virtual ~iterator();
    };
    /// @brief Clase iteradora de reversa
    /// @tparam T Tipo de dato que se desea(!Atencion: debe coincidir con el tipo de dato que guarda el arreglo!)
    template<typename T>
    class reverse_iterator
    {
    private:
        /// @brief Puntero al elemento iterado
        const T *__arrarptr__;

    public:
        /// @brief Contructor de la clase ieradora
        /// @param __arrarptr Direccion de memoria(!Atencion: El iterador de inicio debe ser la direccion final o la direccion de inicio mas el tamano disminuido en 1! y el valor del iterador final la direccion de inicio - 1 para que funcione correctamente en caso de arreglos o trails<T>)
        explicit reverse_iterator(const T *__arrarptr);
        bool operator==(const reverse_iterator &otro) const;
        bool operator!=(const reverse_iterator &otro) const;
        T &operator*();
        T *operator->();
        reverse_iterator operator++()
        {
            --(this->__arrarptr__);
            return *this;
        }
        reverse_iterator operator++(int)
        {
            reverse_iterator temp(*this);
            ++(*this);
            return temp;
        }
        virtual ~reverse_iterator();
    };
} // namespace iterators

#include "iterator.tpp"

#endif