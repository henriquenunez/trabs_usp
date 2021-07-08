6. As diferenças estão basicamente nas funções que cada um executa. O Hub
conecta diretamente os circuitos das portas de entrada. O Switch é similar ao
Hub, no entanto também ......................................... .
Já o Roteador tem a capacidade de transmitir pacotes para outra rede, o que é
particularmente útil.

7. O protocolo arp permite que dentro de uma mesma rede os pacotes sejam
   transmitidos com o endereço MAC do destinatário.

8. O funcionamento do protocolo ARP é dado da seguinte forma:

- Uma máquina A deseja enviar um pacote a outra máquina B na mesma rede, portanto
  o pacote não precisa passar por um roteador. Sendo assim, ela deve fazer uma
  requisição ARP para saber qual o endereço MAC associado àquele IP.

- "A" envia então um pacote do tipo "_who has X.X.X.X?_", para toda a rede. A
  máquina B então que possui o IP em questão reponde o pacote com um pacote do
  tipo "_X.X.X.X is YY:YY:YY:YY:YY_". Assim, a máquina "A" registra em sua
  tabela ARP o endereço MAC associado ao IP, para que comunicações posteriores
  sejam feitas diretamente. É importante ressaltar que a tabela ARP é atualizada
  com uma frequência definida pelo sistema de rede da máquina.

- Os pacotes enviados de "A" para "B" são endereçados com o MAC de B.

9. Calcular o CRC


```
Gerador = 1101  Dados=100110
100110 XOR
1101 =
010010 XOR
01101 =
001000 XOR
001101 =
000101 << Resto
```


10. `11100110110101`. O bit de verificação deve ser 1 para fechar a paridade par
do algoritmo.

13.

	A. 
	B. 
	C.

14. Máquinas em redes.

	A. Sobram 24 bits para endereçamento na rede. Sendo 2 endereços
reservados para _Broadcast_ e rede, temos $2^{24} - 2 = 16777214$ possíveis
máquinas nessa rede.

	B. Sobram 8 bits para endereçamento na rede. Sendo 2 endereços
reservados para _Broadcast_ e rede, temos $2^{8} - 2 = 254$ possíveis
máquinas nessa rede.

	C. Sobram 16 bits para endereçamento na rede. Sendo 2 endereços
reservados para _Broadcast_ e rede, temos $2^{16} - 2 = 65534$ possíveis
máquinas nessa rede.


20. O DHCP é um protocolo de configuração automática de rede, ou seja, um
usuário não precisa ter um conhecimento sobre as configurações de rede, como
faixa de endereçamento, IP de Gateway e até mesmo Servidores DNS, pois o DHCP
permite que todas essas informações sejam obtidas automaticamente na conexão.
Além disso, em redes com muita movimentação permite que os endereços IP sejam
reutilizados, já que não são reservados a uma máquina em específico.

21. O uso de NAT permite, entre outras coisas:

- Que diversos dispositivos possam compartilhar o  mesmo endereço IP, o que
  reduz a gravidade do esgotamento de IPv4.

- Uma maior segurança dos dispositivos que estão atrás da NAT, uma vez que suas
  portas não estão expostas diretamente na internet, quererendo um
  redirecionamento de porta caso isso seja necessário.

- Não sei
