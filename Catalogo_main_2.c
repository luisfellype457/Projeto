#include "catalogo.h"

int main() {
    int opcao;
    char nome[Comprimento_maximo];
    char categoria[Tamanho_Maximo_da_Categoria];
    int emprestado;

    CarregarCatalogo();

    do {
        printf("\n1. Adicionar Livro\n2. Listar Livros\n3. Remover Livro\n4. Atualizar Emprestimo\n5. Verificar Emprestimo\n6. Salvar e Sair\nEscolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                printf("Nome do Livro: ");
                fgets(nome, Comprimento_maximo, stdin);
                nome[strcspn(nome, "\n")] = '\0';

                printf("Categoria do Livro: ");
                fgets(categoria, Tamanho_Maximo_da_Categoria, stdin);
                categoria[strcspn(categoria, "\n")] = '\0';

                AdicionarLivro(nome, categoria);
                break;

            case 2:
                ListarLivros();
                break;

            case 3:
                printf("Nome do Livro a remover: ");
                fgets(nome, Comprimento_maximo, stdin);
                nome[strcspn(nome, "\n")] = '\0';
                RemoverLivro(nome);
                break;

            case 4:
                printf("Nome do Livro para atualizar o emprestimo: ");
                fgets(nome, Comprimento_maximo, stdin);
                nome[strcspn(nome, "\n")] = '\0';

                printf("Emprestado? (1 para Sim, 0 para Nao): ");
                scanf("%d", &emprestado);

                AtualizarEmprestimo(nome, emprestado);
                break;

            case 5:
                printf("Nome do Livro para verificar emprestimo: ");
                fgets(nome, Comprimento_maximo, stdin);
                nome[strcspn(nome, "\n")] = '\0';

                emprestado = verificarEmprestimo(nome);
                if (emprestado == -1) {
                    printf("Livro nao encontrado.\n");
                } else {
                    printf("O livro esta %semprestado.\n", emprestado ? "" : "nao ");
                }
                break;

            case 6:
                SalvarCatalogo();
                printf("Saindo...\n");
                break;

            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 6);

    return 0;
}

