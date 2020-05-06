# A calculadora mais rápida do Oeste!

## Tipos numéricos

- As operações básicas ( +, -, \*, /) aceitam tanto inteiro quanto ponto
  flutuante
- IMC aceita apenas ponto flutuante (estatisticamente raro alguem ter peso e
  altura inteiro).
- Fibonacci aceita apenas inteiro.
- Raiz quadrada aceita apenas ponto flutuante.
- Fatorial é apenas de números inteiros.
- A tabuada aceita números inteiros.

## Resultados encontrados

- As operações numéricas dão overflow caso o número extrapole os limites (2^31-1
  e -2^31).
- IMC está válido.
- Potência dá um resultado aproximado em 4 algarismos significativos.
- Raiz quadrada está correta, discute-se abaixo.
- Fibonacci está correto.
- Tabuada está correta.

## Tratamento de erros

- Divisão se *recusa* a executar caso divisor seja 0.
- Potência se *recusa* a executar caso o tipo numérico seja inteiro e o expoente
  seja negativo.
- IMC se *recusa* a executar caso altura ou peso <= 0.
- O Fibonacci, desde onde está enterrado, se *recusa* a executar se o parâmetro
  A <= 0.

### Observações

- Se a divisão for inteira, é mostrado o resultado da divisão inteira e o resto.

- A validade dos resultados foi comprovada fazendo a mesma operação com Python
  3.8.2

- IMC recebe nas unidades do S.I. (kg e m).

- Algoritmo utilizado para raiz quadrada:

```
   REAL FUNCTION  MySqrt(Input)
      IMPLICIT  NONE
      REAL, INTENT(IN) :: Input
      REAL             :: X, NewX
      REAL, PARAMETER  :: Tolerance = 0.00001

      IF (Input == 0.0) THEN            ! if the input is zero
         MySqrt = 0.0                   !    returns zero
      ELSE                              ! otherwise,
         X = ABS(Input)                 !    use absolute value
         DO                             !    for each iteration
            NewX  = 0.5*(X + Input/X)   !       compute a new approximation
            IF (ABS(X - NewX) < Tolerance)  EXIT  ! if very close, exit
            X = NewX                    !       otherwise, keep the new one
         END DO
         MySqrt = NewX
      END IF
   END FUNCTION  MySqrt

END PROGRAM  SquareRoot
```
[Raiz
quadrada](https://pages.mtu.edu/~shene/COURSES/cs201/NOTES/chap06/sqrt-1.html)

- Para a raiz quadrada, um epsilon menor que 0.0001 não fez diferença nos
  resultados (raiz de 2, 3, 5, 6, 7, 8, 9, 11, 12, 13, 14, 15, 16, 17, 18, 19,
20, 121, 122, 123, 144, 145), que tiveram erro menor que 0.000001.

#### Curiosidades

- Fibonacci, also known as Leonardo Bonacci, Leonardo of Pisa, or Leonardo Bigollo
Pisano, was an Italian mathematician from the Republic of Pisa, considered to be
"the most talented Western mathematician of the Middle Ages". Source:
[Fibonacci](https://en.wikipedia.org/wiki/Fibonacci)

© 2020 H.I.R.A.M.
