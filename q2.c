#include <stdio.h>
#include <stdlib.h>

int mdc(int a, int b){ // Função para calcular o MDC entre dois numeros --> Algoritmo de Euclides
    int resto = a % b;
    if(resto == 0) return b;
    return( mdc(b, resto)) ;
}

int mmc(int x, int y){ // Calcula Menor Multiplo Comum entre dois números
    // mmc( x, y ) = (x * y) / mdc( x, y)
    return( (x * y) / mdc( x, y) );
}

int main(){

    int n;
    printf("\nInsira a quantidade de chaves a serem usadas (Entre 1 e 10) \n> ");
    scanf("%d", &n);

    int array_c[n];
    printf("Insira as %d chaves a serem usadas (Entre 2 e 20) \n> ", n);
    for(int i = 0; i < n; i++) scanf("%d", &array_c[i]);

    printf("================================================================\n \tINICIO DO ALGORITMO PARA CALCULAR O ANO\n");


    // Calculo o MMC entre todos os numeros sequencialmente --> Propriedade Associativa do MMC
    /*
    ano = num1
    ano = mmc(num1, num2)

    Na proxima iteração vou calcular:
    mmc = mmc(ano, num3) --> Porem ano agora = mmc(num1, num2)  --> mmc = mmc(mmc(num1, num2), num3)

    Isso, indiretamente calcula o MMC entre todos os numeros do array, rodando o código vai ser mostrado sequencialmente o calculo
    */

    int ano = array_c[0];
    for(int i = 0; i < n-1; i++){
        printf("MMC de %d e %d = %d \n", ano, array_c[i+1], mmc(ano, array_c[i+1]));
        ano = mmc(ano, array_c[i+1]);
    }

    printf("================================================================\n");
    if(ano > 0 && ano < 51){
        printf("SUCESSO: O Ano em que as chaves podem usadas é: %d\n", ano);
    }
    else{
        printf("FALHA: As chaves não podem ser utilizadas pois o limite ultrapassou 50 anos \n");
    }
    printf("================================================================\n");

    return 0;
}