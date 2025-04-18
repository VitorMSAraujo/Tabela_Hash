#include "tabela_hash.h"

// função hash nível 1: soma simples dos bytes mod 10
int TabelaHashDoisNiveis::funcaoHash1(const std::string& chave) {
    unsigned int h = 0;
    for (unsigned char c : chave) 
        h += c;
    return h % 10;
}

// função hash nível 2: polynomial rolling mod tamanhoSegundoNivel_
int TabelaHashDoisNiveis::funcaoHash2(const std::string& chave) const {
    unsigned int h = 0;
    for (unsigned char c : chave) 
        h = h * 31u + c;
    return h % tamanhoSegundoNivel_;
}

TabelaHashDoisNiveis::TabelaHashDoisNiveis(int n)
    : tamanhoPrimeiroNivel_(10),
      tamanhoSegundoNivel_((n + 9) / 10),
      tabelas_(tamanhoPrimeiroNivel_,
               std::vector<std::list<std::pair<std::string,std::string>>>(
                   tamanhoSegundoNivel_))
{}

// insere novo par ou atualiza valor se a chave já existir
void TabelaHashDoisNiveis::inserir(const std::string& chave, const std::string& valor) {
    int i = funcaoHash1(chave);
    int j = funcaoHash2(chave);
    auto& lista = tabelas_[i][j];

    // se já existe, atualiza e retorna
    for (auto& par : lista) {
        if (par.first == chave) {
            par.second = valor;
            return;
        }
    }

    // senão, insere novo nó no início da lista
    lista.emplace_front(chave, valor);
}

// busca valor pela chave; retorna "" se não encontrado
std::string TabelaHashDoisNiveis::buscar(const std::string& chave) const {
    int i = funcaoHash1(chave);
    int j = funcaoHash2(chave);
    const auto& lista = tabelas_[i][j];

    for (auto& par : lista) {
        if (par.first == chave)
            return par.second;
    }
    return "";
}
