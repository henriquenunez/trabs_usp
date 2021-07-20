INSERT INTO TIME (NOME, ESTADO, TIPO, SALDO_GOLS) VALUES ('PALMEIRAS', 'SP', 'PROFISSIONAL', 23);
INSERT INTO TIME (NOME, ESTADO, TIPO, SALDO_GOLS) VALUES ('VASCO', 'RJ', 'PROFISSIONAL', 2);
INSERT INTO TIME (NOME, ESTADO, TIPO, SALDO_GOLS) VALUES ('FLAMENGO', 'RJ', 'PROFISSIONAL', 16);
INSERT INTO TIME (NOME, ESTADO, TIPO, SALDO_GOLS) VALUES ('BOTAFOGO', 'RJ', 'PROFISSIONAL', 0);
INSERT INTO TIME (NOME, ESTADO, TIPO, SALDO_GOLS) VALUES ('CHAPECOENSE', 'SC', 'PROFISSIONAL', 20);
INSERT INTO TIME (NOME, ESTADO, TIPO, SALDO_GOLS) VALUES ('SANTOS', 'SP', 'PROFISSIONAL', 21);
INSERT INTO TIME (NOME, ESTADO, TIPO, SALDO_GOLS) VALUES ('UNIDOS', NULL, 'AMADOR', NULL);
INSERT INTO TIME (NOME, ESTADO, TIPO, SALDO_GOLS) VALUES ('INTER', 'SP', 'AMADOR', 1);
INSERT INTO TIME (NOME, ESTADO, TIPO, SALDO_GOLS) VALUES ('CRUZEIRO', 'MG', 'PROFISSIONAL', 17);
INSERT INTO TIME (NOME, ESTADO, TIPO, SALDO_GOLS) VALUES ('ATLETICO', 'MG', 'PROFISSIONAL', 15);


INSERT INTO JOGA (TIME1, TIME2, CLASSICO) VALUES ('VASCO', 'CHAPECOENSE', 'N');
INSERT INTO JOGA (TIME1, TIME2, CLASSICO) VALUES ('INTER', 'PALMEIRAS', 'N');
INSERT INTO JOGA (TIME1, TIME2, CLASSICO) VALUES ('PALMEIRAS', 'SANTOS', 'S');
INSERT INTO JOGA (TIME1, TIME2, CLASSICO) VALUES ('UNIDOS', 'INTER', NULL);
INSERT INTO JOGA (TIME1, TIME2, CLASSICO) VALUES ('CRUZEIRO', 'SANTOS', 'N');
INSERT INTO JOGA (TIME1, TIME2, CLASSICO) VALUES ('VASCO', 'FLAMENGO', 'S');

INSERT INTO PARTIDA (TIME1, TIME2, DATA, PLACAR, LOCAL) VALUES ('VASCO', 'CHAPECOENSE', TO_DATE('2018/04/30 16:00:00', 'YYYY/MM/DD HH24:MI:SS'), DEFAULT, 'RIO DE JANEIRO');
INSERT INTO PARTIDA (TIME1, TIME2, DATA, PLACAR, LOCAL) VALUES ('VASCO', 'CHAPECOENSE', TO_DATE('2018/01/30 15:00:00', 'YYYY/MM/DD HH24:MI:SS'), DEFAULT, 'SAO PAULO');
INSERT INTO PARTIDA (TIME1, TIME2, DATA, PLACAR, LOCAL)  VALUES ('INTER', 'PALMEIRAS', TO_DATE('2018/03/02 20:00:00', 'YYYY/MM/DD HH24:MI:SS'), '1X0', NULL);
INSERT INTO PARTIDA (TIME1, TIME2, DATA, PLACAR, LOCAL) VALUES ('PALMEIRAS', 'SANTOS', TO_DATE('2018/02/01 14:30:00', 'YYYY/MM/DD HH24:MI:SS'), '4X2', 'SANTOS');
INSERT INTO PARTIDA (TIME1, TIME2, DATA, PLACAR, LOCAL) VALUES ('UNIDOS', 'INTER', TO_DATE('2021/12/02 16:30:00', 'YYYY/MM/DD HH24:MI:SS'), DEFAULT, 'SANTOS');
INSERT INTO PARTIDA (TIME1, TIME2, DATA, PLACAR, LOCAL) VALUES ('UNIDOS', 'INTER', TO_DATE('2020/12/01 16:30:00', 'YYYY/MM/DD HH24:MI:SS'), DEFAULT, 'SAO CARLOS');
INSERT INTO PARTIDA (TIME1, TIME2, DATA, PLACAR, LOCAL) VALUES ('CRUZEIRO', 'SANTOS', TO_DATE('2018/07/01 14:30:00', 'YYYY/MM/DD HH24:MI:SS'), '0X2', 'BELO HORIZONTE');
INSERT INTO PARTIDA (TIME1, TIME2, DATA, PLACAR, LOCAL) VALUES ('UNIDOS', 'INTER', TO_DATE('2021/12/01 16:30:00', 'YYYY/MM/DD HH24:MI:SS'), DEFAULT, 'BELO HORIZONTE');
INSERT INTO PARTIDA (TIME1, TIME2, DATA, PLACAR, LOCAL) VALUES ('CRUZEIRO', 'SANTOS', TO_DATE('2018/12/07 14:30:00', 'YYYY/MM/DD HH24:MI:SS'), '3X2', NULL);
INSERT INTO PARTIDA (TIME1, TIME2, DATA, PLACAR, LOCAL) VALUES ('VASCO', 'FLAMENGO', TO_DATE('2018/02/10 16:00:00', 'YYYY/MM/DD HH24:MI:SS'), '2X1', 'RIO DE JANEIRO');
INSERT INTO PARTIDA (TIME1, TIME2, DATA, PLACAR, LOCAL) VALUES ('VASCO', 'FLAMENGO', TO_DATE('2020/12/03 16:00:00', 'YYYY/MM/DD HH24:MI:SS'), DEFAULT, NULL);


INSERT INTO JOGADOR (CPF, RG, NOME, DATA_NASC, NATURALIDADE, TIME)
    VALUES ('400.560.298-61', '20.000.201-3', 'REINALDO', TO_DATE('1995/09/02', 'YYYY/MM/DD'), 'SAO PAULO', 'SANTOS');
INSERT INTO JOGADOR (CPF, RG, NOME, DATA_NASC, NATURALIDADE, TIME)
    VALUES ('400.560.298-60', '40.123.201-3', 'JOSE', TO_DATE('1997/10/12', 'YYYY/MM/DD'), NULL,'PALMEIRAS');
INSERT INTO JOGADOR (CPF, RG, NOME, DATA_NASC, NATURALIDADE, TIME)
    VALUES ('111.460.298-60', '40.435.201-3', 'ALFREDO', TO_DATE('1990/01/22', 'YYYY/MM/DD'), 'RIO DE JANEIRO', 'CHAPECOENSE');
INSERT INTO JOGADOR (CPF, RG, NOME, DATA_NASC, NATURALIDADE, TIME)
    VALUES ('103.460.333-60', '40.234.201-3', 'EDERSON', TO_DATE('1989/10/10', 'YYYY/MM/DD'), 'CAMPINAS', 'SANTOS');
INSERT INTO JOGADOR (CPF, RG, NOME, DATA_NASC, NATURALIDADE, TIME)
    VALUES ('011.460.298-60', '20.435.201-3', 'NETO', TO_DATE('1991/09/02', 'YYYY/MM/DD'), 'FLORIANOPOLIS', 'CHAPECOENSE');
INSERT INTO JOGADOR (CPF, RG, NOME, DATA_NASC, NATURALIDADE, TIME)
    VALUES ('123.340.198-45', '34.124.002-5', 'SANTIAGO', TO_DATE('1987/12/01', 'YYYY/MM/DD'), 'IBATE', 'UNIDOS');
INSERT INTO JOGADOR (CPF, RG, NOME, DATA_NASC, NATURALIDADE, TIME)
    VALUES ('301.400.298-00', '40.100.202-7', 'ALESSANDRO', TO_DATE('1992/03/01', 'YYYY/MM/DD'), 'BELO HORIZONTE', 'SANTOS');

INSERT INTO POSICAO_JOGADOR (JOGADOR, POSICAO)  VALUES ('400.560.298-61', 'MEIA');
INSERT INTO POSICAO_JOGADOR (JOGADOR, POSICAO)  VALUES ('400.560.298-60', 'GOLEIRO');
INSERT INTO POSICAO_JOGADOR (JOGADOR, POSICAO)  VALUES ('111.460.298-60', 'ATACANTE');
INSERT INTO POSICAO_JOGADOR (JOGADOR, POSICAO)  VALUES ('103.460.333-60', 'ZAGUEIRO');
INSERT INTO POSICAO_JOGADOR (JOGADOR, POSICAO)  VALUES ('011.460.298-60', 'GOLEIRO');
INSERT INTO POSICAO_JOGADOR (JOGADOR, POSICAO)  VALUES ('123.340.198-45', 'ZAGUEIRO');
INSERT INTO POSICAO_JOGADOR (JOGADOR, POSICAO)  VALUES ('301.400.298-00', 'ATACANTE');

INSERT INTO DIRETOR (TIME, NOME) VALUES ('PALMEIRAS', 'ROGER MACHADO');
INSERT INTO DIRETOR (TIME, NOME) VALUES ('VASCO', 'ZE RICARDO');
INSERT INTO DIRETOR (TIME, NOME) VALUES ('CHAPECOENSE', 'GILSON');
INSERT INTO DIRETOR (TIME, NOME) VALUES ('INTER', 'AUGUSTO');
INSERT INTO DIRETOR (TIME, NOME) VALUES ('SANTOS', 'JAIR');
INSERT INTO DIRETOR (TIME, NOME) VALUES ('UNIDOS', 'CAMARGO');
INSERT INTO DIRETOR (TIME, NOME) VALUES ('CRUZEIRO', 'MANO MENEZES');

INSERT INTO UNIFORME (TIME, TIPO, COR_PRINCIPAL) VALUES ('PALMEIRAS', 'TITULAR', 'VERDE');
INSERT INTO UNIFORME (TIME, TIPO, COR_PRINCIPAL) VALUES ('PALMEIRAS', 'RESERVA', 'BRANCO');
INSERT INTO UNIFORME (TIME, TIPO, COR_PRINCIPAL) VALUES ('VASCO', 'TITULAR', 'BRANCO');
INSERT INTO UNIFORME (TIME, TIPO, COR_PRINCIPAL) VALUES ('CHAPECOENSE', 'RESERVA', NULL);
INSERT INTO UNIFORME (TIME, TIPO, COR_PRINCIPAL) VALUES ('SANTOS', 'RESERVA', 'PRETO');
INSERT INTO UNIFORME (TIME, TIPO, COR_PRINCIPAL) VALUES ('INTER', 'TITULAR', NULL);
INSERT INTO UNIFORME (TIME, TIPO, COR_PRINCIPAL) VALUES ('CRUZEIRO', 'TITULAR', 'AZUL');
INSERT INTO UNIFORME (TIME, TIPO, COR_PRINCIPAL) VALUES ('UNIDOS', 'TITULAR', 'AZUL');
