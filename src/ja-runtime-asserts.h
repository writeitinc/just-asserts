#ifndef ja_runtime_asserts_h
#define ja_runtime_asserts_h

#include "ja-templates.h"

#if JA_DEBUG
# define JA__DEBUG_ONLY(expr) (expr)
#else
# define JA__DEBUG_ONLY(expr) (void)0
#endif

#define ja_assert(expr) ja_assert_msg(expr, "Failed assertion: `" #expr "`")
#define ja_expect(expr) ja_expect_msg(expr, "Unmet expectation: `" #expr "`")
#define ja_assert_msg(expr, ...) ((expr) \
		? (void)0 \
		: ja__fail(JA__ASSERTION, JA__TRACE, __VA_ARGS__))
#define ja_expect_msg(expr, ...) ((expr) \
		? (void)0 \
		: ja__fail(JA__EXPECTATION, JA__TRACE, __VA_ARGS__))

#define ja_dbg_assert(expr) JA__DEBUG_ONLY(ja_assert(expr))
#define ja_dbg_assert_msg(expr, msg) JA__DEBUG_ONLY(ja_assert_msg(expr, msg))
#define ja_dbg_expect(expr) JA__DEBUG_ONLY(ja_expect(expr))
#define ja_dbg_expect_msg(expr, msg) JA__DEBUG_ONLY(ja_expect_msg(expr, msg))

#if JA_DEBUG
# define ja_assume_true(expr) (ja_expect_msg(expr, \
		"False expression was assumed to be true: `" #expr "`"), (expr))
# define ja_assume_false(expr) (ja_expect_msg(!(expr), \
		"True expression was assumed to be false: `" #expr "`"), (expr))
#else
# define ja_assume_true(expr) (1)
# define ja_assume_false(expr) (0)
#endif

#define ja_assert_cmp(T, a, OP, b) (JA_COMPARE(T, a, OP, b) \
		? (void)0 \
		: ja__cmp_fail(JA__ASSERTION, JA__TRACE, JA__GENERIC_COMPARISON, \
					JA_TYPE_STR(T), JA_FMT(T), #a, #OP, #b, \
					JA_FMT_ARGS(T, a), JA_FMT_ARGS(T, b)))
#define ja_expect_cmp(T, a, OP, b) (JA_COMPARE(T, a, OP, b) \
		? (void)0 \
		: ja__cmp_fail(JA__EXPECTATION, JA__TRACE, JA__GENERIC_COMPARISON, \
					JA_TYPE_STR(T), JA_FMT(T), #a, #OP, #b, \
					JA_FMT_ARGS(T, a), JA_FMT_ARGS(T, b)))

#define ja_assert_eq(T, a, b) (JA_EQUALS(T, a, b) \
		? (void)0 \
		: ja__cmp_fail(JA__ASSERTION, JA__TRACE, JA__EQUALITY, \
					JA_TYPE_STR(T), JA_FMT(T), #a, "==", #b, \
					JA_FMT_ARGS(T, a), JA_FMT_ARGS(T, b)))
#define ja_expect_eq(T, a, b) (JA_EQUALS(T, a, b) \
		? (void)0 \
		: ja__cmp_fail(JA__EXPECTATION, JA__TRACE, JA__EQUALITY, \
					JA_TYPE_STR(T), JA_FMT(T), #a, "==", #b, \
					JA_FMT_ARGS(T, a), JA_FMT_ARGS(T, b)))
#define ja_assert_neq(T, a, b) (!JA_EQUALS(T, a, b) \
		? (void)0 \
		: ja__cmp_fail(JA__ASSERTION, JA__TRACE, JA__NON_EQUALITY, \
					JA_TYPE_STR(T), JA_FMT(T), #a, "!=", #b, \
					JA_FMT_ARGS(T, a), JA_FMT_ARGS(T, b)))
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
		const char *type_str, const char *type_fmt, const char *expr_a_str,
		const char *op_str, const char *expr_b_str,
		... /* T res_a, T res_b */);

#ifdef JA_IMPLEMENTATION

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

static void ja__report_trace(JACheckType check_type, JATrace trace);
static void ja__report_line(const char *fmt, ...);
static void ja__report(const char *fmt, ...);
static void ja__report_line_va(const char *fmt, va_list va_args);
static void ja__report_va(const char *fmt, va_list va_args);
static void ja__report_char(char c);

void ja__fail(JACheckType check_type, JATrace trace, const char *fmt, ...)
{
	va_list va_args;
	va_start(va_args, fmt);

	ja__report_trace(check_type, trace);
	ja__report_line_va(fmt, va_args);

	va_end(va_args);

	if (check_type == JA__ASSERTION) {
		exit(EXIT_FAILURE);
	}
}

void ja__cmp_fail(JACheckType check_type, JATrace trace, JAComparisonType cmp_type,
		const char *type_str, const char *type_fmt, const char *expr_a_str,
		const char *op_str, const char *expr_b_str,
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

	ja__report_trace(check_type, trace);
	ja__report_line("%s for %s of type `%s`", FAILURE_DESCRIPTIONS[check_type],
			COMPARISON_TYPE_STR[cmp_type], type_str);

	// "        Assertion: (<expr_a>) <op> (<expr_b>)"
	// "               ==> (<res_a>) <op> (<res_b>)"
	ja__report_line("Assertion: %s %s %s", expr_a_str, op_str, expr_b_str);
	ja__report_char('\t');
	ja__report("       ==> ");
	ja__report_va(type_fmt, va_args);
	ja__report(" %s ", op_str);
	ja__report_va(type_fmt, va_args);
	ja__report_char('\n');

	va_end(va_args);

	if (check_type == JA__ASSERTION) {
		exit(EXIT_FAILURE);
	}
}

void ja__report_trace(JACheckType check_type, JATrace trace)
{
	const char *CHECK_TYPE_DIAGNOSTIC_STR[] = {
		[JA__ASSERTION] = "assert",
		[JA__EXPECTATION] = "expect",
	};
	ja__report("[ja:%s] <%s:%s:%u>\n", CHECK_TYPE_DIAGNOSTIC_STR[check_type],
			trace.file, trace.func, trace.line);
}

void ja__report_line(const char *fmt, ...)
{
	va_list va_args;
	va_start(va_args, fmt);

	ja__report_line_va(fmt, va_args);

	va_end(va_args);
}

void ja__report_line_va(const char *fmt, va_list va_args)
{
	ja__report_char('\t');
	ja__report_va(fmt, va_args);
	ja__report_char('\n');
}

void ja__report(const char *fmt, ...)
{
	va_list va_args;
	va_start(va_args, fmt);

	ja__report_va(fmt, va_args);

	va_end(va_args);
}

void ja__report_va(const char *fmt, va_list va_args)
{
	vfprintf(stderr, fmt, va_args);
}

void ja__report_char(char c)
{
	putc(c, stderr);
}

#endif // JA_IMPLEMENTATION

#endif // ja_runtime_asserts_h
