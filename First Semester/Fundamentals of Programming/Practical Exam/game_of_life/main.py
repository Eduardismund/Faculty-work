def load(self, name):
    model = []
    ok = 0
    with open("file.txt", "r") as file:
        for line in file:
            if line.strip() == name:
                ok = 1
                i = 0
            elif ok == 1 and (line.strip()[0] == 'x' or line.strip()[0] == '+'):
                parts = line.strip().split(',')
                if len(model) <= i:
                    model.append([])
                for j in range(len(parts)):
                    if parts[j] == '+':
                        model[i].append(' ')
                    else:
                        model[i].append('X')
                i += 1
            elif ok == 1 and line.strip().isalpha():
                break
    self._model = model
