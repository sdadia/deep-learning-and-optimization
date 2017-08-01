
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



############################# INPUTS  #########################################

SRC_DIR += ./src

INCLUDE_DIR += -I ./include -I /usr/local/include/xtensor-blas/flens/

LDFLAGS += -lgtest -lgmock -lglog -lpthread -lblas


############################# OUTPUTS #########################################

BIN_DIR +=./build/bin
LIB_DIR +=./build/lib


############################# TARGETS TO CREATE ###############################

all : libdpl

test : test_sigmoid_layer test_crossentropyloss_layer



############################### INSTRUCTIONS ##################################



libdpl : math_functions.o sigmoid_layer.o common.o crossentropyloss_layer.o
	ar -cvq $(LIB_DIR)/libdpl.a math_functions.o sigmoid_layer.o common.o crossentropyloss_layer.o

common.o : $(SRC_DIR)/common.cpp
	$(COMPILER) $(COMPILER_FLAGS) -c $(SRC_DIR)/common.cpp  $(INCLUDE_DIR)  $(LDFLAGS)

math_functions.o : $(SRC_DIR)/math_functions.cpp
	$(COMPILER) $(COMPILER_FLAGS) -c $(SRC_DIR)/math_functions.cpp  $(INCLUDE_DIR)  $(LDFLAGS)


crossentropyloss_layer.o : $(SRC_DIR)/crossentropyloss_layer.cpp
	$(COMPILER) $(COMPILER_FLAGS) -c $(SRC_DIR)/crossentropyloss_layer.cpp  $(INCLUDE_DIR)  $(LDFLAGS)


sigmoid_layer.o : $(SRC_DIR)/sigmoid_layer.cpp
	$(COMPILER) $(COMPILER_FLAGS) -c $(SRC_DIR)/sigmoid_layer.cpp  $(INCLUDE_DIR)  $(LDFLAGS)


test_sigmoid_layer : $(SRC_DIR)/test_sigmoid_layer.cpp libdpl
	$(COMPILER) $(COMPILER_FLAGS) -o $(BIN_DIR)/test_sigmoid_layer $(SRC_DIR)/test_sigmoid_layer.cpp  $(INCLUDE_DIR)  $(LDFLAGS) $(LIB_DIR)/libdpl.a


test_crossentropyloss_layer : $(SRC_DIR)/test_crossentropyloss_layer.cpp libdpl
	$(COMPILER) $(COMPILER_FLAGS) -o $(BIN_DIR)/test_crossentropyloss_layer $(SRC_DIR)/test_crossentropyloss_layer.cpp  $(INCLUDE_DIR)  $(LDFLAGS) $(LIB_DIR)/libdpl.a


clean:
	rm -rf $(BIN_DIR)/* $(LIB_DIR)/* ./docs/* ./*.o


doxy:
	@doxygen Doxyfile










