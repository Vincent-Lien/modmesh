#pragma once

/*
 * Copyright (c) 2019, Yung-Yu Chen <yyc@solvcon.net>
 * BSD 3-Clause License, see COPYING
 */

#include <type_traits>
#include <cmath>

namespace modmesh
{

namespace detail
{

template <typename T>
inline constexpr T pow(T /*base*/, std::integral_constant<size_t, 0> /*unused*/) { return 1; }

template <typename T>
inline constexpr T pow(T base, std::integral_constant<size_t, 1> /*unused*/) { return base; }

template <typename T, size_t N>
inline constexpr T pow(T base, std::integral_constant<size_t, N> /*unused*/)
{
    return pow(base, std::integral_constant<size_t, N - 1>()) * base;
}

template <typename T>
constexpr T pi_v = std::enable_if_t<std::is_floating_point_v<T>, T>(3.141592653589793238462643383279502884L);

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
}; /* end class ComplexImpl */

} /* end namespace detail */

template <size_t N, typename T>
inline constexpr T pow(T base)
{
    return detail::pow(base, std::integral_constant<size_t, N>());
}

template <typename T>
constexpr T pi = detail::pi_v<T>;

template <typename T>
using Complex = detail::ComplexImpl<T>;

} /* end namespace modmesh */

// vim: set ff=unix fenc=utf8 et sw=4 ts=4 sts=4:
