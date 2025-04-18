#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>
#include "tabela_hash.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Uso: " << argv[0] << " teste_hash.txt\n";
        return 1;
    }

    std::ifstream arquivo(argv[1]);
    if (!arquivo) {
        std::perror("erro ao abrir arquivo");
        return 1;
    }

    int n;
    if (!(arquivo >> n)) {
        std::cerr << "Formato inválido: a primeira linha deve ser um número inteiro\n";
        return 1;
    }
    arquivo.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // descarta o resto da linha

    // cria tabela esperando n elementos
    TabelaHashDoisNiveis tabela(n);

    std::string linha;
    while (std::getline(arquivo, linha)) {
        if (linha.empty()) 
            continue;

        std::istringstream ss(linha);
        char operacao;
        ss >> operacao;

        if (operacao == 'I') {
            std::string chave, valor;
            ss >> chave >> valor;
            if (!chave.empty() && !valor.empty())
                tabela.inserir(chave, valor);
        }
        else if (operacao == 'G') {
            std::string chave;
            ss >> chave;
            std::string resultado = tabela.buscar(chave);
            if (resultado.empty())
                std::cout << "Não encontrado\n";
            else
                std::cout << resultado << "\n";
        }
        // outras operações podem ser adicionadas aqui
    }

    return 0;
}
