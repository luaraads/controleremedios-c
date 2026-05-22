#include"venda.h"
#include<stdio.h>
#include<stdlib.h>

int main(){

int opcaoPrincipal = 1;
int total = 0;
int codigo;
char nome[100];
char nomeArquivoEstoque[] = "estoque.txt";
Remedio *estoque = inicializarEstoque(&total);
Remedio *medicamentoEncontrado = NULL;
total = carregarEstoque(estoque, nomeArquivoEstoque);

int totalClientes = 0;
char nomeArquivoClientes[] = "clientes.txt";
Cliente *clientes = inicializarClientes(&totalClientes);
totalClientes = carregarClientes(clientes, nomeArquivoClientes);

int totalVendas = 0;
char nomeArquivoVendas[] = "vendas.txt";
Venda *vendas = inicializarVendas(&totalVendas);
totalVendas = carregarVendas(vendas, nomeArquivoVendas);

do{
	printf("\n---- SISTEMA DE CONTROLE DE FARMACIA ----\n");
	printf("\ndigite um numero equivalente as opcoes:\n\n1-gerenciar remedios\n2-gerenciar clientes\n3-gerenciar vendas\n0-sair\n");
	printf("\nopcao: ");
	scanf("%d", &opcaoPrincipal);
	getchar();

	switch(opcaoPrincipal){

	case 1:{
		int opcaoRemedio = 1;

		do{
			printf("\n---- MENU DE REMEDIOS ----\n");
			printf("\ndigite um numero equivalente as opcoes:\n\n1-cadastrar\n2-listar\n3-buscar por codigo\n4-buscar por nome\n5-atualizar\n6-remover\n7-listar estoque baixo\n8-salvar estoque\n0-voltar\n");

			printf("\nopcao: ");
			scanf("%d", &opcaoRemedio);
			getchar();

			switch(opcaoRemedio){

			case 1:
				cadastrar(&estoque, &total);
				salvarEstoque(estoque, total, nomeArquivoEstoque);
				break;

			case 2:
				listar(estoque, total);
				break;

			case 3:
				printf("\n-------------------------\n");
				printf("BUSCAR MEDICAMENTO NO ESTOQUE:\n");
				printf("-------------------------\n");
				printf("digite o codigo: ");
				scanf("%d", &codigo);
				medicamentoEncontrado = buscar(estoque, total, codigo);

				if(medicamentoEncontrado != NULL){
					int posicao = medicamentoEncontrado - estoque;
					printf("posicao no vetor: %d\n", posicao);
					printf("\tcodigo: %d\n\tnome: %s\n\tlaboratorio: %s\n\tpreco: %.2f\n\tquantidade: %d\n",
					medicamentoEncontrado->codigo,
					medicamentoEncontrado->nome,
					medicamentoEncontrado->laboratorio,
					medicamentoEncontrado->preco,
					medicamentoEncontrado->quantidade);
				}else{
					printf("medicamento nao encontrado.\n");
				}
				break;

			case 4:
				printf("\n-------------------------\n");
				printf("BUSCAR MEDICAMENTO NO ESTOQUE:\n");
				printf("-------------------------\n");
				printf("digite o nome: ");
				scanf(" %[^\n]", nome);
				medicamentoEncontrado = buscarPorNome(estoque, total, nome);

				if(medicamentoEncontrado != NULL){
					printf("\tcodigo: %d\n\tnome: %s\n\tlaboratorio: %s\n\tpreco: %.2f\n\tquantidade: %d\n",
					medicamentoEncontrado->codigo,
					medicamentoEncontrado->nome,
					medicamentoEncontrado->laboratorio,
					medicamentoEncontrado->preco,
					medicamentoEncontrado->quantidade);
				}else{
					printf("medicamento nao encontrado.\n");
				}
				break;

			case 5:
				atualizarRemedio(estoque, total);
				salvarEstoque(estoque, total, nomeArquivoEstoque);
				break;

			case 6:
				remover(&estoque, &total);
				salvarEstoque(estoque, total, nomeArquivoEstoque);
				break;

			case 7:
				listarEstoqueBaixo(estoque, total);
				break;

			case 8:
				salvarEstoque(estoque, total, nomeArquivoEstoque);
				printf("estoque salvo com sucesso!\n");
				break;

			case 0:
				printf("voltando...\n");
				break;

			default:
				printf("invalido.\n");
			}

		}while(opcaoRemedio != 0);
		break;
	}

	case 2:{
		int opcaoCliente = 1;

		do{
			printf("\n---- MENU CLIENTES ----\n");
			printf("\ndigite um numero equivalente as opcoes:\n\n1-cadastrar\n2-listar\n3-buscar por codigo\n4-buscar por nome\n5-atualizar\n6-remover\n7-salvar clientes\n0-voltar\n");

			printf("\nopcao: ");
			scanf("%d", &opcaoCliente);
			getchar();

			switch(opcaoCliente){

			case 1:
				cadastrarCliente(&clientes, &totalClientes);
				salvarClientes(clientes, totalClientes, nomeArquivoClientes);
				break;

			case 2:
				listarClientes(clientes, totalClientes);
				break;

			case 3:{
				int codigoCliente;
				printf("\ndigite o codigo: ");
				scanf("%d", &codigoCliente);

				Cliente *clienteEncontrado = buscarCliente(clientes, totalClientes, codigoCliente);

				if(clienteEncontrado != NULL){
					printf("\ncodigo: %d\nnome: %s\ncpf: %s\ntelefone: %s\n",
					clienteEncontrado->codigo,
					clienteEncontrado->nome,
					clienteEncontrado->cpf,
					clienteEncontrado->telefone);
				}else{
					printf("cliente nao encontrado.\n");
				}
				break;
			}

			case 4:{
				char nomeBusca[100];
				printf("digite o nome: ");
				scanf(" %[^\n]", nomeBusca);

				Cliente *c = buscarClienteNome(clientes, totalClientes, nomeBusca);

				if(c != NULL){
					printf("\ncodigo: %d\nnome: %s\ncpf: %s\ntelefone: %s\n",
					c->codigo, c->nome, c->cpf, c->telefone);
				}else{
					printf("cliente nao encontrado.\n");
				}
				break;
			}

			case 5:
				atualizarCliente(clientes, totalClientes);
				salvarClientes(clientes, totalClientes, nomeArquivoClientes);
				break;

			case 6:
				removerCliente(&clientes, &totalClientes);
				salvarClientes(clientes, totalClientes, nomeArquivoClientes);
				break;

			case 7:
				salvarClientes(clientes, totalClientes, nomeArquivoClientes);
				printf("clientes salvos com sucesso!\n");
				break;

			case 0:
				printf("voltando...\n");
				break;

			default:
				printf("invalido.\n");
			}

		}while(opcaoCliente != 0);
		break;
	}

	case 3:{
		int opcaoVenda = 1;

		do{
			printf("\n---- MENU VENDAS ----\n");
			printf("\ndigite um numero equivalente as opcoes:\n\n1-registrar venda\n2-listar vendas\n3-salvar vendas\n4-buscar venda\n0-voltar\n");

			printf("\nopcao: ");
			scanf("%d", &opcaoVenda);
			getchar();

			switch(opcaoVenda){

			case 1:
				registrarVenda(&vendas, &totalVendas, estoque, total, clientes, totalClientes);
				salvarVendas(vendas, totalVendas, nomeArquivoVendas);
				salvarEstoque(estoque, total, nomeArquivoEstoque);
				break;

			case 2:
				listarVendas(vendas, totalVendas);
				break;

			case 3:
				salvarVendas(vendas, totalVendas, nomeArquivoVendas);
				printf("vendas salvas com sucesso!\n");
				break;

			case 4:{
				int codigoVenda;
				printf("\ndigite o codigo da venda: ");
				scanf("%d", &codigoVenda);

				Venda *v = buscarVenda(vendas, totalVendas, codigoVenda);

				if(v != NULL){
					printf("\ncodigo da venda: %d\n", v->codigoVenda);
					printf("codigo do cliente: %d\n", v->codigoCliente);
					printf("quantidade de itens: %d\n", v->quantidadeItens);

					for(int i = 0; i < v->quantidadeItens; i++){
						printf("\nitem %d\n", i+1);
						printf("codigo remedio: %d\n", v->itens[i].codigoRemedio);
						printf("quantidade: %d\n", v->itens[i].quantidade);
					}

				}else{
					printf("venda nao encontrada.\n");
				}
				break;
			}

			case 0:
				printf("voltando...\n");
				break;

			default:
				printf("invalido.\n");
			}

		}while(opcaoVenda != 0);
		break;
	}

	case 0:
		salvarEstoque(estoque, total, nomeArquivoEstoque);
		salvarClientes(clientes, totalClientes, nomeArquivoClientes);
		salvarVendas(vendas, totalVendas, nomeArquivoVendas);
		printf("dados salvos com sucesso!\n");
		printf("saindo...\n");
		break;

	default:
		printf("invalido.\n");
	}

}while(opcaoPrincipal != 0);

free(estoque);
free(clientes);

for(int i = 0; i < totalVendas; i++){
	free(vendas[i].itens);
}

free(vendas);

return 0;
}