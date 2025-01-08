/*
 * Copyright (c) 2025, Chun-Hsu Lai <as2266317@gmail.com>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 * - Neither the name of the copyright holder nor the names of its contributors
 *   may be used to endorse or promote products derived from this software
 *   without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <type_traits>
#include <cmath>

namespace modmesh
{

namespace detail
{
template <typename T, typename = std::enable_if_t<std::is_arithmetic<T>::value>>
struct ComplexImpl
{
    T real_v;
    T imag_v;

    explicit ComplexImpl()
        : ComplexImpl(0.0, 0.0)
    {
    }

    explicit ComplexImpl(T r, T i)
        : real_v(r)
        , imag_v(i)
    {
    }

    explicit ComplexImpl(const ComplexImpl & other)
        : real_v(other.real_v)
        , imag_v(other.imag_v)
    {
    }

    ComplexImpl operator+(const ComplexImpl & other) const
    {
        return ComplexImpl(real_v + other.real_v, imag_v + other.imag_v);
    }

    ComplexImpl operator-(const ComplexImpl & other) const
    {
        return ComplexImpl(real_v - other.real_v, imag_v - other.imag_v);
    }

    ComplexImpl operator*(const ComplexImpl & other) const
    {
        return ComplexImpl(real_v * other.real_v - imag_v * other.imag_v, real_v * other.imag_v + imag_v * other.real_v);
    }

    ComplexImpl operator/(const T & other) const
    {
        return ComplexImpl(real_v / other, imag_v / other);
    }

    ComplexImpl & operator=(const ComplexImpl & other)
    {
        if (this != &other) // Check for self-assignment
        {
            real_v = other.real_v;
            imag_v = other.imag_v;
        }
        return *this;
    }

    ComplexImpl & operator+=(const ComplexImpl & other)
    {
        real_v += other.real_v;
        imag_v += other.imag_v;
        return *this;
    }

    ComplexImpl & operator-=(const ComplexImpl & other)
    {
        real_v -= other.real_v;
        imag_v -= other.imag_v;
        return *this;
    }

    T real() const { return real_v; }
    T imag() const { return imag_v; }
    T norm() const { return real_v * real_v + imag_v * imag_v; }
}; /* end struct ComplexImpl */

} /* end namespace detail */

template <typename T>
using Complex = detail::ComplexImpl<T>;

} /* end namespace modmesh */

// vim: set ff=unix fenc=utf8 et sw=4 ts=4 sts=4: