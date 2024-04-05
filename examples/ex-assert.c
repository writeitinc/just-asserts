#define JA_INCLUDE_STD_HEADERS
#define JA_IMPLEMENTATION
#include <just-asserts/ja-runtime-asserts.h>

typedef struct Vec2D {
	float x;
	float y;
} Vec2D;

#define JA_TYPE_Vec2D Vec2D
#define JA_EQUALS_Vec2D(a, b) ((a).x == (b).x && (a).y == (b).y)
#define JA_FMT_Vec2D "[%g, %g]"
#define JA_FMT_ARGS_Vec2D(v) (v).x, (v).y

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

	ja_assert_cmp(float, 1.0f, !=, 1.5f);
	ja_expect_cmp(int, 1.0f, !=, 1.5f); // runtime warning

	ja_assert_eq(float, 1.0f, 1.0f);
	ja_expect_eq(int, 2 + 2, 5); // runtime warning

	ja_assert_neq(float, 1.0f, 1.5f);
	ja_expect_neq(int, 1.0f, 1.5f); // runtime warning

	Vec2D vec = { 2, 1.5 };
	ja_expect_eq(Vec2D, vec, ((Vec2D){ 2, 1.5 })); // compound literals require parentheses
	ja_expect_eq(Vec2D, ((Vec2D){ 1, 2 }), ((Vec2D){ 2, 1 })); // runtime warning

	ja_expect_eq(ptr, &vec, &vec.x);
	ja_expect_eq(ptr, &vec, &vec.y); // runtime warning

	ja_expect_eq(cstr, "deadbeef", "deadbeef");
	ja_expect_eq(cstr, "deadbeef", "feedbeef");

	return 0;
}
