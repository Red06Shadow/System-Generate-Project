
#ifndef TYPEDEFNUMBERS
#define TYPEDEFNUMBERS

/* @Documentacion:
 * Este archivo presenta una reduccion en la definicion de los tipos para los valores de 8bits a 128bits
 */

/// @brief Tipo de dato entero con signo de 8bit
using i8 = char;
/// @brief Tipo de dato entero sin signo de 8bit
using u8 = unsigned char;
#define sizeu8 sizeof(u8)
#define nbitsu8 8
#define maxu8 size_t(256)

/// @brief Tipo de dato entero con signo de 16bit
using i16 = short;
/// @brief Tipo de dato entero sin signo de 16bit
using u16 = unsigned short;
#define sizeu16 sizeof(u16)
#define nbitsu16 16
#define maxu16 size_t(maxu8 *maxu8)

/// @brief Tipo de dato entero con signo de 32bit
using i32 = int;
/// @brief Tipo de dato entero sin signo de 32bit
using u32 = unsigned int;
#define sizeu32 sizeof(u32)
#define nbitsu32 32
#define maxu32 size_t(maxu16 *maxu16)

/// @brief Tipo de dato entero con signo de 64bit
using i64 = long long;
/// @brief Tipo de dato entero sin signo de 64bit
using u64 = unsigned long long;
#define sizeu64 sizeof(u64)
#define nbitsu64 64
#define maxu64l size_t(-1)

/// @brief Tipo de dato flotante de 32bit
using f32 = float;
#define sizef32 sizeof(f32)
#define nbitsf32 32

/// @brief Tipo de dato flotante(double) de 64bit
using f64 = double;
#define sizef64 sizeof(f64)
#define nbitsf64 64

/// @brief Tipo de dato flotante(long double) de 128bit
using f128 = long double;
#define sizef128 sizeof(f128)
#define nbitsf128 128

#endif