from ctypes import c_void_p

from .api import lib
from .solver import IntExpression, IntOperation

class IntAdd(IntOperation):
    _operand1: IntExpression
    _operand2: IntExpression

    def __init__(self, operand1: IntExpression, operand2: IntExpression) -> None:
        self._operand1 = operand1
        self._operand2 = operand2

    def _get(self) -> c_void_p:
        return lib.int_op_add(c_void_p(self._operand1._get()), c_void_p(self._operand2._get()))

class IntSub(IntOperation):
    _operand1: IntExpression
    _operand2: IntExpression

    def __init__(self, operand1: IntExpression, operand2: IntExpression) -> None:
        self._operand1 = operand1
        self._operand2 = operand2

    def _get(self) -> c_void_p:
        return lib.int_op_sub(c_void_p(self._operand1._get()), c_void_p(self._operand2._get()))

class IntMul(IntOperation):
    _operand1: IntExpression
    _operand2: IntExpression

    def __init__(self, operand1: IntExpression, operand2: IntExpression) -> None:
        self._operand1 = operand1
        self._operand2 = operand2

    def _get(self) -> c_void_p:
        return lib.int_op_mul(c_void_p(self._operand1._get()), c_void_p(self._operand2._get()))

class IntDiv(IntOperation):
    _operand1: IntExpression
    _operand2: IntExpression

    def __init__(self, operand1: IntExpression, operand2: IntExpression) -> None:
        self._operand1 = operand1
        self._operand2 = operand2

    def _get(self) -> c_void_p:
        return lib.int_op_div(c_void_p(self._operand1._get()), c_void_p(self._operand2._get()))