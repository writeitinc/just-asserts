#ifndef ja_color_policy_h
#define ja_color_policy_h

#include <stdbool.h>

#include "ja-export.h"

typedef enum JAColorPolicy {
	JA_COLOR_POLICY_NOT_SET = -1,
	JA_COLOR_POLICY_NEVER   =  0,
	JA_COLOR_POLICY_ALWAYS  =  1,
	JA_COLOR_POLICY_AUTO    =  2,
} JAColorPolicy;

JA_EXPORT extern JAColorPolicy ja_color_policy;

JA_EXPORT extern JAColorPolicy ja_get_color_policy_from_env(void);
JA_EXPORT extern bool ja_outputting_color(void);

#ifdef JA_IMPLEMENTATION

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ja-platform.h"

#if defined(JA_PLATFORM_POSIX)
# include <unistd.h>
#elif defined(JA_PLATFORM_WINDOWS)
# include <io.h>
#endif

JAColorPolicy ja_get_color_policy_from_env(void)
{
	JAColorPolicy env_policy = JA_COLOR_POLICY_NOT_SET;

	const char *env_policy_str = getenv("JA_COLOR_POLICY");
	if (env_policy_str != NULL) {
		if (strcmp(env_policy_str, "always")
				== 0) {
			return JA_COLOR_POLICY_ALWAYS;
		}
		if (strcmp(env_policy_str, "never")
				== 0) {
			return JA_COLOR_POLICY_NEVER;
		}
		if (strcmp(env_policy_str, "auto")
				== 0) {
			return JA_COLOR_POLICY_AUTO;
		}
	}

	return env_policy;
}

bool ja_outputting_color(void)
{
	JAColorPolicy env_policy = ja_get_color_policy_from_env();

	if (env_policy == JA_COLOR_POLICY_ALWAYS
			|| env_policy == JA_COLOR_POLICY_NEVER) {
		return (bool)env_policy;
	}

	if (ja_color_policy == JA_COLOR_POLICY_AUTO
			|| env_policy == JA_COLOR_POLICY_AUTO) {
#if defined(JA_PLATFORM_POSIX)
		return isatty(fileno(stderr));
#elif defined(JA_PLATFORM_WINDOWS)
		return _isatty(_fileno(stderr));
#else
		return false;
#endif
	}

	if (ja_color_policy == JA_COLOR_POLICY_ALWAYS
			|| ja_color_policy == JA_COLOR_POLICY_NEVER) {
		return (bool)ja_color_policy;
	}

	return false;
}

JAColorPolicy ja_color_policy = JA_COLOR_POLICY_AUTO;

#endif

#endif // ja_color_policy_h
