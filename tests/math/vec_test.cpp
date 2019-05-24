#include "pch.h"

#include "myLib/math/vec.h"


template <typename Num>
class VecTest : public ::testing::Test {

public:

	static const uint64_t N = Num::value;

	void ctor_test()
	{
		maths::Vec<double, N> v;
        for (uint64_t i = 0; i < N; i++) {
			ASSERT_EQ(v[i], 0);
		}

        double value = 11;
        maths::Vec<double, N> v1(value);
        for (uint64_t i = 0; i < N; i++) {
            ASSERT_EQ(v1[i], value);
        }

		double values[N];

        for (uint64_t i = 0; i < N; i++) {
			values[i] = i;
		}

		maths::Vec<double, N> v2(values);
        for (uint64_t i = 0; i < N; i++) {
			ASSERT_EQ(v2[i], values[i]);
			ASSERT_EQ(v2[i], i);
		}

	}

	void out_of_boundaries_test()
	{
        maths::Vec<double, N> v;
        using except = typename maths::Vec<double, N>::ExceptionVectorOutofBoundIndex;
        ASSERT_THROW(v[N], except);
	}


};

template <int N>
struct Number {
	static const int value = N;
};

using VecSizes = ::testing::Types<Number<1>, Number<2>, Number<3>, Number<4>, Number<10>, Number<50 >> ;
//using VecSizes = ::testing::Types<Number<3>>;
TYPED_TEST_CASE(VecTest, VecSizes);

TYPED_TEST(VecTest, ctor_test)
{
    this->ctor_test();
}

TYPED_TEST(VecTest, out_of_boundaries)
{
    this->out_of_boundaries_test();
}

template<int N>
void assert_values(maths::Vec<double, N> v)
{
    for(uint64_t i = 0; i < N ; i++)
    {
        ASSERT_EQ(i ,v[i]);
    }
}

TEST(VecTestCtor, variadic_ctor)
{
    maths::Vec<double, 1> v1(1);
    ASSERT_EQ(v1[0], 1);

    maths::Vec<double, 2> v2(0,1);
    assert_values<2>(v2);

    maths::Vec<double, 3> v3(0,1,2);
    assert_values<3>(v3);

    maths::Vec<double, 4> v4(0,1,2,3);
    assert_values<4>(v4);

    maths::Vec<double, 10> v10(0,1,2,3,4,5,6,7,8,9);
    assert_values<10>(v10);

}

