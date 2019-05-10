#include "pch.h"

#include "myLib/math/vec.h"


template <typename Num>
class VecTest : public ::testing::Test {

public:

	static const uint64_t N = Num::value;

	void ctor_test()
	{
		maths::Vec<double, N> v;
		for (int i = 0; i < N; i++) {
			ASSERT_EQ(v[i], 0);
		}

		//double value = 11;
		//maths::Vec<double, N> v1(true, value);
		//for (int i = 0; i < N; i++) {
		//	ASSERT_EQ(v1[i], value);
		//}

		double values[N];

		for (int i = 0; i < N; i++) {
			values[i] = i;
		}

		maths::Vec<double, N> v2(values);
		for (int i = 0; i < N; i++) {
			ASSERT_EQ(v2[i], values[i]);
			ASSERT_EQ(v2[i], i);
		}

	}

	void out_of_boundaries_test()
	{
		//maths::Vec<double, N> v;
		//	ASSERT_THROW(v[N], maths::Vec<double, N>::ExceptionVectorOutofBoundIndex());
	}
};

template <int N>
struct Number {
	static const int value = N;
};

//using VecSizes = ::testing::Types<Number<1>, Number<2>, Number<3>, Number<4>, Number<10>, Number<50 >> ;
using VecSizes = ::testing::Types<Number<3>>;
TYPED_TEST_CASE(VecTest, VecSizes);

TYPED_TEST(VecTest, ctor_test) {
	ctor_test();
}
