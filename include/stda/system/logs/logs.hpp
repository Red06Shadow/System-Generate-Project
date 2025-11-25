#include <stda/system/files/filesystem.hpp>
#include <stda/sstrings/sstrings.hpp>
#include <stda/system/time/time.hpp>
#include <stda/system/memory/memory.hpp>
#include <stda/utilitys/utilitys.hpp>

#ifndef LOGSSTDX
#define LOGSSTDX

/* @Documentacion:
 * Este archivo contiene la clase logs para el manejo de mensajes ya sean 
 * comunes o excepciones enviadas por los programs que usen dicho archivo
 */


/// @brief Este es el espacio de nombre que contiene todo lo relacionado con el log
namespace systems
{
    /// @brief Clase que maneja 
    class logs
    {
    public:
        /// @brief Id para identificar el nuvel del log
        enum class type : u8
        {
            menssage,
            warning,
            error,
            none
        };
        /// @brief Cadena que guarda el mensaje
        __stringbuffer message;
        /// @brief Id del log
        type id;
        /// @brief Tiempo en el que se emitio el log
        time::time_point time;
        /// @brief Construtor basico para el log
        /// @param _message Mensaje a enviar de tipo(?const __caracter*?)
        /// @param _id Id del log
        logs(const __caracter* _message, type _id);
        /// @brief Construtor basico para el log
        /// @param _message Mensaje a enviar de tipo(?__string?)
        /// @param _id Id del log
        logs(const __string& _message, type _id);
        /// @brief Construtor basico para el log
        /// @param _message Mensaje a enviar de tipo(?__stringbuffer?)
        /// @param _id Id del log
        logs(const __stringbuffer& _message, type _id);
        /// @brief Construtor basico para el log
        /// @param _message Excepcion recibida
        /// @param _id Id del log
        logs(const std::exception& _message, type _id);
        logs(const logs& other) {
            message = other.message;
            id = other.id;
            time = other.time;
        }
        logs(logs&& other) {
            message = other.message;
            id = other.id;
            time = other.time;
        }
        ~logs() {}
    };
    class log_manager
    {
    private:
        static const char* codecolor[4];
        static const char* codemensage[4];
        static std::vector<logs> allocator;
        static const char* nameprogram;
    public:
        /// @brief Funcion que exporta todos los mensajes hacia un archivo dentro del la ruta especificada
        /// @param path Ruta del archivo
        static void exportfile(const systems::Url& path = systems::Url(__argv[0]));
        /// @brief Funcion que muestra todos los logs por consola
        static void view();
        /// @brief Agrega un log al administrador para luego enviarlo a donde se desee
        /// @param log Log deseado
        static void serialize(const logs& log);
    };
} // namespace logssystem

#endif