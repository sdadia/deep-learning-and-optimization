<p align="center"> 
![DPLO](.dpl_logo.png)
</p>

## Dependencies

- Xtensor : https://github.com/QuantStack/xtensor
- BLAS & LAPACK
- Gtest : https://github.com/google/googletest
- Cmake
- Make
- Doxygen
- Git


## Install Dependencies

<!--```-->
    sudo apt-get update ; sudo apt-get upgrade
<!--```-->

- BLAS and LAPACK, Make, libstdc++, GCC, Doxygen, Gtest:

<!--```-->
    sudo apt-get install build-essential git libblas-dev liblapack-dev libgtest-dev doxygen
<!--```-->

- Xtensor : https://github.com/QuantStack/xtensor

<!--```-->
    cd $HOME ; git clone https://github.com/QuantStack/xtensor
    cd xtensor; mkdir build && cd build;
    cmake -DBUILD_TESTS=ON -DDOWNLOAD_GTEST=ON ..
    make
    make xtest
    sudo make install

<!--```-->


## Compilation & Install
This will create static library in **build/lib** & executibles in **build/bin/**

<!--```-->
    make all -j4 -s -O      # to make static library and test executible
    make docs               # to create documentation

    make clean # to remove all the above
<!--```-->


## Create new layer
Just create a new .hpp and .cpp file with the corresponding layer name
* implement setUp(), forward(), backward() functions

**sigmoid.hpp**
<!--```-->
    #include "common.hpp"

    namespace dpl
    {
        class MySigmoidLayer
        {
            void setUp(std::vector<ftensor_t> inputs);

            void forward();

            void backward(std::vector<ftensor_t> grad_from_top);
        }
    }

<!--```-->



**sigmoid.cpp**
<!--```-->
    #include "common.hpp"
    #include "sigmoid.hpp"

    namespace dpl
    {
        void MySigmoidLayer::setUp(std::vector<ftensor_t> inputs)
        {
            // code here
        }

        void MySigmoidLayer::forward()
        {
            // forward prop code here
        }   

        void MySigmoidLayer::backward(std::vector<ftensor_t> grad_from_top)
        {
            // back prop code here
        }
        
    }

<!--```-->
