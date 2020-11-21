#include <memory>
#include <utility>
#include <variant>
#include <vector>

#include "basics/utility.h"
#include "model/expression.h"

namespace opencbls {
	template <class T>
	std::vector<bool> const_t<T>::_dummy = std::vector<bool>();

	template <class T>
	const_t<T>::const_t() : _value() {};

	template <class T>
	const_t<T>::const_t(T value) : _value(value) {};

	template <class T>
	T const_t<T>::value() {
		return this->_value;
	}

	template <class T>
	std::vector<bool>& const_t<T>::dummy_vector() {
		return _dummy;
	}

    template <class T>
    var_t<T>::var_t(std::size_t id, T min, T max) : _id(id), _min(min), _max(max), _value(), _onehot(make_onehot(id)) {}

    template <class T>
    std::size_t var_t<T>::id() {
    	return this->_id;
    }

    template <class T>
    T var_t<T>::min() {
        return this->_min;
    }

    template <class T>
    T var_t<T>::max() {
        return this->_max;
    }

    template <class T>
    T var_t<T>::value() {
        return this->_value;
    }

    template <class T>
    void var_t<T>::assign(T value) {
    	this->_value = value;
    }

    template <class T>
    std::vector<bool>& var_t<T>::id_onehot() {
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
    T expr_t<T>::value() {
    	class get_value_t {
    	public:
    		T operator() (const_t<T>& cst) {
    			return cst.value();
    		}
    		T operator() (std::raw_ptr<var_t<T>>& var) {
    			return var->value();
    		}
    		T operator() (std::unique_ptr<op_t<T>>& op) {
    			return op->value();
    		}
    	};
    	get_value_t get_value;
    	return std::visit(get_value, this->_expr);
    }

    template <class T>
    std::vector<bool>& expr_t<T>::related_var() {
    	class get_related_var_t {
    	public:
    		std::vector<bool>& operator() (const_t<T>& cst) {
    			return cst.dummy_vector();
    		}
    		std::vector<bool>& operator() (std::raw_ptr<var_t<T>>& var) {
    			return var->id_onehot();
    		}
    		std::vector<bool>& operator() (std::unique_ptr<op_t<T>>& op) {
    			return op->related_var();
    		}
    	};
    	get_related_var_t get_related_var;
    	return std::visit(get_related_var, this->_expr);
    }

    template <class T>
    T expr_t<T>::delta(std::raw_ptr<var_t<T>> var, T value) {
       	class get_delta_t {
       	private:
       		std::raw_ptr<var_t<T>> _var;
       		T _value;
       	public:
       		get_delta_t(std::raw_ptr<var_t<T>> var, T value) : _var(std::move(var)), _value(std::move(value)) {}

       		T operator() (const_t<T>& cst) {
       			return 0;
       		}
       		T operator() (std::raw_ptr<var_t<T>>& other) {
       			if (other == this->_var) {
       				return this->_value - other->value();
       			} else {
       				return 0;
       			}
       		}
       		T operator() (std::unique_ptr<op_t<T>>& op) {
       			return op->delta(this->_var, this->_value);
       		}
       	};
       	get_delta_t get_delta(var, value);
       	return std::visit(get_delta, this->_expr);
    }

    template <class T>
    op_t<T>::op_t(std::vector<bool> related_var) : _related_var(std::move(related_var)) {}

    template <class T>
    T op_t<T>::delta(std::raw_ptr<var_t<T>> var, T value) {
    	std::size_t _id = var->id();
    	bool _relate = this->_related_var.size() > _id && this->_related_var[_id];
    	return _relate ? this->delta_helper(var, value) : T(0);
    }

    template <class T>
    std::vector<bool>& op_t<T>::related_var() {
    	return this->_related_var;
    }

    template <class T>
    op_t<T>::~op_t() = default;

    template class const_t<int>;
    template class var_t<int>;
    template class op_t<int>;
    template class expr_t<int>;

}
