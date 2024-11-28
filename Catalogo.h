#ifndef CATALOGO_H
#define CATALOGO_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define Numero_Maximo_de_Livros 100
#define Comprimento_maximo 100
#define Tamanho_Maximo_da_Categoria 50
#define ARQUIVO_LIVROS "catalogo_livros.txt"

typedef struct {
    char nome[Comprimento_maximo];
    char categoria[Tamanho_Maximo_da_Categoria];
    int emprestado; 
} Cadastro;

extern Cadastro catalogo[Numero_Maximo_de_Livros];
extern int totalLivros;

void AdicionarLivro(char *nome, char *categoria);
void ListarLivros();
void RemoverLivro(char *nome);
void AtualizarEmprestimo(char *nome, int emprestado);
int verificarEmprestimo(char *nome);
void SalvarCatalogo();
void CarregarCatalogo();

#endif
