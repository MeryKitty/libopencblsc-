#ifndef ALGORITHM_ALGORITHM_H_INCLUDED
#define ALGORITHM_ALGORITHM_H_INCLUDED

#include <any>
#include <memory>
#include <utility>
#include <vector>

#include "basics/constant.h"
#include "model/expression.h"
#include "model/constraint.h"

namespace opencbls {
	template <class T>
	void simple_hill_climbing(std::vector<std::raw_ptr<var_t<T>>>& variables,
			std::vector<std::pair<T, std::unique_ptr<constraint_t<T>>>>& constraints,
			std::any parameters);

	template <class T>
	void tabu_search(std::vector<std::raw_ptr<var_t<T>>>& variables,
			std::vector<std::pair<T, std::unique_ptr<constraint_t<T>>>>& constraints,
			std::any parameters);

	template <class T>
	struct tabu_parameters {
	public:
		std::size_t intensify_period;
		std::size_t diversify_period;
		std::size_t limit_iter;
		std::size_t stale_iter;
		T intensify_weight;
		T diversify_weight;

		tabu_parameters() noexcept;
	};
}


#endif /* ALGORITHM_ALGORITHM_H_INCLUDED */
