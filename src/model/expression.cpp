#include <memory>
#include <utility>
#include <variant>
#include <vector>

#include "model/expression.h"

namespace opencbls {
	template <class T>
	const_t<T>::const_t() {};

	template <class T>
	const_t<T>::const_t(T value) : _value(value) {};

	template <class T>
	T const_t<T>::eval() {
		return this->_value;
	}

	template <class T>
	const std::vector<bool>& const_t<T>::dummy_vector() {
		return _dummy;
	}

    template <class T>
    var_t<T>::var_t(std::size_t id, T min, T max) : _id(id), _min(min), _max(max) {}

    template <class T>
    std::size_t var_t<T>::id() {
    	return this->_id;
    }

    template <class T>
    T var_t<T>::eval() {
        return this->_value;
    }

    template <class T>
    const std::vector<bool>& var_t<T>::id_onehot() {
    	return this->_onehot;
    }

    template <class T>
    expr_t<T>::expr_t(expr_t<T>&& in) {
    	this->_expr.swap(in._expr);
    }

    template <class T>
    expr_t<T>& expr_t<T>::operator =(expr_t<T>&& in) {
    	this->_expr.swap(in._expr);
    	return *this;
    }

    template <class T>
    expr_t<T>::expr_t(std::unique_ptr<op_t<T>> op) : _expr(std::move(op)) {}

    template <class T>
    expr_t<T>::expr_t(std::raw_ptr<var_t<T>> var) : _expr(std::move(var)) {}

    template <class T>
    expr_t<T>::expr_t(const_t<T> cst) : _expr(std::move(cst)) {}

    template <class T>
    T expr_t<T>::eval() {
    	class get_value_t {
    	public:
    		T operator() (const_t<T>& cst) {
    			return cst.eval();
    		}
    		T operator() (std::raw_ptr<var_t<T>>& var) {
    			return var->eval();
    		}
    		T operator() (std::unique_ptr<op_t<T>>& op) {
    			return op->eval();
    		}
    	};
    	get_value_t get_value;
    	return std::visit(get_value, this->_expr);
    }

    template <class T>
    const std::vector<bool>& expr_t<T>::related_var() {
    	class get_related_var_t {
    	public:
    		const std::vector<bool>& operator() (const_t<T>& cst) {
    			return cst.dummy_vector();
    		}
    		const std::vector<bool>& operator() (std::raw_ptr<var_t<T>>& var) {
    			return var->id_onehot();
    		}
    		const std::vector<bool>& operator() (std::unique_ptr<var_t<T>>& op) {
    			return op->related_var();
    		}
    	};
    	get_related_var_t get_related_var;
    	return std::visit(get_related_var, this->_expr);
    }

    template <class T>
        T expr_t<T>::delta(std::raw_ptr<var_t<T>> var, T value) {
        	class get_delta_t {
        	public:
        		T operator() (const_t<T>& cst) {
        			return 0;
        		}
        		T operator() (std::raw_ptr<var_t<T>>& other) {
        			if (other == var) {
        				return value - other->eval();
        			} else {
        				return 0;
        			}
        		}
        		T operator() (std::unique_ptr<op_t<T>>& op) {
        			return op->delta(var, value);
        		}
        	};
        	get_delta_t get_delta;
        	return std::visit(get_delta, this->_expr);
        }

    template <class T>
    bool op_t<T>::relate(std::raw_ptr<var_t<T>> var) {
    	std::size_t _id = var->id();
    	return this->related_var.size() > _id && this->related_var[_id];
    }

    template <class T>
    T op_t<T>::delta(std::raw_ptr<var_t<T>> var, T value) {
    	return this->relate(var) ? this->delta_helper(var, value) : 0;
    }

    template <class T>
    const std::vector<bool>& op_t<T>::related_var() {
    	return this->related_var;
    }
}
