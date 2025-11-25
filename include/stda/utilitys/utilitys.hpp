#include <typeinfo>

#ifndef STDXUTILITYS
#define STDXUTILITYS

/* @Documentacion:
 * Este archivo contiene duferentes clases utiles para el desarrollo de programas
 */


/// @brief Espacio de nombre para las utilidades
namespace utilitys
{
    /// @brief Guarda un par de elementos de tipo A y B
    /// @tparam A Tipo de dato que desee guardar
    /// @tparam B Tipo de dato que desee guardar
    template <typename A, typename B>
    class pair
    {
    public:
        /// @brief Primer elemento, contenedor de A
        A firts;
        /// @brief Segundo elemento, contenedor de B
        B second;
        /// @brief Constructor por defecto
        pair() : firts(), second() {}
        /// @brief Constructor que recibe los dos valores de entrada
        /// @tparam A1 Tipo de dato que desee guardar(!Atencion: Debe coincidir con el tipo que desea guardar!)
        /// @tparam B1 Tipo de dato que desee guardar(!Atencion: Debe coincidir con el tipo que desea guardar!)
        /// @param __firts Primer elemento, contenedor de A
        /// @param __second Segundo elemento, contenedor de B
        template <typename A1, typename B1>
        pair(A1 __firts, B1 __second) : firts(__firts), second(__second) {}
        pair(const pair &other) : firts(other.firts), second(other.second) {}
        pair(pair &&other) noexcept : firts(std::move(other.firts)), second(std::move(other.second)) {}
        pair &operator=(const pair &other)
        {
            if (this != &other)
            {
                this->firts = other.firts;
                this->second = other.second;
            }
            return *this;
        }
        pair &operator=(pair &&other)
        {
            if (this != &other)
            {
                this->firts = std::move(other.firts);
                this->second = std::move(other.second);
            }
            return *this;
        }
        /// @brief Intercambia las instancias entre si
        /// @param objectivo1 instansia numero 1
        /// @param objectivo2 instansia numero 2
        void swap(pair<A, B> &objectivo1, pair<A, B> &objectivo2)
        {
            std::swap(objectivo1.firts, objectivo2.firts);
            std::swap(objectivo1.second, objectivo2.second);
        }
        /// @brief Obtiene el std::string del tipo de dato
        /// @return Devuelve el tipo de dato que almacena en el primer elemento
        std::string type1()
        {
            return typeid(firts).name();
        }
        /// @brief Obtiene el std::string del tipo de dato
        /// @return Devuelve el tipo de dato que almacena en el segundo elemento
        std::string type2()
        {
            return typeid(second).name();
        }
    };
    /// @brief Guarda un par de elementos de tipo A, B y C
    /// @tparam A Tipo de dato que desee guardar
    /// @tparam B Tipo de dato que desee guardar
    /// @tparam C Tipo de dato que desee guardar
    template <typename A, typename B, typename C>
    class trio
    {
    public:
        /// @brief Primer elemento, contenedor de A
        A firts;
        /// @brief Segundo elemento, contenedor de B
        B second;
        /// @brief Tercer elemento, contenedor de C
        C third;
        /// @brief Constructor por defecto
        trio() : firts(), second(), third() {}
        /// @brief Constructor que recibe los dos valores de entrada
        /// @tparam A1 Tipo de dato que desee guardar(!Atencion: Debe coincidir con el tipo que desea guardar!)
        /// @tparam B1 Tipo de dato que desee guardar(!Atencion: Debe coincidir con el tipo que desea guardar!)
        /// @tparam C1 Tipo de dato que desee guardar(!Atencion: Debe coincidir con el tipo que desea guardar!)
        /// @param __firts Primer elemento, contenedor de A
        /// @param __second Segundo elemento, contenedor de B
        /// @param __third Tercer elemento, contenedor de C
        template <typename A1, typename B1, typename C1>
        trio(A1 __firts, B1 __second, C1 __third) : firts(__firts), second(__second), third(__third) {}
        trio(const trio &other) : firts(other.firts), second(other.second), third(other.third) {}
        trio(trio &&other) noexcept : firts(std::move(other.firts)), second(std::move(other.second)), third(std::move(other.third)) {}
        trio &operator=(const trio &other)
        {
            if (this != &other)
            {
                this->firts = other.firts;
                this->second = other.second;
                this->third = other.third;
            }
            return *this;
        }
        trio &operator=(trio &&other)
        {
            if (this != &other)
            {
                this->firts = std::move(other.firts);
                this->second = std::move(other.second);
                this->third = std::move(other.third);
            }
            return *this;
        }
        /// @brief Intercambia las instancias entre si
        /// @param objectivo1 instansia numero 1
        /// @param objectivo2 instansia numero 2
        void swap(trio<A, B, C> &objectivo1, trio<A, B, C> &objectivo2)
        {
            std::swap(objectivo1.firts, objectivo2.firts);
            std::swap(objectivo1.second, objectivo2.second);
            std::swap(objectivo1.third, objectivo2.third);
        }
        /// @brief Obtiene el std::string del tipo de dato
        /// @return Devuelve el tipo de dato que almacena en el primer elemento
        std::string type1()
        {
            return typeid(firts).name();
        }
        /// @brief Obtiene el std::string del tipo de dato
        /// @return Devuelve el tipo de dato que almacena en el segundo elemento
        std::string type2()
        {
            return typeid(second).name();
        }
        /// @brief Obtiene el std::string del tipo de dato
        /// @return Devuelve el tipo de dato que almacena en el tercer elemento
        std::string type3()
        {
            return typeid(third).name();
        }
    };
    /// @brief Guarda un par de elementos de tipo A, B, C y D
    /// @tparam A Tipo de dato que desee guardar
    /// @tparam B Tipo de dato que desee guardar
    /// @tparam C Tipo de dato que desee guardar
    /// @tparam D Tipo de dato que desee guardar
    template <typename A, typename B, typename C, typename D>
    class quartet
    {
    public:
        /// @brief Primer elemento, contenedor de A
        A firts;
        /// @brief Segundo elemento, contenedor de B
        B second;
        /// @brief Tercer elemento, contenedor de C
        C third;
        /// @brief Cuarto elemento, contenedor de D
        D fourth;
        /// @brief Constructor por defecto
        quartet() : firts(), second(), third(), fourth() {}
        /// @brief Constructor que recibe los dos valores de entrada
        /// @tparam A1 Tipo de dato que desee guardar(!Atencion: Debe coincidir con el tipo que desea guardar!)
        /// @tparam B1 Tipo de dato que desee guardar(!Atencion: Debe coincidir con el tipo que desea guardar!)
        /// @tparam C1 Tipo de dato que desee guardar(!Atencion: Debe coincidir con el tipo que desea guardar!)
        /// @tparam D1 Tipo de dato que desee guardar(!Atencion: Debe coincidir con el tipo que desea guardar!)
        /// @param __firts Primer elemento, contenedor de A
        /// @param __second Segundo elemento, contenedor de B
        /// @param __third Tercer elemento, contenedor de C
        /// @param __fourth Cuarto elemento, contenedor de D
        template <typename A1, typename B1, typename C1, typename D1>
        quartet(A1 __firts, B1 __second, C1 __third, D1 __fourth) : firts(__firts), second(__second), third(__third), fourth(__fourth) {}
        quartet(const quartet &other) : firts(other.firts), second(other.second), third(other.third), fourth(other.fourth) {}
        quartet(quartet &&other) noexcept : firts(std::move(other.firts)), second(std::move(other.second)), third(std::move(other.third)), fourth(std::move(other.fourth)) {}
        quartet &operator=(const quartet &other)
        {
            if (this != &other)
            {
                this->firts = other.firts;
                this->second = other.second;
                this->third = other.third;
                this->fourth = other.fourth;
            }
            return *this;
        }
        quartet &operator=(quartet &&other)
        {
            if (this != &other)
            {
                this->firts = std::move(other.firts);
                this->second = std::move(other.second);
                this->third = std::move(other.third);
                this->fourth = std::move(other.fourth);
            }
            return *this;
        }
        /// @brief Intercambia las instancias entre si
        /// @param objectivo1 instansia numero 1
        /// @param objectivo2 instansia numero 2
        void swap(quartet<A, B, C, D> &objectivo1, quartet<A, B, C, D> &objectivo2)
        {
            std::swap(objectivo1.firts, objectivo2.firts);
            std::swap(objectivo1.second, objectivo2.second);
            std::swap(objectivo1.third, objectivo2.third);
            std::swap(objectivo1.fourth, objectivo2.fourth);
        }
        /// @brief Obtiene el std::string del tipo de dato
        /// @return Devuelve el tipo de dato que almacena en el primer elemento
        std::string type1()
        {
            return typeid(firts).name();
        }
        /// @brief Obtiene el std::string del tipo de dato
        /// @return Devuelve el tipo de dato que almacena en el segundo elemento
        std::string type2()
        {
            return typeid(second).name();
        }
        /// @brief Obtiene el std::string del tipo de dato
        /// @return Devuelve el tipo de dato que almacena en el tercer elemento
        std::string type3()
        {
            return typeid(third).name();
        }
        /// @brief Obtiene el std::string del tipo de dato
        /// @return Devuelve el tipo de dato que almacena en el cuarto elemento
        std::string type4()
        {
            return typeid(fourth).name();
        }
    };
    /// @brief Clase que almacena una tupla de datos de varios tipos definidos por el usuario
    /// @tparam ...Types 
    template <typename... Types>
    class tuple;
    /// @brief Tupla definida para cuando sea de un numero vacio de elementos
    template <>
    class tuple<>
    {
    public:
        static constexpr unsigned long long size = 0;
    };
    /// @brief Clase tupla completa para el manejo del tipo actual y del resto de elementos definidos en la plantlla
    /// @tparam T Tipo de dato actual de la template...
    /// @tparam ...Rest Resto de elementos del template
    template <typename T, typename... Rest>
    class tuple<T, Rest...>
    {
    private:
        T value;
        tuple<Rest...> rest;

    public:
        /// @brief Constrcutor que inicializa todos los elementos
        /// @param first Primer elemento de la lista
        /// @param ...others Rresto de elemntos
        tuple(const T &first, const Rest &...others) : value(first), rest(others...) {}
        /// @brief Obtienes a parir de la pocision de dicho tipo de dato el valor almacenado en esa variable
        /// @tparam N Id del tipo
        /// @return Devuelve el valor en ese tipo de dato
        template <size_t N>
        auto &get()
        {
            if constexpr (N == 0)
                return value;
            else
                return rest.template get<N - 1>();
        }
        /// @brief Expresion constante que maneja el numero de elementos dentro de (?tuple?)
        static constexpr size_t size = 1 + sizeof...(Rest);
        /// @brief Funcion que, siempre que el tipo sea imprimible, muestra en la terminal todos los elementos dentro de la tupla
        void print() const
        {
            std::cout << value;
            if constexpr (sizeof...(Rest) > 0)
            {
                std::cout << "|";
                rest.print();
            }
        }
    };
} // namespace utilitys

#endif