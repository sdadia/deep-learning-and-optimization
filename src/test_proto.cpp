#include <iostream>
#include "../proto/dpl.pb.h"


int main()
{
    GOOGLE_PROTOBUF_VERIFY_VERSION;                         // checks if the .proto file is compiled with same protobuf version

    dpl::FullyConnected mylayer;                            // initialise an instance of the class - each 

    // setter functions - begin with "set"
    mylayer.set_name("fc1");                                // set the parametrs
    mylayer.set_numoutputneurons(10);
    mylayer.set_numinputneurons(10);


    // getter function - begin with paramter itself
    std::cout << mylayer.name() << std::endl;               // get the parameters
    std::cout << mylayer.numoutputneurons() << std::endl;

    return 1;
}
