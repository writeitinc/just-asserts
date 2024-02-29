#define JA_IMPLEMENTATION
#include <just-asserts/just-asserts.h>

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

	return 0;
}
