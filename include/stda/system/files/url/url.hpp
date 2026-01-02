#include <stda/system/exceptions/exceptions.hpp>
#include <stda/sstrings/sstrings.hpp>
#include <windows.h>
#include <vector>

#include <codecvt>
#include <stdlib.h>
#include <io.h>
#include <fcntl.h>

#ifndef URL
#define URL

/* @Documentacion:
 * Este archivo contiene el manejo de direcciones a archivos a partir de la clase URL
 * aunque ya existe en el standart de c++ quise crearlas para manejra y entender como funcionan y
 * mejoralas con el tiempo
 */

#include <PathCch.h>

#if defined(USINGWCARACTER)
#define __caracter wchar_t
using __string = std::wstring;
using __stringbuffer = wstringbuffer;
#define __compare(str1, str2) std::wcscmp(str1, str2)
#define __size(str1) std::wcslen(str1)
#define __copy(str1, str2) std::wcscpy(str1, str2)
#define __ncopy(str1, str2, n_char) std::wcscpy(str1, str2, n_char)
#define __exceptiosconvert(str) std::string(std::stringconverter::convert_utf8_to_ascii(str))
#define __concaturl L"\\"
#define __standartcout std::wcout
#define __standartcin std::wcin
#define __to_str(value) std::to_wstring(value)
#define __dot L"."
#define __dot2 L".."
#else
#define __caracter char
using __string = std::string;
using __stringbuffer = stringbuffer;
#define __compare(str1, str2) std::strcmp(str1, str2)
#define __size(str1) std::strlen(str1)
#define __copy(str1, str2) std::strcpy(str1, str2)
#define __ncopy(str1, str2, n_char) std::strncpy(str1, str2, n_char)
#define __exceptiosconvert(str) std::string(str)
#define __concaturl "\\"
#define __standartcout std::cout
#define __standartcin std::cin
#define __to_str(value) std::to_string(value)
#define __dot "."
#define __dot2 ".."
#endif

#define label(__name__) \
    __name__:
#define etiqueta(__name__) label(__name__)

#pragma comment(lib, "Pathcch.lib")
namespace systems
{
    /// @brief Clase que se encarga de manejar las rutas de archivos
    class Url
    {
    private:
        bool __consta__;
        const __caracter *__path__;
        static void __generate__(__caracter **destine, const __caracter *sources);
        static void __generate__(__caracter **destine, const __caracter *sources, size_t size);
        // friend files;

    public:
        /// @brief Una pequena estructura para el control del directorio padre y el nombre del archivo o directorio
        struct Atributes
        {
            const __caracter *nameParent;
            const __caracter *nameSon;
        };
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        /// @brief Constructor por defecto
        Url() : __path__(nullptr), __consta__(false) {}
        /// @brief Constructor con ruta base sin abrir nueva memoria
        /// @param path Ruta del archivo(!Atencion: Si coloca una ruta invalida se generara un error!)
        /// @param checkExistUrl Si esta activado comprueba si existe el directorio o el archivo(!Atencion: Si se desea usar la ruta para nuevos archivos no active el valor o obtendra un error!)
        Url(const __caracter *path, bool checkExistUrl = false);
        /// @brief Constructor con ruta base copiando la cadena
        /// @param path Ruta del archivo(!Atencion: Si coloca una ruta invalida se generara un error!)
        /// @param checkExistUrl Si esta activado comprueba si existe el directorio o el archivo(!Atencion: Si se desea usar la ruta para nuevos archivos no active el valor o obtendra un error!)
        Url(__caracter *path, bool checkExistUrl = false);
        /// @brief Constructor con ruta base de tipo (?__string?)
        /// @param path Ruta del archivo(!Atencion: Si coloca una ruta invalida se generara un error!)
        /// @param checkExistUrl Si esta activado comprueba si existe el directorio o el archivo(!Atencion: Si se desea usar la ruta para nuevos archivos no active el valor o obtendra un error!)
        Url(const __string &path, bool checkExistUrl = false);
        /// @brief Constructor con ruta base de tipo (?__stringbuffer?)
        /// @param path Ruta del archivo(!Atencion: Si coloca una ruta invalida se generara un error!)
        /// @param checkExistUrl Si esta activado comprueba si existe el directorio o el archivo(!Atencion: Si se desea usar la ruta para nuevos archivos no active el valor o obtendra un error!)
        Url(const __stringbuffer &path, bool checkExistUrl = false);
        Url(const Url& other);
        Url(Url&& other);
        Url &operator=(const Url &other);
        Url &operator=(Url &&other);
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool operator==(const Url &url) { return __compare(this->__path__, url.__path__) == 0; }
        bool operator==(const __caracter *url) { return __compare(this->__path__, url) == 0; }
        bool operator==(const __string &url) { return __compare(this->__path__, url.c_str()) == 0; }
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool operator!=(const Url &url) { return __compare(this->__path__, url.__path__) != 0; }
        bool operator!=(const __caracter *url) { return __compare(this->__path__, url) != 0; }
        bool operator!=(const __string &url) { return __compare(this->__path__, url.c_str()) != 0; }
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        friend Url operator+(const Url &url, const __caracter *subdir)
        {
            __string str = url.string();
            return Url(str + (str.back() == '\\' ? "" : __concaturl) + subdir);
        }
        friend Url operator+(const Url &url, const __string &subdir)
        {
            __string str = url.string();
            return Url(str + (str.back() == '\\' ? "" : __concaturl) + subdir);
        }
        friend std::ostream &operator<<(std::ostream &os, Url _v)
        {
            os << _v.__path__;
            return os;
        }
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        /// @brief Obtienes el string de la ruta
        /// @return Devuelve una cadena de caracteres de tipo (?__string?)
        const __string string() const { return __string(__path__); }
        /// @brief Obtienes el string de la ruta
        /// @return Devuelve una cadena de caracteres de tipo (?__caracter?)
        const __caracter *c_str() const { return __path__; }

        /// @brief Obtienes el nombre del archivo o directorio
        /// @return DEvuelve una cadena de caracteres de tipo(?const __caracter?)
        const __caracter *name() const;
        /// @brief Obtienes la ruta absoluta
        /// @return Devuelve un (?Url?)
        const Url root() const;
        /// @brief Obtienes la ruta padre
        /// @return Devuelve un (?Url?)
        const Url parent() const;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        /// @brief Compara dos rutas
        /// @param url1 Ruta numero 1 de tipo (?Url?)
        /// @param url2 Ruta numero 2 de tipo (?Url?)
        /// @return Devuelve verdadero si son iguales  
        static bool equals(const Url &url1, const Url &url2);
        /// @brief Compara dos rutas
        /// @param url1 Ruta numero 1 de tipo (?Url?)
        /// @param url2 Ruta numero 2 de tipo (?const __caracter*?)
        /// @return Devuelve verdadero si son iguales
        static bool equals(const Url &url1, const __caracter *strurl);

        /// @brief Obtienes el nombre del archivo o directorio
        /// @param path Ruta de tipo (?__caracter?)
        /// @return DEvuelve una cadena de caracteres de tipo(?const __caracter?)
        static const __caracter *name(const __caracter *path);
        /// @brief Obtienes la ruta absoluta
        /// @param path Ruta de tipo (?__caracter?)
        /// @return Devuelve un (?Url?)
        static const Url root(const __caracter *path);
        /// @brief Obtienes la ruta padre
        /// @param path Ruta de tipo (?__caracter?)
        /// @return Devuelve un (?Url?)
        static const Url parent(const __caracter *path);

        /// @brief Separa las rutas de los archivos en una lista de estas
        /// @param url Ruta de tipo (?Url?)
        /// @param __vect Vector para contener los nombres de cada token(!Atencion: Debe estar vacio!)
        static const void get_tokens(const Url &url, std::vector<const __caracter *> &__vect);


        /// @brief Comprueba si la ruta es valida gramaticamente
        /// @param url Ruta de tipo (?Url?)
        /// @return Devuelve verdadero si lo es
        static const bool is_corret(const Url &url);
        /// @brief Comprueba si la ruta es valida gramaticamente
        /// @param url Ruta de tipo (?__caracter*?)
        /// @return Devuelve verdadero si lo es
        static const bool is_corret(const __caracter *path);
        /// @brief Comprueba si la ruta es valida gramaticamente
        /// @param url Ruta de tipo (?__string?)
        /// @return Devuelve verdadero si lo es
        static const bool is_corret(const __string &path);

        /// @brief Obtiene el tipo del archivo
        /// @param url Ruta de tipo (?Url?) (!Atencion: Si inserta un directorio se mostrara un error!)
        /// @return Devuelve el tipo en formato (?__string?)
        static const __string get_file_type(const Url &url);
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ~Url()
        {
            if (!this->__consta__)
                delete[] this->__path__;
        }
    };

}
#endif
