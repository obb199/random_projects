import matplotlib.pyplot as plt


# aplicação de função polinomial que retorna y
def funcao(x, *args):
    y = 0
    valores = []

    # invertendo os valores dados
    for i in range(1, len(args) + 1):
        valores.append(args[-i])

    for i in range(len(args)):
        y += valores[i] * x ** i

    return y


def uso_funcao(inicio, fim, *args):
    values = []
    values_y = []
    intervalos = []
    raizes = []
    x = inicio

    # Caso não haja função:
    if len(args) == 0:
        print("Não há função para análise")

    # Caso seja uma função constante em X
    elif len(args) == 1:
        print(f"A função é constante em x = {args[0]}")

    # Caso seja uma função polinomial de primeiro grau:
    elif len(args) == 2:
        x1 = -1 * args[1] / args[0]
        if inicio <= x1 <= fim:
            print(f'A raíz da função no intervalo é {x1}')
        else:
            print(f'A funçao possui a raíz {x1}, porém não está contida no intervalo.')

    # Caso seja uma função polinominal de segundo grau:
    elif len(args) == 3:
        delta = (args[1] ** 2) - 4 * args[0] * args[2]

        if delta < 0:
            print("Não existem raízes na função.")

        elif delta == 0:
            x1 = (-1 * args[1] + delta ** (1 / 2)) / 2 * args[0]
            if inicio <= x1 <= fim:
                print('Raíz do intervalo:', x1)
            else:
                print(f"Existe uma raíz na função ({x1}), mas não está contida no intervalo")

        else:
            x1 = (-1 * args[1] + delta ** (1 / 2)) / 2 * args[0]
            x2 = (-1 * args[1] - delta ** (1 / 2)) / 2 * args[0]
            if inicio <= x1 <= fim and inicio <= x2 <= fim:
                print('raízes do intervalo:', x1, 'e', x2)
            elif inicio <= x1 <= fim:
                print(f'A função possui duas raízes ({x1}, {x2} e uma no intervalo. A raíz do intervalo é:', x1)
            elif inicio <= x2 <= fim:
                print(f'A função possui duas raízes ({x1}, {x2}) e uma no intervalo. A raíz do intervalo é:', x2)
            else:
                if len(raizes) > 0:
                    print(f"Existem raízes ({x1}, {x2}), porém não há raízes no intervalo.")

    # Caso seja uma função polinomial de grau 3 ou maior:
    else:

        while x <= fim:
            values.append(x)
            values_y.append(funcao(x, *args))
            x += 0.1

        # descobrindo intervalos que possuem raiz
        for i in range(len(values) - 1):
            if funcao(values[i], *args) == 0:
                raizes.append(i)

            elif funcao(values[i], *args) < 0 and funcao(values[i + 1], *args) > 0:
                intervalos.append((values[i], values[i + 1]))
                if len(intervalos) == len(args):
                    break

            elif funcao(values[i], *args) > 0 and funcao(values[i + 1], *args) < 0:
                intervalos.append((values[i], values[i + 1]))
                if len(intervalos) == len(args):
                    break

        # procurando raiz dentro de intervalos
        for i in intervalos:
            a = i[0]
            b = i[1]
            ref = funcao(a, *args)
            while a <= b:
                if ref > 0:
                    if funcao(a, *args) == 0 or funcao(a, *args) < 0:
                        raizes.append(a)
                        break
                    a += 0.000001
                elif ref < 0:
                    if funcao(a, *args) == 0 or funcao(a, *args) > 0:
                        raizes.append(a)
                        break
                    a += 0.000001

        if len(raizes) == 0:
            print('Intervalo não possui raízes')

        elif len(raizes) == 1:
            print('A raíz do intervalo é:', raizes)

        else:
            print("As raízes do intervalo são:", raizes)

    plt.plot(values, values_y)
    plt.xlabel('X')
    plt.ylabel('Y')
    plt.title('GRÁFICO DO INTERVALO')
    plt.show()

# EXAMPLES:
# p/ x³ + 2x² - 3x + 7 in range -5 e 5 --> uso_funcao(-5, 5 1, 2, -3, 7)

if __name__ == '__main__':
    uso_funcao(-10, 10, 1, -5, 1, 3, -2)
