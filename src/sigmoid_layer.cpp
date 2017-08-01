#include <iostream>
#include <vector>
#include <xtensor/xarray.hpp>
#include <xtensor/xio.hpp>
#include <xtensor/xtensor.hpp>
#include <glog/logging.h>       // for check macro
#include "common.hpp"
#include "sigmoid_layer.hpp"




namespace dpl
{


    SigmoidLayer::SigmoidLayer()
    {}

    SigmoidLayer::SigmoidLayer(std::vector<ftensor_t>  &input)
    {
        this->setUp(input);
    }

    void SigmoidLayer::setUp(std::vector<ftensor_t>  &input)
    {
        CHECK_GE(input.size(), 1) << "Atleast 1 input tensor is required";         // check number of inputs == 1

        // set number of inputs and outputs
        m_num_inputs = input.size();
        m_num_outputs = input.size();

        //std::cout << "Number of inputs " << m_num_inputs << "\n";
        //std::cout << "Number of outputs " << m_num_outputs << "\n";

        // setup the size of top and bottom gradient
        m_input.resize(m_num_inputs);
        m_output.resize(m_num_inputs);
        m_top_gradient.resize(m_num_inputs);
        m_bottom_gradient.resize(m_num_inputs);



        // set the data pointers of inputs and outputs properly
        for(unsigned int i=0; i<m_num_inputs; i++)
        {
            auto shape = input[i].shape();
            auto count = input[i].size();
            m_input[i].reshape(shape);
            m_output[i].reshape(shape);
            m_top_gradient[i].reshape(shape);
            m_bottom_gradient[i].reshape(shape);

            m_input[i] = input[i];

            for(unsigned int k=0; k<count; k++)
            {
                m_bottom_gradient[i][k] = 1.0;
                m_top_gradient[i][k] = 1.0;
            }
        }


        return ;
    }


    std::vector<ftensor_t> SigmoidLayer::forward()
    {
        // iterate over each input vector
        for(unsigned int input_number=0; input_number<m_num_inputs; input_number++)
        {
            auto shape = m_input[input_number].shape();
            auto count = m_input[input_number].size();

            //flatten input and output
            m_input[input_number].reshape({count}); // flatten the input vector
            m_output[input_number].reshape({count}); // flatten the output vector

            //apply sigmoid to each element of the input
            for(unsigned int i=0; i<m_input[input_number].size(); i++)
            {
                m_output[input_number][i] = 1 / (1+exp(-1.0 * m_input[input_number][i])); // 1 / 1 + exp(-x)
            }

            //un-flatten input and output
            m_input[input_number].reshape(shape);
            m_output[input_number].reshape(shape);



        }
        return m_output;
    }


    void SigmoidLayer::backward()
    {
        // iterate over each input vector
        for(unsigned int input_number=0; input_number<m_num_inputs; input_number++)
        {
            std::cout << "Input vector : " << input_number << "\n";
            auto shape = m_input[input_number].shape();
            unsigned int count = m_input[input_number].size();


            // get pointers to raw data
            const auto output_data = m_output[input_number].raw_data();         // sigmoid(x)
            const auto top_gradient = m_top_gradient[input_number].raw_data();  // top_grad = gradient from top
            auto bottom_gradient = m_bottom_gradient[input_number].raw_data();  // bottom_grad = top_grad * local_grad

            for(unsigned int i=0; i<count; i++)
            {
                bottom_gradient[i] =  top_gradient[i] * output_data[i] * (1-output_data[i]); // bottom = top * sigmoid *(1-sigmoid)
                //std::cout << input_data[i] << ", " << output_data[i] << ", " << bottom_gradient[i] << ", " << top_gradient[i] << std::endl;
            }
            std::cout << m_input[input_number] << std::endl;
            std::cout << m_output[input_number] << std::endl;
            std::cout << m_top_gradient[input_number] << std::endl;
            std::cout << m_bottom_gradient[input_number] << std::endl;
        }

    }


    void SigmoidLayer::backward(std::vector<ftensor_t> grad_from_top)
    {
        if(grad_from_top.size() != 0)
            m_top_gradient = grad_from_top;
      
        // iterate over each input vector
        for(unsigned int input_number=0; input_number<m_num_inputs; input_number++)
        {
            std::cout << "Input vector : " << input_number << "\n";
            auto shape = m_input[input_number].shape();
            unsigned int count = m_input[input_number].size();


            // get pointers to raw data
            const auto output_data = m_output[input_number].raw_data();         // sigmoid(x)
            const auto top_gradient = m_top_gradient[input_number].raw_data();  // top_grad = gradient from top
            auto bottom_gradient = m_bottom_gradient[input_number].raw_data();  // bottom_grad = top_grad * local_grad

            for(unsigned int i=0; i<count; i++)
            {
                bottom_gradient[i] =  top_gradient[i] * output_data[i] * (1-output_data[i]); // bottom = top * sigmoid *(1-sigmoid)
                //std::cout << input_data[i] << ", " << output_data[i] << ", " << bottom_gradient[i] << ", " << top_gradient[i] << std::endl;
            }
            std::cout << m_input[input_number] << std::endl;
            std::cout << m_output[input_number] << std::endl;
            std::cout << m_top_gradient[input_number] << std::endl;
            std::cout << m_bottom_gradient[input_number] << std::endl;
        }

    }


    void SigmoidLayer::getTopGradient(std::vector<ftensor_t> top_gradient)
    {
        top_gradient = m_top_gradient;
    }


    std::vector<ftensor_t> SigmoidLayer::getTopGradient()
    {

        return m_top_gradient;
    }


    void SigmoidLayer::getBottomGradient(std::vector<ftensor_t> top_gradient)
    {
        top_gradient = m_top_gradient;
    }


    std::vector<ftensor_t> SigmoidLayer::getBottomGradient()
    {

        return m_top_gradient;
    }

    void SigmoidLayer::setTopGradient(std::vector<ftensor_t> new_top_gradient)
    {
        CHECK_EQ(m_top_gradient.size(), new_top_gradient.size()); // check if input is equal
        m_top_gradient = new_top_gradient;
    }


    void SigmoidLayer::setBottomGradient(std::vector<ftensor_t> new_bottom_gradient)
    {
        CHECK_EQ(m_bottom_gradient.size(), new_bottom_gradient.size()); // check if input is equal
        m_bottom_gradient = new_bottom_gradient;
    }

};


