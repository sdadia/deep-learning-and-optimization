
############################### SETUP #########################################


COMPILER = g++
ifeq ($(COMPILER), clang++)
	COMPILER_FLAGS += -std=c++1z # c++17 standard - if clang
else
	COMPILER_FLAGS += -std=c++14
endif

# Set compilation type to DEBUG OR RELEASE
# in DEBUG, no optimization and debig flags are set
# In RELASE, O3 optimization is set
COMPILATION_TYPE=DEBUG
ifeq ($(COMPILATION_TYPE), RELEASE)
$(info "RELEASE MODE")
	COMPILER_FLAGS += -O3
else
$(info "DEBUG mode")
	COMPILER_FLAGS += -O0 -ggdb -Wall
endif

DOXYGEN = doxygen



############################# INPUTS  #########################################

SRC_DIR += ./src

INCLUDE_DIR += -I ./include 

LDFLAGS += -lgtest -lglog -lpthread -lblas


############################# OUTPUTS #########################################

BIN_DIR +=./build/bin
LIB_DIR +=./build/lib


############################# TARGETS TO CREATE ###############################

all : test_math_functions  test_sigmoid_layer doxy



############################### INSTRUCTIONS ##################################


test_math_functions : $(SRC_DIR)/math_functions.cpp
	$(COMPILER) $(COMPILER_FLAGS) -o $(BIN_DIR)/test_math_functions $(SRC_DIR)/math_functions.cpp  $(INCLUDE_DIR)  $(LDFLAGS)

test_sigmoid_layer : $(SRC_DIR)/sigmoid.cpp
	$(COMPILER) $(COMPILER_FLAGS) -o $(BIN_DIR)/test_sigmoid_layer $(SRC_DIR)/sigmoid.cpp  $(INCLUDE_DIR)  $(LDFLAGS)

clean:
	rm -rf $(BIN_DIR)/* $(LIB_DIR)/* ./docs/* ./documentation.html

doxy:
	@doxygen Doxyfile










