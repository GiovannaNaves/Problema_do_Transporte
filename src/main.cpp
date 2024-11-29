#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;

void lerArquivo(const string& nomeArquivo, int& ofertas, int& demandas, vector<int>& ofertasV, vector<int>& demandasV, vector<vector<int>>& custos) {
    ifstream arquivo(nomeArquivo);
    if (!arquivo) {
        cerr << "Erro ao abrir o arquivo: " << nomeArquivo << endl;
        exit(1);
    }

    arquivo >> ofertas >> demandas;
    ofertasV.resize(ofertas);
    demandasV.resize(demandas);
    custos.resize(ofertas, vector<int>(demandas));

    for (int i = 0; i < ofertas; ++i) arquivo >> ofertasV[i];
    for (int i = 0; i < demandas; ++i) arquivo >> demandasV[i];
    for (int i = 0; i < ofertas; ++i)
        for (int j = 0; j < demandas; ++j)
            arquivo >> custos[i][j];

    arquivo.close();
}

void transporte(int ofertas, int demandas, vector<int>& ofertasV, vector<int>& demandasV, vector<vector<int>>& custos) {
    vector<vector<int>> matrizAlocacao(ofertas, vector<int>(demandas, 0));
    int custoTotal = 0;

    for (int i = 0; i < ofertas; ++i) {
        for (int j = 0; j < demandas; ++j) {
            int delta = min(ofertasV[i], demandasV[j]);
            matrizAlocacao[i][j] = delta;
            ofertasV[i] -= delta;
            demandasV[j] -= delta;
            custoTotal += delta * custos[i][j];
        }
    }

    cout << "Matriz de Alocacao:\n";
    for (const auto& linha : matrizAlocacao) {
        for (int valor : linha) cout << valor << "\t";
        cout << endl;
    }
    cout << "Custo total de transporte: " << custoTotal << endl;
}

int main() {
    string nomeArquivo;
    cout << "Digite o nome do arquivo: ";
    cin >> nomeArquivo;

    int ofertas, demandas;
    vector<int> ofertasV, demandasV;
    vector<vector<int>> custos;

    lerArquivo(nomeArquivo, ofertas, demandas, ofertasV, demandasV, custos);
    transporte(ofertas, demandas, ofertasV, demandasV, custos);

    return 0;
}
