#include "catalogo.h"

Cadastro catalogo[Numero_Maximo_de_Livros];
int totalLivros = 0;

void AdicionarLivro(char *nome, char *categoria) {
    if (totalLivros < Numero_Maximo_de_Livros) {
        strncpy(catalogo[totalLivros].nome, nome, Comprimento_maximo);
        strncpy(catalogo[totalLivros].categoria, categoria, Tamanho_Maximo_da_Categoria);
        catalogo[totalLivros].emprestado = 0;
        totalLivros++;
    } else {
        printf("Catálogo cheio! Não é possível adicionar mais livros.\n");
    }
}

void ListarLivros() {
    for (int i = 0; i < totalLivros; i++) {
        printf("Nome: %s\nCategoria: %s\nEmprestado: %s\n\n", 
               catalogo[i].nome, catalogo[i].categoria, 
               catalogo[i].emprestado ? "Sim" : "Não");
    }
}

void RemoverLivro(char *nome) {
    for (int i = 0; i < totalLivros; i++) {
        if (strcmp(catalogo[i].nome, nome) == 0) {
            for (int j = i; j < totalLivros - 1; j++) {
                catalogo[j] = catalogo[j + 1];
            }
            totalLivros--;
            printf("Livro removido com sucesso.\n");
            return;
        }
    }
    printf("Livro não encontrado.\n");
}

void AtualizarEmprestimo(char *nome, int emprestado) {
    for (int i = 0; i < totalLivros; i++) {
        if (strcmp(catalogo[i].nome, nome) == 0) {
            catalogo[i].emprestado = emprestado;
            printf("Status de empréstimo atualizado.\n");
            return;
        }
    }
    printf("Livro não encontrado.\n");
}

int verificarEmprestimo(char *nome) {
    for (int i = 0; i < totalLivros; i++) {
        if (strcmp(catalogo[i].nome, nome) == 0) {
            return catalogo[i].emprestado;
        }
    }
    return -1;
}

void SalvarCatalogo() {
    FILE *file = fopen(ARQUIVO_LIVROS, "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para salvar.\n");
        return;
    }
    for (int i = 0; i < totalLivros; i++) {
        fprintf(file, "%s;%s;%d\n", catalogo[i].nome, catalogo[i].categoria, catalogo[i].emprestado);
    }
    fclose(file);
    printf("Catálogo salvo com sucesso.\n");
}

void CarregarCatalogo() {
    FILE *file = fopen(ARQUIVO_LIVROS, "r");
    if (file == NULL) {
        printf("Arquivo de catálogo não encontrado.\n");
        return;
    }
    totalLivros = 0;
    while (fscanf(file, "%[^;];%[^;];%d\n", catalogo[totalLivros].nome, catalogo[totalLivros].categoria, 
                  &catalogo[totalLivros].emprestado) == 3) {
        totalLivros++;
    }
    fclose(file);
    printf("Catálogo carregado com sucesso.\n");
}
