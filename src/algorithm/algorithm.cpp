#include "algorithm/algorithm.h"

namespace opencbls {
    template <class T>
    tabu_parameters<T>::tabu_parameters() noexcept :
            intensify_period(50),
            diversify_period(50),
            limit_iter(10000),
            stale_iter(500),
            intensify_weight(2),
            diversify_weight(2) {}
}