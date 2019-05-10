#pragma once

#include <string>
#include <type_traits>


namespace utils {

	template <typename Type>
	struct add_neutral
	{
		static constexpr Type value = static_cast<Type>(0);
	};

	template <typename Type>
	struct mult_neutral
	{
		static constexpr Type value = static_cast<Type>(1);
	};
	
	
}