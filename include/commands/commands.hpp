#include <global/global.hpp>
#include <excecute/excecute.hpp>
#include <parser/parser.hpp>
#include <stda/system/time/time.hpp>

#ifndef COMMAND
#define COMMAND
class Argv
{
private:
    const char **__end;
    const char **__begin;
    const char **__ponit = nullptr;

public:
    Argv(const char *argv[], const size_t size) : __begin(argv), __ponit(argv), __end(argv + size) {}
    const char **get() const { return __ponit; }
    void next() { __ponit++; }
    const char **end() const { return __end; }
    const char **begin() const { return __begin; }
};

class Command
{
public:
    enum class Id : u8
    {
        create,
        remove,
        none
    };
    typedef bool (*Handle)(Argv &, Command::Id id);

private:
    static std::map<std::string, Handle> commands;
    inline static bool sources_user = false;
    inline static bool destine_user = false;
    inline static bool name_user = false;
    inline static std::string commnads_names[static_cast<u8>(Id::none) + 1] = {"create", "remove", "SG-Project"};

    static bool version(Argv &iterator, Command::Id id);
    static bool help(Argv &iterator, Command::Id id);

    static bool create(Argv &iterator, Command::Id id);

    static bool create_proyect_folder(Argv &iterator, Command::Id id);
    static bool create_proyect_name(Argv &iterator, Command::Id id);
    static bool create_proyect_format(Argv &iterator, Command::Id id);

    static bool create_proyect_name_insert();
    static bool create_proyect_folder_insert();
    static bool create_proyect_format_insert(const Argv &iterator);

    static void cheeck_valid_command(const Argv &iterator, Command::Id id_inserted, Command::Id id_validate);
    static void help_command_not_next(bool is_help_command_insert);

public:
    static bool excecute(Argv& iterator);
};
// "C:/Proyectos(Red06Shadow)/SG-Proyects/test/c++_projects_cmake.sgc"
#endif