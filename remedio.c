#include"remedio.h"

int cadastrar(Remedio **estoque, int *total){
	int novoTotal = *total + 1;

	Remedio *novoEstoque = (Remedio*) realloc(*estoque, novoTotal * sizeof(Remedio));

	if(novoEstoque == NULL){
		printf("erro ao alocar memoria...\n");
		return 0;
	}

	*estoque = novoEstoque;
	
	 Remedio *novoRemedio = &(*estoque)[*total];


	printf("\n---- CADASTRO ----\n");

	printf("nome: ");
	scanf(" %[^\n]", novoRemedio->nome);

	printf("laboratorio: ");
	scanf(" %[^\n]", novoRemedio->laboratorio);

	printf("codigo: ");
	scanf("%d", & novoRemedio->codigo);

	printf("preco: ");
	scanf("%f", & novoRemedio->preco);

	printf("quantidade: ");
	scanf("%d", & novoRemedio->quantidade);
	
	(*total)++;

	printf("\nmedicamento cadastrado com sucesso!\n");
	return 1;
}

void listar(Remedio estoque[], int total){
	if(total == 0){
		printf("\nnenhum medicamento foi cadastrado....\n");
		return;
	}
	 printf("\n-------------------------\n");
	printf("\n---- LISTA DE MEDICAMENTOS ----\n");
	 printf("\n-------------------------\n");
	for(int i = 0; i < total; i++){
		
		 printf("\tcodigo: %d\n\tnome: %s\n\tlaboratorio: %s\n\tpreco: "
           "%.2f\n\tquantidade: %d\n",
           estoque[i].codigo, estoque[i].nome, estoque[i].laboratorio,
           estoque[i].preco, estoque[i].quantidade);
           printf("\n-------------------------\n");
	}
}

Remedio *buscar(Remedio estoque[], int total, int codigo) {
    for (int i = 0; i < total; i++) {
        if (estoque[i].codigo == codigo) {
            return &estoque[i];
        }
    }
    return NULL;
}

Remedio *buscarPorNome(Remedio estoque[], int total, char nome[]){
	for(int i = 0; i < total; i++){
		if(strcmp(estoque[i].nome, nome) == 0){
			return &estoque[i];
		}
	}
	return NULL;
}

void remover(Remedio **estoque, int *total) {
    printf("\n-------------------------\n");
    printf("REMOVER MEDICAMENTO DO ESTOQUE:\n");
    printf("-------------------------\n");
    int  continuar;
    char nome[100];
    printf("digite o nome do medicamento a ser removido: ");
    scanf(" %[^\n]", nome);
    Remedio *medicamento = buscarPorNome(*estoque, *total, nome);
    if(medicamento != NULL){
    	int indice = medicamento - *estoque;
    	 printf("\tcodigo: %d\n\tnome: %s\n\tlaboratorio: %s\n\tpreco: "
             "%.2f\n\tquantidade: %d\n",
             medicamento->codigo, medicamento->nome, medicamento->laboratorio, medicamento->preco, 
             medicamento->quantidade);
             printf("continuar a remocao? (1 - Sim, 0 - Nao): ");
              scanf("%d", &continuar);
	
        if(continuar){
        
          for (int i = indice; i < (*total) - 1; i++) {
              (*estoque)[i] = (*estoque)[i + 1];
          }
        
         		 Remedio *novoEstoque = (Remedio*) realloc(*estoque, sizeof(Remedio) * ((*total) - 1));
          			if (novoEstoque != NULL) {
              			*estoque = novoEstoque;
              			(*total)--;
              			printf("medicamento removido com sucesso!\n");
          } else {
              printf("erro ao realocar memoria para o estoque.\n");
          }
        }
        
    } else {
        printf("medicamento nao encontrado.\n");
    }
 }

Remedio *inicializarEstoque(int *total){
    Remedio *estoque = (Remedio *) malloc(100 * sizeof(Remedio));

    if(estoque == NULL){
        printf("Erro ao alocar memória.\n");
        exit(EXIT_FAILURE);
    }
    *total = 0;
    return estoque;
}

int carregarEstoque(Remedio estoque[], char *nomeArquivo){
    FILE *arquivo = fopen(nomeArquivo, "r");

    if(arquivo == NULL){
        printf("Arquivo não encontrado. Criando novo arquivo.\n");
        return 0;
    }

    int total = 0;

    while(fscanf(arquivo, "%d;%[^;];%[^;];%f;%d\n",
        &estoque[total].codigo,
        estoque[total].nome,
        estoque[total].laboratorio,
        &estoque[total].preco,
        &estoque[total].quantidade) == 5){

        total++;
    }

    fclose(arquivo);

    return total;
}

void salvarEstoque(Remedio estoque[], int total, char *nomeArquivo){
    FILE *arquivo = fopen(nomeArquivo, "w");

    if(arquivo == NULL){
        printf("erro ao salvar arquivo.\n");
        return;
    }
    for(int i = 0; i < total; i++){
        fprintf(arquivo, "%d;%s;%s;%.2f;%d\n",
            estoque[i].codigo,
            estoque[i].nome,
            estoque[i].laboratorio,
            estoque[i].preco,
            estoque[i].quantidade);
    }
    fclose(arquivo);
}

void listarEstoqueBaixo(Remedio estoque[], int total){
	int encontrou = 0;
	printf("\n-------------------------\n");
	printf("REMEDIOS COM ESTOQUE BAIXO:\n");
	printf("-------------------------\n");

	for(int i = 0; i < total; i++){
		if(estoque[i].quantidade <= 5){
			printf("\tcodigo: %d\n\tnome: %s\n\tlaboratorio: %s\n\tquantidade: %d\n",
			estoque[i].codigo,
			estoque[i].nome,
			estoque[i].laboratorio,
			estoque[i].quantidade);
			printf("\n-------------------------\n");
			encontrou = 1;
		}
	}
	if(encontrou == 0){
		printf("nenhum remedio com estoque baixo.\n");
	}
}

void atualizarRemedio(Remedio estoque[], int total){
    int codigo;
    printf("\n-------------------------\n");
    printf("ATUALIZAR MEDICAMENTO:\n");
    printf("-------------------------\n");

    printf("digite o codigo: ");
    scanf("%d", &codigo);
    Remedio *r = buscar(estoque, total, codigo);
    if(r != NULL){

        printf("novo nome: ");
        scanf(" %[^\n]", r->nome);
        printf("novo laboratorio: ");
        scanf(" %[^\n]", r->laboratorio);
        printf("novo preco: ");
        scanf("%f", &r->preco);
        printf("nova quantidade: ");
        scanf("%d", &r->quantidade);
        printf("atualizado com sucesso!\n");
    }else{
        printf("medicamento nao encontrado.\n");
    }
}
