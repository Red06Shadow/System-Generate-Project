#include <vector>
#include <stda/sstrings/sstrings.hpp>
#include <stda/numbers/numbers.hpp>

#ifndef TYPEDEFS
#define TYPEDEFS

/* @Documentacion:
 * Contiene una simplificacion de definiciones de clases para facilitar su uso
 */

typedef std::vector<numbers::byte> vbytes;
typedef std::vector<numbers::word> vword;
typedef std::vector<numbers::dword> vdword;
typedef std::vector<numbers::qword> vqword;
typedef std::vector<stringbuffer> vstringbuffers;
typedef std::vector<wstringbuffer> vwstringbuffers;
typedef std::vector<std::string> vstrings;
typedef std::vector<std::wstring> vwstrings;
typedef std::vector<char*> vcstr;
#endif