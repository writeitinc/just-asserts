#ifndef ja_runtime_asserts_h
#define ja_runtime_asserts_h

#if JA_DEBUG
# define JA__DEBUG_ONLY(expr) (expr)
#else
# define JA__DEBUG_ONLY(expr) (void)0
#endif

#define JA__WARN(fmt, ...) ja__warn(__FILE__, __LINE__, __func__, fmt, __VA_ARGS__)
#define JA__ERROR(fmt, ...) ja__error(__FILE__, __LINE__, __func__, fmt, __VA_ARGS__)

#define ja_assert(expr) ja_assert_msg(expr, "Failed assertion")
#define ja_expect(expr) ja_expect_msg(expr, "Unmet expectation")
#define ja_assert_msg(expr, msg) ((expr) \
		? (void)0 \
		: JA__ERROR("%s: `%s`", msg, #expr))
#define ja_expect_msg(expr, msg) ((expr) \
		? (void)0 \
		: JA__WARN("%s: `%s`", msg, #expr))

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

void ja__warn(const char *file, unsigned int line, const char *func, const char *fmt, ...);
void ja__error(const char *file, unsigned int line, const char *func, const char *fmt, ...);

#ifdef JA_IMPLEMENTATION

# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>

static void ja__report(const char *report_type, const char *file, unsigned int line,
		const char *func, const char *fmt, va_list va_args);

void ja__warn(const char *file, unsigned int line, const char *func, const char *fmt, ...)
{
	va_list va_args;
	va_start(va_args, fmt);

	ja__report("warn", file, line, func, fmt, va_args);

	va_end(va_args);
}

void ja__error(const char *file, unsigned int line, const char *func, const char *fmt, ...)
{
	va_list va_args;
	va_start(va_args, fmt);

	ja__report("err", file, line, func, fmt, va_args);

	va_end(va_args);

	exit(EXIT_FAILURE);
}

void ja__report(const char *report_type, const char *file, unsigned int line, const char *func,
		const char *fmt, va_list va_args)
{
	fprintf(stderr, "[ja:%s] <%s:%s:%u>\n", report_type, file, func, line);
	fputc('\t', stderr);
	vfprintf(stderr, fmt, va_args);
	fputc('\n', stderr);
}

#endif // JA_IMPLEMENTATION

#endif // ja_runtime_asserts_h
