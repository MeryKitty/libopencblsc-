from . import capi
from .solver import IntExpression, IntOperation

class IntAdd(IntOperation):
    _operand1: IntExpression
    _operand2: IntExpression

    def __init__(self, operand1: IntExpression, operand2: IntExpression) -> None:
        self._operand1 = operand1
        self._operand2 = operand2

    def _get(self):
        return capi.int_op_add(self._operand1._get(), self._operand2._get())

class IntSub(IntOperation):
    _operand1: IntExpression
    _operand2: IntExpression

    def __init__(self, operand1: IntExpression, operand2: IntExpression) -> None:
        self._operand1 = operand1
        self._operand2 = operand2

    def _get(self):
        return capi.int_op_sub(self._operand1._get(), self._operand2._get())

class IntMul(IntOperation):
    _operand1: IntExpression
    _operand2: IntExpression

    def __init__(self, operand1: IntExpression, operand2: IntExpression) -> None:
        self._operand1 = operand1
        self._operand2 = operand2

    def _get(self):
        return capi.int_op_mul(self._operand1._get(), self._operand2._get())

class IntDiv(IntOperation):
    _operand1: IntExpression
    _operand2: IntExpression

    def __init__(self, operand1: IntExpression, operand2: IntExpression) -> None:
        self._operand1 = operand1
        self._operand2 = operand2

    def _get(self):
        return capi.int_op_div(self._operand1._get(), self._operand2._get())