#include <just-asserts/ja-static-asserts.h>

#include <stddef.h>

ja_static_assert(1);
ja_static_assert_msg(2 + 2 != 5, "Literally 1987.");

struct S {
	int i;
#ifdef JA_STATIC_ASSERT_IN_STRUCT_DECL
	ja_static_assert_msg(1, "Honestly, I'm not really sure if this feature has any real use.");
#endif
};

int main(void)
{
	ja_static_assert(1);
	ja_static_assert_msg(sizeof(size_t) == sizeof(ptrdiff_t),
			"Expected `size_t` and `ptrdiff_t` to be the same size.");

	return 0;
}
