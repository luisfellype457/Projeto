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
        printf("Catalogo cheio! Nao e possivel adicionar mais livros.\n");
    }
}

void ListarLivros() {
    int i; 
    for (i = 0; i < totalLivros; i++) {
        printf("Nome: %s\nCategoria: %s\nEmprestado: %s\n\n", 
               catalogo[i].nome, catalogo[i].categoria, 
               catalogo[i].emprestado ? "Sim" : "Nao");
    }
}

void RemoverLivro(char *nome) {
    int i, j;
    for (i = 0; i < totalLivros; i++) {
        if (strcmp(catalogo[i].nome, nome) == 0) {
            for (j = i; j < totalLivros - 1; j++) {
                catalogo[j] = catalogo[j + 1];
            }
            totalLivros--;
            printf("Livro removido com sucesso.\n");
            return;
        }
    }
    printf("Livro nao encontrado.\n");
}

void AtualizarEmprestimo(char *nome, int emprestado) {
    int i; 
    for (i = 0; i < totalLivros; i++) {
        if (strcmp(catalogo[i].nome, nome) == 0) {
            catalogo[i].emprestado = emprestado;
            printf("Status de emprestimo atualizado.\n");
            return;
        }
    }
    printf("Livro nao encontrado.\n");
}

int verificarEmprestimo(char *nome) {
    int i;
    for (i = 0; i < totalLivros; i++) {
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
    int i; 
    for (i = 0; i < totalLivros; i++) {
        fprintf(file, "%s;%s;%d\n", catalogo[i].nome, catalogo[i].categoria, catalogo[i].emprestado);
    }
    fclose(file);
    printf("Catalogo salvo com sucesso.\n");
}

void CarregarCatalogo() {
    FILE *file = fopen(ARQUIVO_LIVROS, "r");
    if (file == NULL) {
        printf("Arquivo de catalogo nao encontrado.\n");
        return;
    }
    totalLivros = 0;
    while (fscanf(file, "%[^;];%[^;];%d\n", catalogo[totalLivros].nome, catalogo[totalLivros].categoria, 
                  &catalogo[totalLivros].emprestado) == 3) {
        totalLivros++;
    }
    fclose(file);
    printf("Catalogo carregado com sucesso.\n");
}

