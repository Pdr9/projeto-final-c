#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int MAX_ALUNOS = 100;
const int MAX_DISCIPLINAS = 20;

string alunos[MAX_ALUNOS];
string matriculas[MAX_ALUNOS];
string turmas[MAX_ALUNOS];
string disciplinas[MAX_DISCIPLINAS];
string codigos[MAX_DISCIPLINAS];
float notas[MAX_ALUNOS][MAX_DISCIPLINAS];

int totalAlunos = 0;
int totalDisciplinas = 0;

void salvarAluno(string nome, string matricula, string turma) {
    ofstream arquivo("alunos.txt", ios::app);
    if (arquivo.is_open()) {
        arquivo << nome << ";" << matricula << ";" << turma << "\n";
        arquivo.close();
    }
}

void salvarDisciplina(string nome, string codigo) {
    ofstream arquivo("disciplinas.txt", ios::app);
    if (arquivo.is_open()) {
        arquivo << nome << ";" << codigo << "\n";
        arquivo.close();
    }
}

void carregarAlunos() {
    ifstream arquivo("alunos.txt");
    string linha;
    totalAlunos = 0;
    while (getline(arquivo, linha)) {
        size_t p1 = linha.find(';');
        size_t p2 = linha.rfind(';');
        alunos[totalAlunos] = linha.substr(0, p1);
        matriculas[totalAlunos] = linha.substr(p1 + 1, p2 - p1 - 1);
        turmas[totalAlunos] = linha.substr(p2 + 1);
        totalAlunos++;
    }
    arquivo.close();
}

void carregarDisciplinas() {
    ifstream arquivo("disciplinas.txt");
    string linha;
    totalDisciplinas = 0;
    while (getline(arquivo, linha)) {
        size_t p = linha.find(';');
        disciplinas[totalDisciplinas] = linha.substr(0, p);
        codigos[totalDisciplinas] = linha.substr(p + 1);
        totalDisciplinas++;
    }
    arquivo.close();
}

void salvarNotas() {
    ofstream arquivo("notas.txt");
    for (int i = 0; i < totalAlunos; i++) {
        for (int j = 0; j < totalDisciplinas; j++) {
            arquivo << notas[i][j];
            if (j < totalDisciplinas - 1) arquivo << ";";
        }
        arquivo << "\n";
    }
    arquivo.close();
}

void carregarNotas() {
    ifstream arquivo("notas.txt");
    string linha;
    int i = 0;
    while (getline(arquivo, linha)) {
        int j = 0;
        size_t pos = 0;
        while (pos != string::npos && j < totalDisciplinas) {
            size_t sep = linha.find(';', pos);
            string valor = (sep == string::npos) ? linha.substr(pos) : linha.substr(pos, sep - pos);
            notas[i][j] = stof(valor);
            pos = (sep == string::npos) ? string::npos : sep + 1;
            j++;
        }
        i++;
    }
    arquivo.close();
}

void cadastrarAluno() {
    string nome, matricula, turma;
    cout << "Nome do aluno: ";
    getline(cin, nome);
    cout << "Matrícula: ";
    getline(cin, matricula);
    cout << "Turma: ";
    getline(cin, turma);
    salvarAluno(nome, matricula, turma);
}

void cadastrarDisciplina() {
    string nome, codigo;
    cout << "Nome da disciplina: ";
    getline(cin, nome);
    cout << "Código: ";
    getline(cin, codigo);
    salvarDisciplina(nome, codigo);
}

void lancarNotas() {
    for (int i = 0; i < totalAlunos; i++) {
        cout << "Aluno: " << alunos[i] << endl;
        for (int j = 0; j < totalDisciplinas; j++) {
            cout << "Nota para " << disciplinas[j] << ": ";
            cin >> notas[i][j];
        }
    }
    cin.ignore(); // Limpar buffer
    salvarNotas();
}

void consultarNotasAluno() {
    string nome;
    cout << "Digite o nome do aluno: ";
    getline(cin, nome);
    for (int i = 0; i < totalAlunos; i++) {
        if (alunos[i] == nome) {
            cout << "Notas de " << nome << ":\n";
            for (int j = 0; j < totalDisciplinas; j++) {
                cout << disciplinas[j] << ": " << notas[i][j] << endl;
            }
            return;
        }
    }
    cout << "Aluno não encontrado.\n";
}

void consultarNotasDisciplina() {
    string nome;
    cout << "Digite o nome da disciplina: ";
    getline(cin, nome);
    int j = -1;
    for (int d = 0; d < totalDisciplinas; d++) {
        if (disciplinas[d] == nome) j = d;
    }
    if (j == -1) {
        cout << "Disciplina não encontrada.\n";
        return;
    }
    for (int i = 0; i < totalAlunos; i++) {
        cout << alunos[i] << ": " << notas[i][j] << endl;
    }
}

void calcularMedias() {
    for (int i = 0; i < totalAlunos; i++) {
        float soma = 0;
        cout << "Médias de " << alunos[i] << ":\n";
        for (int j = 0; j < totalDisciplinas; j++) {
            cout << disciplinas[j] << ": " << notas[i][j] << endl;
            soma += notas[i][j];
        }
        cout << "Média geral: " << (soma / totalDisciplinas) << "\n\n";
    }
}

void gerarRelatorio() {
    ofstream arquivo("relatorio.txt");
    if (!arquivo.is_open()) {
        cout << "Erro ao criar o relatório.\n";
        return;
    }

    arquivo << "RELATÓRIO DE NOTAS E MÉDIAS\n\n";

    for (int i = 0; i < totalAlunos; i++) {
        arquivo << "Aluno: " << alunos[i] << " (Matrícula: " << matriculas[i] << ", Turma: " << turmas[i] << ")\n";
        float soma = 0;
        for (int j = 0; j < totalDisciplinas; j++) {
            arquivo << "  " << disciplinas[j] << ": " << notas[i][j] << "\n";
            soma += notas[i][j];
        }
        float media = totalDisciplinas > 0 ? soma / totalDisciplinas : 0;
        arquivo << "  Média Geral: " << media << "\n\n";
    }

    arquivo.close();
    cout << "Relatório salvo em 'relatorio.txt'.\n";
}

void menu() {
    carregarAlunos();
    carregarDisciplinas();
    carregarNotas();
    string opcao = "1";
    while (opcao != "0") {
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
        getline(cin, opcao);

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

int main() {
    menu();
    return 0;
}