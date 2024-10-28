#include <stddef.h>
#include <stdio.h>

#include <just-asserts/ja-runtime-asserts.h>

static void print_info(void);
static const char *color_policy_to_str(JAColorPolicy color_policy);

int main(void)
{
	ja_color_policy = JA_COLOR_POLICY_ALWAYS;
	print_info();
	ja_expect(0); // prints warning with color formatting

	printf("\n---\n\n");

	ja_color_policy = JA_COLOR_POLICY_NEVER;
	print_info();
	ja_expect(0); // prints warning without color formatting

	printf("\n---\n\n");

	ja_color_policy = JA_COLOR_POLICY_AUTO;
	print_info();
	ja_expect(0); // prints warning without color formatting
}

void print_info(void)
{
	printf(" Runtime color policy: %s\n", color_policy_to_str(ja_color_policy));
	printf(" Environment color policy: %s\n",
			color_policy_to_str(ja_get_color_policy_from_env()));
	printf(" Outputting in color: %s\n", ja_outputting_color() ? "yes" : "no");
}

const char *color_policy_to_str(JAColorPolicy color_policy)
{
	static const char *STRINGS[] = {
		[JA_COLOR_POLICY_NEVER]  = "never",
		[JA_COLOR_POLICY_ALWAYS] = "always",
		[JA_COLOR_POLICY_AUTO]   = "auto",
	};
	static const size_t nstrings = sizeof(STRINGS) / sizeof(STRINGS[0]);

	if (color_policy < 0
			|| color_policy > (int)nstrings) {
		return "not set";
	}

	return STRINGS[color_policy];
}
