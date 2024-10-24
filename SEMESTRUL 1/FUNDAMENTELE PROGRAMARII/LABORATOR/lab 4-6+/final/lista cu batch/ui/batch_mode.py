from ui.console import process_command_UI
from domain.e_list import generate_expenses
def run_batch_mode():
    expenses_list = generate_expenses()
    undo_list = [[]]
    commands = input("Introduceți comenzile sub formă de șir: ")
    commands_list = commands.split(';')
    for cmd in commands_list:
        process_command_UI(expenses_list, undo_list, cmd.strip())