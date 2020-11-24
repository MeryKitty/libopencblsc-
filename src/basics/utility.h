#ifndef BASICS_UTILITY_H_INCLUDED
#define BASICS_UTILITY_H_INCLUDED

#include <vector>

namespace std {
	
}

namespace opencbls {
	std::vector<bool> operator || (std::vector<bool>& operand1, std::vector<bool>& operand2);
	std::vector<bool> make_onehot(std::size_t value);
}

#endif /* BASICS_UTILITY_H_INCLUDED */
