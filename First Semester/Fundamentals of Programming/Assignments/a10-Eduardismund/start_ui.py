from domain.board import Board
from service.service import GomokuService
from ui_.ui import TextGomokuUI

if __name__ == "__main__":
    board = Board(size=15)
    service = GomokuService(board)
    ui = TextGomokuUI(service)
    ui.play_game()