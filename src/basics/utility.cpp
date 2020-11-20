/*
 * utility.cpp
 *
 *  Created on: 3 Nov 2020
 *      Author: MeryKitty
 */

#include <algorithm>
#include <functional>
#include <vector>

namespace opencbls {
	std::vector<bool> operator || (std::vector<bool>& operand1, std::vector<bool>& operand2) {
		std::size_t _max_size = operand1.size() > operand2.size() ? operand1.size() : operand2.size();
		std::size_t _min_size = _max_size == operand1.size() ? operand2.size() : operand1.size();
		auto&& _longer_operand = _max_size == operand1.size() ? operand1 : operand2;
		std::vector<bool> result(_max_size);
		std::size_t i = 0;
		for (; i < _min_size; i++) {
			result[i] = operand1[i] || operand2[i];
		}
		for (; i < _max_size; i++) {
			result[i] = _longer_operand[i];
		}
		return result;
	}

	std::vector<bool> make_onehot(std::size_t value) {
		std::vector<bool> result(value + 1);
		result[value] = true;
		return result;
	}
}
