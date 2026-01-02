#include <stda/sstrings/converter.hpp>
#include <exception>
#include <string>
#include <cstring>

#ifndef EXCEPTIONSME
#define EXCEPTIONSME

/* @Documentacion:
 * Este archivo contiene el manejo de excepciones para namespace systems
 * facilita y ahorra tiempo a la hora de generarlas y aunque aun no este completa
 * tambien puede recibir excepciones fuera de las ya predefinidas
 */

/// @brief Nombres de espacios de variables
namespace systems
{
    /// @brief Clase que maneja las expeciones systems
    class exception : public std::exception
    {
    public:
        enum class error : unsigned int
        {
            __none,
            __iofaul,
            __notfolderdestine,
            __notgetfilesize,
            __notfileupdater,
            __invalidopmovecopy,
            __notexistingfolder,
            __other,
        };

    private:
#define __SIZE__ 6
        static char const *const errors[__SIZE__];
        error __error__;
    protected:
        char* __other__;

    public:
        /// @brief Constructor por defecto
        exception() noexcept : __error__(error::__none), __other__(nullptr) {}
        /// @brief Constructor que usa el id de error
        /// @param __message Identificador de tipo (?systems::exception::error?)
        explicit exception(const error __message) : __error__(__message), __other__(nullptr) {}
        /// @brief Constructor que usa el id de error y un mensaje extra definido por el programador
        /// @param __message Identificador de tipo (?systems::exception::error?)
        /// @param other_message Mensaje adicional que se desea enviar
        explicit exception(const error __message, const char* other_message) : __error__(__message), __other__(const_cast<char*>(other_message)) {}
        /// @brief Constructor que usa un mensaje puro para aletras indefinidas
        /// @param __message Mensaje que se desea enviar de tipo (?const char*?)
        explicit exception(const char* __message) : __error__(error::__other), __other__(const_cast<char*>(__message)) {}
        /// @brief Constructor que usa un mensaje puro para aletras indefinidas
        /// @param __message Mensaje que se desea enviar de tipo (?std::string*?)
        explicit exception(const std::string __message) : __error__(error::__other) {
            __other__ = new char[__message.size() + 1];
            __other__[__message.size()] = 0;
            std::strcpy(__other__, __message.c_str());
        }
        /// @brief Constructor que usa un mensaje puro para aletras indefinidas
        /// @param __message Mensaje que se desea enviar de tipo (?std::wstring*?)
        explicit exception(const std::wstring __message) : __error__(error::__other) {
            __other__ = new char[__message.size() + 1];
            __other__[__message.size()] = 0;
            char* str = stringconverter::convert_utf8_to_ascii(__message.c_str());
            std::strcpy(__other__, str);
            delete[](str);
        }
        exception &operator=(exception const &_Other) noexcept
        {
            if (this == &_Other)
            {
                return *this;
            }
            this->__error__ = _Other.__error__;
            return *this;
        }
        /// @brief Obtiene el mensaje en formato (?const char*?)
        /// @return Devuelve el mensaje
        const char *what() const noexcept override;
        virtual ~exception() noexcept {}
        /// @brief Obtiene el codigo de error en caso de tenerlo
        /// @return Devuelve un valor de tipo (?systems::exception::error?)
        error get_code() const { return __error__; }
    };
}
#endif