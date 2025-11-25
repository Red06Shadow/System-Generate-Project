#include <stda/numbers/numbers.hpp>
#include <stda/trails/trails.hpp>
#include <memory>
#include <vector>
#include <map>

#ifndef MODESSTD
#define MODESSTD

/* @Documentacion:
 * Este archivo se encarga de compilar un sistema de nodos para uso multiple, aunque fuera interesante relacionarlo con
 * grafos, aun la idea no esta clara, pero se tiene en cuenta
 */

namespace node
{
    /// @brief id del tipo de nodo especificado, esto permite identificar el nodo a base de un puntero y luego proceder a hacer un cast a este elemento
    enum id : u8
    {
        _S_base,
        _S_point,
        _S_array,
        _S_vector,
        _S_mapped,
        _S_other
    };
    /// @brief La clase padre del resto de nodos para que estos puedan usarse con punteros y se tenga el acceso a los elementos como el id, asi como otros elementos estaticos para el control
    class base
    {
    public:
        /// @brief Id del nodo
        node::id pid;

    protected:
        /// @brief Identificado unico para cada nodo generado dentro de la ejecucion del programa
        size_t __intern__id;
        /// @brief Esta es la seccion de contadores de elementos de los diferentes tipos de nodos
        static size_t countofelements, countofpoints, countofarrays, countofvector, countofmaping, countofother;

    public:
        /// @brief Constructor principal de clase, no tiene uno por defecto para que el programado r que genere un nuevo tipo de nodo no se equivoque a la hora de generar un id distinto
        /// @param __id Id del nodo
        /// @note (!Importante: Use base::countofother y countofother::id::_S_other para nodos personalizados!)
        base(const node::id __id = node::_S_base) : __intern__id(countofelements), pid(__id) { countofelements++; }
        base(const base &other)
        {
            __intern__id = other.__intern__id;
            pid = other.pid;
        }
        base(base &&other)
        {
            __intern__id = other.__intern__id;
            pid = other.pid;
        }
        virtual ~base() = default;
    };
    /// @brief Clase de nodo de tipo final de dato, almacena el dato y no permite insetar un nuevo nodo, puede usr este nodo para generar otros nodos similares si lo desea
    /// @tparam T Tipo de dato que se desea(!Atencion: debe coincidir con el tipo de dato que guarda el arreglo!)
    template <typename T>
    class point : public base
    {
    private:
        /// @brief Variable que almacena el dato insertado en el nodo
        T value;

    public:
        /// @brief Constructor de point base(!Atencion: Note que no hay contructor por defecto ya que eso evita que el programador intente inicualizar el dato con un elemento vacio!)
        /// @param __value
        point(const T &__value);
        point(const point<T> &other);
        point(point<T> &&other);
        point<T> &operator=(const point<T> &other)
        {
            if (this != &other)
            {
                pid = other.pid;
                __intern__id = other.__intern__id;
                std::copy(value, other.value);
            }
            return *this;
        }
        point<T> &operator=(point<T> &&other)
        {
            if (this != &other)
            {
                pid = other.pid;
                __intern__id = other.__intern__id;
                value = std::move(other.value);
            }
            return *this;
        }
        /// @brief Importante operador de comparacion (?>?) para ordenar los nodos, era algo que se tenia en mente para los grafos pero debido a la propia implementacion no se ha podidi realizar
        /// @param lhs Miembro izquierdo de la operacion
        /// @param rhs Miembro derecho de la operacion
        /// @return Devuelve verdadero si se cumple
        friend bool operator>(const point<T> &lhs, const point<T> &rhs) { return lhs.get() > rhs.get(); }
        /// @brief Importante operador de comparacion (?<?) para ordenar los nodos, era algo que se tenia en mente para los grafos pero debido a la propia implementacion no se ha podidi realizar
        /// @param lhs Miembro izquierdo de la operacion
        /// @param rhs Miembro derecho de la operacion
        /// @return Devuelve verdadero si se cumple
        friend bool operator<(const point<T> &lhs, const point<T> &rhs) { return lhs.get() < rhs.get(); }
        /// @brief Importante operador de comparacion (?>=?) para ordenar los nodos, era algo que se tenia en mente para los grafos pero debido a la propia implementacion no se ha podidi realizar
        /// @param lhs Miembro izquierdo de la operacion
        /// @param rhs Miembro derecho de la operacion
        /// @return Devuelve verdadero si se cumple
        friend bool operator>=(const point<T> &lhs, const point<T> &rhs) { return lhs.get() >= rhs.get(); }
        /// @brief Importante operador de comparacion (?<=?) para ordenar los nodos, era algo que se tenia en mente para los grafos pero debido a la propia implementacion no se ha podidi realizar
        /// @param lhs Miembro izquierdo de la operacion
        /// @param rhs Miembro derecho de la operacion
        /// @return Devuelve verdadero si se cumple
        friend bool operator<=(const point<T> &lhs, const point<T> &rhs) { return lhs.get() <= rhs.get(); }
        /// @brief Importante operador de comparacion (?==?) para ordenar los nodos, era algo que se tenia en mente para los grafos pero debido a la propia implementacion no se ha podidi realizar
        /// @param lhs Miembro izquierdo de la operacion
        /// @param rhs Miembro derecho de la operacion
        /// @return Devuelve verdadero si se cumple
        friend bool operator==(const point<T> &lhs, const point<T> &rhs) { return lhs.get() == rhs.get(); }
        /// @brief Importante operador de comparacion (?!=?) para ordenar los nodos, era algo que se tenia en mente para los grafos pero debido a la propia implementacion no se ha podidi realizar
        /// @param lhs Miembro izquierdo de la operacion
        /// @param rhs Miembro derecho de la operacion
        /// @return Devuelve verdadero si se cumple
        friend bool operator!=(const point<T> &lhs, const point<T> &rhs) { return lhs.get() != rhs.get(); }
        /// @brief Obtiene el elemento dentro del objecto
        /// @return Devuelve el elemento(Por supuesto)
        const T &get() const;
        /// @brief Remplaza el elemento dentro por el insertado como parametro de (?__value?)
        /// @param __value
        void set(const T &__value);
        ~point() override;
    };
    /// @brief Clase que genera un array estatico en compilacion que guarda varias direcciones de nodos
    /// @tparam N Numero de elementos de array
    template <size_t N>
    class array : public base
    {
    private:
        /// @brief Locacion de arreglo de elementos
        base *values[N];

    public:
        /// @brief Clase que maneja la iteracion reversa del array
        class reverse
        {
        private:
            base *const *__arrarptr__;

        public:
            reverse(const array &__base) : __arrarptr__(__base.values) {}
            /// @brief Punto de partida de la iteracion reversa del array
            /// @return Devuelve el iterador que apunta al elemento final del array
            iterators::reverse_iterator<base *> begin() const { return iterators::reverse_iterator<base *>(__arrarptr__ + N - 1); }
            /// @brief Punto final de la iteracion reversa del array
            /// @return Devuelve el iterador que apunta al elemento inicial del array
            iterators::reverse_iterator<base *> end() const { return iterators::reverse_iterator<base *>(__arrarptr__ - 1); }
            ~reverse() {}
        };
        /// @brief Punto de partida de la iteracion del array
        /// @return Devuelve el iterador que apunta al elemento inicial del array
        iterators::iterator<base *> begin() const { return iterators::iterator<base *>(values); }
        /// @brief Punto final de la iteracion del array
        /// @return Devuelve el iterador que apunta al elemento final del array
        iterators::iterator<base *> end() const { return iterators::iterator<base *>(values + N); }
        ////////////////////////////////////////////////////////////////////////////////
        /// @brief Punto de partida de la iteracion reversa del array
        /// @return Devuelve el iterador que apunta al elemento final del array
        iterators::reverse_iterator<base *> rbegin() const { return iterators::reverse_iterator<base *>(values + N - 1); }
        /// @brief Punto final de la iteracion reversa del array
        /// @return Devuelve el iterador que apunta al elemento inicial del array
        iterators::reverse_iterator<base *> rend() const { return iterators::reverse_iterator<base *>(values - 1); }
        /// @brief Constructor por defecto de array
        array() : node::base(node::_S_array) { base::countofarrays++; }
        /// @brief Constructor del array en base a un (?std::initializer_list<base*>?)
        /// @param list Lista de elementos a agregar(!Importante: Fallara si ingresas un numero mayor de elemntos!)
        array(const std::initializer_list<base *> &list);
        array(const array<N> &other);
        array(array<N> &&other);
        /// @brief Expresion constante quer devuelve el tamano del arreglo
        /// @return Numero (?size_t?) del tamano del arreglo
        constexpr size_t size() const { return N; }
        /// @brief Operador de acceso inmediato al elemento
        /// @param pos Posicion del elemento dentro del array(!Importante: No esta protejido congtra excepciones por lo que si se accede a un ekemento fuera del rango ocurrira un Segmentation Fault!)
        /// @return Devuelve el puntero al nodo generado
        base *&operator[](size_t pos);
        /// @brief Funcion de acceso al elemento
        /// @param pos Posicion del elemento dentro del array
        /// @return Devuelve el puntero al nodo generado
        const base *at(size_t pos) const;
        /// @brief Funcion de acceso al ultimo elemento
        /// @return Devuelve el puntero al ultimo nodo generado
        const base *back() const { return values[N - 1]; }
        /// @brief Funcion de acceso al primer elemento
        /// @return Devuelve el puntero al primer nodo generado
        const base *top() const { return values[0]; }
        /// @brief Remplaza el elemento de puntero de la pocision especificada por otro
        /// @param element Elemeto a insertar 
        /// @param pos Posicion del elemento
        void replace(base *element, size_t pos);
        /// @brief Elimina un elemento del arreglo volviendo a nullptr el valor de esa pocision
        /// @param pos Posicion del elemento
        void remove(size_t pos);
        array &operator=(const array &other)
        {
            if (this != &other)
            {
                pid = other.pid;
                __intern__id = other.__intern__id;
                std::copy(values, other.values);
            }
            return *this;
        }
        array &operator=(array &&other)
        {
            if (this != &other)
            {
                pid = other.pid;
                __intern__id = other.__intern__id;
                values = std::move(other.values);
            }
            return *this;
        }
        ~array() override;
    };
    /// @brief Clase que almacena un (?std::vector?) de punteros de nodos
    class vector : public base
    {
    private:
        /// @brief Allocator de esos elementos
        std::vector<base *> values;

    public:
        /// @brief Constructor por defecto del vector
        vector() : node::base(node::_S_vector) { base::countofvector++; }
        /// @brief Constructor del array en base a un (?std::initializer_list<base*>?)
        /// @param list Lista de elementos a agregar
        vector(const std::initializer_list<base *> &list);
        vector(const std::vector<base *> &factor);
        vector(const node::vector &other);
        vector(node::vector &&other);
        base *&operator[](size_t pos)
        {
            return values[pos];
        }
        /// @brief Funcion de acceso al elemento
        /// @param pos Posicion del elemento dentro del array
        /// @return Devuelve el puntero al nodo generado
        const base *at(size_t pos) const
        {
            return values.at(pos);
        }
        vector &operator=(const vector &other)
        {
            if (this != &other)
            {
                pid = other.pid;
                __intern__id = other.__intern__id;
                values = other.values;
            }
            return *this;
        }
        vector &operator=(vector &&other)
        {
            if (this != &other)
            {
                pid = other.pid;
                __intern__id = other.__intern__id;
                values = std::move(other.values);
            }
            return *this;
        }
        /// @brief Inserta un elemento en la posicion deseada
        /// @param pos Posicion en donde se deasea insertar(?Atencion: Si la pocision supera el tamano de vector se agregara al final?)
        /// @param value Valor del puntero del nodo
        void insert(size_t pos, base *value);
        /// @brief Inserta un elemento en la posicion deseada
        /// @param pos Iterador del vector
        /// @param value Valor del puntero del nodo
        void insert(const std::vector<base *>::iterator &pos, base *value);
        /// @brief Agrega el elemento al final del arreglo
        /// @param value Valor del puntero del nodo
        void push_back(base *value) { values.push_back(value); }
        /// @brief Elimina el elemento de la ultima posicion
        void pop_back() { values.pop_back(); }
        /// @brief Remplaza el elemento de puntero de la pocision especificada por otro
        /// @param pos Posicion del elemento
        /// @param value Elemeto a insertar 
        void replace(size_t pos, base *value);
        /// @brief Reserva tamano para el vector(!Importante: El tamano debe ser mayor al ya anteriormente reservado(Ver en capacity) si no obtendras error!)
        /// @param size Tamano a reservar
        void reserve(size_t size) { values.reserve(size); }
        /// @brief Capacidad del vector definida
        /// @return Devuelve un (?size_t?) del numero de elemntos del vector reservados
        size_t capacity() { return values.capacity(); }
        /// @brief Limpira el vector completamente, colocando los elementos a nullptr y liberando su memoria
        void clear() { values.clear(); }
        /// @brief Elimina un elemento del arreglo volviendo a nullptr el valor de esa pocision
        /// @param pos Posicion del elemento
        void remove(size_t pos);
        /// @brief Elimina un elemento del arreglo volviendo a nullptr el valor de esa pocision
        /// @param pos Iterador del elemento
        void remove(const std::vector<base *>::iterator &pos);
        /// @brief Obtiene una expresion constante del tamano del arreglo
        /// @return Devuelve un (?size_t?) del numero de elementos tangibles del vector
        const size_t size() const { return values.size(); }
        /// @brief Funcion de acceso al ultimo elemento
        /// @return Devuelve el puntero al ultimo nodo generado
        const base *back() const { return const_cast<const base *>(values[values.size() - 1]); }
        /// @brief Funcion de acceso al inicio elemento
        /// @return Devuelve el puntero al inicio nodo generado
        const base *top() const { return const_cast<const base *>(values[0]); }
        /// @brief Punto de partida de la iteracion del array
        /// @return Devuelve el iterador que apunta al elemento inicial del array
        std::vector<base *>::iterator begin() { return values.begin(); }
        /// @brief Punto de final de la iteracion del array
        /// @return Devuelve el iterador que apunta al elemento final del array
        std::vector<base *>::iterator end() { return values.end(); }
        ~vector() override;
    };
    /// @brief Clase que guarda los elemntos de nodos en base a una clave(?std::map?)
    /// @tparam _Key Tipo de dato que se convertira en la clave
    template <typename _Key>
    class mapped : public base
    {
    private:
        /// @brief Mapa que guarda los elementos
        std::map<_Key, base *> values;

    public:
        /// @brief Consttuctor por defecto
        mapped() : node::base(node::_S_mapped) { base::countofmaping++; }
        /// @brief Constructor del array en base a un (?std::std::initializer_list<std::pair<_Key, base *>>?)
        /// @param list Lista de elementos a agregar
        mapped(const std::initializer_list<std::pair<_Key, base *>> &list);
        mapped(const std::map<_Key, base *> &factor);
        mapped(const node::mapped<_Key> &other);
        mapped(node::mapped<_Key> &&other);
        /// @brief Inserta a partir de una clave no repetida el elemento que se desea
        /// @param key Clave de almacenamiento del elemento
        /// @param value Valor a guardar
        void insert(_Key key, base *value) { values.insert(key, value); }
        /// @brief Elimina el objecto del mapa
        /// @param key Clave del elemento
        void remove(_Key key) { values.erase(key); }
        /// @brief Limpira el vector completamente, colocando los elementos a nullptr y liberando su memoria
        void clear() { values.clear(); }
        /// @brief Obtiene una expresion constante del tamano del arreglo
        /// @return Devuelve un (?size_t?) del numero de elementos tangibles del vector
        const size_t size() const { return values.size(); }
        /// @brief Operador de acceso directo al elemento
        /// @param pos Clave de acceso
        /// @return Devuelve el puntero al nodo generado
        base *&operator[](const _Key &pos)
        {
            return values[pos];
        }
        /// @brief Funcion de acceso al elemento
        /// @param pos Clave de acceso
        /// @return Devuelve el puntero al nodo generado
        const base *at(const _Key &pos) const
        {
            return values.at(pos);
        }
        mapped &operator=(const mapped &other)
        {
            if (this != &other)
            {
                pid = other.pid;
                __intern__id = other.__intern__id;
                values = other.values;
            }
            return *this;
        }
        mapped &operator=(mapped &&other)
        {
            if (this != &other)
            {
                pid = other.pid;
                __intern__id = other.__intern__id;
                values = std::move(other.values);
            }
            return *this;
        }
        ~mapped() override;
    };
} // namespace node
#include "nodes.tpp"

#endif