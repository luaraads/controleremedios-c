#include"venda.h"

Venda *inicializarVendas(int *total){
	Venda *vendas = (Venda*) malloc(100 * sizeof(Venda));
	if(vendas == NULL){
		printf("erro ao alocar memoria.\n");
		return NULL;
	}
	*total = 0;
	return vendas;
}

void registrarVenda(Venda **vendas, int *totalVendas,
	Remedio estoque[], int totalEstoque,
	Cliente clientes[], int totalClientes){

	printf("\n-------------------------\n");
	printf("REGISTRAR VENDA:\n");
	printf("-------------------------\n");
	
	int codigoCliente;
	printf("digite o codigo do cliente: ");
	scanf("%d", &codigoCliente);

	Cliente *clienteEncontrado = buscarCliente(clientes, totalClientes, codigoCliente);

	if(clienteEncontrado == NULL){
		printf("cliente nao encontrado.\n");
		return;
	}

	Venda *novaVenda = (Venda*) realloc(*vendas,
	((*totalVendas) + 1) * sizeof(Venda));
	if(novaVenda == NULL){
		printf("erro ao alocar memoria.\n");
		return;
	}

	*vendas = novaVenda;
	Venda *venda = &(*vendas)[*totalVendas];
	venda->codigoVenda = (*totalVendas) + 1;
	venda->codigoCliente = codigoCliente;
	venda->itens = NULL;
	venda->quantidadeItens = 0;
	int continuar = 1;

	while(continuar){
		int codigo;
		int quantidade;

		printf("digite o codigo do remedio: ");
		scanf("%d", &codigo);

		Remedio *medicamentoEncontrado = buscar(estoque, totalEstoque, codigo);

		if(medicamentoEncontrado != NULL){
			printf("digite a quantidade: ");
			scanf("%d", &quantidade);

			if(quantidade <= medicamentoEncontrado->quantidade){
				ItemVenda *novosItens = (ItemVenda*) realloc(
				venda->itens,
				(venda->quantidadeItens + 1) * sizeof(ItemVenda));

				if(novosItens == NULL){
					printf("erro ao alocar memoria.\n");
					return;
				}

				venda->itens = novosItens;
				venda->itens[venda->quantidadeItens].codigoRemedio = codigo;
				venda->itens[venda->quantidadeItens].quantidade = quantidade;
				venda->quantidadeItens++;
				medicamentoEncontrado->quantidade -= quantidade;
				printf("item adicionado na venda!\n");

			}else{
				printf("quantidade insuficiente no estoque.\n");
			}

		}else{
			printf("medicamento nao encontrado.\n");
		}
		printf("deseja adicionar outro remedio? (1-sim / 0-nao): ");
		scanf("%d", &continuar);
	}
	(*totalVendas)++;
	printf("venda registrada com sucesso!\n");
}

void listarVendas(Venda vendas[], int total){
	if(total == 0){
		printf("\nnenhuma venda cadastrada.\n");
		return;
	}
	printf("\n-------------------------\n");
	printf("LISTA DE VENDAS:\n");
	printf("-------------------------\n");

	for(int i = 0; i < total; i++){
		printf("\ncodigo da venda: %d\n",
		vendas[i].codigoVenda);
		printf("codigo do cliente: %d\n",
		vendas[i].codigoCliente);
		printf("quantidade de itens: %d\n",
		vendas[i].quantidadeItens);

		for(int j = 0; j < vendas[i].quantidadeItens; j++){
			printf("\nitem %d\n", j + 1);
			printf("codigo do remedio: %d\n",
			vendas[i].itens[j].codigoRemedio);
			printf("quantidade: %d\n",
			vendas[i].itens[j].quantidade);
		}
		printf("\n-------------------------\n");
	}
}

void salvarVendas(Venda vendas[], int total, char *nomeArquivo){
	FILE *arquivo = fopen(nomeArquivo, "w");
	if(arquivo == NULL){
		printf("erro ao salvar vendas.\n");
		return;
	}
	for(int i = 0; i < total; i++){
		fprintf(arquivo, "%d;%d;%d",
		vendas[i].codigoVenda,
		vendas[i].codigoCliente,
		vendas[i].quantidadeItens);

		for(int j = 0; j < vendas[i].quantidadeItens; j++){
			fprintf(arquivo, ";%d;%d",
			vendas[i].itens[j].codigoRemedio,
			vendas[i].itens[j].quantidade);
		}
		fprintf(arquivo, "\n");
	}
	fclose(arquivo);
}

int carregarVendas(Venda vendas[], char *nomeArquivo){
	FILE *arquivo = fopen(nomeArquivo, "r");
	if(arquivo == NULL){
		printf("arquivo de vendas nao encontrado.\n");
		return 0;
	}
	int total = 0;
	while(fscanf(arquivo, "%d;%d;%d",
		&vendas[total].codigoVenda,
		&vendas[total].codigoCliente,
		&vendas[total].quantidadeItens) == 3){
		vendas[total].itens = (ItemVenda*)
		malloc(vendas[total].quantidadeItens * sizeof(ItemVenda));

		for(int i = 0; i < vendas[total].quantidadeItens; i++){
			fscanf(arquivo, ";%d;%d",
			&vendas[total].itens[i].codigoRemedio,
			&vendas[total].itens[i].quantidade);
		}

		fscanf(arquivo, "\n");
		total++;
	}
	fclose(arquivo);
	return total;
}

Venda *buscarVenda(Venda vendas[], int total, int codigo){
    for(int i = 0; i < total; i++){
        if(vendas[i].codigoVenda == codigo){
            return &vendas[i];
        }
    }
    return NULL;
}