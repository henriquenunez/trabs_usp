# Prova 2 - 05/05/2020

Implemente em Assembly MIPS um programa que implemente a função strncmp( )
existente na linguagem C. Esta função tem a seguinte prototipação:
```
	int strncmp (char *s1, char *s2, int n)
```
e tem por objetivo comparar as duas strings s1 e s2,
considerando os primeiros n caracteres de ambas. A função retorna um inteiro
menor que, igual a ou maior que zero, se s1 é, respectivamente, menor que, igual
a ou maior que s2. O valor retornado corresponde à diferença do primeiro
caractere que for diferente, se existir tal diferença dentre os n primeiros
caracteres. Caso as strings sejam iguais, a diferença é zero. Na função
principal o programa deve ler do usuário as duas strings e o valor numérico e
imprimir o resultado da função strncmp.

A sua solução deve seguir a especificação, estar correta e o código seguir as
boas práticas de programação citadas em sala de aula, relativas à manipulação de
pilha, identação, nomes de rótulos, espaçamento entre linhas, comentários e
demais questões relativas à legibilidade e qualidade dos códigos.
