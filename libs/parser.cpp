#include <parser/parser.hpp>

std::map<std::string, Funtions> Parser::directives = {
    {"dir", Parser::syntax_dir_parser},
    {"generate", Parser::syntax_generate_parser},
    {"write", Parser::syntax_write_parser},
    {"\"", Parser::syntax_parser_string},
    {"[", Parser::syntax_operator_opencorch_parser},
    {"]", Parser::syntax_operator_closecorch_parser},
    {":", Parser::syntax_operator_twodot_parser},
    {"end", Parser::syntax_end_parser},
    {"exc", nullptr},
};
std::map<std::string, Ats::Base *> Parser::variables = {};

void Parser::initialize()
{
    Parser::variables = {
        {"TRUE", new Ats::Data(Ats::Data::Id::boolean, _TRUE)},
        {"FALSE", new Ats::Data(Ats::Data::Id::boolean, _FALSE)},
        {"FOLDER", new Ats::Data(Ats::Data::Id::boolean, _TRUE)},
        {"FILE", new Ats::Data(Ats::Data::Id::boolean, _FALSE)},
        {"WORKSPACES", new Ats::Data(Ats::Data::Id::url, sources_proyect.string())},
        {"PROJECT", new Ats::Data(Ats::Data::Id::str, name_proyect)},
        {"SOURCES", new Ats::Data(Ats::Data::Id::url, sources_configs.string())},
        {"PROGRAM", new Ats::Data(Ats::Data::Id::url, installed_program.string())},
        {"BEGIN", new Ats::Data(Ats::Data::Id::number, "0")},
        {"END", new Ats::Data(Ats::Data::Id::number, "-1")},
    };
}

Ats::Base *Parser::opeartion(Tokens &allocator, const std::vector<slfbp::token>::iterator &iterator)
{
    Funtions handle = directives[(*iterator)._atom.c_str()];
    Ats::Base *value = nullptr;
    if (handle != nullptr)
        return handle(allocator);
    return variables[(*iterator)._atom.c_str()];
}

void Parser::construction_ats_intern(Ats::Base *value, bool confirmation)
{
    Ats::Node *_value = new Ats::Node(value);
    if (confirmation)
        listactual.top()->push_back(_value);
    else
        actual->list()->push_back(_value);
    actual = _value;
}

Ats::Base *Parser::syntax_parser_string(Tokens &allocator)
{
    static size_t pos = 0;
    std::vector<slfbp::token>::iterator iterator;
    bool modo = false;
    pos = allocator.position(allocator.get());
    allocator.next();
    while ((iterator = allocator.get()) != allocator.end())
    {
        if ((*iterator).equals("\\", slfbp::token::id::symbol))
        {
            modo = true;
            allocator.next();
            continue;
        }
        if (!(*iterator).equals("\"", slfbp::token::id::symbol))
        {
            incomplete_str += (*iterator)._atom.c_str();
            allocator.next();
            continue;
        }
        if (modo)
        {
            incomplete_str += (*iterator)._atom.c_str();
        }
        else
        {
            Ats::Base *node = new Ats::Data(Ats::Data::Id::str, incomplete_str);
            incomplete_str.clear();
            return node;
        }
        allocator.next();
    }
    if (modo)
        throw sgp::exceptions("Error de Sintaxis: Fin incorrecto del generador de caracteres, no se cerraron las comillas dobles.", n_lines, pos, pos + 1, line);
    return nullptr;
}

void Parser::syntax_parametres_parser(Tokens &allocator, std::vector<Parametre> &destine, size_t &startparametres, size_t &endparametres)
{
    std::vector<slfbp::token>::iterator iterator;
    Parametre param;
    Parser::n_l_parentesis++;
    allocator.next();
    if ((iterator = allocator.get()) == allocator.end() || !iterator->equals("(", slfbp::token::id::symbol))
    {
        size_t pos = allocator.position(allocator.get());
        throw sgp::exceptions("Error de Sintaxis: La funcion debe seguir de () para ser llamada.", n_lines, pos - 1, pos, line);
    }
    startparametres = sstring::find_word(iterator->_atom.c_str(), line);
    allocator.next();
    while ((iterator = allocator.get()) != allocator.end())
    {
        if (iterator->equals(",", slfbp::token::id::symbol))
        {
            destine.push_back(param);
            allocator.next();
            continue;
        }
        if (iterator->equals(")", slfbp::token::id::symbol))
        {
            destine.push_back(param);
            Parser::n_l_parentesis--;
            break;
        }
        Ats::Base *result = Parser::opeartion(allocator, iterator);
        if (result == nullptr)
            throw sgp::exceptions("Error de Sintaxis: no es una operacion, variable o valor valido: " + std::string((*iterator)._atom.c_str()) + ".", n_lines, (*iterator)._atom.c_str(), line);
        size_t ini = sstring::find_word((*iterator)._atom.c_str(), line);
        param = Parametre(result, ini, sstring::find_word(allocator.get()->_atom.c_str(), line));
        allocator.next();
    }
    endparametres = sstring::find_word(iterator->_atom.c_str(), line);
}

Ats::Base *Parser::syntax_dir_parser(Tokens &allocator)
{
    /// Extrae los parametros para la funcion y tambien los valores de donde inicia y donde termina la seccion de parametros
    std::vector<Parametre> args;
    size_t ini, end;
    syntax_parametres_parser(allocator, args, ini, end);
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Identifica un mensaje de error en caso de que los parametrso sean superiores o menores a los requeridos
    if (args.size() < 1)
        throw sgp::exceptions("Error de Sintaxis: El numero de parametros insertados es menor que los que se requieren para que la funcion dir se ejecute. Parametros requeridos 1", n_lines, ini, end, line);
    if (args.size() > 1)
        throw sgp::exceptions("Error de Sintaxis: El numero de parametros insertados es mayor que los que se requieren para que la funcion dir se ejecute. Parametros requeridos 1", n_lines, ini, end, line);
    /// Convierte los valores a Ats::Data solo si el argumento tiene el id Ats::Id::data
    Ats::Data *__argcv;
    if (args[0].parametre()->ids() != Ats::Id::data)
        throw std::runtime_error("Error de Codigo Main: El valor de tipo de dato de Node::Base para el dato en el parametro 1 de dir no es valido.");
    else
        __argcv = static_cast<Ats::Data *>(args[0].parametre());
    /// Comprueba si el tipo de dato enviado es valido con el requerido
    if (__argcv->type() != Ats::Data::Id::str)
        throw sgp::exceptions("Error de Sintaxis: El tipo de dato del parametro debe ser un string en la funcion dir.", n_lines, args[0].start(), args[0].end(), line);
    /// Por ultimo generamos el Handle y agregamos los parametros
    Ats::Handle *result = new Ats::Handle(Ats::Handle::Id::_dir, trails<Ats::Base *>(1), 0, Parser::n_lines, 0, 0);
    result->argV()[0] = __argcv;
    return result;
}

Ats::Base *Parser::syntax_operator_twodot_parser(Tokens &allocator)
{
    return new Ats::Control(Ats::Control::Id::exceces_concatenation);
}

Ats::Base *Parser::syntax_operator_opencorch_parser(Tokens &allocator)
{
    listactual.push(actual->list());
    return new Ats::Control(Ats::Control::Id::open_multi_concatenation);
}
Ats::Base *Parser::syntax_operator_closecorch_parser(Tokens &allocator)
{
    listactual.pop();
    return new Ats::Control(Ats::Control::Id::close_multi_concatenation);
}

Ats::Base *Parser::syntax_end_parser(Tokens &allocator)
{
    return new Ats::Control(Ats::Control::Id::end_reader);
}

Ats::Base *Parser::syntax_generate_parser(Tokens &allocator)
{
    std::vector<Parametre> args;
    size_t ini, end;
    syntax_parametres_parser(allocator, args, ini, end);
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    if (args.size() < 2)
        throw sgp::exceptions("Error de Sintaxis: El numero de parametros insertados es menor que los que se requieren para que la funcion generate se ejecute. Parametros requeridos 2.", n_lines, ini, end, line);
    if (args.size() > 2)
        throw sgp::exceptions("Error de Sintaxis: El numero de parametros insertados es mayor que los que se requieren para que la funcion generate se ejecute. Parametros requeridos 2", n_lines, ini, end, line);
    Ats::Data *__argcv1, *__argcv2;
    if (args[0].parametre()->ids() != Ats::Id::data)
        throw std::runtime_error("Error de Codigo Main: El valor de tipo de dato de Node::Base para el dato en el parametro 1 de generate no es valido.");
    else
        __argcv1 = static_cast<Ats::Data *>(args[0].parametre());
    if (args[1].parametre()->ids() != Ats::Id::data)
        throw std::runtime_error("Error de Codigo Main: El valor de tipo de dato de Node::Base para el dato en el parametro 2 de generate no es valido.");
    else
        __argcv2 = static_cast<Ats::Data *>(args[1].parametre());
    /// Comprueba si el tipo de dato enviado es valido con el requerido
    if (__argcv1->type() != Ats::Data::Id::str)
        throw sgp::exceptions("Error de Sintaxis: El tipo de dato del parametro debe ser un string en la funcion generate.", n_lines, args[0].start(), args[0].end(), line);
    if (__argcv2->type() != Ats::Data::Id::boolean)
        throw sgp::exceptions("Error de Sintaxis: El tipo de dato del parametro debe ser un boelano en la funcion generate.", n_lines, args[1].start(), args[1].end(), line);
    /// Por ultimo generamos el Handle y agregamos los parametros
    Ats::Handle *result = new Ats::Handle(Ats::Handle::Id::_generate, trails<Ats::Base *>(2), 2, Parser::n_lines, 1, 0);
    result->argV()[0] = __argcv1;
    result->argV()[1] = __argcv2;
    return result;
}
Ats::Base *Parser::syntax_write_parser(Tokens &allocator)
{
    /// Extrae los parametros para la funcion y tambien los valores de donde inicia y donde termina la seccion de parametros
    std::vector<Parametre> args;
    size_t ini, end;
    syntax_parametres_parser(allocator, args, ini, end);
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Identifica un mensaje de error en caso de que los parametrso sean superiores o menores a los requeridos
    if (args.size() < 3)
        throw sgp::exceptions("Error de Sintaxis: El numero de parametros insertados es menor que los que se requieren para que la funcion dir se ejecute. Parametros requeridos 3", n_lines, ini, end, line);
    if (args.size() > 3)
        throw sgp::exceptions("Error de Sintaxis: El numero de parametros insertados es mayor que los que se requieren para que la funcion dir se ejecute. Parametros requeridos 3", n_lines, ini, end, line);
    /// Convierte los valores a Ats::Data solo si el argumento tiene el id Ats::Id::data
    Ats::Data *__argcv1, *__argcv2, *__argcv3;
    if (args[0].parametre()->ids() != Ats::Id::data)
        throw std::runtime_error("Error de Codigo Main: El valor de tipo de dato de Node::Base para el dato en el parametro 1 de write no es valido.");
    else
        __argcv1 = static_cast<Ats::Data *>(args[0].parametre());
    if (args[1].parametre()->ids() != Ats::Id::data)
        throw std::runtime_error("Error de Codigo Main: El valor de tipo de dato de Node::Base para el dato en el parametro 2 de write no es valido.");
    else
        __argcv2 = static_cast<Ats::Data *>(args[1].parametre());
    if (args[2].parametre()->ids() != Ats::Id::data)
        throw std::runtime_error("Error de Codigo Main: El valor de tipo de dato de Node::Base para el dato en el parametro 3 de write no es valido.");
    else
        __argcv3 = static_cast<Ats::Data *>(args[2].parametre());
    /// Comprueba si el tipo de dato enviado es valido con el requerido
    if (__argcv1->type() != Ats::Data::Id::number)
        throw sgp::exceptions("Error de Sintaxis: El tipo de dato del parametro debe ser un numero en la funcion write.", n_lines, args[0].start(), args[0].end(), line);
    if (__argcv2->type() != Ats::Data::Id::number)
        throw sgp::exceptions("Error de Sintaxis: El tipo de dato del parametro debe ser un numero en la funcion write.", n_lines, args[1].start(), args[1].end(), line);
    if (__argcv3->type() != Ats::Data::Id::str)
        throw sgp::exceptions("Error de Sintaxis: El tipo de dato del parametro debe ser una string en la funcion write.", n_lines, args[1].start(), args[1].end(), line);
    /// Por ultimo generamos el Handle y agregamos los parametros
    Ats::Handle *result = new Ats::Handle(Ats::Handle::Id::_write, trails<Ats::Base *>(3), 3, Parser::n_lines, 1, 0);
    result->argV()[0] = __argcv1;
    result->argV()[1] = __argcv2;
    result->argV()[2] = __argcv3;
    return result;
}

std::list<Ats::Node *> &Parser::parsing()
{
    std::vector<slfbp::token> tokens;
    Tokens allocator(tokens);
    tokens.reserve(256);
    // Guarda la direccion de la lista en una pila para generar las acciones
    listactual.push(&listmain);
    // Pucle principal
    while (!sources.iseof())
    {
        line = sources.get<std::string>();
        lex.tokenize(line, tokens);
        allocator.update();
        std::vector<slfbp::token>::iterator iterator;
        bool concatenation_permision = true;
        bool confirm_is_first_value = true;
        while ((iterator = allocator.get()) != allocator.end())
        {
            if (concatenation_permision)
            {
                Ats::Base *result = Parser::opeartion(allocator, iterator);
                if (result == nullptr)
                    throw sgp::exceptions("Error de Sintaxis: no es una operacion, variable o valor valido: " + std::string((*iterator)._atom.c_str()) + ".", n_lines, (*iterator)._atom.c_str(), line);
                concatenation_permision = false;

                if (result->ids() == Ats::Id::control)
                {
                    switch (static_cast<Ats::Control *>(result)->id())
                    {
                    case Ats::Control::Id::end_reader:
                        goto endreader;
                        break;
                    case Ats::Control::Id::exceces_concatenation:
                        throw sgp::exceptions("Error de Sintaxis: No se ha agregado una expresion entre las dos concatenaciones.", n_lines, (*iterator)._atom.c_str(), line);
                        break;
                    case Ats::Control::Id::open_multi_concatenation:
                        goto endoperatiopenandclose;
                        break;
                    case Ats::Control::Id::close_multi_concatenation:
                        goto endoperatiopenandclose;
                        break;
                    default:
                        break;
                    }
                }
                Parser::construction_ats_intern(result, confirm_is_first_value);
            }
            else
            {
                if (aperture_corchetes)
                    throw sgp::exceptions("Error de Sintaxis: Concatenacion de operaciones erronea, no puede existir nada despues de una apertura de corchetes.", n_lines, (*iterator)._atom.c_str(), line);
                if ((*iterator).equals(":", slfbp::token::id::symbol))
                    concatenation_permision = true;
                else
                    throw sgp::exceptions("Error de Sintaxis: Concatenacion de operaciones erronea, debe existir una separacion a traves de un ':'.", n_lines, (*iterator)._atom.c_str(), line);
            }
        endoperatiopenandclose:
            allocator.next();
            confirm_is_first_value = false;
        }
        allocator.reset();
        n_lines++;
        line.clear();
    }
endreader:
    if (!incomplete_str.empty())
        throw sgp::exceptions("Error de Sintaxis: No se cerraron las \"...\"", n_lines, "\"", line);
    if (n_l_corchetes != 0)
        throw sgp::exceptions("Error de Sintaxis: No se cerraron los [...]", n_lines, ")", line);
    return listmain;
}

void Parser::view(const AtsList &list, size_t level)
{
    for (auto &&i : list)
    {
        std::cout << "Lv: " << level << "-:";
        for (size_t j = 0; j < level; j++)
            std::cout << "-";
        i->value()->debug_view(level + 1);
        std::cout << std::endl;
        view(*(i->list()), level + 1);
    }
}

LabelT &Parser::resolve_references()
{
    while (!sources.iseof())
    {
        line = sources.get<std::string>();
        if (line.back() == '\r')
            line.pop_back();
        if (line[0] == '.' && line.back() == ':')
        {
            line.erase(line.begin());
            line.pop_back();
            u64 begin = sources.getpos();
            u64 end = null_caracter_end();
            labels.emplace(line, Label(begin, end, n_lines));
            sources.setpos(end, false);
        }
        line.clear();
    }
    return labels;
}

u64 Parser::null_caracter_end()
{
    std::string __line;
    u64 pos = 0;
    do
    {
        pos = sources.getpos();
        __line = sources.get<std::string>();
        n_lines++;
    } while (!__line.empty() && (__line[0] == ' ' || __line[0] == '\t'));
    return pos;
}