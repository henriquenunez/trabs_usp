# Lista de Memória & I/O (21/12/2020)

## Henrique Hiram Libutti Núñez - 11275300

1. Supondo que cada registrador armazene uma palavra de memória, temos que o tempo de salvar o estado da máquina será de
(32 + 2) x 10ns = 340ns. Esse é o tempo mínimo de processamento de uma interrupção. Supondo que a cpu leva apenas esse tempo
processando a interrupção, para saber quantas interrupções por segundo ela é capaz de processar, basta elevar o número a -1,
para ter o valor em Hz. A máquina consegue processar aproximadamente 2,94 milhões de interrupções por segundo .


2. Primeiramente, vamos calcular qual o tempo que a impressora demoraria para receber cada caracter. Se cada página tem 50
linhas de 80 colunas cada, e a impressora imprime 6 páginas por minuto, temos (50*80)*6/60 como a quantidade de caracteres 
por segundo. Esse valor é de 400 caracteres por segundo, e invertendo esse valor temos que ela leva 2.5ms por cada caractere 
impresso. Sendo assim, não tem sentido em utilizar a E/S orientada a interrupções, pois a impressora irá perder 47,5ms em 
ociosidade a cada interrupção.


3. As camadas são:

- a) _Devices_, pois é papel do do controlador interno do disco calcular onde a informação deve ser armazenada, baseado em um
comando gerado pela controladora do lado do computador.

- b) _Hardware_, pois é a a parte do computador que é capaz de interagir diretamente com o dispositivo e fornecer uma abstração
para o sistema operacional.

- c) _Kernel space_, o sistema operacional que tem acesso a suas políticas de permissão, e estipula assim se cada usuário tem
permissão ou não para acessar arquivos e dispositivos. Portanto, a camada é a de kernel.

- d) _User space_, pois tipicamente o programa que o usuário está utilizando terá sua própria lógica de operação, como um
processador de textos, editor de fotos, capazes de exportar uma representação de algo (texto ou foto) a ser impresso em algo mais
diretamente operável pela máquina. Em geral estes programas não precisam executar em modo kernel. 


4. 

- 4.1) (c) Pois 1G/1M = 1k.

- 4.2) (c) Nenhuma das anteriores

- 4.3) (a) Zero, pois apenas o topo da memória estará ocupado com o S.O. (considerando que endereços menores são os primeiros)

- 4.4) (b) Como pertencem à mesma página, basta calcular o deslocamento dentro dessa mesma página para calcular o endereço real.

- 4.5) (c) 30 bits se traduzem em 1GB se uma palavra tem um byte. Logo, 1GB deve ser reservado para a paginação.

- 4.6) (c) Apenas parte da memória virtual não poderá ser utilizada.

5. 

- a) Assumindo que o endereçamento é realizado a nível de byte, e sendo que o sistema tem o endereçamento em 16 páginas,
e cada página tem 4kB em endereços, o endereço virtual endereça então 16 \* 4kB = 64kB. Sendo k = 1024, o logaritmo de k \* 64
em base 2 é 16. Portanto 16 bits são necessários. O formato é de 4 bits para seleção de página, e 12 para deslocamento dentro
da página.

-b) 

```
Fila inicial: 0, 2, 1, 9, 11, 4, 5, 2, 3.

5, 15, 12, 8, 0, 15, 6, 10, 11 e 13.

5 => inaltera fila.
15 => -0, 2, 1, 9, 11, 4, 5, 2, 3, +15 = 2, 1, 9, 11, 4, 5, 2, 3, 15.
12 => -2, 1, 9, 11, 4, 5, 2, 3, 15, +12 = 1, 9, 11, 4, 5, 2, 3, 15, 12. 
8 =>  -1, 9, 11, 4, 5, 2, 3, 15, 12, +8 = 9, 11, 4, 5, 2, 3, 15, 12, 8.
0 =>  -9, 11, 4, 5, 2, 3, 15, 12, 8, +0 = 11, 4, 5, 2, 3, 15, 12, 8, 0.
15 => inaltera fila.
6 =>  -11, 4, 5, 2, 3, 15, 12, 8, 0, +6 = 4, 5, 2, 3, 15, 12, 8, 0, 6.
10 => -4, 5, 2, 3, 15, 12, 8, 0, 6, +10 = 5, 2, 3, 15, 12, 8, 0, 6, 10.
11 => -5, 2, 3, 15, 12, 8, 0, 6, 10, +11 = 2, 3, 15, 12, 8, 0, 6, 10, 11.
13 => -2, 3, 15, 12, 8, 0, 6, 10, 11, +13 = 3, 15, 12, 8, 0, 6, 10, 11, 13.
```

Houveram 8 faltas de páginas nos 10 acessos realizados.

6.

- a) T+4 e T+5.
- b) No instante (T+3) satura-se o limite de 11 páginas carregadas na memória.
- c) não sei.
- d) Através do bit de modificação e bit de validade.

7. O Estado inicial é 1111 1110 0000 0000:

- a) 1111 1111 1111 0000 (5 blocos a mais)

- b) 1000 0001 1111 0000 (6 blocos a menos)

- c) 1111 1111 1111 1100 (8 blocos a mais)

- d) 1111 1110 0000 1100 (8 blocos a mais)


8. A fração em disco desperdiçada será de aproximadamente 50%, pois um bloco de disco pode pertencer a apenas um arquivo.
O desperdício em um sistema de arquivos real provavelmente é menor, pois o tamanho dos arquivos não necessariamente é de 1KB, e além disso,
existem algumas técnicas para evitar que existam muitos arquivos pequenos, como é o exemplo do _busybox_, onde existe um grande binário, que
contém diversos executáveis nele, cada executável é acessado através de um link simbólico para uma posição específica dentro do _busybox_.

