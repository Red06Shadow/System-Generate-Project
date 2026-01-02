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
    const char **get() { return __ponit; }
    void next() { __ponit++; }
    const char **end() { return __end; }
    const char **begin() { return __begin; }
};

typedef bool (*Handle)(Argv &);

class Command
{
private:
    static std::map<std::string, Handle> __commnads_interns;
    inline static bool sources_user = false;
    inline static bool destine_user = false;
    inline static bool name_user = false;

    static bool version(Argv &iterator);
    static bool create(Argv &iterator);
    static bool help(Argv &iterator);
    static bool destine(Argv &iterator);
    static bool name(Argv &iterator);
    static bool format(Argv &iterator);
    static void is_all_ready();


public:
    static bool excecute(const char* argv[], size_t size);
};
// "C:/Proyectos(Red06Shadow)/SG-Proyects/test/c++_projects_cmake.sgc"
#endif