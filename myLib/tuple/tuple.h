#pragma once

#include "tuple_mem.h"
#include <cstring>
#include <sstream>
#include <iostream>
#include <utility>

namespace myLib
{

template<typename ...Args>
class Tuple{

public:

    template <typename ...BuildArgs>
    Tuple(BuildArgs&&... args)
    {
        if constexpr(SIZE>0)
               put(std::forward<BuildArgs>(args)...);

    }


    Tuple(Args&&... args)
    {
        if constexpr(SIZE>0)
               put(std::forward<Args>(args)...);

    }

    size_t size() { return MEM_SIZE; }

    std::string to_string()
    {
        std::stringstream ss;

        ss<< "Tuple(" <<SIZE<<"): sizeof="<<sizeof(*this) <<", data.size ="<< sizeof(data)   ;

        return ss.str();
    }

    template <int MEM_SIZE>
    auto& get() {
        using Type = typename get_nth_element_type<MEM_SIZE, Args...>::type;
        uint8_t * address=  data + get_location<MEM_SIZE, Args...>();
        Type * value = (Type *) (address);
        return *value;
    }
private:

    constexpr static uint64_t MEM_SIZE = size_of_tuple_aligned<Args...>();
    constexpr static uint64_t SIZE = sizeof...(Args);
    uint8_t data[MEM_SIZE];


    template<typename Arg , typename ...REST>
    void put(Arg arg, REST&&... args)
    {
        put_ex<SIZE - (sizeof...(REST))-1, Arg>(std::forward<Arg>(arg)) ;
        put<REST...>(std::forward<REST>(args)...);
    }

    template<typename Arg>
    void put(Arg && arg)
    {

        put_ex<SIZE-1, Arg>(std::forward<Arg>(arg));
    }


    template< uint64_t N, typename ...Arg>
    void put_ex(Arg&&... arg)
    {
        using Type = typename get_nth_element_type<N, Args...>::type;
        uint8_t * address=  data + get_location<N, Args...>();

        new (reinterpret_cast<Type *> (address)) Type(std::forward<Arg>(arg)...);
    }

    template<typename Arg , typename ...REST>
    void print(Arg arg, REST&&... args)
    {
        print<Arg>(std::forward<Arg>(arg)) ;
        print<REST...>(std::forward<REST>(args)...);
    }

    template<typename Arg>
    void print(Arg && arg)
    {

        std::cout << typeid(Arg).name() <<'\n';
    }

};

}
