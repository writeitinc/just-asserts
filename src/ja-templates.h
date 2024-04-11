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

#define JA__LVALUE(T, v) (T [1]){ (v) }[0]

#define JA_COMPARE_ARITHMETIC(a, OP, b) ((a) OP (b))
#define JA_EQUALS_ARITHMETIC(a, b) ((a) == (b))
#define JA_CASTED_COMPARE_ARITHMETIC(T, a, OP, b) ((T)(a) OP (T)(b))
#define JA_CASTED_EQUALS_ARITHMETIC(T, a, b) ((T)(a) == (T)(b))

#define JA_COMPARE_DIV(a, OP, b) (((a).quot OP (b).quot) && ((a).rem OP (b).rem))

// ### Implementations ###

// Basic Types

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

// Special Pointer Types

#define JA_TYPE_ptr void *
#define JA_COMPARE_ptr(a, OP, b) JA_CASTED_COMPARE_ARITHMETIC(void *, a, OP, b)
#define JA_EQUALS_ptr(a, b) JA_CASTED_EQUALS_ARITHMETIC(void *, a, b)
#define JA_FMT_ptr "%p"
#define JA_FMT_ARGS_ptr(v) (void *)(v)

#ifndef JA_DONT_INCLUDE_STD_HEADERS
# include <string.h>
#endif
#define JA_TYPE_cstr const char *
#define JA_COMPARE_cstr(a, OP, b) (strcmp(a, b) OP 0)
#define JA_EQUALS_cstr(a, b) (strcmp(a, b) == 0)
#define JA_FMT_cstr "\"%s\""
#define JA_FMT_ARGS_cstr(v) (const char *)(v)

// Size/Diff Types

#define JA_TYPE_size_t size_t
#define JA_COMPARE_size_t(a, OP, b) JA_CASTED_COMPARE_ARITHMETIC(size_t, a, OP, b)
#define JA_EQUALS_size_t(a, b) JA_CASTED_EQUALS_ARITHMETIC(size_t, a, b)
#define JA_FMT_size_t "%zu"
#define JA_FMT_ARGS_size_t(v) (size_t)(v)

#define JA_TYPE_ptrdiff_t ptrdiff_t
#define JA_COMPARE_ptrdiff_t(a, OP, b) JA_CASTED_COMPARE_ARITHMETIC(ptrdiff_t, a, OP, b)
#define JA_EQUALS_ptrdiff_t(a, b) JA_CASTED_EQUALS_ARITHMETIC(ptrdiff_t, a, b)
#define JA_FMT_ptrdiff_t "%td"
#define JA_FMT_ARGS_ptrdiff_t(v) (ptrdiff_t)(v)

// Efficient Floating-Point Types

#define JA_TYPE_float_t float_t
#define JA_COMPARE_float_t(a, OP, b) JA_CASTED_COMPARE_ARITHMETIC(float_t, a, OP, b)
#define JA_EQUALS_float_t(a, b) JA_CASTED_EQUALS_ARITHMETIC(float_t, a, b)
#define JA_FMT_uint_float_t "%Lf"
#define JA_FMT_ARGS_float_t(v) (long double)(v) // probably long enough

#define JA_TYPE_double_t double_t
#define JA_COMPARE_double_t(a, OP, b) JA_CASTED_COMPARE_ARITHMETIC(double_t, a, OP, b)
#define JA_EQUALS_double_t(a, b) JA_CASTED_EQUALS_ARITHMETIC(double_t, a, b)
#define JA_FMT_uint_double_t "%Lf"
#define JA_FMT_ARGS_double_t(v) (long double)(v) // probably long enough

// Complex Types

#ifndef __STDC_NO_COMPLEX__
# ifndef JA_DONT_INCLUDE_STD_HEADERS
#  include <complex.h>
# endif

# define JA_TYPE_float_complex float _Complex
# define JA_COMPARE_float_complex(a, OP, b) JA_CASTED_COMPARE_ARITHMETIC(float _Complex, a, OP, b)
# define JA_EQUALS_float_complex(a, b) JA_CASTED_EQUALS_ARITHMETIC(float _Complex, a, b)
# define JA_FMT_float_complex "%g+%gi"
# define JA_FMT_ARGS_float_complex(v) crealf(v), cimagf(v)

# define JA_TYPE_double_complex double _Complex
# define JA_COMPARE_double_complex(a, OP, b) JA_CASTED_COMPARE_ARITHMETIC(double _Complex, a, OP, b)
# define JA_EQUALS_double_complex(a, b) JA_CASTED_EQUALS_ARITHMETIC(double _Complex, a, b)
# define JA_FMT_double_complex "%lg+%lgi"
# define JA_FMT_ARGS_double_complex(v) creal((double _Complex)(v)), cimag((double _Complex)(v))

# define JA_TYPE_long_double_complex long double _Complex
# define JA_COMPARE_long_double_complex(a, OP, b) JA_CASTED_COMPARE_ARITHMETIC(long double _Complex, a, OP, b)
# define JA_EQUALS_long_double_complex(a, b) JA_CASTED_EQUALS_ARITHMETIC(long double _Complex, a, b)
# define JA_FMT_long_double_complex "%Lg+%Lgi"
# define JA_FMT_ARGS_long_double_complex(v) creall(v), cimagl(v)
#endif

// Division Result Types

#define JA_TYPE_div_t div_t
#define JA_COMPARE_div_t(a, OP, b) JA_COMPARE_DIV(a, OP, b)
#define JA_EQUALS_div_t(a, b) JA_COMPARE_DIV(a, ==, b)
#define JA_FMT_div_t "%dr%d"
#define JA_FMT_ARGS_div_t(v) (v).quot, (v).rem

#define JA_TYPE_ldiv_t ldiv_t
#define JA_COMPARE_ldiv_t(a, OP, b) JA_COMPARE_DIV(a, OP, b)
#define JA_EQUALS_ldiv_t(a, b) JA_COMPARE_DIV(a, ==, b)
#define JA_FMT_ldiv_t "%ldr%ld"
#define JA_FMT_ARGS_ldiv_t(v) (v).quot, (v).rem

#define JA_TYPE_lldiv_t lldiv_t
#define JA_COMPARE_lldiv_t(a, OP, b) JA_COMPARE_DIV(a, OP, b)
#define JA_EQUALS_lldiv_t(a, b) JA_COMPARE_DIV(a, ==, b)
#define JA_FMT_lldiv_t "%ldr%ld"
#define JA_FMT_ARGS_lldiv_t(v) (v).quot, (v).rem

#define JA_TYPE_imaxdiv_t imaxdiv_t
#define JA_COMPARE_imaxdiv_t(a, OP, b) JA_COMPARE_DIV(a, OP, b)
#define JA_EQUALS_imaxdiv_t(a, b) JA_COMPARE_DIV(a, ==, b)
#define JA_FMT_imaxdiv_t "%jdr%jd"
#define JA_FMT_ARGS_imaxdiv_t(v) (v).quot, (v).rem

// Wide Character Types

#define JA_TYPE_wchar_t wchar_t
#define JA_COMPARE_wchar_t(a, OP, b) JA_CASTED_COMPARE_ARITHMETIC(wchar_t, a, OP, b)
#define JA_EQUALS_wchar_t(a, b) JA_CASTED_EQUALS_ARITHMETIC(wchar_t, a, b)
#define JA_FMT_wchar_t "%lc"
#define JA_FMT_ARGS_wchar_t(v) (wint_t)(v)

#define JA_TYPE_wint_t wint_t
#define JA_COMPARE_wint_t(a, OP, b) JA_CASTED_COMPARE_ARITHMETIC(wint_t, a, OP, b)
#define JA_EQUALS_wint_t(a, b) JA_CASTED_EQUALS_ARITHMETIC(wint_t, a, b)
#define JA_FMT_wint_t "%lc"
#define JA_FMT_ARGS_wint_t(v) (wint_t)(v)

// Fixed-Width Integer Types

#define JA_TYPE_int8_t int8_t
#define JA_COMPARE_int8_t(a, OP, b) JA_CASTED_COMPARE_ARITHMETIC(int8_t, a, OP, b)
#define JA_EQUALS_int8_t(a, b) JA_CASTED_EQUALS_ARITHMETIC(int8_t, a, b)
#define JA_FMT_int8_t PRId8
#define JA_FMT_ARGS_int8_t(v) (int8_t)(v)

#define JA_TYPE_int16_t int16_t
#define JA_COMPARE_int16_t(a, OP, b) JA_CASTED_COMPARE_ARITHMETIC(int16_t, a, OP, b)
#define JA_EQUALS_int16_t(a, b) JA_CASTED_EQUALS_ARITHMETIC(int16_t, a, b)
#define JA_FMT_int16_t PRId16
#define JA_FMT_ARGS_int16_t(v) (int16_t)(v)

#define JA_TYPE_int32_t int32_t
#define JA_COMPARE_int32_t(a, OP, b) JA_CASTED_COMPARE_ARITHMETIC(int32_t, a, OP, b)
#define JA_EQUALS_int32_t(a, b) JA_CASTED_EQUALS_ARITHMETIC(int32_t, a, b)
#define JA_FMT_int32_t PRId32
#define JA_FMT_ARGS_int32_t(v) (int32_t)(v)

#define JA_TYPE_int64_t int64_t
#define JA_COMPARE_int64_t(a, OP, b) JA_CASTED_COMPARE_ARITHMETIC(int64_t, a, OP, b)
#define JA_EQUALS_int64_t(a, b) JA_CASTED_EQUALS_ARITHMETIC(int64_t, a, b)
#define JA_FMT_int64_t PRId64
#define JA_FMT_ARGS_int64_t(v) (int64_t)(v)

#define JA_TYPE_uint8_t uint8_t
#define JA_COMPARE_uint8_t(a, OP, b) JA_CASTED_COMPARE_ARITHMETIC(uint8_t, a, OP, b)
#define JA_EQUALS_uint8_t(a, b) JA_CASTED_EQUALS_ARITHMETIC(uint8_t, a, b)
#define JA_FMT_uint8_t PRId8
#define JA_FMT_ARGS_uint8_t(v) (uint8_t)(v)

#define JA_TYPE_uint16_t uint16_t
#define JA_COMPARE_uint16_t(a, OP, b) JA_CASTED_COMPARE_ARITHMETIC(uint16_t, a, OP, b)
#define JA_EQUALS_uint16_t(a, b) JA_CASTED_EQUALS_ARITHMETIC(uint16_t, a, b)
#define JA_FMT_uint16_t PRIu16
#define JA_FMT_ARGS_uint16_t(v) (uint16_t)(v)

#define JA_TYPE_uint32_t uint32_t
#define JA_COMPARE_uint32_t(a, OP, b) JA_CASTED_COMPARE_ARITHMETIC(uint32_t, a, OP, b)
#define JA_EQUALS_uint32_t(a, b) JA_CASTED_EQUALS_ARITHMETIC(uint32_t, a, b)
#define JA_FMT_uint32_t PRIu32
#define JA_FMT_ARGS_uint32_t(v) (uint32_t)(v)

#define JA_TYPE_uint64_t uint64_t
#define JA_COMPARE_uint64_t(a, OP, b) JA_CASTED_COMPARE_ARITHMETIC(uint64_t, a, OP, b)
#define JA_EQUALS_uint64_t(a, b) JA_CASTED_EQUALS_ARITHMETIC(uint64_t, a, b)
#define JA_FMT_uint64_t PRIu64
#define JA_FMT_ARGS_uint64_t(v) (uint64_t)(v)

#define JA_TYPE_intmax_t intmax_t
#define JA_COMPARE_intmax_t(a, OP, b) JA_CASTED_COMPARE_ARITHMETIC(intmax_t, a, OP, b)
#define JA_EQUALS_intmax_t(a, b) JA_CASTED_EQUALS_ARITHMETIC(intmax_t, a, b)
#define JA_FMT_intmax_t PRIdMAX
#define JA_FMT_ARGS_intmax_t(v) (intmax_t)(v)

#define JA_TYPE_uintmax_t uintmax_t
#define JA_COMPARE_uintmax_t(a, OP, b) JA_CASTED_COMPARE_ARITHMETIC(uintmax_t, a, OP, b)
#define JA_EQUALS_uintmax_t(a, b) JA_CASTED_EQUALS_ARITHMETIC(uintmax_t, a, b)
#define JA_FMT_uintmax_t PRIuMAX
#define JA_FMT_ARGS_uintmax_t(v) (uintmax_t)(v)

#define JA_TYPE_int_fast8_t int_fast8_t
#define JA_COMPARE_int_fast8_t(a, OP, b) JA_CASTED_COMPARE_ARITHMETIC(int_fast8_t, a, OP, b)
#define JA_EQUALS_int_fast8_t(a, b) JA_CASTED_EQUALS_ARITHMETIC(int_fast8_t, a, b)
#define JA_FMT_int_fast8_t PRIdFAST8
#define JA_FMT_ARGS_int_fast8_t(v) (int_fast8_t)(v)

#define JA_TYPE_int_fast16_t int_fast16_t
#define JA_COMPARE_int_fast16_t(a, OP, b) JA_CASTED_COMPARE_ARITHMETIC(int_fast16_t, a, OP, b)
#define JA_EQUALS_int_fast16_t(a, b) JA_CASTED_EQUALS_ARITHMETIC(int_fast16_t, a, b)
#define JA_FMT_int_fast16_t PRIdFAST16
#define JA_FMT_ARGS_int_fast16_t(v) (int_fast16_t)(v)

#define JA_TYPE_int_fast32_t int_fast32_t
#define JA_COMPARE_int_fast32_t(a, OP, b) JA_CASTED_COMPARE_ARITHMETIC(int_fast32_t, a, OP, b)
#define JA_EQUALS_int_fast32_t(a, b) JA_CASTED_EQUALS_ARITHMETIC(int_fast32_t, a, b)
#define JA_FMT_int_fast32_t PRIdFAST32
#define JA_FMT_ARGS_int_fast32_t(v) (int_fast32_t)(v)

#define JA_TYPE_int_fast64_t int_fast64_t
#define JA_COMPARE_int_fast64_t(a, OP, b) JA_CASTED_COMPARE_ARITHMETIC(int_fast64_t, a, OP, b)
#define JA_EQUALS_int_fast64_t(a, b) JA_CASTED_EQUALS_ARITHMETIC(int_fast64_t, a, b)
#define JA_FMT_int_fast64_t PRIdFAST64
#define JA_FMT_ARGS_int_fast64_t(v) (int_fast64_t)(v)

#define JA_TYPE_uint_fast8_t uint_fast8_t
#define JA_COMPARE_uint_fast8_t(a, OP, b) JA_CASTED_COMPARE_ARITHMETIC(uint_fast8_t, a, OP, b)
#define JA_EQUALS_uint_fast8_t(a, b) JA_CASTED_EQUALS_ARITHMETIC(uint_fast8_t, a, b)
#define JA_FMT_uint_fast8_t PRIdFAST8
#define JA_FMT_ARGS_uint_fast8_t(v) (uint_fast8_t)(v)

#define JA_TYPE_uint_fast16_t uint_fast16_t
#define JA_COMPARE_uint_fast16_t(a, OP, b) JA_CASTED_COMPARE_ARITHMETIC(uint_fast16_t, a, OP, b)
#define JA_EQUALS_uint_fast16_t(a, b) JA_CASTED_EQUALS_ARITHMETIC(uint_fast16_t, a, b)
#define JA_FMT_uint_fast16_t PRIuFAST16
#define JA_FMT_ARGS_uint_fast16_t(v) (uint_fast16_t)(v)

#define JA_TYPE_uint_fast32_t uint_fast32_t
#define JA_COMPARE_uint_fast32_t(a, OP, b) JA_CASTED_COMPARE_ARITHMETIC(uint_fast32_t, a, OP, b)
#define JA_EQUALS_uint_fast32_t(a, b) JA_CASTED_EQUALS_ARITHMETIC(uint_fast32_t, a, b)
#define JA_FMT_uint_fast32_t PRIuFAST32
#define JA_FMT_ARGS_uint_fast32_t(v) (uint_fast32_t)(v)

#define JA_TYPE_uint_fast64_t uint_fast64_t
#define JA_COMPARE_uint_fast64_t(a, OP, b) JA_CASTED_COMPARE_ARITHMETIC(uint_fast64_t, a, OP, b)
#define JA_EQUALS_uint_fast64_t(a, b) JA_CASTED_EQUALS_ARITHMETIC(uint_fast64_t, a, b)
#define JA_FMT_uint_fast64_t PRIuFAST64
#define JA_FMT_ARGS_uint_fast64_t(v) (uint_fast64_t)(v)

#define JA_TYPE_int_least8_t int_least8_t
#define JA_COMPARE_int_least8_t(a, OP, b) JA_CASTED_COMPARE_ARITHMETIC(int_least8_t, a, OP, b)
#define JA_EQUALS_int_least8_t(a, b) JA_CASTED_EQUALS_ARITHMETIC(int_least8_t, a, b)
#define JA_FMT_int_least8_t PRIdLEAST8
#define JA_FMT_ARGS_int_least8_t(v) (int_least8_t)(v)

#define JA_TYPE_int_least16_t int_least16_t
#define JA_COMPARE_int_least16_t(a, OP, b) JA_CASTED_COMPARE_ARITHMETIC(int_least16_t, a, OP, b)
#define JA_EQUALS_int_least16_t(a, b) JA_CASTED_EQUALS_ARITHMETIC(int_least16_t, a, b)
#define JA_FMT_int_least16_t PRIdLEAST16
#define JA_FMT_ARGS_int_least16_t(v) (int_least16_t)(v)

#define JA_TYPE_int_least32_t int_least32_t
#define JA_COMPARE_int_least32_t(a, OP, b) JA_CASTED_COMPARE_ARITHMETIC(int_least32_t, a, OP, b)
#define JA_EQUALS_int_least32_t(a, b) JA_CASTED_EQUALS_ARITHMETIC(int_least32_t, a, b)
#define JA_FMT_int_least32_t PRIdLEAST32
#define JA_FMT_ARGS_int_least32_t(v) (int_least32_t)(v)

#define JA_TYPE_int_least64_t int_least64_t
#define JA_COMPARE_int_least64_t(a, OP, b) JA_CASTED_COMPARE_ARITHMETIC(int_least64_t, a, OP, b)
#define JA_EQUALS_int_least64_t(a, b) JA_CASTED_EQUALS_ARITHMETIC(int_least64_t, a, b)
#define JA_FMT_int_least64_t PRIdLEAST64
#define JA_FMT_ARGS_int_least64_t(v) (int_least64_t)(v)

#define JA_TYPE_uint_least8_t uint_least8_t
#define JA_COMPARE_uint_least8_t(a, OP, b) JA_CASTED_COMPARE_ARITHMETIC(uint_least8_t, a, OP, b)
#define JA_EQUALS_uint_least8_t(a, b) JA_CASTED_EQUALS_ARITHMETIC(uint_least8_t, a, b)
#define JA_FMT_uint_least8_t PRIdLEAST8
#define JA_FMT_ARGS_uint_least8_t(v) (uint_least8_t)(v)

#define JA_TYPE_uint_least16_t uint_least16_t
#define JA_COMPARE_uint_least16_t(a, OP, b) JA_CASTED_COMPARE_ARITHMETIC(uint_least16_t, a, OP, b)
#define JA_EQUALS_uint_least16_t(a, b) JA_CASTED_EQUALS_ARITHMETIC(uint_least16_t, a, b)
#define JA_FMT_uint_least16_t PRIuLEAST16
#define JA_FMT_ARGS_uint_least16_t(v) (uint_least16_t)(v)

#define JA_TYPE_uint_least32_t uint_least32_t
#define JA_COMPARE_uint_least32_t(a, OP, b) JA_CASTED_COMPARE_ARITHMETIC(uint_least32_t, a, OP, b)
#define JA_EQUALS_uint_least32_t(a, b) JA_CASTED_EQUALS_ARITHMETIC(uint_least32_t, a, b)
#define JA_FMT_uint_least32_t PRIuLEAST32
#define JA_FMT_ARGS_uint_least32_t(v) (uint_least32_t)(v)

#define JA_TYPE_uint_least64_t uint_least64_t
#define JA_COMPARE_uint_least64_t(a, OP, b) JA_CASTED_COMPARE_ARITHMETIC(uint_least64_t, a, OP, b)
#define JA_EQUALS_uint_least64_t(a, b) JA_CASTED_EQUALS_ARITHMETIC(uint_least64_t, a, b)
#define JA_FMT_uint_least64_t PRIuLEAST64
#define JA_FMT_ARGS_uint_least64_t(v) (uint_least64_t)(v)

#define JA_TYPE_intptr_t intptr_t
#define JA_COMPARE_intptr_t(a, OP, b) JA_CASTED_COMPARE_ARITHMETIC(intptr_t, a, OP, b)
#define JA_EQUALS_intptr_t(a, b) JA_CASTED_EQUALS_ARITHMETIC(intptr_t, a, b)
#define JA_FMT_intptr_t "0x" PRIxPTR
#define JA_FMT_ARGS_intptr_t(v) (intptr_t)(v)

#define JA_TYPE_uintptr_t uintptr_t
#define JA_COMPARE_uintptr_t(a, OP, b) JA_CASTED_COMPARE_ARITHMETIC(uintptr_t, a, OP, b)
#define JA_EQUALS_uintptr_t(a, b) JA_CASTED_EQUALS_ARITHMETIC(uintptr_t, a, b)
#define JA_FMT_uintptr_t "0x" PRIxPTR
#define JA_FMT_ARGS_uintptr_t(v) (uintptr_t)(v)

// Time/Date Types

#define JA_TYPE_clock_t clock_t
#define JA_COMPARE_clock_t(a, OP, b) JA_CASTED_COMPARE_ARITHMETIC(clock_t, a, OP, b)
#define JA_EQUALS_clock_t(a, b) JA_CASTED_EQUALS_ARITHMETIC(clock_t, a, b)
#define JA_FMT_clock_t "%Lf"
#define JA_FMT_ARGS_clock_t(v) (long double)(v) // probably fine

#define JA_TYPE_time_t time_t
#define JA_COMPARE_time_t(a, OP, b) JA_CASTED_COMPARE_ARITHMETIC(time_t, a, OP, b)
#define JA_EQUALS_time_t(a, b) JA_CASTED_EQUALS_ARITHMETIC(time_t, a, b)
#define JA_FMT_time_t "%lld"
#define JA_FMT_ARGS_time_t(v) (long long)(v) // educated guess

#define JA_TYPE_struct_tm struct tm
#define JA_COMPARE_struct_tm(a, OP, b) \
	JA_CASTED_COMPARE_ARITHMETIC(time_t, \
		mktime(&JA__LVALUE(struct tm, a)), \
		mktime(&JA__LVALUE(struct tm, b)))
#define JA_EQUALS_struct_tm(a, b) \
	JA_CASTED_EQUALS_ARITHMETIC(time_t, \
		mktime(&JA__LVALUE(struct tm, a)), \
		mktime(&JA__LVALUE(struct tm, b)))
#define JA_FMT_struct_tm "%.24s"
#define JA_FMT_ARGS_struct_tm(v) ja_cpy_asctime(asctime(&JA__LVALUE(struct tm, v))).ascii

// sig_atomic_t

#define JA_TYPE_sig_atomic_t sig_atomic_t
#define JA_COMPARE_sig_atomic_t(a, OP, b) JA_CASTED_COMPARE_ARITHMETIC(sig_atomic_t, a, OP, b)
#define JA_EQUALS_sig_atomic_t(a, b) JA_CASTED_EQUALS_ARITHMETIC(sig_atomic_t, a, b)
#define JA_FMT_sig_atomic_t "%lld"
#define JA_FMT_ARGS_sig_atomic_t(v) (long long)(v) // probably long enough

typedef struct JAAsciiTime {
	char ascii[26];
} JAAsciiTime;

JAAsciiTime ja_cpy_asctime(const char asctime_str[26]);

#ifdef JA_IMPLEMENTATION
#include <string.h>

JAAsciiTime ja_cpy_asctime(const char asctime_str[26])
{
	JAAsciiTime ascii_time;
	memcpy(ascii_time.ascii, asctime_str, sizeof(ascii_time.ascii));

	return ascii_time;
}
#endif // JA_IMPLEMENTATION

#endif // ja_template_h
