struct Instrumento {
    char nome[30];
    float preco;
};

struct User {
    char name[30];
    char email[80];
    char pass[10];
    struct Instrumento cart[5];  
    int cartSize;                
};

void menup();
void lojaMenu();
void verCarrinho(struct User* user);
void comprarInstrumento(struct User* user);
void editarCompra(struct User* user);
void excluirInstrumento(struct User* user);
void finalizarCompra(struct User* user);
int validarEmail(struct User* v, int qtd, char email[]);
void cadastrar(struct User* v, int* qtd);
void listar(struct User* v, int qtd);
int autenticar(struct User* v, int qtd, char email[], char pass[]);
