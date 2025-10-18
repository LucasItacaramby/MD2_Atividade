#include <stdio.h>

/*
  Nome: Lucas Chaves Itacaramby
  Matrícula: 231026456
*/

// Função para calcular o mcd pelo algoritmo de Euclides
int mdc(int a, int b)
{
    printf("\n--- Etapa 1: Cálculo do MDC ---\n");
    printf("  Calculando mdc(%d, %d):\n", a, b);
    int passo = 1;
    while (b != 0)
    {
        int resto = a % b;
        printf("    Passo %d: a = %d, b = %d, resto = %d\n", passo, a, b, resto);
        a = b;
        b = resto;
        passo++;
    }
    printf("    Resultado mdc = %d\n", a);
    return a;
}

// Função para calcular o mmc de dois números
// Obs. usamos (a * b) / mdc para obter o mmc
int mmc(int a, int b)
{
    int g = mdc(a, b);           // calcula e imprime passos do mdc
    int resultado = (a * b) / g; // mmc = (a * b) / mdc(a,b)
    printf("\n--- Etapa 2: Cálculo do MMC ---\n");
    printf("  mmc(%d, %d) = (%d * %d) / %d = %d\n", a, b, a, b, g, resultado);
    return resultado;
}

int main()
{
    int N;
    int ciclos[10]; // N <= 10
    int i;

    // Entrada de dados
    printf("Digite o numero de chaves (1 ≤ N ≤ 10): ");
    if (scanf("%d", &N) != 1)
    {
        printf("Erro na leitura do numero de chaves!\n");
        return 0;
    }

    if (N < 1 || N > 10)
    {
        printf("Numero de chaves inválido!\n");
        return 0;
    }

    printf("Digite os %d ciclos das chaves (2 ≤ Ci ≤ 20): ", N);
    for (i = 0; i < N; i++)
    {
        if (scanf("%d", &ciclos[i]) != 1)
        {
            printf("Erro na leitura dos ciclos!\n");
            return 0;
        }
        if (ciclos[i] < 2 || ciclos[i] > 20)
        {
            printf("Ciclo inválido, tente números entre 2 e 20!\n");
            return 0;
        }
    }

    // Calcula o MMC de todos os ciclos
    int sincronizacao = ciclos[0];

    for (i = 1; i < N; i++)
    {
        sincronizacao = mmc(sincronizacao, ciclos[i]);
    }

    // Verifica se o ano sincronizado está dentro do limite
    printf("\n--- Etapa 3: Resultado Final ---\n");
    printf("Resultado final: MMC de todos os ciclos = %d\n", sincronizacao);
    if (sincronizacao > 50)
    {
        printf("Não é possivel sincronizar todas as chaves dentro de 50 anos\n");
    }
    else if (sincronizacao <= 0)
    {
        // Proteção extra
        printf("Não foi possivel determinar um ano válido de sincronização\n");
    }
    else
    {
        printf("Primeiro ano de sincronização dentro do limite de 50 anos: %d\n", sincronizacao);
    }

    return 0;
}