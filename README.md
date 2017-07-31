# DPL (DEEP LEARNING LIBRARY)

### Dependencies

- Xtensor : https://github.com/QuantStack/xtensor
- BLAS & LAPACK
- Gtest : https://github.com/google/googletest
- Cmake
- Make
- Doxygen
- Git


### Install Dependencies

```
sudo apt-get update ; sudo apt-get upgrade
```

- BLAS and LAPACK, Make, libstdc++, GCC, Doxygen, Gtest:

```
sudo apt-get install build-essential git
sudo apt-get install libblas-dev liblapack-dev libgtest-dev doxygen
```

- Xtensor : https://github.com/QuantStack/xtensor

```
cd $HOME ; git clone https://github.com/QuantStack/xtensor
cd xtensor; mkdir build && cd build;
cmake -DBUILD_TESTS=ON -DDOWNLOAD_GTEST=ON ..
make
make xtest
sudo make install

```


### Compilation & Install
This will create static library in **build/lib** & executibles in **build/bin/**

```
mkdir -p build/bin build/lib
make
```

