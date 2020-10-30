/*
 * constant.hpp
 *
 *  Created on: 29 Oct 2020
 *      Author: MeryKitty
 */

#ifndef BASICS_CONSTANT_H_INCLUDED
#define BASICS_CONSTANT_H_INCLUDED

namespace opencbls {
	namespace constant {
		template <class T>
		constexpr T false_violation = 1;

		enum arity {
			unary, binary, multary
		};
	}
}



#endif // BASICS_CONSTANT_H_INCLUDED
