COMPILER=g++ 
CXXFLAGS=  -std=c++14 -O3 -g
LDFLAGS= /usr/lib/x86_64-linux-gnu/libprotobuf.a  # link against static library of protobuf
PROTOSRC= ./proto/dpl.pb.cc 
INCLUDE_DIR= -I./include/ -I./proto/
SRC_DIR=./src
BIN_DIR=./build/bin

test_proto : $(SRC_DIR)/test_proto.cpp
	$(COMPILER) $(CXXFLAGS) -o $(BIN_DIR)/test_protobuf $(SRC_DIR)/test_proto.cpp $(PROTOSRC) $(INCLUDE_DIR)  $(LDFLAGS)








