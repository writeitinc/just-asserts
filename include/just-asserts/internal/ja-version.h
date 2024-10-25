#ifndef ja_version_h
#define ja_version_h

#include "ja-export.h"

#define JA_HEADER_VERSION_MAJOR 1
#define JA_HEADER_VERSION_MINOR 0
#define JA_HEADER_VERSION_PATCH 1
#define JA_HEADER_VERSION_STRING JA__VERSION_TO_STRING( \
		JA_HEADER_VERSION_MAJOR, \
		JA_HEADER_VERSION_MINOR, \
		JA_HEADER_VERSION_PATCH)

JA_EXPORT extern const int JA_LIB_VERSION_MAJOR;
JA_EXPORT extern const int JA_LIB_VERSION_MINOR;
JA_EXPORT extern const int JA_LIB_VERSION_PATCH;
JA_EXPORT extern const char JA_LIB_VERSION_STRING[];

#define JA__VERSION_TO_STRING(major, minor, patch) JA__VERSION_TO_STRING_(major, minor, patch)
#define JA__VERSION_TO_STRING_(major, minor, patch) #major "." #minor "." #patch

#ifdef JA_IMPLEMENTATION

const int JA_LIB_VERSION_MAJOR = JA_HEADER_VERSION_MAJOR;
const int JA_LIB_VERSION_MINOR = JA_HEADER_VERSION_MINOR;
const int JA_LIB_VERSION_PATCH = JA_HEADER_VERSION_PATCH;
const char JA_LIB_VERSION_STRING[] = JA_HEADER_VERSION_STRING;

#endif // JA_IMPLEMENTATION

#endif // ja_version_h

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
