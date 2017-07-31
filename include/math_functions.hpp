// Copyright 2013 Yangqing Jia

#ifndef _MATH_FUNCTIONS_HPP_
#define _MATH_FUNCTIONS_HPP_

#include <cblas.h>
//#include "mkl.h"


namespace dpl {

    // Decaf gemm provides a simpler interface to the gemm functions, with the
    // limitation that the data has to be contiguous in memory.
    template <typename Dtype>
    void dpl_cpu_gemm(const CBLAS_TRANSPOSE TransA,
                      const CBLAS_TRANSPOSE TransB,
                      const int M,
                      const int N,
                      const int K,
                      const Dtype alpha,
                      const Dtype* A,
                      const Dtype* B,
                      const Dtype beta,
                      Dtype* C);


    template <typename Dtype>
    void dpl_cpu_gemv(const CBLAS_TRANSPOSE TransA,
                      const int M,
                      const int N,
                      const Dtype alpha,
                      const Dtype* A,
                      const Dtype* x,
                      const Dtype beta,
                      Dtype* y);




    template <typename Dtype>
        void dpl_axpy(const int N,
                      const Dtype alpha,
                      const Dtype* X,
                      Dtype* Y);


    //template <typename Dtype>
        //void dpl_axpby(const int N, const Dtype alpha, const Dtype* X,
                //const Dtype beta, Dtype* Y);


    template <typename Dtype>
        void dpl_copy(const int N,
                      const Dtype *X,
                      Dtype *Y);


    template <typename Dtype>
        void dpl_scal(const int N,
                      const Dtype alpha,
                      Dtype *X);


    template <typename Dtype>
        void dpl_sqr(const int N,  Dtype* y);

    template <typename Dtype>
        void dpl_add(const int N, const Dtype* a, const Dtype* b, Dtype* y);

    template <typename Dtype>
        void dpl_sub(const int N, const Dtype* a, const Dtype* b, Dtype* y);

    template <typename Dtype>
        void dpl_mul(const int N, const Dtype* a, const Dtype* b, Dtype* y);

    template <typename Dtype>
        void dpl_div(const int N, const Dtype* a, const Dtype* b, Dtype* y);

    template <typename Dtype>
        void dpl_powx(const int n, const Dtype* a, const Dtype b, Dtype* y);

    //template <typename Dtype>
        //void dpl_vRngUniform(const int n, Dtype* r, const Dtype a, const Dtype b);

    //template <typename Dtype>
        //void dpl_vRngGaussian(const int n, Dtype* r, const Dtype a,
                //const Dtype sigma);

    template <typename Dtype>
        void dpl_exp(const int n, const Dtype* a, Dtype* y);

    template <typename Dtype>
        Dtype dpl_cpu_dot(const int n,
                          const Dtype* x,
                          const Dtype* y);


}  // namespace dpl


#endif  // _MATH_FUNCTIONS_HPP_
