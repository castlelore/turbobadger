// ================================================================================
// == This file is a part of Tinkerbell UI Toolkit. (C) 2011-2012, Emil Seger�s ==
// ==                   See tinkerbell.h for more information.                   ==
// ================================================================================

#ifndef TB_HASH_H
#define TB_HASH_H

#include "tb_types.h"

namespace tinkerbell {

// On C++ compilers that support it, use const expr for hash so that
// TBID comparisions turn into simple uint32 comparisions compiletime.
// Disabled for debug builds, so TBID string debugging is available.

#ifndef _DEBUG
#if __cplusplus >= 201103L
#define TB_SUPPORT_CONSTEXPR
#endif
#endif

#ifdef TB_SUPPORT_CONSTEXPR

// FNV constants
static constexpr uint32 basis = 2166136261U;
static constexpr uint32 prime = 16777619U;

// compile-time hash helper function
constexpr uint32 TBGetHash_one(char c, const char* remain, uint32 value)
{
	return c == 0 ? value : TBGetHash_one(remain[0], remain + 1, (value ^ c) * prime);
}

// compile-time hash
constexpr uint32 TBGetHash(const char* str)
{
	return (str && *str) ? TBGetHash_one(str[0], str + 1, basis) : 0;
}

#define TBIDC(str) TBID(TBGetHash(str))

#else // TB_SUPPORT_CONSTEXPR

#define TBIDC(str) TBID(str)

/** Get hash value from string */
uint32 TBGetHash(const char *str);

#endif // !TB_SUPPORT_CONSTEXPR

}; // namespace tinkerbell

#endif // TB_HASH_H