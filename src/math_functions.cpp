// Copyright 2013 Yangqing Jia

#include "mkl.h"                                  // add intel MKL library later
#include <iostream>
#include <math.h>
//#include <cblas.h>
#include "math_functions.hpp"

namespace dpl {

    template <>
        void dpl_cpu_gemv<float>(const CBLAS_TRANSPOSE TransA,
                                 const int M,
                                 const int N, 
                                 const float alpha, 
                                 const float* A, 
                                 const float* x,
                                 const float beta, 
                                 float* y)
        {
            cblas_sgemv(CblasRowMajor, TransA, M, N, alpha, A, N, x, 1, beta, y, 1);
        }

    template <>
        void dpl_cpu_gemv<double>(const CBLAS_TRANSPOSE TransA, 
                                  const int M,
                                  const int N, 
                                  const double alpha, 
                                  const double* A, 
                                  const double* x,
                                  const double beta, 
                                  double* y) 
        {
            cblas_dgemv(CblasRowMajor, TransA, M, N, alpha, A, N, x, 1, beta, y, 1);
        }

    template<>
        void dpl_cpu_gemm<float>(const CBLAS_TRANSPOSE TransA,
                                 const CBLAS_TRANSPOSE TransB, 
                                 const int M, 
                                 const int N, 
                                 const int K,
                                 const float alpha, 
                                 const float* A, 
                                 const float* B, 
                                 const float beta,
                                 float* C) 
        {
          int lda = (TransA == CblasNoTrans) ? K : M;
          int ldb = (TransB == CblasNoTrans) ? N : K;
          cblas_sgemm(CblasRowMajor, 
                      TransA, 
                      TransB, 
                      M, 
                      N, 
                      K, 
                      alpha, 
                      A, 
                      lda, 
                      B,
                      ldb, 
                      beta, 
                      C, 
                      N);
        }


    template<>
        void dpl_cpu_gemm<double>(const CBLAS_TRANSPOSE TransA,
                                 const CBLAS_TRANSPOSE TransB, 
                                 const int M, 
                                 const int N, 
                                 const int K,
                                 const double alpha, 
                                 const double* A, 
                                 const double* B, 
                                 const double beta,
                                 double* C) 
        {
          int lda = (TransA == CblasNoTrans) ? K : M;
          int ldb = (TransB == CblasNoTrans) ? N : K;
          cblas_dgemm(CblasRowMajor, 
                      TransA, 
                      TransB, 
                      M, 
                      N, 
                      K, 
                      alpha, 
                      A, 
                      lda, 
                      B,
                      ldb, 
                      beta, 
                      C, 
                      N);
        }



    template <>
        void dpl_axpy<float>(const int N, 
                             const float alpha, 
                             const float* X,
                             float* Y) 
        { 
            cblas_saxpy(N, alpha, X, 1, Y, 1);
        }

    template <>
        void dpl_axpy<double>(const int N, 
                              const double alpha,
                              const double* X,
                              double* Y) 
        { 
            cblas_daxpy(N, alpha, X, 1, Y, 1); 
        }

    template <>
        void dpl_copy<float>(const int N, 
                             const float* X, 
                             float* Y) 
        {
            cblas_scopy(N, X, 1, Y, 1);
        }

    template <>
        void dpl_copy<double>(const int N, 
                              const double* X, 
                              double* Y) 
        {
            cblas_dcopy(N, X, 1, Y, 1);
        }

    template <>
        void dpl_scal<float>(const int N, const float alpha, float *X) 
        {
            cblas_sscal(N, alpha, X, 1);
        }

    template <>
        void dpl_scal<double>(const int N, const double alpha, double *X) 
        {
            cblas_dscal(N, alpha, X, 1);
        }

    template <>
        float dpl_cpu_dot<float>(const int n, const float* x, const float* y) 
        {
            return cblas_sdot(n, x, 1, y, 1);
        }

    template <>
        double dpl_cpu_dot<double>(const int n, const double* x, const double* y) 
        {
            return cblas_ddot(n, x, 1, y, 1);
        }

    template<>
        void dpl_sqr<float>(const int N, float* y)
        {   
            for(int i=0; i<N ;++i)
            {
                y[i] = pow(y[i], 2.0);
            }
        }


    template<>
        void dpl_sqr<double>(const int N, double* y)
        {   
            for(int i=0; i<N ;++i)
            {
                y[i] = pow(y[i], 2.0);
            }
        }

    template<>
        void dpl_add<float>(const int N, const float* a, const float* b, float* y)
        {
            for(int i=0; i<N; i++)
            {
                y[i] = a[i] + b[i];
            }
        }


    template<>
        void dpl_add<double>(const int N, const double* a, const double* b, double* y)
        {
            for(int i=0; i<N; i++)
            {
                y[i] = a[i] + b[i];
            }
        }

    template<>
        void dpl_sub<float>(const int N, const float* a, const float* b, float* y)
        {
            for(int i=0; i<N; i++)
            {
                y[i] = a[i] - b[i];
            }
        }


    template<>
        void dpl_sub<double>(const int N, const double* a, const double* b, double* y)
        {
            for(int i=0; i<N; i++)
            {
                y[i] = a[i] - b[i];
            }
        }


    template <>
        void dpl_mul<float>(const int N, const float* a, const float* b, float* y)
        {
            for(int i=0; i<N; i++)
            {
                y[i] = a[i] * b[i];
            }
        }

    template <>
        void dpl_mul<double>(const int N, const double* a, const double* b, double* y)
        {
            for(int i=0; i<N; i++)
            {
                y[i] = a[i] * b[i];
            }
        }


    template <>
        void dpl_div<float>(const int N, const float* a, const float* b, float* y)
        {
            for(int i=0; i<N; i++)
            {
                y[i] = a[i] / b[i];
            }
        }

    template <>
        void dpl_div<double>(const int N, const double* a, const double* b, double* y)
        {
            for(int i=0; i<N; i++)
            {
                y[i] = a[i] * b[i];
            }
        }


    template <>
        void dpl_powx<float>(const int n, const float* a, const float b, float* y)
        {
            for(int i=0; i<n; i++)
            {
                y[i] = pow(a[i], b);
            }
        }

    template <>
        void dpl_powx<double>(const int n, const double* a, const double b, double* y)
        {
            for(int i=0; i<n; i++)
            {
                y[i] = pow(a[i], b);
            }
        }


    template <>
        void dpl_exp<float>(const int n, const float* a, float* y)
        {
            for(int i=0; i<n; i++)
            {
                y[i] = exp(a[i]);
            }
        }


    template <>
        void dpl_exp<double>(const int n, const double* a, double* y)
        {
            for(int i=0; i<n; i++)
            {
                y[i] = exp(a[i]);
            }
        }




}  // namespace dpl


int main()
{
    int N=10;
    double ar1[N] = {0.0};
    double ar2[N] = {0.0};
    double ar3[N] = {0.0};

    // fill the array
    for(int i=0; i<N ; i++)
    {
        ar1[i] = i;
        ar2[i] = i+1;
    }

    // find dot prooduct
    std::cout <<  dpl::dpl_cpu_dot(N, ar1, ar2) << std::endl;

    // find square of a vector 
    dpl::dpl_powx(N, ar1, 1/2.0, ar3);
    for(int i=0; i<N; i++)
        std::cout << ar3[i] << std::endl;


    // take square of the vector
    dpl::dpl_sqr(N, ar3);
    for(int i=0; i<N; i++)
        std::cout << ar3[i] << std::endl;



    return 1;
}
