////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2012 Bryce Adelstein-Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#include <hpx/util/lightweight_test.hpp>

#include <complex>

/// The C interface for BLAS require complex numbers to be represented by
/// two floating point numbers of the same type that reside in a contiguous
/// block of memory, with the real part first and the imaginary second. This
/// test verifies that std::complex<> fulfills those requirements.

template <
    typename T
>
void test()
{
    std::complex<T> x(17.0, 42.0);

    T* real = (T*) &x;
    T* imag = ((T*) &x) + 1;

    HPX_SANITY(real);

    if (real)
        HPX_TEST_EQ(17.0, *real);

    HPX_SANITY(imag);

    if (imag)
        HPX_TEST_EQ(42.0, *imag);
}

int main()
{
    test<float>();
    test<double>();

    return hpx::util::report_errors();
}

