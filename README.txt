This project is an alternative to Caffe of BVLC.

-   We will be using google protobuf to generate the setter and getter functions
    for each layer's paramters. Each layer type will have its own set of 
    parameters, which is defined in dpl.proto file.
    For example : If we use FullyConnected Layer, which has number of output
                  neurons, input_data, output_data, grad_from_top, grad_to_bottom,
                  then we will need a method to get and set these variables.
                  Such as numOutputNeurons.set() etc.

-   The dpl.proto is compiled using protoc to generate the getter and setter
    method described above. After compiling, 2 new files *.pb.cc and *.pb.h will
    be created. The header file will contain the methods to set and get the
    variables mentioned for that particular layer.
    Generic command : protoc -I=/path/to/protoc/file protoc/file/name -ccp_out=/path/to/protoc/file
    Our Command : cd proto ; protoc -I=./ ./dpl.proto --cpp_out=./ ; cd ..



