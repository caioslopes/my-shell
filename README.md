# Projeto
Objetivo do projeto é desenvolver um interpretador de comandos shell utilizando a linguagem de programação C.

## Requisitos
- Comando interno cd. Use a chamada de sistema chdir.
- Comando interno exit;
- Prompt no formato “user@host[hh:mm:ss] $”. O horário deve ser atualizado a cada novo comando.
- Comando interno alias (alias da shell bash).
- Comando interno history.
O comando history deve exibir o histórico dos N=10 últimos comandos, em linhas numeradas de 1 a N. O usuário poderá repetir um desses comandos digitando a expressão !n , seguida de Enter, em que n é o número de um comando no histórico.

# Desenvolvimento
Iniciamos o desenvolvimento a partir da execução das chamadas de sistemas (comandos externos), no qual consistia em coletar o comandos digitado pelo usuário (input) e filtrar os dados para utiliza-los na função execvp().

O primeiro desafio que tivemos de lidar, foi a filtragem da string, na linguagem C a string é tratada como um vetor de caracteres, ou seja, precisariamos filtrar esse vetor, separa-lo e armazena-lo.

Para lidar com a string, utilizamos ponteiros de caracteres (char *) e vetor de ponteiro de caracter (char *vetor[]). 

Seguindo adiante, era preciso ter os argumentos no tipo correto para passar como parametro para a função execvp(). Para obter tal resultado temos uma função chamada filter_string(char *string, char *args[], char *caracter), que recebe como argumento, o ponteiro de uma string (vetor de caracteres), um vetor de ponteiros de caracteres e novamente o ponteiro de uma string.
- char *string: é o input do usuário;
- char *args[]: é o vetor que irá armazenar os argumentos necessários para a função execvp();
- char *caracter: é o caracter que você deseja filtrar a string passada no primeiro argumento.

...

Para concluir o objetivo do projeto, utilizamos algumas estrutura de dados para o armazenamento dos dados, sendo elas a fila - para armazenar o historico de coomandos - e a lista - para armazenar os alias (apelido dos comandos).

# Integrantes
- Augusto G Serrano
- Caio S Lopes
