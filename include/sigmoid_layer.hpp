#ifndef _SIGMOID_LAYER_HPP_
#define _SIGMOID_LAYER_HPP_

#include "common.hpp"

namespace dpl
{
        class SigmoidLayer
        {

        
            public:


                SigmoidLayer();
                

                SigmoidLayer(std::vector<ftensor_t>  &input);


                void setUp(std::vector<ftensor_t>  &input);


                std::vector<ftensor_t> forward();


                void backward();


                void backward(std::vector<ftensor_t> grad_from_top={});
                

                void getTopGradient(std::vector<ftensor_t> top_gradient);


                std::vector<ftensor_t> getTopGradient();


                void getBottomGradient(std::vector<ftensor_t> top_gradient);


                std::vector<ftensor_t> getBottomGradient();


                void setTopGradient(std::vector<ftensor_t> new_top_gradient);


                void setBottomGradient(std::vector<ftensor_t> new_bottom_gradient);
                

            private:
                std::vector<ftensor_t> m_top_gradient;
                std::vector<ftensor_t> m_bottom_gradient;
                std::vector<ftensor_t> m_input;
                std::vector<ftensor_t> m_output;

                unsigned int m_num_inputs = 0;
                unsigned int m_num_outputs = 0;

        };
}

#endif
