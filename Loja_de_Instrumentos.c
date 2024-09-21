#include <stdio.h>
#include "funcoes.h"
#include <locale.h>

int main() {
    setlocale(LC_ALL, "portuguese");

    struct User usuarios[100];
    int qtdUsuarios = 0;
    int opcao, usuarioAutenticado;

    printf("Bem-vindo ao sistema da loja Mandacaru Music!\n");

    do {
        menup();
        printf("Escolha uma op��o: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrar(usuarios, &qtdUsuarios);
                break;

            case 2:
                {
                    char email[80], pass[10];
                    printf("Informe seu email: \n");
                    scanf(" %[^\n]", email);
                    printf("Informe sua senha: \n");
                    scanf("%s", pass);

                    usuarioAutenticado = autenticar(usuarios, qtdUsuarios, email, pass);

                    if (usuarioAutenticado != -1) {
                        printf("Bem-vindo, %s!\n", usuarios[usuarioAutenticado].name);

                        int opcaoLoja;

                        do {
                            lojaMenu();
                            printf("Escolha uma op��o: ");
                            scanf("%d", &opcaoLoja);

                            switch (opcaoLoja) {
                                case 1:
                                    comprarInstrumento(&usuarios[usuarioAutenticado]);
                                    break;

                                case 2:
                                    verCarrinho(&usuarios[usuarioAutenticado]);
                                    break;

                                case 3:
                                    editarCompra(&usuarios[usuarioAutenticado]);
                                    break;

                                case 4:
                                    excluirInstrumento(&usuarios[usuarioAutenticado]);
                                    break;

                                case 5:
                                    finalizarCompra(&usuarios[usuarioAutenticado]);
                                    break;

                                case 0:
                                    printf("Saindo do menu da loja...\n");
                                    break;

                                default:
                                    printf("Op��o inv�lida! Tente novamente.\n");
                                    break;
                            }
                        } while (opcaoLoja != 0);
                    } else {
                        printf("Email ou senha inv�lidos.\n");
                    }
                }
                break;

            case 3:
                listar(usuarios, qtdUsuarios);
                break;

            case 0:
                printf("Saindo do sistema...\n");
                break;

            default:
                printf("Op��o inv�lida! Tente novamente.\n");
                break;
        }
    } while (opcao != 0);

    return 0;
}

