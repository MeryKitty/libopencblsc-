import ctypes

from .api import lib
from .solver import Constraint, Expression

class AllNotEqual(Constraint):
    _operands: list

    def __init__(self, operands: list) -> None:
        self._operands = operands.copy()

    def get(self) -> ctypes.c_void_p:
        temp_operand_list = [ele.get() for ele in self._operands]
        temp_operands = (ctypes.c_void_p * len(self._operands))(*temp_operand_list)
        return lib.constraint_all_not_equal(len(self._operands), temp_operands)
