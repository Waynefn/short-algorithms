class Solution(object):

    def __init__(self):
        self.NUM_SET = set("123456789")
        self.rows = [None] * 9
        self.columns = [None] * 9
        self.blocks = [[None] * 3, [None] * 3, [None] * 3]

    def get_choice(self, board, i, j):
        if board[i][j] != '.':
            return set()
        return self.NUM_SET - self.rows[i] - self.columns[j] - self.blocks[i // 3][j // 3]

    def update_info(self, board):
        for i in range(9):
            self.rows[i] = set(board[i]) - set('.')
            self.columns[i] = set([x[i] for x in board]) - set('.')
        for i in range(3):
            for j in range(3):
                self.blocks[i][j] = set([y for x in board[i * 3:i * 3 + 3] for y in x[j * 3:j * 3 + 3]]) - set('.')
        return

    def get_adj(self, board, choice, i, j):
        for cho in choice:
            flag = True
            for ii in range(i // 3 * 3, i // 3 * 3 + 3):
                for jj in range(j // 3 * 3, j // 3 * 3 + 3):
                    if ii == i and jj == j:
                        continue
                    if cho in self.get_choice(board, ii, jj):
                        flag = False
                if not flag:
                    break
            if flag:
                return [cho]
        return choice

    def solveSudoku(self, board):
        """
        :type board: List[List[str]]
        :rtype: void Do not return anything, modify board in-place instead.
        """
        self.update_info(board)
        board_tmp = []
        while True:
            if board_tmp == board:
                break
            board_tmp = board[:]
            for i in range(9):
                for j in range(9):
                    if board[i][j] == '.':
                        choice = self.get_choice(board, i, j)
                        if len(choice) > 1:
                            choice = self.get_adj(board, choice, i, j)
                        if len(choice) == 1:
                            num = choice.pop()
                            self.rows[i].add(num)
                            self.columns[j].add(num)
                            self.blocks[i // 3][j // 3].add(num)
                            board[i][j] = num
        self.solveSudoku2(board)
    def dfs(self, board, stack1, stack2):
        if not stack1: return
        x, y = stack1.pop()
        stack2.append((x, y))
        box = [board[x // 3 * 3 + i][y // 3 * 3 + j] for i in range(3) for j in range(3)]
        row = [board[x][j] for j in range(9)]
        col = [board[i][y] for i in range(9)]
        for i in "123456789":
            if not any([i in box, i in col, i in row]):
                board[x][y] = i
                self.dfs(board, stack1, stack2)
                if not stack1: return
        board[x][y] = "."
        pos = stack2.pop()
        stack1.append(pos)
    def solveSudoku2(self, board):
        stack1 = [(i, j) for i in range(9) for j in range(9) if board[i][j] == "."]
        stack2 = []
        self.dfs(board, stack1, stack2)

a = Solution()
board = [[".", ".", "9", "7", "4", "8", ".", ".", "."],
         ["7", ".", ".", ".", ".", ".", ".", ".", "."],
         [".", "2", ".", "1", ".", "9", ".", ".", "."],
         [".", ".", "7", ".", ".", ".", "2", "4", "."],
         [".", "6", "4", ".", "1", ".", "5", "9", "."],
         [".", "9", "8", ".", ".", ".", "3", ".", "."],
         [".", ".", ".", "8", ".", "3", ".", "2", "."],
         [".", ".", ".", ".", ".", ".", ".", ".", "6"],
         [".", ".", ".", "2", "7", "5", "9", ".", "."]]
a.solveSudoku(board)
print(board)
