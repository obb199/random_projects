#any line in dictionary represents a word, first the english representation, second '=', third the portuguese representation
with open('words.txt', 'r') as arquivo:
    dictionary = arquivo.readlines()


def english_portuguese(word): #Funciona
    """search in dictionary a meaning of a english word"""
    found = False
    for i in range(0, len(dictionary)):
        english_word = dictionary[i].split()
        if english_word[0] == word:
            print(f"A tradução da palavra '{english_word[0]}' é '{english_word[2]}'")
            found = True
        if i == len(dictionary) - 1 and found == False:
            print('Palavra não encontrada. =(')


def portuguese_english(word):
    """search in dictionary a meaning of a portuguese word"""
    found = False
    for i in range(0, len(dictionary)):
        portuguese_word = dictionary[i].split()
        if portuguese_word[2] == word:
            print()
            print()
            print(f"A tradução da palavra '{portuguese_word[2]}' é '{portuguese_word[0]}'")
            found = True
        if i == len(dictionary) - 1 and found == False:
            print()
            print()
            print('Palavra não encontrada. =(')



menu = ''
while menu != 'sair':
    print('|==================DICIONÁRIO PORTUGUÊS E INGLÊS====================|')
    print('|                                                                   |')
    print("| Digite '1' para procurar o significado de uma palavra em português|")
    print('|                                                                   |')
    print("| Digite '2' para procurar o significado de uma palavra em inglês   |")
    print('|                                                                   |')
    print("| Digite 'sair' para finalizar.                                     |")
    print('|                                                                   |')
    print('| ================================================================= |')
    print()
    print()
    menu = input('Digite o comando a seguir: ')
    menu = menu.lower().strip()

    if menu == '1':
        print()
        word = input('Qual palavra deseja traduzir?')
        word = word.lower().strip()
        portuguese_english(word)
    elif menu == '2':
        print()
        word = input('Qual palavra deseja traduzir?')
        word = word.lower().strip()
        english_portuguese(word)
    elif menu == 'sair':
        print()
        print('Obrigado por utilizar nosso dicionário!!!')
    else:
        print()
        print("Comando inválido. Utilize apenas '1', '2' e 'sair'")

    print()
    print()
    print()
    print()
