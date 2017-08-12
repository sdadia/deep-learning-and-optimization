#ifndef _BISECTION_METHOD_HPP_
#define _BISECTION_METHOD_HPP_

#include "common.hpp"


namespace dpl
{
    /** 
     * @brief Bisection Method for finding zeros of a function in an interval
     * 
     * @param f [in] Function which takes a single value as input and calculates the output.
     *               The function should save the output by reference.
     * @param left_bound [in] Left bound of the interval 
     * @param right_bound [in] Right bound of the interval
     * @param accuracy [in, default : 1e-6] Accuracy of solution
     * @param to_print [in, default : false] Wether to print details of each step of algorithm
     * 
     * @return Returns the zero location of the function
     */

    double bisectionMethod(void (*f)(double input, double& output), 
            double left_bound, 
            double right_bound, 
            double accuracy=1.0e-6, 
            bool to_print=false);
}

#endif 
