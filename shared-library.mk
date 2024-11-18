CC=gcc
CFLAGS=-fPIC -Wall -I./include
LDFLAGS=-shared -ldl

SRC_DIR=src
INCLUDE_DIR=include
BUILD_DIR=build

SOURCES=$(SRC_DIR)/tor.c $(SRC_DIR)/proxy_request.c $(SRC_DIR)/proxy_response.c
HEADERS=$(INCLUDE_DIR)/proxy_request.h $(INCLUDE_DIR)/proxy_response.h $(INCLUDE_DIR)/constants.h
TARGET=libtpn.so

$(BUILD_DIR)/$(TARGET): $(SOURCES) $(HEADERS)
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $(SOURCES) $(LDFLAGS)

all: $(BUILD_DIR)/$(TARGET)

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean
