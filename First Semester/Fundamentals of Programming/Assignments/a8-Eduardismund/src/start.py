from random import randint
from src.ui.UI import UI


def generate_unique_numbers(num_numbers, start_range, end_range):
    unique_numbers = set()

    while len(unique_numbers) < num_numbers:
        random_number = randint(start_range, end_range)
        unique_numbers.add(random_number)

    return list(unique_numbers)



list_of_numbers = generate_unique_numbers(20, 100, 999)
ui = UI(list_of_numbers)
ui.print_menu()









