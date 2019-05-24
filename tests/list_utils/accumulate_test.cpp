#include "pch.h"

#include "myLib/list_utils/list_utils.h"
#include <numeric>
#include <cstdlib>

template <typename Type>
class NumericFoldLeft : public ::testing::Test {

public:

	static const int N = 100;
	static const int RANGE = 1000;
	Type list[N];
	Type init[N];


	void SetUp() {

		srand(512);
		for (int i = N - 1; i >= 0; i--) 
		{
			list[i] = static_cast <Type> (rand()) / (static_cast <Type> (RAND_MAX / RANGE));//(Type)(i + 1);
			init[i] = static_cast <Type> (rand()) / (static_cast <Type> (RAND_MAX / RANGE)); //(Type)(i);
		}
	}

	void test_fold_left() 
	{
        for (int i = 0; i < N; i++)
        {
            auto plus = std::plus<Type>{};
            compareAccumulate<decltype(plus)>(plus, init[i]);

            auto  minus = std::minus<Type>{};
            compareAccumulate<decltype(minus)>(minus, init[i]);

            auto mult = std::multiplies<Type>{};
            compareAccumulate<decltype(mult)>(mult, init[i]);

            auto  div = std::divides<Type>{};
            compareAccumulate<decltype(div)>(div, init[i]);
        }
	}

private:

	template <typename Op>
	void compareAccumulate(Op & op, Type  & init)
	{
		Type myRes = utils::accumulate<decltype(list), decltype(op), Type, N>(list, op, init);
		Type stdRes = std::accumulate(list, list + N, init, op);

		ASSERT_EQ(myRes, stdRes);

	}
};

using MyTypes = ::testing::Types<int, unsigned int, float, double>;
TYPED_TEST_CASE(NumericFoldLeft, MyTypes);

TYPED_TEST(NumericFoldLeft, test_left_fold) 
{
    this->test_fold_left();
}



TEST(test_one_or_empty, test_one_or_empty) {


	std::vector<std::string> list{};
	auto plus = std::plus<std::string>{};

	std::string  myRes = utils::accumulate<decltype(list), decltype(plus), std::string, 0>(list, plus, "");
	std::string  stdRes = std::accumulate(list.begin(), list.end(), std::string(""), plus);
	ASSERT_EQ(myRes, stdRes);

	list.push_back(std::string("aaa"));
	myRes = utils::accumulate<decltype(list), decltype(plus), std::string, 1>(list, plus, "");
	stdRes = std::accumulate(list.begin(), list.end(), std::string(""), plus);
	ASSERT_EQ(myRes, stdRes);


};


template <typename Type>
class NumericDoubleFoldLeft : public ::testing::Test 
{

public:

	static const int N = 100;
	static const int RANGE = 20;
	Type list1[N];
	Type list2[N];
	Type init[N];

	void SetUp() 
	{
		srand(512);
		for (int i = N - 1; i >= 0; i--) 
		{
			list1[i] = static_cast <Type> (rand()) / (static_cast <Type> (RAND_MAX / RANGE));//(Type)(i + 1);
			list2[i] = static_cast <Type> (rand()) / (static_cast <Type> (RAND_MAX / RANGE));//(Type)(i + 1);
			init[i] = static_cast <Type> (rand()) / (static_cast <Type> (RAND_MAX / RANGE)); //(Type)(i);
		}
	}

	void test_fold_left() 
	{
		for (int i = 0; i < N; i++)
		{
			auto plus = std::plus<Type>{};
			auto mult = std::multiplies<Type>{};
			
			Type res = utils::fold_left < Type[N], decltype(mult), decltype(plus), Type, N >(list1, list2, mult, plus, init[i]);
			Type expected = init[i];
		
			for (int i = 0; i < N; i++)
			{
				expected += list1[i] * list2[i];
			}
			ASSERT_EQ(res, expected);
		}
	}
};

using MyTypes = ::testing::Types< int, unsigned int, float, double >;
TYPED_TEST_CASE(NumericDoubleFoldLeft, MyTypes);

TYPED_TEST(NumericDoubleFoldLeft, test_left_fold) 
{
    this->test_fold_left();
}


TEST(MixedDoubleFoldLeft, test_mixed_left_fold) 
{
	const int N = 4;
	int list1[N] = { 1, 2, 3, 4 };
	int list2[N] = { 1, 2, 3, 4 };

	auto plusI = [](int x, int y) { return x + y; };
	auto plusS = [](std::string &acc, int v) { return acc + std::to_string(v); };

	std::string  myRes = utils::fold_left
		<decltype(list1), decltype(plusI), decltype(plusS), std::string, N>(list1, list2, plusI, plusS, "");

	std::string expected = "2468";
	ASSERT_EQ(myRes, expected);
};



