#include "biblioteca.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LIBRARIES 10

Biblioteca library[MAX_LIBRARIES];
int count = 0;
FILE *p;

void criar_arquivo_biblioteca(){
	int i;
	p = fopen("Bibliotecas.txt", "w");
	if (p == NULL){
		printf("Nao foi possivel abrir o arquivo.");
		exit(1);
	}
	for (i=0; i < count; i++){
		fprintf(p, "Nome: %s\nLocal: %s\nFuncionarios: %d\nAbertura: %s\nFechamento: %s\n\n", library[i].nome, library[i].local, library[i].num_funcionarios, library[i].hora_abertura, library[i].hora_fechamento);
	}
	fclose(p);
	return;
}

void ler_arquivo(){
	p = fopen("Bibliotecas.txt", "a+");
	if (p == NULL){
		printf("Nao foi possivel abrir/ler o arquivo.");
		exit(2);
	}
	count = 0;
	while(fscanf(p, "Nome: %[^\n]\nLocal: %[^\n]\nFuncionarios: %d\nAbertura: %5[^\n]\nFechamento: %5[^\n]\n", library[count].nome, library[count].local, &library[count].num_funcionarios, library[count].hora_abertura, library[count].hora_fechamento) == 5){
		count++;
		if (count >= MAX_LIBRARIES)
			break;
		fscanf(p, "\n");
	}
	fclose(p);
	return;
}

void criar_biblioteca() {
    char confirm[3], nome_temp[20];
    int i;
    do {
        if (count >= MAX_LIBRARIES) {
            printf("\nNumero maximo de bibliotecas atingido! (count >= MAX_LIBRARIES)\n");
            return;
        }
        ler_arquivo();
        printf("\nDigite o nome da biblioteca:\n> ");
        scanf("%19[^\n]", nome_temp);
        fflush(stdin);
        for (i = 0; i < count; i++) {
            if (!strcmp(library[i].nome, nome_temp)) {
                printf("\nErro: ja existe uma biblioteca chamada '%s'\n\n", nome_temp);
                return;
            }
        }
        strcpy(library[count].nome, nome_temp);
        printf("Digite o local da biblioteca:\n> ");
        scanf("%19[^\n]", library[count].local);
        fflush(stdin);
        printf("Digite o numero de funcionarios da biblioteca:\n> ");
        scanf("%d", &library[count].num_funcionarios);
        fflush(stdin);
        printf("Digite o horario de abertura (ex.: 07:00):\n> ");
        scanf("%5[^\n]", library[count].hora_abertura);
        fflush(stdin);
        printf("Digite o horario de fechamento (ex.: 20:00):\n> ");
        scanf("%5[^\n]", library[count].hora_fechamento);
        fflush(stdin);
        count++;
        criar_arquivo_biblioteca();
        printf("\nBiblioteca cadastrada! Deseja continuar cadastrando? (sim/nao)\n> ");
        scanf("%3[^\n]", confirm);
        fflush(stdin);
        printf("\n");
    } while (!strcasecmp(confirm, "sim") || !strcasecmp(confirm, "s"));
}

void deletar_biblioteca() {
	int i, j, found = 0;
	char nome[30];
	ler_arquivo();
	printf("\nDigite o nome da biblioteca a ser excluida:\n> ");
	scanf("%29[^\n]", nome);
	fflush(stdin);
	for (i = 0; i < count; i++) {
		if (!strcmp(library[i].nome, nome)) {
			found = 1;
			break;
		}
	}
	if (!found) {
		printf("\nBiblioteca '%s' nao encontrada.\n", nome);
		return;
	}
	for (j = i; j < count - 1; j++) {
		library[j] = library[j + 1];
	}
	count--;
	criar_arquivo_biblioteca();
	printf("\nBiblioteca '%s' deletada com sucesso.\n\n", nome);
	return;
}

void mostrar_biblioteca(){
	int i, c, found=0;
	char nomep[30], confirm[3];
	ler_arquivo();
	printf("\n(1) - Pesquisar uma biblioteca\n(2) - Mostrar lista completa\n(3) - Cancelar\n\n> ");
	scanf("%d", &c);
	fflush(stdin);
	if (c == 1){
		do{
			printf("\nDigite o nome da biblioteca:\n> ");
			scanf("%29[^\n]", nomep);
			fflush(stdin);
			for (i=0; i < count; i++){
				if (!strcmp(library[i].nome, nomep)){
					found=1;
					printf("\n\tBiblioteca encontrada!\n\n");
					printf("Nome: %s\n", library[i].nome);
					printf("Local: %s\n", library[i].local);
					printf("Funcionarios: %d\n", library[i].num_funcionarios);
					printf("Horario de abertura: %s\n", library[i].hora_abertura);
					printf("Horario de fechamento: %s\n\n", library[i].hora_fechamento);
				}
			}
			if (!found)
				printf("\n\tBiblioteca nao econtrada!\n\n");
			printf("Deseja repetir a busca? (sim/nao)\n> ");
			scanf("%3[^\n]", confirm);
			fflush(stdin);
		} while(!strcasecmp(confirm, "sim") || !strcasecmp(confirm, "s"));
	} else if (c==2) {
		for (i=0; i < count; i++){
			printf("\n\t#Biblioteca %d\n\n", i+1);
			printf("Nome: %s\n", library[i].nome);
			printf("Local: %s\n", library[i].local);
			printf("Numero de Funcionarios: %d\n", library[i].num_funcionarios);
			printf("Horario de abertura: %s\n", library[i].hora_abertura);
			printf("Horario de fechamento: %s\n\n", library[i].hora_fechamento);
		}
	} else {
		return;
	}
	return;
}

void update_biblioteca(){
	char nomep[30], confirm[3];
	int i, op, found=0;
	ler_arquivo();
	printf("\nDigite o nome da biblioteca a ser alterada:\n> ");
	scanf("%29[^\n]", nomep);
	fflush(stdin);
	for (i = 0; i < count; i++){
		if (!strcmp(library[i].nome, nomep)){
			found = 1;
			printf("\n\tBiblioteca encontrada!\n\n");
			printf("Nome: %s\n", library[i].nome);
			printf("Local: %s\n", library[i].local);
			printf("Funcionarios: %d\n", library[i].num_funcionarios);
			printf("Horario de abertura: %s\n", library[i].hora_abertura);
			printf("Horario de fechamento: %s\n\n", library[i].hora_fechamento);
			break;
		}
	}
	if (!found){
		printf("\n\tBiblioteca nao encontrada!\n\n");
		return;
	}
	printf("Selecione o que deseja alterar:\n\n");
	printf("(1) - Nome\n");
	printf("(2) - Local\n");
	printf("(3) - Numero de Funcionarios\n");
	printf("(4) - Horario de Abertura\n");
	printf("(5) - Horario de Fechamento\n");
	printf("(6) - Cancelar\n\n> ");
	scanf("%d", &op);
	fflush(stdin);
	switch(op){
		case 1:
			printf("Digite o novo nome:\n> ");
			scanf("%29[^\n]", library[i].nome);
			fflush(stdin);
			break;
		case 2:
			printf("Digite o novo local:\n> ");
			scanf("%29[^\n]", library[i].local);
			fflush(stdin);
			break;
		case 3:
			printf("Digite o novo numero de funcionarios:\n> ");
			scanf("%d", &library[i].num_funcionarios);
			fflush(stdin);
			break;
		case 4:
			printf("Digite o novo horario de abertura (ex.: 08:00):\n> ");
			scanf("%29[^\n]", library[i].hora_abertura);
			fflush(stdin);
			break;
		case 5:
			printf("Digite o novo horario de fechamento (ex.: 22:00):\n> ");
			scanf("%29[^\n]", library[i].hora_fechamento);
			fflush(stdin);
			break;
		default:
			return;
	}
	printf("\nAlterado com sucesso!\n\n");
	criar_arquivo_biblioteca();
}

void menu_bibliotecas(){
	int op;
	do{
		printf("- - - - - [Menu Bibliotecas] - - - - -\n\n");
		printf("(1) - Criar biblioteca\n");
		printf("(2) - Pesquisar/listar bibliotecas\n");
		printf("(3) - Deletar biblioteca\n");
		printf("(4) - Atualizar biblioteca\n");
		printf("(5) - Sair\n\n> ");
		scanf("%d", &op);
		fflush(stdin);
		switch(op){
			case 1:
				criar_biblioteca();
				break;
			case 2: 
				mostrar_biblioteca();
				break;
			case 3:
				deletar_biblioteca();
				break;
			case 4:
				update_biblioteca();
				break;
			case 5:
				printf("\n");
				break;
			default:
				break;
		}
	} while (op < 5 && op > 0);
	return;
}
