#ifndef ja_runtime_asserts_h
#define ja_runtime_asserts_h

#include "ja-templates.h"

#if JA_DEBUG
# define JA__DEBUG_ONLY(expr) (expr)
#else
# define JA__DEBUG_ONLY(expr) (void)0
#endif

#define ja_assert(expr) ja_assert_msg(expr, "Failed assertion")
#define ja_expect(expr) ja_expect_msg(expr, "Unmet expectation")
#define ja_assert_msg(expr, ...) ((expr) \
		? (void)0 \
		: ja__assert_fail(JA__TRACE, __VA_ARGS__))
#define ja_expect_msg(expr, ...) ((expr) \
		? (void)0 \
		: ja__expect_fail(JA__TRACE, __VA_ARGS__))

#define ja_dbg_assert(expr) JA__DEBUG_ONLY(ja_assert(expr))
#define ja_dbg_assert_msg(expr, msg) JA__DEBUG_ONLY(ja_assert_msg(expr, msg))
#define ja_dbg_expect(expr) JA__DEBUG_ONLY(ja_expect(expr))
#define ja_dbg_expect_msg(expr, msg) JA__DEBUG_ONLY(ja_expect_msg(expr, msg))

#if JA_DEBUG
# define ja_assume_true(expr) (ja_dbg_expect_msg((expr), "Unmet assumption"), (expr))
# define ja_assume_false(expr) (ja_dbg_expect_msg(!(expr), "Unmet assumption"), (expr))
#else
# define ja_assume_true(expr) (1)
# define ja_assume_false(expr) (0)
#endif

#define ja_assert_comparison(T, a, OP, b) (JA_COMPARE(T, a, OP, b) \
		? (void)0 \
		: ja__assert_comparison_fail(JA__TRACE, JA_TYPE_STR(T), JA_FMT(T), #a, #OP, #b, \
					JA_FMT_ARGS(T, a), JA_FMT_ARGS(T, b)))
#define ja_expect_comparison(T, a, OP, b) (JA_COMPARE(T, a, OP, b) \
		? (void)0 \
		: ja__expect_comparison_fail(JA__TRACE, JA_TYPE_STR(T), JA_FMT(T), #a, #OP, #b, \
					JA_FMT_ARGS(T, a), JA_FMT_ARGS(T, b)))

#define ja_assert_eq(T, a, b) (JA_EQUALS(T, a, b) \
		? (void)0 \
		: ja__assert_eq_fail(JA__TRACE, JA_TYPE_STR(T), JA_FMT(T), #a, #b, \
					JA_FMT_ARGS(T, a), JA_FMT_ARGS(T, b)))
#define ja_expect_eq(T, a, b) (JA_EQUALS(T, a, b) \
		? (void)0 \
		: ja__expect_eq_fail(JA__TRACE, JA_TYPE_STR(T), JA_FMT(T), #a, #b, \
					JA_FMT_ARGS(T, a), JA_FMT_ARGS(T, b)))
#define ja_assert_neq(T, a, b) (!JA_EQUALS(T, a, b) \
		? (void)0 \
		: ja__assert_neq_fail(JA__TRACE, JA_TYPE_STR(T), JA_FMT(T), #a, #b, \
					JA_FMT_ARGS(T, a), JA_FMT_ARGS(T, b)))
#define ja_expect_neq(T, a, b) (!JA_EQUALS(T, a, b) \
		? (void)0 \
		: ja__expect_neq_fail(JA__TRACE, JA_TYPE_STR(T), JA_FMT(T), #a, #b, \
					JA_FMT_ARGS(T, a), JA_FMT_ARGS(T, b)))

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

void ja__assert_fail(JATrace trace, const char *fmt, ...);
void ja__expect_fail(JATrace trace, const char *fmt, ...);
void ja__assert_comparison_fail(JATrace trace, const char *type_str, const char *type_fmt,
		const char *expr_a_str, const char *op_str, const char *expr_b_str,
		... /* T res_a, T res_b */);
void ja__expect_comparison_fail(JATrace trace, const char *type_str, const char *type_fmt,
		const char *expr_a_str, const char *op_str, const char *expr_b_str,
		... /* T res_a, T res_b */);
void ja__assert_eq_fail(JATrace trace, const char *type_str, const char *type_fmt,
		const char *expr_a_str, const char *expr_b_str,
		... /* T res_a, T res_b */);
void ja__expect_eq_fail(JATrace trace, const char *type_str, const char *type_fmt,
		const char *expr_a_str, const char *expr_b_str,
		... /* T res_a, T res_b */);
void ja__assert_neq_fail(JATrace trace, const char *type_str, const char *type_fmt,
		const char *expr_a_str, const char *expr_b_str,
		... /* T res_a, T res_b */);
void ja__expect_neq_fail(JATrace trace, const char *type_str, const char *type_fmt,
		const char *expr_a_str, const char *expr_b_str,
		... /* T res_a, T res_b */);

#ifdef JA_IMPLEMENTATION

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

static void ja__report_comparison_fail(const char *type_str, const char *type_fmt,
		const char *expr_a_str, const char *op_str, const char *expr_b_str,
		va_list va_args);
static void ja__report_trace(const char *severity, JATrace trace);
static void ja__report_line(const char *fmt, ...);
static void ja__report(const char *fmt, ...);
static void ja__report_line_va(const char *fmt, va_list va_args);
static void ja__report_va(const char *fmt, va_list va_args);
static void ja__report_char(char c);

void ja__assert_fail(JATrace trace, const char *fmt, ...)
{
	va_list va_args;
	va_start(va_args, fmt);

	ja__report_trace("err", trace);
	ja__report_line_va(fmt, va_args);

	va_end(va_args);
	exit(EXIT_FAILURE);
}

void ja__expect_fail(JATrace trace, const char *fmt, ...)
{
	va_list va_args;
	va_start(va_args, fmt);

	ja__report_trace("warn", trace);
	ja__report_line_va(fmt, va_args);

	va_end(va_args);
}

void ja__assert_comparison_fail(JATrace trace, const char *type_str, const char *type_fmt,
		const char *expr_a_str, const char *op_str, const char *expr_b_str,
		... /* T res_a, T res_b */)
{
	va_list va_args;
	va_start(va_args, expr_b_str);

	ja__report_trace("err", trace);
	ja__report_line("Failed assertion for comparison of type `%s`", type_str);
	ja__report_comparison_fail(type_str, type_fmt, expr_a_str, op_str, expr_b_str, va_args);

	va_end(va_args);
	exit(EXIT_FAILURE);
}

void ja__expect_comparison_fail(JATrace trace, const char *type_str, const char *type_fmt,
		const char *expr_a_str, const char *op_str, const char *expr_b_str,
		... /* T res_a, T res_b */)
{
	va_list va_args;
	va_start(va_args, expr_b_str);

	ja__report_trace("warn", trace);
	ja__report_line("Unmet expectation for comparison of type `%s`", type_str);
	ja__report_comparison_fail(type_str, type_fmt, expr_a_str, op_str, expr_b_str, va_args);

	va_end(va_args);
}

void ja__assert_eq_fail(JATrace trace, const char *type_str, const char *type_fmt,
		const char *expr_a_str, const char *expr_b_str,
		... /* T res_a, T res_b */)
{
	va_list va_args;
	va_start(va_args, expr_b_str);

	ja__report_trace("err", trace);
	ja__report_line("Failed assertion for equality of type `%s`", type_str);
	ja__report_comparison_fail(type_str, type_fmt, expr_a_str, "==", expr_b_str, va_args);

	va_end(va_args);
	exit(EXIT_FAILURE);
}

void ja__expect_eq_fail(JATrace trace, const char *type_str, const char *type_fmt,
		const char *expr_a_str, const char *expr_b_str,
		... /* T res_a, T res_b */)
{
	va_list va_args;
	va_start(va_args, expr_b_str);

	ja__report_trace("warn", trace);
	ja__report_line("Unmet expectation for equality of type `%s`", type_str);
	ja__report_comparison_fail(type_str, type_fmt, expr_a_str, "==", expr_b_str, va_args);

	va_end(va_args);
}

void ja__assert_neq_fail(JATrace trace, const char *type_str, const char *type_fmt,
		const char *expr_a_str, const char *expr_b_str,
		... /* T res_a, T res_b */)
{
	va_list va_args;
	va_start(va_args, expr_b_str);

	ja__report_trace("err", trace);
	ja__report_line("Failed assertion for inequality of type `%s`", type_str);
	ja__report_comparison_fail(type_str, type_fmt, expr_a_str, "!=", expr_b_str, va_args);

	va_end(va_args);
	exit(EXIT_FAILURE);
}

void ja__expect_neq_fail(JATrace trace, const char *type_str, const char *type_fmt,
		const char *expr_a_str, const char *expr_b_str,
		... /* T res_a, T res_b */)
{
	va_list va_args;
	va_start(va_args, expr_b_str);

	ja__report_trace("warn", trace);
	ja__report_line("Unmet expectation for inequality of type `%s`", type_str);
	ja__report_comparison_fail(type_str, type_fmt, expr_a_str, "!=", expr_b_str, va_args);

	va_end(va_args);
}

void ja__report_comparison_fail(const char *type_str, const char *type_fmt,
		const char *expr_a_str, const char *op_str, const char *expr_b_str, va_list va_args)
{
	// "        Assertion: (<expr_a>) <op> (<expr_b>)"
	// "               ==> (<res_a>) <op> (<res_b>)"
	ja__report_line("Assertion: (%s)(%s) %s (%s)(%s)", type_str, expr_a_str, op_str, type_str,
			expr_b_str);
	ja__report_char('\t');
	ja__report("       ==> ");
	ja__report_va(type_fmt, va_args);
	ja__report(" %s ", op_str);
	ja__report_va(type_fmt, va_args);
	ja__report_char('\n');
}

void ja__report_trace(const char *severity, JATrace trace)
{
	ja__report("[ja:%s] <%s:%s:%u>\n", severity, trace.file, trace.func, trace.line);
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
