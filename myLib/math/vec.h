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


    Vec(Type const& value)
    {
        std::fill_n(m_value, N, value);
    }


    template<typename... Args>
    Vec(Type &&arg1, Type && arg2, Args&&... args)
    {
        static_assert(sizeof...(Args) != N, "Wrong number of arguments.");
        put(arg1, arg2, args...);
    }


    class ExceptionVectorOutofBoundIndex :public std::exception
    {
        const std::string msg = std::string("index is out of vector range (") + std::to_string(N) + ")";
        const char* what() const throw()
        {
                return msg.c_str();
        }
    };


    void fill(Type const& value)
    {
        std::fill_n(m_value, N, value);
    }

    Type& operator[] (uint64_t n)
    {
        if (n >= N)
                throw ExceptionVectorOutofBoundIndex();
        return m_value[n];
    }

    Vec<Type, N>& operator+=(Vec<Type, N> const& other)
    {
        auto plus = std::plus<Type>{};
        //auto mult = std::multiplies<Type>{};
        utils::apply<Type[N], decltype(plus), N>(m_value, plus);
        return *this;
    }

    std::ostream & stream(std::ostream &o) const
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
        put(args...);
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
