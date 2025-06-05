#include <iostream>
using namespace std;

const int MAX = 100;

struct FilaVetor {
    int dados[MAX];
    int inicio;
    int fim;
    int tamanho;
};

// Inicializa a fila
void inicializar(FilaVetor &fila) {
    fila.inicio = 0;
    fila.fim = 0;
    fila.tamanho = 0;
}

// Verifica se está vazia
bool estaVazia(FilaVetor &fila) {
    return fila.tamanho == 0;
}

// Verifica se está cheia
bool estaCheia(FilaVetor &fila) {
    return fila.tamanho == MAX;
}

// Enfileira uma nova senha
void enfileirar(FilaVetor &fila, int senha) {
    if (estaCheia(fila)) {
        cout << "Fila cheia!\n";
        return;
    }
    fila.dados[fila.fim] = senha;
    fila.fim = (fila.fim + 1) % MAX;
    fila.tamanho++;
}

// Remove a senha da frente
int desenfileirar(FilaVetor &fila) {
    if (estaVazia(fila)) return -1;
    int senha = fila.dados[fila.inicio];
    fila.inicio = (fila.inicio + 1) % MAX;
    fila.tamanho--;
    return senha;
}

// Exibe senhas da fila
void exibirFila(FilaVetor &fila) {
    if (estaVazia(fila)) {
        cout << "(vazia)";
        return;
    }
    for (int i = 0; i < fila.tamanho; i++) {
        int index = (fila.inicio + i) % MAX;
        cout << "[" << fila.dados[index] << "] ";
    }
}

int main() {
    FilaVetor senhasGeradas, senhasAtendidas;
    int senhaAtual = 1;
    int opcao;

    inicializar(senhasGeradas);
    inicializar(senhasAtendidas);

    do {
        cout << "\n=== MENU ===\n";
        cout << "Senhas aguardando (" << senhasGeradas.tamanho << "): ";
        exibirFila(senhasGeradas);
        cout << endl;

        cout << "Senhas atendidas (" << senhasAtendidas.tamanho << "): ";
        exibirFila(senhasAtendidas);
        cout << endl;

        cout << "0 - Sair\n";
        cout << "1 - Gerar senha\n";
        cout << "2 - Realizar atendimento\n";
        cout << "Escolha: ";
        cin >> opcao;

        switch(opcao) {
            case 1:
                cout << "Senha [" << senhaAtual << "] gerada!\n";
                enfileirar(senhasGeradas, senhaAtual++);
                break;

            case 2:
                if (!estaVazia(senhasGeradas)) {
                    int atendida = desenfileirar(senhasGeradas);
                    cout << "Atendendo senha [" << atendida << "]\n";
                    enfileirar(senhasAtendidas, atendida);
                } else {
                    cout << "Nenhuma senha aguardando atendimento.\n";
                }
                break;

            case 0:
                if (!estaVazia(senhasGeradas)) {
                    cout << "Ainda existem senhas aguardando! Termine o atendimento antes de sair.\n";
                    opcao = -1;
                }
                break;

            default:
                cout << "Opção inválida.\n";
        }

    } while(opcao != 0);

    cout << "\nSistema encerrado.\n";
    cout << "Senhas atendidas (" << senhasAtendidas.tamanho << "): ";
    exibirFila(senhasAtendidas);
    cout << endl;

    return 0;
}
