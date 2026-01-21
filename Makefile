### Define folder structure

ROOT_DIR	:= $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
#
BIN_DIR		:= $(ROOT_DIR)/bin
BUILD_DIR 	:= $(ROOT_DIR)/build
INC_DIR 	:= $(ROOT_DIR)/include
LIBRARY_DIR 	:= $(ROOT_DIR)/lib
SRC_DIR 	:= $(ROOT_DIR)/src
TEST_DIR 	:= $(ROOT_DIR)/tests
#
MAIN_FILE	:= $(BIN_DIR)/chess
# TEST_FILE	:= $(TEST_DIR) ## Thinking through if I need this

### Compiler options
CXX		:= g++
CXXFLAGS	:= -std=c++20 -Wall -I$(INC_DIR)

### Collect file locations
SOURCE		:= $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS		:= $(SOURCE:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
OBJECTS_NO_MAIN	:= $(filter-out $(BUILD_DIR)/chess.o, $(OBJECTS))

MAIN_TEST	:= $(TEST_DIR)/test_all.cpp
TST		:= $(wildcard $(TEST_DIR)/*.cpp)
TST		:= $(filter-out $(MAIN_TEST), $(TST))
TST_OBJ		:= $(TST:$(TEST_DIR)/%.cpp=$(BUILD_DIR)/tests/%.o)

$(MAIN_FILE): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	echo "$(TST_OBJ)"
	$(CXX) $^ -o $@

$(OBJECTS): $(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp 
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@


# Main testing file for all modules
test: $(TST_OBJ) $(MAIN_TEST) $(OBJECTS_NO_MAIN)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -g -o $(BIN_DIR)/$@

# Attempt to automate test files
$(TST_OBJ): $(BUILD_DIR)/tests/test_%.o: $(BUILD_DIR)/%.o $(TEST_DIR)/test_%.cpp
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BUILD_DIR)/tests
	$(CXX) $(CXXFLAGS) -c -g $^ -o $@



# Clean folder code
.PHONY: clean
clean:
	rm -rf $(BIN_DIR) $(BUILD_DIR)

