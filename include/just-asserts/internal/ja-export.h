#ifndef ja_export_h
#define ja_export_h

#if defined(_WIN32) && !defined(JA_STATIC_LIB)
# if defined(JA_IMPLEMENTATION)
#  define JA_EXPORT __declspec(dllexport)
# else
#  define JA_EXPORT __declspec(dllimport)
# endif
#elif defined(__GNUC__) && !defined(JA_STATIC_LIB)
# define JA_EXPORT __attribute__((visibility("default")))
#else
# define JA_EXPORT
#endif

#endif // ja_export_h
