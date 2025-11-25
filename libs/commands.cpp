#include <commands/commands.hpp>

std::map<std::string, Handle2> Command::__commnads_interns = {};
bool Command::version(iteratorC &iterator)
{
    std::cout << "Version: 1.0.0 System Generate Proyects @ Alexandros Dieste Garcia" << std::endl;
    return true;
}
bool Command::help(iteratorC &iterator)
{
    std::cout << "Por ahora me da pereza la ayuda, aprendan solos" << std::endl;
    return true;
}
bool Command::destine(iteratorC &iterator)
{
    iterator.next();
    if (iterator.get() == iterator.end())
        throw std::runtime_error("Debe ingresar la ruta despues de escribir dicho comando");
    urld = systems::Url(*iterator.get(), true);
    return false;
}
bool Command::name(iteratorC &iterator)
{
    iterator.next();
    if (iterator.get() == iterator.end())
        throw std::runtime_error("Debe ingresar el nombre despues de escribir dicho comando");
    nameP = *iterator.get();
    return false;
}
bool Command::format(iteratorC &iterator)
{
    iterator.next();
    if (iterator.get() == iterator.end())
        throw std::runtime_error("Debe ingresar el nombre despues de escribir dicho comando");
    if (std::strcmp(*iterator.get(), "-o") != 0)
    {
        urls = systems::Url::parent(*iterator.begin()) + "config";
        bool end = false;
        for (auto &&i : filesystem::container(urls))
        {
            if (std::strcmp(i.cFileName, *iterator.get()) == 0)
            {
                urls = urls + i.cFileName;
                end = true;
                break;
            }
        }
        if (!end)
            throw std::runtime_error("No se ingreso un archivo de configuracion valido");
    }
    else
    {
        iterator.next();
        if (iterator.get() == iterator.end())
            throw std::runtime_error("Debe ingresar el nombre despues de escribir dicho comando");
        urls = systems::Url(*iterator.get());
    }
    sourcesacpt = true;
    return false;
}
void Command::is_all_ready()
{
    if (!sourcesacpt)
        throw std::runtime_error("Es obligatorio escribir el formato(-f/--format) para la generacion del proyecto");
}
void Command::operation_active()
{
    try
    {
        if (!nameP)
            nameP = urld.name();
        Script::init(urls, nameP, urld);
        Script::excecute();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}
void Command::comands(const char *argv[], size_t size)
{
    iteratorC it(argv, size);
    bool exit__ = false;

    __commnads_interns = {
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

    if (size < 2)
    {
        version(it);
    }
    else
    {
        it.next();
        while (it.get() != it.end())
        {
            Handle2 handle;
            if (!(handle = __commnads_interns[*it.get()]))
                throw std::runtime_error("No es una operacion del sistema");
            if (exit__ = handle(it))
                break;
            it.next();
        }
        if (!exit__)
        {
            is_all_ready();
            operation_active();
        }
    }
}