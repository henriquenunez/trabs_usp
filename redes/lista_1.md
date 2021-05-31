## Lista 1 - Redes de computadores

Aluno: Henrique Hiram Libutti Núñez
\#USP: 11275300

### Parte 1

1. A internet é padronização da comunicação mundial, formada por diversos
   computadores conectados (sejam servidores, dispositivos de transmissão de
sinal), que permite a transmissão da informação em uma base comum, e geralmente
com protocolos bem definidos, como o HTTP.
2. Um programa cliente é um programa utilizado para a execução de uma parte da
   lógica de serviço, sendo essa a lógica do cliente. Normalmente são utilizados
em complementação do programa servidor. O programa servidor é um programa que
normalmente encontra-se executando indefinidamente, aguardando conexões de
programas clientes. O programa servidor executa a lógica de servidor, geralmente
armazenando dados, realizando autenticações de acordo com a lógica de serviço e
também processamentos que não devem ser feitos pelo cliente.
3. Dentre as tecnologias de acesso que estão na vanguarda em 2021, podemos
   destacar o 5G, que é uma tecnologia para dados móveis, a Starlink, uma rede
de satélites proprietárias que permite Internet de banda larga, e a fibra
óptica, que é o padrão para acesso à Internet em imóveis.
4. As redes de comutação de circuitos oferecem, na janela de tempo destinada a
   uma determinada comunicação, ou circuito, uma garantia de taxa constante de
transmissão e uso dedicado do enlace. Isso evita que o sistema sofra com
problemas de perda de pacote por filas cheias nos roteadores.
5. Um serviço orientado à conexão necessita que, antes de ocorrer a comunicação
   entre duas partes, haja uma apresentação e o estabelecimento de um conceito
que comunicação, geralmente utilizando o protocolo TCP no contexto de redes de
computadores. Um serviço não orientado à conexão não exige que isso aconteça,
simplesmente espera que uma _stream_ de dados se apresente em uma determinada
porta, sem a necessidade de uma apresentação e um estabelecimento de conexão
antes.
6. Os dois modelos representam a pilha de protocolos necessária para a
   transmissão de dados a partir de um programa em alto nível, passando de
camada a camada em níveis mais baixos até o meio de comunicação, que é físico, e
passando novamente camada a camada, em níveis mais altos, para que os dados
estejam disponíveis na outra parte da comunicação. A camada TCP/IP se divide em
4 camadas, e a camada ISO/OSI se divide em 7 camadas. Por possuir mais camadas,
o modelo OSI faz com que cada possível abstração seja insertida em uma nova
camada, seja ela em nível de aplicação ou nos níveis mais próximos do meio de
comunicação.
7. Um protocolo é um estabelecimento de padrões que devem ser utilizados por
   diferentes partes, para que uma lógica se mantenha consistente. Existem
diversos protocolos utilizados na computação, normalmente estabelecidos por
documentos, como normas IEEE, IETF e RFC. Em especial, a área de Redes de
Computadores na computação utiliza extensivamente protocolos para a conversão da
informação em diferentes representações, juntamente com métodos de checagem de
erros, e principalmente para que máquinas diferentes, sistemas operacionais
diferentes, possam com implementações diferentes terem uma base comum de
comunicação, permitindo a transmissão de dados e a comunicação com diferentes
máquinas, e, com isso, permite também a comunicação efetiva entre máquinas que
estão fisicamente distantes.
8. Aplicação: Permite o uso com muitos recursos por programas em alto nível,
   como navegadores, que requerem autenticação e formas de transmitir arquivos;
Transporte: Executa controle de erros nos pacotes, estabelece controle de fluxos
e sequenciamento quando necessário; Rede: permite identificar logicamente os
dispositivos numa rede, e endereçar pacotes utilizando o protocolo IP; Enlace:
endereça em baixo nível os pacotes que estão conectados diretamente nos
roteadores. Física: transmite sinais digitais que representam bits da
transmissão, através do meio físico, como ondas eletromagnéticas ou sinais
elétricos.
9. Controle de fluxo é o conjunto de técnicas que alguns protocolos (como o TCP)
   implementam para garantir que a informação chegue numa sequência correta, e
com certas garantias, como algoritmos de verificação de erros.
10. Controle de congestionamento é o método que sistemas de ... utilizam para
    que diversos clientes consigam utilizar a rede. O controle de
congestionamento serve para evitar que hajam atrasos significativos na
comunicação entre duas ou mais partes passando por um mesmo roteador. Ela atua
na taxa de envio de pacotes.
11. São duas técnicas de multiplexação para permitir o acesso de múltiplos
    clientes ao serviço (rede de comunicação). O _Frequency Division
Multiplex_(FDM) atua na divisão do canal de comunicação (sendo ele uma faixa do
espectro eletromagnético, por exemplo) em diferentes canais, e assim
estabelecendo que determinado cliente do sistema de comunicação deve utilizar
determinada faixa. O _Time Division Multiplex_(TDM) divide o tempo de utilização
do canal, reservando integralmente para que determinado cliente realize sua
comunicação com o resto da rede.
12. Respondido na questão 7.
13. Um sistema de comunicação é um conjunto de tecnologias capazes de transmitir
    informações entre dispositivos fisicamente ou logicamente separados. Para
que seja possível realizar esse tipo de comunicação, é necessário que a forma
como a comunicação é feita seja bem definida, como por exemplo uma rede cabeada
ethernet, que funciona a partir da variação de tensão nos terminais. A partir
disso, monta-se uma pilha de protocolos que são capazes de, a cada nível de
abstração, entregar as informações de um modo mais possível de ser utilizado por
programas de computador, como clientes e servidores. O sistema de comunicação,
além disso, é responsável pela integridade da informação. O nível lógico,
mencionado anteriormente, é uma representação virtual do sistema de comunicação,
como as interfaces de _loopback_ que são comuns em sistemas operacionais
modernos e permitem diversos tipos de utilização, sendo o mais comum deles, a
comunicação interprocessos (IPC).
14. _Multicast_ é o oferecimento da comunicação a um determinado grupo de
    dispositivos conectados em uma rede. O _broadcast_ é o oferecimento da
comunicação para todos os dispositivos conectados na rede.
15. É possível definir os diferentes tipos de Área de Rede baseado nos
    dispositivos que normalmente a irão utilizar, e também nas velocidades de
comunicação. _Wide Area Network_(WAN) refere-se à comunicação cujos limites
extrapolam os perímetros urbanos. Pode-se dizer que toda a Internet está
conectada através de WAN. _Personal Area Network_(PAN) é considerada a rede de
acesso dos dispositivos de posse pessoal, ou seja, celulares, _wearables_,
cartões inteligentes e computadores (quando comunicando com esses dispositivos)
integram a PAN, sendo um protocolo representativo o Bluetooth. _Local Area
Network_(LAN), é a rede que semanticamente está contida em uma edificação, mas
pode também ser a rede de uma empresa, no caso de vários prédios, e entre
outros. Ela isola os dispositivos conectados nela, e geralmente possui um
_gateway_ para permitir o acesso à Internet. A _Metropolitan Area Network_(MAN)
é a rede que interliga os diversos sistemas que as áreas urbanas possuem, como
sincronização de semáforos de trânsito.

### Parte 2

1.
	A.  Primeiramente, 1000 bytes = 8000 bits. Se a velocidade do enlace é
1000Mbps, devemos dividir a quantidade de bits pela velocidade do enlace para
calcular a velocidade de transmissão do enlace. Além disso, devemos calcular a
velocidade de propagação para calcular a diferença de tempo do sinal chegar no
outro computador. Portanto, 800km/(200.000kmps) = 4ms, e o tempo do enlace é
8kb/100Mpps = 0.08ms. Logo o tempo total de transmissão é 4.08ms.
	B.  Já temos alguns valores calculados, como o tempo de propagação. Sendo
o tamanho do pacote 800 bits, o tempo fim a fim é de 4ms + 0.008ms,
totalizando 4.008ms.
	C.  É o tempo de propagação, ou seja, de 4ms.
	D.  É o tempo de propagação, ou seja, de 4ms.
	E.  Isso depende do tamanho dos _buffers_ de saída dos dispositivos,
portanto não é possível calcular.
2.
	A.  O atraso é o tempo de transmissão somado ao tempo de propagação, ou
seja, 1e4km / 2e8mps + 30Mb / 10Mbps = (3s + 0.05s) = 3.05s.
	B. Temos o tempo de propagação, de 0.05s. Se multiplicarmos isso pelo
tempo de enlace, teremos a quantidade de bits enviados. Ou seja, 0.05s * 10Mbps =
500kb.
	C. Para isso, devemos dobrar o tempo de tranmissão, já que o enlace é o
mesmo. Portanto, o tempo total será de 3.10s.
3.  Já que serão 3 pacotes, temos a propriedade que enquando um pacote é
    retransmitido pelo roteador, um novo pode ser enviado. O tempo de propagação
continua o mesmo, mas agora o tempo de tranmissão para um pacote será de 1s.
Mas, o roteador tem que esperar que o pacote inteiro chegue, e retransmití-lo
implica em dobrar o tempo. Para o primeiro pacote, 2s, o segundo pacote requer
um segundo mais e o terceiro pactore um segundo mais, totalizando 4s. Com o
tempo de propagação, temos 4.05s.
4.
	A.  O tempo de propagação é a distância divida pelo tempo de propagação,
ou seja, dprop = m/s.
	B.  O tempo de transmissão do pacote é o tamanho do pacote dividido pela
velocidade do enlace, ou seja, dtx = L/R.
	C. Para o tempo ponto-a-ponto, somamos dprop a dtx.
5. Calculando primeiramente o atraso de propagação, temos que o tempo do sinal
   sair da _Phoenix_ e chegar até a Terra é 60e9m/3e8mps = 200s. Além disso,
temos o tempo do enlace, que é de 128kpbs. Para calcular o tempo no enlace,
64e6b/128kpbs = 500s. Somando temos 700s de tempo de trasmissão. Resposta: (d).
6.
	A.  O atraso de propagação pode ser calculado dividindo a distância pelo
tempo de propagação no enlace. Logo, como a distância entre X e Y é de 300km, e
também a velocidade de propagação é 2.5^8 kmps, logo o atraso de propagação é
1.2ms.
	B.  O pacote a ser enviado tem 3Mb, e a velocidade de enlace é de
50Mbps. Se calcularmos o tempo no enlace, será de 60ms.
	C.  Somando o tempo de propagação e o do enlace, temos 61.2ms.
	D.  O tamanho do pacote seria 60kb, fazendo uma regra de três com 60ms
<> 3Mb, 1.2ms <> x, x = 60kb.
	E.  Realizando novamente a regra de três, com 300km <> 1.2ms, x <> 60ms,
x = 15e6m.
	F.  Recalculando o atraso de transmissão, temos 3Mb/1Gbps = 3ms. O
atraso total portanto é de 4.2ms.
7.
	A.  O tempo de propagação deve ser 1e2/2e8 = 0.0005ms.
	B.  O tempo de transmissão do pacote é 1024/4e6 = 0.265ms
	C.  O tempo fim a fim da transmissão é 0.0005 + 0.265 = 0.2655ms
8. Já que não é necessário considerar atrasos de propagação, enfileiramento e
   processamento, podemos simplesmente dividir o tamanho da tranmissão pelo
   tempo dos enlaces. Então, temos 200 pacotes de 1500 bytes => 200 * 8 * 1500 =
   2400000 bits, e isso dividido pelo tempo dos enlaces somados, uma vez que a
   transmissão é sequencial. Logo (2400000/(600kbps))\*3 = 12s.

