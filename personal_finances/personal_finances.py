import matplotlib.pyplot as plt
import datetime

data = datetime.datetime.now()

#Verificando saldo atual
with open('dados_financa', 'r') as archive:
    lines = archive.readlines()
    saldo = int((lines[-1].split(','))[-2])


def mostra_saldo():
    global saldo
    print(f'O SALDO ATUAL: R${saldo}')


def depositar():
    global saldo
    global data

    while True:
        # RECEBENDO VALOR:
        try:
            quantia = int(input('Digite o valor de depósito: '))
            if quantia <= 0:
                print("Valor inválido para depósito.")
                continue
            else:
                saldo += quantia
        except ValueError:
            print("Valor inválido para depósito. Tente novamente.")
            continue

        # PASSANDO VALOR DADO PARA O ARQUIVO DO TEXTO
        with open('dados_financa', 'a') as archive:
            archive.write(f'{str(data.day)}/{str(data.month)}/{str(data.year)},+,{quantia},{saldo},\n')

        print(f"Foram depositados {quantia} reais e o saldo atual agora é: {saldo} reais.\n\n\n")
        break


def saque():
    global saldo
    global data

    while True:
        # RETIRANDO VALOR:
        try:
            quantia = int(input('Digite o valor que irá retirar: '))
            if quantia > 0:
                if saldo - quantia >= 0:
                    saldo -= quantia
                else:
                    print(
                        "Valor inválido. O saldo ficará negativo caso esse valor tenha sido retirado. Tente novamente.\n")
                    continue
            else:
                print("Valor inválido para saque. Tente novamente.\n")
                continue

        except ValueError:
            print("Valor inválido para saque. Tente novamente.\n")
            continue

        # PASSANDO O VALOR DADO PARA O ARQUIVO DE TEXTO
        with open('dados_financa', 'a') as archive:
            archive.write(f'{str(data.day)}/{str(data.month)}/{str(data.year)},-,{quantia},{saldo},\n')

        print(f"Foram retirados {quantia} reais e o saldo atual agora é: {saldo} reais.\n\n\n")
        break


def relatorio():
    global saldo
    global data

    # CRIANDO RELATÓRIO
    relatorio = []
    with open('dados_financa', 'r') as archive:
        lines = archive.readlines()
        for i in lines:
            data = (i.split(',')[0], i.split(',')[3], i.split(',')[1])
            relatorio.append(data)
        print()
        for i in relatorio:
            if i[2] == '+':
                print(f'DATA: {i[0]} - OPERAÇÃO: DEPÓSITO - SALDO: R${i[1]}')
            else:
                print(f'DATA: {i[0]} - OPERAÇÃO: SAQUE - SALDO: R${i[1]}')
        print()
        print()


def mostra_grafico():
    eixo_x = []
    eixo_y = []
    with open('dados_financa', 'r') as archive:
        lines = archive.readlines()
        for i in lines:
            eixo_x.append(i.split(',')[0])
            eixo_y.append(int(i.split(',')[3]))

    plt.plot(eixo_x, eixo_y)
    plt.xlabel('Datas de operação')
    plt.ylabel('Quantia em reais')
    plt.title('ANÁLISE GRÁFICA DO SALDO NA CONTA AO PASSAR DOS DIAS')
    print('\n\n')
    plt.show()


def mostra_grafico_10_dias():
    eixo_x = []
    eixo_y = []
    with open('dados_financa', 'r') as archive:
        lines = archive.readlines()
        for i in lines:
            eixo_x.append(i.split(',')[0])
            eixo_y.append(int(i.split(',')[3]))
            if len(eixo_x) >= 11:
                eixo_x.pop(0)
                eixo_y.pop(0)

    plt.plot(eixo_x, eixo_y)
    plt.xlabel('Datas de operação')
    plt.ylabel('Quantia em reais')
    plt.title('ANÁLISE GRÁFICA DO SALDO NA CONTA AO PASSAR DOS DIAS')
    print('\n\n')
    plt.show()


while True:
    while True:
        print("||///////////////////////////////////////////////////////////////////||")
        print("|| DIGITE 1 PARA VERIFICAR O SALDO                                   ||")
        print("|| DIGITE 2 PARA REALIZAR UM DEPÓSITO                                ||")
        print("|| DIGITE 3 PARA REALIZAR UM SAQUE                                   ||")
        print("|| DIGITE 4 PARA VISUALIZAR O ESTRATO                                ||")
        print("|| DIGITE 5 PARA VISUALIZAR O GRÁFICO DOS SALDOS GLOBAIS             ||")
        print("|| DIGITE 6 PARA VISUALIZAR O GRÁFICO DAS ÚLTIMOS DEZ TRANSFERÊNCIAS ||")
        print("||\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\||")

        try:
            escolha = int(input('Digite aqui: '))
        except ValueError:
            print("Valor digitado inválido. Tente novamente")
            continue

        if escolha < 1 or escolha > 6:
            print("Opção inexistente. Tente novamente\n")
        else:
            break

    if escolha == 1:
        mostra_saldo()

    elif escolha == 2:
        depositar()

    elif escolha == 3:
        saque()

    elif escolha == 4:
        relatorio()

    elif escolha == 5:
        mostra_grafico()

    elif escolha == 6:
        mostra_grafico_10_dias()

    resp = input('Deseja utilizar outra função? [S/N]')
    while resp != 'S' and resp != 'N':
        print("Valor inválido.")
        resp = input("Deseja utilizar outra função? [S/N] ")

    if resp == 'N':
        break
    else:
        print('\n\n\n')
