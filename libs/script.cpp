#include <script/script.hpp>

template <>
Value<systems::Url>::Value()
{
    value = systems::Url();
}

void Script::init(const systems::Url &url_file_config, const char *name, const systems::Url &url_workspaces)
{
    _url = url_file_config;
    _url2 = url_workspaces;
    _name = name;
    argsimportes.push(new Value<systems::Url>(url_workspaces.root(), Node::type::__url));
    sizestackcalled.push(1);
    in = systems::ios::ifstream(url_file_config, true);
    directives = {
        {"generate", Script::generate},
        {"dir", Script::dir},
        {"end", Script::end},
        {":", Script::operator_twodot},
        {"\"", Script::parseString},
        {"[", Script::operator_opencorch},
        {"]", Script::operator_closecorch},
        {"write", Script::write},
        {"PROJECT", [](Allocator &alloc) -> Node *
         {
             return new Value<std::string>(std::string(_name), Node::type::__str);
         }},
        {"BEGIN", [](Allocator &alloc) -> Node *
         {
             return new Value<size_t>(0ULL, Node::type::__int);
         }},
        {"END", [](Allocator &alloc) -> Node *
         {
             return new Value<size_t>(-1ULL, Node::type::__int);
         }},
        {"SOURCES", [](Allocator &alloc) -> Node *
         {
             return new Value<systems::Url>(_url, Node::type::__url);
         }},
        {"WORKSPACES", [](Allocator &alloc) -> Node *
         {
             return new Value<systems::Url>(_url2, Node::type::__url);
         }},
        {"USERWORKSPACES", [](Allocator &alloc) -> Node *
         {
             std::cout << argsimportes.top() << " : inserte la ruta donde se desea aplicar dicha accion >> ";
             std::string __str;
             std::getline(std::cin, __str);
             return new Value<systems::Url>(systems::Url(__str, true), Node::type::__url);
         }},
        {"__NOW__", [](Allocator &alloc) -> Node *
         {
             return new Value<long long>(systems::time::now(), Node::type::__int);
         }},
        {"NOW", [](Allocator &alloc) -> Node *
         {
             return new Value<std::string>(systems::time::time_point(systems::time::now()).to_string(), Node::type::__str);
         }},
        {"TRUE", [](Allocator &alloc) -> Node *
         {
             return new Value<bool>(true, Node::type::__bool);
         }},
        {"FALSE", [](Allocator &alloc) -> Node *
         {
             return new Value<bool>(false, Node::type::__bool);
         }}};
    directives["FILE"] = directives["FALSE"];
    directives["FOLDER"] = directives["TRUE"];
}

void Script::deletef(std::vector<Node *> &refdelete)
{
    for (auto &&i : refdelete)
    {
        if (i)
        {
            delete i;
            i = nullptr;
        }
    }
}

Node *Script::parseString(Allocator &allocator)
{
    std::vector<slfbp::token>::iterator iterator;
    bool modo = false;
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
            Node *node = new Value<std::string>(incomplete_str, Node::type::__str);
            incomplete_str.clear();
            return node;
        }
        allocator.next();
    }
    if (modo)
        throw std::runtime_error("Error: Fin incorrecto del generador de caracteres");
    return new Value<int>(1, Node::type::__control);
}

std::vector<Node *> Script::parametresParser(Allocator &allocator)
{
    std::vector<Node *> args;
    std::vector<slfbp::token>::iterator iterator;
    Node *node = nullptr;
    flagofnotendparenteis++;
    allocator.next();
    if ((iterator = allocator.get()) == allocator.end() || !iterator->equals("(", slfbp::token::id::symbol))
        throw std::runtime_error("Error: La funcion debe seguir de () para ser llamada");
    allocator.next();
    while ((iterator = allocator.get()) != allocator.end())
    {
        if (iterator->equals(",", slfbp::token::id::symbol))
        {
            args.push_back(node);
            node = nullptr;
            allocator.next();
            continue;
        }
        if (iterator->equals(")", slfbp::token::id::symbol))
        {
            args.push_back(node);
            node = nullptr;
            flagofnotendparenteis--;
            break;
        }
        Handle handle;
        if (!(handle = directives[(*iterator)._atom.c_str()]))
            throw std::runtime_error("Error: no es una operacion valoda: " + std::string((*iterator)._atom.c_str()));
        node = handle(allocator);
        allocator.next();
    }
    return args;
}

Node *Script::dir(Allocator &allocator)
{
    std::vector<Node *> args = parametresParser(allocator);
    if (args.size() != 1)
        throw std::runtime_error("Error: El numero de para metros permitidos es de 1 para la funcion dir");
    if (args[0]->_type != Node::type::__str)
        throw std::runtime_error("Error: El tipo de dato del parametro debe ser un string en la funcion dir");
    Node *returned = new Value<systems::Url>(static_cast<Value<std::string> *>(args[0])->get(), Node::type::__url);
    deletef(args);
    return returned;
}

Node *Script::operator_twodot(Allocator &allocator)
{
    if (flagofnotendparenteis)
        throw std::runtime_error("Error: No se puede usar el operador dentro de las llamadas a las funciones");
    return new Value<int>(1, Node::type::__control);
}
Node *Script::end(Allocator &allocator)
{
    return new Value<int>(4, Node::type::__control);
}
Node *Script::operator_opencorch(Allocator &allocator)
{

    lock_eliminate_satck = true;
    sizestackcalled.push(argsimportes.size());
    flagofnotendcorcht++;
    return new Value<int>(3, Node::type::__control);
}
Node *Script::operator_closecorch(Allocator &allocator)
{
    lock_eliminate_satck = false;
    if (!flagofnotendcorcht)
        throw std::runtime_error("Error: No se a abierto un corchete");
    flagofnotendcorcht--;
    sizestackcalled.pop();
    return new Value<int>(3, Node::type::__control);
}

Node *Script::generate(Allocator &allocator)
{
    std::vector<Node *> args = parametresParser(allocator);

    if (args.size() != 2)
        throw std::runtime_error("Error: El numero de para metros permitidos es de 2 para la funcion generate");

    if (args[0]->_type != Node::type::__str)
        throw std::runtime_error("Error: El tipo de dato del parametro 1 debe ser un string en la funcion generate");

    if (args[1]->_type != Node::type::__bool)
        throw std::runtime_error("Error: El tipo de dato del parametro 2 debe ser un booleano (true, false o algo que devuelva estos valores) en la funcion generate");

    if (argsimportes.empty())
        throw std::runtime_error("Error: No se ha insertado al stack la variable/s necesarias para la funcion generate");

    if (argsimportes.top()->_type != Node::type::__url)
        throw std::runtime_error("Error: El tipo de dato de la variable de pila necesaria debe ser una Url(Dieccion de archivo) en la funcion generate");

    systems::Url usl = static_cast<Value<systems::Url> *>(argsimportes.top())->get();

    if (static_cast<Value<bool> *>(args[1])->get())
        filesystem::create_directory(usl, static_cast<Value<std::string> *>(args[0])->get(), filesystem::options_for_create::overwrite, &usl);
    else
        filesystem::create_file(usl, static_cast<Value<std::string> *>(args[0])->get(), filesystem::options_for_create::overwrite, &usl);

    std::cout << "Se ha generador el " << (static_cast<Value<bool> *>(args[1])->get() ? "directorio" : "archivo") << ": " << usl << std::endl;

    Node *returned = new Value<systems::Url>(usl, Node::type::__url);
    deletef(args);
    return returned;
}

Node *Script::write(Allocator &allocator)
{
    std::vector<Node *> args = parametresParser(allocator);

    if (args.size() != 3)
        throw std::runtime_error("Error: El numero de para metros permitidos es de 3 para la funcion write");

    if (args[0]->_type != Node::type::__int)
        throw std::runtime_error("Error: El tipo de dato del parametro 1 debe ser un entero sin signo en la funcion write");

    if (args[1]->_type != Node::type::__int)
        throw std::runtime_error("Error: El tipo de dato del parametro 2 debe ser un entero sin signo o etiqueta en la funcion write");

    if (args[2]->_type != Node::type::__str)
        throw std::runtime_error("Error: El tipo de dato del parametro 3 debe ser un entero sin signo o etiqueta en la funcion write");

    if (argsimportes.empty())
        throw std::runtime_error("Error: No se ha insertado al stack la variable/s necesarias para la funcion write");

    if (argsimportes.top()->_type != Node::type::__url)
        throw std::runtime_error("Error: El tipo de dato de la variable de pila necesaria debe ser una Url(Dieccion de archivo) en la funcion write");

    statusWrite.emplace(static_cast<Value<std::string> *>(args[2])->get(), Status(static_cast<Value<systems::Url> *>(directives["SOURCES"](allocator))->get(), static_cast<Value<systems::Url> *>(argsimportes.top())->get(), static_cast<Value<size_t> *>(args[0])->get(), static_cast<Value<size_t> *>(args[1])->get()));
    deletef(args);
    return new Value<int>(2, Node::type::__control);
}

void Script::__intern_write(size_t start, const systems::Url &destine, size_t ini, size_t end)
{
    if (filesystem::is_directory(destine))
        throw std::runtime_error("Error: No se permiten directorios en write");
    systems::ios::ofstream out = systems::ios::ofstream(destine, true);
    in.setpos(start, false);
    out.setpos(ini, false);
    if (end == size_t(-1))
    {
        while (!in.iseof())
        {
            char v = '\0';
            in >> v;
            if (v == 0)
                break;
            out << v;
        }
    }
    else
    {
        for (size_t i = 0; i < end && !in.iseof(); i++)
        {
            char v = '\0';
            in >> v;
            if (v == 0)
                break;
            out << v;
        }
    }
}

bool Script::__intern_operation_main()
{
    std::vector<slfbp::token> tokens;
    tokens.reserve(256);
    Allocator allocator(tokens);
    while (!in.iseof())
    {
        std::string line;
        in >> line;
        lex.tokenize(line, tokens);
        // lex.view(tokens);
        allocator.start();
        //////////////////////
        std::vector<slfbp::token>::iterator iterator;
        bool access_to_next_operation = true;
        while ((iterator = allocator.get()) != allocator.end())
        {
            if (access_to_next_operation)
            {
                Handle handle;
                if (!(handle = directives[(*iterator)._atom.c_str()]))
                    throw std::runtime_error("Error: no es una operacion valoda: " + std::string((*iterator)._atom.c_str()));
                Node *control = handle(allocator);
                if (control->_type == Node::type::__control)
                {
                    switch (static_cast<Value<int> *>(control)->get())
                    {
                    case 1:
                        throw std::runtime_error("Error: No se ha agregado una expresion entre las dos concatenaciones.");
                        break;
                    case 4:
                        goto endoperationsmaster;
                        break;
                    default:
                        break;
                    }
                }
                else
                {
                    access_to_next_operation = false;
                    argsimportes.push(control);
                }
            }
            else
            {
                if ((*iterator).equals(":", slfbp::token::id::symbol))
                    access_to_next_operation = true;
                else
                    throw std::runtime_error("Error: Concatenacion de operaciones erronea, debe existir una separacion a traves de un ':'");
            }
            allocator.next();
        }
        //////////////////////
        allocator.reset();
        while (argsimportes.size() > sizestackcalled.top())
            argsimportes.pop();
    }
    endoperationsmaster:
    if (!incomplete_str.empty())
        throw std::runtime_error("Error: No se cerraron las \"...\"");
    if (flagofnotendparenteis)
        throw std::runtime_error("Error: No se cerraron los (...)");
    return false;
}

bool Script::excecute()
{
    __intern_operation_main();
    while (!in.iseof())
    {
        std::string line;
        in >> line;
        if (line.back() == '\r') line.pop_back();
        if (line[0] == '.' && line.back() == ':')
        {
            line.erase(line.begin());
            line.pop_back();
            Status sts;
            if ((sts = statusWrite[line]).defineded_)
            {
                __intern_write(in.getpos(), sts.geturldestine(), sts.getstart(), sts.getn_caracters());
                statusWrite.erase(line);
            }
        }
        else
        {
            break;
        }
    }
    return true;
}
systems::ios::ifstream Script::in;
