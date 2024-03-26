# Projeto

O objetivo do projeto é desenvolver um interpretador de comandos shell utilizando a linguagem de programação C.
Projeto referente a disciplina Sistemas Operacionais 3º Semestre (2024) - ARQSSOS.

## Requisitos

- Implementação do comando interno cd utilizando a chamada de sistema chdir.
- Implementação do comando interno exit.
- Prompt no formato “user@host[hh:mm:ss] $”. O horário deve ser atualizado a cada novo comando.
- Implementação do comando interno alias (similar ao da shell bash).
- Implementação do comando interno history.
O comando history deve exibir o histórico dos últimos N=10 comandos, numerados de 1 a N. O usuário pode repetir um desses comandos digitando a expressão !n , seguida de Enter, onde n é o número de um comando no histórico.

Extra:
Como um desafio extra, implemente a funcionalidade de redirecionamento de saída de comandos (operador > ).

# Desenvolvimento

O desenvolvimento foi iniciado a partir da execução das chamadas de sistema (comandos externos), que consistia em coletar o comando digitado pelo usuário (input) e filtrar os dados para utilizá-los na função execvp().

O primeiro desafio enfrentado foi a filtragem da string. Na linguagem C, a string é tratada como um vetor de caracteres, então foi necessário filtrar esse vetor, separá-lo e armazenar o resultado.

Para lidar com a string, foram utilizados ponteiros de caracteres (char *) e vetores de ponteiros de caracteres (char *vetor[]).

Em seguida, foi necessário ter os argumentos no tipo correto para passá-los como parâmetro para a função execvp(). Para obter esse resultado, foi utilizada a função filter_string(char *string, char *args[], char *caracter), que recebe como argumentos o ponteiro de uma string, um vetor de ponteiros de caracteres e novamente o ponteiro de uma string.
| Parametro | Descrição |
| --- | --- |
| char *string | é o input do usuário |
| char *args[] | é o vetor que irá armazenar os argumentos necessários para a função execvp() |
| char *caracter | é o caracter que se deseja filtrar na string passada no primeiro argumento |

Após receber os parâmetros necessários, é feita a filtragem. Foi utilizada a função strtok(), que recebe como parâmetros a string que será quebrada e o caracter de separação. Esse caracter será procurado em toda a string e, se encontrado, a string será quebrada em duas partes, e assim sucessivamente.

A função filter_string() é do tipo void, ou seja, não possui retorno, porém ela armazena o resultado da quebra da string no segundo parâmetro passado a ela, char *args[].

Com a função filter_string(), agora os argumentos estão tratados para serem passados para a função execvp(). Antes de ir direto para a execução da função, é necessário verificar se o input do usuário não corresponde aos comandos internos, aliases ou se possui redirecionamento de saída. Caso alguma dessas verificações seja verdadeira, o programa irá executar outro fluxo; caso contrário, o programa seguirá o fluxo para efetuar a chamada de sistema (system calls) externa.

## History e Alias

Parte dos requisitos history e alias são funções que precisam armazenar dados. Para efetuar esse armazenamento, foram utilizadas duas estruturas de dados: filas (queue) e listas (lists).

Para o history, foi utilizada a fila com uma implementação em vetor circular, pois com essa implementação não é necessário mover todas as posições do vetor caso haja alguma modificação na fila. Escolheu-se a fila, pois nas especificações do history cita-se o armazenamento dos últimos 10 comandos, e nesse caso a fila atende às necessidades do history, já que utiliza o conceito FIFO (First in First out).

Para o alias, foi utilizada uma lista simplesmente encadeada (linked list). Essa implementação foi escolhida pois nos requisitos não é especificado o tamanho dessa lista e, para evitar supor um tamanho para o vetor, decidiu-se utilizar o conceito de encadeamento, que cresce e diminui conforme a necessidade.

## Desafio (Redirecionamento de saída)

Um requisito extra, mas não obrigatório, é o redirecionamento de saída, que consiste em redirecionar a saída do programa para algum lugar específico, como um arquivo de texto.

Para desenvolver esse desafio, foi necessário entender como funcionam as funções dup() e dup2().

Antes de explicar o que cada função faz, é importante abordar o fluxo do file descriptor (fd).

Ao executar um arquivo, temos uma tabela que representa as entradas e saídas do mesmo:
| Id | E/S |
| --- | --- |
| 0 | stdin|
| 1 | stdout |
| 2 | stderr |

É possível alterar as E/S e isso será feito adiante.

Por padrão, o sistema irá coletar as entradas (stdin) da entrada padrão do sistema (normalmente o teclado) e redirecionar as saídas (stdout) para a saída padrão do sistema (normalmente a tela). Porém, antes de ser encaminhada para a tela, essa saída é armazenada em um buffer. E, por fim, o stderr redireciona a saída de erro diretamente para a tela e depois a armazena em um buffer.

Entendendo esse fluxo, podemos retomar as funções dup() e dup2().

| Função | Descrição |
| --- | --- |
| dup(int oldfd) | Recebe um valor inteiro, que representa uma entrada ou saída registrada na tabela do arquivo e retorna a referencia da entrada ou saída inserida. |
| dup2(int oldfd, int newfd) | Recebe dois valores inteiros, a função atribui o valor de oldfd a newfd. |

- Utiliza-se dup para armazenar a saída padrão para depois reatribuí-la à posição 0.
- Utiliza-se dup2 para reatribuir a saída padrão de volta ao programa.

Para executar todo esse fluxo descrito acima utiliza-se da função redirect(char *string, char *args[], Queue commands, List alias), que recebe a string já testada pela função hasRedirect(char *string) - função que verifica se na string existe o operador de redirecionamento ‘>’ -, o vetor de argumentos, a fila de comandos e a lista de aliases.

A função realiza as verificações necessárias e filtra a string para ser passada à função interpret() que irá executar o comando.

# Conclusão

O projeto foi concluído cumprindo todos os tópicos requisitados e o desafio (tópico extra). A principal dificuldade do projeto foi a manipulação de strings, na qual era preciso lidar com ponteiros de diversos níveis diferentes. Também tivemos contato com novas chamadas de sistema, o dup e o dup2, já descritas neste texto.

# Executando o programa

- Clone o projeto no seu computador
- Acesse a pasta my-shell
- No terminal (precisa estar dentro da pasta my-shell) rode o comando abaixo:

Para linux:
```
$ make linux
```
Para macos:
```
% make macos
```

# Integrantes

- Augusto G. Serrano
- Caio S. Lopes
