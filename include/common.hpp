#ifndef _COMMON_HPP_
#define _COMMON_HPP_


#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <glog/logging.h>       // for CHECK macro
#include <iostream>
#include <vector>
#include <xtensor/xarray.hpp>
#include <xtensor/xio.hpp>
#include <xtensor/xtensor.hpp>
#include <cstddef>
#include <stdexcept>
#include <cstring>
#include <ostream>

#ifndef _MSC_VER
#  if __cplusplus < 201103
#    define CONSTEXPR11_TN
#    define CONSTEXPR14_TN
#    define NOEXCEPT_TN
#  elif __cplusplus < 201402
#    define CONSTEXPR11_TN constexpr
#    define CONSTEXPR14_TN
#    define NOEXCEPT_TN noexcept
#  else
#    define CONSTEXPR11_TN constexpr
#    define CONSTEXPR14_TN constexpr
#    define NOEXCEPT_TN noexcept
#  endif
#else  // _MSC_VER
#  if _MSC_VER < 1900
#    define CONSTEXPR11_TN
#    define CONSTEXPR14_TN
#    define NOEXCEPT_TN
#  elif _MSC_VER < 2000
#    define CONSTEXPR11_TN constexpr
#    define CONSTEXPR14_TN
#    define NOEXCEPT_TN noexcept
#  else
#    define CONSTEXPR11_TN constexpr
#    define CONSTEXPR14_TN constexpr
#    define NOEXCEPT_TN noexcept
#  endif
#endif  // _MSC_VER

class static_string
{
    const char* const p_;
    const std::size_t sz_;

    public:
    typedef const char* const_iterator;

    template <std::size_t N>
        CONSTEXPR11_TN static_string(const char(&a)[N]) NOEXCEPT_TN
        : p_(a)
        , sz_(N-1)
        {}

    CONSTEXPR11_TN static_string(const char* p, std::size_t N) NOEXCEPT_TN
        : p_(p)
        , sz_(N)
        {}

    CONSTEXPR11_TN const char* data() const NOEXCEPT_TN {return p_;}
    CONSTEXPR11_TN std::size_t size() const NOEXCEPT_TN {return sz_;}

    CONSTEXPR11_TN const_iterator begin() const NOEXCEPT_TN {return p_;}
    CONSTEXPR11_TN const_iterator end()   const NOEXCEPT_TN {return p_ + sz_;}

    CONSTEXPR11_TN char operator[](std::size_t n) const
    {
        return n < sz_ ? p_[n] : throw std::out_of_range("static_string");
    }
};

inline
    std::ostream&
operator<<(std::ostream& os, static_string const& s)
{
    return os.write(s.data(), s.size());
}

template <class T>
CONSTEXPR14_TN
    static_string
type_name()
{
#ifdef __clang__
    static_string p = __PRETTY_FUNCTION__;
    return static_string(p.data() + 31, p.size() - 31 - 1);
#elif defined(__GNUC__)
    static_string p = __PRETTY_FUNCTION__;
#  if __cplusplus < 201402
    return static_string(p.data() + 36, p.size() - 36 - 1);
#  else
    return static_string(p.data() + 46, p.size() - 46 - 1);
#  endif
#elif defined(_MSC_VER)
    static_string p = __FUNCSIG__;
    return static_string(p.data() + 38, p.size() - 38 - 7);
#endif
}


    template <class T>
std::vector<T>& operator+=(std::vector<T>& lhs, std::initializer_list<T> l)
{
    lhs.insert(std::end(lhs), l);
    return lhs;
}



typedef xt::xarray_container<xt::uvector<float, std::allocator<float> >, (xt::layout_type)1, std::vector<long unsigned int> > ftensor_t;
typedef xt::xarray_container<xt::uvector<double, std::allocator<double> >, (xt::layout_type)2, std::vector<long unsigned int> > dtensor_t;
typedef unsigned int uint_t;
typedef std::vector<unsigned long int> shape_vec_t;



/* See
http://randomascii.wordpress.com/2012/02/25/comparing-floating-point-numbers-2012-edition/
for thorough information about comparing floating point values.
For this particular application we know that the value range is -1 to 1 (audio signal),
so we can compare to absolute delta of 1/2^22 which is the smallest representable value in
a 22-bit recording.
*/

//const double FLOAT_INEQUALITY_TOLERANCE = double(1e-5);
    template <class T>
::testing::AssertionResult AreFloatingPointArraysEqual(
        const T* const expected,
        const T* const actual,
        unsigned long length,
        const double FLOAT_INEQUALITY_TOLERANCE=1e-6)
{
    ::testing::AssertionResult result = ::testing::AssertionFailure();
    int errorsFound = 0;
    const char* separator = " ";
    for (unsigned long index = 0; index < length; index++)
    {
        if (fabs(expected[index] - actual[index]) > FLOAT_INEQUALITY_TOLERANCE)
        {
            if (errorsFound == 0)
            {
                result << "Differences found:";
            }
            if (errorsFound < 3)
            {
                result << separator
                    << expected[index] << " != " << actual[index]
                    << " @ " << index;
                separator = ", ";
            }
            errorsFound++;
        }
    }
    if (errorsFound > 0)
    {
        result << separator << errorsFound << " differences in total";
        return result;
    }
    return ::testing::AssertionSuccess();
}

#endif 
