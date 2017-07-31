#ifndef _TENSOR_HPP_
#define _TENSOR_HPP_

#include <iostream>
#include <vector>
#include <glog/logging.h> // for CHECK_  Macro

namespace dpl
{
    class Tensor
    {
        private:
            float* m_data=nullptr;
            std::vector<int> m_shape;
            int m_num_dimensions=0;
            int m_count_=0;
            std::vector<int> m_index_vector;

            int m_sum(std::vector<int> shape);
            void m_set_count(std::vector<int> shape);
            void setShape(std::vector<int> shape);

            int m_find_stride(int dim)
            {
                int stride=1;
                for(int i=0; i<dim; i++)
                {
                    stride*=m_shape[i];
                }
                return stride;
            }

        public:


            template<typename... Args>
                int at(const int &first, const Args&... args)
                {
                    m_index_vector.clear();
                    m_index_vector.push_back(first);
                    int dummy[] = { 0, (m_index_vector.push_back(args), 0)...}; // all magic is here
                    (void) dummy; // Avoid unused variable warning.
                    
                    // check if the dimensions provided are less than the total number of dimensions
                    CHECK_LE(m_index_vector.size(),m_num_dimensions) << " Number of dimensions indices are greater than the total number of dimensions"; 

                    return find_offset(m_index_vector);
                }

            int find_offset(std::vector<int> index_vector)
            {
                int offset=0;
                for(int i=m_num_dimensions-1 ; i>=0 ; i--)
                {
                    if(i==1)
                    {
                        int stride = m_shape[1];
                        offset += index_vector[0] * stride + index_vector[1];
                        return offset;
                    }
                    else
                    {
                        std::cout << "Stride is : " << m_find_stride(i) << std::endl;
                        offset += index_vector[i] * m_find_stride(i);
                    }
                }


            }


            Tensor();

            Tensor(float* data, 
                    std::vector<int> shape);

            Tensor(std::vector<int> shape);

            void setNewData(float* newData);

            void copyData(float* newData);

            float* getData();

            void deleteData();

            std::vector<int> getShape();

            void reshape(std::vector<int> shape);

            void copyFromTensor(Tensor* otherTensor);

            int getCount();

            void reset();


    };
}

#endif 
