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

    keep

  2. **decode()**

    keep

  1. **execute()**

    keep


Testes e Resultados
---
Para realização dos testes utilizei a biblioteca `CATCH` para testes unitários, avaliando cada uma das funções em cases. Os testes foram os seguintes:
```
```

Implementação e Especificações
===
Está sessão apresenta os códigos utilizados para o simulador, especificações de software, compilação e desenvolvimento.

Código Fonte
---
**funcs.hpp**
```
```

**mips.hpp**
```
```


**main.cpp**
```
```

Especificações de Desenvolvimento
---
Para a escrita do simulador utilizei o `VIM` com plugins auxiliares e o
`GNU/Make`, para compilação utilizei o `GCC` e para os testes a biblioteca
`CATCH`, o sistema operacional é o `Ubuntu 16.04 LTS`.
