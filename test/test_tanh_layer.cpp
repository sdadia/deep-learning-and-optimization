#include "tanh_layer.hpp"
#include "common.hpp"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <glog/logging.h>


// it should give an error when no input is given
TEST(DISABLED_TanhLayer, NoInputTest)
{

    std::vector<ftensor_t> ins;

    dpl::TanhLayer tanh1(ins);
}



TEST(TanhLayer, InputTest)
{

    ftensor_t f1{0.1, 0.2, 0.3}, f2 {-0.1, -0.2, -0.3};

    std::vector<ftensor_t> ins{f1,f2}, outs;
    outs = ins;

    dpl::TanhLayer tanh1(ins);

}


TEST(TanhLayer, forward)
{

    ftensor_t f1{0.1, 0.2, 0.3}, f2 {-0.1, -0.2, -0.3};
    ftensor_t t1{0.099667, 0.197375, 0.291312}, t2{-0.099667, -0.197375, -0.291312};

    std::vector<ftensor_t> ins{f1,f2}, outs, true_values{t1,t2};

    dpl::TanhLayer tanh1(ins);
    outs = tanh1.forward();

    for(uint_t i=0; i<outs.size(); i++)
    {
        auto output_raw_data = outs[i].raw_data();
        auto true_value_raw_data = true_values[i].raw_data();

        EXPECT_TRUE(AreFloatingPointArraysEqual(output_raw_data, true_value_raw_data, outs[i].size()));
    }

}

int main(int argc, char** argv)
{


    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();


}
