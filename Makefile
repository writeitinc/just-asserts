# This Makefile is based on a template (lib+examples.makefile version 2.1.0).
# See: https://github.com/writeitinc/makefile-templates

NAME = just-asserts

ifndef NAME
$(error NAME is not set)
endif

CFLAGS = $(WFLAGS) $(OPTIM)

CSTD = c99
WFLAGS = -Wall -Wextra -Wpedantic -std=$(CSTD)

# Inputs Dirs

SOURCE_DIR = src
INCLUDE_DIR = include
HEADER_DIR = $(INCLUDE_DIR)/$(NAME)

EXAMPLE_DIR = examples

# Output Dirs

BUILD_DIR = build

OBJ_DIR = $(BUILD_DIR)/obj
STATIC_OBJ_DIR = $(OBJ_DIR)/static
SHARED_OBJ_DIR = $(OBJ_DIR)/shared
EXAMPLE_OBJ_DIR = $(OBJ_DIR)/examples

LIB_DIR = $(BUILD_DIR)/lib
BIN_DIR = $(BUILD_DIR)/bin

# Outputs

LIBRARIES = $(STATIC_LIB) $(SHARED_LIB)
STATIC_LIB = $(LIB_DIR)/lib$(NAME).a
SHARED_LIB = $(LIB_DIR)/lib$(NAME).so

EXAMPLES = $(BIN_DIR)/ex-runtime-asserts \
	   $(BIN_DIR)/ex-static-asserts

# Build Rules

.PHONY: default
default: release

.PHONY: release
release: OPTIM = -O3 $(LTOFLAGS)
release: build-dirs $(LIBRARIES) $(EXAMPLES)

.PHONY: debug
debug: DEBUG = -fsanitize=address,undefined
debug: OPTIM = -g
debug: build-dirs $(LIBRARIES) $(EXAMPLES)

.PHONY: library-release
library-release: OPTIM = -O3 $(LTOFLAGS)
library-release: library-build-dirs $(LIBRARIES)

.PHONY: library-debug
library-debug: DEBUG = -fsanitize=address,undefined
library-debug: OPTIM = -g
library-debug: library-build-dirs $(LIBRARIES)

# library

SOURCES = $(wildcard $(SOURCE_DIR)/*.c)
HEADERS = $(wildcard $(HEADER_DIR)/*.h)
STATIC_OBJS = $(patsubst $(SOURCE_DIR)/%.c, $(STATIC_OBJ_DIR)/%.o, $(SOURCES))
SHARED_OBJS = $(patsubst $(SOURCE_DIR)/%.c, $(SHARED_OBJ_DIR)/%.o, $(SOURCES))

PIC_FLAGS = -fPIC

$(STATIC_LIB): $(STATIC_OBJS)
	$(AR) crs $@ $^

$(SHARED_LIB): $(SHARED_OBJS)
	$(CC) -o $@ $^ -shared $(PIC_FLAGS) $(LDFLAGS)

$(STATIC_OBJ_DIR)/%.o: $(SOURCE_DIR)/%.c $(HEADERS)
	$(CC) -o $@ $< -c -I$(HEADER_DIR) $(CFLAGS) $(DEBUG) $(DEFINES) \
		-DJA_DONT_INCLUDE_STD_HEADERS

$(SHARED_OBJ_DIR)/%.o: $(SOURCE_DIR)/%.c $(HEADERS)
	$(CC) -o $@ $< -c -I$(HEADER_DIR) $(PIC_FLAGS) $(CFLAGS) $(DEBUG) $(DEFINES) \
		-DJA_DONT_INCLUDE_STD_HEADERS

# examples

EXAMPLE_HEADERS = $(wildcard $(EXAMPLE_DIR)/*.h)

EXAMPLE_LDFLAGS = -L$(LIB_DIR) -l:lib$(NAME).a $(LDFLAGS)

$(BIN_DIR)/%: $(EXAMPLE_OBJ_DIR)/%.o $(LIBRARIES)
	$(CC) -o $@ $< $(EXAMPLE_LDFLAGS) $(DEBUG) $(DEFINES)

$(EXAMPLE_OBJ_DIR)/%.o: $(EXAMPLE_DIR)/%.c $(HEADERS) $(EXAMPLE_HEADERS)
	$(CC) -o $@ $< -c -I$(INCLUDE_DIR) $(CFLAGS) $(DEBUG) $(DEFINES)

# build-dirs

.PHONY: build-dirs
build-dirs: library-build-dirs example-build-dirs

.PHONY: library-build-dirs
library-build-dirs: $(STATIC_OBJ_DIR)/ $(SHARED_OBJ_DIR)/ $(LIB_DIR)/

.PHONY: example-build-dirs
example-build-dirs: $(EXAMPLE_OBJ_DIR)/ $(BIN_DIR)/

%/:
	mkdir -p $@

# install

VERSION = $(VERSION_MAJOR).$(VERSION_MINOR).$(VERSION_PATCH)
VERSION_MAJOR = 1
VERSION_MINOR = 0
VERSION_PATCH = 1

DEST_DIR = # root

.PHONY: install-linux
install-linux:
	install -Dm755 "$(LIB_DIR)/lib$(NAME).so"       "$(DEST_DIR)/usr/lib/lib$(NAME).so.$(VERSION)"
	ln -snf        "lib$(NAME).so.$(VERSION)"       "$(DEST_DIR)/usr/lib/lib$(NAME).so.$(VERSION_MAJOR)"
	ln -snf        "lib$(NAME).so.$(VERSION_MAJOR)" "$(DEST_DIR)/usr/lib/lib$(NAME).so"
	
	find "$(HEADER_DIR)" -type f -exec install -Dm644 -t "$(DEST_DIR)/usr/include/$(NAME)/" "{}" \;
	
	install -Dm644 -t "$(DEST_DIR)/usr/lib/"                    "$(LIB_DIR)/lib$(NAME).a"
	install -Dm644 -t "$(DEST_DIR)/usr/share/licenses/$(NAME)/" "LICENSE"
	install -Dm644 -t "$(DEST_DIR)/usr/share/doc/$(NAME)/"      "README.md"

# clean

.PHONY: clean
clean:
	$(RM) -r build/*
