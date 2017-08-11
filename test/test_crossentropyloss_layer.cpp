#include "crossentropyloss_layer.hpp"
#include "common.hpp"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <glog/logging.h>




TEST(CrossEntropyLossLayer, CheckNumInputs)
{
    // if zero inputs, then a problem will occour
    std::vector<dtensor_t> input(2);
    std::vector<dtensor_t> labels(2);

    dpl::CrossEntropyLossLayer p;
    p.setUp(input, labels);
}


TEST(CrossEntropyLossLayer, forward)
{

    // input, label, and true value
    dtensor_t p1{123, 456, 789}, p2{1, -2, 0}, p3 {0.5,-1, 0};
    dtensor_t l1{1,0,0}, l2{0,1,0}, l3{0,0,1};
    dtensor_t t1{0.0,0.0,1.0}, t2{0.705384,0.035119, 0.259496}, t3{0.546549,0.121951,0.331498};


    std::vector<dtensor_t> input{p1,p2,p3}, labels{l1,l2,l3}, true_values{t1,t2,t3};

    dpl::CrossEntropyLossLayer p;
    p.setUp(input, labels);
    auto output = p.forward();


    for(uint_t i=0; i<output.size(); i++)
    {
        auto output_raw_data = output[i].raw_data();
        auto true_value_raw_data = true_values[i].raw_data();
        EXPECT_TRUE(AreFloatingPointArraysEqual(output_raw_data, true_value_raw_data, output[i].size()));
    }
}

TEST(CrossEntropyLossLayer, backward)
{

    // input, label, and true value
    dtensor_t p1{123, 456, 789}, p2{1, -2, 0}, p3 {0.5,-1, 0};
    dtensor_t l1{1,0,0}, l2{0,1,0}, l3{0,0,1};
    dtensor_t t1{0.0,0.0,1.0}, t2{0.705384,0.035119, 0.259496}, t3{0.546549,0.121951,0.331498};
    //dtensor_t g1{}


    std::vector<dtensor_t> input{p1,p2,p3}, labels{l1,l2,l3}, true_values{t1,t2,t3};

    dpl::CrossEntropyLossLayer p;
    p.setUp(input, labels);
    auto output = p.forward();


    for(uint_t i=0; i<output.size(); i++)
    {
        auto output_raw_data = output[i].raw_data();
        auto true_value_raw_data = true_values[i].raw_data();
        EXPECT_TRUE(AreFloatingPointArraysEqual(output_raw_data, true_value_raw_data, output[i].size()));
    }
}



int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
