#include <iostream>
using namespace std;

const int MAX = 30;

// ----------------------------
// Pilha com Vetor
// Projeto realizado em dupla por Gustavo Murai e Igor Murai
// ----------------------------
struct PilhaVetor {
    int dados[MAX];
    int topo;
};

void inicializaPilhaVetor(PilhaVetor &p) {
    p.topo = -1;
}

bool estaCheia(PilhaVetor p) {
    return p.topo == MAX - 1;
}

bool estaVazia(PilhaVetor p) {
    return p.topo == -1;
}

void empilhaVetor(PilhaVetor &p, int valor) {
    if (!estaCheia(p)) {
        p.dados[++p.topo] = valor;
    }
}

int desempilhaVetor(PilhaVetor &p) {
    if (!estaVazia(p)) {
        return p.dados[p.topo--];
    }
    return -1; // Erro
}

// ----------------------------
// Pilha com Lista Encadeada
// ----------------------------
struct No {
    int valor;
    No* prox;
};

struct PilhaLista {
    No* topo;
};

void inicializaPilhaLista(PilhaLista &p) {
    p.topo = nullptr;
}

bool estaVaziaLista(PilhaLista p) {
    return p.topo == nullptr;
}

void empilhaLista(PilhaLista &p, int valor) {
    No* novo = new No;
    novo->valor = valor;
    novo->prox = p.topo;
    p.topo = novo;
}

int desempilhaLista(PilhaLista &p) {
    if (!estaVaziaLista(p)) {
        No* temp = p.topo;
        int valor = temp->valor;
        p.topo = temp->prox;
        delete temp;
        return valor;
    }
    return -1; // Erro
}

// ----------------------------
// Função Principal
// ----------------------------
int main() {
    int numeros[MAX];
    int numero;

    // Pilhas com vetor
    PilhaVetor paresV, imparesV;
    inicializaPilhaVetor(paresV);
    inicializaPilhaVetor(imparesV);

    // Pilhas com lista
    PilhaLista paresL, imparesL;
    inicializaPilhaLista(paresL);
    inicializaPilhaLista(imparesL);

    cout << "Digite 30 numeros inteiros em ordem crescente:\n";

    for (int i = 0; i < MAX; i++) {
        cin >> numero;

        if (i > 0 && numero <= numeros[i - 1]) {
            cout << "Erro: o numero deve ser maior que o anterior.\n";
            i--; // volta uma posição
            continue;
        }

        numeros[i] = numero;

        // Empilhando nas duas estruturas
        if (numero % 2 == 0) {
            empilhaVetor(paresV, numero);
            empilhaLista(paresL, numero);
        } else {
            empilhaVetor(imparesV, numero);
            empilhaLista(imparesL, numero);
        }
    }

    // Exibindo resultados (em ordem decrescente pois é desempilhando)
    cout << "\n--- Desempilhando PILHA COM VETOR ---\n";
    cout << "Pares (vetor): ";
    while (!estaVazia(paresV)) {
        cout << desempilhaVetor(paresV) << " ";
    }

    cout << "\nImpares (vetor): ";
    while (!estaVazia(imparesV)) {
        cout << desempilhaVetor(imparesV) << " ";
    }

    cout << "\n\n--- Desempilhando PILHA COM LISTA ENCADEADA ---\n";
    cout << "Pares (lista): ";
    while (!estaVaziaLista(paresL)) {
        cout << desempilhaLista(paresL) << " ";
    }

    cout << "\nImpares (lista): ";
    while (!estaVaziaLista(imparesL)) {
        cout << desempilhaLista(imparesL) << " ";
    }

    cout << endl;
    return 0;
}
