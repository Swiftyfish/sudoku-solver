from sample.library.SudokuCell import Cell
from sample.library.SudokuGroup import Group

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
            