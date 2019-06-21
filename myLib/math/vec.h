#pragma once

#include <stdint.h>
#include <string>
#include <cstring>
#include <exception>
#include <ostream>
#include <algorithm>

#include "myLib/list_utils/list_utils.h"
#include "myLib/string_utils.h"
#include "myLib/type_utils.h"
#include "myLib/string_utils.h"

namespace maths
{

template< typename Type, uint64_t N>
class Vec
{

public:

    Vec()
    {
        std::memset(m_value, 0, sizeof(Type) * N);
    }

    Vec(const Type *values)
    {
        std::memcpy(m_value, values, sizeof(Type) * N);
    }

    Vec(Type *values)
    {
        std::memcpy(m_value, values, sizeof(Type) * N);
    }

    Vec(Type &&arg)
    {
        std::fill_n(m_value, N, arg);
    }

    Vec(Type const& arg)
    {

        std::fill_n(m_value, N, arg);

    }

    template<typename... Args>
    Vec(Type &&arg ,Args&&... args)
    {
        static_assert (sizeof...(args) == N -1 ,"wrong number of parameters");
        put(std::forward<Type>(arg), std::forward<Args>(args)...);
    }

    template<typename... Args>
    Vec(Type const& arg ,Args const &... args)
    {
        static_assert (sizeof...(args) == N -1 , "wrong number of parameters");
        put(arg , args...);
    }


    Vec(const Vec<Type,N>& other)
    {
        std::copy_n(other.m_value, N, this->m_value);
    }

    Vec(Vec<Type,N>&& other)
    {
        this->m_value = std::move(other.m_value);
    }


    class ExceptionVectorOutofBoundIndex :public std::exception
    {
        const std::string msg = std::string("index is out of vector range (") + std::to_string(N) + ")";
        const char* what() const throw()
        {
                return msg.c_str();
        }
    };

    Type& operator[] (uint64_t n)
    {
        if (n >= N)
                throw ExceptionVectorOutofBoundIndex();
        return m_value[n];
    }

    Vec<Type, N>& operator+=(Vec<Type, N> const& other)
    {
        auto plus = std::plus<Type>{};
        utils::apply<Type[N], decltype(plus), N>(m_value, other,m_value , plus);
        return *this;
    }

    Vec<Type, N> operator+(Vec<Type, N> const& other)
    {
        Vec<Type, N> newVal;
        auto plus = std::plus<Type>{};
        utils::apply<Type[N], decltype(plus), N>(m_value, other, newVal->m_value , plus);
        return newVal;
    }

    std::ostream& stream(std::ostream &o) const
    {
            utils::stream_list<Type[N], N>(o, m_value);
            return o;
    }

 private:

    Type m_value[N];

    template<typename Arg, typename... Args>
    void put(Arg && arg, Args&&... args)
    {
        m_value[N - (sizeof...(Args)) - 1] = arg;
        put(std::forward<Args>(args)...);
    }

    template<typename Arg>
    void put(Arg && arg)
    {
            m_value[N - 1] = arg;
    }
};


template<typename Type, uint64_t N>
std::ostream & operator << (std::ostream &o, const Vec<Type, N> & vec)
{
    o << "{";
    vec.stream(o);
    o << "}";
    return o;
}

}// namespace maths
