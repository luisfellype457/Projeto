#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

typedef struct{
	char nome[30];
	char local[30];
	int num_funcionarios;
	char hora_abertura[5];
	int hora_fechamento[5];
}Biblioteca;

void criar_arquivo_biblioteca();

void ler_arquivo();

void criar_biblioteca();

void deletar_biblioteca();

void mostrar_biblioteca();

#endif
