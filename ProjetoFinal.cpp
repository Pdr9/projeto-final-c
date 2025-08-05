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