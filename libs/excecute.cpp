#include <excecute/excecute.hpp>

Funtion Excecute::operations[4] = {nullptr, Excecute::dir, Excecute::generate, Excecute::write};

Ats::Data *Excecute::operation(Ats::Base *node)
{
    if (node == nullptr)
        throw std::runtime_error("El puntero dentro de operation es nulo");
    switch (node->ids())
    {
    case Ats::Id::data:
        return static_cast<Ats::Data *>(node);
        break;
    case Ats::Id::hanlde:
    {
        Ats::Handle *self = static_cast<Ats::Handle *>(node);
        return operations[static_cast<u8>(self->get_code())](self);
    }
    break;
    default:
        return nullptr;
        break;
    }
}

void Excecute::excecute(const AtsList &handles, size_t level)
{
    for (auto &&i : handles)
    {
        Ats::Data *result = operation(i->value());
        if (!i->list()->empty())
        {
            stack_argv.push(result);
            excecute(*i->list(), level + 1);
            stack_argv.pop();
            // delete i->value();
        }
    }
}
void Excecute::set_labels(LabelT &_labels)
{
    labels = _labels;
}
void Excecute::error_cleaner()
{
    while (!operatios_stack.empty())
    {
        filesystem::remove(operatios_stack.top());
        operatios_stack.pop();
    }
}

Ats::Data *Excecute::dir(Ats::Handle *self)
{
    Ats::Data *arg;
    if ((arg = Excecute::operation(self->argV()[0]))->type() != Ats::Data::Id::str)
        throw sgp::exceptions("Error de Ejecucion: El parametro numero 1 de dir debe ser de tipo Url", 0, 0, 0, "");
    if (!filesystem::is_exist(arg->value()))
        throw sgp::exceptions("Error de Ejecucion: La ruta del archivo o directorio no existe", 0, 0, 0, "");
    return new Ats::Data(Ats::Data::Id::url, arg->value());
}

Ats::Data *Excecute::generate(Ats::Handle *self)
{
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    if (stack_argv.size() < 1)
        throw sgp::exceptions("Error de Ejecucion: El numero de parametros en pila de concatenacion para generate es menor que 1. Parametros requeridos 1", 0, 0, 0, "");
    Ats::Data *argstack;
    if ((argstack = stack_argv.top())->type() != Ats::Data::Id::url)
        throw sgp::exceptions("Error de Ejecucion: El de parametros en pila de concatenacion para generate debe ser de tipo Url", 0, 0, 0, "");
    systems::Url __sources = stack_argv.top()->value();
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Ats::Data *arg1;
    if ((arg1 = Excecute::operation(self->argV()[0]))->type() != Ats::Data::Id::str)
        throw sgp::exceptions("Error de Ejecucion: El parametro numero 1 de generate ser de tipo str", 0, 0, 0, "");
    std::string name = arg1->value();
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Ats::Data *arg2;
    if ((arg2 = Excecute::operation(self->argV()[1]))->type() != Ats::Data::Id::boolean)
        throw sgp::exceptions("Error de Ejecucion: El parametro numero 2 de generate ser de tipo boolean", 0, 0, 0, "");
    bool is_directory = (arg2->value() == _TRUE);
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    if (is_directory)
    {
        filesystem::create_directory(__sources, name, filesystem::options_for_create::overwrite, &__sources);
        operatios_stack.push(__sources);
    }
    else
    {
        filesystem::create_file(__sources, name, filesystem::options_for_create::overwrite, &__sources);
        operatios_stack.push(__sources);
    }
    std::cout << "\x1b[32m" << "Se ha generado el " << (is_directory ? "directorio" : "archivo") << ": " << __sources << "\033[m" << std::endl;
    return new Ats::Data(Ats::Data::Id::url, __sources.string());
}
Ats::Data *Excecute::write(Ats::Handle *self)
{
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    if (stack_argv.size() < 1)
        throw sgp::exceptions("Error de Ejecucion: El numero de parametros en pila de concatenacion para write es menor que 1. Parametros requeridos 1", 0, 0, 0, "");
    Ats::Data *argstack;
    if ((argstack = stack_argv.top())->type() != Ats::Data::Id::url)
        throw sgp::exceptions("Error de Ejecucion: El paramtro de pila de write debe ser un Url", 0, 0, 0, "");
    systems::Url __sources = stack_argv.top()->value();
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Ats::Data *arg1;
    if ((arg1 = Excecute::operation(self->argV()[0]))->type() != Ats::Data::Id::number)
        throw sgp::exceptions("Error de Ejecucion: El parametro numero 1 de write debe ser un valor entero", 0, 0, 0, "");
    const u64 begin = std::strtoull(arg1->value().c_str(), nullptr, 10);
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Ats::Data *arg2;
    if ((arg2 = Excecute::operation(self->argV()[1]))->type() != Ats::Data::Id::number)
        throw sgp::exceptions("Error de Ejecucion: El parametro numero 2 de write debe ser un valor entero", 0, 0, 0, "");
    const u64 end = std::strtoull(arg2->value().c_str(), nullptr, 10);
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Ats::Data *arg3;
    if ((arg3 = Excecute::operation(self->argV()[2]))->type() != Ats::Data::Id::str)
        throw sgp::exceptions("Error de Ejecucion: El parametro numero 3 de write debe ser una cadena de caracteres", 0, 0, 0, "");
    const std::string &__name = arg3->value();
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Label __label;
    if (!(__label = labels[__name]).defined)
        throw sgp::exceptions("Error de Ejecucion: No existe una etiqueta con el nombre de: " + __name, 0, 0, 0, "");
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    systems::ios::ofstream out = systems::ios::ofstream(__sources, true);
    out.setpos(begin, false);
    sources.setpos(__label.position_in_file, false);

    bool control = true;
    if (end == size_t(-1))
    {
        for (u64 i = __label.position_in_file; i < __label.n_caracters_reader && !sources.iseof(); i++)
        {
            char car;
            sources >> car;
            if (car == 0)
                break;
            if ((car != ' ' && car != '\t') && control)
                control = false;
            if (car == '\n')
                control = true;
            if (!control)
                out << car;
        }
    }
    else
    {
        for (u64 i = __label.position_in_file; i < end && i < __label.n_caracters_reader && !sources.iseof(); i++)
        {
            char car;
            sources >> car;
            if (car == 0)
                break;
            if ((car != ' ' && car != '\t') && control)
                control = false;
            if (car == '\n')
                control = true;
            if (!control)
                out << car;
        }
    }
    return nullptr;
}