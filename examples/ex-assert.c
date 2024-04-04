#define JA_IMPLEMENTATION
#include <just-asserts/ja-runtime-asserts.h>

int main(void)
{
	ja_assert(1);
	// ja_assert(0); // <-- runtime error (aborts)

	ja_expect(1);
	ja_expect(0);

	// one of these will (probably) cause a runtime warning
	ja_expect_msg(sizeof(long) == sizeof(long long),
			"Expected `long` and `long long` to be the same size");
	ja_expect_msg(sizeof(long) == sizeof(int),
			"Expected `long` and `int` to be the same size");

	ja_assert_comparison(float, 1.0f, !=, 1.5f);
	ja_expect_comparison(int, 1.0f, !=, 1.5f); // runtime warning

	return 0;
}
