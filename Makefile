# This Makefile is based on a template.
# See: https://github.com/writeitinc/makefile-templates

#### Project Config ############################################################

NAME = just-asserts

VERSION = $(VERSION_MAJOR).$(VERSION_MINOR).$(VERSION_PATCH)
VERSION_MAJOR = 1
VERSION_MINOR = 1
VERSION_PATCH = 0

ifndef NAME
$(error NAME is not set)
endif

#### Commandline Control Flags #################################################

BUILD_TYPE = $(DEFAULT_BUILD_TYPE)
CFLAGS = $(CFLAGS_DEFAULT)
LDFLAGS = # none by default
LTOFLAGS = -flto=auto
DEFINES = # none by default

USE_WINDOWS_CMD = # guess by default
PRODUCE_WINDOWS_OUTPUTS = # guess by default

#### Build Config ##############################################################

DEFAULT_BUILD_TYPE = release # release, debug, or sanitize
CSTD = c99

# Flags #

CFLAGS_DEFAULT = $(OPTIM) $(WFLAGS) $(FEATURE_FLAGS)
WFLAGS = -Wall -Wextra -Wpedantic
FEATURE_FLAGS = -std=$(CSTD) $(FEATURE_TEST_MACRO_FLAGS)
FEATURE_TEST_MACRO_FLAGS = -D_POSIX_C_SOURCE

OPTIM = $(OPTIM_$(BUILD_TYPE))
OPTIM_release = -O2
OPTIM_debug = -g
OPTIM_sanitize = $(OPTIM_debug)

SANITIZE_FLAGS = $(SANITIZE_FLAGS_$(BUILD_TYPE))
SANITIZE_FLAGS_release = # none by default
SANITIZE_FLAGS_debug = # none by default
SANITIZE_FLAGS_sanitize = -fsanitize=address,undefined

STATIC_LIB_FLAGS = -DJA_STATIC_LIB
SHARED_LIB_FLAGS = $(PLATFORM_SHARED_LIB_FLAGS)

# Output Directories #

OUTPUT_DIR = build

LIB_DIR = $(OUTPUT_DIR)/lib
BIN_DIR = $(OUTPUT_DIR)/bin
INTERMEDIATE_DIR = $(OUTPUT_DIR)/obj

#### Library Build Config ######################################################

# Inputs #

SOURCE_DIR = src
INCLUDE_DIR = include
HEADER_DIR = $(INCLUDE_DIR)/$(NAME)

SOURCES = $(wildcard $(SOURCE_DIR)/*.c)
HEADERS = $(wildcard $(HEADER_DIR)/*.h $(HEADER_DIR)/internal/*.h)

# Outputs #

LIBRARIES = $(STATIC_LIB) $(SHARED_LIB)
STATIC_LIB = $(LIB_DIR)/$(LIB_PREFIX)$(NAME).a
SHARED_LIB = $(LIB_DIR)/$(LIB_PREFIX)$(NAME)$(SHARED_LIB_EXT)

# Intermediates #

STATIC_OBJS = $(patsubst $(SOURCE_DIR)/%.c, $(INTERMEDIATE_DIR)/%.static.o, $(SOURCES))
SHARED_OBJS = $(patsubst $(SOURCE_DIR)/%.c, $(INTERMEDIATE_DIR)/%.shared.o, $(SOURCES))
.SECONDARY: $(STATIC_OBJS) $(SHARED_OBJS)

#### Platform/Toolchain Detection ##############################################

include platform.mk

#### Build Targets #############################################################

### General ###

.PHONY: default
default: $(DEFAULT_BUILD_TYPE)

.PHONY: release
release: BUILD_TYPE = release
release: output-dirs
release: $(LIBRARIES)

.PHONY: debug
debug: BUILD_TYPE = debug
debug: output-dirs
debug: $(LIBRARIES)

.PHONY: sanitize
sanitize: BUILD_TYPE = sanitize
sanitize: output-dirs
sanitize: $(LIBRARIES)

# Pro Tip: DO NOT EVER run `rm -rf` (or similar) on a variable
.PHONY: clean
clean:
	$(call RM_RF,build/*)

### Library ###

.PHONY: library
library: library-$(DEFAULT_BUILD_TYPE)

.PHONY: static-library
static-library: static-library-$(DEFAULT_BUILD_TYPE)

.PHONY: shared-library
shared-library: shared-library-$(DEFAULT_BUILD_TYPE)

.PHONY: library-release
library-release: BUILD_TYPE = release
library-release: library-output-dirs $(LIBRARIES)

.PHONY: library-debug
library-debug: BUILD_TYPE = debug
library-debug: library-output-dirs $(LIBRARIES)

.PHONY: library-sanitize
library-sanitize: BUILD_TYPE = sanitize
library-sanitize: library-output-dirs $(LIBRARIES)

.PHONY: static-library-release
static-library-release: BUILD_TYPE = release
static-library-release: static-library-output-dirs $(STATIC_LIB)

.PHONY: static-library-debug
static-library-debug: BUILD_TYPE = debug
static-library-debug: static-library-output-dirs $(STATIC_LIB)

.PHONY: static-library-sanitize
static-library-sanitize: BUILD_TYPE = sanitize
static-library-sanitize: static-library-output-dirs $(STATIC_LIB)

.PHONY: shared-library-release
shared-library-release: BUILD_TYPE = release
shared-library-release: shared-library-output-dirs $(SHARED_LIB)

.PHONY: shared-library-debug
shared-library-debug: BUILD_TYPE = debug
shared-library-debug: shared-library-output-dirs $(SHARED_LIB)

.PHONY: shared-library-sanitize
shared-library-sanitize: BUILD_TYPE = sanitize
shared-library-sanitize: shared-library-output-dirs $(SHARED_LIB)

#### Library Build Rules #######################################################

$(STATIC_LIB): $(STATIC_OBJS)
	$(AR) crs $@ $^

$(SHARED_LIB): $(SHARED_OBJS)
	$(CC) -o $@ $^ -shared $(LDFLAGS) $(LTOFLAGS)

$(INTERMEDIATE_DIR)/%.static.o: $(SOURCE_DIR)/%.c $(HEADERS)
	$(CC) -o $@ $< -c -I$(HEADER_DIR) $(STATIC_LIB_FLAGS) \
		$(CFLAGS) $(LTOFLAGS) $(SANITIZE_FLAGS) $(DEFINES)

$(INTERMEDIATE_DIR)/%.shared.o: $(SOURCE_DIR)/%.c $(HEADERS)
	$(CC) -o $@ $< -c -I$(HEADER_DIR) $(SHARED_LIB_FLAGS) \
		$(CFLAGS) $(LTOFLAGS) $(SANITIZE_FLAGS) $(DEFINES)

#### Directory Build Rules #####################################################

### General ###

.PHONY: output-dirs
output-dirs: library-output-dirs

%/:
	$(call MKDIR_P,"$@")

### Library ###

.PHONY: library-output-dirs
library-output-dirs: static-library-output-dirs shared-library-output-dirs

.PHONY: static-library-output-dirs
static-library-output-dirs: $(LIB_DIR)/ $(INTERMEDIATE_DIR)/

.PHONY: shared-library-output-dirs
shared-library-output-dirs: $(LIB_DIR)/ $(INTERMEDIATE_DIR)/

#### Inclusions ################################################################

include examples.mk
include linux-install.mk
