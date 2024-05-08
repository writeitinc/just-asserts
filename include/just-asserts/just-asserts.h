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

#include "ja-runtime-asserts.h" // IWYU pragma: export
#include "ja-static-asserts.h" // IWYU pragma: export
#include "ja-version.h" // IWYU pragma: export

#endif // just_asserts_h

/*
 * Copyright 2024 shan <writeitinc99@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the “Software”), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
