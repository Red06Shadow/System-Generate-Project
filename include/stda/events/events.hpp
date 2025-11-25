#include <stda/utilitys/utilitys.hpp>
#include <functional>

#ifndef EVENTSSTDX
#define EVENTSSTDX

/* @Documentacion:
 * Este archivo se crea con el objectivo de crear una clase que pueda almacenar funciones y luego puedan ser llamadas como eventos
 * disenados para cumplir con necesidades variadas del programador.
*/

template <typename... _Params>
class events
{
private:
    /// @brief Variable interna que almacena la funcion
    void(*handle)(_Params...);
public:
    events() : handle(nullptr) {}
    /*!Importante!
    * Por alguna razon que escapa de mis conicimientos actuales no puedo definir a partir del tipo de la funcion la cantidad de argumentos para _Params
    * Actualmente se recomienda encarecidamente deginir los tipos de datos de los argumentos en la plantilla de events
    * Las funciones no pueden refornar valores por el momento hasta que inbvestigue un poco mas sobre el uso de estas plantillas
    * */
    template<typename Calleble>
    events(Calleble&& callback) : handle(std::forward<Calleble>(callback)) {}
    /// @brief Funcion para llamar al evento generado segun un numero de parametros que insertes
    /// @tparam ...Args Plantilla que carga los parametros indeterminados de la funcion
    /// @param ...args Contenedor de los argumentos
    template<typename... Args>
    void emit(Args&&... args) {
        static_assert(sizeof...(Args) == sizeof...(_Params), "Número de argumentos incorrecto");
        if (handle)
            handle(std::forward<Args>(args)...);
    }
};

#endif