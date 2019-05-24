#pragma once


namespace utils {

	namespace apply_ex {

		template<typename ListType, typename Op, int N, int S>
		struct apply_all {

			static inline void apply_in_place(ListType& list, Op & op)
			{
                list[N - S] = op(list[N - S]);
				apply_all<ListType, Op, N, S - 1>::apply_in_place(list, op);
			}

            static inline void apply(ListType const& src_list, ListType& list_dst, Op & op)
			{
                list_dst[N - S] = op(src_list[N - S]);
                apply_all<ListType, Op, N, S - 1>::apply(src_list, list_dst, op);
			}

            static inline void apply(ListType const& src_list1, ListType const& src_list2, ListType& list_dst, Op & op)
			{
                list_dst[N - S] = op(src_list1[N - S], src_list2[N - S]);
                apply_all<ListType, Op, N, S - 1>::apply(src_list1, src_list2, list_dst, op);
			}

		};

		template<typename ListType, typename Op, int N>
		struct apply_all<ListType, Op, N, 1> {

			static inline void apply_in_place(ListType& list, Op & op)
			{
                list[N - 1] = list[N - 1] = op(list[N - 1]);
			}

            static inline void apply(ListType const& src_list, ListType& list_dst, Op & op)
			{
                list_dst[N - 1] = op(src_list[N - 1]);
			}

            static inline void apply(ListType const& src_list1, ListType const& src_list2, ListType& list_dst, Op & op)
			{
                list_dst[N - 1] = op(src_list1[N - 1], src_list2[N - 1]);
			}
		};

		template<typename ListType, typename Op, int N>
		struct apply_all<ListType, Op, N, 0> {
			static inline void apply_in_place(ListType& list, Op & op)
			{
				return;
			}

            static inline void apply(ListType const& src_list, ListType& list_dst, Op & op)
			{
				return;
			}

            static inline void apply(ListType const& src_list1, ListType const& src_list2, ListType& list_dst, Op & op)
			{
				return;
			}

		};
	}

	template<typename ListType, typename Op, int N>
	ListType& apply(ListType& list, Op & op) {
		apply_ex::apply_all<ListType, Op, N, N>::apply_in_place(list, op);
		return list;
	}

	template<typename ListType, typename Op, int N>
    ListType& apply(ListType const& src_list, ListType& list_dst, Op & op) {
        apply_ex::apply_all<ListType, Op, N, N>::apply(src_list, list_dst, op);
        return list_dst;
	}

	template<typename ListType, typename Op, int N>
    ListType& apply(ListType const& src_list1, ListType const& src_list2, ListType& list_dst, Op & op) {
        apply_ex::apply_all<ListType, Op, N, N>::apply(src_list1, src_list2, list_dst, op);
        return list_dst;
	}

}
