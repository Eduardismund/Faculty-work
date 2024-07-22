class FunctionCall:
    # this implements the Command design pattern
    def __init__(self, f_name, *f_params):
        # *f_params is variable number of arguments
        self.__fname = f_name
        self.__fparams = f_params

    def call(self):
        return self.__fname(*self.__fparams)  # () function call operator

    def __call__(self, *args, **kwargs):
        """
        Overloads the function call operator -> ()
        :param args:
        :param kwargs:
        :return:
        """
        return self.call()


class Operation:
    def __init__(self, undo_function: FunctionCall, redo_function: FunctionCall):
        self.__undo_function = undo_function
        self.__redo_function = redo_function

    def undo(self):
        self.__undo_function()  # we use the () operator
        # self.__undo_function.call() # <=> to the line above

    def redo(self):
        self.__redo_function()


class CascadedOperation:
    """
    Composite design pattern
    """

    def __init__(self, *operations):
        self.__operations = operations

    def undo(self):
        for op in self.__operations:
            op.undo()

    def redo(self):
        for op in self.__operations:
            op.redo()


class UndoError(Exception):
    pass


class UndoService:

    def __init__(self):
        # history of program operations
        self.__history = []
        # where we are in the history
        self.__index = -1

    def record_undo(self, operation: Operation):
        self.__history.append(operation)
        self.__index = len(self.__history) - 1

    def undo(self):
        if self.__index == -1:
            raise UndoError("No more undos!")
        self.__history[self.__index].undo()
        # we go back 1 operation
        self.__index -= 1

    def redo(self):
        if self.__index == len(self.__history) - 1:
            raise UndoError("No more redos!")
        # we go forward 1 operation
        self.__index += 1
        self.__history[self.__index].redo()
