#include <stdio.h>
#include <string.h>
#include <locale.h>

void leitura_dos_dados(int codmu[1348], int ano[1348], char nome[1348][50], int CV_SCR[1348]);
void busca_por_ano(char nome[1348][50], int CV_SCR[1348], int ano[1348], int codmu[1348]);
void busca_por_codigo(char nome[1348][50], int CV_SCR[1348], int ano[1348], int codmu[1348]);

int main(){
    setlocale(LC_ALL, "Portuguese"); // command to possibility accentuation

    //values from dataset:
    int codmu[1348];
    int ano[1348];
    char nome[1348][50];
    int CV_SCR[1348];

    leitura_dos_dados(codmu, ano, nome, CV_SCR); // Function to read values and put then in correctly array

    //Main menu
    int escolha = 0;

    while(1){ // Infinity loop
        printf("--------------------------------------------------------------------\n");
        printf("**ANÁLISE DE DADOS SOBRE VACINAÇÃO DE SARAMPO DOS ESTADOS DO NORTE**\n");
        printf("--------------------------------------------------------------------\n\n");

        printf("1 - Pesquisar maiores valores de pessoas vacinadas por ano\n"); // search biggest values per year.
        printf("2 - Pesquisar dados por código da cidade\n"); // search values for any city with the code.
        printf("3 - Sair\n"); // exit.
        scanf("%d", &escolha);

        switch(escolha){
            case 1: busca_por_ano(nome, CV_SCR, ano, codmu); break;
            case 2: busca_por_codigo(nome, CV_SCR, ano, codmu); break;
            case 3: return 1;
            default: printf("Valor inválido. Escolha valores entre 1 e 3 \n"); // to invalid values
        }
    }

    return 0;
}



void leitura_dos_dados(int codmu[1348], int ano[1348], char nome[1348][50], int CV_SCR[1348]){
    FILE *arquivo;

    arquivo = fopen("base_vacinas.csv", "r"); //opening dataset

    if (arquivo == NULL){
        printf("O arquivo não pode ser lido. Tente novamente. ");
    }

    char string[100];
    char *token;

    //Reading the title:
    fgets(string, 100, arquivo);

    int i = 0;
    while (fgets(string, sizeof(string), arquivo) != NULL){

        token = strtok(string, ",");
        codmu[i] = atoi(token);
        token = strtok(NULL, ",");
        ano[i] = atoi(token);
        token = strtok(NULL, ",");
        strcpy(nome[i], token);
        token = strtok(NULL, ",");
        CV_SCR[i] = atoi(token);
        i++;
    }

    fclose(arquivo); //closing the archive after reading

    //SORTING PROCESS:

    //assistants values
    char nome_aux[50];
    int CV_SCR_aux = 0;
    int ano_aux = 0;
    int codmu_aux = 0;
    int j = 0;

    //sorting with amount of vaccinated peoples per year:

    //Sorting 2016
    for (int i=0; i<449; i++){
        strcpy(nome_aux, nome[i]);
        CV_SCR_aux = CV_SCR[i];
        codmu_aux = codmu[i];

        j = i - 1;
        while(j >= 0 && CV_SCR[j] < CV_SCR_aux){
            strcpy(nome[j+1], nome[j]);
            CV_SCR[j+1] = CV_SCR[j];
            codmu[j+1] = codmu[j];

            j--;
        }
        strcpy(nome[j+1], nome_aux);
        CV_SCR[j+1] = CV_SCR_aux;
        codmu[j+1] = codmu_aux;
        }

    //Sorting 2017
    for (int i=450; i<898; i++){
        strcpy(nome_aux, nome[i]);
        CV_SCR_aux = CV_SCR[i];
        codmu_aux = codmu[i];

        j = i - 1;
        while(j >= 449 && CV_SCR[j] < CV_SCR_aux){
            strcpy(nome[j+1], nome[j]);
            CV_SCR[j+1] = CV_SCR[j];
            codmu[j+1] = codmu[j];

            j--;
        }
        strcpy(nome[j+1], nome_aux);
        CV_SCR[j+1] = CV_SCR_aux;
        codmu[j+1] = codmu_aux;
    }

    //Sorting 2018
    for (int i=899; i<1347; i++){
        strcpy(nome_aux, nome[i]);
        CV_SCR_aux = CV_SCR[i];
        codmu_aux = codmu[i];

        j = i - 1;
        while(j >= 898 && CV_SCR[j] < CV_SCR_aux){
            strcpy(nome[j+1], nome[j]);
            CV_SCR[j+1] = CV_SCR[j];
            codmu[j+1] = codmu[j];

            j--;
        }
        strcpy(nome[j+1], nome_aux);
        CV_SCR[j+1] = CV_SCR_aux;
        codmu[j+1] = codmu_aux;
    }
}


void busca_por_ano(char nome[1348][50], int CV_SCR[1348], int ano[1348], int codmu[1348]){

    int escolha = 0;
    printf("\nDigite qual ano deseja visualizar as cidades com mais pessoas vacinadas: ");
    scanf("%d", &escolha);

    //loop para garantir que o valor colocado seja algum dos anos válidos
    while(escolha != 2016 && escolha != 2017 && escolha != 2018){
        printf("Valor digitado é inválido. Digite uma data entre 2016 e 2018: ");
        scanf("%d", &escolha);
    }

    int count = 0; //variable to finish the loop before the normal end
    char escolha_salvar[2];

    int valores_usados[5];// array para guardar os índices usados

    for(int i=0;i<1348; i++){
        if (ano[i] == escolha){
            printf("%s %d\n", nome[i], CV_SCR[i]);
            valores_usados[count] = count;
            count++;
       }
        if (count == 5){ // após achar os valores o loop é terminado
            break;
        }
    }

    printf("\nDeseja salvar os dados visualizados? [S/N] ");
    scanf("%s[^\n]", &escolha_salvar);

    //Loop while user put invalid values:
    while (strcasecmp(escolha_salvar, "S") != 0 && strcasecmp(escolha_salvar, "N") != 0){
        printf("\n O valor digitado é inválido. Digite apenas 'S' ou 'N'.\n");
        printf("\n Deseja salvar os dados visualizados? [S/N]");
        scanf("%s[^\n]", &escolha_salvar);
    }

    //Case user want to save the datas:
    if (strcasecmp(escolha_salvar, "S") == 0){
        FILE *arquivo;
        int aux;

        if (escolha == 2016){
            arquivo = fopen("2016.csv", "w");
            fprintf(arquivo, "Cidades com mais pessoas vacinadas em 2016: \n");
            for (int i = 0; i<5; i++){
                aux = valores_usados[i];
                fprintf(arquivo, "%s,%d\n", nome[aux], CV_SCR[aux]);
                if (i == 4){
                    printf("\nDados salvos com sucesso!\n\n");
                    fclose(arquivo);
                }
            }
        }else{
            if (escolha == 2017){
                arquivo = fopen("2017.csv", "w");
                fprintf(arquivo, "Cidades com mais pessoas vacinadas em 2017: \n");
                for (int i = 0; i<5; i++){
                    aux = valores_usados[i];
                    fprintf(arquivo, "%s,%d\n", nome[aux], CV_SCR[aux]);
                    if (i == 4){
                        printf("\nDados salvos com sucesso!\n\n");
                        fclose(arquivo);
                        }
                    }
            }else{
                arquivo = fopen("2018.csv", "w");
                fprintf(arquivo, "Cidades com mais pessoas vacinadas em 2018: \n");
                for (int i = 0; i<5; i++){
                    aux = valores_usados[i];
                    fprintf(arquivo, "%s,%d\n", nome[aux], CV_SCR[aux]);
                    if (i == 4){
                        printf("\nDados salvos com sucesso!\n\n");
                        fclose(arquivo);
                        }
                    }
                }
            }
        }
    printf("\nRetornando ao menu principal.. \n\n\n");
    }


void busca_por_codigo(char nome[1348][50], int CV_SCR[1348], int ano[1348], int codmu[1348]){

    int codigo = -1;
    short int existencia = 0; // value to use equals a bool variable
    int count = 0; // counter to break the loop while the normal finish


    while (1){
        printf("\n\nDigite o código que deseja procurar: ");
        scanf("%d", &codigo);

        existencia = 0;
        count = 0;
        char escolha = "E";

        for(int i=0; i<1348; i++){
            if (codmu[i] == codigo){
                if (count == 0){
                    printf("Cidade do código fornecido: %s\n\n", nome[i]);
                }
                printf("%d - %d vacinados\n\n", ano[i], CV_SCR[i]);
                count++;
                }
                if (count == 3){
                    existencia = 1;
                    break;
                }
            }

        if (existencia == 1){
            printf("Pesquisa realizada com sucesso!!\n\n");
        }else{
            printf("Valor inválido.\n\n");
        }
        printf("Deseja fazer outra busca? [S/N]");
        scanf(" %c", &escolha);

        while (escolha != 83 && escolha != 78 && escolha != 115 && escolha != 110){ // S = 83, N = 78, s = 115, n = 110
            printf("Valor inválido. Digite apenas 'S' ou 'N'\n\n");
            printf("Deseja fazer outra busca? [S/N]");
            scanf(" %c", &escolha);
        }
        if (escolha == 78 || escolha == 110){
            printf("\n\n\n\n\n");
            break;
        }
    }
}
