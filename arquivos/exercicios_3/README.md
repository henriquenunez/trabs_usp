#Exercícios dos dias 30/03 e 31/03 (2 exercícios) - data de entrega: 05/04 até as 23h59

Considere a organização híbrida de campos e registros. Foi visto em sala de aula
que os campos de tamanho fixo e de tamanho variável podem ser organizados de
duas formas: (a) primeiro todos os campos de tamanho fixo (no começo do
registro) e depois todos os campos de tamanho variável e (b) primeiro todos os
campos de tamanho variável e depois todos os campos de tamanho fixo (no final do
registro)

Considere: (i) registros de tamanho fixo de 30 bytes; (ii) dois campos de
tamanho fixo: estado (string de 2 bytes) e cep (string de 8 bytes); (iii) dois
campos de tamanho variável: nome cidade (string de tamanho variável) e nome país
(string de tamanho variável); (iv) o método indicador de tamanho para os campos
de tamanho variável; (v) um primeiro registro com valores: cep: 13333555,
cidade: Sao Carlos, estado: SP, país: Brasil; (vi) um segundo registro com
valores: cep: 17666999, cidade: Araraquara, estado: SP, país: Brasil.


Exercício 1. Insira os dois registros considerando a organização (a).

Exercício 2. Insira os dois registros considerando a organização (b).

## Respostas às dúvidas dos alunos:

- Considerando a organização (a), ao inserir o primeiro registro, o número de
bytes ultrapassa o limite. O que deve ser feito? Trunque os dados. Como não foi
especificada a forma de truncamento, escolha uma opção e explique.
