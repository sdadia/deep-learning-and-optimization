
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
BUILD_TYPE=DEBUG




############################# INPUTS  #########################################

SRC_DIR += ./src

INCLUDE_DIR += -I ./include -I /usr/local/include/xtensor-blas/flens/

LDFLAGS += -lgtest -lgmock -lglog -lpthread -lblas


############################# OUTPUTS #########################################

BIN_DIR += ./build/bin
LIB_DIR += ./build/lib
DOCS_DIR += ./docs
# create the above directories - if they exist, they will NOT be overwritten
$(shell mkdir -p $(LIB_DIR) $(BIN_DIR) $(DOCS_DIR))




############################# TARGETS TO CREATE ###############################

# creates the main library
all : libdpl.a

# creates test -  it depends on above libdpl.a library
test : test_sigmoid_layer test_crossentropyloss_layer

# creates Documentation
docs : Doxy

# Remove all the above
clean : Clean

############################### INSTRUCTIONS ##################################



libdpl.a : math_functions.o sigmoid_layer.o common.o crossentropyloss_layer.o
	ar -cvq $(LIB_DIR)/libdpl.a math_functions.o sigmoid_layer.o common.o crossentropyloss_layer.o
	$(eval LDFLAGS += $(LIB_DIR)/libdpl.a) 

common.o : $(SRC_DIR)/common.cpp
	$(COMPILER) $(COMPILER_FLAGS) -c $(SRC_DIR)/common.cpp  $(INCLUDE_DIR)  $(LDFLAGS)

math_functions.o : $(SRC_DIR)/math_functions.cpp
	$(COMPILER) $(COMPILER_FLAGS) -c $(SRC_DIR)/math_functions.cpp  $(INCLUDE_DIR)  $(LDFLAGS)


crossentropyloss_layer.o : $(SRC_DIR)/crossentropyloss_layer.cpp
	$(COMPILER) $(COMPILER_FLAGS) -c $(SRC_DIR)/crossentropyloss_layer.cpp  $(INCLUDE_DIR)  $(LDFLAGS)


sigmoid_layer.o : $(SRC_DIR)/sigmoid_layer.cpp
	$(COMPILER) $(COMPILER_FLAGS) -c $(SRC_DIR)/sigmoid_layer.cpp  $(INCLUDE_DIR)  $(LDFLAGS)


test_sigmoid_layer : $(SRC_DIR)/test_sigmoid_layer.cpp all
	$(COMPILER) $(COMPILER_FLAGS) -o $(BIN_DIR)/test_sigmoid_layer $(SRC_DIR)/test_sigmoid_layer.cpp  $(INCLUDE_DIR)  $(LDFLAGS) 


test_crossentropyloss_layer : $(SRC_DIR)/test_crossentropyloss_layer.cpp all
	$(COMPILER) $(COMPILER_FLAGS) -o $(BIN_DIR)/test_crossentropyloss_layer $(SRC_DIR)/test_crossentropyloss_layer.cpp  $(INCLUDE_DIR)  $(LDFLAGS)


Clean:
	rm -r ./build/ ./docs/ ./*.o

Doxy:
	@doxygen Doxyfile










