<h2> Sobre o projeto </h2>
Este repositório contém o código fonte de um compilador para uma linguagem de programação simples. O compilador foi desenvolvido como parte da disciplina de Compiladores na Universidade Estadual da Bahia em 2024.1.

<h4> ⚙️ Instalação </h4>
Passo 1: Compilação do DoBlock

Compile o arquivo DoBlock.c utilizando um compilador C. Isso gerará o executável DoBlock.
Importante: No arquivo DoBlock.c, nas linhas 24 e 94, atualize o caminho para o arquivo expression.txt com o caminho real onde o arquivo está localizado.<br> Este arquivo contém a estrutura a ser analisada pelos analisadores léxico e sintático.

Passo 2: Execução do compilador
Abra o terminal e navegue até o diretório onde o executável DoBlock foi gerado.
Para realizar a análise léxica da expressão presente no arquivo expression.txt, execute o comando:<br>
./DoBlock lexico<br>
Para realizar a análise sintática, execute o comando:<br>
./DoBlock sintatico<br>
