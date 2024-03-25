#ifndef ja_runtime_asserts_h
#define ja_runtime_asserts_h

#if JA_DEBUG
# define JA__DEBUG_ONLY(expr) (expr)
#else
# define JA__DEBUG_ONLY(expr) (void)0
#endif

#define JA__TRACE __FILE__, __func__, __LINE__

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

void ja__assert_fail(const char *file, const char *func, unsigned int line, const char *fmt, ...);
void ja__expect_fail(const char *file, const char *func, unsigned int line, const char *fmt, ...);
void ja__report_trace(const char *severity, const char *file, const char *func, unsigned int line);
void ja__report_line(const char *fmt, ...);

#ifdef JA_IMPLEMENTATION

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

static void ja__report_line_va(const char *fmt, va_list va_args);

void ja__assert_fail(const char *file, const char *func, unsigned int line, const char *fmt, ...)
{
	va_list va_args;
	va_start(va_args, fmt);

	ja__report_trace("err", file, func, line);
	ja__report_line_va(fmt, va_args);

	va_end(va_args);
	exit(EXIT_FAILURE);
}

void ja__expect_fail(const char *file, const char *func, unsigned int line, const char *fmt, ...)
{
	va_list va_args;
	va_start(va_args, fmt);

	ja__report_trace("warn", file, func, line);
	ja__report_line_va(fmt, va_args);

	va_end(va_args);
}

void ja__report_trace(const char *severity, const char *file, const char *func, unsigned int line)
{
	fprintf(stderr, "[ja:%s] <%s:%s:%u>\n", severity, file, func, line);
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
	putc('\t', stderr);
	vfprintf(stderr, fmt, va_args);
	putc('\n', stderr);
}

#endif // JA_IMPLEMENTATION

#endif // ja_runtime_asserts_h
