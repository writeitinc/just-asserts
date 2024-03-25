#ifndef ja_runtime_asserts_h
#define ja_runtime_asserts_h

#include <stdio.h>
#include <stdlib.h>

#if !defined(JA_DEBUG)
# define JA_DEBUG 0
#endif

#if JA_DEBUG
# define JA__DEBUG_ONLY(expr) (expr)
#else
# define JA__DEBUG_ONLY(expr) (void)0
#endif

#define ja_assert(expr) ja_assert_msg(expr, "Failed assertion")
#define ja_expect(expr) ja_expect_msg(expr, "Unmet expectation")
#define ja_assert_msg(expr, ...) ((expr) \
		? (void)0 \
		: (void)( \
			ja__report_trace("err"), \
			ja__report_msg(__VA_ARGS__), \
			ja__report_char('\n'), \
			exit(EXIT_FAILURE), \
			(void)0 \
		))
#define ja_expect_msg(expr, ...) ((expr) \
		? (void)0 \
		: (void)( \
			ja__report_trace("warn"), \
			ja__report_msg(__VA_ARGS__), \
			ja__report_char('\n'), \
			(void)0 \
		))

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

#define ja__report(...) fprintf(stderr, __VA_ARGS__)
#define ja__report_char(c) putc((c), stderr)
#define ja__report_trace(severity) \
	ja__report("[ja:%s] <%s:%s:%u>\n", severity, __FILE__, __func__, __LINE__)
#define ja__report_msg(...) ( \
		ja__report_char('\t'), \
		ja__report(__VA_ARGS__), \
		ja__report_char('\n'))

#define JA_CAST(T, v) (JA_TYPE(T))(v)
#define JA_TYPE(T) JA__CAT(JA_TYPE_, T)
#define JA_PRI(T) JA__CAT(JA_PRI_, T)
#define JA_PRI_ARGS(T, v) JA__CAT(JA_PRI_ARGS_, T)(v)
#define JA_COMPARE(T, a, OP, b) JA__CAT(JA_COMPARE_, T)(a, OP, b)

#define JA_TYPE_int int
#define JA_COMPARE_int(a, OP, b) JA_COMPARE_ARITHMETIC(int, a, OP, b)
#define JA_PRI_int "%d"
#define JA_PRI_ARGS_int(v) (int)(v)

#define JA_TYPE_float float
#define JA_COMPARE_float(a, OP, b) JA_COMPARE_ARITHMETIC(float, a, OP, b)
#define JA_PRI_float "%f"
#define JA_PRI_ARGS_float(v) (float)(v)

#define JA_COMPARE_ARITHMETIC(T, a, OP, b) ((JA_TYPE(T))(a) OP (JA_TYPE(T))(b))

#define JA__CAT(a, b) JA__CAT_I(a, b)
#define JA__CAT_I(a, b) a##b

#endif // ja_runtime_asserts_h
