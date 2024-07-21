import unittest

from controller import Controller


class Test(unittest.TestCase):
    def test1(self):
        controller = Controller()
        controller.make_human_move(1,1, 'X')
        controller.make_human_move(2, 2, 'X')
        controller.make_human_move(3, 3, 'X')
        controller.make_human_move(4, 4, 'X')
        controller.make_ai_move()
        self.assertEqual(controller.coordinates(0,0), "O")

    def test2(self):
        controller = Controller()
        controller.make_ai_move()
        self.assertEqual(controller.contor(), 1)


