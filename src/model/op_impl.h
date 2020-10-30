#ifndef OP_IMPL_H_INCLUDED
#define OP_IMPL_H_INCLUDED

#include <functional>
#include <memory>
#include <utility>
#include <vector>

#include "model/expression.h"

namespace opencbls {
	template <class T>
    class op_add : public op_t<T> {
    private:
    	p_expr_t<T> operand1;
    	p_expr_t<T> operand2;
    public:
    	op_add(p_expr_t<T> operand1, p_expr_t<T> operand2);

        T eval();
    };

    template <class T>
    class op_sub : public op_t<T> {
    private:
        p_expr_t<T> operand1;
        p_expr_t<T> operand2;
    public:
        op_sub(p_expr_t<T> operand1, p_expr_t<T> operand2);

        T eval();
    };

    template <class T>
    class op_mul : public op_t<T> {
    private:
        p_expr_t<T> operand1;
        p_expr_t<T> operand2;
    public:
    	op_mul(p_expr_t<T> operand1, p_expr_t<T> operand2);

        T eval();
    };

    template <class T>
    class op_div : public op_t<T> {
    private:
        p_expr_t<T> operand1;
        p_expr_t<T> operand2;
    public:
    	op_div(p_expr_t<T> operand1, p_expr_t<T> operand2);

        T eval();
    };

    template <class T>
    class op_sum : public op_t<T> {
    private:
    	std::vector<p_expr_t<T>> operands;
    public:
    	op_sum(std::vector<p_expr_t<T>> operands);

    	T eval();
    };

    template <class T>
    class op_user_defined : public op_t<T> {
    private:
        std::function<T(std::vector<T>)> op;
    	std::vector<p_expr_t<T>> operands;
    public:
        op_user_defined(std::function<T(std::vector<T>&)> op, std::vector<p_expr_t<T>> operands);

        T eval();
    };
}

#endif // OP_IMPL_H_INCLUDED
