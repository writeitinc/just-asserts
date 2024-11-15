#ifndef ja_report_h
#define ja_report_h

#include <stdarg.h>

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

#ifdef JA_IMPLEMENTATION

#include "ja-color-policy.h"

#include <stdbool.h>
#include <stdio.h>

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
	bool output_color = ja_outputting_color();

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
	bool output_color = ja_outputting_color();

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
	bool output_color = ja_outputting_color();

	if (output_color) {
		ja__report(ANSI_COLOR_CODES[color]);
	}

	ja__report_char(c);

	if (output_color) {
		ja__report(ANSI_COLOR_CODES[JA_COLOR_NONE]);
	}
}

#endif // JA_IMPLEMENTATION

#endif // ja_report_h

// License (MIT):
/*
 * Copyright 2024 shan <writeitinc99@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the “Software”), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
