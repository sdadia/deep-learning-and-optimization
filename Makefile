COMPILER=g++ 
CXXFLAGS=-std=c++14 -O3 -ggdb
LDFLAGS =/usr/lib/x86_64-linux-gnu/libprotobuf.a  # link against static library of protobuf
PROTOSRC=./proto/dpl.pb.cc 
MKLROOT =/opt/intel/mkl
INCLUDE_DIR=-I./include/ -I./proto/ -m64 -I${MKLROOT}/include 
SRC_DIR=./src
BIN_DIR=./build/bin
LIB_DIR=./build/lib

# for MKL library
LDFLAGS+=-Wl,--start-group ${MKLROOT}/lib/intel64/libmkl_intel_lp64.a ${MKLROOT}/lib/intel64/libmkl_sequential.a ${MKLROOT}/lib/intel64/libmkl_core.a -Wl,--end-group -lpthread -lm -ldl -lgomp  

all : test_proto test_math_functions 

test_proto : $(SRC_DIR)/test_proto.cpp
	$(COMPILER) $(CXXFLAGS) -o $(BIN_DIR)/test_protobuf $(SRC_DIR)/test_proto.cpp $(PROTOSRC) $(INCLUDE_DIR)  $(LDFLAGS)

test_math_functions : $(SRC_DIR)/math_functions.cpp
	$(COMPILER) $(CXXFLAGS) -o $(BIN_DIR)/test_math_functions $(SRC_DIR)/math_functions.cpp $(PROTOSRC) $(INCLUDE_DIR)  $(LDFLAGS)



clean:
	rm -rf $(BIN_DIR)/* $(LIB_DIR)/* 









