#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "remedio.h"
#include "cliente.h"

typedef struct{
    int codigoRemedio;
    int quantidade;
} ItemVenda;

typedef struct{
    int codigoVenda;
    int codigoCliente;
    ItemVenda *itens;
    int quantidadeItens;
} Venda;

Venda* inicializarVendas(int *total);

void registrarVenda(Venda **vendas, int *totalVendas, Remedio estoque[], int totalEstoque, Cliente clientes[], int totalClientes);

int carregarVendas(Venda vendas[], char *nomeArquivo);
void salvarVendas(Venda vendas[], int total, char *nomeArquivo);
void listarVendas(Venda vendas[], int total);
Venda *buscarVenda(Venda vendas[], int total, int codigo);
