
#include <iostream>
#include <tuple>

#include <type_traits>
#include "myLib/alocators/std_alignment.h"
#include "myLib/tuple/tuple.h"

using namespace std;


struct A{
    char a; __int128 b; int c;
};



int main()
{
    using namespace std;

    cout << myLib::Tuple<>().to_string() <<endl;

    myLib::Tuple<int, char,double> a(10, 'a', 1.32321e-15);

//    a.get<0>() =1;

//    a.get<1>() = 'a';
//    a.get<2>() = "hello";
    cout << a.get<0>() << endl;
    cout << a.get<1>() << endl;
    cout << a.get<2>() << endl;
    return 0;
}
