# Algoritmo para listagem de registros removidos.

- Supõe-se um header que armazena o topo da pilha de registros removidos.
- Supõe-se algumas funções já implementadas e abstrai-se manipulação direta com
  arquivos
- Algoritmo em pseudocódigo com sintaxe simliar a linguagens estilo C.

```
#define REG_SIZE NN //tamanho do registro
#define F_OFFSET NN //deslocamento do começo dos registros em relação ao começo
		    //do arquivo
#define OFF(n) ((n * REG_SIZE) + F_OFFSET) //macro para calcular bytes do começo
					   //do registro

r = HEADER_TOP; //variavel temporaria, armazena valor topo q esta no header
cur_pos; 	//posicao atual no arquivo

//Supõe-se uma função get_next_removed(int)
//que retorna o rrn do próximo registro

while r >= 0 {
	cur_pos = OFF(r);
	println("RRN: {}, Offset: {}", r, cur_pos);
	r = get_next_removed(r);
}

```
