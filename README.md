# just-asserts

Structured tests are lame and complicated. Why not just use asserts?

## Basic Usage
Below is a summary of basic usage of this library. See the [examples](examples) directory for
concrete examples.

### Static Assertions
```c
ja_static_assert(0 == -0);
ja_static_assert_msg(2 + 2 != 5, "Literally 1987.");
```

### Runtime Assertions
```c
// nonfatal assertions
ja_expect(cond);
ja_expect_msg(cond, "Something went wrong; continuing");

// fatal assertions
ja_assert(cond);
ja_assert_msg(cond, "Something went *very* wrong; aborting");

// debug-only assertions
ja_dbg_expect(cond); // no-op if JA_DEBUG is not defined
ja_dbg_assert(cond);

// comparisons
ja_assert(num1 == num2);
ja_assert_eq(int, num1, num2); // same as above but gives more context
ja_assert_neq(int, num3, num4);
ja_assert_cmp(int, num5, >=, num4);

// c-string support
ja_assert_eq(cstr, my_str, "deadbeef");
ja_assert_cmp(cstr, my_str, >, "deadbeef");

// pointer support
ja_assert_eq(ptr, my_str, NULL);
```

### Adding Support for More Types
```c
typedef struct Vec2D {
	float x;
	float y;
} Vec2D;

#define JA_TYPE_Vec2D Vec2D
#define JA_EQUALS_Vec2D(a, b) ((a).x == (b).x && (a).y == (b).y)
#define JA_FMT_Vec2D "[%g, %g]"
#define JA_FMT_ARGS_Vec2D(v) (v).x, (v).y

Vec2D vec = { 2, 1.5 };
ja_assert_eq(Vec2D, vec, ((Vec2D){ 2, 1.5 }));
```

## Limitations

### Preprocessor Weirdness
Due to the way the C preprocessor parses macro arguments, compound literals require parentheses:
```c
ja_assert_eq(Vec2D, vec, ((Vec2D){ 2, 1.5 })); // correct
ja_assert_eq(Vec2D, vec, (Vec2D){ 2, 1.5 }); // error--erroneously parsed as 4 arguments
```

### No C++ Support
This library was not built with C++ support in mind.

## Use as a Header-Only Library:
In *one* of your translation units, define the macro `JA_IMPLEMENTATION` *before* including any
headers. For example:
```c
#define JA_IMPLEMENTATION
#include <just-asserts/just-asserts.h>
```
