#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <locale.h>
#include <string.h>

typedef struct produto PRODUTO;

struct produto{
	char id[5];
	char descricao[30];
	char marca[20];
	char categoria[20];
	int estoque;
	float valor;	
};

void cabecalho();
void inserir();
void pesquisar();
void editar();
void remover();
void listar();

main() {
	setlocale(LC_ALL, "Portuguese");
	int opcao;
	
	do{
		cabecalho();
		printf("1 - Inserir novo produto\n");
		printf("2 - Exibir\n");
		printf("3 - Editar produto\n");
		printf("4 - Deletar registro\n");
		printf("5 - Listar produtos\n");
		printf("6 - Sair\n\n");
		scanf("%d",&opcao);
		
		switch (opcao){
			case 1: 
			inserir();
			break;
			
			case 2: 
			pesquisar();
			break;
			
			case 3: 
			editar();
			break;

			case 4: 
			remover();
			break;

			case 5: 
			listar();
			break;

			case 6: 
			printf("Obrigado por sua visita!\n");
			getch();
			break;
			
			default:
			printf("Op��o inv�lida\n");
			getch();
			break;		
		}		
	} while (opcao != 6);
}

void cabecalho() {
	system("cls");
	printf("----------------------------------------\n");
	printf("CADASTRO DE PRODUTOS\n");
	printf("----------------------------------------\n\n");
}

void inserir() {
	FILE* arquivo;
	PRODUTO prod;
	
	arquivo = fopen("cadastro.txt", "a");
	
	if(arquivo == NULL)
	{
		printf("Problemas na abertura do arquivo.\n");
	} 
	else
	{
		do
		{
		cabecalho();
		
		fflush(stdin);
		printf("Digite o ID: ");
		gets(prod.id);
		
		fflush(stdin);
		printf("Digite a descri��o: ");
		gets(prod.descricao);

		fflush(stdin);
		printf("Digite a marca: ");
		gets(prod.marca);	
		
		fflush(stdin);
		printf("Digite a categoria do item: ");
		gets(prod.categoria);
		
		fflush(stdin);
		printf("Digite o estoque do item: ");
		scanf("%d", &prod.estoque);
		
		fflush(stdin);
		printf("Digite o valor: ");
		scanf("%f", &prod.valor);
		
		fwrite(&prod, sizeof(PRODUTO), 1, arquivo);
		
		printf("\nDeseja continuar (s/n)? ");
		} while (getche() == 's');
		fclose(arquivo);
	}
}

void pesquisar(){
	FILE* arquivo;
	PRODUTO prod;
	char id[5];
	
	cabecalho();
	arquivo = fopen("cadastro.txt", "r");
	
	if(arquivo == NULL) {
		printf("Problemas na abertura do arquivo.\n");
	} 
	else
	{
		cabecalho();
		fflush(stdin);
		printf("Digite o ID do produto: ");
		gets(id);
		
		while(fread(&prod, sizeof(PRODUTO), 1, arquivo) == 1) {
			if(strcmp(id, prod.id) == 0) {
				cabecalho();
				printf("ID: %s\n", prod.id);
				printf("Descri��o: %s\n", prod.descricao);
				printf("Marca: %s\n", prod.marca);
				printf("Categoria: %s\n", prod.categoria);
				printf("Estoque: %d\n", prod.estoque);
				printf("Valor: %.2f\n", prod.valor);
				printf("----------------------------------------\n\n");
			}
		}
	}
	
	fclose(arquivo);
	getch();
	
}

void editar(){
	FILE* arquivo;
	FILE* temp;
	PRODUTO prod;
	char id[5];	
	
	arquivo = fopen("cadastro.txt", "r");
	temp = fopen("temp.txt", "w");
	
	if(arquivo == NULL && temp == NULL) {
		printf("Problemas na abertura do arquivo.");
		getch();
	} else {
		cabecalho();
		fflush(stdin);
		printf("Digite o ID do produto a editar: ");
		gets(id);	
		
		while (fread(&prod, sizeof(PRODUTO), 1, arquivo) == 1) {
			if(strcmp(id, prod.id) == 0) {
				printf("ID: %s\n", prod.id);
				printf("Descri��o: %s\n", prod.descricao);
				printf("Marca: %s\n", prod.marca);
				printf("Categoria: %s\n", prod.categoria);
				printf("Estoque: %d\n", prod.estoque);
				printf("Valor: %.2f\n", prod.valor);
				printf("----------------------------------------\n\n");
			} else {
				fwrite(&prod, sizeof(PRODUTO), 1, temp);
			}
		}
			
	
	fclose(arquivo);
	fclose(temp);
	fflush(stdin);
	printf("Tem certeza que deseja alterar este produto (s/n)? ");
	if(getche() == 's') {
		if(remove("cadastro.txt") == 0 && rename ("temp.txt", "cadastro.txt") == 0) {
		FILE* arquivo;
		PRODUTO prod;

		arquivo = fopen("cadastro.txt", "a");

		fflush(stdin);
		printf("\nDigite o ID atualizado: ");
		gets(prod.id);
				
		fflush(stdin);
		printf("Digite a descri��o do novo item: ");
		gets(prod.descricao);

		fflush(stdin);
		printf("Digite a marca do novo item: ");
		gets(prod.marca);

		fflush(stdin);
		printf("Digite a categoria do novo item: ");
		gets(prod.categoria);
		
		fflush(stdin);
		printf("Digite o estoque do novo item: ");
		scanf("%d", &prod.estoque);
		
		fflush(stdin);
		printf("Digite o valor do novo item: ");
		scanf("%f", &prod.valor);
		
		fwrite(&prod, sizeof(PRODUTO), 1, arquivo);
		
		printf("\nItem alterado com sucesso!");
					
			} else {
				remove("temp.txt");
			}
		}
	
	fclose(arquivo);
	fclose(temp);
	getch();
	}	
}

void remover() {
	FILE* arquivo;
	FILE* temp;
	PRODUTO prod;
	char id[5];	
	
	arquivo = fopen("cadastro.txt", "r");
	temp = fopen("temp.txt", "wb");
	
	if(arquivo == NULL && temp == NULL) {
		printf("Problemas na abertura do arquivo.");
		getch();
	} else{
		cabecalho();
		fflush(stdin);
		printf("Digite o ID do produto a deletar: ");
		gets(id);
		
	while(fread(&prod, sizeof(PRODUTO), 1, arquivo) == 1) {
		if(strcmp(id, prod.id) == 0){
			cabecalho();
			printf("ID: %s\n", prod.id);
			printf("Descri��o: %s\n", prod.descricao);
			printf("Marca: %s\n", prod.marca);
			printf("Categoria: %s\n", prod.categoria);
			printf("Estoque: %d\n", prod.estoque);
			printf("Valor: %.2f\n", prod.valor);
			printf("----------------------------------------\n\n");			
		} else{
			fwrite(&prod, sizeof(PRODUTO), 1, temp); //gravar o registro no arquivo temp.txt
		}
	}
	}
	
	fclose(arquivo);
	fclose(temp);	
	fflush(stdin);
	
	printf("Deseja deletar (s/n)? ");

	if(getche() == 's') {
		if(remove("cadastro.txt") == 0 && rename("temp.txt","cadastro.txt") == 0) {
			printf("\nOpera��o realizada com sucesso!");
		} else {
			remove("temp.txt");
		}
	}
	fclose(arquivo);
	fclose(temp);
	getch();
}

void listar() {
	FILE* arquivo;
	PRODUTO prod;
	
	arquivo = fopen("cadastro.txt", "r");
	
	cabecalho();
	if(arquivo == NULL)
	{
		printf("Problemas na abertura do arquivo.\n");
	} else
	{
		while(fread(&prod, sizeof(PRODUTO), 1, arquivo) == 1){
			printf("ID: %s\n", prod.id);
			printf("Descri��o: %s\n", prod.descricao);
			printf("Marca: %s\n", prod.marca);
			printf("Categoria: %s\n", prod.categoria);
			printf("Estoque: %d\n", prod.estoque);
			printf("Valor: %.2f\n", prod.valor);
			printf("----------------------------------------\n\n");
		}
	}
	fclose(arquivo);
	getch();
}
