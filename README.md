# sudoku-solver
A Sudoku 3x3 solver with multiple solving techniques

Currently implemented:
- Brute force solver (with possible value prechecking)
- Stochastic brute force solver (with shuffled possible value prechecking)

The current implementations find the possible values that can be placed in the target cell.

The brute force solver walks through the branches starting from 1 and going up to 9. As a result of this puzzles can be designed to counteract this approach i.e. by forcing it to solve the first row as 9 8 7 6 5 4 3 2 1, which could take tens of millions of iterations.
The stochastic solver attempts to lower this worst case scenario by randomly selecting the cell values from the possible values. The upper bound for complexity is the same as the brute force approach but now puzzles cannot be designed maliciously in the same manner.

Next stages:
- Interactive web app (user can add clues to the grid and see the backtracking process)
- Iterations per second counter
- Other solving approaches
