#define JA_IMPLEMENTATION
#include <just-asserts/ja-runtime-asserts.h>

int main(void)
{
	ja_assert(1);
	ja_assert_msg(sizeof(long) == sizeof(long int),
			"`long` and `long int` should be the same type");

	// ja_assert(0); // <-- runtime error (aborts)
	
	ja_expect(1);

	// one of these will (probably) cause a runtime warning
	ja_expect_msg(sizeof(long) == sizeof(long long),
			"Expected `long` and `long long` to be the same size");
	ja_expect_msg(sizeof(long) == sizeof(int),
			"Expected `long` and `int` to be the same size");

#define ja_assert_comparison(T, a, OP, b) \
	do { \
		if (!JA_COMPARE(int, a, OP, b)) { \
			ja__report_trace("err"); \
			ja__report_msg("Failed assertion for comparison of type `" #T "`"); \
			ja__report_msg("Assertion: `" #a "` " #OP " `" #b "`"); \
			ja__report_msg("       ==> `" JA_PRI(T) "` " #OP " `" JA_PRI(T) "`", \
					JA_CAST(T, a), JA_CAST(T, b)); \
		} \
	} while (0)

	ja_assert_comparison(float, 8, !=, 3 + 5);

	return 0;
}
