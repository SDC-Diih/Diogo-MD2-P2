#include <stdio.h>

#ifdef WIN32
#include <windows.h>
#endif

// Função para calcular o máximo divisor comum (MDC) com exibição dos passos
int mdcComPassos(int a, int b) {
    int resto;
    while (b != 0) { // [1] Condição de parada do Algoritmo de Euclides --> 'b' que representa resto, deve parar quando resto == 0
        resto = a % b;
        printf("Algoritmo de Euclides: %d mod %d = %d\n", a, b, resto);
        a = b;
        b = resto; // [2] Atualização do valor de 'b', vira o novo resto
    }
    return a;
}

// Função para calcular o inverso modular usando o Algoritmo Estendido de Euclides
int inversoModular(int a, int m) {
    int m0 = m, t, q;
    int x0 = 0, x1 = 1;
    int A = a, B = m;

    // [3] Precisa checar se o mdc(a, m) == 1, para o inversoModular existir 
    if(mdcComPassos(a, m) != 1) return 0; // Coloquei o return 0 como código de erro

    while (m != 0) {
        q = a / m;
        t = m;
        m = a % m;
        a = t;

        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }

    if (x1 < 0) {
        x1 += m0; // [4] Garante que o resultado seja positivo, pois o inverso não pode ser negativo
    }

    printf("\nSubstituindo, temos que o inverso de %d em %d é %d.\n", A, B, x1);
    return x1;
}

int powMod(int base, int exp, int mod) {
    long long res = 1;
    long long b = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) { // [5] Checa se o expoente é impar, pois se não for, o shift lógico a direita é mais eficiente
            res = (res * b) % mod;
        }
        b = (b * b) % mod;
        exp >>= 1; // Shift logico de bit a direita --> Mesma coisa que dividir por dois
    }
    return (int)res;
}

int main() {
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
    #endif

    int H, G, Zn, X, n1;

    printf("Insira H: ");
    scanf("%d", &H);
    printf("Insira G: ");
    scanf("%d", &G);
    printf("Insira Zn: ");
    scanf("%d", &Zn);
    printf("Insira X: ");
    scanf("%d", &X);
    printf("Insira n1: ");
    scanf("%d", &n1);

    int inverso = inversoModular(G, Zn); // [6] Função do inverso modular
    int a = (H * inverso) % Zn;

    printf("Fazendo a multiplicação modular: %d * %d mod %d = %d\n", H, inverso, Zn, a);
    printf("Sendo %d o inverso de %d.\n", inverso, G);
    
    int resultado = powMod(a, X, n1); // [7] Função da exponenciação modular --> a^X mod n1
    printf("Valor final da congruência: %d\n", resultado);

    return 0;

    /* 
    A SAÍDA DOS VALORES
    H: 7, G: 3, Zn: 11, x: 10, n1:13

    Algoritmo de Euclides: 3 mod 11 = 3
    Algoritmo de Euclides: 11 mod 3 = 2
    Algoritmo de Euclides: 3 mod 2 = 1
    Algoritmo de Euclides: 2 mod 1 = 0

    Substituindo, temos que o inverso de 3 em 11 é 4.
    Fazendo a multiplicação modular: 7 * 4 mod 11 = 6
    Sendo 4 o inverso de 3.
    Valor final da congruência: 4
    */

    /*
    QUESTÕES VERDADEIRO OU FALSO

    ( V ) O algoritmo de Euclides estendido é utilizado para calcular o inverso modular de um número.

    ( F ) Se mdc(G, Zn) ≠ 1, o programa ainda consegue encontrar o inverso de G em Zn.
    
    ( V ) A operação (H * inverso) % Zn representa a divisão modular de H por G.

    ( F ) Se n1 for primo, o código aplica o Pequeno Teorema de Fermat para simplificar o cálculo de
    a^x mod n1.

    ( F ) A função powMod implementa o cálculo de potência modular utilizando multiplicações diretas
    sem otimização.

    ( V ) Quando o resultado do inverso é negativo, o código ajusta o valor somando o módulo m0.
    
    ( F ) O cálculo de fi(n1) (função totiente de Euler) é utilizado apenas quando n1 não é primo.
    */
}

