#include"cliente.h"

Cliente *inicializarClientes(int *total){
	Cliente *clientes = (Cliente*) malloc(100 * sizeof(Cliente));
	if(clientes == NULL){
		printf("erro ao alocar memoria.\n");
		return NULL;
	}
	*total = 0;
	return clientes;
}

int cadastrarCliente(Cliente **clientes, int *total){
	Cliente *novoClientes = (Cliente*) realloc(
	*clientes,
	((*total) + 1) * sizeof(Cliente));
	if(novoClientes == NULL){
		printf("erro ao alocar memoria.\n");
		return 0;
	}
	*clientes = novoClientes;
	Cliente *novoCliente = &(*clientes)[*total];
	printf("\n-------------------------\n");
	printf("CADASTRO DE CLIENTE:\n");
	printf("-------------------------\n");

	printf("codigo: ");
	scanf("%d", &novoCliente->codigo);

	printf("nome: ");
	scanf(" %[^\n]", novoCliente->nome);

	printf("cpf: ");
	scanf(" %[^\n]", novoCliente->cpf);

	printf("telefone: ");
	scanf(" %[^\n]", novoCliente->telefone);

	(*total)++;

	printf("cliente cadastrado com sucesso!\n");

	return 1;
}

void listarClientes(Cliente clientes[], int total){
	if(total == 0){
		printf("\nnenhum cliente cadastrado.\n");
		return;
	}
	printf("\n-------------------------\n");
	printf("LISTA DE CLIENTES:\n");
	printf("-------------------------\n");

	for(int i = 0; i < total; i++){
		printf("\ncodigo: %d\nnome: %s\ncpf: %s\ntelefone: %s\n",
		clientes[i].codigo,
		clientes[i].nome,
		clientes[i].cpf,
		clientes[i].telefone);
		printf("\n-------------------------\n");
	}
}

Cliente *buscarCliente(Cliente clientes[], int total, int codigo){
	for(int i = 0; i < total; i++){
		if(clientes[i].codigo == codigo){
			return &clientes[i];
		}
	}
	return NULL;
}

int carregarClientes(Cliente clientes[], char *nomeArquivo){
	FILE *arquivo = fopen(nomeArquivo, "r");
	if(arquivo == NULL){
		printf("arquivo de clientes nao encontrado.\n");
		return 0;
	}
	int total = 0;
	while(fscanf(arquivo, "%d;%[^;];%[^;];%[^\n]\n",
		&clientes[total].codigo,
		clientes[total].nome,
		clientes[total].cpf,
		clientes[total].telefone) == 4){
		total++;
	}
	fclose(arquivo);
	return total;
}

void salvarClientes(Cliente clientes[], int total, char *nomeArquivo){
	FILE *arquivo = fopen(nomeArquivo, "w");
	if(arquivo == NULL){
		printf("erro ao salvar clientes.\n");
		return;
	}
	for(int i = 0; i < total; i++){
		fprintf(arquivo, "%d;%s;%s;%s\n",
		clientes[i].codigo,
		clientes[i].nome,
		clientes[i].cpf,
		clientes[i].telefone);
	}
	fclose(arquivo);
}

Cliente *buscarClienteNome(Cliente clientes[], int total, char nome[]){
    for(int i = 0; i < total; i++){
        if(strcmp(clientes[i].nome, nome) == 0){
            return &clientes[i];
        }
    }
    return NULL;
}

void atualizarCliente(Cliente clientes[], int total){
    int codigo;
    printf("\n-------------------------\n");
    printf("ATUALIZAR CLIENTE:\n");
    printf("-------------------------\n");
    printf("digite o codigo: ");
    scanf("%d", &codigo);

    Cliente *c = buscarCliente(clientes, total, codigo);

    if(c != NULL){
        printf("novo nome: ");
        scanf(" %[^\n]", c->nome);
        printf("novo cpf: ");
        scanf(" %[^\n]", c->cpf);
        printf("novo telefone: ");
        scanf(" %[^\n]", c->telefone);
        printf("cliente atualizado!\n");

    }else{
        printf("cliente nao encontrado.\n");
    }
}

void removerCliente(Cliente **clientes, int *total){

    int codigo;

    printf("\n-------------------------\n");
    printf("REMOVER CLIENTE:\n");
    printf("-------------------------\n");

    printf("digite o codigo: ");
    scanf("%d", &codigo);

    for(int i = 0; i < *total; i++){
        if((*clientes)[i].codigo == codigo){

            for(int a = i; a < *total - 1; a++){
                (*clientes)[a] = (*clientes)[a + 1];
            }
            *clientes = realloc(*clientes, (*total - 1) * sizeof(Cliente));
            (*total)--;
            printf("cliente removido!\n");
            return;
        }
    }
    printf("cliente nao encontrado.\n");
}