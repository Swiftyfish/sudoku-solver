from sample.library.SudokuCell import Cell

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
                cell.set_value(value)
            elif type(cell.value) == list:
                cell.value[value] = 0