/*
 * hill_climbing.h
 *
 *  Created on: 17 Nov 2020
 *      Author: MeryKitty
 */

#ifndef ALGORITHM_ALGORITHMS_H_INCLUDED
#define ALGORITHM_ALGORITHMS_H_INCLUDED

#include <memory>
#include <utility>
#include <vector>

#include "model/expression.h"
#include "model/constraint.h"

namespace opencbls {
	template <class T>
	class simple_hill_climbing {
	public:
		void operator() (std::vector<std::unique_ptr<var_t<T>>>& variables,
					std::vector<std::pair<T, std::unique_ptr<constraint_t<T>>>>& constraints);
	};
}



#endif /* ALGORITHM_ALGORITHMS_H_INCLUDED */
