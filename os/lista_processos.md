# Listão de processos (9/11/2020)

## Henrique Hiram Libutti Núñez - 11275300 

1. Evoluções de hardware: aumento de memória, aumento de velocidade de
processamento, e várias opções de entrada e saída. Evoluções de software: .

2. Gerenciar os recursos de um computador, entre os programas em execução;
fornecer uma abstração do hardware para os programas.

3. Programa é um arquivo contendo intruções necessárias para realizar uma
determinada tarefa. Processo é a instância de um programa, no contexto do
sistema operacional. Thread é uma parte do programa que pode ser executada
assincronamente, o que permite que o processo não fique bloqueado em operações
de I/O.

4. As *kernel-threads* são contextos que o escalonador gerencia, e são
completamente dependentes da implementação do sistema operacional. As
*user-threads* são abstrações das *kernel-threads*, disponíveis nas linguagens
de programação para permitir o uso de *threads* nos programas.

5. Hierarquicamente, as threads existem no contexto de um processo. O processo
possui um espaço de endereçamento próprio, que é formado na criação dele. As
threads compartilham o mesmo espaço de endereçamento (portanto as race
conditions) e isso permite que sejam mais leves.

6. Os possíveis estados são: *Ready*, *Blocked* e *Running*. O estado *Ready* é
assumido quando o processo não está executando, mas terminou suas operações de
I/O e pode voltar a executar; O estado *Blocked* é assumido quando o processo
incia uma operação de I/O, que depende da espera de módulos mais lentos e de
tempo indeterminado, como leitura e escrita no disco, operações de rede e
interação com o usuário. O estado *Running* é quando realmente as instruções são
avançadas no programa, e os cálculos realizados pela CPU ocorrem.

7. Processos CPU-bound são processos que dependem fortemente da execução da CPU,
e seu tempo de término depende basicamente da velocidade do processador.
Processos I/O-bound são processos que executam muitas operações de entrada e
saída. Se existirem muitos processos CPU-bound, eles terão de compartilhar o
processador, e vai depender do número de núcleos e a velocidade da execução o
tempo e a resposta dos programas. Se existirem muitos processos I/O bound, eles
deverão ficar numa fila e aguardar a operações dos outros processos, o que pode
desacelerar a execução.

8. Chamadas de sistema são parte de uma API fornecida pelo sistema operacional.
Essas chamadas de sistema basicamente são abstrações para operações de baixo
nível que por segurança e conveniência devem ser executados pelo SO. Os passos
para uma chama de sistema são, de forma simples: o processo insere parâmetros
das syscalls em registradores, uma interrupção é lançada, e nesse momento o SO
assume o controle. A partir desse momento, ele entra em modo kernel, lê os
argumentos e analisa uma tabela de funções para determinar qual endereço de
função.

9. A resposta correta é a c, pois o microkernel implementa funcionalidades muito
primárias e básicas, sendo um sistema mais conciso. Isso permite que os serviços
sejam reconfigurados facilmente, e o processo de desenvolvimento seja mais
simples.

10. Sistemas operacionais em camadas permitem uma separação das partes
importantes, e evita que falhas nas camadas superiores atinjam sistemas mais
críticos inferiores, bem como a segurança.

11. O escalonador realiza uma preempção nos processos em execução, e insere
outros processos em seu lugar. Isso permite que processos que tenham um custo
menor de tempo consigam ser terminados, ao passo de que a execução de processos
mais lentos continua.

12. *Round robin*: Permite que os processos permaneçam um determinado tempo em
execução na CPU, chamado de *quantum*, e à medida que novos processos entram em
execução, são inseridos numa fila circular; Prioridades: Determina uma
prioridade para os processos, e estes são executados conforme a prioridade,
sendo que processos com prioridade mais alta são colocados no lugar dos
processos em execuçaõ atualmente, e logo após processos com prioridade normal
são chamados em execução; Múltiplas filas: São estabelecidas múltiplas filas,
cada uma para um determinado tipo de prioridade, e internamente são utilizadas
algoritmos como *round robin*.

13. Se o *quantum* for muito pequeno, há muitos chaveamentos de processos, algo
que pode se tornar um problema pois a troca de contexto é lenta. Se o *quantum*
for muito grande, a impressão de paralelismo de execução das aplicações perde-se
um pouco.

14. *Race condition* é quando duas thread acessam uma região crítica de memória,
sem um sincronizador, o que possibilita que preempção de uma thread modifique um
valor crítico, não acabe a execução, se uma outra thread alterar o valor, temos
um resultado indeterminístico. *Mutual Exclusion* é uma técnica de sincronização
de regiões críticas, permitindo que apenas uma thread acesse a região por vez,
evitando reace conditions.

15. As condições são basicamente:

- Não haver espera infinita;

- Previsões sobre tempo de execução serem desconsiderados;

- Os bloqueios devem acontecer apenas dentro de regiões críticas.

- Dados críticos não podem ser acessados simultaneamente.

16. Soluções com os algoritmos:

- Round robin:
A(4),B(8),C(11),D(15),E(19),A(23),B(27),D(29),E(33),A(37),E(40),A(42).

Tempo médio: 24s.

- SJF:
C(3),D(8),B(15),E(24),A(35).

Tempo médio: 17s.

- FIFO:
A(11),B(18),C(21),D(26),E(35).

Tempo médio: 22.2s.

17. Os processos com menor tempo de uso devem ser executados antes, ou seja, a
estratégia Shortest Job First deve ser usada. Mas, pensando em X como um valor
médio entre o menor e o maior tempo de processos, eu colocaria o processo com
valor X no meio da fila de execução, sendo esta portanto:
3, 5, X, 6, 9

18. a) Pois se um processo desabilita as interrupções, pode nunca mais
reativá-las, o que impede que o escalonador cause preempção nos processos e
assim mata o princípio de multiprogramação. c) . d) O mapeamento da memória é
algo crítico para o computador, processos não devem modificá-lo pois quem lida
com a virtualização da memória é o sistema operacional e os processos utilizam
as abstrações fornecidas por ele.

19. A sincronização é uma característica essencial da programação concorrente,
ou seja, deve ser utilizada sempre que usamos threads. A sincronização serve
para controlar o acesso a regiões críticas, ou seja, de escrita compartilhada
entre threads, e impedir que resultados incorretos e indeterminísticos
aconteçam.

20. Sleep e wakeup dormem e acordam uma determinada thread. Essas primitivas
resolvem o acesso à memória pois antes de uma thread entrar na região crítica,
ela pode utilizar essa primitiva nas threads concorrentes, e assim garantir que
apenas ela está acessando. Após o término da opração crítica, ela reativa as
outras threads.

21. Pois as interrupções devem ser gerenciadas exclusivamente pelo kernel, uma
vez que caso elas não sejam reativadas, o processo nunca vai ser interrompido, e
pode nunca terminar.

22. Semáforos são variáveis que se relacionam com a disponibilidade de regiões
críticas. Os semáforos podem ter seu valor aumentado ou diminuído,
preferencialmente de forma atômica, e caso o valor seja menor que um limite
estabelecido, uma thread entra em modo de espera. Ao liberar a região crítica, o
valor do semáforo é decrescido.

23. É possível utilizar um semáforo booleano para a implementação do monitor,
que irá gerenciar o acesso à região crítica das threads, adquirir e soltar a
trava.

24. Se:

- a) Caso o buffer estiver cheio, pode haver deadlock, pois o produtor terá
  pego a trava da regiã́o crítica, mas não poderá acessá-la, e o consumidor não
  conseguirá acessa por causa da trava.

- b) Não iria causar nenhuma implicação, mas impossibilitaria o consumidor
  operar caso haja preempção entre as duas chamadas.

- c) Se o buffer estiver vazio, o consumidor pode pegar a trava e não vai de
  fato acessar a região crítica, e o produtor não poderá produzir pela trava s,
  ou seja, deadlock.

25. Uma situação na vida real para exclusão mútua é a utilização de chaves para
banheiros. A pessoa que vai utilizar (thread) pega a chave (lock) para utilizar
o banheiro (região crítica), evitando assim problemas.

26. A espera ocupada é uma condição onde há uma constante checagem por um valor,
como por exemplo um laço esperando que uma variável seja verdadeira, antes de
começar a executar o código interno ao laço. Isso consome muita CPU por está sem
parar utilizando os recursos e não fazendo operações de I/O. É possível evitar
com as primitivas de sleep e wakeup. Não sei quando é aceitável.

27. Exclusão mútua de recursos, situação de *hold and wait*, não preempção de
processos e espera circular.

28. As possíveis estratégias são:

- Caso a ocorrência seja mínima, e as implicações não sejam grandes, é possível
  ignorar o problema.

- Detecção do problema, e sua correção. A detecção pode ser realizada por meio
  da construção de um grafo e uma das formas de recuperar o deadlock é a
  preempção.

- A alocação dinâmica de recursos prevê se a requisição pelo recurso irá gerar
  um estado inseguro, isto é, com a possibilidade de formação de deadlocks, a
  requisição é pausada, e cedida a um outro processo.
- Evitar uma das condições para o deadlock. Para cada condição existe uma
  solução possível.

29. A execução de A não depende de recursos que C utiliza, não formando assim um
ciclo, e logo sem deadlock.

30. Se D requisitar, ficará um disponível, e, portanto, inseguro. Se C
requisitar, o estado será seguro pois é concluível, sendo 1 recurso a mais, e C
precisando de 1 recurso.

31. Não é possível ocorrer um deadlock, pois como os recursos são idênticos, é
indiferente a ordem de requisição deles. Então no pior caso, um dos processos
requisitou 2 deles, e irá terminar, e o outro processo está com 1 recurso
alocado, e terá de esperar por um processo que irá de fato terminar. Portanto é
seguro.

32. O menor valor possível é 2, pois possibilitaria que todos os processos
terminassem, se o processo C alocar os 2 recursos tidos pelo A, e o A novamente
alocar 1 recurso, irá entrar em deadlock. O valor é 2 portanto.


