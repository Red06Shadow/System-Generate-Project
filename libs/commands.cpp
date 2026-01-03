#include <commands/commands.hpp>

std::map<std::string, Command::Handle> Command::commands = {
    {"-v", version},
    {"--version", version},
    {"-h", help},
    {"--help", help},
    {"-dir", create_proyect_folder},
    {"-name", create_proyect_name},
    {"-config", create_proyect_format},
    {"create", create}};

void Command::cheeck_valid_command(const Argv &iterator, Command::Id id_inserted, Command::Id id_validate)
{
    if (id_inserted != id_validate)
        throw systems::exception("La operacion: " + std::string(*iterator.get()) + " no se puede ejecutar bajo un entorno de: " + commnads_names[static_cast<u8>(id_inserted)] + ", este comando pertenece a la seccion: " + commnads_names[static_cast<u8>(id_validate)] + ".");
}
void Command::help_command_not_next(bool is_help_command_insert)
{
    if (is_help_command_insert)
        throw systems::exception("No se pueden agregar mas commandos despues de help.");
}

bool Command::create_proyect_name_insert()
{
    if (name_user)
        return true;
    std::cout << "Nombre del proyecto(Pulse Enter para default): ";
    std::getline(std::cin, name_proyect);
    if (name_proyect.empty())
        name_proyect = sources_proyect.name();
    return false;
}

bool Command::create_proyect_folder_insert()
{
    std::string sources_proyect_p = std::string();
    if (destine_user)
        return true;
    std::cout << "Ruta del proyecto(Pulse Enter para default): ";
    std::getline(std::cin, sources_proyect_p);
    if (sources_proyect_p.empty())
        sources_proyect = filesystem::current_directory();
    else
        sources_proyect = systems::Url(sources_proyect_p, true);
    return false;
}

bool Command::create_proyect_format_insert(const Argv &iterator)
{
    std::string sources_configs_p = std::string();
    if (sources_user)
        return true;
    std::cout << "Nombre del archivo de configuracion o ruta de ese archvivo: ";
    std::getline(std::cin, sources_configs_p);
    if (sources_configs_p.empty())
        throw systems::exception("Es obligatorio escribir el formato(-config) para la generacion del proyecto.");
    if (systems::Url::is_corret(sources_configs_p))
    {
        sources_configs = systems::Url(sources_configs_p, true);
        return false;
    }
    else
    {
        sources_configs = systems::Url::parent(*iterator.begin()) + "config";
        bool finder = false;
        for (auto &&i : filesystem::container(sources_configs))
        {
            if (std::strcmp(i.cFileName, sources_configs_p.c_str()) == 0)
            {
                sources_configs = sources_configs + i.cFileName;
                finder = true;
                break;
            }
        }
        if (!finder)
            throw systems::exception("No se ingreso un archivo de configuracion valido o la ruta insertda no es valida: " + std::string(*iterator.get()));
    }
    return false;
}
bool Command::create(Argv &iterator, Command::Id id)
{
    bool __exit = false;
    cheeck_valid_command(iterator, id, Command::Id::none);
    /// Siguiente argumento
    iterator.next();
    /// Codigo
    while (iterator.get() != iterator.end())
    {
        Handle handle;
        help_command_not_next(__exit);
        if (!(handle = commands[*iterator.get()]))
            throw systems::exception("La operacion: " + std::string(*iterator.get()) + " no es valida como comando de secuencia create.");
        __exit = handle(iterator, Command::Id::create);
    }
    if (__exit)
        return true;

    create_proyect_format_insert(iterator);
    create_proyect_folder_insert();
    create_proyect_name_insert();

    try
    {
        std::cout << "Comienza la operacion a las: " << systems::time::time_point(systems::time::now()).to_string() << std::endl;
        sources = systems::ios::ifstream(sources_configs, true);
        Parser::initialize();
        AtsList &list = Parser::parsing();
        Excecute::set_labels(Parser::resolve_references());
        Excecute::excecute(list, 0);
        std::cout << "Termina la operacion satisfactoriamente a las: " << systems::time::time_point(systems::time::now()).to_string() << std::endl;
        // Parser::view(list);
        return false;
    }
    catch (const sgp::exceptions &e)
    {
        std::cerr << e.what() << std::endl;
        Excecute::error_cleaner();
        std::cout << "Fallido a las: " << systems::time::time_point(systems::time::now()).to_string() << std::endl;
    }
    return false;
}

bool Command::version(Argv &iterator, Command::Id id)
{
    cheeck_valid_command(iterator, id, Command::Id::none);
    std::cout << "Version: 1.0.0 System Generate Proyects @ Red06Shadow." << std::endl;
    /// Siguiente argumento autoatico para siguinte operacion
    iterator.next();
    return true;
}
bool Command::help(Argv &iterator, Command::Id id)
{
    switch (id)
    {
    case Command::Id::none:
        std::cout << "-v/--version : Version del activo\n\n\
-h/--help : Ayuda de comandos generales o si es necesario muestra la ayuda especifica de cada comando\n\n\
create [args] : Se utilza para crear proyectos con el sistema inetrno del gestor a partir de archivos de configuracion.sgc\
Los proyectos generados con este comando cuentan con las configuraciones de GitHub y un sistema de proyectos locales para administrar las versiones de \
estos en el dispositivo convirtiendo en modulos o paquetes en algunos casos los realese para usarlos en otros proyectos de SG-Proyect de manera que su \
importacion, actualizacion y distrribucion entre estos sea mas rapida y eficiente." << std::endl;
        break;
    case Command::Id::create:
        std::cout << "--h/--help : Muestra una ayuda como usar los comandos dentro de create\n\n-dir \"Ruta de localozacion\" : Ingresa donde se generara \
el proyecto, por defecto la ruta actual del terminal\n\n-name \"Nombre del projecto\" : Ingresa el nombre del proyecto(Tanto para carpetas como para valores \
internos(proximamante)), por defecto el nombre de la carpeta acutual de la ruta de la terminal\n\n-config : Formato del proyecto, obligatorio, define para \
que lenguaje y como se generara el proyecto\nSi se agrega -user como comando se permite leer un archivo de configuracion definido por el usuario\nSi no, se leera \
simplemente la cadena como el nombre de un archivo dentro del repositorio del programa.\n\n\
En caso de solo escribir algunos o ningun argumento se abrira una interfaz para completar los valores necesarion, solo el config es obligatorio debido a que \
apartir de este se genera el formato del proyecto. \n\n Ejemplo: SG-Projects create -dir \"C:/.../local\" -name \"Proyect1\" -config \"c++_projects_cmake.sgc\"" << std::endl;
        break;
    default:
        break;
    }
    /// Siguiente argumento autoatico para siguinte operacion
    iterator.next();
    return true;
}
bool Command::create_proyect_folder(Argv &iterator, Command::Id id)
{
    cheeck_valid_command(iterator, id, Command::Id::create);
    /// Siguiente argumento
    iterator.next();
    /// Codigo
    if (iterator.get() == iterator.end())
        throw systems::exception("El comando (-dir) debe recibir una ruta a un directorio.");
    sources_proyect = systems::Url(*iterator.get(), true);
    if (!filesystem::is_directory(sources_proyect))
        throw systems::exception("La ruta especificada en el comando(-dir), debe ser un directorio.");
    destine_user = true;
    /// Siguiente argumento autoatico para siguinte operacion
    iterator.next();
    return false;
}
bool Command::create_proyect_name(Argv &iterator, Command::Id id)
{
    cheeck_valid_command(iterator, id, Command::Id::create);
    /// Siguiente argumento
    iterator.next();
    /// Codigo
    if (iterator.get() == iterator.end())
        throw systems::exception("El comando (-name) debe recibir el nombre del proyecto.");
    name_proyect = *iterator.get();
    name_user = true;
    /// Siguiente argumento autoatico para siguinte operacion
    iterator.next();
    return false;
}
bool Command::create_proyect_format(Argv &iterator, Command::Id id)
{
    cheeck_valid_command(iterator, id, Command::Id::create);
    /// Siguiente argumento
    iterator.next();
    /// Codigo
    if (iterator.get() == iterator.end())
        throw systems::exception("El comando (-config) debe recibir una cadena de caractres que represente una ruta o un valor de archivo por defecto.");
    if (std::strcmp(*iterator.get(), "-user") != 0)
    {
        sources_configs = systems::Url::parent(*iterator.begin()) + "config";
        bool end = false;
        for (auto &&i : filesystem::container(sources_configs))
        {
            if (std::strcmp(i.cFileName, *iterator.get()) == 0)
            {
                sources_configs = sources_configs + i.cFileName;
                end = true;
                break;
            }
        }
        if (!end)
            throw systems::exception("No se ingreso un archivo de configuracion valido: " + std::string(*iterator.get()));
    }
    else
    {
         /// Siguiente argumento
        iterator.next();
        if (iterator.get() == iterator.end())
            throw systems::exception("El comando (-user) debe recibir una cadena de caracteres con la ruta del archivo especificada.");
        sources_configs = systems::Url(*iterator.get());
        if (!filesystem::is_regular_file(sources_configs))
            throw systems::exception("La ruta especificada en el comando(-user), debe ser un archivo regular.");
    }
    sources_user = true;
    /// Siguiente argumento autoatico para siguinte operacion
    iterator.next();
    return false;
}
bool Command::excecute(Argv& iterator)
{
    
    bool __exit = false;
    if (iterator.get() == iterator.end())
    {
        version(iterator, Command::Id::none);
        help(iterator, Command::Id::none);
        return true;
    }

    while (iterator.get() != iterator.end())
    {
        Handle handle;
        help_command_not_next(__exit);
        if (!(handle = commands[*iterator.get()]))
            throw systems::exception("La operacion: " + std::string(*iterator.get()) + " no es valida como comando base del programa.");
        __exit = handle(iterator, Command::Id::none);
    }
    if (__exit)
        return true;

    return false;
}