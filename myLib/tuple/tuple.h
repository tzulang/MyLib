#pragma once

#include "../alocators/std_alignment.h"
#include <cstring>
#include <sstream>
#include <iostream>
#include <utility>

namespace myLib
{

template<typename ...Args>
class Tuple{

public:

    Tuple(Args&&... args)
    {
        memset(data, 0, MEM_SIZE);
        if constexpr(SIZE>0)
               put(args...);

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
        uint8_t * address=  data +get_location<MEM_SIZE, Args...>();
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
        get<SIZE - (sizeof...(REST))-1>() = arg;
        std::cout<< "XXXX "<< SIZE - (sizeof...(REST))-1<< '\n';
        put(args...);
    }

    template<typename Arg>
    void put(Arg && arg)
    {
        get<SIZE - 1>() = arg;
        std::cout<<"Y "<< SIZE - 1 << "\n";
    }



};

}
