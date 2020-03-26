# Descrição

Seu amigo Monk gosta muito de informática, então seus professores deixaram que ele preparasse uma aula para seus colegas de turma. Antes de entrar na sala, Monk percebeu que não lembra o nome de todos da turma. Para evitar que esse esquecimento o atrapalhe, Monk quer que você o ajude. A forma de ajudá-lo é informando o nome do aluno a partir da posição onde está sentado na sala a partir da implementação de um algoritmo usando hash. Assim, Monk te pergunta qual o nome do colega sentado em uma posição e você responde rapidamente qual o nome.

# Entrada

A primeira linha da entrada é a quantidade N de colegas de Monk, em seguida, são N linhas com os nomes e as respectivas posições. Depois um novo inteiro é informado, representando a quantidade de consultas que serão feitas. Em seguida, as consultas em si, cada em uma linha.
Saída

Cada consulta retorna uma string que deve ser mostrada em uma nova linha.

# Restrições

Implemente uma tabela hash estática aberta (que utiliza lista encadeada).

1 < N <= 10^3

|nome| <= 25

0 < posição <= 10^5

# Exemplo

## Entrada

    5

    1 vasya

    2 petya

    3 kolya

    4 limak

    5 illya

    2

    1

    2

## Saída

    vasya

    petya

