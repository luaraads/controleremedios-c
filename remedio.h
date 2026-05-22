#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
	int codigo;
	char nome[100];
	char laboratorio[100];
	int quantidade;
	float preco;
} Remedio;

int cadastrar(Remedio **estoque, int *total);

void listar(Remedio estoque[], int total);

Remedio *buscar(Remedio estoque[], int total, int codigo);

Remedio *buscarPorNome(Remedio estoque[], int total, char nome[]);

void remover(Remedio **estoque, int *total);

int carregarEstoque(Remedio estoque[], char *nomeArquivo);

Remedio *inicializarEstoque(int *total);

void salvarEstoque(Remedio estoque[], int total, char *nomeArquivo);

void listarEstoqueBaixo(Remedio estoque[], int total);

void atualizarRemedio(Remedio estoque[], int total);