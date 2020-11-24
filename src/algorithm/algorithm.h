#ifndef ALGORITHM_ALGORITHM_H_INCLUDED
#define ALGORITHM_ALGORITHM_H_INCLUDED

#include <memory>
#include <utility>
#include <vector>

#include "model/expression.h"
#include "model/constraint.h"

namespace opencbls {
	template <class T>
	void simple_hill_climbing(std::vector<std::raw_ptr<var_t<T>>>& variables,
		std::vector<std::pair<T, std::unique_ptr<constraint_t<T>>>>& constraints);
}



#endif /* ALGORITHM_ALGORITHM_H_INCLUDED */
