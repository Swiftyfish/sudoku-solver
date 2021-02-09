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
        self.value = value
        
        self.row.update_cells(value, self.column.position)
        self.column.update_cells(value, self.row.position)
        self.block.update_cells(value)
        
    
class Group():
    """
    A group can be a row, column or block containing 9 sudoku squares
    """
    def __init__(self, position, cells=[]):
        self.position = position
        self.cells = cells
        
    def update_cells(self, value, position=None):
        """
        Update each of the contained cells to not allow value
        and place value in position
        """
        
        for i in range(9):
            cell = self.cells[i]
            
            if i == position:
                cell.value = value
            elif type(cell.value) == list:
                cell.value[value] = 0
                
def grid_builder(cells):
    """
    Takes in the base grid in the form of a comma separated string and 
    parses it into 81 cells grouped by row, column and block
    """
    
    #Should probably populate the grid using the update cells method
    #So that cells have their pencil marks done initially
    
    cell_values = map(int, cells.split())
    rows = [Group(i) for i in range(9)]
    columns = [Group(i) for i in range(9)]
    blocks = [Group(i) for i in range(9)]
    
    for i in range(81):
        row = i // 9
        column = i % 9
        block = row // 3 + 3 * (column // 3)
        
        cell = Cell(row, column, block)
        if cell_values[i]:
            cell.value = cell_values[i]
        
        rows[row].cells.append(cell)
        columns[column].cells.append(cell)
        blocks[block].cells.append(cell)
            
