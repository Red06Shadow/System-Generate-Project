#include <stda/system/files/filesystem.hpp>
#include <stda/numbers/typedefs.hpp>
#include <stda/typedef/typedef.hpp>
#include <stda/sstrings/sstrings.hpp>
#include <stda/system/time/time.hpp>
#include <lexer/lexer.hpp>
#include <stack>
#include <map>

#ifndef SRCIPT
#define SRCIPT

class Node
{
public:
    enum class type : u8
    {
        __none,
        __str,
        __int,
        __bool,
        __url,
        __file,
        __label,
        __control
    };
    type _type;
    Node() : _type(Node::type::__none) {}
    Node(Node::type __type) : _type(__type) {}
    virtual ~Node() = default;
};
template <typename T>
class Value : public Node
{
private:
    T value = T();

public:
    Value() : value(T()) {}
    Value(const T &_value, Node::type __type) : value(_value), Node(__type) {}
    T &get()
    {
        return value;
    }
    ~Value() override {}
};

class Allocator
{
private:
    std::vector<slfbp::token>::iterator it;

public:
    std::vector<slfbp::token> &alloc;
    Allocator(std::vector<slfbp::token> &tokens) : alloc(tokens) {}
    void start() { it = alloc.begin(); }
    const std::vector<slfbp::token>::iterator get() { return it; }
    void next() { it++; }
    const std::vector<slfbp::token>::iterator end() { return alloc.end(); }
    bool isend(const std::vector<slfbp::token>::iterator &_it) { return _it == alloc.end(); }
    void reset() { alloc.clear(); }
};

typedef Node *(*Handle)(Allocator &allocator);

class Status
{
private:
    systems::Url urldestine;
    size_t posInit;
    size_t n_caracters;
public:
    bool defineded_;
    Status() : urldestine(), posInit(0), n_caracters(0), defineded_(false) {}
    Status(const systems::Url& _urlsources, const systems::Url& _urldestine, size_t _posInit, size_t _n_caracters) : posInit(_posInit), n_caracters(_n_caracters), defineded_(true) {
        urldestine = _urldestine;
    }
    Status(const Status& other) {
        if(this != &other) {
            if(other.defineded_)
            {
                this->urldestine = other.urldestine;
                this->posInit = other.posInit;
                this->n_caracters = other.n_caracters;
            }
            this->defineded_ = other.defineded_;
        }
    }
    Status(Status&& other) {
        if(this != &other) {
            if(other.defineded_)
            {
                this->urldestine = other.urldestine;
                this->posInit = other.posInit;
                this->n_caracters = other.n_caracters;
            }
            this->defineded_ = other.defineded_;
        }
    }
    Status operator=(const Status& other) {
        if(this != &other) {
            if(other.defineded_)
            {
                this->urldestine = other.urldestine;
                this->posInit = other.posInit;
                this->n_caracters = other.n_caracters;
            }
            this->defineded_ = other.defineded_;
        }
        return *this;
    }
    Status operator=(Status&& other) {
        if(this != &other) {
            if(other.defineded_)
            {
                this->urldestine = other.urldestine;
                this->posInit = other.posInit;
                this->n_caracters = other.n_caracters;
            }
            this->defineded_ = other.defineded_;
        }
        return *this;
    }
    size_t getstart() {return posInit;}
    size_t getn_caracters() {return n_caracters;}
    const systems::Url& geturldestine() {return urldestine;}
    ~Status() {}
};

class Script
{
private:
    static systems::ios::ifstream in;
    inline static std::string incomplete_str = "\0";
    inline static slfbp::lexer lex = slfbp::lexer({"@", ":", "[", "]", "(", ")", ","});
    inline static size_t flagofnotendparenteis = 0;
    inline static size_t flagofnotendcorcht = 0;
    inline static std::stack<Node *> argsimportes = {};
    inline static std::stack<size_t> sizestackcalled = {};
    inline static std::map<std::string, Handle> directives = {};
    inline static std::map<std::string, Status> statusWrite = {};
    inline static bool lock_eliminate_satck = false;
    inline static systems::Url _url;
    inline static systems::Url _url2;
    inline static const char* _name;

    static void deletef(std::vector<Node *> &refdelete);
    static Node *parseString(Allocator &allocator);
    static std::vector<Node *> parametresParser(Allocator &allocator);
    static Node *dir(Allocator &allocator);
    static Node *operator_twodot(Allocator &allocator);
    static Node *operator_opencorch(Allocator &allocator);
    static Node *operator_closecorch(Allocator &allocator);
    static Node *generate(Allocator &allocator);
    static Node *write(Allocator &allocator);
    static Node *end(Allocator &allocator);
    static void __intern_write(size_t start, const systems::Url &destine, size_t ini, size_t end);
    static bool __intern_operation_main();

public:
    static void init(const systems::Url &url_file_config, const char* name, const systems::Url &url_workspaces);
    static bool excecute();
};

#endif