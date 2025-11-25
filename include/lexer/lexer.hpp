#include <stda/sstrings/sstrings.hpp>
#include <stda/numbers/typedefs.hpp>
#include <stda/typedef/typedef.hpp>
#include <map>

#ifndef LEXER_SLFBP
#define LEXER_SLFBP

#define ARGDEFAULT {"#", "(", ")", "[", "]", "{", "}", ".", "->", "++", "--", "!", "*", "/", "%", "+", "-", "<<", ">>", "<", ">", "<=", ">=", "==", "!=", "&", "^", "|", "&&", "||", "?", ":", "=", "+=", "-=", "*=", "/=", "&=", "|=", "^=", "<<=", ">>=", "%=", ","}

namespace slfbp
{

    class token
    {
    public:
        enum class id : u8
        {
            none,
            word,
            symbol
        };
        token::id _id;
        stringbuffer _atom;
        token() : _atom(), _id(token::id::none) {}
        token(const char *atom, token::id id) : _atom(atom), _id(id) {}
        token(const char *atom, size_t size, token::id id) : _atom(atom, size), _id(id) {}
        bool equals(const char *atom, token::id id)
        {
            if (id != _id)
                return false;
            return _atom == atom;
        }
        ~token() {}
    };
    inline bool operator==(token::id lhs, u8 rhs)
    {
        return static_cast<u8>(lhs) == rhs;
    }
    inline bool operator!=(token::id lhs, u8 rhs)
    {
        return static_cast<u8>(lhs) == rhs;
    }
    inline u8 operator*(token::id lhs)
    {
        return static_cast<u8>(lhs);
    }
    class lexer
    {
    private:
        std::map<std::string, bool> symbols_reference;
        void add(std::string &str, slfbp::token::id type, std::vector<slfbp::token> &alloc);

    public:
        lexer(std::initializer_list<const char *> args_symbols = ARGDEFAULT);
        void tokenize(const std::string &str, std::vector<slfbp::token> &alloc);
        bool issymbol(const std::string &symbol);
        void view(const std::vector<slfbp::token> &alloc);
        ~lexer() {}
    };
}

#endif