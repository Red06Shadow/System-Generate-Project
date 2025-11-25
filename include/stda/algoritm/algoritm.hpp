#include <stda/numbers/numbers.hpp>
#include <vector>

#ifndef STDX_ALGORITM
#define STDX_ALGORITM

/* @Documentacion:
 * Este archivo se crea con el objectivo de reunir un conjunto de algoritmos 
 * disenados para cumplir con necesidades variadas del programador.
*/

namespace algoritm
{
    /// @brief Permite ver un arreglo de una dimension del tipo T insertado por el programador
    /// @tparam T Tipo de dato que se desea(!Atencion: debe coincidir con el tipo de dato que guarda el arreglo!)
    /// @param array Arreglo que se desea visualizar
    /// @param size Tamano que posee este(!Atencion: El tamano no puede ser mayor que el del arreglo original)
    template <typename T>
    void view(const T array[], size_t size);
    /// @brief Permite ver el trais<T> deseado
    /// @tparam T Tipo de dato que se desea(!Atencion: debe coincidir con el tipo de dato que guarda el arreglo!) 
    /// @param array Referencia al elemento de tipo trails<T> que se desea visualizar
    template <typename T>
    void view(const trails<T>& array);
    /// @brief Copia un arreglo de un tipo determinado por T a otro arreglo del mismo tipo
    /// @tparam T Tipo de dato que se desea(!Atencion: debe coincidir con el tipo de dato que guarda el arreglo!)
    /// @param _destine_ Arreglo de destino donde se copiara el el arreglo _sources
    /// @param _sources Arreglo que se copiara al arreglo _destine_
    /// @param _sdestine_ Tamano que posee el arreglo _sdestine_(!Atencion: El tamano no puede ser mayor que el del arreglo original)
    /// @param _ssources Tamano que posee el arreglo _ssources(!Atencion: El tamano no puede ser mayor que el del arreglo original)
    template <typename T>
    inline void copy(T _destine_[], const T _sources[], size_t _sdestine_, size_t _ssources);
    /// @brief Copia un vector de un tipo determinado por T a otro vector del mismo tipo
    /// @tparam T Tipo de dato que se desea(!Atencion: debe coincidir con el tipo de dato que guarda el arreglo!)
    /// @param _destine_ Vector de destino de la copia
    /// @param _sources Vector de entrada para la copia
    template <typename T>
    inline void copy(std::vector<T> &_destine_, const std::vector<T> &_sources);
    /// @brief Obitiene el numero en base al bit siguiente del mas signiicativo de un numero determinado
    /// @param n El numero de referencia para determinar
    /// @return Devuelve el valor del numero en base al bit sigiente mas significativo
    inline size_t bitforaround(size_t n);
    /// @brief Copia a un vectr un arreglo del mismo tipo de dato
    /// @tparam T Tipo de dato que se desea(!Atencion: debe coincidir con el tipo de dato que guarda el arreglo!)
    /// @param _destine_ Vector de destino de la copia
    /// @param _sources Arreglo de entrada para la copia
    /// @param _ssources Tamano que posee el arreglo _ssources(!Atencion: El tamano no puede ser mayor que el del arreglo original)
    template <typename T>
    inline void copy(std::vector<T> &_destine_, const T _sources[], size_t _ssources);
    /// @brief Obtiene el numero de elementos de un arreglo determinado
    /// @tparam U Tipo de dato que se desea(!Atencion: debe coincidir con el tipo de dato que guarda el arreglo!)
    /// @param _sources Arreglo de entrada
    /// @return Devuelve el numero de elementos
    template <typename U>
    size_t size(const U _sources[]);
    /// @brief Algoritmo de QickShort de un pivote para arreglos
    /// @tparam Q Tipo de dato que se desea(!Atencion: debe coincidir con el tipo de dato que guarda el arreglo!)
    /// @param array Arreglo a ordenar
    /// @param size Tamano que posee el arreglo _ssources(!Atencion: El tamano no puede ser mayor que el del arreglo original)
    template <typename Q>
    void qickshort(Q array[], size_t size);
    /// @brief Algoritmo de QickShort de dos pivotes para arreglos(?Aclaracion: Se dice que es mejor para arreglos de gran tamanos?)
    /// @tparam Q Tipo de dato que se desea(!Atencion: debe coincidir con el tipo de dato que guarda el arreglo!)
    /// @param array Arreglo a ordenar
    /// @param size Tamano que posee el arreglo _ssources(!Atencion: El tamano no puede ser mayor que el del arreglo original) 
    template <typename Q>
    void qickshort2(Q array[], size_t size);
    /// @brief BAlgoritmo de Busqueda binaria para arreglos
    /// @tparam Q Tipo de dato que se desea(!Atencion: debe coincidir con el tipo de dato que guarda el arreglo!)
    /// @param array Arreglo ordenado 
    /// @param element Elemento que se desea encontrar dentro del arreglo
    /// @param size Tamano que posee el arreglo _ssources(!Atencion: El tamano no puede ser mayor que el del arreglo original)
    /// @return Devuelve la pocision del elemento en todo caso de no encontrarlo devuelve size_t(-1)
    template <typename Q>
    size_t binarysearch(Q array[], Q element, size_t size);
}

#include "algoritm.tpp"

#endif