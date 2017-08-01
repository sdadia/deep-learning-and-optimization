#ifndef _SIGMOID_LAYER_WITH_LOSS_HPP_
#define _SIGMOID_LAYER_WITH_LOSS_HPP_

#include "common.hpp"

namespace dpl
{
    class CrossEntropyLossLayer
    {
        public:
            CrossEntropyLossLayer();


            CrossEntropyLossLayer(std::vector<dtensor_t> &input, std::vector<dtensor_t> &labels);


            void setUp(std::vector<dtensor_t>  &input,
                       std::vector<dtensor_t> &labels);


            std::vector<dtensor_t> forward();


            void backward();


            void backward(std::vector<dtensor_t> grad_from_top);


            void getTopGradient(std::vector<dtensor_t> top_gradient);


            std::vector<dtensor_t> getTopGradient();


            void getBottomGradient(std::vector<dtensor_t> top_gradient);


            std::vector<dtensor_t> getBottomGradient();


            void setTopGradient(std::vector<dtensor_t> new_top_gradient);


            void setBottomGradient(std::vector<dtensor_t> new_bottom_gradient);


            void getLoss(std::vector<dtensor_t> loss);


            std::vector<dtensor_t> getLoss();


            void setLoss(std::vector<dtensor_t> loss);





        private:
            std::vector<dtensor_t> m_top_gradient;
            std::vector<dtensor_t> m_bottom_gradient;
            std::vector<dtensor_t> m_input;
            std::vector<dtensor_t> m_output;
            std::vector<dtensor_t> m_labels;
            std::vector<dtensor_t> m_loss;


            unsigned int m_num_inputs = 0;
            unsigned int m_num_outputs = 0;




    };
}


#endif
