#include <iostream>
#include "common.hpp"
#include "crossentropyloss_layer.hpp"
#include <glog/logging.h>       // for CHECK macro
#include "xtensor-blas/xlinalg.hpp"
#include <algorithm>    // std::max



namespace dpl
{
    CrossEntropyLossLayer::CrossEntropyLossLayer(){}

    CrossEntropyLossLayer::CrossEntropyLossLayer(std::vector<dtensor_t> &input, std::vector<dtensor_t> &labels)
    {
        setUp(input, labels);
    }

    void CrossEntropyLossLayer::setUp(std::vector<dtensor_t>  &input,
            std::vector<dtensor_t> &labels)
    {
        CHECK_GE(input.size(), 1) << "Atleast 1 input tensor is required";         // check number of inputs == 1
        CHECK_EQ(input.size(), labels.size()) << "Number of label tensor and Number of prediction tensors are different";


        // set number of inputs and outputs
        m_num_inputs = input.size();
        m_num_outputs = input.size();

        // setup the size of top and bottom gradient
        m_input.resize(m_num_inputs);
        m_output.resize(m_num_inputs);
        m_top_gradient.resize(m_num_inputs);
        m_bottom_gradient.resize(m_num_inputs);
        m_labels.resize(labels.size());
        m_loss.resize(m_num_inputs);


        // set the data pointers of inputs and outputs properly
        for(unsigned int i=0; i<m_num_inputs; i++)
        {

            auto shape = input[i].shape();
            auto count = input[i].size();
            m_input[i].reshape(shape);
            m_output[i].reshape(shape);
            m_top_gradient[i].reshape({1});
            m_bottom_gradient[i].reshape({1});

            m_input[i] = input[i];
            m_labels[i] = labels[i];

            count = m_top_gradient[i].size();

            for(unsigned int k=0; k<count; k++) // set bottom and top gradient
            {
                m_bottom_gradient[i][k] = 1.0;
                m_top_gradient[i][k] = 1.0;
            }
        }


        return ;
    }

    std::vector<dtensor_t> CrossEntropyLossLayer::forward()
    {
        // move along each input
        for(uint_t input_number=0; input_number<m_num_inputs; input_number++)
        {
            auto prediction = m_input[input_number];
            auto labels = m_labels[input_number];
            auto loss = m_output[input_number];

            auto prediction_raw_data = prediction.raw_data();

            auto max_value= *std::max_element((prediction_raw_data), (prediction_raw_data+prediction.size()));
            //std::cout << "Max value is : " << max_value << std::endl;

            // normalise prediction by softmax between [0,1]
            prediction = prediction-max_value;
                //std::cout << prediction << std::endl;
            auto prediction_softmax = xt::exp(prediction);
                //std::cout << prediction_softmax << std::endl;
            auto prediction_softmax_sum = xt::sum(prediction_softmax);
                //std::cout << prediction_softmax_sum << std::endl;

            auto normalised_prediction = prediction_softmax / prediction_softmax_sum;

            m_output[input_number] = normalised_prediction;
            //std::cout << "Softmax is  : " << normalised_prediction << std::endl;
            //std::cout << "Softmax is  : " << m_output[input_number] << std::endl;

            prediction = normalised_prediction;

            // calculate CE loss = -1 * sum( labels * log(prediction) )
            loss = -1 * xt::linalg::dot(labels, xt::log(normalised_prediction)) ;

            //m_output[input_number] = normalised_prediction;
            m_loss[input_number] = dtensor_t{loss};
        }

        return m_output;
    }

    void CrossEntropyLossLayer::backward()
    {

        // move along each input
        for(uint_t input_number=0; input_number<m_num_inputs; input_number++)
        {
            auto normalised_prediction = m_input[input_number];
            auto labels = m_labels[input_number];
            const auto top_gradient = m_top_gradient[input_number];  // top_grad = gradient from top
            auto bottom_gradient = m_bottom_gradient[input_number];  // bottom_grad = top_grad * local_grad
            auto loss = m_output[input_number];

            bottom_gradient = (labels - normalised_prediction) * top_gradient;
        }

    }

    void CrossEntropyLossLayer::backward(std::vector<dtensor_t> grad_from_top)
    {

        // move along each input
        for(uint_t input_number=0; input_number<m_num_inputs; input_number++)
        {
            auto normalised_prediction = m_input[input_number];
            auto labels = m_labels[input_number];
            const auto top_gradient = grad_from_top[input_number];  // top_grad = gradient from top
            auto bottom_gradient = m_bottom_gradient[input_number];  // bottom_grad = top_grad * local_grad
            auto loss = m_output[input_number];

            bottom_gradient = (labels - normalised_prediction) * top_gradient;
        }

    }

    std::vector<dtensor_t> CrossEntropyLossLayer::getLoss()
    {
        return m_loss;
    }
}


