# MD2 Atividade
## Autor

* **Lucas Chaves Itacaramby** - 231026456

## Como Compilar e Executar

O código foi desenvolvido em C e pode ser compilado utilizando o gcc

```bash
# Para compilar o programa das questões
gcc -o programa.exe Qi.c

# Para executar
./programa.exe
```
Substituia o i em **Qi.c** pelo número da questão que deseja testar

---

## Respostas - Questão 4
(Respostas também presentes ao final do código do arquivo Q4.c)

### Previsão da saída com os valores dados pela questão

Com os valores: H: 7, G: 3, Zn: 11, x: 10, n1: 13

```
Insira H: 7
Insira G: 3
Insira Zn: 11
Insira x: 10
Insira n1: 13

Algorítmo de Euclides: 3 mod 11 = 3
Algorítmo de Euclides: 11 mod 3 = 2
Algorítmo de Euclides: 3 mod 2 = 1
Algorítmo de Euclides: 2 mod 1 = 0

Substituindo, temos que o inverso de 3 em 11 é 4.

Fazendo a multiplicação modular: 7 * 4 mod 11 = 6
 Sendo 4 o inverso de 3.
Valor final da congruência: 4
```

### Respostas para Verdadeiro ou Falso

* **(V)** O algoritmo de Euclides estendido é utilizado para calcular o inverso modular de um número.
* **(F)** Se mdc(G, Zn) ≠ 1, o programa ainda consegue encontrar o inverso de G em Zn.
* **(V)** A operação `(H * inverso) % Zn` representa a divisão modular de H por G.
* **(V)** Se n1 for primo, o código aplica o Pequeno Teorema de Fermat para simplificar o cálculo de a^x mod n1.
* **(F)** A função powMod implementa o cálculo de potência modular utilizando multiplicações diretas sem otimização.
* **(V)** Quando o resultado do inverso é negativo, o código ajusta o valor somando o módulo m0.
* **(V)** O cálculo de fi(n1) (função totiente de Euler) é utilizado apenas quando n1 não é primo.
