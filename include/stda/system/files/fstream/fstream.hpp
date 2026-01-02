#include <stda/system/files/url/url.hpp>
#include <stda/sstrings/stringbuffer.hpp>
#include <stda/numbers/numbers.hpp>
#include <stdio.h>
#include <stdlib.h>

#ifndef FSTREAM
#define FSTREAM

/* @Documentacion:
 * Este archivo contiene el manejo de archivos a partir de valores de entrada y salida
 * aunque estas funcionalidades existen en el standart de c++ prefiero usar esas ya que puedo modificarlas en caso de que fallen
 * o mejorarlas de ser necesario y ademas para mi es mas comodo :)
 */
namespace systems
{
    namespace ios
    {
        /// @brief Indicativo entero que permite identificar mas rapido el formato de archivo
        enum base
        {
            in = 0b00001,
            out = 0b00010,
            app = 0b00100,
            bin = 0b01000,
            trunc = 0b10000
        };

        _GLIBCXX_NODISCARD _GLIBCXX_CONSTEXPR inline base
        operator&(base __a, base __b) _GLIBCXX_NOTHROW
        {
            return base(static_cast<u8>(__a) & static_cast<u8>(__b));
        }

        _GLIBCXX_NODISCARD _GLIBCXX_CONSTEXPR inline base
        operator|(base __a, base __b) _GLIBCXX_NOTHROW
        {
            return base(static_cast<u8>(__a) | static_cast<u8>(__b));
        }

        _GLIBCXX_NODISCARD _GLIBCXX_CONSTEXPR inline base
        operator^(base __a, base __b) _GLIBCXX_NOTHROW
        {
            return base(static_cast<u8>(__a) ^ static_cast<u8>(__b));
        }

        _GLIBCXX_NODISCARD _GLIBCXX_CONSTEXPR inline base
        operator~(base __a) _GLIBCXX_NOTHROW
        {
            return base(~static_cast<u8>(__a));
        }

        _GLIBCXX14_CONSTEXPR
        inline const base &
        operator|=(base &__a, base __b) _GLIBCXX_NOTHROW
        {
            return __a = __a | __b;
        }

        _GLIBCXX14_CONSTEXPR
        inline const base &
        operator&=(base &__a, base __b) _GLIBCXX_NOTHROW
        {
            return __a = __a & __b;
        }

        _GLIBCXX14_CONSTEXPR
        inline const base &
        operator^=(base &__a, base __b) _GLIBCXX_NOTHROW
        {
            return __a = __a ^ __b;
        }

        _GLIBCXX_NODISCARD _GLIBCXX_CONSTEXPR inline u8
        operator-(base __a, u8 __b) _GLIBCXX_NOTHROW
        {
            return static_cast<u8>(__a) - __b;
        }

        _GLIBCXX_NODISCARD _GLIBCXX_CONSTEXPR inline u8
        operator+(base __a, u8 __b) _GLIBCXX_NOTHROW
        {
            return static_cast<u8>(__a) + __b;
        }

        _GLIBCXX_NODISCARD _GLIBCXX_CONSTEXPR inline base
        operator-(base __a, base __b) _GLIBCXX_NOTHROW
        {
            return base(static_cast<u8>(__a) - static_cast<u8>(__b));
        }

        _GLIBCXX_NODISCARD _GLIBCXX_CONSTEXPR inline base
        operator+(base __a, base __b) _GLIBCXX_NOTHROW
        {
            return base(static_cast<u8>(__a) + static_cast<u8>(__b));
        }
        /// @brief Fstream idica las funciones basicas
        class fstream
        {
        public:
            static const u8 mode(ios::base __base);
            ////////////////////////////////////////////////////////////////////////////////
            fstream() = default;
            fstream(const __caracter *__path, ios::base __mode);
            fstream(const fstream &other);
            fstream(fstream &&other);
            fstream &operator=(const fstream &other);
            fstream &operator=(fstream &&other);
            ////////////////////////////////////////////////////////////////////////////////
            /// @brief Coloca el puntero del archivo en la pocision especificada
            /// @param position Posicion a partir de cero a la que usted desea que el puntero apunte
            /// @param actual Indica si se usara la pocision actual o el principio para la pocision
            void setpos(size_t position, bool actual);
            /// @brief Guarda en una variable especial un puntero del archivo
            /// @param position Posicion a partir de cero a la que usted desea que el puntero apunte
            /// @param actual Indica si se usara la pocision actual o el principio para la pocision
            void setposaux(size_t position, bool actual);
            ////////////////////////////////////////////////////////////////////////////////
            /// @brief Coloca el puntero del archivo en la pocision especificada
            /// @param position Posicion a partir de cero a la que usted desea que el puntero apunte
            /// @param size Tamano del dato a insertar(utial para estructura)
            /// @param actual Indica si se usara la pocision actual o el principio para la pocision
            void setpos(size_t position, size_t size, bool actual);
            /// @brief Guarda en una variable especial un puntero del archivo
            /// @param position Posicion a partir de cero a la que usted desea que el puntero apunte
            /// @param size Tamano del dato a insertar(utial para estructura)
            /// @param actual Indica si se usara la pocision actual o el principio para la pocision
            void setposaux(size_t position, size_t size, bool actual);
            ////////////////////////////////////////////////////////////////////////////////
            /// @brief Obtiene la pocision del archivo
            size_t getpos();
            /// @brief Obtiene la real pocision del archivo(No usar en setpos)
            size_t getposreal();
            /// @brief Obtiene la pocision base del archivo
            size_t getposbe();
            /// @brief Obtiene la pocision auxialiar del fstream
            size_t getposaux();
            ////////////////////////////////////////////////////////////////////////////////
            void changemode(ios::base __mode);
            ////////////////////////////////////////////////////////////////////////////////
            /// @brief Inserta el caracter de fin de cadenas de texto
            /// @param _c caracter entero puede ser wchar_t o char
            void setendchar(int _c);
            /// @brief Obtienes el caracter que esta siendo usando para el final de las cadenas
            int getendchar();
            ////////////////////////////////////////////////////////////////////////////////
            /// @brief Comprueba si el archivo esta abierto
            bool isopen();
            /// @brief Comprueba si el puntero esta en el final del archivo
            bool iseof();
            /// @brief Coloca el puntero al inicio del archivo
            void setstartp();
            /// @brief Coloca el puntero al final del archivo
            void setendp();
            /// @brief Vacia el buffer del archivo ppor completo
            void fsflush();
            /// @brief Elimina todos los indicadores de error del archivo
            void clearerror();
            /// @brief Obtiene si el archivo es binario
            bool isBinary();
            ////////////////////////////////////////////////////////////////////////////////
            /// @brief Crea una instancia de fstream sin llamar al constructor
            /// @param __path Path del archivo
            /// @param __mode Modo en el que se abrira el archivo
            static fstream open(const __caracter *__path, ios::base __mode);
            /// @brief A partir de una instancia cerrada por close reabre el archivo con el path definido
            /// @param __path Path del archivo
            /// @param __mode Modo en el que se abrira el archivo
            /// @param __fstream__ Fstream a reabrir
            /// @note Si el archivo aun est abierto lanzara un error
            static void reopen(const __caracter *__path, ios::base __mode, fstream &__fstream__);
            /// @brief Cierra el archivo pero sin eliminar la instancia definida
            static void close(fstream &__fstream__);
            ////////////////////////////////////////////////////////////////////////////////
            ~fstream();
            ////////////////////////////////////////////////////////////////////////////////
            friend class iofstream;

        protected:
            FILE *__fptr__ = nullptr;
            bool __binary__ = false;
            size_t __position_before__ = 0;
            size_t __position_aux__ = 0;
            __caracter __endstr__ = '\n';
            ////////////////////////////////////////////////////////////////////////////////
        private:
            static void copy(fstream *ptrfstream, fstream &reffstream);
            static const char *const __mode__[12];
        };

        ///@brief Clase que maneja la lectura de elementos del archivo destinado
        class ifstream : public fstream
        {
        public:
            ///@brief Constructor por defecto
            ifstream() : fstream() {}
            ///@brief Constructor con direccion path del archivo con tipo Url
            ///@param url path del archivo a iniciar flujo
            ifstream(const Url &url);
            ///@brief Constructor con direccion path del archivo con tipo Url, y si se abrira en binario
            ///@param url path del archivo a iniciar flujo
            ///@param binary indica si el archivo a abrir sera en formato binario
            ifstream(const Url &url, bool binary);
            /// @brief Lee todos los caracetres de formato ASCII del archivo y los almacena en str
            /// @param str cadena de caracteres para str(?std::string&?)
            /// @param sources punto de donde se empieca a leer
            /// @param end punto donde se detiene la lectura, por defecto -1 para leer archivo completo
            void read(std::string &str, size_t sources = 0, size_t end = -1ULL);
            /// @brief Lee todos los caracetres de formato UTF-8 del archivo y los almacena en str
            /// @param str cadena de caracteres para str(?std::wstring&?)
            /// @param sources punto de donde se empieca a leer
            /// @param end punto donde se detiene la lectura, por defecto -1 para leer archivo completo
            void read(std::wstring &str, size_t sources = 0, size_t end = -1ULL);
            /// @brief Lee todos los caracetres de formato ASCII del archivo y los almacena en str hasta el caracter especificado
            /// @param str cadena de caracteres para str(?std::string&?)
            /// @param caracter_end caracter de tipo(?char?) que determina hasta donde se leera
            void read(std::string& str, char caracter_end);
             /// @brief Lee todos los caracetres de formato UTF-8 del archivo y los almacena en str hasta el caracter especificado
            /// @param str cadena de caracteres para str(?std::string&?)
            /// @param caracter_end caracter de tipo(?wchar_t?) que determina hasta donde se leera
            void read(std::string &str, wchar_t caracter_end);
            /// @brief Obtienes un valor de un tipo determinado por (?data?) siempre y cuando tenga un operador de lectura para ese tipo
            /// @tparam data Tipo de dato a leer en el archivo
            /// @return Devuelve el valor del dato leido
            template <typename data>
            data get()
            {
                data __data;
                *this >> __data;
                return __data;
            }
            ////////////////////////////////////////////////////////////////////
            friend ifstream &operator>>(ifstream &is, char *&__str);
            friend ifstream &operator>>(ifstream &is, std::string &__str);
            friend ifstream &operator>>(ifstream &is, std::wstring &__str);
            friend ifstream &operator>>(ifstream &is, stringbuffer &__str);
            friend ifstream &operator>>(ifstream &is, wstringbuffer &__str);
            friend ifstream &operator>>(ifstream &is, int &__n);
            friend ifstream &operator>>(ifstream &is, unsigned int &__n);
            friend ifstream &operator>>(ifstream &is, char &__n);
            friend ifstream &operator>>(ifstream &is, wchar_t &__n);
            friend ifstream &operator>>(ifstream &is, unsigned char &__n);
            friend ifstream &operator>>(ifstream &is, long &__n);
            friend ifstream &operator>>(ifstream &is, unsigned long &__n);
            friend ifstream &operator>>(ifstream &is, long long &__n);
            friend ifstream &operator>>(ifstream &is, unsigned long long &__n);
            friend ifstream &operator>>(ifstream &is, float &__n);
            friend ifstream &operator>>(ifstream &is, double &__n);
            friend std::ostream &operator<<(std::ostream &out, ifstream &is);
            ////////////////////////////////////////////////////////////////////
            friend class iofstream;
        };
        ///@brief Clase que maneja la escritura de elementos del archivo destinado
        class ofstream : public fstream
        {
        public:
            ///@brief Constructor por defecto
            ofstream() : fstream() {}
            ///@brief Constructor con direccion path del archivo con tipo Url
            ///@param url path del archivo a iniciar flujo
            ofstream(const Url &url);
            ///@brief Constructor con direccion path del archivo con tipo Url, y modo de apertura
            ///@param url path del archivo a iniciar flujo
            ///@param binary indica si el archivo a abrir sera en formato binario
            ofstream(const Url &url, bool binary);
            /// @brief Constructor con direccion path del archivo con tipo Url, y modo de apertura
            /// @param url path del archivo a iniciar flujo
            /// @param __mode indica el modo de operacion al abir el archivo(Solo se admitiran modos de lectura)
            ofstream(const Url &url, ios::base __mode);
            /// @brief Escribe todo lo que este dentro de la cadena str en un apocision determinada por sources
            /// @param str Cadena de caracteres de escritura(?std::string&?)
            /// @param strstart Pocision de donde se quiere leer la cadena
            /// @param strend Pocision de donde termina la lectura
            /// @param sources Posicion en el archivo de donde se empieza a escribir
            void write(const std::string &str, size_t strstart = 0, size_t strend = -1ULL, size_t sources = 0);
            /// @brief Escribe todo lo que este dentro de la cadena str en un apocision determinada por sources
            /// @param str Cadena de caracteres de escritura(?std::wstring&?)
            /// @param strstart Pocision de donde se quiere leer la cadena
            /// @param strend Pocision de donde termina la lectura
            /// @param sources Posicion en el archivo de donde se empieza a escribir
            void write(const std::wstring &str, size_t strstart = 0, size_t strend = -1ULL, size_t sources = 0);
            /// @brief Envia un valor de un tipo determinado por (?data?) siempre y cuando tenga un operador de escritura para ese tipo
            /// @tparam data Tipo de dato a leer en el archivo
            /// @param __data Valor a enviar al fichero
            template <typename data>
            void get(const data& __data)
            {
                *this << __data;
            }
            ////////////////////////////////////////////////////////////////////
            friend ofstream &operator<<(ofstream &os, const char *__str);
            friend ofstream &operator<<(ofstream &os, const std::string __str);
            friend ofstream &operator<<(ofstream &os, const std::wstring __str);
            friend ofstream &operator<<(ofstream &os, const stringbuffer &__str);
            friend ofstream &operator<<(ofstream &os, const wstringbuffer &__str);
            friend ofstream &operator<<(ofstream &os, const int __n);
            friend ofstream &operator<<(ofstream &os, const unsigned int __n);
            friend ofstream &operator<<(ofstream &os, const char __n);
            friend ofstream &operator<<(ofstream &os, const unsigned char __n);
            friend ofstream &operator<<(ofstream &os, const wchar_t __n);
            friend ofstream &operator<<(ofstream &os, const long __n);
            friend ofstream &operator<<(ofstream &os, const unsigned long __n);
            friend ofstream &operator<<(ofstream &os, const long long __n);
            friend ofstream &operator<<(ofstream &os, const unsigned long long __n);
            friend ofstream &operator<<(ofstream &os, const float __n);
            friend ofstream &operator<<(ofstream &os, const double __n);
            friend ofstream &operator<<(ofstream &out, ifstream &is);
            friend std::istream &operator>>(std::istream &in, ofstream &out);
            ////////////////////////////////////////////////////////////////////
            friend class iofstream;
        };
        ///@brief maneja el flujo entrada/salida de el fichero seleccionado
        class iofstream
        {
        private:
            bool __syncroned_input_output_system__;
            fstream *__syncroned__file__input__output__;
            ofstream *__output__;
            ifstream *__input__;

        public:
            //////////////////////////////////////////////////////
            ///@brief Constructor por defecto de iofstream
            iofstream() = default;
            ///@brief Constructor con direccion path del archivo con tipo Url
            ///@param url path del archivo a iniciar flujo
            iofstream(const Url &url);
            ///@brief Constructor con direccion path del archivo con tipo Url, y modo de apertura
            ///@param url path del archivo a iniciar flujo
            ///@param binary indica si el archivo a abrir sera en formato binario
            ///@param syncroned_input_output_system indica si se activara la sinconizacion de entrada y salida
            iofstream(const Url &url, bool binary, bool syncroned_input_output_system);
            iofstream(const iofstream &other);
            iofstream(iofstream &&other);
            iofstream &operator=(const iofstream &other)
            {
                if (this != &other)
                {
                    if (__input__ != nullptr)
                        delete __input__;
                    if (__output__ != nullptr)
                        delete __output__;
                    if (__syncroned__file__input__output__ != nullptr)
                        delete __syncroned__file__input__output__;
                    this->__syncroned_input_output_system__ = other.__syncroned_input_output_system__;
                    this->__input__ = std::move(other.__input__);
                    this->__output__ = std::move(other.__output__);
                }
                return *this;
            }
            iofstream &operator=(iofstream &&other)
            {
                if (this != &other)
                {
                    if (__input__ != nullptr)
                        delete __input__;
                    if (__output__ != nullptr)
                        delete __output__;
                    if (__syncroned__file__input__output__ != nullptr)
                        delete __syncroned__file__input__output__;
                    this->__syncroned_input_output_system__ = other.__syncroned_input_output_system__;
                    this->__syncroned__file__input__output__ = other.__syncroned__file__input__output__;
                    other.__syncroned__file__input__output__ = nullptr;
                    this->__input__ = other.__input__;
                    other.__input__ = nullptr;
                    this->__output__ = other.__output__;
                    other.__output__ = nullptr;
                }
                return *this;
            }
            /// @brief A traves de esta funcion obtienes la entrada de datos del archivo
            /// @return Devuelve una referencia a un ifstream
            ifstream &in();
            /// @brief A traves de esta funcion obtienes la salida de datos del archivo
            /// @return Devuelve una referencia a un ofstream
            ofstream &out();
            /// @brief Permite verificar si el archivo fue abierto como binario o no
            /// @return Devuelve verdadero si asi fue
            bool isBinaryFile();
            /// @brief Activa o desactiva la configuracion de entrada y salida sincronizada
            /// @param __v Activa la sincronizacion si es verdadero, si no la desactiva
            /// @param Syncroned_fstream_reference Referencia a un elemento de tipo (?ios::fstream?) que se usara como manejador del archivo
            void setSyncronedInputOutputSystem(bool __v, fstream &Syncroned_fstream_reference);
            ~iofstream()
            {
                if (__input__ != nullptr)
                    delete __input__;
                if (__output__ != nullptr)
                    delete __output__;
                if (__syncroned__file__input__output__ != nullptr)
                    delete __syncroned__file__input__output__;
            }
        };
    }
}
#endif
