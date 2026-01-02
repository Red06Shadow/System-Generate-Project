#include <global/global.hpp>
#include <stda/numbers/typedefs.hpp>
#include <stda/trails/trails.hpp>
#include <exceptions/exceptions.hpp>
#include <nodos/nodos.hpp>
#include <stack>

#ifndef STRUCTS
#define STRUCTS

typedef std::list<Ats::Node *> *ptr_list;

class Tokens
{
private:
    std::vector<slfbp::token> &reference_tokens;
    std::vector<slfbp::token>::iterator iterator;

public:
    Tokens(std::vector<slfbp::token> &tokens) : reference_tokens(tokens), iterator(tokens.begin()) {}
    const std::vector<slfbp::token>::iterator &get() const { return iterator; }
    void next() { iterator++; }
    void update() { iterator = reference_tokens.begin(); }
    const std::vector<slfbp::token>::iterator begin() const { return reference_tokens.begin(); }
    const std::vector<slfbp::token>::iterator end() const { return reference_tokens.end(); }
    size_t position(const std::vector<slfbp::token>::iterator &_iterator) { return _iterator - reference_tokens.begin(); }
    void reset() { reference_tokens.clear(); }
};

typedef Ats::Base *(*Funtions)(Tokens &allocator);

class Parametre
{
private:
    Ats::Base *atom;
    size_t pos_inicio;
    size_t pos_final;

public:
    Parametre() : atom(nullptr), pos_inicio(0), pos_final(0) {}
    Parametre(Ats::Base *const _atom, size_t _pos_inicio, size_t _pos_final) : atom(_atom), pos_inicio(_pos_inicio), pos_final(_pos_final) {}
    bool defined() { return atom != nullptr; }
    Ats::Base *parametre() { return atom; }
    size_t start() { return pos_inicio; }
    size_t end() { return pos_final; }
    ~Parametre() { atom = nullptr; }
};

class Label
{
public:
    bool defined;
    u64 position_in_file;
    u64 n_caracters_reader;
    u64 n_line_define;
    Label() : defined(false), position_in_file(0), n_caracters_reader(0), n_line_define(0) {}
    Label(u64 _position_in_file, u64 _n_caracters_reader, u64 _n_line_define) : defined(true), position_in_file(_position_in_file), n_caracters_reader(_n_caracters_reader), n_line_define(_n_line_define) {}
    ~Label() {}
};

typedef std::list<Ats::Node *> AtsList;
typedef std::map<std::string, Label> LabelT;
typedef std::vector<std::string> V_cheeck_write;

#endif