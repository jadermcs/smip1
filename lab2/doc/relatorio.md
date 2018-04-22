% Relatorio Simulador 2 de MIPS em C++
% Jader Martins Camboim de Sá - 140168915
% 15 Abril, 2018

Objetivo
===
Este trabalho consiste na simulação das instruções de acesso à memória do MIPS
em linguagem C explorando diferentes tipos de dados.
Este trabalho consiste na implementação de um simulador da arquitetura MIPS em
linguagem de alto nível (C/C++/Java). O simulador deve implementar as funções de
busca da instrução (`fetch()`), decodificação da instrução (`decode()`) e execução
da instrução (`execute()`). O programa binário a ser executado deve ser gerado a
partir do montador MARS, juntamento com os respectivos dados. O simulador deve
ler arquivos binários contendo o segmento de código e o segmento de dados para
sua memória e executá-lo.

Descrição do Problema
---
A partir de arquivos montados pelo MARS, executar a simulação dos mesmos em C++
de tal forma que o programa interprete as operações do MIPS.

Funções Implementadas
---
Foram implementadas as seguintes funções através de máscaras e operações *bitwise*:

  1. **fetch()**

    lê uma instrução da memoria e incrementa o pc

  2. **decode()**

    decodifica as intruções para os registradores

  1. **execute()**

    executa os codigos dos registradores e avalia operações executando as chamadas

  1. **step()**

    executa nesta ordem, fetch, decode, execute

  1. **run()**

    executa o step até o fim da memoria ou uma chamada de fim de programa


Testes e Resultados
---
Para realização dos testes utilizei a biblioteca `CATCH` para testes unitários, avaliando cada uma das funções em cases. Os testes foram os seguintes:
```
MEM[0]=20082000
MEM[1]=20092020
MEM[2]=8d290000
MEM[3]=24020004
MEM[4]=20042024
MEM[5]=c
MEM[6]=11200009
MEM[7]=24020001
MEM[8]=8d040000
MEM[9]=c
MEM[10]=24020004
MEM[11]=2004204c
MEM[12]=c
MEM[13]=21080004
MEM[14]=2129ffff
MEM[15]=8000006
MEM[16]=2402000a
MEM[17]=c
MEM[18]=0
MEM[2048]=1
MEM[2049]=3
MEM[2050]=5
MEM[2051]=7
MEM[2052]=b
MEM[2053]=d
MEM[2054]=11
MEM[2055]=13
MEM[2056]=8
MEM[2057]=6f20734f
MEM[2058]=206f7469
MEM[2059]=6d697270
MEM[2060]=6f726965
MEM[2061]=756e2073
MEM[2062]=6f72656d
MEM[2063]=72702073
MEM[2064]=736f6d69
MEM[2065]=6f617320
MEM[2066]=203a20
MEM[2067]=20
MEM[2068]=0
Os oito primeiros numeros primos sao : 1 3 5 7 11 13 17 19
```
Como é visivel, o programa armazena corretamente em memoria os dados.

Implementação e Especificações
===
Está sessão apresenta os códigos utilizados para o simulador, especificações de software, compilação e desenvolvimento.

Especificações de Desenvolvimento
---
Para a escrita do simulador utilizei o `VIM` com plugins auxiliares e o
`GNU/Make`, para compilação utilizei o `GCC` e para os testes a biblioteca
`CATCH`, o sistema operacional é o `Ubuntu 16.04 LTS`.
