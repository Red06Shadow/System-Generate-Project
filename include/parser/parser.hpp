#include <structs/structs.hpp>

/*Funciones primitivas
dir, generate, write, operators
*/

// Crear el ATS
// Definir variables, funciones y clases

#ifndef PARSER
#define PARSER

class Parser
{
private:
    inline static AtsList listmain = {};
    inline static std::stack<ptr_list> listactual = {};
    static std::map<std::string, Funtions> directives;
    inline static LabelT labels;
    static std::map<std::string, Ats::Base *> variables;
    inline static u64 n_lines = 1;
    inline static bool aperture_corchetes = false;
    inline static Ats::Node *actual = nullptr;
    inline static std::string incomplete_str = std::string();
    inline static u64 n_l_corchetes = 0, n_l_parentesis = 0;
    inline static std::string line = "\0";

    static Ats::Base *opeartion(Tokens &allocator, const std::vector<slfbp::token>::iterator &iterator);
    static void construction_ats_intern(Ats::Base *value, bool confirmation);
    static u64 null_caracter_end();

    static Ats::Base *syntax_parser_string(Tokens &allocator);
    static void syntax_parametres_parser(Tokens &allocator, std::vector<Parametre> &destine, size_t &startparametres, size_t &endparametres);
    static Ats::Base *syntax_dir_parser(Tokens &allocator);
    static Ats::Base *syntax_operator_twodot_parser(Tokens &allocator);
    static Ats::Base *syntax_operator_opencorch_parser(Tokens &allocator);
    static Ats::Base *syntax_operator_closecorch_parser(Tokens &allocator);
    static Ats::Base *syntax_generate_parser(Tokens &allocator);
    static Ats::Base *syntax_write_parser(Tokens &allocator);
    static Ats::Base *syntax_end_parser(Tokens &allocator);

public:
    static AtsList &parsing();
    static LabelT &resolve_references();
    static V_cheeck_write &returned_cheek();
    static void view(const AtsList &list, size_t level = 0);
    static void initialize();
};

#endif