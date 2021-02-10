# -*- coding: utf-8 -*-
"""
Created on Mon Feb  8 22:48:26 2021

@author: swift
"""

class Cell():
    def __init__(self, row, column, block, value=None):
        self.row = row
        self.column = column
        self.block = block
        
        if (value is not None):
            self.value = value
        else:
            self.value = [1 for i in range(9)]
    
    def set_value(self, value):
        """
        Sets the current value of the cell
        """
        self.value = value

    def block_value(self, value):
        """
        Blocks the value from the current cell
        """
        if type(value) is list:
            self.value[value-1] = 0
        else:
            pass