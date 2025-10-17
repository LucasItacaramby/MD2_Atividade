#include <stdio.h>
#include <stdlib.h>

/*
  Nome: Lucas Chaves Itacaramby
  Matrícula: 231026456
*/

/* ---------- Funções auxiliares ---------- */

// mdc: Algoritmo de Euclides com impressão passo-a-passo
// Mostra as divisões sucessivas r0 = q1*r1 + r2 ...
// Retorna mdc(a,b)
// Obs: Esta função imprime os passos sempre que é chamada (o pedido do usuário)
int mdc(int a, int b)
{
    int A = abs(a);
    int B = abs(b);
    printf("\nCalculando mdc(%d, %d) pelo Algoritmo de Euclides:\n", A, B);
    if (A == 0 && B == 0)
    {
        printf("Ambos zero: mdc indefinido (retornando 0)\n");
        return 0;
    }
    int step = 1;
    while (B != 0)
    {
        int q = A / B;
        int r = A % B;
        printf(" Passo %d: %d = %d * %d + %d  (q=%d, r=%d)\n", step++, A, B, q, r, q, r);
        A = B;
        B = r;
    }
    printf("Resultado: mdc = %d\n", A);
    return A;
}

// f para Pollard Rho (simples): f(x) = x^2 + 1 (mod n)
int f(int x, int n)
{
    long long res = ((long long)x * x + 1) % n;
    return (int)res;
}

// Pollard Rho simplificado: tenta encontrar um fator não-trivial de Ni
// Imprime x_i e os cálculos de mdc realizados (já que mdc imprime passos também)
int pollard(int Ni)
{
    int x[10000];
    x[0] = 2;
    int fatortrivial = 1;
    for (int i = 1; i < 9999; i++)
    {
        x[i] = f(x[i - 1], Ni);
        printf("x%d = %d (mod %d)\n", i, x[i], Ni);

        if (i % 2 == 0)
        {
            int iter = i / 2;
            int diff = abs(x[i] - x[iter]);
            printf(" Testando mdc(|x%d - x%d| = %d, %d)\n", i, iter, diff, Ni);
            fatortrivial = mdc(diff, Ni); // mdc já imprime passos
            printf("\n");
            if (fatortrivial > 1 && fatortrivial < Ni)
            {
                return fatortrivial;
            }
        }
    }
    return fatortrivial; // pode retornar 1 se não achar
}

// Algoritmo Estendido de Euclides (iterativo) com impressão em tabela
// Retorna mdc(a,b) e preenche *x e *y tais que a*x + b*y = mdc(a,b)
// Impressões detalham as colunas r, q, s, t em cada iteração
int euclides_estendido(int a, int b, int *x, int *y)
{
    int r0 = a, r1 = b;
    int s0 = 1, s1 = 0;
    int t0 = 0, t1 = 1;

    printf("\nAlgoritmo Estendido de Euclides para (%d, %d):\n", a, b);
    printf("Iter |   r0    |   r1    |  q  |   s0    |   s1    |   t0    |   t1\n");
    printf("-----------------------------------------------------------------\n");

    int iter = 0;
    while (r1 != 0)
    {
        int q = r0 / r1;
        int r2 = r0 - q * r1;
        int s2 = s0 - q * s1;
        int t2 = t0 - q * t1;
        printf("%4d | %7d | %7d | %3d | %7d | %7d | %7d | %7d\n",
               iter, r0, r1, q, s0, s1, t0, t1);

        // avança
        r0 = r1;
        r1 = r2;
        s0 = s1;
        s1 = s2;
        t0 = t1;
        t1 = t2;
        iter++;
    }
    // última linha: q não definido porque r1 == 0, mas mostramos resultado final
    printf("%4d | %7d | %7d |     | %7d | %7d | %7d | %7d\n",
           iter, r0, r1, s0, s1, t0, t1);

    // r0 é mdc agora; s0 e t0 tais que a*s0 + b*t0 = r0
    *x = s0;
    *y = t0;
    printf("Resultado: mdc = %d, x = %d, y = %d  (verifica: %d*%d + %d*%d = %d)\n",
           r0, *x, *y, a, *x, b, *y, a * (*x) + b * (*y));
    return r0;
}

// inverso_modular: usa euclides_estendido e imprime passo-a-passo da decisão
// Retorna D tal que D*E ≡ 1 (mod z) ou -1 se inverso não existir
int inverso_modular(int E, int z)
{
    printf("\nDeterminando inverso modular de E=%d mod z=%d\n", E, z);
    int x, y;
    int g = euclides_estendido(E, z, &x, &y); // já imprime passos
    if (g != 1)
    {
        printf("Não existe inverso modular porque mdc(%d, %d) = %d ≠ 1\n", E, z, g);
        return -1;
    }
    // x é tal que E*x + z*y = 1 -> x é inverso modulo z (talvez negativo)
    int D = (x % z + z) % z; // normaliza para [0, z-1]
    printf("Valor encontrado x = %d, inverso modular D = x mod z = %d\n", x, D);
    // validação final
    long long check = ((long long)D * E) % z;
    printf("Verificação: (%d * %d) mod %d = %lld\n", D, E, z, check);
    return D;
}

// Função auxiliar: teste simples para ver se o número é primo
int eh_primo(int n)
{
    if (n <= 1)
        return 0;
    for (int i = 2; i * i <= n; i++)
        if (n % i == 0)
            return 0;
    return 1;
}

// Exponenciação modular com impressão passo-a-passo
// Mantém a saída detalhada dos passos
long long exp_modular(long long base, long long exp, long long mod)
{
    long long resultado = 1;
    long long passo = 1;
    long long b = base % mod;

    printf("\nCálculo de %lld^%lld (mod %lld):\n", base, exp, mod);
    printf("Usando exponenciação binária:\n");

    while (exp > 0)
    {
        printf(" Passo %lld: base=%lld, expoente=%lld, resultado=%lld\n",
               passo++, b, exp, resultado);
        if (exp & 1)
        {
            resultado = (resultado * b) % mod;
            printf("   -> expoente ímpar: resultado = (resultado * base) mod %lld = %lld\n", mod, resultado);
        }
        b = (b * b) % mod;
        exp >>= 1;
    }
    printf("Resultado final: %lld\n", resultado);
    return resultado;
}

/* ---------- main: fluxo principal ---------- */
int main()
{
    // ==========================
    // Etapa 1 – Fatoração Interativa (Pollard Rho)
    // ==========================
    printf("\n--- ETAPA 1: Fatoração Interativa ---\n\n");

    int N1, N2;
    printf("Insira dois numeros compostos distintos entre 100 e 9999:\n");
    printf("Obs: cada Ni deve ser produto de primos distintos para que Pollard seja eficiente!\n");
    if (scanf("%d %d", &N1, &N2) != 2)
    {
        printf("Erro na leitura!\n");
        return 1;
    }
    if (N1 < 100 || N1 > 9999 || N2 < 100 || N2 > 9999 || N1 == N2)
    {
        printf("Numeros invalidos!\n");
        return 1;
    }

    // Aplicamos Pollard Rho para fatorar N1 e N2
    // manter simples e imprimir iteracoes para fácil entendimento
    int p = pollard(N1);
    if (p <= 1 || p == N1)
    {
        printf("Aviso: Pollard nao encontrou fator nao-trivial para N1 (%d)! p=%d\n", N1, p);
        printf("Encerrando (fatoracao falhou)\n");
        return 0;
    }
    else
    {
        printf("Fator nao trivial p encontrado: %d\n\n", p);
    }

    int q = pollard(N2);
    if (q <= 1 || q == N2)
    {
        printf("Aviso: Pollard nao encontrou fator nao-trivial para N2 (%d)! q=%d\n", N2, q);
        printf("Encerrando (fatoracao falhou)\n");
        return 0;
    }
    else
    {
        printf("Fator nao trivial q encontrado: %d\n\n", q);
    }

    // ==========================
    // Etapa 2 – Geração das Chaves RSA
    // ==========================
    printf("\n--- ETAPA 2: Geracao das Chaves RSA ---\n\n");
    printf("Decisao: usar n = p * q e z = (p-1)*(q-1) (totiente de Euler)\n");
    printf("p = %d, q = %d\n", p, q);

    int n = p * q;
    printf("Modulo n = p * q = %d\n", n);

    int z = (p - 1) * (q - 1);
    printf("Totiente z = (p-1)*(q-1) = %d\n", z);

    // Escolha do expoente publico e: procura-se e tal que 1 < e < n e mdc(e,z) = 1
    int e = 2;
    printf("Procurando expoente publico e (1 < e < n e mdc(e,z)=1)...\n");
    for (e = 2; e < n; e++)
    {
        if (mdc(e, z) == 1)
        { // função mdc imprime passos
            printf("Escolhido e = %d\n", e);
            break;
        }
    }

    if (e >= n)
    {
        printf("Nao foi possivel encontrar expoente publico e adequadamente!\n");
        return 1;
    }

    // Calculo do expoente privado D (inverso modular de e modulo z)
    int D = inverso_modular(e, z); // imprime tabela do estendido e verificação
    if (D == -1)
    {
        printf("Nao foi possivel determinar expoente privado D!\n");
        return 1;
    }

    printf("Chave publica: (n=%d, e=%d)\n", n, e);
    printf("Chave privada: (n=%d, D=%d)\n", n, D);

    // ==========================
    // Etapa 3 – Codificacao e Decodificacao
    // ==========================
    printf("\n--- ETAPA 3: Codificacao (Criptografia) e Decodificacao ---\n\n");

    // Entrada da mensagem (somente maiusculas e espaco)
    char mensagem[200];
    printf("Digite a mensagem (letras maiusculas): ");
    scanf(" %[^\n]", mensagem);

    // Pré-codificação: A=11, B=12, ..., Z=36, espaço=00
    int blocos[200];
    int tamanho = 0;
    for (int i = 0; mensagem[i] != '\0'; i++)
    {
        if (mensagem[i] == ' ')
            blocos[tamanho++] = 0; // 00
        else
        {
            // assume entrada valida (A..Z). Caso contrario, ajustaria/ignorar.
            blocos[tamanho++] = (mensagem[i] - 'A' + 11);
        }
    }

    printf("\nMensagem original: %s\n", mensagem);
    printf("Pre-codificacao (blocos numericos): ");
    for (int i = 0; i < tamanho; i++)
        printf("%02d ", blocos[i]);
    printf("\n");

    // Codificacao (criptografia): C = M^e mod n
    long long cifrado[200];
    printf("\n--- CODIFICACAO ---\n");
    for (int i = 0; i < tamanho; i++)
    {
        long long M = blocos[i];
        long long exp_reduzido = e;

        // Seleciona automaticamente qual teorema usar para reduzir expoente:
        if (eh_primo(n))
        {
            // Pequeno Teorema de Fermat
            printf("\nBloco %d: M=%02lld -> n é primo, aplicando Pequeno Teorema de Fermat\n", i + 1, M);
            exp_reduzido = e % (n - 1);
            printf(" e reduzido = e mod (n-1) = %lld\n", exp_reduzido);
        }
        else if (mdc(M, n) == 1)
        {
            // Teorema de Euler
            printf("\nBloco %d: M=%02lld -> mdc(M,n)=1, aplicando Teorema de Euler\n", i + 1, M);
            exp_reduzido = e % z;
            printf(" e reduzido = e mod phi(n) = %lld\n", exp_reduzido);
        }
        else
        {
            // Divisao Euclidiana (nenhuma redução teórica aplicavel)
            printf("\nBloco %d: M=%02lld -> aplicando Teorema da Divisao Euclidiana (sem reducao teorica)\n", i + 1, M);
            exp_reduzido = e;
        }

        printf("Executando exponenciacao modular para cifrar o bloco %d:\n", i + 1);
        cifrado[i] = exp_modular(M, exp_reduzido, n);
        printf("Bloco %d cifrado -> C = %lld\n", i + 1, cifrado[i]);
    }

    // Decodificacao (descriptografia): M = C^D mod n
    printf("\n--- DECODIFICACAO ---\n");
    long long decifrado[200];
    for (int i = 0; i < tamanho; i++)
    {
        long long C = cifrado[i];
        long long exp_reduzido = D;

        // Seleção dos teoremas para reduzir D ao calcular M = C^D mod n
        if (eh_primo(n))
        {
            printf("\nBloco %d: C=%lld -> n é primo, aplicando Pequeno Teorema de Fermat\n", i + 1, C);
            exp_reduzido = D % (n - 1);
            printf(" D reduzido = D mod (n-1) = %lld\n", exp_reduzido);
        }
        else if (mdc(C, n) == 1)
        {
            printf("\nBloco %d: C=%lld -> mdc(C,n)=1, aplicando Teorema de Euler\n", i + 1, C);
            exp_reduzido = D % z;
            printf(" D reduzido = D mod phi(n) = %lld\n", exp_reduzido);
        }
        else
        {
            printf("\nBloco %d: C=%lld -> aplicando Divisao Euclidiana (sem reducao teorica)\n", i + 1, C);
            exp_reduzido = D;
        }

        printf("Executando exponenciacao modular para decifrar o bloco %d:\n", i + 1);
        decifrado[i] = exp_modular(C, exp_reduzido, n);
        printf("Bloco %d decifrado -> M = %lld\n", i + 1, decifrado[i]);
    }

    // Resumo final: exibir mensagens originais, cifradas e decifradas (blocos e texto)
    printf("\n==============================\n");
    printf("        RESUMO FINAL\n");
    printf("==============================\n");

    // Mensagem original
    printf("\nMensagem original (texto): %s\n", mensagem);
    printf("Mensagem original (blocos): ");
    for (int i = 0; i < tamanho; i++)
        printf("%02d ", blocos[i]);
    printf("\n");

    // Mensagem criptografada
    printf("\nMensagem criptografada (blocos): ");
    for (int i = 0; i < tamanho; i++)
        printf("%lld ", cifrado[i]);
    printf("\nMensagem criptografada (texto simulado): ");
    // Como os blocos cifrados nao correspondem diretamente a letras da tabela,
    // mostra uma representacao simulada (apenas para visualizacao)
    for (int i = 0; i < tamanho; i++)
    {
        printf("%c", (char)((cifrado[i] % 26) + 'A'));
    }
    printf("\n");

    // Mensagem descriptografada
    printf("\nMensagem descriptografada (blocos): ");
    for (int i = 0; i < tamanho; i++)
        printf("%lld ", decifrado[i]);
    printf("\nMensagem descriptografada (texto): ");
    for (int i = 0; i < tamanho; i++)
    {
        if (decifrado[i] == 0)
            printf(" ");
        else
            printf("%c", (char)(decifrado[i] - 11 + 'A'));
    }
    printf("\n");

    return 0;
}