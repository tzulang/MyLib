#pragma once

namespace utils {

	namespace io_ex {

		template<typename ListType, int N, int S>
		struct print_fixed_size_list {
			static std::ostream& print(std::ostream &o, const ListType & list)
			{
				static_assert (N >= S);
				static_assert (S > 0);

				o << list[N-S] << ", "; 
				return print_fixed_size_list<ListType, N, S - 1>::print(o, list);
			}
		};

		template<typename ListType, int N>
		struct print_fixed_size_list<ListType, N, 0> {
			static std::ostream& print(std::ostream &o, const ListType & list)
			{
				return o;
			}
		};

		template<typename ListType, int N>
		struct print_fixed_size_list<ListType, N, 1> {
			static std::ostream& print(std::ostream &o, const ListType & list)
			{
				o << list[N - 1];
				return o;
			}
		};
	}

	template<typename ListType, int N>
	std::ostream & stream_list(std::ostream &o, const ListType & list) {
		return io_ex::print_fixed_size_list<ListType, N, N>::print(o, list);
	}

	template <typename T>
	std::ostream & stream_list(	std::ostream &o,
								T begin,
								T end) {
		for (auto& i = begin; i != end; i++) {
			o << *i;
			if (i+1 != end) 
				o << ", ";
		}
		return o;
	}
}