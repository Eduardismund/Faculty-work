import tkinter as tk
from domain.board import Board
from service.service import GomokuService
from ui_.ui import GomokuGUI

if __name__ == "__main__":
    root = tk.Tk()
    board = Board(size=15)
    service = GomokuService(board)
    gui = GomokuGUI(root, service)
    root.mainloop()