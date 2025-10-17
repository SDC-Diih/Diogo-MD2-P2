#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

/*
    CABEÇALHO DO CÓDIGO
    ALUNO: DIOGO OLIVEIRA FERREIRA
    MATRICULA: 231011266
*/

// ===================================================================
// FUNÇÕES AUXILIARES
// ===================================================================

int mdc(int a, int b){ // Função para calcular o MDC entre dois numeros --> Algoritmo de Euclides
    int resto = a % b;
    if(resto == 0) return b;
    return( mdc(b, resto)) ;
}

int ehPrimo(int number) { // Função que verifica se número é PRIMO, me baseei no algoritmo mais eficiente da internet
    // Retorna 1 se for Primo, retorna 0 se NÃO for primo

    // Checa se o número é igual ou menor que 1
    if (number <= 1) {
        return 0;
    }

    // Checa todos os numeros de 2 até a raiz quadrada do número
    // Se um número não tem um divisor além de 1 até sua raiz quadrada, o número é primo.
    for (int i = 2; i * i <= number; i++) {
        if (number % i == 0) {
            return 0;
        }
    }
    return 1;
}

int CoPrimo(int a, int b){ // Retorna 1 quando são Co-Primos e 0 quando não são
    // Pequena correção para evitar mdc com b=0
    if (b == 0) return a == 1;
    if(mdc(a, b) == 1) return 1;
    else return 0;
}


int main(){
    printf("========================================================\n");
    printf("   IMPLEMENTAÇÃO DA RAZÃO DE EFICIÊNCIA DE UM NÚMERO");
    printf("\n========================================================\n");
    
    int n;
    printf("Insira um número entre 1 e 105: \n >");
    scanf("%d", &n);


    // ===================================================================
    //                  ACHAR FATORAÇÃO PRIMA DE N
    // ===================================================================

    printf("\n================================================\n");
    printf("\t ACHAR τ(N) e σ(N) \n\n");

    // Função τ(N) — conta o número total de divisores de N
    float t = 0; 
    // Função σ(N) — conta a soma dos divisores de N
    float o = 0; 

    int fatoracaoPrima[10]; // Array para armazenar produtos primos
    int contador = 0;

    if(ehPrimo(n)){
        // Se n for primo, so tem 2 divisores (1 e ele mesmo)
        t = 2;
        o = 1 + n;
        // Se n for primo so vai ter um fator primo, ele mesmo
        fatoracaoPrima[0] = n;
        contador++;
    }
    else{
        int n_copia = n;
        for(int i = 1; i <= n; i++){
            if(n % i == 0){ // Resto 0 --> Achou divisor
                printf("Divisor encontrado: %d ---> τ = %.0f\n", i, ++t);
                printf("Soma atualizada: σ = %.0f + %d = %d\n\n", o, i, (int)(o) + i);
                o += i; // Soma divisor
                if(ehPrimo(i)){ // Parte responsável por achar a fatoração prima de N
                    while(n_copia % i == 0){ // Repete até não dar mais
                    fatoracaoPrima[contador++] = i;
                    n_copia /= i;
                    }
                }
            }
        }
    }
    printf("\n================================================\n");

    
    printf("\n================================================\n");
    printf("\t FATORAÇÃO PRIMA DO NÚMERO N = %d: \n", n);
    int ultimo = fatoracaoPrima[0];
    int repete = 1;
    for(int i = 0; i < contador; i++){
        if(ultimo == fatoracaoPrima[i+1]){
            repete++;
        }
        else{
            printf("%d^%d \n", ultimo, repete);
            ultimo = fatoracaoPrima[i+1];
            repete = 1;
        }
    } 

    printf("\n================================================\n\n");
    printf(" Função τ (Total de divisores) = %.0f \n Função σ(Soma dos divisores) = %.0f \n", t, o);
    printf(" RAZÃO DE EFICIÊNCIA DO NÚMERO N = %.2f \n", t/o);
    
    return 0;
}