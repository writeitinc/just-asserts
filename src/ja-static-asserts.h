#ifndef just_asserts_static_asserts_h
#define just_asserts_static_asserts_h

/*
 * This header defines two macros:
 * - `ja_static_assert_msg(cond, message)`
 * - `ja_static_assert(cond)`
 *
 * `ja_static_assert()` checks a condition at compile time and produces an error if said condition
 * isn't met.
 * `ja_static_assert_msg()` functions the same, but also (attempts to) display a user-provided
 * message to explain the error.
 *
 * These macros can be used in both function and global scope:
 * ```c
 * ja_static_assert(1);
 *
 * void some_func(void)
 * {
 * 	ja_static_assert(1);
 * }
 * ```
 *
 * When compiling with gcc, clang, or C11 and later, you may also place static assertions within
 * struct/union declarations. The availability of this feature is indicated by defining the macro
 * `JA_STATIC_ASSERT_IN_STRUCT_DECL`.
 * ```c
 * struct SomeStruct {
 * 	int i;
 * #ifdef JA_STATIC_ASSERT_IN_STRUCT_DECL
 * 	ja_static_assert(1);
 * #endif
 * };
 * ```
 */

/*
 * Summary of static assertion builtins and their availability:
 *
 * -----------------------------------------------------------------
 * Keyword/Macro                  |  Availability    
 * -----------------------------------------------------------------
 * _Static_assert(cond, message)  |  (as keyword) since C11
 *                                |  (as keyword) as a GNU extension
 * -----------------------------------------------------------------
 * static_assert(cond, message)   |  (<assert.h>) since C11
 *                                |  (as keyword) since C23
 * -----------------------------------------------------------------
 * static_assert(cond)            |  (as keyword) since C23
 * -----------------------------------------------------------------
 */

#if __STDC_VERSION__ > 201710L // Check for version later than C17 (i.e. C23)

# define ja_static_assert_msg(cond, message) static_assert(cond, message)
# define ja_static_assert(cond) static_assert(cond)

#elif __STDC_VERSION__ >= 201112L // C11 or later

# define JA_STATIC_ASSERT_IN_STRUCT_DECL

# define ja_static_assert_msg(cond, message) _Static_assert(cond, message)
# define ja_static_assert(cond) \
	ja_static_assert_msg(cond, "Expression `" #cond "` should be non-zero")

#elif __clang__

// prevent glibc from shadowing the _Static_assert builtin
# undef _Static_assert
# define _Static_assert _Static_assert

# define JA_STATIC_ASSERT_IN_STRUCT_DECL

/*
 * We must use pragmas to avoid pedantic warnings.
 * This doesn't work when compiling with gcc because gcc expects a semicolon right after the static
 * assert statement.
 */
# define ja_static_assert_msg(cond, message) \
	_Pragma("GCC diagnostic push") \
	_Pragma("GCC diagnostic ignored \"-Wpedantic\"") \
	_Static_assert(cond, message) \
	_Pragma("GCC diagnostic pop")
# define ja_static_assert(cond) ja_static_assert_msg(cond, "`" #cond "`")

#elif __GNUC__

// prevent glibc from shadowing the _Static_assert builtin
# undef _Static_assert
# define _Static_assert _Static_assert

# define JA_STATIC_ASSERT_IN_STRUCT_DECL

/*
 * We must use the `__extension__` keyword to avoid pedantic warnings.
 * This doesn't work under clang within a struct/union declaration because clang will interpret
 * `__extension__` as a type.
 */
# define ja_static_assert_msg(cond, message) __extension__ _Static_assert(cond, message)
# define ja_static_assert(cond) ja_static_assert_msg(cond, "`" #cond "`")

#elif defined(__COUNTER__)

/*
 * Triggers a compilation error within an anonymous enum declaration.
 * A unique enum constant identifier is generated using the `__COUNTER__` macro.
 *
 * Pros:
 * - works with every compiler I've tested
 * - works in both file and function scope
 *
 * Cons:
 * - does not work within a struct/union declaration unless anonymous enum fields are supported (as
 *   a compiler extension)
 * - compiler errors aren't always helpful (overly verbose or not verbose enough)
 */
# define ja_static_assert(cond) \
	enum { JA__UNIQUE_IDENT(JA__STATIC_ASSERT_ENUM) = sizeof(char [(cond) ? 1 : -1]) }
# define ja_static_assert_msg(cond, msg) ja_static_assert(cond)

# define JA__CAT(a, b) JA__CAT_(a, b)
# define JA__CAT_(a, b) a##b

# define JA__UNIQUE_IDENT(base) JA__CAT(base, __COUNTER__)

#else // Universal Implementation

/*
 * Triggers a compilation error within an extern variable declaration.
 *
 * Pros:
 * - works with every compiler I've tested
 * - works in both file and function scope
 *
 * Cons:
 * - does not work within a struct/union declaration
 * - compiler errors aren't always helpful (overly verbose or not verbose enough)
 * - emits an external symbol (ja__static_assert_helper_array)
 */
# define ja_static_assert(cond) extern const char ja__static_assert_helper_array[(cond) ? 1 : -1]
# define ja_static_assert_msg(cond, msg) ja_static_assert(cond)

extern const char ja__static_assert_helper_array[1];

#endif

#endif // just_asserts_static_asserts_h

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
