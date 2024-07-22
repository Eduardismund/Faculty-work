import tkinter as tk
from domain.board import BoardError


class TextGomokuUI:
    def __init__(self, service):
        self.service = service
        self.current_player = 'X'

    def make_player_move(self, row, col):
        success = self.service.make_player_move(row, col)
        if success:
            print("_____THE CURRENT STATE OF THE GAME_____")
            print(self.service.to_display())

    def play_game(self):
        print("\tWelcome to my implementation of the game -Gomoku-")
        print("_________________________________________________________________")
        print("You will play against a low-level AI that will eagerly try to block most of your attempts to win!")
        input("Press Enter to start...")

        while True:
            if self.current_player == 'X':
                try:
                    row = int(input("Enter row (1-15): ")) - 1
                    col = int(input("Enter column (1-15): ")) - 1
                    self.make_player_move(row, col)

                    if self.service.check_winner('X', row, col):
                        print("Congrats! You won!")
                        option = input("Press 1 to play again or 2 to exit: ")
                        if option == '1':
                            self.service.clear_table()
                            self.play_game()
                        elif option == '2':
                            print("Goodbye!")
                            return

                    self.current_player = 'O'
                    input("Press Enter to change turns with the AI...")
                except (ValueError, IndexError, BoardError) as e:
                    print(f"Error: {e}")
            else:
                row, col = self.service.make_ai_move()
                print("_____THE CURRENT STATE OF THE GAME_____")
                print(self.service.to_display())

                if self.service.check_winner('O', row, col):
                    print("Commiserations! AI won!")
                    option = input("Press 1 to play again or 2 to exit: ")
                    if option == '1':
                        self.service.clear_table()
                        self.play_game()
                    elif option == '2':
                        print("Goodbye!")
                        return

                self.current_player = 'X'
            try:
                self.service.check_is_draw()
            except BoardError as e:
                print(e)
                option = input("Press 1 to play again or 2 to exit: ")
                if option == '1':
                    self.service.clear_table()
                    self.play_game()
                elif option == '2':
                    print("Goodbye!")
                    return


class GomokuGUI:
    def __init__(self, master, service):
        self.master = master
        self.master.title("Gomoku Game")
        self.service = service
        self.current_player = 'X'
        self.game_over = False
        self.score_x = 0
        self.score_o = 0
        self.create_widgets()

    def create_widgets(self):
        self.message_label = tk.Label(self.master, text="Welcome to Gomoku!")
        self.message_label.grid(row=0, column=0, columnspan=2)

        self.score_label = tk.Label(self.master, text="Score: X - 0, O - 0", fg="black", font=("Helvetica", 12))
        self.score_label.grid(row=0, column=2, columnspan=2, pady=10)

        self.canvas = tk.Canvas(self.master, width=400, height=400, borderwidth=2, relief="solid")
        self.canvas.grid(row=1, column=0, columnspan=2)

        self.reset_button = tk.Button(self.master, text="Reset Game", command=self.reset_game, fg="white", bg="purple")
        self.reset_button.grid(row=2, column=0, columnspan=2, pady=10)

        self.canvas.bind("<Button-1>", self.on_canvas_click)

        self.update_board_display()

    def on_canvas_click(self, event):
        if self.game_over:
            return
        row = int(event.y / 25)
        col = int(event.x / 25)

        try:
            self.service.make_player_move(row, col)
            if self.service.check_winner('X', row, col):
                self.update_board_display()
                self.update_score('X')
                self.display_winner('X')
                self.game_over = True
            else:
                self.current_player = 'O'
                self.service.check_is_draw()
                row, col = self.service.make_ai_move()
                if self.service.check_winner('O', row, col):
                    self.update_score('O')
                    self.display_winner('O')
                    self.game_over = True
                self.current_player = 'X'
                self.update_board_display()
        except BoardError as e:
            self.message_label.config(text=f"Error: {e}")

    def update_board_display(self):
        self.canvas.delete("all")
        for i in range(1, 15):
            self.canvas.create_line(i * 25, 0, i * 25, 400)
            self.canvas.create_line(0, i * 25, 400, i * 25)

        for row in range(15):
            for col in range(15):
                player = self.service.get_player_at(row, col)
                if player != ' ':
                    color = "black" if player == 'X' else "red"
                    self.canvas.create_text(col * 25 + 12, row * 25 + 12, text=player, fill=color,
                                            font=("Helvetica", 10, "bold"))

    def update_score(self, player):
        if player == 'X':
            self.score_x += 1
        elif player == 'O':
            self.score_o += 1
        self.score_label.config(text=f"Score: X - {self.score_x}, O - {self.score_o}")

    def display_winner(self, player):
        self.message_label.config(text=f"Congratulations! Player {player} wins!", fg="blue")

    def reset_game(self):
        self.game_over = False
        self.service.clear_table()
        self.current_player = 'X'
        self.message_label.config(text="Game reset.", fg="blue")
        self.update_board_display()