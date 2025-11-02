# the vars
BUILD_DIR := ./build
SRC_DIR := ./src

# The generated vars
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
TARGET := $(BUILD_DIR)/main

# Add the phony to keep overlapping files from breaking build
.PHONY: build run clean all

# The targets (build is default)
build:  $(SRCS) 
	mkdir -p $(BUILD_DIR)
	$(CXX) -std=c++17 $(SRCS) -o $(TARGET)

build-debug:  $(SRCS) 
	mkdir -p $(BUILD_DIR)
	$(CXX) -std=c++17 -g $(SRCS) -o $(TARGET)

run: build
	./$(TARGET)

debug: build-debug
	gdb ./$(TARGET)

clean:
	rm -rf ${BUILD_DIR}
