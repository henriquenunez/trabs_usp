-- Exercício 3 - SCC0240 Bases de Dados
-- Aluno: Henrique Hiram Libutti Núñez, NUSP: 11275300

-- Q1 (Q1: Selecionar nome  e  estado  dos  times  que  possuem  uniforme  titular  mas  a  cor  principal  não  foi cadastrada.)

-- Primeira solução.
-- SELECT NOME, ESTADO
-- FROM TIME
--     WHERE NOME IN
--           (
--               SELECT TIME
--               FROM UNIFORME
--               WHERE TIPO = 'TITULAR'
--               AND COR_PRINCIPAL IS NULL
--           );

-- Solução definitiva (o editor dá de graça aos vermes. - Machado de Assis)
SELECT T.NOME, T.ESTADO
    FROM TIME T
    JOIN UNIFORME U
        ON U.TIME = T.NOME AND U.TIPO = 'TITULAR' AND U.COR_PRINCIPAL IS NULL;

-- Q2 (Q2: Selecionar, para cada jogador:nome, data de nascimento, time em que joga, estado do time e, se o time jogou alguma partida clássica, listar também data e local da partida.)

SELECT J.NOME, J.DATA_NASC, T.NOME, T.ESTADO, P.DATA, P.LOCAL
    FROM JOGADOR J
        JOIN TIME T
            ON J.TIME = T.NOME
        LEFT JOIN PARTIDA P
            ON P.TIME1 = J.TIME OR P.TIME2 = J.TIME AND (SELECT CLASSICO FROM JOGA WHERE JOGA.TIME1 = P.TIME1 AND JOGA.TIME2 = P.TIME2) = 'S';

-- Q3: Selecionar a quantidade de partidas de jogos clássicos e de jogos não clássicos ocorridos em períodos de férias de verão (meses de janeiro e fevereiro).

SELECT JOGA.CLASSICO, COUNT(*)
    FROM PARTIDA P
    JOIN JOGA
        ON JOGA.TIME1 = P.TIME1 AND JOGA.TIME2 = P.TIME2
    WHERE EXTRACT(MONTH FROM P.DATA) between 1 and 2
    GROUP BY JOGA.CLASSICO;

-- Q4: Selecionar a quantidade de jogos clássicos que ocorreram por mês no ano de 2018. Ordene o resultado do mês com maior quantidade para o de menor quantidade de jogos.

SELECT EXTRACT(MONTH FROM P.DATA), COUNT(*)
    FROM PARTIDA P
    WHERE EXTRACT(YEAR FROM P.DATA) = 2018
    GROUP BY EXTRACT(MONTH FROM P.DATA)
    ORDER BY COUNT(*) DESC;

-- Q5: Para cada time, selecionar: nome, estado, saldo de gols, e a quantidade de jogos clássicos que jogou por ano.

SELECT T.NOME, T.ESTADO, T.SALDO_GOLS, COUNT(CASE WHEN J.CLASSICO = 'S' THEN 1 END) AS CA, EXTRACT(YEAR FROM P.DATA) AS ANO
FROM TIME T
JOIN JOGA J -- Para extrair se é classico ou não
    ON (T.NOME= J.TIME1 OR T.NOME = J.TIME2)
JOIN PARTIDA P
    ON P.TIME1 = J.TIME1 AND P.TIME2 = J.TIME2
GROUP BY T.NOME, T.ESTADO, T.SALDO_GOLS, EXTRACT(YEAR FROM P.DATA)
ORDER BY T.NOME, EXTRACT(YEAR FROM P.DATA);

-- Q6: Selecionar nomes dos times profissionais que jogaram clássicos e não marcaram gols em pelo menos 2 jogos.

SELECT S.NOME
FROM (
         SELECT T.NOME AS NOME,
                COUNT(CASE WHEN P1.PLACAR LIKE '0X%' THEN 1 END) AS C1, -- Conta caso tenha sido o time 1 e seu placar foi 0
                COUNT(CASE WHEN P2.PLACAR LIKE '%X0' THEN 1 END) AS C2  -- Conta caso tenha sido o time 2 e seu placar foi 0
         FROM TIME T
                  JOIN JOGA J
                       ON J.CLASSICO = 'S' AND (J.TIME1 = T.NOME OR J.TIME2 = T.NOME)
                  LEFT JOIN PARTIDA P1 -- CASO O TIME TENHA SIDO O TIME1 NA PARTIDA
                            ON P1.TIME1 = T.NOME
                  LEFT JOIN PARTIDA P2 -- CASO O TIME TENHA SIDO O TIME2 NA PARTIDA
                            ON P2.TIME2 = T.NOME
         WHERE T.TIPO = 'PROFISSIONAL'
         GROUP BY T.NOME
     ) S
WHERE S.C1 > 1 OR S.C2 > 2;

-- Q7: Selecionar a quantidade de times e a média do saldo de gols dos times por estado, por tipo de time. Ordenar o resultado por estado e depois por tipo de time.

SELECT COUNT(*), AVG(T.SALDO_GOLS), T.ESTADO, T.TIPO
    FROM TIME T
    WHERE T.ESTADO IS NOT NULL -- Para a ordenação
    GROUP BY T.ESTADO, T.TIPO
    ORDER BY T.ESTADO, T.TIPO;

-- Q8: Para  os  confrontos  “clássicos”  (Joga),  selecione  a  quantidade  de  vezes  que  os  2  times  já  se  enfrentaram (PARTIDA).

SELECT J.TIME1, J.TIME2, COUNT(*)
    FROM JOGA J
    JOIN PARTIDA P -- Podemos fazer assim ja que a ordem de joga é sempre a mesma da partida.
        ON P.TIME1 = J.TIME1 AND P.TIME2 = J.TIME2
    GROUP BY J.TIME1, J.TIME2;

-- Q9:Selecionar os times do estado de SP que jogaram em todos os locais em que o “Santos” jogou.
-- Conceito de divisão na álgebra relacional.

WITH S AS -- Primeiramente selecionando os locais que o Santos jogou
(
    SELECT LOCAL
    FROM PARTIDA
    WHERE TIME1 = 'SANTOS'
       OR TIME2 = 'SANTOS'
       AND LOCAL IS NOT NULL
)
SELECT T.NOME
FROM TIME T
WHERE NOT EXISTS -- Se "sobrou" algum lugar que Santos jogou,
(                -- quer dizer que o time não jogou em todos os locais que o Santos jogou.
    (SELECT LOCAL FROM S) -- Não precisa checar se é nulo pois é uma checagem já realizada
    MINUS
    (
        SELECT LOCAL
        FROM PARTIDA P
        WHERE P.TIME1 = T.NOME
           OR P.TIME2 = T.NOME
    )
);

-- Q10: Selecionar os times com o menor saldo de gols em cada estado. Apresentar nome do time, estado e saldo de gols.

-- Senti uma richa cruzeiro-galo aqui k k k
SELECT T.NOME, T.ESTADO, M.SALDO
    FROM TIME T
    JOIN
        (
            SELECT T.ESTADO, MIN(T.SALDO_GOLS) AS SALDO
            FROM TIME T
            GROUP BY T.ESTADO
        ) M
        ON M.ESTADO = T.ESTADO AND M.SALDO = T.SALDO_GOLS;
