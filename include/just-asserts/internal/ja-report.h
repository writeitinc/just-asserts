#ifndef ja_report_h
#define ja_report_h

#include <stdarg.h>

#include "ja-export.h"

typedef enum JAColorPolicy {
	JA_COLOR_POLICY_NOT_SET = -1,
	JA_COLOR_POLICY_NEVER   =  0,
	JA_COLOR_POLICY_ALWAYS  =  1,
	JA_COLOR_POLICY_AUTO    =  2,
} JAColorPolicy;

typedef enum JAColor {
	JA_COLOR_NONE,
	JA_COLOR_BLACK,
	JA_COLOR_DARK_RED,
	JA_COLOR_DARK_GREEN,
	JA_COLOR_DARK_YELLOW,
	JA_COLOR_DARK_BLUE,
	JA_COLOR_DARK_MAGENTA,
	JA_COLOR_DARK_CYAN,
	JA_COLOR_GREY1,
	JA_COLOR_GREY2,
	JA_COLOR_LIGHT_RED,
	JA_COLOR_LIGHT_GREEN,
	JA_COLOR_LIGHT_YELLOW,
	JA_COLOR_LIGHT_BLUE,
	JA_COLOR_LIGHT_MAGENTA,
	JA_COLOR_LIGHT_CYAN,
	JA_COLOR_LIGHT_WHITE,
} JAColor;

void ja__report(const char *str);
void ja__reportf(const char *fmt, ...);
void ja__reportf_va(const char *fmt, va_list va_args);
void ja__report_char(int c);
void ja__report_colored(JAColor color, const char *str);
void ja__reportf_colored(JAColor color, const char *fmt, ...);
void ja__reportf_va_colored(JAColor color, const char *fmt, va_list va_args);
void ja__report_char_colored(JAColor color, int c);

JA_EXPORT extern JAColorPolicy ja_color_policy;

#ifdef JA_IMPLEMENTATION

#include "ja-platform.h"

#if defined(JA_PLATFORM_POSIX)
# include <unistd.h>
#elif defined(JA_PLATFORM_WINDOWS)
# include <io.h>
#endif

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

JAColorPolicy ja_color_policy = JA_COLOR_POLICY_AUTO;

static bool should_output_color(void);

static const char *ANSI_COLOR_CODES[] = {
	[JA_COLOR_NONE]          = "\033[00m",
	[JA_COLOR_BLACK]         = "\033[30m",
	[JA_COLOR_DARK_RED]      = "\033[31m",
	[JA_COLOR_DARK_GREEN]    = "\033[32m",
	[JA_COLOR_DARK_YELLOW]   = "\033[33m",
	[JA_COLOR_DARK_BLUE]     = "\033[34m",
	[JA_COLOR_DARK_MAGENTA]  = "\033[35m",
	[JA_COLOR_DARK_CYAN]     = "\033[36m",
	[JA_COLOR_GREY1]         = "\033[37m",
	[JA_COLOR_GREY2]         = "\033[90m",
	[JA_COLOR_LIGHT_RED]     = "\033[91m",
	[JA_COLOR_LIGHT_GREEN]   = "\033[92m",
	[JA_COLOR_LIGHT_YELLOW]  = "\033[93m",
	[JA_COLOR_LIGHT_BLUE]    = "\033[94m",
	[JA_COLOR_LIGHT_MAGENTA] = "\033[95m",
	[JA_COLOR_LIGHT_CYAN]    = "\033[96m",
	[JA_COLOR_LIGHT_WHITE]   = "\033[97m",
};

// Prints a message to `stderr`.
void ja__report(const char *str)
{
	fputs(str, stderr);
}

// Prints a formatted message to `stderr`.
void ja__reportf(const char *fmt, ...)
{
	va_list va_args;
	va_start(va_args, fmt);

	ja__reportf_va(fmt, va_args);

	va_end(va_args);
}

// Prints a formatted message to `stderr`.
void ja__reportf_va(const char *fmt, va_list va_args)
{
	vfprintf(stderr, fmt, va_args);
}

// Prints a byte to `stderr`.
void ja__report_char(int c)
{
	putc(c, stderr);
}

void ja__report_colored(JAColor color, const char *str)
{
	bool output_color = should_output_color();

	if (output_color) {
		ja__report(ANSI_COLOR_CODES[color]);
	}

	fputs(str, stderr);

	if (output_color) {
		ja__report(ANSI_COLOR_CODES[JA_COLOR_NONE]);
	}
}

void ja__reportf_colored(JAColor color, const char *fmt, ...)
{
	va_list va_args;
	va_start(va_args, fmt);

	ja__reportf_va_colored(color, fmt, va_args);

	va_end(va_args);
}

void ja__reportf_va_colored(JAColor color, const char *fmt, va_list va_args)
{
	bool output_color = should_output_color();

	if (output_color) {
		ja__report(ANSI_COLOR_CODES[color]);
	}

	ja__reportf_va(fmt, va_args);

	if (output_color) {
		ja__report(ANSI_COLOR_CODES[JA_COLOR_NONE]);
	}
}

void ja__report_char_colored(JAColor color, int c)
{
	bool output_color = should_output_color();

	if (output_color) {
		ja__report(ANSI_COLOR_CODES[color]);
	}

	ja__report_char(c);

	if (output_color) {
		ja__report(ANSI_COLOR_CODES[JA_COLOR_NONE]);
	}
}

bool should_output_color(void)
{
	JAColorPolicy env_policy = JA_COLOR_POLICY_NOT_SET;
	const char *env_policy_str = getenv("JA_COLOR_POLICY");
	if (env_policy_str != NULL) {
		if (strcmp(env_policy_str, "always")
				== 0) {
			env_policy = JA_COLOR_POLICY_ALWAYS;
		} else if (strcmp(env_policy_str, "never")
				== 0) {
			env_policy = JA_COLOR_POLICY_NEVER;
		} else if (strcmp(env_policy_str, "auto")
				== 0) {
			env_policy = JA_COLOR_POLICY_AUTO;
		}
	}

	if (env_policy == JA_COLOR_POLICY_ALWAYS) {
		return true;
	}

	if (env_policy == JA_COLOR_POLICY_NEVER) {
		return false;
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

	return (bool)ja_color_policy;
}

#endif // JA_IMPLEMENTATION

#endif // ja_report_h
