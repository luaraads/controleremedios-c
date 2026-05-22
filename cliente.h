#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int codigo;
    char nome[100];
    char cpf[20];
    char telefone[20];
} Cliente;

Cliente* inicializarClientes(int *total);
int cadastrarCliente(Cliente **clientes, int *total);
void listarClientes(Cliente clientes[], int total);
Cliente* buscarCliente(Cliente clientes[], int total, int codigo);
Cliente *buscarClienteNome(Cliente clientes[], int total, char nome[]);
void atualizarCliente(Cliente clientes[], int total);
void removerCliente(Cliente **clientes, int *total);

int carregarClientes(Cliente clientes[], char *nomeArquivo);
void salvarClientes(Cliente clientes[], int total, char *nomeArquivo);
