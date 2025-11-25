#include <stda/numbers/numbers.hpp>
#include <time.h>
#include <ctime>
#include <chrono>
#include <vector>
#include <stdexcept>
#include <thread>
#include <windows.h>
#include <iomanip>

#ifndef TIMES
#define TIMES

/* @Documentacion:
 * Este archivo contiene funciones el maneo del tiempo tanto de fechas como de conteos en nanosegundos
 */

namespace systems
{
    /// @brief Clase que maneja el tiempo de sistema
    class time
    {
    private:
        static const char *weekstext[7];
        static const char *monthstext[12];

    public:
        /// @brief Idnica como se mostrara la fecha
        enum class formatdate : u8
        {
            shortlow,
            large,
            largewithweekday
        };
        /// @brief Idnica como se mostrara la hora
        enum class formatclock : u8
        {
            short12h,
            short24h,
            large12h,
            large24h
        };
        /// @brief Clase que almacena un punto determinadi del tiempo en segundos
        class time_point
        {
        protected:
            typedef std::string (*TimerFormat)(const time_point &__tallocator);

        private:
            u16 years;
            u16 month;
            u16 weeks;
            ///////////
            u16 days_of_years;
            u16 days_of_month;
            u16 days_of_weeks;
            ///////////
            u16 hours;
            u16 mins;
            u16 seconds;
            static TimerFormat to_stringformatdate[4];
            static TimerFormat to_stringformatclock[4];

            static u16 clockregulate12h(u16 horsformat24h);
            static std::string clocklarge12(const time_point &__tallocator);
            static std::string clocklarge24(const time_point &__tallocator);
            static std::string clockshort12(const time_point &__tallocator);
            static std::string clockshort24(const time_point &__tallocator);
            static std::string dateshort(const time_point &__tallocator);
            static std::string datelarge(const time_point &__tallocator);
            static std::string datelargewithweekday(const time_point &__tallocator);

        public:
            /// @brief Constuctor por defecto
            time_point() {}

            time_point(time_t __now__)
            {
                tm *__sytime = localtime(&__now__);
                years = __sytime->tm_year, month = __sytime->tm_mon, weeks = __sytime->tm_isdst, days_of_years = __sytime->tm_yday, days_of_month = __sytime->tm_mday, days_of_weeks = __sytime->tm_wday, hours = __sytime->tm_hour, mins = __sytime->tm_min, seconds = __sytime->tm_sec;
            }
            /// @brief Constructor a partir de insertar cada dato de la fecha deseada desde 1900
            /// @param __years Anos
            /// @param __month Meses
            /// @param __weeks Semanas
            /// @param __days_of_years Dia del ano(1-365)
            /// @param __days_of_month Dia del mes(1-31/30/28/29)
            /// @param __days_of_weeks Dia de la semana(1-7)
            /// @param __hours Horas
            /// @param __mins Minutos
            /// @param __seconds Segundos
            time_point(u16 __years, u16 __month, u16 __weeks, u16 __days_of_years, u16 __days_of_month, u16 __days_of_weeks, u16 __hours, u16 __mins, u16 __seconds) : years(__years), month(__month), weeks(__weeks), days_of_years(__days_of_years), days_of_month(__days_of_month), days_of_weeks(__days_of_weeks), hours(__hours), mins(__mins), seconds(__seconds) {}
            /// @brief Transforma el tiempo a una cadena de caracteres
            /// @param fdate Formato de dia
            /// @param fclock Formato de hora
            /// @return Devuelve la cadena de tipo (?std::string?) de la fecha
            std::string to_string(formatdate fdate = formatdate::shortlow, formatclock fclock = formatclock::short12h)
            {
                return (to_stringformatdate[static_cast<u8>(fdate)])(*this) + "   " + (to_stringformatclock[static_cast<u8>(fclock)])(*this);
            }
            ~time_point() {}
        };
        /// @brief Obtiene si el ano sera de 365 o 366 dias
        /// @param year Ano deseado
        /// @return Devuelve el numero de dias especificos
        static u16 get_day_of_years(u16 year) { return ((year % 4 == 0 && year % 400 != 0) ? 366 : 365); }
        /// @brief Obtiene el tiempo actual en segundos desde el 1/1/1900
        /// @return Devuelve el tiempo actual puro en base a (?time_t?)
        static time_t now() { return std::time(nullptr); }
        /// @brief Convierte una unidad de tiempo tipo(?FILETIME?) a (?time_t?)
        /// @param _input valor (?FILETIME?)
        /// @return Devuelve el resultado en (?time_t?)
        static time_t timefile_to_time_t(const FILETIME &_input)
        {
            ULARGE_INTEGER __previus;
            __previus.HighPart = _input.dwHighDateTime;
            __previus.LowPart = _input.dwLowDateTime;
            return (__previus.QuadPart / 10000000ULL) - 11644473600ULL;
        }
        /// @brief Convierte una unidad de tiempo tipo (?time_t?) a (?FILETIME?)
        /// @param _input valor (?time_t?)
        /// @return Devuelve el resultado en (?FILETIME?)
        static FILETIME time_t_to_timefile(const time_t &_input)
        {
            ULARGE_INTEGER __previus;
            FILETIME _result;
            __previus.QuadPart = (_input + 11644473600ULL) * 10000000ULL;
            _result.dwHighDateTime = __previus.HighPart;
            _result.dwLowDateTime = __previus.LowPart;
            return _result;
        }
    };
    /// @brief Contiene funciones para el manejo del tiempo de ejecucion del programa
    class chrono
    {
    public:
        /// @brief Clase que maneja el tiempo del programa
        typedef std::chrono::high_resolution_clock::time_point time_point;
        using seconds = std::chrono::seconds;
        using milliseconds = std::chrono::milliseconds;
        using nanoseconds = std::chrono::nanoseconds;

    private:
        static std::vector<time_point> clockcontainer;

    public:
        /// @brief Obtienes el punto de tiempo guardado en el administrador de chrono
        /// @param idclock Identificador del punto de tiempo
        /// @return Devuelve la referencia al objecto de (?time_point?)
        static time_point &get(size_t idclock) { return clockcontainer[idclock]; }
        /// @brief Agrega el punto de tiempo al administrador de chrono
        /// @param _clock Punto de tiempo dado en (?time_point?)
        /// @return Devuleve el id dentro del administrador
        static size_t push(const time_point &_clock)
        {
            clockcontainer.push_back(_clock);
            return clockcontainer.size() - 1;
        }
        /// @brief Obtiene el valor actual en nanosegundos del conteo del programa
        /// @return Devuelve un (?time_point?) con los nanosegundos transcurridos
        static const time_point now() { return std::chrono::high_resolution_clock::now(); }

        /// @brief Obtienes la conevsruion del (?time_point?) a segundos en dependencia del tipo de dato en (?_Notation?)
        /// @tparam _Notation Tipo de dato primitivo de retorno para el modo de segundos(!Importante: El codigo no funcionara si insertas otras clase que no sean las corresponidentes en este archivo para el manejo de etos casos!)
        /// @param _clock Referencia constante de un (?time_point?)
        /// @return Devuelve la cantidad de segundos del tipo _Notation
        template <typename _Notation>
        static const _Notation getSeconds(const time_point &_clock)
        {
            return std::chrono::duration_cast<std::chrono::seconds>(_clock - time_point()).count();
        }
        /// @brief Obtienes la conevsruion del (?time_point?) a milisegundos en dependencia del tipo de dato en (?_Notation?)
        /// @tparam _Notation Tipo de dato primitivo de retorno para el modo de milisegundos(!Importante: El codigo no funcionara si insertas otras clase que no sean las corresponidentes en este archivo para el manejo de etos casos!)
        /// @param _clock Referencia constante de un (?time_point?)
        /// @return Devuelve la cantidad de milisegundos del tipo _Notation
        template <typename _Notation>
        static const _Notation getMiliseconds(const time_point &_clock)
        {
            return std::chrono::duration_cast<std::chrono::milliseconds>(_clock - time_point()).count();
        }
        /// @brief Obtienes la conevsruion del (?time_point?) a nanosegundos en dependencia del tipo de dato en (?_Notation?)
        /// @tparam _Notation Tipo de dato primitivo de retorno para el modo de nanosegundos(!Importante: El codigo no funcionara si insertas otras clase que no sean las corresponidentes en este archivo para el manejo de etos casos!)
        /// @param _clock Referencia constante de un (?time_point?)
        /// @return Devuelve la cantidad de nanosegundos del tipo _Notation
        template <typename _Notation>
        static const _Notation getNanoseconds(const time_point &_clock)
        {
            return (_clock - time_point()).count();
        }
        /// @brief Transforma el valor de una duracion de tiempi dada por (?std::chrono::duration<int64_t, std::nano>?) en un valor entero segun un tipo de dato insertado en (?_Fromat?)
        /// @tparam _Fromat Tipo de dato de retorno para la base del tiempo(!Importante: El codigo no funcionara si insertas otras clase que no sean las corresponidentes en este archivo para el manejo de etos casos!)
        /// @param __duration Duracion de tipo (?std::chrono::duration<int64_t, std::nano>?)
        /// @return Devuleve el conteo ddel tiempo en base a (?_Fromat?)
        template <typename _Fromat = std::chrono::milliseconds>
        static const size_t count(const std::chrono::duration<int64_t, std::nano> &__duration)
        {
            return std::chrono::duration_cast<_Fromat>(__duration).count();
        }
        /// @brief Retorna segun el tipo deseado por (?_Notation?) y la base de tiempo (?_Fromat?) el maximo conteo que puede realizar con ese tipo de dato
        /// @tparam _Notation Tipo de dato primitivo con el que se retornara el valor
        /// @tparam _Fromat Tipo de dato de retorno para la base del tiempo(!Importante: El codigo no funcionara si insertas otras clase que no sean las corresponidentes en este archivo para el manejo de etos casos!)
        /// @return Devuleve la maxima capacidad de valores del tiempo ra el tipo especificado
        template <typename _Notation, typename _Fromat = std::chrono::milliseconds>
        static _Notation max() { return std::chrono::duration<_Notation, _Fromat>::max(); }
        /// @brief Retorna segun el tipo deseado por (?_Notation?) y la base de tiempo (?_Fromat?) el minimo conteo que puede realizar con ese tipo de dato
        /// @tparam _Notation Tipo de dato primitivo con el que se retornara el valor
        /// @tparam _Fromat Tipo de dato de retorno para la base del tiempo(!Importante: El codigo no funcionara si insertas otras clase que no sean las corresponidentes en este archivo para el manejo de etos casos!)
        /// @return Devuleve la minima capacidad de valores del tiempo ra el tipo especificado
        template <typename _Notation, typename _Fromat = std::chrono::milliseconds>
        static _Notation min() { return std::chrono::duration<_Notation, _Fromat>::min(); }
        /// @brief Dureme el codigo por un tiempo determinado por el (?_Fromat?)
        /// @tparam _Fromat Tipo de dato para la base del tiempo(!Importante: El codigo no funcionara si insertas otras clase que no sean las corresponidentes en este archivo para el manejo de etos casos!)
        /// @param time Entero de 64bit del tiempo
        /// @param message Un mensaje que se desee enviar durante la espera
        template <typename _Fromat = std::chrono::milliseconds>
        static void sleep(int64_t time, const char *message = nullptr)
        {
            if (message != nullptr)
                std::cout << ">> " << message << std::endl;
            std::this_thread::sleep_for(_Fromat(time));
        }
        /// @brief Pausa el codigo indeterminadamente a hasta que el valor booleano cambie a false
        /// @param _v Referencia boleana de bandera(signal)
        static void wait_for_signal(bool &_v)
        {
            while (_v)
                ;
        }
        /// @brief Pausa el codigo indeterminadamente hasta que el usuario pulse la tecla enter
        static void wait_for_input()
        {
            char k;
            std::cin >> k;
            std::cin.clear();
        }
    };
}

#endif