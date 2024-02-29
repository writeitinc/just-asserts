NAME = just-asserts
SOURCE_DIR = $(WORKING_DIR)/src
EXAMPLE_DIR = $(WORKING_DIR)/examples

CFLAGS = $(WFLAGS) $(OPTIM) $(IFLAGS)

WFLAGS = -Wall -Wextra -pedantic -std=c99
IFLAGS = -I$(INCLUDE_DIR)

WORKING_DIR = .
BUILD_DIR = build

INCLUDE_DIR = $(BUILD_DIR)/include
HEADER_DIR = $(INCLUDE_DIR)/$(NAME)

OBJ_DIR = $(BUILD_DIR)/obj
EXAMPLE_OBJ_DIR = $(OBJ_DIR)/examples

BIN_DIR = $(BUILD_DIR)/bin

BINARIES =

.PHONY: default
default: release

.PHONY: release
release: OPTIM = -O3 $(LTOFLAGS)
release: dirs headers $(BINARIES)

.PHONY: debug
debug: DEBUG = -fsanitize=address,undefined
debug: OPTIM = -g
debug: dirs headers $(BINARIES)

# library

SOURCES = $(wildcard $(SOURCE_DIR)/*.c)
HEADERS = $(wildcard $(SOURCE_DIR)/*.h)

# headers

.PHONY: headers
headers: $(HEADER_DIR)

$(HEADER_DIR): $(HEADERS)
	mkdir -p $@
	cp -u -t $@/ $^
	touch $@

# examples

EXAMPLE_HEADERS = $(wildcard $(EXAMPLE_DIR)/*.h)

$(BIN_DIR)/%: $(EXAMPLE_OBJ_DIR)/%.o
	$(CC) -o $@ $< $(LDFLAGS) $(DEBUG) $(DEFINES)

$(EXAMPLE_OBJ_DIR)/%.o: $(EXAMPLE_DIR)/%.c $(HEADERS) $(EXAMPLE_HEADERS)
	$(CC) -o $@ $< -c $(CFLAGS) $(DEBUG) $(DEFINES)

# dirs

.PHONY: dirs
dirs: $(INCLUDE_DIR)/ $(EXAMPLE_OBJ_DIR)/ $(BIN_DIR)/

%/:
	mkdir -p $@

# install

DEST_DIR = # root

.PHONY: install-linux
install-linux:
	install -Dm644 -t "$(DEST_DIR)/usr/include/$(NAME)/"        "build/include/$(NAME)/$(NAME).h"
	install -Dm644 -t "$(DEST_DIR)/usr/share/licenses/$(NAME)/" "LICENSE"
	install -Dm644 -t "$(DEST_DIR)/usr/share/doc/$(NAME)/"      "README.md"

# clean

.PHONY: clean
clean:
	$(RM) -r build/*
