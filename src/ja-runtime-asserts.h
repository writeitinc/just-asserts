/*
 * Before including this header, you may want to define the following macros:
 * - JA_DEBUG:
 *       Enables debug-only asserts.
 * - JA_IMPLEMENTATION:
 *       The library will place objects and functions with external linkage should be placed in the
 *       current translation unit. This allows `just-asserts` to be used as a header-only library.
 */

#ifndef ja_runtime_asserts_h
#define ja_runtime_asserts_h

#include "ja-templates.h"

#ifdef JA_DEBUG
# define JA_DEBUG_RELEASE_SWITCH(debug, release) debug
#else
# define JA_DEBUG_RELEASE_SWITCH(debug, release) release
#endif

// Checks a condition (fatal).
/*
 * If `expr` is falsy (false, null, or zero), prints a diagnostic message and terminates the
 * application with a status of `EXIT_FAILURE`.
 */
#define ja_assert(expr) ja_assert_msg(expr, "Failed assertion: `" #expr "`")

// Checks a condition (nonfatal).
/*
 * If `expr` is falsy (false, null, or zero), prints a diagnostic message.
 */
#define ja_expect(expr) ja_expect_msg(expr, "Unmet expectation: `" #expr "`")

// Checks a condition (fatal, custom message).
/*
 * If `expr` is falsy (false, null, or zero), prints a user-provided diagnostic message and
 * terminates the application with a status of `EXIT_FAILURE`.
 *
 * The variadic arguments should be a printf-style format string and any arguments it specifies.
 */
#define ja_assert_msg(expr, /* const char *fmt, */ ...) ((expr) \
		? (void)0 \
		: ja__fail(JA__ASSERTION, JA__TRACE, __VA_ARGS__))

// Checks a condition (nonfatal, custom message).
/*
 * If `expr` is falsy (false, null, or zero), prints a user-provided diagnostic message.
 *
 * The variadic arguments should be a printf-style format string and any arguments it specifies.
 */
#define ja_expect_msg(expr, /* const char *fmt, */ ...) ((expr) \
		? (void)0 \
		: ja__fail(JA__EXPECTATION, JA__TRACE, __VA_ARGS__))

// These debug macros are the same as their non-debug counterparts except that they evaluate to a
// no-op in a release build.
/*
 * NOTE: `expr` is not evaluated in a release build.
 */
#define ja_dbg_assert(expr) JA_DEBUG_RELEASE_SWITCH(ja_assert(expr), (void)0)
#define ja_dbg_assert_msg(expr, msg) JA_DEBUG_RELEASE_SWITCH(ja_assert_msg(expr, msg), (void)0)
#define ja_dbg_expect(expr) JA_DEBUG_RELEASE_SWITCH(ja_expect(expr), (void)0)
#define ja_dbg_expect_msg(expr, msg) JA_DEBUG_RELEASE_SWITCH(ja_expect_msg(expr, msg), (void)0)

#ifdef JA_DEBUG
// Checks a condition in a debug build but assumes it is true in a release build.
/*
 * Evaluates to `expr`.
 * If `JA_DEBUG` is defined and `expr` is falsy (false, null, or zero), prints a diagnostic message.
 * If `JA_DEBUG` is not defined, `expr` is assumed to be truthy.
 */
# define ja_assume_true(expr) (ja_expect_msg(expr, \
		"False expression was assumed to be true: `" #expr "`"), (expr))

// Checks a condition in a debug build but assumes it is false in a release build.
/*
 * Evaluates to `expr`.
 * If `JA_DEBUG` is defined and `expr` is truthy (true, non-null, or non-zero), prints a diagnostic
 * message.
 * If `JA_DEBUG` is not defined, `expr` is assumed to be falsy.
 */
# define ja_assume_false(expr) (ja_expect_msg(!(expr), \
		"True expression was assumed to be false: `" #expr "`"), (expr))
#else
# define ja_assume_true(expr) (1)
# define ja_assume_false(expr) (0)
#endif

// Checks a comparison (fatal).
/*
 * If `a OP b` does not hold true, prints a diagnostic message and terminates the application with
 * a status of `EXIT_FAILURE`.
 */
#define ja_assert_cmp(T, a, OP, b) (JA_COMPARE(T, a, OP, b) \
		? (void)0 \
		: ja__cmp_fail(JA__ASSERTION, JA__TRACE, JA__GENERIC_COMPARISON, \
					JA_TYPE_STR(T), JA_FMT(T), #a, #OP, #b, \
					JA_FMT_ARGS(T, a), JA_FMT_ARGS(T, b)))
// Checks a comparison (nonfatal).
/*
 * If `a OP b` does not hold true, prints a diagnostic message.
 */
#define ja_expect_cmp(T, a, OP, b) (JA_COMPARE(T, a, OP, b) \
		? (void)0 \
		: ja__cmp_fail(JA__EXPECTATION, JA__TRACE, JA__GENERIC_COMPARISON, \
					JA_TYPE_STR(T), JA_FMT(T), #a, #OP, #b, \
					JA_FMT_ARGS(T, a), JA_FMT_ARGS(T, b)))

// Checks an equality (fatal).
/*
 * If `a` and `b` do not compare equal, prints a diagnostic message and terminates the application
 * with a status of `EXIT_FAILURE`.
 */
#define ja_assert_eq(T, a, b) (JA_EQUALS(T, a, b) \
		? (void)0 \
		: ja__cmp_fail(JA__ASSERTION, JA__TRACE, JA__EQUALITY, \
					JA_TYPE_STR(T), JA_FMT(T), #a, "==", #b, \
					JA_FMT_ARGS(T, a), JA_FMT_ARGS(T, b)))

// Checks an equality (nonfatal).
/*
 * If `a` and `b` do not compare equal, prints a diagnostic message.
 */
#define ja_expect_eq(T, a, b) (JA_EQUALS(T, a, b) \
		? (void)0 \
		: ja__cmp_fail(JA__EXPECTATION, JA__TRACE, JA__EQUALITY, \
					JA_TYPE_STR(T), JA_FMT(T), #a, "==", #b, \
					JA_FMT_ARGS(T, a), JA_FMT_ARGS(T, b)))

// Checks a non-equality (fatal).
/*
 * If `a` and `b` compare equal, prints a diagnostic message and terminates the application with a
 * status of `EXIT_FAILURE`.
 */
#define ja_assert_neq(T, a, b) (!JA_EQUALS(T, a, b) \
		? (void)0 \
		: ja__cmp_fail(JA__ASSERTION, JA__TRACE, JA__NON_EQUALITY, \
					JA_TYPE_STR(T), JA_FMT(T), #a, "!=", #b, \
					JA_FMT_ARGS(T, a), JA_FMT_ARGS(T, b)))

// Checks a non-equality (nonfatal).
/*
 * If `a` and `b` compare equal, prints a diagnostic message.
 */
#define ja_expect_neq(T, a, b) (!JA_EQUALS(T, a, b) \
		? (void)0 \
		: ja__cmp_fail(JA__EXPECTATION, JA__TRACE, JA__NON_EQUALITY, \
					JA_TYPE_STR(T), JA_FMT(T), #a, "!=", #b, \
					JA_FMT_ARGS(T, a), JA_FMT_ARGS(T, b)))

typedef enum JACheckType {
	JA__ASSERTION,
	JA__EXPECTATION,
} JACheckType;

typedef enum JAComparisonType {
	JA__GENERIC_COMPARISON,
	JA__EQUALITY,
	JA__NON_EQUALITY,
} JAComparisonType;

typedef struct JATrace {
	const char *file;
	const char *func;
	unsigned int line;
} JATrace;

#define JA__TRACE (JATrace){ \
		.file = __FILE__, \
		.func = __func__, \
		.line = __LINE__, \
	}

void ja__fail(JACheckType check_type, JATrace trace, const char *fmt, ...);
void ja__cmp_fail(JACheckType check_type, JATrace trace, JAComparisonType cmp_type,
		const char *type_str, const char *type_fmt,
		const char *expr_a_str, const char *op_str, const char *expr_b_str,
		... /* T res_a, T res_b */);

#ifdef JA_IMPLEMENTATION

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

static void report_trace(JACheckType check_type, JATrace trace);
static void report(const char *str);
static void reportf(const char *fmt, ...);
static void reportf_va(const char *fmt, va_list va_args);
static void report_char(int c);

// Prints to `stderr` the details of a failed assertion or expectation.
// In the case of a failed assertion, the application is terminated with a status of `EXIT_FAILURE`.
/*
 * This function isn't designed to cope with multi-line formatted messages.
 */
void ja__fail(JACheckType check_type, JATrace trace, const char *fmt, ...)
{
	va_list va_args;
	va_start(va_args, fmt);

	report_trace(check_type, trace);

	report_char('\t');
	reportf_va(fmt, va_args);
	report_char('\n');

	va_end(va_args);

	if (check_type == JA__ASSERTION) {
		exit(EXIT_FAILURE);
	}
}

// Prints to `stderr` the details of a failed comparison assertion or comparison expectation.
// In the case of a failed assertion, the application is terminated with a status of `EXIT_FAILURE`.
void ja__cmp_fail(JACheckType check_type, JATrace trace, JAComparisonType cmp_type,
		const char *type_str, const char *type_fmt,
		const char *expr_a_str, const char *op_str, const char *expr_b_str,
		... /* T res_a, T res_b */)
{
	va_list va_args;
	va_start(va_args, expr_b_str);

	const char *FAILURE_DESCRIPTIONS[] = {
		[JA__ASSERTION] = "Failed assertion",
		[JA__EXPECTATION] = "Unmet expectation",
	};

	const char *COMPARISON_TYPE_STR[] = {
		[JA__GENERIC_COMPARISON] = "comparison",
		[JA__EQUALITY] = "equality",
		[JA__NON_EQUALITY] = "non-equality",
	};

	report_trace(check_type, trace);
	reportf("\t%s for %s of type `%s`\n", FAILURE_DESCRIPTIONS[check_type],
			COMPARISON_TYPE_STR[cmp_type], type_str);

	// "        Assertion: (<expr_a>) <op> (<expr_b>)"
	// "               ==> (<res_a>) <op> (<res_b>)"
	reportf("\tAssertion: %s %s %s\n", expr_a_str, op_str, expr_b_str);
	report_char('\t');
	report("       ==> ");
	reportf_va(type_fmt, va_args);
	reportf(" %s ", op_str);
	reportf_va(type_fmt, va_args);
	report_char('\n');

	va_end(va_args);

	if (check_type == JA__ASSERTION) {
		exit(EXIT_FAILURE);
	}
}

// Prints a line trace to `stderr` for an assertion or expectation.
void report_trace(JACheckType check_type, JATrace trace)
{
	const char *CHECK_TYPE_DIAGNOSTIC_STR[] = {
		[JA__ASSERTION] = "assert",
		[JA__EXPECTATION] = "expect",
	};
	reportf("[ja:%s] <%s:%s:%u>\n", CHECK_TYPE_DIAGNOSTIC_STR[check_type],
			trace.file, trace.func, trace.line);
}

// Prints a message to `stderr`.
void report(const char *str)
{
	fputs(str, stderr);
}

// Prints a formatted message to `stderr`.
void reportf(const char *fmt, ...)
{
	va_list va_args;
	va_start(va_args, fmt);

	reportf_va(fmt, va_args);

	va_end(va_args);
}

// Prints a formatted message to `stderr`.
void reportf_va(const char *fmt, va_list va_args)
{
	vfprintf(stderr, fmt, va_args);
}

// Prints a byte to `stderr`.
void report_char(int c)
{
	putc(c, stderr);
}

#endif // JA_IMPLEMENTATION

#endif // ja_runtime_asserts_h
