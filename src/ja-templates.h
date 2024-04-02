#ifndef ja_template_h
#define ja_template_h

#define JA_TYPE(T) JA_TYPE_##T
#define JA_TYPE_STR(T) JA__STR(JA_TYPE(T))

#define JA_CAST(T, v) (JA_TYPE(T))(v)

#define JA_FMT(T) JA_FMT_##T
#define JA_FMT_ARGS(T, v) JA_FMT_ARGS_##T(JA_CAST(T, v))

#define JA_COMPARE(T, a, OP, b) JA_COMPARE_##T(JA_CAST(T, a), OP, JA_CAST(T, b))
#define JA_EQUALS(T, a, b) JA_EQUALS_##T(JA_CAST(T, a), JA_CAST(T, b))

#define JA__STR(T) JA__STR_(T)
#define JA__STR_(T) #T

// Implementations

#define JA_TYPE_char char
#define JA_COMPARE_char(a, OP, b) JA_COMPARE_ARITHMETIC(a, OP, b)
#define JA_EQUALS_char(a, b) JA_EQUALS_ARITHMETIC(a, b)
#define JA_FMT_char "%c"
#define JA_FMT_ARGS_char(v) v

#define JA_TYPE_signed_char signed char
#define JA_COMPARE_signed_char(a, OP, b) JA_COMPARE_ARITHMETIC(a, OP, b)
#define JA_EQUALS_signed_char(a, b) JA_EQUALS_ARITHMETIC(a, b)
#define JA_FMT_signed_char "%c"
#define JA_FMT_ARGS_signed_char(v) v

#define JA_TYPE_unsigned_char unsigned char
#define JA_COMPARE_unsigned_char(a, OP, b) JA_COMPARE_ARITHMETIC(a, OP, b)
#define JA_EQUALS_unsigned_char(a, b) JA_EQUALS_ARITHMETIC(a, b)
#define JA_FMT_unsigned_char "%c"
#define JA_FMT_ARGS_unsigned_char(v) v

#define JA_TYPE_short short
#define JA_COMPARE_short(a, OP, b) JA_COMPARE_ARITHMETIC(a, OP, b)
#define JA_EQUALS_short(a, b) JA_EQUALS_ARITHMETIC(a, b)
#define JA_FMT_short "%hd"
#define JA_FMT_ARGS_short(v) v

#define JA_TYPE_unsigned_short unsigned short
#define JA_COMPARE_unsigned_short(a, OP, b) JA_COMPARE_ARITHMETIC(a, OP, b)
#define JA_EQUALS_unsigned_short(a, b) JA_EQUALS_ARITHMETIC(a, b)
#define JA_FMT_unsigned_short "%hu"
#define JA_FMT_ARGS_unsigned_short(v) v

#define JA_TYPE_int int
#define JA_COMPARE_int(a, OP, b) JA_COMPARE_ARITHMETIC(a, OP, b)
#define JA_EQUALS_int(a, b) JA_EQUALS_ARITHMETIC(a, b)
#define JA_FMT_int "%d"
#define JA_FMT_ARGS_int(v) v

#define JA_TYPE_unsigned_int unsigned int
#define JA_COMPARE_unsigned_int(a, OP, b) JA_COMPARE_ARITHMETIC(a, OP, b)
#define JA_EQUALS_unsigned_int(a, b) JA_EQUALS_ARITHMETIC(a, b)
#define JA_FMT_unsigned_int "%u"
#define JA_FMT_ARGS_unsigned_int(v) v

#define JA_TYPE_long long
#define JA_COMPARE_long(a, OP, b) JA_COMPARE_ARITHMETIC(a, OP, b)
#define JA_EQUALS_long(a, b) JA_EQUALS_ARITHMETIC(a, b)
#define JA_FMT_long "%ld"
#define JA_FMT_ARGS_long(v) v

#define JA_TYPE_unsigned_long unsigned long
#define JA_COMPARE_unsigned_long(a, OP, b) JA_COMPARE_ARITHMETIC(a, OP, b)
#define JA_EQUALS_unsigned_long(a, b) JA_EQUALS_ARITHMETIC(a, b)
#define JA_FMT_unsigned_long "%lu"
#define JA_FMT_ARGS_unsigned_long(v) v

#define JA_TYPE_long_long long long
#define JA_COMPARE_long_long(a, OP, b) JA_COMPARE_ARITHMETIC(a, OP, b)
#define JA_EQUALS_long_long(a, b) JA_EQUALS_ARITHMETIC(a, b)
#define JA_FMT_long_long "%lld"
#define JA_FMT_ARGS_long_long(v) v

#define JA_TYPE_unsigned_long_long unsigned long long
#define JA_COMPARE_unsigned_long_long(a, OP, b) JA_COMPARE_ARITHMETIC(a, OP, b)
#define JA_EQUALS_unsigned_long_long(a, b) JA_EQUALS_ARITHMETIC(a, b)
#define JA_FMT_unsigned_long_long "%llu"
#define JA_FMT_ARGS_unsigned_long_long(v) v

#define JA_TYPE_float float
#define JA_COMPARE_float(a, OP, b) JA_COMPARE_ARITHMETIC(a, OP, b)
#define JA_EQUALS_float(a, b) JA_EQUALS_ARITHMETIC(a, b)
#define JA_FMT_float "%f"
#define JA_FMT_ARGS_float(v) v

#define JA_TYPE_double double
#define JA_COMPARE_double(a, OP, b) JA_COMPARE_ARITHMETIC(a, OP, b)
#define JA_EQUALS_double(a, b) JA_EQUALS_ARITHMETIC(a, b)
#define JA_FMT_double "%lf"
#define JA_FMT_ARGS_double(v) v

#define JA_TYPE_long_double long double
#define JA_COMPARE_long_double(a, OP, b) JA_COMPARE_ARITHMETIC(a, OP, b)
#define JA_EQUALS_long_double(a, b) JA_EQUALS_ARITHMETIC(a, b)
#define JA_FMT_long_double "%Lf"
#define JA_FMT_ARGS_long_double(v) v

#define JA_COMPARE_ARITHMETIC(a, OP, b) ((a) OP (b))
#define JA_EQUALS_ARITHMETIC(a, b) ((a) == (b))

#endif // ja_template_h
