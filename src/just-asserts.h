/*
 * Before including this header, you may want to define the following macros:
 * - JA_DEBUG:
 *       Enables debug-only asserts.
 * - JA_IMPLEMENTATION:
 *       The library will place objects and functions with external linkage should be placed in the
 *       current translation unit. This allows `just-asserts` to be used as a header-only library.
 * - JA_DONT_INCLUDE_STD_HEADERS:
 *       Indicates that the library should not include standard headers. This means if you use a
 *       macro whose contents depends on the inclusion of a header, you must include it yourself.
 */

#ifndef just_asserts_h
#define just_asserts_h

#include "ja-runtime-asserts.h"
#include "ja-static-asserts.h"

#endif // just_asserts_h
