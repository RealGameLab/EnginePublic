#ifndef _ssfBaseDataType_h_
#define _ssfBaseDataType_h_

#include <stdint.h>
#include <string>
#include <vector>
#include <list>
#include <memory>

#ifdef UNICODE
typedef wchar_t TCHAR;
#else
typedef char TCHAR;
#endif

namespace ssf
	{
	// specific size types
	typedef char int8;
	typedef int16_t int16;
	typedef int32_t int32;
	typedef int64_t int64;
	typedef uint8_t uint8;
	typedef uint16_t uint16;
	typedef uint32_t uint32;
	typedef uint64_t uint64;
	typedef float real32;
	typedef double real64;

	// string type
	typedef std::string string;

	// vector & list types
	using std::vector;
	using std::list;
	using std::auto_ptr;

	// exception type
	typedef std::exception exception;
	
	// configuration
	const bool convert_endianness = false; // Intel x86/x64 are little-endian
	}

#include "ssfObject.h"
#include "ssfCountedPointer.h"
#include "ssfCRC32.h"
#include "ssfAttribute.h"

#endif//_ssfBaseDataType_h_