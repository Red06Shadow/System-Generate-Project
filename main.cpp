#include <commands/commands.hpp>
#include <stda/system/logs/logs.hpp>

/*
 * Crear el codigo para que SG-Proyect evolucione a un administrador completo de proyectos
 * Separa las funciones en una de crear
 * Cada vez que cree un proyecto genere un archivo con los datos de cada proyecto generado que debe contener
 * Metadatos, Ubicacion del proyecto, Id de version de SG, Commit de GitHub, Release, Paquetes usados(otros proyectos de SG)
 * Metadatos: Nombre, Descripcion del programa(archivo README.md), Version de usario, Descripcion de actalizacion(archivo UPDATE.md)
 * Realese: Empieza con un codigo especial 0x88, 0x44, 0x10, 0x45, luego Metadatos: Nombre o ruta relativa, Si es carpeta o archivo, Ruta, Tamano(si es carpeta se ignora)
*/


int main(int args, const char *argv[])
{
    installed_program = systems::Url(__argv[0]);
    sources_proyect = filesystem::current_directory();
    try
    {
        Command::excecute(argv, args);
    }
    catch (const systems::exception &e)
    {
        Excecute::error_cleaner();
        systems::log_manager::serialize(systems::logs(e, systems::logs::type::error));
        systems::log_manager::view();
    }
    catch (const std::exception &e)
    {
        Excecute::error_cleaner();
        systems::log_manager::serialize(systems::logs(e, systems::logs::type::error));
        systems::log_manager::view();
        systems::log_manager::exportfile(sources_proyect + "log.txt");
    }
    return 0;
}