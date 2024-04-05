#ifndef ja_template_h
#define ja_template_h

#define JA_TYPE(T) JA_TYPE_##T
#define JA_TYPE_STR(T) JA__STR(JA_TYPE(T))

#define JA_FMT(T) JA_FMT_##T
#define JA_FMT_ARGS(T, v) JA_FMT_ARGS_##T(v)

#define JA_COMPARE(T, a, OP, b) JA_COMPARE_##T(a, OP, b)
#define JA_EQUALS(T, a, b) JA_EQUALS_##T(a, b)

#define JA__STR(T) JA__STR_(T)
#define JA__STR_(T) #T

// Implementations

#define JA_TYPE__Bool _Bool
#define JA_COMPARE__Bool(a, OP, b) JA_CASTED_COMPARE_ARITHMETIC(_Bool, a, OP, b)
#define JA_EQUALS__Bool(a, b) JA_CASTED_EQUALS_ARITHMETIC(_Bool, a, b)
#define JA_FMT__Bool "%s"
#define JA_FMT_ARGS__Bool(v) (((_Bool)v) ? "true" : "false")
#define JA_TYPE_bool JA_TYPE__Bool
#define JA_COMPARE_bool JA_COMPARE__Bool
#define JA_EQUALS_bool JA_EQUALS__Bool
#define JA_FMT_bool JA_FMT__Bool
#define JA_FMT_ARGS_bool JA_FMT_ARGS__Bool

#define JA_TYPE_char char
#define JA_COMPARE_char(a, OP, b) JA_CASTED_COMPARE_ARITHMETIC(char, a, OP, b)
#define JA_EQUALS_char(a, b) JA_CASTED_EQUALS_ARITHMETIC(char, a, b)
#define JA_FMT_char "%c"
#define JA_FMT_ARGS_char(v) (char)(v)

#define JA_TYPE_signed_char signed char
#define JA_COMPARE_signed_char(a, OP, b) JA_CASTED_COMPARE_ARITHMETIC(signed char, a, OP, b)
#define JA_EQUALS_signed_char(a, b) JA_CASTED_EQUALS_ARITHMETIC(signed char, a, b)
#define JA_FMT_signed_char "%c"
#define JA_FMT_ARGS_signed_char(v) (signed char)(v)

#define JA_TYPE_unsigned_char unsigned char
#define JA_COMPARE_unsigned_char(a, OP, b) JA_CASTED_COMPARE_ARITHMETIC(unsigned char, a, OP, b)
#define JA_EQUALS_unsigned_char(a, b) JA_CASTED_EQUALS_ARITHMETIC(unsigned char, a, b)
#define JA_FMT_unsigned_char "%c"
#define JA_FMT_ARGS_unsigned_char(v) (unsigned char)(v)

#define JA_TYPE_short short
#define JA_COMPARE_short(a, OP, b) JA_CASTED_COMPARE_ARITHMETIC(short, a, OP, b)
#define JA_EQUALS_short(a, b) JA_CASTED_EQUALS_ARITHMETIC(short, a, b)
#define JA_FMT_short "%hd"
#define JA_FMT_ARGS_short(v) (short)(v)

#define JA_TYPE_unsigned_short unsigned short
#define JA_COMPARE_unsigned_short(a, OP, b) JA_CASTED_COMPARE_ARITHMETIC(unsigned short, a, OP, b)
#define JA_EQUALS_unsigned_short(a, b) JA_CASTED_EQUALS_ARITHMETIC(unsigned short, a, b)
#define JA_FMT_unsigned_short "%hu"
#define JA_FMT_ARGS_unsigned_short(v) (unsigned short)(v)

#define JA_TYPE_int int
#define JA_COMPARE_int(a, OP, b) JA_CASTED_COMPARE_ARITHMETIC(int, a, OP, b)
#define JA_EQUALS_int(a, b) JA_CASTED_EQUALS_ARITHMETIC(int, a, b)
#define JA_FMT_int "%d"
#define JA_FMT_ARGS_int(v) (int)(v)

#define JA_TYPE_unsigned_int unsigned int
#define JA_COMPARE_unsigned_int(a, OP, b) JA_CASTED_COMPARE_ARITHMETIC(unsigned int, a, OP, b)
#define JA_EQUALS_unsigned_int(a, b) JA_CASTED_EQUALS_ARITHMETIC(unsigned int, a, b)
#define JA_FMT_unsigned_int "%u"
#define JA_FMT_ARGS_unsigned_int(v) (unsigned int)(v)

#define JA_TYPE_long long
#define JA_COMPARE_long(a, OP, b) JA_CASTED_COMPARE_ARITHMETIC(long, a, OP, b)
#define JA_EQUALS_long(a, b) JA_CASTED_EQUALS_ARITHMETIC(long, a, b)
#define JA_FMT_long "%ld"
#define JA_FMT_ARGS_long(v) (long)(v)

#define JA_TYPE_unsigned_long unsigned long
#define JA_COMPARE_unsigned_long(a, OP, b) JA_CASTED_COMPARE_ARITHMETIC(unsigned long, a, OP, b)
#define JA_EQUALS_unsigned_long(a, b) JA_CASTED_EQUALS_ARITHMETIC(unsigned long, a, b)
#define JA_FMT_unsigned_long "%lu"
#define JA_FMT_ARGS_unsigned_long(v) (unsigned long)(v)

#define JA_TYPE_long_long long long
#define JA_COMPARE_long_long(a, OP, b) JA_CASTED_COMPARE_ARITHMETIC(long long, a, OP, b)
#define JA_EQUALS_long_long(a, b) JA_CASTED_EQUALS_ARITHMETIC(long long, a, b)
#define JA_FMT_long_long "%lld"
#define JA_FMT_ARGS_long_long(v) (long long)(v)

#define JA_TYPE_unsigned_long_long unsigned long long
#define JA_COMPARE_unsigned_long_long(a, OP, b) JA_CASTED_COMPARE_ARITHMETIC(unsigned long long, a, OP, b)
#define JA_EQUALS_unsigned_long_long(a, b) JA_CASTED_EQUALS_ARITHMETIC(unsigned long long, a, b)
#define JA_FMT_unsigned_long_long "%llu"
#define JA_FMT_ARGS_unsigned_long_long(v) (unsigned long long)(v)

#define JA_TYPE_float float
#define JA_COMPARE_float(a, OP, b) JA_CASTED_COMPARE_ARITHMETIC(float, a, OP, b)
#define JA_EQUALS_float(a, b) JA_CASTED_EQUALS_ARITHMETIC(float, a, b)
#define JA_FMT_float "%f"
#define JA_FMT_ARGS_float(v) (float)(v)

#define JA_TYPE_double double
#define JA_COMPARE_double(a, OP, b) JA_CASTED_COMPARE_ARITHMETIC(double, a, OP, b)
#define JA_EQUALS_double(a, b) JA_CASTED_EQUALS_ARITHMETIC(double, a, b)
#define JA_FMT_double "%lf"
#define JA_FMT_ARGS_double(v) (double)(v)

#define JA_TYPE_long_double long double
#define JA_COMPARE_long_double(a, OP, b) JA_CASTED_COMPARE_ARITHMETIC(long double, a, OP, b)
#define JA_EQUALS_long_double(a, b) JA_CASTED_EQUALS_ARITHMETIC(long double, a, b)
#define JA_FMT_long_double "%Lf"
#define JA_FMT_ARGS_long_double(v) (long double)(v)

#define JA_TYPE_ptr void *
#define JA_COMPARE_ptr(a, OP, b) JA_CASTED_COMPARE_ARITHMETIC(void *, a, OP, b)
#define JA_EQUALS_ptr(a, b) JA_CASTED_EQUALS_ARITHMETIC(void *, a, b)
#define JA_FMT_ptr "%p"
#define JA_FMT_ARGS_ptr(v) (void *)(v)

int strcmp(const char *a, const char *b);
#define JA_TYPE_cstr const char *
#define JA_COMPARE_cstr(a, OP, b) (strcmp(a, b) OP 0)
#define JA_EQUALS_cstr(a, b) (strcmp(a, b) == 0)
#define JA_FMT_cstr "\"%s\""
#define JA_FMT_ARGS_cstr(v) (const char *)(v)

#define JA_COMPARE_ARITHMETIC(a, OP, b) ((a) OP (b))
#define JA_EQUALS_ARITHMETIC(a, b) ((a) == (b))
#define JA_CASTED_COMPARE_ARITHMETIC(T, a, OP, b) ((T)(a) OP (T)(b))
#define JA_CASTED_EQUALS_ARITHMETIC(T, a, b) ((T)(a) == (T)(b))

#endif // ja_template_h
