#ifndef ja_platform_h
#define ja_platform_h

#if defined(_WIN32)
# define JA_PLATFORM_WINDOWS
#elif defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))
# define JA_PLATFORM_POSIX
#endif

#endif // ja_platform_h
