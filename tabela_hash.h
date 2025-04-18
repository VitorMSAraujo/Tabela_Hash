#ifndef TABELA_HASH_H
#define TABELA_HASH_H

#include <string>
#include <vector>
#include <list>
#include <utility>

class TabelaHashDoisNiveis {
public:
    // constrói tabela esperando n elementos
    explicit TabelaHashDoisNiveis(int n);

    // insere ou atualiza o par (chave, valor)
    void inserir(const std::string& chave, const std::string& valor);

    // retorna o valor associado à chave ou string vazia se não existir
    std::string buscar(const std::string& chave) const;

private:
    int tamanhoPrimeiroNivel_;    // sempre 10
    int tamanhoSegundoNivel_;     // (n + 9) / 10
    // tabelas_[i][j] é a lista (encadeamento duplo) daquele bucket
    std::vector<std::vector<std::list<std::pair<std::string,std::string>>>> tabelas_;

    // função hash nível 1: soma simples mod 10
    static int funcaoHash1(const std::string& chave);
    // função hash nível 2: polynomial rolling mod segundo nível
    int funcaoHash2(const std::string& chave) const;
};

#endif // TABELA_HASH_H
