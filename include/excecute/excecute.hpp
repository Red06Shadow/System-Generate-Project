#include <structs/structs.hpp>

#ifndef EXCECUTEALGORITM
#define EXCECUTEALGORITM

typedef Ats::Data *(*Funtion)(Ats::Handle *self);

#define NF_BASE

class Excecute
{
private:
    static Ats::Data *operation(Ats::Base *node);
    static Funtion operations[4];
    inline static std::stack<Ats::Data *> stack_argv = {};
    inline static std::stack<systems::Url> operatios_stack = {};
    inline static LabelT labels = {};

    static Ats::Data *dir(Ats::Handle *self);
    static Ats::Data *generate(Ats::Handle *self);
    static Ats::Data *write(Ats::Handle *self);

public:
    /////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////
    static void excecute(const AtsList &handles, size_t level);
    static void set_labels(LabelT &_labels);
    static void error_cleaner();
};

#endif