#include <locale.h>
#include <string.h>
#include "funcoes.h"

void menup() {
    printf("1 Cadastrar\n");
    printf("2 Login\n");
    printf("3 Listar\n");
    printf("0 Sair\n");
}

void lojaMenu() {
    printf("\n--- Menu da Loja Mandacaru Music ---\n");
    printf("1 Comprar Instrumento\n");
    printf("2 Ver Carrinho\n");
    printf("3 Editar Compra\n");
    printf("4 Excluir Instrumentos da Compra\n");
    printf("5 Finalizar Compra\n");
    printf("0 Sair\n");
}

void verCarrinho(struct User* user) {
	int i;
    printf("\n--- Carrinho de Compras ---\n");
    if (user->cartSize == 0) {
        printf("Seu carrinho está vazio.\n");
    } else {
        for (i = 0; i < user->cartSize; i++) {
            printf("%d. %s - R$%.2f\n", i + 1, user->cart[i].nome, user->cart[i].preco);
        }
    }
}

void comprarInstrumento(struct User* user) {
    struct Instrumento instrumentos[8] = {
        {"Violão", 250.00},
        {"Guitarra", 1200.00},
        {"Baixo", 800.00},
        {"Teclado", 1500.00},
        {"Bateria", 3000.00},
        {"Sanfona", 4000.00},
        {"Ukulele", 350.00},
        {"Microfone", 150.00}
    };

    int escolha;
    int i;

    printf("\n--- Comprar Instrumento ---\n");
    for (i = 0; i < 8; i++) {
        printf("%d. %s - R$%.2f\n", i + 1, instrumentos[i].nome, instrumentos[i].preco);
    }
    printf("Escolha um instrumento para adicionar ao carrinho (0 para voltar): ");
    scanf("%d", &escolha);

    if (escolha > 0 && escolha <= 8) {
        if (user->cartSize < 5) {
            user->cart[user->cartSize] = instrumentos[escolha - 1];
            user->cartSize++;
            printf("%s adicionado ao carrinho!\n", instrumentos[escolha - 1].nome);
        } else {
            printf("Carrinho cheio! Não é possível adicionar mais instrumentos.\n");
        }
    } else if (escolha == 0) {
        printf("Voltando ao menu da loja...\n");
    } else {
        printf("Opção inválida! Tente novamente.\n");
    }
}

void editarCompra(struct User* user) {
    struct Instrumento instrumentos[8] = {
        {"Violão", 250.00},
        {"Guitarra", 1200.00},
        {"Baixo", 800.00},
        {"Teclado", 1500.00},
        {"Bateria", 3000.00},
        {"Sanfona", 4000.00},
        {"Ukulele", 350.00},
        {"Microfone", 150.00}
    };

    int escolha, substituir, novoInstrumento;
	int i;
	
    if (user->cartSize == 0) {
        printf("Seu carrinho está vazio. Não há nada para editar.\n");
        return;
    }

    printf("\n--- Editar Compra ---\n");
    verCarrinho(user);

    printf("Escolha o número do instrumento que deseja substituir (0 para voltar): ");
    scanf("%d", &substituir);

    if (substituir == 0) {
        printf("Voltando ao menu da loja...\n");
        return;
    }

    if (substituir < 1 || substituir > user->cartSize) {
        printf("Opção inválida! Tente novamente.\n");
        return;
    }

    printf("Escolha um novo instrumento para substituir o atual:\n");
    for (i = 0; i < 8; i++) {
        printf("%d. %s - R$%.2f\n", i + 1, instrumentos[i].nome, instrumentos[i].preco);
    }
    printf("Escolha o novo instrumento (0 para voltar): ");
    scanf("%d", &novoInstrumento);

    if (novoInstrumento == 0) {
        printf("Voltando ao menu da loja...\n");
        return;
    }

    if (novoInstrumento < 1 || novoInstrumento > 8) {
        printf("Opção inválida! Tente novamente.\n");
        return;
    }

    user->cart[substituir - 1] = instrumentos[novoInstrumento - 1];
    printf("%s substituído por %s no carrinho!\n", user->cart[substituir - 1].nome, instrumentos[novoInstrumento - 1].nome);
}

void excluirInstrumento(struct User* user) {
    int escolha;
    int i;

    if (user->cartSize == 0) {
        printf("Seu carrinho está vazio. Não há nada para excluir.\n");
        return;
    }

    printf("\n--- Excluir Instrumento ---\n");
    verCarrinho(user);

    printf("Escolha o número do instrumento que deseja excluir (0 para voltar): ");
    scanf("%d", &escolha);

    if (escolha == 0) {
        printf("Voltando ao menu da loja...\n");
        return;
    }

    if (escolha < 1 || escolha > user->cartSize) {
        printf("Opção inválida! Tente novamente.\n");
        return;
    }

    for (i = escolha - 1; i < user->cartSize - 1; i++) {
        user->cart[i] = user->cart[i + 1];
    }
    user->cartSize--;

    printf("Instrumento excluído com sucesso!\n");
}

void finalizarCompra(struct User* user) {
    float total = 0.0;
    int i;

    if (user->cartSize == 0) {
        printf("Seu carrinho está vazio. Não há nada para finalizar.\n");
        return;
    }

    printf("\n--- Finalizar Compra ---\n");
    verCarrinho(user);

    for (i = 0; i < user->cartSize; i++) {
        total += user->cart[i].preco;
    }

    printf("Total da compra: R$%.2f\n", total);

    printf("Pagamento realizado com sucesso!\n");

    user->cartSize = 0;
}

int validarEmail(struct User* v, int qtd, char email[]) {
	int i;
    if (strchr(email, '@') == NULL) {
        printf("Email inválido: não contém '@'.\n");
        return 0;
    }

    if (strlen(email) >= 80) {
        printf("Email inválido: o e-mail deve ter menos de 80 caracteres.\n");
        return 0;
    }

    for (i = 0; i < qtd; i++) {
        if (strcmp(v[i].email, email) == 0) {
            printf("Email inválido: já existe um usuário cadastrado com este e-mail.\n");
            return 0;
        }
    }

    return 1;
}

void cadastrar(struct User* v, int* qtd) {
    char tempEmail[80];

    printf("Informe o nome do usuário: \n");
    scanf(" %[^\n]", v[*qtd].name);

    do {
        printf("Informe o email do usu�rio: \n");
        scanf(" %[^\n]", tempEmail);
    } while (!validarEmail(v, *qtd, tempEmail));

    strcpy(v[*qtd].email, tempEmail);

    printf("Informe a senha do usuário: \n");
    scanf("%s", v[*qtd].pass);

    v[*qtd].cartSize = 0;

    *qtd = *qtd + 1;
}

void listar(struct User* v, int qtd) {
	int i;
    for (i = 0; i < qtd; i++) {
        printf("Nome: %s\n", v[i].name);
        printf("Email: %s\n", v[i].email);
        printf("Senha: %s\n\n", v[i].pass);
    }
}

int autenticar(struct User* v, int qtd, char email[], char pass[]) {
	int i;
    for (i = 0; i < qtd; i++) {
        if (strcmp(v[i].email, email) == 0 && strcmp(v[i].pass, pass) == 0) {
            return i; 
        }
    }
    return -1;
}
