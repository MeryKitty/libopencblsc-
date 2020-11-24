#ifndef BASICS_CONSTANT_H_INCLUDED
#define BASICS_CONSTANT_H_INCLUDED

static_assert(sizeof(int) == 4);
static_assert(sizeof(long long) == 8);

namespace opencbls {
	namespace constant {
		template <class T>
		constexpr T false_violation = T(1);

		template <class T>
		T tolerance;

		template <>
		constexpr int tolerance<int> = 1;

		template <>
		constexpr long long tolerance<long long> = 1;

		template <>
		constexpr float tolerance<float> = 1e-4;

		template <>
		constexpr double tolerance<double> = 1e-8;
	}
}



#endif // BASICS_CONSTANT_H_INCLUDED
