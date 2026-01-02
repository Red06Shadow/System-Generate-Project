#include <commands/commands.hpp>

std::map<std::string, Handle> Command::__commnads_interns = {
    {"-v", version},
    {"--version", version},
    {"-h", help},
    {"--help", help},
    {"-d", destine},
    {"--destine", destine},
    {"-n", name},
    {"--name", name},
    {"-f", format},
    {"--format", format}};

bool Command::create(Argv &iterator)
{
    iterator.next();
    while (iterator.get() != iterator.end())
    {
        Handle handle;
        if (!(handle = __commnads_interns[*iterator.get()]))
            throw systems::exception("La operacion: " + std::string(*iterator.get()) + " no es valida como comando del programa.");
        if (handle(iterator))
            break;
        iterator.next();
    }
    return false;
}

bool Command::version(Argv &iterator)
{
    std::cout << "Version: 1.0.0 System Generate Proyects @ Red06Shadow." << std::endl;
    return true;
}
bool Command::help(Argv &iterator)
{
    std::cout << "-v/--version : Version del activo\n-h/--help : Ayuda de comandos generales o si es uno especifico\n3. -d/--destine \"Ruta de localozacion\" : Ingresa donde se generara el proyecto, por defecto la ruta actual del terminal\n-n/--name \"Nombre del projecto\" : Ingresa el nombre del proyecto(Tanto para carpetas como para valores internos(proximamante)), por defecto el nombre de la carpeta acutual de la ruta de la terminal\n-f/format-- : Formato del proyecto, obligatorio, define para que lenguaje y como se generara el proyecto\nSi se agrega -o como comando se permite leer un archivo de configuracion definido por el usuario\nSi no, se leera simplemente la cadena como el nombre de un archivo dentro del repositorio del programa." << std::endl;
    return true;
}
bool Command::destine(Argv &iterator)
{
    iterator.next();
    if (iterator.get() == iterator.end())
        throw systems::exception("El comando (-d/--destine) debe recibir una ruta a un directorio.");
    sources_proyect = systems::Url(*iterator.get(), true);
    if (!filesystem::is_directory(sources_proyect))
        throw systems::exception("La ruta especificada en el comando(-d/--destine), debe ser un directorio.");
    destine_user = true;
    return false;
}
bool Command::name(Argv &iterator)
{
    iterator.next();
    if (iterator.get() == iterator.end())
        throw systems::exception("El comando (-n/--name) debe recibir el nombre del proyecto.");
    name_proyect = *iterator.get();
    name_user = true;
    return false;
}
bool Command::format(Argv &iterator)
{
    iterator.next();
    if (iterator.get() == iterator.end())
        throw systems::exception("El comando (-f/--format) debe recibir una cadena de caractres que represente una ruta o un valor de archivo por defecto.");
    if (std::strcmp(*iterator.get(), "-o") != 0)
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
        iterator.next();
        if (iterator.get() == iterator.end())
            throw systems::exception("El comando (-o) debe recibir una cadena de caracteres con la ruta del archivo especificada.");
        sources_configs = systems::Url(*iterator.get());
        if (!filesystem::is_regular_file(sources_configs))
            throw systems::exception("La ruta especificada en el comando(-o), debe ser un archivo regular.");
    }
    sources_user = true;
    return false;
}
void Command::is_all_ready()
{
    if (!sources_user)
        throw systems::exception("Es obligatorio escribir el formato(-f/--format) para la generacion del proyecto.");
    if (!destine_user)
        sources_proyect = filesystem::current_directory();
    if (!name_user)
        name_proyect = sources_proyect.name();
}
bool Command::excecute(const char *argv[], size_t size)
{
    Argv iterator(argv, size);
    bool exit__ = false;
    if (size < 2)
    {
        version(iterator);
        return true;
    }
    iterator.next();
    while (iterator.get() != iterator.end())
    {
        Handle handle;
        if (!(handle = __commnads_interns[*iterator.get()]))
            throw systems::exception("La operacion: " + std::string(*iterator.get()) + " no es valida como comando del programa.");
        if (exit__ = handle(iterator))
            break;
        iterator.next();
    }
    if (exit__)
        return true;
    is_all_ready();
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
        return true;
    }
    catch (const sgp::exceptions &e)
    {
        std::cerr << e.what() << std::endl;
        Excecute::error_cleaner();
        std::cout << "Fallido a las: " << systems::time::time_point(systems::time::now()).to_string() << std::endl;
    }
    return false;
}