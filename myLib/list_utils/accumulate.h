#pragma once
 
namespace utils {

	namespace acc_ex {

		/* accumulate */

		template<typename ListType, typename Op, typename AccType, int N, int S>
		struct accumulate {

			static inline AccType fold_left(ListType const& list, Op & op, AccType & acc)
			{
				AccType r = op(acc, list[N - S]);
				return accumulate<ListType, Op, AccType, N, S - 1>::fold_left(list, op, r);
			}

			static inline AccType fold_right(ListType const& list, Op & op, AccType & acc)
			{
				AccType r = accumulate<ListType, Op, AccType, N, S - 1>::fold_right(list, op, acc);
				return  op(r, list[N - S]);
			}
		};

		template<typename ListType, typename Op, typename AccType, int N>
		struct accumulate<ListType, Op, AccType, N, 1> {

			static inline AccType fold_left(ListType const& list, Op & op, AccType & acc) {
				return op(acc, list[N - 1]);
			}

			static inline AccType fold_right(ListType const& list, Op & op, AccType & acc)
			{
				return op(acc, list[N - 1]);
			}


		};

		template<typename ListType, typename Op, typename AccType, int N>
		struct accumulate<ListType, Op, AccType, N, 0> {
			static AccType fold_left(ListType const& list, Op & op, AccType & acc) {
				return acc;
			}

			static AccType fold_right(ListType const& list, Op & op, AccType & acc) {
				return acc;
			}
		};


		/*accumulate2*/

		template<typename ListType, typename InnerOp, typename AggOp, typename AccType, int N, int S>
		struct accumulate2 {
			static inline AccType fold_left(ListType const& list1, ListType const& list2, InnerOp & innerOp, AggOp & aggOp, AccType & acc)
			{
				auto a = innerOp(list1[N - S], list2[N - S]);
				auto r = aggOp(acc, a);
				return accumulate2<ListType, InnerOp, AggOp, AccType, N, S - 1>::fold_left(list1, list2, innerOp, aggOp, r);
			}
		};

		template<typename ListType, typename InnerOp, typename AggOp, typename AccType, int N>
		struct accumulate2<ListType, InnerOp, AggOp, AccType, N, 1> {
			static inline AccType fold_left
			(ListType const& list1, ListType const& list2, InnerOp & innerOp, AggOp & aggOp, AccType & acc)
			{

				return aggOp(acc, innerOp(list1[N - 1], list2[N - 1]));
			}
		};

		template<typename ListType, typename InnerOp, typename AggOp, typename AccType, int N>
		struct accumulate2 <ListType, InnerOp, AggOp, AccType, N, 0> {
			static inline AccType fold_left
			(ListType const& list1, ListType const& list2, InnerOp & innerOp, AggOp & aggOp, AccType & acc)
			{
				return acc;
			}
		};

	}



	template<typename ListType, typename Op, typename AccType, int S>
	AccType accumulate(ListType const& list, Op  op, AccType & init)
	{
		return acc_ex::accumulate<ListType, Op, AccType, S, S>::fold_left(list, op, init);
	}

	template<typename ListType, typename Op, typename AccType, int S>
	AccType accumulate(ListType const& list, Op & op, AccType && init)
	{
		return acc_ex::accumulate<ListType, Op, AccType, S, S>::fold_left(list, op, init);


	}

	template<typename ListType, typename Op, typename AccType, int S>
	AccType fold_right(ListType const& list, Op  op, AccType & init)
	{
		return acc_ex::accumulate<ListType, Op, AccType, S, S>::fold_right(list, op, init);
	}

	template<typename ListType, typename Op, typename AccType, int S>
	AccType fold_right(ListType const& list, Op & op, AccType && init)
	{
		return acc_ex::accumulate<ListType, Op, AccType, S, S>::fold_right(list, op, init);
	}


	template<typename ListType, typename InnerOp, typename AggOp, typename AccType, int S>
	static inline AccType fold_left(ListType const& list1, ListType & list2, InnerOp & innerOp, AggOp & aggOp, AccType & init)
	{
		return acc_ex::accumulate2<ListType, InnerOp, AggOp, AccType, S, S>::fold_left(list1, list2, innerOp, aggOp, init);
	}

	template<typename ListType, typename InnerOp, typename AggOp, typename AccType, int S>
	static inline AccType fold_left(ListType const& list1, ListType const& list2, InnerOp & innerOp, AggOp & aggOp, AccType && init)
	{
		return acc_ex::accumulate2<ListType, InnerOp, AggOp, AccType, S, S>::fold_left(list1, list2, innerOp, aggOp, init);
	}


 

}