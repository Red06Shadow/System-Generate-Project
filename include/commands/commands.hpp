#include <script/script.hpp>

#ifndef COMMAND
#define COMMAND
class iteratorC
{
private:
    const char **__end;
    const char **__begin;
    const char **__ponit = nullptr;

public:
    iteratorC(const char *argv[], const size_t size) : __begin(argv), __ponit(argv), __end(argv + size) {}
    const char **get() { return __ponit; }
    void next() { __ponit++; }
    const char **end() { return __end; }
    const char **begin() { return __begin; }
};

typedef bool (*Handle2)(iteratorC &);

class Command
{
private:
    static std::map<std::string, Handle2> __commnads_interns;
    inline static systems::Url urld = filesystem::current_directory();
    inline static systems::Url urls;
    inline static const char *nameP = nullptr;
    inline static bool sourcesacpt = false;

public:
    static bool version(iteratorC &iterator);
    static bool help(iteratorC &iterator);
    static bool destine(iteratorC &iterator);
    static bool name(iteratorC &iterator);
    static bool format(iteratorC &iterator);
    static void is_all_ready();
    static void operation_active();
    static void comands(const char* argv[], size_t size);
};
// "C:/Proyectos(Red06Shadow)/SG-Proyects/test/c++_projects_cmake.sgc"
#endif