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

// ===================================================================
// FUNÇÕES DE CRIPTOGRAFIA PRINCIPAIS
// ===================================================================

int algoritmoEstendidoEuclides(int a, int b) {
    printf("\n\t---------- INICIO DO ALGORITMO ESTENDIDO DE EUCLIDES ----------\n");
    
    // Variaveis de copia declaradas para o print no final
    int a_original = a;
    int b_original = b;

    // Método Computacional do Algoritmo Estendido Euclidiano
    int x_antigo = 1, y_antigo = 0;
    int x_atual = 0, y_atual = 1;

    printf("\tObjetivo: Encontrar o inverso de %d (mod %d)\n", b, a);
    printf("\tObjetivo: Encontrar 'y' em %dx + %dy = 1\n", a, b);

    while (b != 0) {
        int quociente = a / b;
        int resto = a % b;

        // Atualiza 'x' e 'y' que multiplicam 'a' e 'b' 
        int x_proximo = x_antigo - quociente * x_atual;
        int y_proximo = y_antigo - quociente * y_atual;

        // Logica do MDC
        a = b;
        b = resto;

        // Atualiza as variaveis para o prox loop
        x_antigo = x_atual;
        y_antigo = y_atual;
        x_atual = x_proximo;
        y_atual = y_proximo;
    }

    if (a != 1) { // 'a' recebe o valor do MDC apos o loop
        printf("\tERRO: O inverso de %d mod %d não existe, pois o mdc não é 1.\n", b_original, a_original);
        printf("\t---------- FINAL DO ALGORITMO ESTENDIDO DE EUCLIDES ----------\n");
        return 0;
    }

    printf("\tResultado - Equação final: %d * (%d) + %d * (%d) = 1\n", a_original, x_antigo, b_original, y_antigo);

    int inverso = (y_antigo % a_original + a_original) % a_original; // Inverso pode ser negativo, por isso a operação
    printf("\tO inverso de %d (mod %d) é: %d\n", b_original, a_original, inverso);
    printf("\t---------- FINAL DO ALGORITMO ESTENDIDO DE EUCLIDES ----------\n");
    return inverso;
}

int metodoPollard(int semente, int n){
    printf("\n---------- INICIO DO METODO DE POLLARD RHO para N = %d ----------\n", n);

    if (n % 2 == 0) return 2; // Caso o numero dado seja par

    int x1 = semente;
    int x2 = semente;
    int p = 1;
    int contador = 1;

    // X1 representa o Xk do metodo
    x1 = ((x1 * x1 + 1) % n);

    // X2 representa o X2k do metodo
    x2 = ((x2 * x2 + 1) % n);
    x2 = ((x2 * x2 + 1) % n);
    
    p = mdc(abs(x2 - x1), n);
    printf("\tIteração %d: X1=%d, X2=%d, Fator p=%d\n", contador++, x1, x2, p);

    while(p == 1){ // Repete a etapa de operações até encontra o 'p'
        x1 = ((x1 * x1 + 1) % n);
        x2 = ((x2 * x2 + 1) % n);
        x2 = ((x2 * x2 + 1) % n);

        p = mdc(abs(x2 - x1), n);
        printf("\tIteração %d: X1=%d, X2=%d, Fator p=%d\n", contador++, x1, x2, p);
    };

    printf("--- Fator Não Trivial Encontrado na %dª iteração: p = %d ---\n", contador-1, p);
    printf("---------- FINAL DO METODO DE POLLARD RHO ----------\n");
    return p;
}

int solCongruencia(int base, int expoente, int n, int z){
    printf("\n\t--- Calculando (%d^%d) mod %d ---\n", base, expoente, n);
    
    int expoente_reduzido = expoente;
    
    // Etapa de Redução do Expoente
    printf("\t[Análise para redução do expoente]\n");
    
    // Pequeno Teorema de Fermat, se n for primo;
    if(ehPrimo(n)){
        printf("\tDECISÃO: O módulo 'n' (%d) é primo. Aplicando Pequeno Teorema de Fermat.\n", n);
        expoente_reduzido = expoente % (n - 1);
        if (expoente_reduzido == 0) expoente_reduzido = n - 1; // a^(n-1) mod n = 1
        printf("\t\tExpoente original: %d -> Reduzido para: %d (resto de %d / %d)\n", expoente, expoente_reduzido, expoente, n-1);
    }

    // Teorema de Euler, se mdc(M,n)=1;
    else if(CoPrimo(base, n)){
        printf("\tDECISÃO: A base (%d) e o módulo 'n' (%d) são coprimos. Aplicando Teorema de Euler.\n", base, n);
        expoente_reduzido = expoente % z;
        if (expoente_reduzido == 0) expoente_reduzido = z; // a^z mod n = 1
        printf("\t\tExpoente original: %d -> Reduzido para: %d (resto de %d / %d)\n", expoente, expoente_reduzido, expoente, z);
    }

    // No caso de não for nenhum dos dois outros Teoremas -> Fazer o da Divisão Euclediana
    // Teorema da Divisão Euclidiana
    else {
        printf("\tDECISÃO: Base e módulo não são coprimos. Aplicando redução via Divisão Euclidiana.\n");
        expoente_reduzido = expoente % z;
        if (expoente_reduzido == 0) expoente_reduzido = z;
        printf("\t\tExpoente original: %d -> Reduzido para: %d (resto de %d / %d)\n", expoente, expoente_reduzido, expoente, z);
    }

    printf("\t[Cálculo da exponenciação modular]\n");
    int resultado = 1;

    // Loop responsavel por calcular a resposta com exponenciacao modular
    for(int i = 0; i < expoente_reduzido; i++){
        resultado = (resultado * base) % n;
    }
    printf("\t\tResultado de (%d^%d) mod %d é: %d\n", base, expoente_reduzido, n, resultado);
    return resultado;
}

// ===================================================================
// FUNÇÃO MAIN
// ===================================================================

int main(){
    printf("========================================================\n");
    printf("            IMPLEMENTAÇÃO DO ALGORITMO RSA\n");
    printf("========================================================\n");
    
    // ===================================================================
    // Etapa 1: Fatoração Interativa (Método ρ de Pollard)
    // ===================================================================
    printf("\n===== ETAPA 1: FATORAÇÃO COM POLLARD RHO =====\n");

    int n1 = 0;
    int n2 = 0;
    // Solicita dois números compostos (N1 e N2) --> 100 <= N <= 9999
    while(n1 > 9999 || n1 < 100 || n2 > 9999 || n2 < 100 || ehPrimo(n1) || ehPrimo(n2)){
        printf("Insira dois números COMPOSTOS por DOIS PRIMOS distintos (entre 100 e 9999):\n");
        printf("\n\t Eu recomendo esses pares : (143, 221) e (187, 323) \n");
        scanf("%d%d", &n1, &n2);
    }

    int semente = 2; // X0 

    // Calculo do 'p' e 'q' com n1 e n2
    int p = metodoPollard(semente, n1);
    int q = metodoPollard(semente, n2);

    printf("\n[RESULTADO DA ETAPA 1]\n");
    printf("Fator 'p' de N1 (%d): %d\n", n1, p);
    printf("Fator 'q' de N2 (%d): %d\n", n2, q);

    // ===================================================================
    // Etapa 2: -Geração das Chaves RSA
    // ===================================================================
    printf("\n===== ETAPA 2: GERAÇÃO DAS CHAVES =====\n");
    
    // Cálculo do n = p × q
    int n = p * q;
    printf("\n [PASSO 1] Cálculo do Módulo (n):\n");
    printf("\t n = p * q = %d * %d = %d\n", p, q, n);

    // Totiente de Euler: z(n) = (p−1) x (q−1)
    int z = (p - 1) * (q - 1);
    printf("\n [PASSO 2] Cálculo da Função Totiente (z):\n");
    printf("\t z = (p-1) * (q-1) = %d * %d = %d\n", p-1, q-1, z);

    // Escolha do expoente público: Escolha o menor E >1 e E< n tal que mdc (E , z(n))=1
    int e = 2;
    printf("\n [PASSO 3] Encontrando o Expoente Público (e):\n");
    for(e = 2; e < z; e++){
        if(CoPrimo(e, z)){
            printf("\t Encontrado menor 'e' = %d (pois mdc(%d, %d) = 1)\n", e, e, z);
            break; 
        }
    }

    // Cálculo do expoente privado: D × E ≡ 1 mod z
    printf("\n[PASSO 4] Encontrando o Expoente Privado (d):\n");
    int d = algoritmoEstendidoEuclides(z, e); // Retorna 0 se tiver erro

    if(d == 0){ // Se d == 0, algoritmoEstendidoEuclides falhou
        printf("\nERRO: Não foi possível calcular 'd'. Terminando programa.\n");
        return 0;
    }

    printf("\n--------------------------------------------------------\n");
    printf("Chave Pública (e): (%d)\n", e);
    printf("Chave Privada (d): (%d)\n", d);
    printf("--------------------------------------------------------\n");

    // ===================================================================
    // Etapa 3 - Codificação (Criptografia) e Decodificação (Descriptografia)
    // ===================================================================
    printf("\n===== ETAPA 3: CRIPTOGRAFIA E DESCRIPTOGRAFIA =====\n");
    char palavra[101];
    printf("Insira uma palavra apenas com MAIUSCULAS e sem espacos :\n");
    scanf("%100s", palavra);
    
    int len = strlen(palavra); // Para saber até onde checar no loop mais a frente e otimiza memoria no prox array
    int *palavra_criptografada = malloc(len * sizeof(int));
    
    // --- Codificação a partir das letras na tabela ---
    printf("\n--- FASE DE CRIPTOGRAFIA ---\n");
    for(int i = 0; i < len; i++){ 
        // Pré – Codificação: A = 11, B= 12, …, Z= 36
        int m = palavra[i] - 54; // 'A'(65) - 54 = 11 --> Faz o ajuste para A = 11, B = 12, ... , Z = 36
        
        printf("\n------- Criptografando letra '%c' (bloco M = %d) -------\n", palavra[i], m);
        
        // Acha o C ≡ M^E mod N
        palavra_criptografada[i] = solCongruencia(m, e, n, z);
        printf("------- Letra '%c' criptografada como: C = %d -------\n", palavra[i], palavra_criptografada[i]);
    }
    
    printf("\n--------------------------------------------------------\n");
    printf("MENSAGEM CRIPTOGRAFADA (sequência de números):\n");
    for(int i = 0; i < len; i++) {
        printf("%d ", palavra_criptografada[i]);
    }
    printf("\n--------------------------------------------------------\n");

    // --- Decodificação ---
    printf("\n--- FASE DE DESCRIPTOGRAFIA ---\n");

    // Array para armazenar a palavra que vai ser descriptografada
    char *palavra_descriptografada = malloc((len + 1) * sizeof(char));
    for(int i = 0; i < len; i++){ 
        int c = palavra_criptografada[i];
        
        printf("\n------- Descriptografando bloco C = %d -------\n", c);
        
        // Acha o M ≡ C^D mod N
        int m_decifrado = solCongruencia(c, d, n, z);
        
        // Converte o código encontrado em texto
        palavra_descriptografada[i] = (char)(m_decifrado + 54); // Armazena letra descriptografada no array -> + 54 para manter a logica da professora
        printf("------- Bloco C = %d descriptografado como: M = %d ('%c') -------\n", c, m_decifrado, palavra_descriptografada[i]);
    }
    palavra_descriptografada[len] = '\0'; // Termina a string

    printf("\n--------------------------------------------------------\n");
    printf("MENSAGEM FINAL DESCRIPTOGRAFADA: %s\n", palavra_descriptografada);
    printf("--------------------------------------------------------\n");

    // Compara palavra inserida do inicio com o array que foi descriptografado para ver se deu certo
    if (strcmp(palavra, palavra_descriptografada) == 0) { // 0 no 'strcmp' é sinal de sucesso, diferente das implementações que eu mesmo fiz
        printf("\nSUCESSO: A mensagem decriptografada é a mesma da original.\n");
    } else {
        printf("\nFALHA: A mensagem decriptografada NÃO é a mesma da original.\n");
    }

    return 0;
}