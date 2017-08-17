
############################### SETUP #########################################


# which compiler to use - default is g++
COMPILER = g++
ifeq ($(COMPILER), g++)
	COMPILER_FLAGS += -std=c++14
else
	COMPILER_FLAGS += -std=c++1z # c++17 standard - if clang
endif

# Set build type - default is DEBUG
# in DEBUG, no optimization and debig flags are set
# In RELASE, O3 optimization is set
BUILD_TYPE=DEBUG
ifeq ($(BUILD_TYPE), DEBUG)
$(info "DEBUG Mode")
	COMPILER_FLAGS += -Wall -O0 -ggdb -pg
else
$(info "RELEASE Mode")
	COMPILER_FLAGS += -O3 -msse3 -funroll-loops --fast-math
endif

NO_COLOR="\033[0m"
OK_COLOR="\033[32;01m"
ERROR_COLOR="\033[31;01m"
WARN_COLOR="\033[33;01m"
 
OK_STRING=$(OK_COLOR)[OK]$(NO_COLOR)
ERROR_STRING=$(ERROR_COLOR)[ERRORS]$(NO_COLOR)
WARN_STRING=$(WARN_COLOR)[WARNINGS]$(NO_COLOR)





############################# INPUT SETTING ##################################

# location of source files
SRC_DIR += ./src

# location of test files
TEST_SRC_DIR += ./test

INCLUDE_DIR += -I ./include -I /usr/local/include/xtensor-blas/flens/ -I /home/sahil/Documents/programs/timepass/include/
LDFLAGS += -fopenmp -lgtest -lgmock -lglog -lpthread -lblas -L /home/sahil/Documents/programs/timepass/generated_static_libs -lrandom_helper






############################# OUTPUTS SETTING #################################

BIN_DIR += ./build/bin
LIB_DIR += ./build/lib
DOCS_DIR += ./docs
# create the above directories - if they exist, they will NOT be overwritten
$(shell mkdir -p $(LIB_DIR) $(BIN_DIR) $(DOCS_DIR))





############################# FILE SETTING #################################

TEST_CPP_FILES = $(wildcard $(TEST_SRC_DIR)/*.cpp)
TEST_OBJ_FILES = $(subst $(TEST_SRC_DIR)/, $(BIN_DIR)/, $(patsubst %.cpp,%.o, $(TEST_CPP_FILES)))
TEST_EXECUTIBLE_FILES = $(subst $(TEST_SRC_DIR)/, $(BIN_DIR)/, $(patsubst %.cpp,%, $(TEST_CPP_FILES)))


SRC_CPP_FILES = $(wildcard $(SRC_DIR)/*.cpp)
SRC_OBJ_FILES = $(subst $(SRC_DIR)/, $(BIN_DIR)/, $(patsubst %.cpp, %.o, $(SRC_CPP_FILES)))
SRC_EXEC_FILES = $(subst $(SRC_DIR)/, $(BIN_DIR)/, $(patsubst %.cpp,%, $(SRC_CPP_FILES)))

LIBRARY_NAME = libdplo.a





############################# TARGETS TO CREATE ###############################

# creates everything
all : lib test

# main Library
lib : $(LIB_DIR)/$(LIBRARY_NAME)
#ls ./include/*.hpp | sed -r 's/^.+\///' >> dpl.hpp

# creates test -  it depends on above $(LIBRARY_NAME) library
test : $(TEST_EXECUTIBLE_FILES)
	rm -rf ./run_test.sh
	ls $(BIN_DIR)/test* > ./run_test.sh

# creates Documentation
docs : DOXY

DOXY:
	@doxygen Doxyfile
	ln -sf ./docs/html/index.html ./documentation.html

# Remove all the above
clean:
	rm -fr ./build/ ./docs/ ./*.o ./*.html ./*.out ./run_test.sh


############################### INSTRUCTIONS ##################################

# target : requirement_1, requirement_2, requirement_3 ....
#   commands
# $? means all requirement - here target is made only if requirement changes
# $^ means all the requirements of the target
# $< means requirement_1
# $@ means the target name


# Compiling source code to create library
$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp 
	@printf "Building :  %-50s\t\t\t" $@
	g++ -c  $< -o $@ $(INCLUDE_DIR) $(LDFLAGS) $(COMPILER_FLAGS)
	@echo $(OK_STRING)


# Compiling test source code to create tests
$(BIN_DIR)/%: $(TEST_SRC_DIR)/%.cpp  $(LIB_DIR)/$(LIBRARY_NAME)
	@printf "Building :  %-50s\t\t\t" $@
	g++  $< -o $@ $(INCLUDE_DIR) $(LDFLAGS) $(COMPILER_FLAGS) $(LIB_DIR)/$(LIBRARY_NAME)
	@echo $(OK_STRING)

# Create static archive from src files and NOT test files - it also needs to
# bre remade whenever there is a new change in the CPP files
$(LIB_DIR)/$(LIBRARY_NAME) : $(SRC_OBJ_FILES) $(SRC_CPP_FILES)
	@printf "\n\nBuilding :  %-50s\t\t\t" $@
	ar -cq $@ $?
	$(eval LDFLAGS += $@)
	@echo $(OK_STRING) 
	@printf "\n\n"
