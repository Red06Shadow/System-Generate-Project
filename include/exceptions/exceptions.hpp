#include <stda/system/exceptions/exceptions.hpp>
#include <stda/sstrings/sstrings.hpp>
#include <stdlib.h>

#ifndef EXCEPTIONSLENGAJE
#define EXCEPTIONSLENGAJE
namespace sgp
{
    class exceptions : public systems::exception
    {
    private:
        std::string cadena(size_t posicion_in_line, size_t posicion_in_line_end, size_t sizelineerror) const
        {
            std::string str;
            if (posicion_in_line == -1ULL)
                return "";
            for (size_t i = 0; i < sizelineerror; i++)
            {
                if (i >= posicion_in_line && i < posicion_in_line_end)
                    str.push_back('^');
                else
                    str.push_back(' ');
            }
            return str;
        }

    public:
        exceptions(const std::string &message, size_t _n_lines, const size_t ini, const size_t end, const std::string &_lineerror) : systems::exception(systems::exception::error::__other)
        {
            std::string str_main = "\0";
            str_main = message + "\n\t Linea: " + std::to_string(_n_lines) + "; Pocision: " + std::to_string(ini) + "\n" + _lineerror + "\n" + cadena(ini, end, _lineerror.size());
            this->__other__ = new char[str_main.size() + 1];
            std::strcpy(__other__, str_main.c_str());
        }
        exceptions(const char *message, size_t _n_lines, const size_t ini, const size_t end, const std::string &_lineerror) : systems::exception(systems::exception::error::__other)
        {
            std::string str_main = message;
            str_main += "\n\t Linea: " + std::to_string(_n_lines) + "; Pocision: " + std::to_string(ini) + "\n" + _lineerror + "\n" + cadena(ini, end, _lineerror.size());
            this->__other__ = new char[str_main.size() + 1];
            std::strcpy(__other__, str_main.c_str());
        }
        exceptions(const std::string &message, size_t _n_lines, const std::string &_cadena_error, const std::string &_lineerror) : systems::exception(systems::exception::error::__other)
        {
            size_t ini = sstring::find_word(_cadena_error, _lineerror);
            size_t end = ini + _cadena_error.size();
            std::string str_main = "\0";
            str_main = message + "\n\t Linea: " + std::to_string(_n_lines) + "; Pocision: " + std::to_string(ini) + "\n" + _lineerror + "\n" + cadena(ini, end, _lineerror.size());
            this->__other__ = new char[str_main.size() + 1];
            std::strcpy(__other__, str_main.c_str());
        }
    };
} // namespace sgp
#endif