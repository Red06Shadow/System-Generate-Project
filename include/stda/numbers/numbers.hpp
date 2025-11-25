#include <iostream>
#include <stda/sstrings/stringbuffer.hpp>
#include <stda/numbers/typedefs.hpp>

#ifndef HEXADECIMALS
#define HEXADECIMALS

/* @Documentacion:
 * Este archivo crea clases para manejar numeros de 8 bits hasta de 128bits... 
 * Proximamente se espera crear para valores de 256, 512 o de numeros infinitos a base de vectores
 * Tambien cuenta con funciones para generar cadenas de bit y hexadecimales
 */

namespace numbers
{
    /// @brief Estructura pa almacenar bits por separado de la clase byte
    struct Bits
    {
        u8 bit0 : 1;
        u8 bit1 : 1;
        u8 bit2 : 1;
        u8 bit3 : 1;
        u8 bit4 : 1;
        u8 bit5 : 1;
        u8 bit6 : 1;
        u8 bit7 : 1;
    };
    /// @brief Clase para el manejo de valores de 8bits
    class byte
    {
    private:
        u8 __value__;

    public:
        /// @brief Constructor por defecto
        byte() : __value__(0) {}
        /// @brief Constructor con valor de inicializacion uint8_t
        /// @param data Parametro de inicializacion
        byte(u8 data) : __value__(data) {}
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Funcion para obtener el valor de dicho objecto en base a int8_t
        /// @return Retorna el elemento en int8_t
        i8 value_signed() { return __value__; }
        /// @brief Funcion para obtener el valor de dicho objecto en base a uint8_t
        /// @return Retorna el elemento en uint8_t
        u8 value_unsigned() { return __value__; }
        /// @brief Funcion statica para obtener el valor de dicho objecto en base a int8_t
        /// @param __v Objecto de tipo byte
        /// @return Retorna el elemento en int8_t
        static i8 value_signed(byte __v) { return __v.__value__; }
        /// @brief Funcion statica para obtener el valor de dicho objecto en base a uint8_t
        /// @param __v Objecto de tipo byte
        /// @return Retorna el elemento en uint8_t
        static u8 value_unsigned(byte __v) { return __v.__value__; }

        /// @brief Funcion para obtener una referencia del vaor interno en base int8_t
        /// @return Retorna la referencia del int8_t
        i8 &reference_signed() { return (i8 &)__value__; }
        /// @brief Funcion para obtener una referencia del vaor interno en base uint8_t
        /// @return Retorna la referencia del uint8_t
        u8 &reference_unsigned() { return __value__; }
        /// @brief Funcion para obtener una referencia del vaor interno en base int8_t
        /// @param __v Referencia del objecto de tipo byte
        /// @return Retorna la referencia del int8_t
        static i8 &reference_signed(byte &__v) { return (i8 &)__v.__value__; }
        /// @brief Funcion para obtener una referencia del vaor interno en base uint8_t
        /// @param __v Referencia del objecto de tipo byte
        /// @return Retorna la referencia del uint8_t
        static u8 &reference_unsigned(byte &__v) { return __v.__value__; }

        /// @brief Obtiene los bist del valor de byte
        /// @param _bits Referencia a un elemento
        void bits(Bits &_bits)
        {
            _bits.bit7 = __value__ & (u8)(0b10000000);
            _bits.bit6 = __value__ & (u8)(0b01000000);
            _bits.bit5 = __value__ & (u8)(0b00100000);
            _bits.bit4 = __value__ & (u8)(0b00010000);
            _bits.bit3 = __value__ & (u8)(0b00001000);
            _bits.bit2 = __value__ & (u8)(0b00000100);
            _bits.bit1 = __value__ & (u8)(0b00000010);
            _bits.bit0 = __value__ & (u8)(0b00000001);
        }
        /// @brief Obtiene los bist del valor de byte
        /// @param _byte Calse byte para la cual se aplica
        /// @param _bits Referencia a un elemento
        static void bits(byte _byte, Bits &_bits)
        {
            _bits.bit7 = _byte.__value__ & (u8)(0b10000000);
            _bits.bit6 = _byte.__value__ & (u8)(0b01000000);
            _bits.bit5 = _byte.__value__ & (u8)(0b00100000);
            _bits.bit4 = _byte.__value__ & (u8)(0b00010000);
            _bits.bit3 = _byte.__value__ & (u8)(0b00001000);
            _bits.bit2 = _byte.__value__ & (u8)(0b00000100);
            _bits.bit1 = _byte.__value__ & (u8)(0b00000010);
            _bits.bit0 = _byte.__value__ & (u8)(0b00000001);
        }
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////
        friend byte operator+(byte _byte, byte _byte2) { return (u8)(_byte.value_unsigned() + _byte2.value_unsigned()); }
        friend byte operator+(byte _byte, i8 value2) { return (i8)(_byte.value_signed() + value2); }
        friend byte operator+(byte _byte, u8 value2) { return (u8)(_byte.value_unsigned() + value2); }
        friend byte operator+(i8 value2, byte _byte) { return (i8)(value2 + _byte.value_signed()); }
        friend byte operator+(u8 value2, byte _byte) { return (u8)(value2 + _byte.value_unsigned()); }
        friend byte operator+(byte _byte, int value2) { return (i8)(_byte.value_signed() + (i8)value2); }
        byte operator+=(int value2);
        byte operator+=(i8 value2);
        byte operator+=(u8 value2);
        byte operator+=(byte _byte2);
        friend byte operator-(byte _byte, byte _byte2) { return (u8)(_byte.value_unsigned() - _byte2.value_unsigned()); }
        friend byte operator-(byte _byte, i8 value2) { return (i8)(_byte.value_signed() - value2); }
        friend byte operator-(byte _byte, u8 value2) { return (u8)(_byte.value_unsigned() - value2); }
        friend byte operator-(i8 value2, byte _byte) { return (i8)(value2 - _byte.value_signed()); }
        friend byte operator-(u8 value2, byte _byte) { return (u8)(value2 - _byte.value_unsigned()); }
        friend byte operator-(byte _byte, int value2) { return (i8)(_byte.value_signed() - (i8)value2); }
        byte operator-=(int value2);
        byte operator-=(i8 value2);
        byte operator-=(u8 value2);
        byte operator-=(byte _byte2);
        friend byte operator*(byte _byte, byte _byte2) { return (u8)(_byte.value_unsigned() * _byte2.value_unsigned()); }
        friend byte operator*(byte _byte, i8 value2) { return (i8)(_byte.value_signed() * value2); }
        friend byte operator*(byte _byte, u8 value2) { return (u8)(_byte.value_unsigned() * value2); }
        friend byte operator*(i8 value2, byte _byte) { return (i8)(value2 * _byte.value_signed()); }
        friend byte operator*(u8 value2, byte _byte) { return (u8)(value2 * _byte.value_unsigned()); }
        friend byte operator*(byte _byte, int value2) { return (i8)(_byte.value_signed() * (i8)value2); }
        byte operator*=(int value2);
        byte operator*=(i8 value2);
        byte operator*=(u8 value2);
        byte operator*=(byte _byte2);
        friend byte operator/(byte _byte, byte _byte2) { return (u8)(_byte.value_unsigned() / _byte2.value_unsigned()); }
        friend byte operator/(byte _byte, i8 value2) { return (i8)(_byte.value_signed() / value2); }
        friend byte operator/(byte _byte, u8 value2) { return (u8)(_byte.value_unsigned() / value2); }
        friend byte operator/(i8 value2, byte _byte) { return (i8)(value2 / _byte.value_signed()); }
        friend byte operator/(u8 value2, byte _byte) { return (u8)(value2 / _byte.value_unsigned()); }
        friend byte operator/(byte _byte, int value2) { return (i8)(_byte.value_signed() / (i8)value2); }
        byte operator/=(int value2);
        byte operator/=(i8 value2);
        byte operator/=(u8 value2);
        byte operator/=(byte _byte2);
        friend byte operator%(byte _byte, byte _byte2) { return (u8)(_byte.value_unsigned() % _byte2.value_unsigned()); }
        friend byte operator%(byte _byte, i8 value2) { return (i8)(_byte.value_signed() % value2); }
        friend byte operator%(byte _byte, u8 value2) { return (u8)(_byte.value_unsigned() % value2); }
        friend byte operator%(i8 value2, byte _byte) { return (i8)(value2 % _byte.value_signed()); }
        friend byte operator%(u8 value2, byte _byte) { return (u8)(value2 % _byte.value_unsigned()); }
        friend byte operator%(byte _byte, int value2) { return (i8)(_byte.value_signed() % (i8)value2); }
        byte operator%=(int value2);
        byte operator%=(i8 value2);
        byte operator%=(u8 value2);
        byte operator%=(byte _byte2);
        friend byte operator&(byte _byte, byte _byte2) { return _byte.value_unsigned() & _byte2.value_unsigned(); }
        friend byte operator&(byte _byte, u8 value2) { return _byte.value_unsigned() & value2; }
        friend byte operator&(u8 value2, byte _byte) { return value2 & _byte.value_unsigned(); }
        byte operator&=(u8 value2);
        byte operator&=(byte _byte2);
        friend byte operator|(byte _byte, byte _byte2) { return _byte.value_unsigned() | _byte2.value_unsigned(); }
        friend byte operator|(byte _byte, u8 value2) { return _byte.value_unsigned() | value2; }
        friend byte operator|(u8 value2, byte _byte) { return value2 | _byte.value_unsigned(); }
        byte operator|=(u8 value2);
        byte operator|=(byte _byte2);
        friend byte operator^(byte _byte, byte _byte2) { return _byte.value_unsigned() ^ _byte2.value_unsigned(); }
        friend byte operator^(byte _byte, u8 value2) { return _byte.value_unsigned() ^ value2; }
        friend byte operator^(u8 value2, byte _byte) { return value2 ^ _byte.value_unsigned(); }
        byte operator^=(u8 value2);
        byte operator^=(byte _byte2);
        byte operator~() { return ~this->value_unsigned(); }
        friend byte operator>>(byte _byte, u8 value2) { return _byte.value_unsigned() >> value2; }
        friend byte operator<<(byte _byte, u8 value2) { return _byte.value_unsigned() << value2; }
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool operator==(byte v);
        bool operator==(u8 v);
        bool operator==(i8 v);
        bool operator==(int v);
        bool operator!=(byte v);
        bool operator!=(u8 v);
        bool operator!=(i8 v);
        bool operator!=(int v);
        bool operator<(byte v);
        bool operator<(u8 v);
        bool operator<(i8 v);
        bool operator<(int v);
        bool operator>(byte v);
        bool operator>(u8 v);
        bool operator>(i8 v);
        bool operator>(int v);
        bool operator>=(byte v);
        bool operator>=(u8 v);
        bool operator>=(i8 v);
        bool operator>=(int v);
        bool operator<=(byte v);
        bool operator<=(u8 v);
        bool operator<=(i8 v);
        bool operator<=(int v);
        bool operator&&(byte v);
        bool operator&&(u8 v);
        bool operator&&(i8 v);
        bool operator&&(int v);
        bool operator||(byte v);
        bool operator||(u8 v);
        bool operator||(i8 v);
        bool operator||(int v);
        bool operator!();
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////
        friend std::ostream &operator<<(std::ostream &os, byte v)
        {
            os << v.value_unsigned();
            return os;
        }
        friend std::istream &operator<<(std::istream &is, byte v)
        {
            is >> v.reference_unsigned();
            return is;
        }
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////
        byte operator++();
        byte operator--();
        byte operator++(int);
        byte operator--(int);
    };
    class word
    {
    private:
        byte __low__;
        byte __high__;

    public:
        /// @brief Constructor por defecto
        word() { (*(u16 *)(this)) = 0; }
        /// @brief Constructor con valor de inicializacion uint16_t
        /// @param data Parametro de inicializacion
        word(u16 data) { (*(u16 *)(this)) = data; }
        /// @brief Constructor con valor de inicializacion uint16_t
        /// @param low uint16_t de la parte baja del numero
        /// @param low uint16_t de la parte alta del numero
        word(u8 low, u8 high) : __low__(low), __high__(high) {}
        /// @brief Constructor con valor de inicializacion byte
        /// @param low byte de la parte baja del numero
        /// @param low byte de la parte alta del numero
        word(byte low, byte high) : __low__(low), __high__(high) {}
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Funcion para obtener el valor de dicho objecto en base a int16_t
        /// @return Retorna el elemento en int16_t
        i16 value_signed() { return (*(u16 *)(this)); }
        /// @brief Funcion para obtener el valor de dicho objecto en base a uint16_t
        /// @return Retorna el elemento en uint16_t
        u16 value_unsigned() { return (*(u16 *)(this)); }
        /// @brief Funcion statica para obtener el valor de dicho objecto en base a int16_t
        /// @param __v Objecto de tipo word
        /// @return Retorna el elemento en int16_t
        static i16 value_signed(word __v) { return (*(u16 *)(&__v)); }
        /// @brief Funcion statica para obtener el valor de dicho objecto en base a uint16_t
        /// @param __v Objecto de tipo word
        /// @return Retorna el elemento en uint16_t
        static u16 value_unsigned(word __v) { return (*(u16 *)(&__v)); }

        /// @brief Funcion para obtener una referencia del vaor interno en base int16_t
        /// @return Retorna la referencia del int16_t
        i16 &reference_signed() { return (i16 &)(*(u16 *)(this)); }
        /// @brief Funcion para obtener una referencia del vaor interno en base uint16_t
        /// @return Retorna la referencia del uint16_t
        u16 &reference_unsigned() { return (*(u16 *)(this)); }
        /// @brief Funcion para obtener una referencia del vaor interno en base int16_t
        /// @param __v Referencia del objecto de tipo word
        /// @return Retorna la referencia del int16_t
        static i16 &reference_signed(word &__v) { return (i16 &)(*(u16 *)(&__v)); }
        /// @brief Funcion para obtener una referencia del vaor interno en base uint16_t
        /// @param __v Referencia del objecto de tipo word
        /// @return Retorna la referencia del uint16_t
        static u16 &reference_unsigned(word &__v) { return (*(u16 *)(&__v)); }

        /// @brief Obtiene los bist del valor de word
        /// @param _bits Referencia a un elemento
        void bits(Bits &_low, Bits &_high)
        {
            __low__.bits(_low);
            __high__.bits(_high);
        }
        /// @brief Obtiene los bist del valor de byte
        /// @param _byte Calse byte para la cual se aplica
        /// @param _bits Referencia a un elemento
        static void bits(word _word, Bits &_low, Bits &_high)
        {
            _word.__low__.bits(_low);
            _word.__high__.bits(_high);
        }
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////
        friend word operator+(word _word, word _word2) { return (u16)(_word.value_unsigned() + _word2.value_unsigned()); }
        friend word operator+(word _word, i16 value2) { return (i16)(_word.value_signed() + value2); }
        friend word operator+(word _word, u16 value2) { return (u16)(_word.value_unsigned() + value2); }
        friend word operator+(i16 value2, word _word) { return (i16)(value2 + _word.value_signed()); }
        friend word operator+(u16 value2, word _word) { return (u16)(value2 + _word.value_unsigned()); }
        friend word operator+(word _word, int value2) { return (i16)(_word.value_signed() + (i16)value2); }
        word operator+=(int value2);
        word operator+=(i16 value2);
        word operator+=(u16 value2);
        word operator+=(word _word2);
        friend word operator-(word _word, word _word2) { return (u16)(_word.value_unsigned() - _word2.value_unsigned()); }
        friend word operator-(word _word, i16 value2) { return (i16)(_word.value_signed() - value2); }
        friend word operator-(word _word, u16 value2) { return (u16)(_word.value_unsigned() - value2); }
        friend word operator-(i16 value2, word _word) { return (i16)(value2 - _word.value_signed()); }
        friend word operator-(u16 value2, word _word) { return (u16)(value2 - _word.value_unsigned()); }
        friend word operator-(word _word, int value2) { return (i16)(_word.value_signed() - (i16)value2); }
        word operator-=(int value2);
        word operator-=(i16 value2);
        word operator-=(u16 value2);
        word operator-=(word _word2);
        friend word operator*(word _word, word _word2) { return (u16)(_word.value_unsigned() * _word2.value_unsigned()); }
        friend word operator*(word _word, i16 value2) { return (i16)(_word.value_signed() * value2); }
        friend word operator*(word _word, u16 value2) { return (u16)(_word.value_unsigned() * value2); }
        friend word operator*(i16 value2, word _word) { return (i16)(value2 * _word.value_signed()); }
        friend word operator*(u16 value2, word _word) { return (u16)(value2 * _word.value_unsigned()); }
        friend word operator*(word _word, int value2) { return (i16)(_word.value_signed() * (i16)value2); }
        word operator*=(int value2);
        word operator*=(i16 value2);
        word operator*=(u16 value2);
        word operator*=(word _word2);
        friend word operator/(word _word, word _word2) { return (u16)(_word.value_unsigned() / _word2.value_unsigned()); }
        friend word operator/(word _word, i16 value2) { return (i16)(_word.value_signed() / value2); }
        friend word operator/(word _word, u16 value2) { return (u16)(_word.value_unsigned() / value2); }
        friend word operator/(i16 value2, word _word) { return (i16)(value2 / _word.value_signed()); }
        friend word operator/(u16 value2, word _word) { return (u16)(value2 / _word.value_unsigned()); }
        friend word operator/(word _word, int value2) { return (i16)(_word.value_signed() / (i16)value2); }
        word operator/=(int value2);
        word operator/=(i16 value2);
        word operator/=(u16 value2);
        word operator/=(word _word2);
        friend word operator%(word _word, word _word2) { return (u16)(_word.value_unsigned() % _word2.value_unsigned()); }
        friend word operator%(word _word, i16 value2) { return (i16)(_word.value_signed() % value2); }
        friend word operator%(word _word, u16 value2) { return (u16)(_word.value_unsigned() % value2); }
        friend word operator%(i16 value2, word _word) { return (i16)(value2 % _word.value_signed()); }
        friend word operator%(u16 value2, word _word) { return (u16)(value2 % _word.value_unsigned()); }
        friend word operator%(word _word, int value2) { return (i16)(_word.value_signed() % (i16)value2); }
        word operator%=(int value2);
        word operator%=(i16 value2);
        word operator%=(u16 value2);
        word operator%=(word _word2);
        friend word operator&(word _word, word _word2) { return _word.value_unsigned() & _word2.value_unsigned(); }
        friend word operator&(word _word, u16 value2) { return _word.value_unsigned() & value2; }
        friend word operator&(u16 value2, word _word) { return value2 & _word.value_unsigned(); }
        word operator&=(u16 value2);
        word operator&=(word _word2);
        friend word operator|(word _word, word _word2) { return _word.value_unsigned() | _word2.value_unsigned(); }
        friend word operator|(word _word, u16 value2) { return _word.value_unsigned() | value2; }
        friend word operator|(u16 value2, word _word) { return value2 | _word.value_unsigned(); }
        word operator|=(u16 value2);
        word operator|=(word _word2);
        friend word operator^(word _word, word _word2) { return _word.value_unsigned() ^ _word2.value_unsigned(); }
        friend word operator^(word _word, u16 value2) { return _word.value_unsigned() ^ value2; }
        friend word operator^(u16 value2, word _word) { return value2 ^ _word.value_unsigned(); }
        word operator^=(u16 value2);
        word operator^=(word _word2);
        word operator~() { return ~this->value_unsigned(); }
        friend word operator>>(word _word, u16 value2) { return _word.value_unsigned() >> value2; }
        friend word operator<<(word _word, u16 value2) { return _word.value_unsigned() << value2; }
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool operator==(word v);
        bool operator==(u16 v);
        bool operator==(i16 v);
        bool operator==(int v);
        bool operator!=(word v);
        bool operator!=(u16 v);
        bool operator!=(i16 v);
        bool operator!=(int v);
        bool operator<(word v);
        bool operator<(u16 v);
        bool operator<(i16 v);
        bool operator<(int v);
        bool operator>(word v);
        bool operator>(u16 v);
        bool operator>(i16 v);
        bool operator>(int v);
        bool operator>=(word v);
        bool operator>=(u16 v);
        bool operator>=(i16 v);
        bool operator>=(int v);
        bool operator<=(word v);
        bool operator<=(u16 v);
        bool operator<=(i16 v);
        bool operator<=(int v);
        bool operator&&(word v);
        bool operator&&(u16 v);
        bool operator&&(i16 v);
        bool operator&&(int v);
        bool operator||(word v);
        bool operator||(u16 v);
        bool operator||(i16 v);
        bool operator||(int v);
        bool operator!();
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////
        friend std::ostream &operator<<(std::ostream &os, word v)
        {
            os << v.value_unsigned();
            return os;
        }
        friend std::istream &operator<<(std::istream &is, word v)
        {
            is >> v.reference_unsigned();
            return is;
        }
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////
        word operator++();
        word operator--();
        word operator++(int);
        word operator--(int);
    };
    class dword
    {
    private:
        word __low__;
        word __high__;

    public:
        /// @brief Constructor por defecto
        dword() { (*(u32 *)(this)) = 0; }
        /// @brief Constructor con valor de inicializacion uint32_t
        /// @param data Parametro de inicializacion
        dword(u32 data) { (*(u32 *)(this)) = data; }
        /// @brief Constructor con valor de inicializacion uint32_t
        /// @param low uint32_t de la parte baja del numero
        /// @param low uint32_t de la parte alta del numero
        dword(u8 low, u8 high) : __low__(low), __high__(high) {}
        /// @brief Constructor con valor de inicializacion word
        /// @param low word de la parte baja del numero
        /// @param low word de la parte alta del numero
        dword(word low, word high) : __low__(low), __high__(high) {}
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Funcion para obtener el valor de dicho objecto en base a int32_t
        /// @return Retorna el elemento en int32_t
        i32 value_signed() { return (*(u32 *)(this)); }
        /// @brief Funcion para obtener el valor de dicho objecto en base a uint32_t
        /// @return Retorna el elemento en uint32_t
        u32 value_unsigned() { return (*(u32 *)(this)); }
        /// @brief Funcion statica para obtener el valor de dicho objecto en base a int32_t
        /// @param __v Objecto de tipo dword
        /// @return Retorna el elemento en int32_t
        static i32 value_signed(dword __v) { return (*(u32 *)(&__v)); }
        /// @brief Funcion statica para obtener el valor de dicho objecto en base a uint32_t
        /// @param __v Objecto de tipo dword
        /// @return Retorna el elemento en uint32_t
        static u32 value_unsigned(dword __v) { return (*(u32 *)(&__v)); }

        /// @brief Funcion para obtener una referencia del vaor interno en base int32_t
        /// @return Retorna la referencia del int32_t
        i32 &reference_signed() { return (i32 &)(*(u32 *)(this)); }
        /// @brief Funcion para obtener una referencia del vaor interno en base uint32_t
        /// @return Retorna la referencia del uint32_t
        u32 &reference_unsigned() { return (*(u32 *)(this)); }
        /// @brief Funcion para obtener una referencia del vaor interno en base int32_t
        /// @param __v Referencia del objecto de tipo dword
        /// @return Retorna la referencia del int32_t
        static i32 &reference_signed(dword &__v) { return (i32 &)(*(u32 *)(&__v)); }
        /// @brief Funcion para obtener una referencia del vaor interno en base uint32_t
        /// @param __v Referencia del objecto de tipo dword
        /// @return Retorna la referencia del uint32_t
        static u32 &reference_unsigned(dword &__v) { return (*(u32 *)(&__v)); }

        /// @brief Obtiene los bist del valor de dword
        /// @param _bits Referencia a un elemento
        void bits(Bits &_lowlow, Bits &_highlow, Bits &_lowhigh, Bits &_highhigh)
        {
            __low__.bits(_lowlow, _highlow);
            __high__.bits(_lowhigh, _highhigh);
        }
        /// @brief Obtiene los bist del valor de word
        /// @param _word Calse word para la cual se aplica
        /// @param _bits Referencia a un elemento
        static void bits(dword _dword, Bits &_lowlow, Bits &_highlow, Bits &_lowhigh, Bits &_highhigh)
        {
            _dword.__low__.bits(_lowlow, _highlow);
            _dword.__high__.bits(_lowhigh, _highhigh);
        }
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////
        friend dword operator+(dword _dword, dword _dword2) { return (u32)(_dword.value_unsigned() + _dword2.value_unsigned()); }
        friend dword operator+(dword _dword, i32 value2) { return (i32)(_dword.value_signed() + value2); }
        friend dword operator+(dword _dword, u32 value2) { return (u32)(_dword.value_unsigned() + value2); }
        friend dword operator+(i32 value2, dword _dword) { return (i32)(value2 + _dword.value_signed()); }
        friend dword operator+(u32 value2, dword _dword) { return (u32)(value2 + _dword.value_unsigned()); }
        dword operator+=(i32 value2);
        dword operator+=(u32 value2);
        dword operator+=(dword _dword2);
        friend dword operator-(dword _dword, dword _dword2) { return (u32)(_dword.value_unsigned() - _dword2.value_unsigned()); }
        friend dword operator-(dword _dword, i32 value2) { return (i32)(_dword.value_signed() - value2); }
        friend dword operator-(dword _dword, u32 value2) { return (u32)(_dword.value_unsigned() - value2); }
        friend dword operator-(i32 value2, dword _dword) { return (i32)(value2 - _dword.value_signed()); }
        friend dword operator-(u32 value2, dword _dword) { return (u32)(value2 - _dword.value_unsigned()); }
        dword operator-=(i32 value2);
        dword operator-=(u32 value2);
        dword operator-=(dword _dword2);
        friend dword operator*(dword _dword, dword _dword2) { return (u32)(_dword.value_unsigned() * _dword2.value_unsigned()); }
        friend dword operator*(dword _dword, i32 value2) { return (i32)(_dword.value_signed() * value2); }
        friend dword operator*(dword _dword, u32 value2) { return (u32)(_dword.value_unsigned() * value2); }
        friend dword operator*(i32 value2, dword _dword) { return (i32)(value2 * _dword.value_signed()); }
        friend dword operator*(u32 value2, dword _dword) { return (u32)(value2 * _dword.value_unsigned()); }
        dword operator*=(i32 value2);
        dword operator*=(u32 value2);
        dword operator*=(dword _dword2);
        friend dword operator/(dword _dword, dword _dword2) { return (u32)(_dword.value_unsigned() / _dword2.value_unsigned()); }
        friend dword operator/(dword _dword, i32 value2) { return (i32)(_dword.value_signed() / value2); }
        friend dword operator/(dword _dword, u32 value2) { return (u32)(_dword.value_unsigned() / value2); }
        friend dword operator/(i32 value2, dword _dword) { return (i32)(value2 / _dword.value_signed()); }
        friend dword operator/(u32 value2, dword _dword) { return (u32)(value2 / _dword.value_unsigned()); }
        dword operator/=(i32 value2);
        dword operator/=(u32 value2);
        dword operator/=(dword _dword2);
        friend dword operator%(dword _dword, dword _dword2) { return (u32)(_dword.value_unsigned() % _dword2.value_unsigned()); }
        friend dword operator%(dword _dword, i32 value2) { return (i32)(_dword.value_signed() % value2); }
        friend dword operator%(dword _dword, u32 value2) { return (u32)(_dword.value_unsigned() % value2); }
        friend dword operator%(i32 value2, dword _dword) { return (i32)(value2 % _dword.value_signed()); }
        friend dword operator%(u32 value2, dword _dword) { return (u32)(value2 % _dword.value_unsigned()); }
        dword operator%=(i32 value2);
        dword operator%=(u32 value2);
        dword operator%=(dword _dword2);
        friend dword operator&(dword _dword, dword _dword2) { return _dword.value_unsigned() & _dword2.value_unsigned(); }
        friend dword operator&(dword _dword, u32 value2) { return _dword.value_unsigned() & value2; }
        friend dword operator&(u32 value2, dword _dword) { return value2 & _dword.value_unsigned(); }
        dword operator&=(u32 value2);
        dword operator&=(dword _dword2);
        friend dword operator|(dword _dword, dword _dword2) { return _dword.value_unsigned() | _dword2.value_unsigned(); }
        friend dword operator|(dword _dword, u32 value2) { return _dword.value_unsigned() | value2; }
        friend dword operator|(u32 value2, dword _dword) { return value2 | _dword.value_unsigned(); }
        dword operator|=(u32 value2);
        dword operator|=(dword _dword2);
        friend dword operator^(dword _dword, dword _dword2) { return _dword.value_unsigned() ^ _dword2.value_unsigned(); }
        friend dword operator^(dword _dword, u32 value2) { return _dword.value_unsigned() ^ value2; }
        friend dword operator^(u32 value2, dword _dword) { return value2 ^ _dword.value_unsigned(); }
        dword operator^=(u32 value2);
        dword operator^=(dword _dword2);
        dword operator~() { return ~this->value_unsigned(); }
        friend dword operator>>(dword _dword, u32 value2) { return _dword.value_unsigned() >> value2; }
        friend dword operator<<(dword _dword, u32 value2) { return _dword.value_unsigned() << value2; }
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool operator==(dword v);
        bool operator==(u32 v);
        bool operator==(i32 v);

        bool operator!=(dword v);
        bool operator!=(u32 v);
        bool operator!=(i32 v);

        bool operator<(dword v);
        bool operator<(u32 v);
        bool operator<(i32 v);

        bool operator>(dword v);
        bool operator>(u32 v);
        bool operator>(i32 v);

        bool operator>=(dword v);
        bool operator>=(u32 v);
        bool operator>=(i32 v);

        bool operator<=(dword v);
        bool operator<=(u32 v);
        bool operator<=(i32 v);

        bool operator&&(dword v);
        bool operator&&(u32 v);
        bool operator&&(i32 v);

        bool operator||(dword v);
        bool operator||(u32 v);
        bool operator||(i32 v);

        bool operator!();
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////
        friend std::ostream &operator<<(std::ostream &os, dword v)
        {
            os << v.value_unsigned();
            return os;
        }
        friend std::istream &operator<<(std::istream &is, dword v)
        {
            is >> v.reference_unsigned();
            return is;
        }
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////
        dword operator++();
        dword operator--();
        dword operator++(int);
        dword operator--(int);
    };
    class qword
    {
    private:
        dword __low__;
        dword __high__;

    public:
        /// @brief Constructor por defecto
        qword() { (*(u64 *)(this)) = 0; }
        /// @brief Constructor con valor de inicializacion uint64_t
        /// @param data Parametro de inicializacion
        qword(u64 data) { (*(u64 *)(this)) = data; }
        /// @brief Constructor con valor de inicializacion uint64_t
        /// @param low uint64_t de la parte baja del numero
        /// @param low uint64_t de la parte alta del numero
        qword(u8 low, u8 high) : __low__(low), __high__(high) {}
        /// @brief Constructor con valor de inicializacion dword
        /// @param low dword de la parte baja del numero
        /// @param low dword de la parte alta del numero
        qword(dword low, dword high) : __low__(low), __high__(high) {}
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Funcion para obtener el valor de dicho objecto en base a int64_t
        /// @return Retorna el elemento en int64_t
        i64 value_signed() { return (*(u64 *)(this)); }
        /// @brief Funcion para obtener el valor de dicho objecto en base a uint64_t
        /// @return Retorna el elemento en uint64_t
        u64 value_unsigned() { return (*(u64 *)(this)); }
        /// @brief Funcion statica para obtener el valor de dicho objecto en base a int64_t
        /// @param __v Objecto de tipo qword
        /// @return Retorna el elemento en int64_t
        static i64 value_signed(qword __v) { return (*(u64 *)(&__v)); }
        /// @brief Funcion statica para obtener el valor de dicho objecto en base a uint64_t
        /// @param __v Objecto de tipo qword
        /// @return Retorna el elemento en uint64_t
        static u64 value_unsigned(qword __v) { return (*(u64 *)(&__v)); }

        /// @brief Funcion para obtener una referencia del vaor interno en base int64_t
        /// @return Retorna la referencia del int64_t
        i64 &reference_signed() { return (i64 &)(*(u64 *)(this)); }
        /// @brief Funcion para obtener una referencia del vaor interno en base uint64_t
        /// @return Retorna la referencia del uint64_t
        u64 &reference_unsigned() { return (*(u64 *)(this)); }
        /// @brief Funcion para obtener una referencia del vaor interno en base int64_t
        /// @param __v Referencia del objecto de tipo qword
        /// @return Retorna la referencia del int64_t
        static i64 &reference_signed(qword &__v) { return (i64 &)(*(u64 *)(&__v)); }
        /// @brief Funcion para obtener una referencia del vaor interno en base uint64_t
        /// @param __v Referencia del objecto de tipo qword
        /// @return Retorna la referencia del uint64_t
        static u64 &reference_unsigned(qword &__v) { return (*(u64 *)(&__v)); }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////
        friend qword operator+(qword _dword, qword _dword2) { return (u64)(_dword.value_unsigned() + _dword2.value_unsigned()); }
        friend qword operator+(qword _dword, i64 value2) { return (i64)(_dword.value_signed() + value2); }
        friend qword operator+(qword _dword, u64 value2) { return (u64)(_dword.value_unsigned() + value2); }
        friend qword operator+(i64 value2, qword _dword) { return (i64)(value2 + _dword.value_signed()); }
        friend qword operator+(u64 value2, qword _dword) { return (u64)(value2 + _dword.value_unsigned()); }
        friend qword operator+(qword _dword, int value2) { return (i64)(_dword.value_signed() + (i64)value2); }
        qword operator+=(int value2);
        qword operator+=(i64 value2);
        qword operator+=(u64 value2);
        qword operator+=(qword _dword2);
        friend qword operator-(qword _dword, qword _dword2) { return (u64)(_dword.value_unsigned() - _dword2.value_unsigned()); }
        friend qword operator-(qword _dword, i64 value2) { return (i64)(_dword.value_signed() - value2); }
        friend qword operator-(qword _dword, u64 value2) { return (u64)(_dword.value_unsigned() - value2); }
        friend qword operator-(i64 value2, qword _dword) { return (i64)(value2 - _dword.value_signed()); }
        friend qword operator-(u64 value2, qword _dword) { return (u64)(value2 - _dword.value_unsigned()); }
        friend qword operator-(qword _dword, int value2) { return (i64)(_dword.value_signed() - (i64)value2); }
        qword operator-=(int value2);
        qword operator-=(i64 value2);
        qword operator-=(u64 value2);
        qword operator-=(qword _dword2);
        friend qword operator*(qword _dword, qword _dword2) { return (u64)(_dword.value_unsigned() * _dword2.value_unsigned()); }
        friend qword operator*(qword _dword, i64 value2) { return (i64)(_dword.value_signed() * value2); }
        friend qword operator*(qword _dword, u64 value2) { return (u64)(_dword.value_unsigned() * value2); }
        friend qword operator*(i64 value2, qword _dword) { return (i64)(value2 * _dword.value_signed()); }
        friend qword operator*(u64 value2, qword _dword) { return (u64)(value2 * _dword.value_unsigned()); }
        friend qword operator*(qword _dword, int value2) { return (i64)(_dword.value_signed() * (i64)value2); }
        qword operator*=(int value2);
        qword operator*=(i64 value2);
        qword operator*=(u64 value2);
        qword operator*=(qword _dword2);
        friend qword operator/(qword _dword, qword _dword2) { return (u64)(_dword.value_unsigned() / _dword2.value_unsigned()); }
        friend qword operator/(qword _dword, i64 value2) { return (i64)(_dword.value_signed() / value2); }
        friend qword operator/(qword _dword, u64 value2) { return (u64)(_dword.value_unsigned() / value2); }
        friend qword operator/(i64 value2, qword _dword) { return (i64)(value2 / _dword.value_signed()); }
        friend qword operator/(u64 value2, qword _dword) { return (u64)(value2 / _dword.value_unsigned()); }
        friend qword operator/(qword _dword, int value2) { return (i64)(_dword.value_signed() / (i64)value2); }
        qword operator/=(int value2);
        qword operator/=(i64 value2);
        qword operator/=(u64 value2);
        qword operator/=(qword _dword2);
        friend qword operator%(qword _dword, qword _dword2) { return (u64)(_dword.value_unsigned() % _dword2.value_unsigned()); }
        friend qword operator%(qword _dword, i64 value2) { return (i64)(_dword.value_signed() % value2); }
        friend qword operator%(qword _dword, u64 value2) { return (u64)(_dword.value_unsigned() % value2); }
        friend qword operator%(i64 value2, qword _dword) { return (i64)(value2 % _dword.value_signed()); }
        friend qword operator%(u64 value2, qword _dword) { return (u64)(value2 % _dword.value_unsigned()); }
        friend qword operator%(qword _dword, int value2) { return (i64)(_dword.value_signed() % (i64)value2); }
        qword operator%=(int value2);
        qword operator%=(i64 value2);
        qword operator%=(u64 value2);
        qword operator%=(qword _dword2);
        friend qword operator&(qword _dword, qword _dword2) { return _dword.value_unsigned() & _dword2.value_unsigned(); }
        friend qword operator&(qword _dword, u64 value2) { return _dword.value_unsigned() & value2; }
        friend qword operator&(u64 value2, qword _dword) { return value2 & _dword.value_unsigned(); }
        qword operator&=(u64 value2);
        qword operator&=(qword _dword2);
        friend qword operator|(qword _dword, qword _dword2) { return _dword.value_unsigned() | _dword2.value_unsigned(); }
        friend qword operator|(qword _dword, u64 value2) { return _dword.value_unsigned() | value2; }
        friend qword operator|(u64 value2, qword _dword) { return value2 | _dword.value_unsigned(); }
        qword operator|=(u64 value2);
        qword operator|=(qword _dword2);
        friend qword operator^(qword _dword, qword _dword2) { return _dword.value_unsigned() ^ _dword2.value_unsigned(); }
        friend qword operator^(qword _dword, u64 value2) { return _dword.value_unsigned() ^ value2; }
        friend qword operator^(u64 value2, qword _dword) { return value2 ^ _dword.value_unsigned(); }
        qword operator^=(u64 value2);
        qword operator^=(qword _dword2);
        qword operator~() { return ~this->value_unsigned(); }
        friend qword operator>>(qword _dword, u64 value2) { return _dword.value_unsigned() >> value2; }
        friend qword operator<<(qword _dword, u64 value2) { return _dword.value_unsigned() << value2; }
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool operator==(qword v);
        bool operator==(u64 v);
        bool operator==(i64 v);
        bool operator==(int v);
        bool operator!=(qword v);
        bool operator!=(u64 v);
        bool operator!=(i64 v);
        bool operator!=(int v);
        bool operator<(qword v);
        bool operator<(u64 v);
        bool operator<(i64 v);
        bool operator<(int v);
        bool operator>(qword v);
        bool operator>(u64 v);
        bool operator>(i64 v);
        bool operator>(int v);
        bool operator>=(qword v);
        bool operator>=(u64 v);
        bool operator>=(i64 v);
        bool operator>=(int v);
        bool operator<=(qword v);
        bool operator<=(u64 v);
        bool operator<=(i64 v);
        bool operator<=(int v);
        bool operator&&(qword v);
        bool operator&&(u64 v);
        bool operator&&(i64 v);
        bool operator&&(int v);
        bool operator||(qword v);
        bool operator||(u64 v);
        bool operator||(i64 v);
        bool operator||(int v);
        bool operator!();
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////
        friend std::ostream &operator<<(std::ostream &os, qword v)
        {
            os << v.value_unsigned();
            return os;
        }
        friend std::istream &operator<<(std::istream &is, qword v)
        {
            is >> v.reference_unsigned();
            return is;
        }
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////
        qword operator++();
        qword operator--();
        qword operator++(int);
        qword operator--(int);
    };
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class Binary
    {
    public:
        /// @brief Funcion para obtener el binario de un dato primitivo
        /// @tparam T Tipo de dato primitivo(!Atencion: No se debe insertar ningun tipo de dato nuevo!)
        /// @param value Valor a analizar
        /// @return Devuelve una cadena de caracteres tipo (?stringbuffer?) con el binario
        template <typename T>
        static stringbuffer binary(T value)
        {
            stringbuffer __bin__("0b", sizeof(T) * 8 + 2);
            i16 i = sizeof(T) * 8;
            while (--i >= 0)
                __bin__[(sizeof(T) * 8) - i + 1] = value & ((T)(1) << i) ? '1' : '0';
            return __bin__;
        }
        stringbuffer operator<<(u8 __value);
        stringbuffer operator<<(i8 __value);
        stringbuffer operator<<(byte __value);
        stringbuffer operator<<(u16 __value);
        stringbuffer operator<<(i16 __value);
        stringbuffer operator<<(word __value);
        stringbuffer operator<<(u32 __value);
        stringbuffer operator<<(i32 __value);
        stringbuffer operator<<(dword __value);
        stringbuffer operator<<(u64 __value);
        stringbuffer operator<<(i64 __value);
        stringbuffer operator<<(qword __value);
    };
    inline Binary bin;
    class Hexadecimal
    {
    private:
        static char __hexadecimal__caracter__(u8 value) { return (value < 10) ? '0' + value : value - 10 + 'a'; }

    public:
        /// @brief Funcion para obtener el hexadecimal de un dato primitivo
        /// @tparam T Tipo de dato primitivo(!Atencion: No se debe insertar ningun tipo de dato nuevo!)
        /// @param value Valor a analizar
        /// @return Devuelve una cadena de caracteres tipo (?stringbuffer?) con el hexadecimal
        template <typename T>
        static stringbuffer hexadecimal(T value)
        {
            stringbuffer __hex__("0x", sizeof(T) * 2 + 2);
            i16 i = sizeof(T) * 2;
            while (--i >= 0)
            {
                __hex__[sizeof(T) * 2 - i + 1] = __hexadecimal__caracter__(value / ((T)(1) << (4 * i)));
                value %= ((T)(1) << (T)(4 * i));
            }
            return __hex__;
        }
        stringbuffer operator<<(u8 __value);
        stringbuffer operator<<(i8 __value);
        stringbuffer operator<<(byte __value);
        stringbuffer operator<<(u16 __value);
        stringbuffer operator<<(i16 __value);
        stringbuffer operator<<(word __value);
        stringbuffer operator<<(u32 __value);
        stringbuffer operator<<(i32 __value);
        stringbuffer operator<<(dword __value);
        stringbuffer operator<<(u64 __value);
        stringbuffer operator<<(i64 __value);
        stringbuffer operator<<(qword __value);
    };
    inline Hexadecimal hex;

    /// @brief Clase que genera los limites de los tipos de datos
    /// @tparam T Tipo de dato primitivo(!Atencion: No se debe insertar ningun tipo de dato nuevo!)
    template <typename T>
    class limits
    {
    public:
        /// @brief Expresion constante para obtener el limite
        /// @return Devuelve el limite minimo del dato primitivo
        static constexpr T min()
        {
            if constexpr (std::is_unsigned<T>())
                return 0;
            else if constexpr (sizeof(T) == 1)
                return 0x80;
            else if constexpr (sizeof(T) == 2)
                return 0x8000;
            else if constexpr (sizeof(T) == 4)
                return 0x80000000;
            else if constexpr (sizeof(T) == 8)
                return 0x8000000000000000;
            else
                return 0;
        }
        /// @brief Expresion constante para obtener el limite
        /// @return Devuelve el limite maximo del dato primitivo
        static constexpr T max()
        {
            if constexpr (sizeof(T) == 1)
                return std::is_unsigned<T>() ? 0xff : 0x7f;
            else if constexpr (sizeof(T) == 2)
                return std::is_unsigned<T>() ? 0xffff : 0x7fff;
            else if constexpr (sizeof(T) == 4)
                return std::is_unsigned<T>() ? 0xffffffff : 0x7fffffff;
            else if constexpr (sizeof(T) == 8)
                return std::is_unsigned<T>() ? 0xffffffffffffffff : 0x7fffffffffffffff;
            else
                return 0;
        }
        ~limits() {}
    };
}
#endif