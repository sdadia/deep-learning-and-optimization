#include "sigmoid_layer.hpp"
#include "common.hpp"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <glog/logging.h>



TEST(SigmoidLayer, check_num_outputs_in_forward)
{
    std::vector<ftensor_t> tensor_vector, output; // create a vector


    tensor_vector.clear();

    ftensor_t f1, f2, f3, f4;             
    f1 = {1.0};
    f2 = {1.235, 0.22};
    f3 = {1.0, 3.0, 0.8};

    tensor_vector.push_back(f1);
    tensor_vector.push_back(f2);
    tensor_vector.push_back(f3);

    dpl::SigmoidLayer p(tensor_vector);
    output = p.forward();

    ASSERT_EQ(tensor_vector.size(), output.size());

    for(uint_t i=0; i<tensor_vector.size(); i++)
    {
        ASSERT_EQ(tensor_vector[i].size(), output[i].size());
    }
}


TEST(DISABLED_SigmoidLayer, check_forward_prop)
{
    std::vector<ftensor_t> tensor_vector, expected_answer; // create a vector

    ftensor_t f1, f2, f3;             
    ftensor_t out_f1, out_f2, out_f3;
    ftensor_t exp;

    f1 = {1.0};
    f2 = {1.235, 0.22};
    f3 = {1.0, 3.0, 0.8};

    out_f1 = {0.731058};
    out_f2 = {0.774692, 0.554779};
    out_f3 = {0.731058, 0.952574, 0.689974};

    //tensor_vector.push_back(f1);
    tensor_vector.push_back(f2);
    tensor_vector.push_back(f3);

    //expected_answer.push_back(out_f1);
    expected_answer.push_back(out_f2);
    expected_answer.push_back(out_f3);

    dpl::SigmoidLayer p(tensor_vector);
    auto output = p.forward();

    for(uint_t i=0; i<tensor_vector.size(); i++)
    {
        auto output_raw_data = output[i].raw_data();
        auto true_values_raw_raw_data = expected_answer[i].raw_data();
        EXPECT_TRUE(AreFloatingPointArraysEqual(output_raw_data, true_values_raw_raw_data, output[i].size(), 1e-6));
    }
}


int main(int argc, char **argv) 
{
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
