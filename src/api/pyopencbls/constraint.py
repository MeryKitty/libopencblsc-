from ctypes import c_void_p

from .api import lib
from .solver import IntConstraint, IntExpression

class IntAllNotEqual(IntConstraint):
    _operands: list

    def __init__(self, operands: list) -> None:
        self._operands = operands.copy()

    def get(self) -> c_void_p:
        temp_operand_list = [ele.get() for ele in self._operands]
        temp_operands = (c_void_p * len(self._operands))(*temp_operand_list)
        return lib.int_constraint_all_not_equal(len(self._operands), temp_operands)
