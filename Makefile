# Set root directory to be the makefile holder
ROOT_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

# Define all subdirectories
SRC_DIR		:= $(ROOT_DIR)/src
INC_DIR		:= $(ROOT_DIR)/include
BUILD_DIR	:= $(ROOT_DIR)/build
BIN_DIR		:= $(ROOT_DIR)/bin
TEST_DIR	:= $(ROOT_DIR)/tests

# Compiler options
CXX		:= g++
CXXFLAGS	:= -std=c++20 -Wall -I$(INC_DIR)

# Collect files for the main program
SRCS		:= $(wildcard $(SRC_DIR)/*.cpp)
MAIN		:= $(SRC_DIR)/chess.cpp
SRCS_NO_MAIN	:= $(filter-out $(MAIN), $(SRCS))
MAIN_OBJS	:= $(SRCS_NO_MAIN:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
ALL_OBJS	:= $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
MAIN_O		:= $(BUILD_DIR)/chess.o

# Collect files for testing
TST_SRC		:= $(wildcard $(TEST_DIR)/*.cpp)
TST_OBJ		:= $(TST_SRC:$(TEST_DIR)/%.cpp=$(BUILD_DIR)/tests/%.o)

# Make vars for the executables
CHESS		:= $(BIN_DIR)/chess
TEST		:= $(BIN_DIR)/test_board

# Set default make argument to build the target file
all: $(MAIN)

$(MAIN): $(MAIN_O) $(MAIN_OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $^ -o $@

$(TEST): $(TST_OBJ) $(MAIN_OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) -g $^ -o $@

# $(BUILD_DIR)%.o: $(SRC_DIR)/%.cpp
$(ALL_OBJS): $(SRCS)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TST_OBJ): $(TEST_SRC) $(MAIN_OBJS)
	@mkdir -p $(BUILD_DIR)/tests
	$(CXX) $(CXXFLAGS) -g -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

#
#test: $(TEST_DIR)/test_board.cpp $(BUID_DIR)/board.o
#	g++ ../tests/test_board.cpp ./board.o -g -o test
