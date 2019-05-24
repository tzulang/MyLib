#include "pch.h"

#include "myLib/list_utils/list_utils.h"
#include <numeric>
#include <cstdlib>


TEST(for_each, test_apply_in_place) {

    const int N = 4;
	using Type = double;
	Type val[N] = { 1,2,3,4 };
    int index=0;
	auto plusIndex = 
        [&](double x) ->double { return x + static_cast<double>(index++); };

	utils::apply<Type[N], decltype(plusIndex), N>(val, plusIndex);

	for (int i = 0; i < N; i++) {
		ASSERT_EQ(i + (i + 1), val[i]);
	}
}

TEST(for_each, test_apply) {

	const int N = 4;
	using Type = double;
	Type val1[N] = { 1,2,3,4 };
	Type val2[N] = { 1,2,3,4 };
	Type res1[N] = {};
	Type res2[N] = {};

    int index= 0;
	auto plusIndex =
        [&](double x) ->double { return x + static_cast<double>(index++); };

	utils::apply<Type[N], decltype(plusIndex), N>(val1, res1, plusIndex);

	for (int i = 0; i < N; i++)
	{
		ASSERT_EQ(i + val1[i], res1[i]);
	}

    auto plus = std::plus{};

    utils::apply<Type[N], decltype(plus), N>(val1, val2, res2, plus);
		
	for (int i = 0; i < N; i++) 
	{
		ASSERT_EQ( val1[i] + val2[i] , res2[i]);
	}

}
