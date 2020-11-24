#ifndef MODEL_OP_IMPL_H_INCLUDED
#define MODEL_OP_IMPL_H_INCLUDED

#include <functional>
#include <memory>
#include <utility>
#include <vector>

#include "basics/raw_ptr.h"
#include "model/expression.h"

namespace opencbls {
	template <class T>
    class op_add : public op_t<T> {
    private:
    	expr_t<T> _operand1;
    	expr_t<T> _operand2;
    protected:
    	T delta_helper(std::raw_ptr<var_t<T>> var, T value);
    public:
    	op_add(expr_t<T> operand1, expr_t<T> operand2);

        T value();
    };

    template <class T>
    class op_sub : public op_t<T> {
    private:
        expr_t<T> _operand1;
        expr_t<T> _operand2;
    protected:
    	T delta_helper(std::raw_ptr<var_t<T>> var, T value);
    public:
        op_sub(expr_t<T> operand1, expr_t<T> operand2);

        T value();
    };

    template <class T>
    class op_mul : public op_t<T> {
    private:
        expr_t<T> _operand1;
        expr_t<T> _operand2;
    protected:
    	T delta_helper(std::raw_ptr<var_t<T>> var, T value);
    public:
    	op_mul(expr_t<T> operand1, expr_t<T> operand2);

        T value();
    };

    template <class T>
    class op_div : public op_t<T> {
    private:
        expr_t<T> _operand1;
        expr_t<T> _operand2;
    protected:
    	T delta_helper(std::raw_ptr<var_t<T>> var, T value);
    public:
    	op_div(expr_t<T> operand1, expr_t<T> operand2);

        T value();
    };

    template <class T>
    class op_sum : public op_t<T> {
    private:
    	std::vector<expr_t<T>> _operands;
    protected:
    	T delta_helper(std::raw_ptr<var_t<T>> var, T value);
    public:
    	op_sum(std::vector<expr_t<T>> operands);

    	T value();
    };

    template <class T>
    class op_user_defined : public op_t<T> {
    private:
        std::function<T(std::vector<T>&)> _op;
        std::function<T(std::vector<T>&, std::vector<T>&)> _delta;
    	std::vector<expr_t<T>> _operands;
    protected:
    	T delta_helper(std::raw_ptr<var_t<T>> var, T value);
    public:
        op_user_defined(std::function<T(std::vector<T>&)> op, std::function<T(std::vector<T>&, std::vector<T>&)> delta, std::vector<expr_t<T>> operands);

        T value();
    };
}

#endif // MODEL_OP_IMPL_H_INCLUDED
