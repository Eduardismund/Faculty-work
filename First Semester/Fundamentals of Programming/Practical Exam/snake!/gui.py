import tkinter as tk
from controller import Controller, GameOver

class SnakeGUI:
    def __init__(self, master):
        self.master = master
        self.master.title("Snake Game")

        self.controller = Controller()
        self.history = ["up"]
        self.contor = 0

        self.canvas = tk.Canvas(self.master, width=400, height=400, bg="white")
        self.canvas.pack()

        self.score_label = tk.Label(self.master, text="Score: 0")
        self.score_label.pack()

        self.master.bind("<Right>", self.move_right)
        self.master.bind("<Left>", self.move_left)
        self.master.bind("<Up>", self.move_up)
        self.master.bind("<Down>", self.move_down)

        self.update_ui()

    def move_right(self, event):
        self.move("right")

    def move_left(self, event):
        self.move("left")

    def move_up(self, event):
        self.move("up")

    def move_down(self, event):
        self.move("down")

    def move(self, direction):
        try:
            if direction == "right" and self.history[self.contor] != "right":
                self.controller.right()
                self.history.append(direction)
                self.contor += 1

            if direction == "left" and self.history[self.contor] != "left":
                self.controller.left()
                self.history.append(direction)
                self.contor += 1

            if direction == "down" and self.history[self.contor] != "down":
                self.controller.down()
                self.history.append(direction)
                self.contor += 1

            if direction == "up" and self.history[self.contor] != "up":
                self.controller.up()
                self.history.append(direction)
                self.contor += 1

        except GameOver as e:
            self.handle_game_over(e)

        self.update_ui()

    def update_ui(self):
        self.canvas.delete("all")
        for i in range(self.controller._board._n):
            for j in range(self.controller._board._n):
                if self.controller._board._board[i][j] == '*':
                    self.canvas.create_rectangle(j * 20, i * 20, (j + 1) * 20, (i + 1) * 20, fill="green")
                elif self.controller._board._board[i][j] == '+':
                    self.canvas.create_rectangle(j * 20, i * 20, (j + 1) * 20, (i + 1) * 20, fill="red")
                elif self.controller._board._board[i][j] == 'a':
                    self.canvas.create_rectangle(j * 20, i * 20, (j + 1) * 20, (i + 1) * 20, fill="blue")

        self.score_label.config(text=f"Score: {self.controller.score()}")
        self.master.update()

    def handle_game_over(self, e):
        print(e)

if __name__ == "__main__":
    root = tk.Tk()
    snake_gui = SnakeGUI(root)
    root.mainloop()
