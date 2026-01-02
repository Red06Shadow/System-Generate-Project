#include <stda/numbers/typedefs.hpp>
#include <stda/trails/trails.hpp>
#include <list>

#ifndef NODES_BASE
#define NODES_BASE

namespace Ats
{
    enum class Id : u8
    {
        /// @brief Valores puros
        data,
        /// @brief Funcion interna del sistema
        hanlde,
        /// @brief Valor de control
        control,
        /// @brief Variables del sistema o de ususario
        variable,
        // @brief Funcion definida por el usuario
        funtion
    };

    class Base
    {
    protected:
        Id id;

    public:
        Base(Id _id) : id(_id) {}
        Id ids() { return id; }
        virtual void debug_view(u64 spaces)
        {
            std::cout << "This is node Base; Id:" << static_cast<u8>(id);
        }
        ~Base() {}
    };

    class Data : public Base
    {
    public:
        enum class Id : u8
        {
            number,
            str,
            url,
            boolean,
            labels
        };

    private:
        Ats::Data::Id data_id;
        std::string data;

    public:
        Data(Ats::Data::Id _data_id, const char *_data) : Base(Ats::Id::data), data_id(_data_id), data(_data) {}
        Data(Ats::Data::Id _data_id, const std::string &_data) : Base(Ats::Id::data), data_id(_data_id), data(_data) {}
        Ats::Data::Id type() { return data_id; }
        const std::string &value() { return data; }
        void debug_view(u64 spaces) override
        {
            std::cout << "This is node Data; Id:" << static_cast<u8>(id) << " Int code: " << (static_cast<int>(data_id)) << " Value: " << data;
        }
        ~Data() {}
    };

    class Control : public Base
    {
    public:
        enum class Id : u8
        {
            none,
            end_reader,
            exceces_concatenation,
            open_multi_concatenation,
            close_multi_concatenation
        };

    private:
        Id control_;

    public:
        Control(Id _control_) : Base(Ats::Id::control), control_(_control_) {}
        Id id() { return control_; }
        void debug_view(u64 spaces) override {}
        ~Control() {}
    };

    class Handle : public Base
    {
    public:
        enum class Id : u8
        {
            none,
            _dir,
            _generate,
            _write
        };

    private:
        const Handle::Id code;
        trails<Base *> argv_default;
        const u64 args_stack;

        static void espace_generate(u64 spaces)
        {
            for (size_t i = 0; i < spaces; i++)
                std::cout << ' ';
        }

        inline static std::string operations_debug[4] = {"none", "dir", "generate", "write"};

    public:
        const u64 n_line, n_pos, n_pos_end;
        Handle(const Handle::Id _code, const u64 _args_stack, const u64 _n_line, const u64 _n_pos, const u64 _n_pos_end) : Base(Ats::Id::hanlde), code(_code), argv_default(trails<Base *>()), args_stack(_args_stack), n_line(_n_line), n_pos(_n_pos), n_pos_end(_n_pos_end) {}
        Handle(const Handle::Id _code, const trails<Base *> &_argv_default, const u64 _args_stack, const u64 _n_line, const u64 _n_pos, const u64 _n_pos_end) : Base(Ats::Id::hanlde), code(_code), argv_default(_argv_default), args_stack(_args_stack), n_line(_n_line), n_pos(_n_pos), n_pos_end(_n_pos_end) {}

        Handle::Id get_code() const { return code; }
        bool is_valid() const { return code != Handle::Id::none; }
        bool is_have_params() const { return argv_default.size() != 0; }
        bool is_have_params_of_stack() const { return args_stack != 0; }
        trails<Base *> &argV() { return argv_default; }
        const u64 n_params() const { return argv_default.size(); }
        const u64 n_params_of_stack() const { return args_stack; }

        void debug_view(u64 spaces) override
        {
            std::cout << "This is node Handle; Id:" << static_cast<u8>(id) << std::endl;
            espace_generate(spaces);
            std::cout << ":--Code: " << operations_debug[static_cast<u8>(code)] << std::endl;
            espace_generate(spaces);
            std::cout << ":--Args: " << argv_default.size() << std::endl;
            espace_generate(spaces);
            std::cout << ":--Sargs: " << args_stack << std::endl;
            espace_generate(spaces);
            std::cout << ":--Line: " << n_line << std::endl;
            espace_generate(spaces);
            std::cout << ":--Pos_ini: " << n_pos << std::endl;
            espace_generate(spaces);
            std::cout << ":--Pos_end: " << n_pos_end;
        }
        ~Handle() {}
    };

    class Node
    {
    private:
        Base *element;
        std::list<Node *> concatenation;

    public:
        Node(Base *const _element) : element(_element) {}
        std::list<Node *> *list() { return &concatenation; }
        Base *value() { return element; }
    };
};

#endif