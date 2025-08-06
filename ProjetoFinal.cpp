/*
 * SISTEMA DE GESTÃO ACADÊMICA
 * 
 * Este programa implementa um sistema básico de gestão acadêmica que permite:
 * - Cadastrar alunos e disciplinas
 * - Lançar e consultar notas
 * - Calcular médias
 * - Gerar relatórios
 * 
 * Os dados são persistidos em arquivos de texto para manter as informações
 * entre execuções do programa.
 */

#include <iostream>  // Para entrada e saída de dados (cin, cout)
#include <fstream>   // Para manipulação de arquivos
#include <string>    // Para uso de strings
using namespace std;

// Constantes que definem o tamanho máximo dos arrays
const int MAX_ALUNOS = 100;        // Máximo de 100 alunos no sistema
const int MAX_DISCIPLINAS = 20;    // Máximo de 20 disciplinas no sistema

// Arrays para armazenar informações dos alunos
string alunos[MAX_ALUNOS];      // Nomes dos alunos
string matriculas[MAX_ALUNOS];  // Números de matrícula dos alunos
string turmas[MAX_ALUNOS];      // Turmas dos alunos

// Arrays para armazenar informações das disciplinas
string disciplinas[MAX_DISCIPLINAS];  // Nomes das disciplinas
string codigos[MAX_DISCIPLINAS];      // Códigos das disciplinas

// Matriz bidimensional para armazenar as notas
// notas[i][j] = nota do aluno i na disciplina j
float notas[MAX_ALUNOS][MAX_DISCIPLINAS];

// Contadores para controlar quantos alunos e disciplinas estão cadastrados
int totalAlunos = 0;      // Número atual de alunos cadastrados
int totalDisciplinas = 0; // Número atual de disciplinas cadastradas

/*
 * FUNÇÃO: salvarAluno
 * 
 * Descrição: Salva os dados de um aluno no arquivo "alunos.txt"
 * 
 * Parâmetros:
 *   - nome: Nome completo do aluno
 *   - matricula: Número de matrícula do aluno
 *   - turma: Turma do aluno
 * 
 * Funcionamento:
 *   - Abre o arquivo "alunos.txt" em modo de anexar (ios::app)
 *   - Escreve os dados separados por ponto e vírgula
 *   - Fecha o arquivo automaticamente
 */
void salvarAluno(string nome, string matricula, string turma) {
    ofstream arquivo("alunos.txt", ios::app);  // Abre arquivo em modo anexar
    if (arquivo.is_open()) {  // Verifica se o arquivo foi aberto com sucesso
        // Salva os dados no formato: nome;matricula;turma
        arquivo << nome << ";" << matricula << ";" << turma << "\n";
        arquivo.close();  // Fecha o arquivo
    }
}

/*
 * FUNÇÃO: salvarDisciplina
 * 
 * Descrição: Salva os dados de uma disciplina no arquivo "disciplinas.txt"
 * 
 * Parâmetros:
 *   - nome: Nome da disciplina
 *   - codigo: Código da disciplina
 * 
 * Funcionamento:
 *   - Abre o arquivo "disciplinas.txt" em modo de anexar
 *   - Escreve os dados separados por ponto e vírgula
 *   - Fecha o arquivo automaticamente
 */
void salvarDisciplina(string nome, string codigo) {
    ofstream arquivo("disciplinas.txt", ios::app);  // Abre arquivo em modo anexar
    if (arquivo.is_open()) {  // Verifica se o arquivo foi aberto com sucesso
        // Salva os dados no formato: nome;codigo
        arquivo << nome << ";" << codigo << "\n";
        arquivo.close();  // Fecha o arquivo
    }
}

/*
 * FUNÇÃO: carregarAlunos
 * 
 * Descrição: Carrega todos os alunos do arquivo "alunos.txt" para a memória
 * 
 * Funcionamento:
 *   - Abre o arquivo "alunos.txt" para leitura
 *   - Lê linha por linha do arquivo
 *   - Separa os dados usando ponto e vírgula como delimitador
 *   - Armazena nome, matrícula e turma nos arrays correspondentes
 *   - Atualiza o contador totalAlunos
 */
void carregarAlunos() {
    ifstream arquivo("alunos.txt");  // Abre arquivo para leitura
    string linha;
    totalAlunos = 0;  // Reseta o contador
    
    while (getline(arquivo, linha)) {  // Lê cada linha do arquivo
        // Encontra as posições dos separadores (;)
        size_t p1 = linha.find(';');        // Primeira posição do ';'
        size_t p2 = linha.rfind(';');       // Última posição do ';'
        
        // Extrai os dados da linha usando substr
        alunos[totalAlunos] = linha.substr(0, p1);                    // Nome
        matriculas[totalAlunos] = linha.substr(p1 + 1, p2 - p1 - 1); // Matrícula
        turmas[totalAlunos] = linha.substr(p2 + 1);                   // Turma
        
        totalAlunos++;  // Incrementa contador
    }
    arquivo.close();  // Fecha o arquivo
}

/*
 * FUNÇÃO: carregarDisciplinas
 * 
 * Descrição: Carrega todas as disciplinas do arquivo "disciplinas.txt" para a memória
 * 
 * Funcionamento:
 *   - Abre o arquivo "disciplinas.txt" para leitura
 *   - Lê linha por linha do arquivo
 *   - Separa nome e código usando ponto e vírgula como delimitador
 *   - Armazena nos arrays disciplinas[] e codigos[]
 *   - Atualiza o contador totalDisciplinas
 */
void carregarDisciplinas() {
    ifstream arquivo("disciplinas.txt");  // Abre arquivo para leitura
    string linha;
    totalDisciplinas = 0;  // Reseta o contador
    
    while (getline(arquivo, linha)) {  // Lê cada linha do arquivo
        size_t p = linha.find(';');  // Encontra a posição do separador
        
        // Extrai nome e código da disciplina
        disciplinas[totalDisciplinas] = linha.substr(0, p);      // Nome da disciplina
        codigos[totalDisciplinas] = linha.substr(p + 1);         // Código da disciplina
        
        totalDisciplinas++;  // Incrementa contador
    }
    arquivo.close();  // Fecha o arquivo
}

/*
 * FUNÇÃO: salvarNotas
 * 
 * Descrição: Salva todas as notas da matriz para o arquivo "notas.txt"
 * 
 * Funcionamento:
 *   - Abre o arquivo "notas.txt" para escrita (sobrescreve conteúdo anterior)
 *   - Para cada aluno, escreve suas notas separadas por ponto e vírgula
 *   - Cada linha representa um aluno, cada coluna uma disciplina
 *   - Formato: nota1;nota2;nota3;...
 */
void salvarNotas() {
    ofstream arquivo("notas.txt");  // Abre arquivo para escrita
    
    // Percorre todos os alunos
    for (int i = 0; i < totalAlunos; i++) {
        // Percorre todas as disciplinas para o aluno atual
        for (int j = 0; j < totalDisciplinas; j++) {
            arquivo << notas[i][j];  // Escreve a nota
            
            // Adiciona separador (;) se não for a última disciplina
            if (j < totalDisciplinas - 1) arquivo << ";";
        }
        arquivo << "\n";  // Nova linha para o próximo aluno
    }
    arquivo.close();  // Fecha o arquivo
}

/*
 * FUNÇÃO: carregarNotas
 * 
 * Descrição: Carrega todas as notas do arquivo "notas.txt" para a matriz na memória
 * 
 * Funcionamento:
 *   - Abre o arquivo "notas.txt" para leitura
 *   - Lê linha por linha (cada linha representa um aluno)
 *   - Separa as notas usando ponto e vírgula como delimitador
 *   - Converte strings para float usando stof()
 *   - Armazena na matriz notas[aluno][disciplina]
 */
void carregarNotas() {
    ifstream arquivo("notas.txt");  // Abre arquivo para leitura
    string linha;
    int i = 0;  // Índice do aluno atual
    
    while (getline(arquivo, linha)) {  // Lê cada linha (um aluno por linha)
        int j = 0;        // Índice da disciplina atual
        size_t pos = 0;   // Posição atual na string
        
        // Processa cada nota na linha
        while (pos != string::npos && j < totalDisciplinas) {
            size_t sep = linha.find(';', pos);  // Encontra próximo separador
            
            // Extrai a substring da nota
            string valor = (sep == string::npos) ? 
                          linha.substr(pos) :           // Última nota da linha
                          linha.substr(pos, sep - pos); // Nota intermediária
            
            notas[i][j] = stof(valor);  // Converte string para float e armazena
            
            // Atualiza posição para próxima iteração
            pos = (sep == string::npos) ? string::npos : sep + 1;
            j++;  // Próxima disciplina
        }
        i++;  // Próximo aluno
    }
    arquivo.close();  // Fecha o arquivo
}

/*
 * FUNÇÃO: cadastrarAluno
 * 
 * Descrição: Interface para cadastrar um novo aluno no sistema
 * 
 * Funcionamento:
 *   - Solicita nome, matrícula e turma do usuário
 *   - Usa getline() para permitir nomes com espaços
 *   - Chama salvarAluno() para persistir os dados no arquivo
 *   - Os dados são automaticamente carregados na próxima execução
 */
void cadastrarAluno() {
    string nome, matricula, turma;
    
    // Coleta dados do usuário
    cout << "Nome do aluno: ";
    getline(cin, nome);      // Permite nomes com espaços
    
    cout << "Matrícula: ";
    getline(cin, matricula);
    
    cout << "Turma: ";
    getline(cin, turma);
    
    // Salva o aluno no arquivo
    salvarAluno(nome, matricula, turma);
}

/*
 * FUNÇÃO: cadastrarDisciplina
 * 
 * Descrição: Interface para cadastrar uma nova disciplina no sistema
 * 
 * Funcionamento:
 *   - Solicita nome e código da disciplina do usuário
 *   - Usa getline() para permitir nomes com espaços
 *   - Chama salvarDisciplina() para persistir os dados no arquivo
 *   - Os dados são automaticamente carregados na próxima execução
 */
void cadastrarDisciplina() {
    string nome, codigo;
    
    // Coleta dados do usuário
    cout << "Nome da disciplina: ";
    getline(cin, nome);     // Permite nomes com espaços
    
    cout << "Código: ";
    getline(cin, codigo);
    
    // Salva a disciplina no arquivo
    salvarDisciplina(nome, codigo);
}

/*
 * FUNÇÃO: lancarNotas
 * 
 * Descrição: Interface para inserir notas de todos os alunos em todas as disciplinas
 * 
 * Funcionamento:
 *   - Percorre todos os alunos cadastrados
 *   - Para cada aluno, solicita nota em cada disciplina
 *   - Armazena as notas na matriz notas[aluno][disciplina]
 *   - Salva todas as notas no arquivo ao final
 *   - Usa cin.ignore() para limpar o buffer de entrada
 */
void lancarNotas() {
    // Percorre todos os alunos cadastrados
    for (int i = 0; i < totalAlunos; i++) {
        cout << "Aluno: " << alunos[i] << endl;
        
        // Para o aluno atual, solicita nota em cada disciplina
        for (int j = 0; j < totalDisciplinas; j++) {
            cout << "Nota para " << disciplinas[j] << ": ";
            cin >> notas[i][j];  // Lê a nota e armazena na matriz
        }
    }
    cin.ignore(); // Limpa o buffer para próximas operações com getline()
    
    // Salva todas as notas no arquivo
    salvarNotas();
}

/*
 * FUNÇÃO: consultarNotasAluno
 * 
 * Descrição: Permite consultar todas as notas de um aluno específico
 * 
 * Funcionamento:
 *   - Solicita o nome do aluno
 *   - Busca o aluno no array de nomes
 *   - Se encontrado, exibe todas as notas do aluno
 *   - Se não encontrado, exibe mensagem de erro
 */
void consultarNotasAluno() {
    string nome;
    cout << "Digite o nome do aluno: ";
    getline(cin, nome);
    
    // Busca o aluno pelo nome
    for (int i = 0; i < totalAlunos; i++) {
        if (alunos[i] == nome) {  // Aluno encontrado
            cout << "Notas de " << nome << ":\n";
            
            // Exibe todas as notas do aluno
            for (int j = 0; j < totalDisciplinas; j++) {
                cout << disciplinas[j] << ": " << notas[i][j] << endl;
            }
            return;  // Sai da função após encontrar o aluno
        }
    }
    
    // Se chegou aqui, o aluno não foi encontrado
    cout << "Aluno não encontrado.\n";
}

/*
 * FUNÇÃO: consultarNotasDisciplina
 * 
 * Descrição: Permite consultar as notas de todos os alunos em uma disciplina específica
 * 
 * Funcionamento:
 *   - Solicita o nome da disciplina
 *   - Busca a disciplina no array de disciplinas
 *   - Se encontrada, exibe as notas de todos os alunos nesta disciplina
 *   - Se não encontrada, exibe mensagem de erro
 */
void consultarNotasDisciplina() {
    string nome;
    cout << "Digite o nome da disciplina: ";
    getline(cin, nome);
    
    int j = -1;  // Índice da disciplina (-1 indica não encontrada)
    
    // Busca a disciplina pelo nome
    for (int d = 0; d < totalDisciplinas; d++) {
        if (disciplinas[d] == nome) {
            j = d;  // Armazena o índice da disciplina encontrada
            break;
        }
    }
    
    // Verifica se a disciplina foi encontrada
    if (j == -1) {
        cout << "Disciplina não encontrada.\n";
        return;
    }
    
    // Exibe as notas de todos os alunos na disciplina encontrada
    for (int i = 0; i < totalAlunos; i++) {
        cout << alunos[i] << ": " << notas[i][j] << endl;
    }
}

/*
 * FUNÇÃO: calcularMedias
 * 
 * Descrição: Calcula e exibe a média geral de cada aluno
 * 
 * Funcionamento:
 *   - Percorre todos os alunos cadastrados
 *   - Para cada aluno, exibe todas as notas individuais
 *   - Calcula a soma de todas as notas do aluno
 *   - Calcula e exibe a média aritmética (soma/total de disciplinas)
 */
void calcularMedias() {
    // Percorre todos os alunos
    for (int i = 0; i < totalAlunos; i++) {
        float soma = 0;  // Acumulador para soma das notas
        cout << "Médias de " << alunos[i] << ":\n";
        
        // Exibe cada nota e acumula na soma
        for (int j = 0; j < totalDisciplinas; j++) {
            cout << disciplinas[j] << ": " << notas[i][j] << endl;
            soma += notas[i][j];  // Adiciona nota à soma total
        }
        
        // Calcula e exibe a média aritmética
        cout << "Média geral: " << (soma / totalDisciplinas) << "\n\n";
    }
}

/*
 * FUNÇÃO: gerarRelatorio
 * 
 * Descrição: Gera um relatório completo em arquivo de texto com todos os dados
 * 
 * Funcionamento:
 *   - Cria arquivo "relatorio.txt" para escrita
 *   - Escreve cabeçalho do relatório
 *   - Para cada aluno, inclui:
 *     * Dados pessoais (nome, matrícula, turma)
 *     * Todas as notas por disciplina
 *     * Média geral calculada
 *   - Confirma salvamento do relatório
 */
void gerarRelatorio() {
    ofstream arquivo("relatorio.txt");  // Cria arquivo para o relatório
    
    // Verifica se o arquivo foi criado com sucesso
    if (!arquivo.is_open()) {
        cout << "Erro ao criar o relatório.\n";
        return;
    }

    // Escreve cabeçalho do relatório
    arquivo << "RELATÓRIO DE NOTAS E MÉDIAS\n\n";

    // Gera dados para cada aluno
    for (int i = 0; i < totalAlunos; i++) {
        // Escreve dados pessoais do aluno
        arquivo << "Aluno: " << alunos[i] 
                << " (Matrícula: " << matriculas[i] 
                << ", Turma: " << turmas[i] << ")\n";
        
        float soma = 0;  // Acumulador para calcular média
        
        // Escreve todas as notas do aluno
        for (int j = 0; j < totalDisciplinas; j++) {
            arquivo << "  " << disciplinas[j] << ": " << notas[i][j] << "\n";
            soma += notas[i][j];  // Acumula para calcular média
        }
        
        // Calcula média (evita divisão por zero)
        float media = totalDisciplinas > 0 ? soma / totalDisciplinas : 0;
        arquivo << "  Média Geral: " << media << "\n\n";
    }

    arquivo.close();  // Fecha o arquivo
    cout << "Relatório salvo em 'relatorio.txt'.\n";
}

/*
 * FUNÇÃO: menu
 * 
 * Descrição: Função principal que controla o fluxo do programa
 * 
 * Funcionamento:
 *   - Carrega dados dos arquivos na inicialização
 *   - Exibe menu de opções para o usuário
 *   - Processa a escolha do usuário
 *   - Repete até que o usuário escolha sair (opção 0)
 *   - Usa string para opcao para evitar problemas com entrada
 */
void menu() {
    // Carrega todos os dados dos arquivos para a memória
    carregarAlunos();      // Carrega lista de alunos
    carregarDisciplinas(); // Carrega lista de disciplinas
    carregarNotas();       // Carrega matriz de notas
    
    string opcao = "1";  // Inicializa com valor diferente de "0"
    
    // Loop principal do menu
    while (opcao != "0") {
        // Exibe opções do menu
        cout << "\n===== MENU =====\n";
        cout << "1 - Cadastrar Aluno\n";
        cout << "2 - Cadastrar Disciplina\n";
        cout << "3 - Lançar Notas\n";
        cout << "4 - Consultar Notas por Aluno\n";
        cout << "5 - Consultar Notas por Disciplina\n";
        cout << "6 - Calcular Médias\n";
        cout << "7 - Gerar Relatório em TXT\n";
        cout << "0 - Sair\n";
        cout << "Escolha: ";
        getline(cin, opcao);  // Lê opção do usuário

        // Processa a opção escolhida
        if (opcao == "1") cadastrarAluno();
        else if (opcao == "2") cadastrarDisciplina();
        else if (opcao == "3") lancarNotas();
        else if (opcao == "4") consultarNotasAluno();
        else if (opcao == "5") consultarNotasDisciplina();
        else if (opcao == "6") calcularMedias();
        else if (opcao == "7") gerarRelatorio();
        else if (opcao != "0") cout << "Opção inválida.\n";
    }
}

/*
 * FUNÇÃO: main
 * 
 * Descrição: Função principal do programa
 * 
 * Funcionamento:
 *   - Ponto de entrada da aplicação
 *   - Chama a função menu() que controla todo o fluxo do programa
 *   - Retorna 0 para indicar execução bem-sucedida
 */
int main() {
    menu();    // Inicia o sistema de menu
    return 0;  // Retorna 0 para indicar sucesso
}