#include "common.hpp"
#include "bisection_method.hpp"
#include "random_helper.hpp"

void func1(double input, double &output)
{
    output = input*input*input - 3*input + 1;
}


void func2(double input, double &output)
{
    output = pow(input, 3) - 2 * sin(input);
}


void func3(double input, double &output)
{
    output = pow(input, 3) - input - 2;
}


TEST(DISABLED_BisectionMethod, sameSignTest)
{
    dpl::bisectionMethod(func1, 0, 0);

    dpl::bisectionMethod(func2, 0.5, 0.5);
}


TEST(BisectionMethod, Inputs)
{

    auto output2 =dpl::bisectionMethod(func2, 0.5, 2);
    //printf("c : %.10f\n", output2);
    ASSERT_NEAR (output2, 1.236183, 1e-4);


    auto output3 =dpl::bisectionMethod(func3, 1, 2);
    //printf("c : %.10f\n",output3);
    ASSERT_NEAR (output3, 1.521392, 1e-4);
}




int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
