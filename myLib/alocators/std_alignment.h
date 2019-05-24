#pragma once

#include <iostream>
#include <tuple>
#include <type_traits>


////////////////////// align and alocate memory
template<typename T>
constexpr uint64_t align(uint64_t n)
{
    return (n % alignof(T) == 0)  ? n: (n / alignof(T) +1 ) * alignof(T);
}

template<int N>
constexpr uint64_t align(uint64_t n)
{
    return  (N ==0 || n % N == 0)  ? n: (n / N +1 )* N;
}

template<typename T>
constexpr uint64_t allocate(uint64_t n)
{
    return align<T>(n) + sizeof(T);
}



template <typename ... B>
constexpr typename std::enable_if<sizeof...(B) == 0, int >::type max_align(uint64_t maxAlign = 0)
{
    return maxAlign;
}

template <typename A, typename ... B>
constexpr uint64_t max_align(uint64_t maxAlign = 0)
{
    if (alignof(A) > maxAlign)
        maxAlign = alignof(A);
    return max_align<B...>(maxAlign);

}


template <typename ... B>
constexpr typename std::enable_if<sizeof...(B) == 0, int >::type size_of_tuple(int n =0)
{
    return n;
}

template <typename A, typename ... B>
constexpr int size_of_tuple(int n = 0)
{
    n  = allocate<A>(n);
    return size_of_tuple<B...>(n);
}


template <typename ... B>
constexpr uint64_t size_of_tuple_aligned()
{
    constexpr uint64_t n= size_of_tuple<B...>();
    constexpr int N =max_align<B...>() ;
    return align<N>(n);
}


/////////////////////////////// get_location by Type


template <typename A, typename ... B>
constexpr typename std::enable_if<sizeof...(B) == 0, int >::type get_location(uint64_t location = 0)
{
    return 0;
}

template <typename A, typename B, typename ... C>
constexpr uint64_t get_location(uint64_t location = 0)
{
    if constexpr (std::is_same<A, B>::value)
    {
        return align<B>(location);
    }
    else
    {
        location = allocate<B>(location);
        return get_location<A,C...>(location);
    }
}

/////////////////////////////// get_location by Index

template <uint64_t N, typename ... B>
constexpr typename std::enable_if<sizeof...(B) == 0, int >::type get_location(uint64_t location = 0)
{
    return 0;
}

template <int N, typename B, typename ... C>
constexpr uint64_t get_location(uint64_t location = 0)
{
    static_assert(N <= sizeof...(C));

    if constexpr (N == 0 ){
        return align<B>(location);
    }
    else
    {
        location = allocate<B>(location);
        return get_location<N-1, C...>(location);

    }
}




////////////////////////////////////////// get nth element type

template <int N, typename... T>
struct get_nth_element_type ;

template <typename T0, typename... T>
struct get_nth_element_type<0, T0, T...> {
    typedef T0 type;
};
template <int N, typename T0, typename... T>
struct get_nth_element_type<N, T0, T...> {
    typedef typename get_nth_element_type<N-1, T...>::type type;
};

template <>
struct get_nth_element_type<0> {
    typedef  void type;
};
