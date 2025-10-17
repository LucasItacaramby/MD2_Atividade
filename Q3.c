#include <stdio.h>

/*
  Nome: Lucas Chaves Itacaramby
  Matrícula: 231026456
*/

// struct para armazenar um fator primo e seu expoente
typedef struct
{
    int primo;
    int expoente;
} Fator;

/* ---------- Funções auxiliares ---------- */

// Função para fatorar N em seus fatores primos (Trial Division)
int fatoracao_prima(int N, Fator fatores[])
{
    int count = 0;
    int expoente;

    printf("\n--- Etapa 1: Fatoracao Prima ---\n");

    // Trata o fator 2 separadamente
    expoente = 0;
    while (N % 2 == 0)
    {
        N /= 2;
        expoente++;
    }
    if (expoente > 0)
    {
        fatores[count].primo = 2;
        fatores[count].expoente = expoente;
        printf("Fator encontrado: 2^%d\n", expoente);
        count++;
    }

    // Trata fatores ímpares
    for (int p = 3; p * p <= N; p += 2)
    {
        expoente = 0;
        while (N % p == 0)
        {
            N /= p;
            expoente++;
        }
        if (expoente > 0)
        {
            fatores[count].primo = p;
            fatores[count].expoente = expoente;
            printf("Fator encontrado: %d^%d\n", p, expoente);
            count++;
        }
    }

    // Se sobrar um número > 1, ele é primo
    if (N > 1)
    {
        fatores[count].primo = N;
        fatores[count].expoente = 1;
        printf("Fator encontrado: %d^1\n", N);
        count++;
    }

    return count;
}

// Função auxiliar para calcular p^k
long long potencia_int(int base, int expoente)
{
    long long resultado = 1;
    for (int i = 0; i < expoente; i++)
    {
        resultado *= base;
    }
    return resultado;
}

// Calcula τ(N) = produto dos (ai + 1)
long long calcular_tau(Fator fatores[], int qtd)
{
    double tau = 1;

    printf("\n--- Etapa 2: Calculo de τ(N) ---\n");
    printf("Formula: τ(N) = (a1+1)*(a2+1)*...(ak+1)\n");

    for (int i = 0; i < qtd; i++)
    {
        int termo = fatores[i].expoente + 1;
        printf("→ Fator %d: (%d + 1) = %d\n", fatores[i].primo, fatores[i].expoente, termo);
        tau *= termo;
        printf("   Produto parcial de τ: %.2f\n", tau);
    }

    printf("τ(N) final = %.2f\n", tau);
    return tau;
}

// Calcula σ(N) = produto de ((p^(a+1) - 1) / (p - 1))
double calcular_sigma(Fator fatores[], int qtd)
{
    double sigma = 1.0;

    printf("\n--- Etapa 3: Calculo de σ(N) ---\n");
    printf("Formula: σ(N) = ∏ [(p^(a+1) - 1) / (p - 1)]\n");

    for (int i = 0; i < qtd; i++)
    {
        int p = fatores[i].primo;
        int a = fatores[i].expoente;

        long long pot = potencia_int(p, a + 1);
        double numerador = pot - 1;
        double denominador = p - 1;
        double termo = numerador / denominador;

        printf("→ Para fator %d^%d:\n", p, a);
        printf("   (%d^(%d+1) - 1) / (%d - 1) = (%lld - 1) / %d = %.2f\n",
               p, a, p, pot, p - 1, termo);

        sigma *= termo;
        printf("   Produto parcial de σ: %.2f\n", sigma);
    }

    printf("σ(N) final = %.2f\n", sigma);
    return sigma;
}

/* ---------- main: fluxo principal ---------- */
int main()
{
    int N;
    printf("Digite um inteiro N (1 ≤ N ≤ 105): ");
    scanf("%d", &N);

    if (N < 1 || N > 105)
    {
        printf("Valor inválido!\n");
        return 0;
    }

    Fator fatores[20];
    int qtd = fatoracao_prima(N, fatores);

    // Calcula τ(N) e σ(N)
    double tau = calcular_tau(fatores, qtd);
    double sigma = calcular_sigma(fatores, qtd);

    // Calcula a razão de eficiência(N)
    double razao = sigma / tau;

    // Exibe resultado final
    printf("\n--- Etapa 4: Resultado Final ---\n");
    printf("τ(N) = %.2f\n", tau);
    printf("σ(N) = %.2f\n", sigma);
    printf("Razao de Eficiência(N) = σ(N) / τ(N) = %.2f\n", razao);

    return 0;
}