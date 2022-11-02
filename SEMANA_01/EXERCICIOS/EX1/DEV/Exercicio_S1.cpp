#include <iostream>
#include <string>
using namespace std;
// 1 -  Faça uma função que recebe uma certa medida e ajusta ela percentualmente
// entre dois valores mínimo e máximo e retorna esse valor

int percent(int entrada,int minimo,int maximo){
    return float((entrada-minimo))/float((maximo-minimo))*100; //claculo de ajuste 
	//entre o minimo e maximo
}
// 2 - Faça uma função que simule a leitura de um sensor lendo o
// valor do teclado ao final a função retorna este valor
int leitor() {
    int teclado;
    cin >> teclado; //entrada de informação (input)
    return teclado; //saída de informação
}
// 3 - Faça uma função que armazena uma medida inteira qualquer
// em um vetor fornecido. Note que como C não possui vetores
// nativos da linguagem, lembre-se que você precisa passar o
// valor máximo do vetor assim como a última posição preenchida
// Evite também que, por acidente, um valor seja escrito em
// uma área de memória fora do vetor
int armazena(int nova_entrada, int ultima_entrada, int *v, int tamanho){
    int *array = v;
    array[ultima_entrada] = nova_entrada;
    return ultima_entrada + 1;
}
// 4 - Faça uma função que recebe um vetor com 4 posições que contém
// o valor da distância de um pequeno robô até cada um dos seus 4 lados.
// A função deve retornar duas informações: A primeira é a direção
// de maior distância ("Direita", "Esquerda", "Frente", "Tras") e a
// segunda é esta maior distância.
const char* direcao(int *array, int *valor_maximo){
    const char* direcoes[] = {"Direita", "Esquerda", "Frente", "Trás"};
    int indice = -1;
    for(int i = 0; i<4; i++){
        if (array[i] > *valor_maximo){
            *valor_maximo = array[i];
            indice = i;
        }
    }
    return direcoes[indice];
}
// 5 - Faça uma função que pergunta ao usuário se ele deseja continuar o mapeamento e
// retorna verdadeiro ou falso
bool comando(){
    char resposta;
    cout << "Deseja continuar o processo? (s/n)" << endl;
    cin >> resposta;
    if(toupper(resposta) == 'n'){
        return false;
    }
    return true;
}
// 6 - A função abaixo (que está incompleta) vai "dirigindo" virtualmente um robô
// e através de 4 sensores em cada um dos 4 pontos do robo ("Direita", "Esquerda",
// "Frente", "Tras").
//      A cada passo, ele verifica as distâncias aos objetos e vai mapeando o terreno
// para uma movimentação futura.
//      Ele vai armazenando estas distancias em um vetor fornecido como parâmetro
// e retorna a ultima posicao preenchida do vetor.
//      Esta função deve ir lendo os 4 sensores até que um comando de pare seja enviado
//
//      Para simular os sensores e os comandos de pare, use as funções já construídas
// nos ítens anteriores e em um looping contínuo até que um pedido de parada seja
// enviado pelo usuário.
//
//      Complete a função com a chamada das funções já criadas
int dirige(int *v,int maxv){
    int maxVetor = maxv;
    int *vetorMov = v;
    int posAtualVetor = 0;
    int dirigindo = 1;
    while(dirigindo){
        for (size_t i = 0; i < 4; i++)
        {
            int medida = leitor();
            medida = percent(medida,0,830);
            posAtualVetor = armazena(medida, posAtualVetor, vetorMov, maxv);
        }
        dirigindo = comando();
    }
    return posAtualVetor;
}
// O trecho abaixo irá utilizar as funções acima para ler os sensores e o movimento
// do robô e no final percorrer o vetor e mostrar o movimento a cada direção baseado
// na maior distância a cada movimento
void percorre(int *v,int percorrido){
    int *vetorMov = v;
    int maiorDir = 0;
    for(int i = 0; i< percorrido; i+=4){
        const char *direcionamento = direcao(&(vetorMov[i]),&maiorDir);
        printf("Movimentando para %s distancia = %i\n",direcionamento,maiorDir);
    }
}
int main(int argc, char** argv) {
    int maxVetor = 100;
    int vetorMov[maxVetor*4];
    int posAtualVet = 0;
    posAtualVet = dirige(vetorMov,maxVetor);
    percorre(vetorMov,posAtualVet);
    return 0;
}