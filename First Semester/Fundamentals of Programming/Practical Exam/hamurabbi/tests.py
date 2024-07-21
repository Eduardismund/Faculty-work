import unittest

from repo import RepoError
from service import Controller


class Tests(unittest.TestCase):
    def test1(self):
        controller = Controller()
        controller.send_info(0, 2000, 800)
        land, grain = controller.info()
        self.assertEqual(land, 1000 )
        self.assertEqual(grain, 0)

    def test_2(self):
        controller = Controller()
        with self.assertRaises(RepoError): controller.send_info(2000, 3000, 900)

    def test_3(self):
        controller = Controller()
        with self.assertRaises(RepoError): controller.send_info(-2000, 3000, 900)

    def test_4(self):
        controller = Controller()
        with self.assertRaises(RepoError): controller.send_info(0, 3000, 900)

    def test_5(self):
        controller = Controller()
        with self.assertRaises(RepoError): controller.send_info(0, 400, 2000)