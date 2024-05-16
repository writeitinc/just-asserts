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
