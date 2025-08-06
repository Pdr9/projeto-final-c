# Sistema de Gerenciamento de Notas Escolares

## 📋 Descrição do Projeto

Este é um sistema completo desenvolvido em C++ para gerenciar notas escolares, permitindo cadastrar alunos, disciplinas, lançar notas, calcular médias e gerar relatórios. O sistema utiliza arquivos de texto para persistência de dados e implementa uma interface de menu interativa.

## 🎯 Objetivo

Desenvolver um sistema em C++ que permita armazenar, manipular e analisar as notas de alunos em diversas disciplinas, utilizando:
- Arquivos TXT para persistência dos dados
- Matrizes para organização interna
- Funções para modularização do código

## ⚙️ Funcionalidades Principais

### 1. **Cadastro de Alunos**
- Permite cadastrar novos alunos com nome, matrícula e turma
- Armazena dados em arquivo `alunos.txt`
- Formato: `nome;matricula;turma`

### 2. **Cadastro de Disciplinas**
- Permite cadastrar disciplinas com nome e código
- Armazena dados em arquivo `disciplinas.txt`
- Formato: `nome;codigo`

### 3. **Lançamento de Notas**
- Interface para inserir notas de todos os alunos em todas as disciplinas
- Utiliza matriz bidimensional `notas[aluno][disciplina]`
- Salva automaticamente em arquivo `notas.txt`

### 4. **Consulta de Notas**
- **Por Aluno**: Consulta todas as notas de um aluno específico
- **Por Disciplina**: Consulta notas de todos os alunos em uma disciplina

### 5. **Cálculo de Médias**
- Calcula e exibe a média aritmética de cada aluno
- Mostra notas individuais e média geral

### 6. **Geração de Relatórios**
- Gera relatório completo em arquivo `relatorio.txt`
- Inclui dados pessoais, notas por disciplina e médias
- Formato estruturado e legível

## 🗂️ Estrutura de Arquivos

O sistema gerencia os seguintes arquivos:

- **`alunos.txt`**: Dados dos alunos (nome, matrícula, turma)
- **`disciplinas.txt`**: Dados das disciplinas (nome, código)
- **`notas.txt`**: Matriz de notas (uma linha por aluno, notas separadas por ;)
- **`relatorio.txt`**: Relatório completo gerado pelo sistema

## 🏗️ Arquitetura do Código

### Estruturas de Dados
```cpp
// Arrays para alunos
string alunos[MAX_ALUNOS];      // Nomes
string matriculas[MAX_ALUNOS];  // Matrículas
string turmas[MAX_ALUNOS];      // Turmas

// Arrays para disciplinas
string disciplinas[MAX_DISCIPLINAS];  // Nomes
string codigos[MAX_DISCIPLINAS];      // Códigos

// Matriz de notas
float notas[MAX_ALUNOS][MAX_DISCIPLINAS];
```

### Principais Funções

#### Persistência de Dados
- `salvarAluno()`: Salva dados do aluno em arquivo
- `salvarDisciplina()`: Salva dados da disciplina em arquivo
- `salvarNotas()`: Salva matriz de notas em arquivo
- `carregarAlunos()`: Carrega alunos do arquivo para memória
- `carregarDisciplinas()`: Carrega disciplinas do arquivo para memória
- `carregarNotas()`: Carrega notas do arquivo para matriz

#### Interface do Usuário
- `cadastrarAluno()`: Interface para cadastro de alunos
- `cadastrarDisciplina()`: Interface para cadastro de disciplinas
- `lancarNotas()`: Interface para lançamento de notas
- `consultarNotasAluno()`: Consulta notas por aluno
- `consultarNotasDisciplina()`: Consulta notas por disciplina

#### Processamento de Dados
- `calcularMedias()`: Calcula e exibe médias dos alunos
- `gerarRelatorio()`: Gera relatório completo em arquivo
- `menu()`: Controla fluxo principal do programa

## 🚀 Como Usar

### Compilação
```bash
g++ -o sistema ProjetoFinal.cpp
```

### Execução
```bash
./sistema
```

### Menu Principal
```
===== MENU =====
1 - Cadastrar Aluno
2 - Cadastrar Disciplina
3 - Lançar Notas
4 - Consultar Notas por Aluno
5 - Consultar Notas por Disciplina
6 - Calcular Médias
7 - Gerar Relatório em TXT
0 - Sair
```

## 📝 Fluxo de Trabalho Recomendado

1. **Primeiro uso**: Cadastre alunos e disciplinas
2. **Lance as notas** para todos os alunos
3. **Consulte dados** conforme necessário
4. **Gere relatórios** para documentação

## 🔧 Características Técnicas

- **Linguagem**: C++
- **Paradigma**: Programação procedural
- **Estruturas**: Arrays, matrizes, strings
- **I/O**: Arquivos de texto, entrada/saída padrão
- **Persistência**: Arquivos TXT com delimitadores
- **Capacidade**: Até 100 alunos e 20 disciplinas

## 📊 Limitações

- Máximo de 100 alunos
- Máximo de 20 disciplinas
- Busca por nome exato (case-sensitive)
- Dados armazenados em texto simples

## 🔒 Validações Implementadas

- Verificação de abertura de arquivos
- Controle de índices dos arrays
- Prevenção de divisão por zero no cálculo de médias
- Limpeza de buffer de entrada

## 📚 Conceitos de C++ Utilizados

- **Manipulação de arquivos**: `ifstream`, `ofstream`
- **Strings**: `string`, `substr()`, `find()`
- **Arrays e matrizes**: Estruturas de dados básicas
- **Estruturas de controle**: `for`, `while`, `if-else`
- **Funções**: Modularização do código
- **I/O**: `cin`, `cout`, `getline()`

## 👨‍💻 Autor

Este projeto foi desenvolvido como trabalho final demonstrando conhecimentos em:
- Programação em C++
- Manipulação de arquivos
- Estruturas de dados
- Modularização de código
- Interface de usuário em console

---

*Projeto Final - Sistema de Gerenciamento de Notas Escolares*



