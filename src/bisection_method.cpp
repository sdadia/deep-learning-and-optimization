#include "common.hpp"
#include "bisection_method.hpp"
#include <thread>
#include <iostream>
#include <cmath>

namespace dpl
{
    double bisectionMethod(void (*f)(double input, double& output), 
            double left_bound, 
            double right_bound, 
            double accuracy, 
            bool to_print)
    {
        double middle_bound = 0, fa = 0, fb = 0, fc = 0, error = right_bound-left_bound;
        int num_iterations = (ceil(std::log10(right_bound-left_bound) - std::log10(2*accuracy)) / std::log10(2))+5;


        std::thread thread_fa(f, left_bound, std::ref(fa));
        std::thread thread_fb(f, right_bound, std::ref(fb));

        thread_fa.join();
        thread_fb.join();

        // check is f(left_bound) and f(right_bound) are opposite or not
        CHECK_EQ(sameSign(fa, fb), false)  << "f(left_bound) and f(right_bound) are of same sign\n"; 

        for(int i=0; i<num_iterations; ++i)
        {
            error = error/2;
            middle_bound = left_bound + error;

            std::thread thread_fc(f, middle_bound, std::ref(fc));
            thread_fc.join();

            if(to_print)
            {
                printf("Iter : %d\t\t",i);
                printf("middle_bound : %.10f\t\t",middle_bound);
                printf("f(middle_bound) : %.10f\t\t",fc);
                printf("Error : %.10f\n", error);
            }



            if(fabs(error) < accuracy )
            {
                printf("Converged\n");
                return middle_bound;
            }

            if(sameSign(fa, fc)==false)
            {
                right_bound = middle_bound;
                fb = fc;

                std::thread thread_fb(f, right_bound, std::ref(fb));
                thread_fb.join();
            }
            else
            {
                left_bound = middle_bound;
                fa = fc;

                std::thread thread_fa(f, left_bound, std::ref(fa));
                thread_fa.join();
            }


        }

        return middle_bound;
    }
}
