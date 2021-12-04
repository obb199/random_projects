#include <iostream>
#include <cstdlib>
#include <ctime>
#include <omp.h>
#include <locale.h>

using namespace std;

void geracao_dados(int, int, int, double []);
void criacao_histograma(double[], int, int, int[], int, int, double[]);
void visualizacao_histograma(int, int[], double[]);

int main(void){
    setlocale (LC_ALL,"Portuguese"); // Fun��o utilizada para permitir o uso de acentua��o.

    int n_dados, n_bins, menor, maior;

    // DADOS PASSADOS VIA TECLADO PELO USU�RIO:
    cout << "Digite quantos dados ser�o gerados:\n";
    cin >> n_dados;
    cout << "Digite quantos bins ser�o utilizados para a divis�o dos dados no histograma: ";
    cin >> n_bins;
    cout << "Digite o menor valor para os dados no intervalo: ";
    cin >> menor;
    cout << "Digite o maior valor para os dados no intervalo: ";
    cin >> maior;

    double dados[n_dados], intervalos[n_bins + 1];
    int bins[n_bins];

    // CHAMADA DAS FUN��ES E VISUALIZA��O DOS DADOS:

    geracao_dados(menor, maior, n_dados, dados);
    criacao_histograma(dados, n_dados, n_bins, bins, menor, maior, intervalos);

    cout << "\n\nDADOS GERADOS NO INTERVALO [" << menor << "," << maior << "]: ";

    #pragma omp parallel for num_threads(4)
    {
        for (int i = 0; i < n_dados-1; i++){
            printf("%.2f, ", dados[i]);
        }
    }
    printf("%.2f", dados[n_dados-1]); //�ltimo valor printado fora do loop para n�o aparecer a v�rgula nem necessitar de condicionais extras no loop.

    cout << "\n\nVALORES DE FREQU�NCIA PARA CADA BIN: ";

    for (int i = 0; i < n_bins; i++) printf("%d ", bins[i]);


    cout << "\n\nHISTOGRAMA COM A FREQU�NCIA RELATIVA DOS BINS: \n";
    visualizacao_histograma(n_bins, bins, intervalos);

    return 0;

}

void geracao_dados(int menor, int maior, int n, double vec[]){
    /*
    Fun��o sem retorno que necessita de 3 vamos inteiros (extremos do intervalo e o tamanho do intervalo) e um vetor de doubles.

    A fun��o gera n n�meros reais com duas casas de precis�o e armazena no vetor vec, para isso � gerado dois n�meros pseudoaleat�rios inteiros e um deles � convertido para decimal (variando entre 0.0 e 0.99).

    Para o loop da gera��o � utilizado a divertiva para paralelismo em loop for do openmp.
    */

    double parte_real;
    srand((unsigned)time(0));

    #pragma omp parallel for num_threads(4) reduction (=: vec[i])
    {
        for (int i = 0; i < n; i++){
            parte_real = (rand()%99);
            vec[i] = rand()%(maior-menor+1) + menor + parte_real/100;
            if (vec[i] > maior){
                vec[i] -= 1;
            }else{
                if (vec[i] < menor){
                    vec[i] += 1;
                }
            }
        }
    }
}

void criacao_histograma(double dados[], int qtd_dados, int n_bins, int bins[], int menor, int maior, double intervalos[]){
    /*
    A fun��o void (sem retorno) necessita de dois vetores do tipo double, um com os dados dos valores pseudoaleat�rios dentro do intervalo pr�-estabelecido, e um vetor para guardar os valores de cada intervalo,
    al�m de um vetor do tipo inteiro para guardar a frequ�ncia dos valores de cada intervalo. Junto disso, quatro valores inteiros s�o necess�rios, o menor e maior valor do intervalo, a quantidade
    de bins e quantidade de dados.

    A fun��o gera um valor inicial e um valor acrescido pr� estabelecido para diferenciar os intervalos, e com dois loops for aninhados, calcula a frequ�ncia de cada intervalo.

    O paralelismo da fun��o utiliza a divetiva omp for nowait para n�o esperar o loop principal, enquanto tamb�m � utilizado a diretiva omp for lastprivate(i) para esperar cada itera��o,
    pois o segundo loop � dependente do primeiro.
    */

    //declara��o dos valores necess�rios
    double acrescimo_bin = (double)(maior-menor)/(double)(n_bins);
    double bin_anterior = menor;
    double bin_atual = menor + acrescimo_bin;
    int contador;

    #pragma omp parallel num_threads(4)
    {
    #pragma omp for nowait
    {
        for(int i = 0; i < n_bins; i++){
            contador = 0;
            intervalos[i] = bin_anterior;
            #pragma omp for lastprivate(i) num_threads(4)
            {
                for (int j = 0; j < qtd_dados; j++){
                    if (dados[j] < bin_atual){
                        if (dados[j] >= bin_anterior){
                            contador++;
                        }
                    }
                }
                // Atualiza��o dos dados
                bins[i] = contador;
                bin_anterior = bin_atual;
                bin_atual += acrescimo_bin;
                }
            }
            intervalos[n_bins] = bin_anterior;
        }
    }
}

void visualizacao_histograma(int n_bins, int bins[], double intervalos[]){
    /*
        Nesta ultima fun��o, tamb�m sem retorno como as anteriores, � necess�rio a quantidade de bins, o vetor que armazenou a frequ�ncia dos bins e o valor dos intervalos.
        A fun��o itera de 0 at� n_bins para printar o intervalo e a cada itera��o h� um segundo loop que utiliza o s�mbolo "|" para determinar
        o tamanho do histograma, a cada 1 vez que algum valor apareceu na lista, uma barra � adicionada ao histograma.

        O paralelismo utiliza-se da diretiva omp parallel for para paralelizar os loops, como o segundo loop depende do primeiro, � utilizado a divertiva lastprivate para aguardar o acrescimo de i
            */
    #pragma omp parallel for num_threads(4)
    {
        for(int i = 0; i < n_bins; i++){
            printf("%7.2f - %7.2f: ", intervalos[i], intervalos[i+1]);
        #pragma omp for lastprivate(i)
        {
                for (int j = 0; j < bins[i]; j++){
                    cout << "|";
                }
                printf("\n");
            }
        }
    }
}
