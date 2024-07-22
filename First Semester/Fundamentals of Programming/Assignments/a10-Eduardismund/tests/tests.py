import unittest
from domain.board import Board, BoardError
from service.service import GomokuService


class Tests(unittest.TestCase):
    def setUp(self):
        self.test_board = Board()
        self.service = GomokuService(self.test_board)

    def test_make_player_move(self):
        self.setUp()
        expected_board = [[' ' for _ in range(15)] for _ in range(15)]
        expected_board[1][1]='X'
        self.service.make_player_move(1, 1)
        self.assertEqual(expected_board, self.service.board._board)

    def test_raise_error_move_1(self):
        self.setUp()
        with self.assertRaises(BoardError): self.service.make_player_move(20, 20)

    def test_raise_error_move_2(self):
        self.setUp()
        self.service.make_player_move(1, 1)
        with self.assertRaises(BoardError): self.service.make_player_move(1, 1)

    def test_is_draw(self):
        self.setUp()
        for i in range(15):
            for j in range(15):
                self.service.make_player_move(i, j)
        with self.assertRaises(BoardError): self.service.check_is_draw()

    def test_win_1(self):
        self.setUp()
        for i in range(5):
            self.service.make_player_move(i, 0)
        self.assertEqual(self.service.check_winner('X', 4, 0), True)

    def test_win_2(self):
        self.setUp()
        for i in range(5):
            self.service.make_player_move(0, i)
        self.assertEqual(self.service.check_winner('X', 0, 4), True)

    def test_win_3(self):
        self.setUp()
        for i in range(5):
            self.service.make_player_move(i, i)
        self.assertEqual(self.service.check_winner('X', 4, 4), True)

    def test_win_4(self):
        self.setUp()
        for i in range(5):
            self.service.make_player_move(i, 5-i-1)
        self.assertEqual(self.service.check_winner('X', 4, 0), True)

    def test_not_win(self):
        self.setUp()
        self.service.make_player_move(1, 1)
        self.assertEqual(self.service.check_winner('X', 1, 1), False)

    def test_clear(self):
        self.setUp()
        for i in range(15):
            for j in range(15):
                self.service.make_player_move(i, j)
        expected_board = [[' ' for _ in range(15)] for _ in range(15)]
        self.service.clear_table()
        self.assertEqual(expected_board, self.service.board._board)


    def test_win_ai_1(self):
        self.setUp()
        for i in range(4):
            self.service.make_player_move(0, i)
        self.assertEqual(self.service.make_ai_move(), (0,4))

    def test_win_ai_2(self):
        self.setUp()
        for i in range(4):
            self.test_board.make_move('O',0, i)
        self.assertEqual(self.service.make_ai_move(), (0,4))

    def test_win_ai_3(self):
        self.setUp()
        x, y=self.service.make_ai_move()
        self.assertEqual(self.service.board._board[x][y], 'O')

    def test_display(self):
        self.setUp()
        self.service.make_player_move(0, 1)
        self.service.to_display()