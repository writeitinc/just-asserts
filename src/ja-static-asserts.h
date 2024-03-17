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
 * When compiling with clang, gcc, or C11 (or later), the macro
 * `JA_FEATURE_STATIC_ASSERT_WITHIN_STRUCT_DECL` will be defined and both static assertion macro
 * can be used anywhere declarations are allowed--including within struct/union declarations. If
 * this behavior is available, the macro `JA_FEATURE_STATIC_ASSERT_WITHIN_STRUCT_DECL` will be
 * defined as `1`:
 * ```c
 * ja_static_assert(1);
 *
 * struct SomeStruct {
 * 	int i;
 * #if JA_FEATURE_STATIC_ASSERT_WITHIN_STRUCT_DECL
 * 	ja_static_assert(1); // Not C99-portable
 * #endif
 * };
 *
 * void some_func(void)
 * {
 * 	ja_static_assert(1);
 * }
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

# define JA_FEATURE_STATIC_ASSERT_WITHIN_STRUCT_DECL 1

# define ja_static_assert_msg(cond, message) _Static_assert(cond, message)
# define ja_static_assert(cond) ja_static_assert_msg(cond, "Expected `" #cond "` to be non-zero")

#elif __clang__

/*
 * Uses pragmas to disable pedantic warnings to avoid pedantic warnings (if applicable).
 * This doesn't work for gcc because gcc expects a semicolon after the static assert statement and
 * before the last pragma.
 */
# define ja_static_assert_msg(cond, message) \
	_Pragma("GCC diagnostic push") \
	_Pragma("GCC diagnostic ignored \"-Wpedantic\"") \
	_Static_assert(cond, message) \
	_Pragma("GCC diagnostic pop")
# define ja_static_assert(cond) ja_static_assert_msg(cond, "`" #cond "`")

#elif __GNUC__

/*
 * Uses the `__extension__` keyword to avoid pedantic warnings (if applicable).
 * This doesn't work for clang if used within a struct/union declaration because clang will
 * interpret `__extension__` as a type.
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
 * - does not work within a struct/union declaration
 *   - incidentally works in gcc/clang since they support anonymous enums as a compiler extension
 * - compiler errors aren't always helpful (overly verbose or not verbose enough)
 */
# define ja_static_assert(cond) \
	enum { JA__UNIQUE_IDENT(JA__STATIC_ASSERT_ENUM) = sizeof(char [(cond) ? 1 : -1]) }
# define ja_static_assert_msg(cond, msg) ja_static_assert(cond)

# define JA__CAT(a, b) JA__CAT1(a, b)
# define JA__CAT1(a, b) a##b

# define JA__UNIQUE_IDENT(base) JA__CAT(base, __COUNTER__)

#else

# define JA_FEATURE_STATIC_ASSERT_WITHIN_STRUCT_DECL 0

// Universal implementation
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
