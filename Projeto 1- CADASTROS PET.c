#include<stdio.h>
#include<stdlib.h>
#include<string.h> //para usar stricmp -  para compara STRINGS com letras maiusculas e minusculas
#include<ctype.h> // para usar toupper - para comparar CARACTERES maisculos e minusculos
#include<locale.h>
#include "tela.h"

typedef struct tno no;

struct tno
{
    int id;

    char nome[20];
    char especie [20];
    char raca [30];
    char sexo;
    int idade;
    char carac_g [120];


    struct tno *prox;

};

// AS FUNÇÕES DE TOTAL DE REGISTROS E DE QUANTIDADE POR ESPÉCIE ESTÃO EMBUTIDAS:

void novo_cadastro(no**inicio, int *cont_total, int *num_id);
void alterar_cadastro(no **inicio);
void remover_cadastro(no **inicio, int *cont_total);
void busca_nome(no *inicio);
void busca_especie(no *inicio); // AQUI - CONTEM A QUANTIDADE POR ESPÉCIE
void busca_raca_especie(no *inicio);
void busca_raca_especie_sexo(no *inicio);
void lista_total(no *inicio, int cont_total); // AQUI - CONTEM O TOTAL DE REGISTROS
void salvar_arquivo(no *inicio, FILE *arq, FILE *cont, int cont_total, int num_id);


int main ()
{
    setlocale(LC_ALL,"portuguese");

    int menu;
    int cont_total=0; // contagem de todos os registros atuais, é modificada ao retirar um cadastro
    int num_id=0; // variavel para poder dar números aos registros, não é modificada ao retirar um cadastro

    no *inicio = (no*)malloc(sizeof(no));

     if(inicio==NULL)
        {
            printf("HEAP OVERFLOW");
            exit(1);
        }

    //inicio->id=num_id; // inicialmente o id é 0 pois não há registros ainda
    inicio->prox=NULL;

    //CRIANDO ARQUIVO

    FILE *cont; // guarda os contadores de total de registros e numero do id

    cont=fopen("Contadores.txt", "r+");


    if(cont==NULL) // se não existe arquivo, cria
    {
        cont=fopen("Contadores.txt", "w+");
    }
    else
    {
        fscanf(cont,"%d %d",&cont_total,&num_id);

        //printf("Total de Registros %d | Último ID registrado: %d\n\n\n",cont_total,num_id);

        fclose(cont);
    }



    FILE *arq; // guarda os registros

    arq=fopen("Arquivo_PETS.txt", "r+");


    if(arq==NULL) // se não existe arquivo, cria
    {
        arq=fopen("Arquivo_PETS.txt", "w+");

    }
    else
    {
        no *novo;

        for(int i=0;i<cont_total;i++)
        {
            novo=(no*)malloc(sizeof(no));

            if(novo==NULL)
            {
            printf("HEAP OVERFLOW");
            exit(1);
            }

            fscanf(arq, "%d %s %s %s %c %d %s",&novo->id,&novo->nome,&novo->especie,&novo->raca,&novo->sexo,&novo->idade,&novo->carac_g);

            //printf("%d %s %s %s %c %d %s\n",novo->id,novo->nome,novo->especie,novo->raca,novo->sexo,novo->idade,novo->carac_g);

            novo->prox=inicio;
            inicio=novo;

        }


        fclose(arq);


        //printf("\n\n\n\t");
        //system("pause");
        //clrscr();
    }



    do
    {
        gotoxy(2,5); // põe o rpint na linha 0 e coluna 30
        textcolor (CIANO); // muda cor do texto
        printf("Cadastro de PETS");


        textcolor (BRANCO);
        gotoxy(2,35);
        printf("MENU");

        gotoxy(4,25);
        printf("1. Cadastrar um novo PET");
        gotoxy(6,25);
        printf("2. Alterar um cadastro");
        gotoxy(8,25);
        printf("3. Remover um cadastro");
        gotoxy(10,25);
        printf("4. Busca por nome");
        gotoxy(12,25);
        printf("5. Busca por espécie");
        gotoxy(14,25);
        printf("6. Busca por espécie e raça");
        gotoxy(16,25);
        printf("7. Busca por espécie, raça, sexo");
        gotoxy(18,25);
        printf("8. Visualizar todos os cadastros");
        gotoxy(20,25);
        textcolor(VERDE);
        printf("9. SALVAR DADOS");
        gotoxy(22,25);
        textcolor(VERMELHO);
        printf("0. SALVAR E SAIR");

        gotoxy(25,25);
        textcolor(BRANCO);
        printf("Digite a opcão: ");
        scanf("%d",&menu);



        switch (menu)
        {
            case 1:
            clrscr();
            novo_cadastro(&inicio, &cont_total, &num_id); //passando endereco '&'
            break;

            case 2:
            clrscr();
            alterar_cadastro(&inicio);
            break;

            case 3:
            clrscr();
            remover_cadastro(&inicio, &cont_total);
            break;

            case 4:
            clrscr();
            busca_nome(inicio);
            break;

            case 5:
            clrscr();
            busca_especie(inicio);
            break;

            case 6:
            clrscr();
            busca_raca_especie(inicio);
            break;

            case 7:
            clrscr();
            busca_raca_especie_sexo(inicio);
            break;

            case 8:
            clrscr();
            lista_total(inicio, cont_total);
            break;

            case 9:
            clrscr();
            salvar_arquivo(inicio, arq, cont, cont_total, num_id);
            textcolor (VERDE);
            printf("\n\n\tRegistros Salvos com Sucesso!");
            textcolor (BRANCO);
            printf("\n\n\n\t");
            system("pause");
            clrscr();
            break;

            case 0:
            printf("\n\n");
            salvar_arquivo(inicio, arq, cont, cont_total, num_id);
            exit(1);

            default:
            gotoxy(26,5);
            textcolor (VERMELHO);
            printf("\n\tOpção Inválida - ");
            system("pause");
            textcolor (BRANCO);
            clrscr();
            break;
        }

    }while(menu!=0);


    printf("\n\n\n");
    system("pause");
    return 0;

}

void novo_cadastro(no** inicio, int *cont_total,int *num_id)
{
   no *aux; //declarando aux

   gotoxy(1,10);
   printf("Novo Cadastro");

    aux=(no*)malloc(sizeof(no)); //alocando memoria aux

        if(aux==NULL)
        {
            printf("HEAP OVERFLOW");
            exit(1);
        }

        (*num_id)++; // ao inserir um registro, o id é somado e é atrubuido ao novo PET
        aux->id=(*num_id);

        gotoxy(4,10);
        printf("Nome do PET: ");
        fflush(stdin);
        gets(aux->nome);
        gotoxy(6,10);
        printf("Espécie: ");
        fflush(stdin);
        gets(aux->especie);
        gotoxy(8,10);
        printf("Raça: ");
        fflush(stdin);
        gets(aux->raca);
        gotoxy(10,10);
        printf("Sexo (f ou m): ");
        fflush(stdin);
        scanf("%c",&aux->sexo);
        gotoxy(12,10);
        printf("Idade: ");
        fflush(stdin);
        scanf("%d",&aux->idade);
        gotoxy(14,10);
        printf("Características Gerais: ");
        fflush(stdin);
        gets(aux->carac_g);

         aux->prox=(*inicio);
        (*inicio)=aux;

        (*cont_total)++;

        gotoxy(18,10);
        textcolor (VERDE); // muda cor do texto para verde
        printf("Cadastro realizado com sucesso!");

        gotoxy(22,10);
        textcolor (BRANCO); // volta a cor do texto para branco
        system("pause");
        clrscr();
}


void alterar_cadastro(no **inicio)
{
    char n_alt[20];
    int cont_encontrados=0;
    int id_busca;

    gotoxy(2,10);
    printf("Digite o nome do PET: ");
    fflush(stdin);
    gets(n_alt);
    no * aux_busca;
    aux_busca=(*inicio);

    while (aux_busca->prox != NULL)
    {

       if(_stricmp(aux_busca->nome,n_alt)==0)
        {

        printf("\n\n\t");
        textcolor (ROSA);
        printf("ID do PET: %d",aux_busca->id);
        textcolor (BRANCO);
        printf("\n\t");
        printf("Nome: %s",aux_busca->nome);
        printf("\n\t");
        printf("Espécie: %s",aux_busca->especie);
        printf("\n\t");
        printf("Raça: %s",aux_busca->raca);
        printf("\n\t");
        printf("Sexo (f ou m): %c",aux_busca->sexo);
        printf("\n\t");
        printf("Idade: %d",aux_busca->idade);
        printf("\n\t");
        printf("Características Gerais: %s",aux_busca->carac_g);

        cont_encontrados++;

        }
        aux_busca=aux_busca->prox; //varrendo a lista
    }

    if(cont_encontrados==0)
    {
        textcolor (VERMELHO);
        gotoxy(5,10);
        printf("Registro não encontrado!");
    }
    else
    {
        printf("\n\n\n\t");
        textcolor (CIANO);
        printf("%d registro(s) encontrado(s)",cont_encontrados);
        textcolor (BRANCO);
        printf("\n\n\tDigite o ID do registro que deseja ALTERAR: ");
        scanf("%d", &id_busca);

        no *aux;
        aux=(*inicio);

        printf("\n\n\t\t");
        textcolor(AMARELO);
        printf("Alterar cadastro\n\n");
        textcolor(BRANCO);

        while (aux->id != id_busca)
        {
            aux=aux->prox;
        }

        printf("\n\t");
        printf("Nome do PET: ");
        fflush(stdin);
        gets(aux->nome);
        printf("\n\t");
        printf("Espécie: ");
        fflush(stdin);
        gets(aux->especie);
        printf("\n\t");
        printf("Raça: ");
        fflush(stdin);
        gets(aux->raca);
        printf("\n\t");
        printf("Sexo (f ou m): ");
        fflush(stdin);
        scanf("%c",&aux->sexo);
        printf("\n\t");
        printf("Idade: ");
        fflush(stdin);
        scanf("%d",&aux->idade);
        printf("\n\t");
        printf("Características Gerais: ");
        fflush(stdin);
        gets(aux->carac_g);

        textcolor (VERDE);
        printf("\n\n\tAlteração concluída com sucesso!");

    }


    textcolor (BRANCO);
    printf("\n\n\n\t");
    system("pause");
    clrscr();

}

void remover_cadastro(no **inicio, int *cont_total)
{
    char n_alt[20];
    int cont_encontrados=0;
    int id_busca;

    gotoxy(2,10);
    printf("Digite o nome do PET: ");
    fflush(stdin);
    gets(n_alt);
    no * aux_busca;
    aux_busca=(*inicio);

    while (aux_busca->prox != NULL)
    {

       if(_stricmp(aux_busca->nome,n_alt)==0)
        {

        printf("\n\n\t");
        textcolor (ROSA);
        printf("ID do PET: %d",aux_busca->id);
        textcolor (BRANCO);
        printf("\n\t");
        printf("Nome: %s",aux_busca->nome);
        printf("\n\t");
        printf("Espécie: %s",aux_busca->especie);
        printf("\n\t");
        printf("Raça: %s",aux_busca->raca);
        printf("\n\t");
        printf("Sexo (f ou m): %c",aux_busca->sexo);
        printf("\n\t");
        printf("Idade: %d",aux_busca->idade);
        printf("\n\t");
        printf("Características Gerais: %s",aux_busca->carac_g);

        cont_encontrados++;

        }
        aux_busca=aux_busca->prox; //varrendo a lista
    }


    if(cont_encontrados==0)
    {
        textcolor (VERMELHO);
        gotoxy(5,10);
        printf("Registro não encontrado!");
    }
    else
    {
        printf("\n\n\n\t");
        textcolor (CIANO);
        printf("%d registro(s) encontrado(s)",cont_encontrados);
        textcolor (BRANCO);
        printf("\n\n\tDigite o ID do registro que deseja REMOVER: ");
        scanf("%d", &id_busca);

        no *aux;
        no *aux2;
        aux=(*inicio);

        if((*inicio)->id == id_busca) //remover o primeiro
        {
            *inicio= (*inicio)->prox;
            free(aux);
            *cont_total=(*cont_total)-1;
        }
        else
        {
            while (aux->prox->id != id_busca)
            {
            aux=aux->prox;
            }

            if(aux->prox->prox==NULL) //remover o ultimo
            {
               aux2=aux->prox;
               aux->prox=NULL;
               free(aux2);
               *cont_total=(*cont_total)-1;
            }
            else // remover no meio
            {
                aux2=aux->prox->prox;
                aux->prox=aux2;
                free(aux->prox);
                *cont_total=(*cont_total)-1;
            }


        }

        textcolor (VERDE);
        printf("\n\n\tRemoção concluída com sucesso!");

    }
    textcolor (BRANCO);
    printf("\n\n\n\t");
    system("pause");
    clrscr();

}

void busca_nome(no *inicio)
{
    char n_busca[20];
    int cont_encontrados=0;
    int id_busca;

    gotoxy(2,10);
    printf("Digite o nome do PET que desejar visualizar: ");
    fflush(stdin);
    gets(n_busca);

    no * aux_busca;
    aux_busca=inicio;

    while (aux_busca->prox != NULL)
    {

       if(_stricmp(aux_busca->nome,n_busca)==0)
        {

        printf("\n\n\t");
        printf("ID do PET: %d",aux_busca->id);
        textcolor (ROSA);
        printf("\n\t");
        printf("Nome: %s",aux_busca->nome);
        textcolor (BRANCO);
        printf("\n\t");
        printf("Espécie: %s",aux_busca->especie);
        printf("\n\t");
        printf("Raça: %s",aux_busca->raca);
        printf("\n\t");
        printf("Sexo (f ou m): %c",aux_busca->sexo);
        printf("\n\t");
        printf("Idade: %d",aux_busca->idade);
        printf("\n\t");
        printf("Características Gerais: %s",aux_busca->carac_g);

        cont_encontrados++;

        }
        aux_busca=aux_busca->prox; //varrendo a lista
    }

    if(cont_encontrados==0)
    {
        textcolor (VERMELHO);
        gotoxy(5,10);
        printf("Registro não encontrado!");
        textcolor (BRANCO);
    }
    else
    {
        textcolor (CIANO);
        printf("\n\n\t");
        printf(" %d registro(s) encontrado(s)",cont_encontrados);
        textcolor (BRANCO);
    }

    printf("\n\n\n\t");
    system("pause");
    clrscr();

}

void busca_especie(no *inicio)
{
    char e_busca[20];
    int cont_encontrados=0;
    int id_busca;

    gotoxy(2,10);
    printf("Digite a espécie do PET que desejar visualizar: ");
    fflush(stdin);
    gets(e_busca);

    no * aux_busca;
    aux_busca=inicio;

    while (aux_busca->prox != NULL)
    {

       if(_stricmp(aux_busca->especie,e_busca)==0)
        {

        printf("\n\n\t");
        printf("ID do PET: %d",aux_busca->id);
        printf("\n\t");
        printf("Nome: %s",aux_busca->nome);
        textcolor (ROSA);
        printf("\n\t");
        printf("Espécie: %s",aux_busca->especie);
        textcolor (BRANCO);
        printf("\n\t");
        printf("Raça: %s",aux_busca->raca);
        printf("\n\t");
        printf("Sexo (f ou m): %c",aux_busca->sexo);
        printf("\n\t");
        printf("Idade: %d",aux_busca->idade);
        printf("\n\t");
        printf("Características Gerais: %s",aux_busca->carac_g);

        cont_encontrados++;

        }
            aux_busca=aux_busca->prox; //varrendo a lista
    }

    if(cont_encontrados==0)
    {
        textcolor (VERMELHO);
        gotoxy(5,10);
        printf("Registro não encontrado!");
        textcolor (BRANCO);
    }
    else
    {
        printf("\n\n\n\t");
        textcolor(CIANO);
        printf("Total de registros da espécie '%s' : %d",e_busca, cont_encontrados); // FUNCIONALIDADE DE QUANTIDADE POR ESPÉCIE
    }

    textcolor(BRANCO);
    printf("\n\n\n\t");
    system("pause");
    clrscr();

}


void busca_raca_especie(no *inicio)
{
    char e_busca[20];
    char r_busca[20];
    int cont_encontrados=0;
    int id_busca;

    gotoxy(2,10);
    printf("Digite a espécie do PET que desejar visualizar: ");
    fflush(stdin);
    gets(e_busca);
    gotoxy(4,10);
    printf("Digite a raça do PET que desejar visualizar: ");
    fflush(stdin);
    gets(r_busca);

    no * aux1;
    no *aux2;

    aux1=inicio;
    aux2=inicio;

    while (aux1->prox != NULL)
    {

       if((_stricmp(aux1->especie,e_busca)==0 )&& (_stricmp(aux2->raca,r_busca)==0 ))
        {

        printf("\n\n\t");
        printf("ID do PET: %d",aux1->id);
        printf("\n\t");
        printf("Nome: %s",aux1->nome);
        textcolor (ROSA);
        printf("\n\t");
        printf("Espécie: %s",aux1->especie);
        printf("\n\t");
        printf("Raça: %s",aux1->raca);
        textcolor (BRANCO);
        printf("\n\t");
        printf("Sexo (f ou m): %c",aux1->sexo);
        printf("\n\t");
        printf("Idade: %d",aux1->idade);
        printf("\n\t");
        printf("Características Gerais: %s",aux1->carac_g);

        cont_encontrados++;

        }

            aux1=aux1->prox; //varrendo a lista
            aux2=aux2->prox;
    }

    if(cont_encontrados==0)
    {
        textcolor (VERMELHO);
        gotoxy(7,10);
        printf("Registro não encontrado!");
        textcolor (BRANCO);
    }
    else
    {
        textcolor(CIANO);
        printf("\n\n\t");
        printf(" %d registro(s) encontrado(s)",cont_encontrados);
    }

    textcolor(BRANCO);
    printf("\n\n\n\t");
    system("pause");
    clrscr();

}

void busca_raca_especie_sexo(no *inicio)
{
    char e_busca[20];
    char r_busca[20];
    char s_busca;
    int cont_encontrados=0;
    int id_busca;

    gotoxy(2,10);
    printf("Digite a espécie do PET que desejar visualizar: ");
    fflush(stdin);
    gets(e_busca);
    gotoxy(4,10);
    printf("Digite a raça do PET que desejar visualizar: ");
    fflush(stdin);
    gets(r_busca);
    gotoxy(6,10);
    printf("Digite o sexo do PET que desejar visualizar: ");
    fflush(stdin);
    scanf("%c", &s_busca);

    no * aux1;
    no *aux2;
    no *aux3;

    aux1=inicio;
    aux2=inicio;
    aux3=inicio;


    while (aux1->prox != NULL)
    {

       if((_stricmp(aux1->especie,e_busca)==0 )&& (_stricmp(aux2->raca,r_busca)==0 ) && (toupper(aux3->sexo) == toupper(s_busca)))
        {

        printf("\n\n\t");
        printf("ID do PET: %d",aux1->id);
        printf("\n\t");
        printf("Nome: %s",aux1->nome);
        textcolor (ROSA);
        printf("\n\t");
        printf("Espécie: %s",aux1->especie);
        printf("\n\t");
        printf("Raça: %s",aux1->raca);
        printf("\n\t");
        printf("Sexo (f ou m): %c",aux1->sexo);
        textcolor (BRANCO);
        printf("\n\t");
        printf("Idade: %d",aux1->idade);
        printf("\n\t");
        printf("Características Gerais: %s",aux1->carac_g);

        cont_encontrados++;

        }
        aux1=aux1->prox; //varrendo a lista
        aux2=aux2->prox;
        aux3=aux3->prox;
    }

    if(cont_encontrados==0)
    {
        textcolor (VERMELHO);
        gotoxy(9,10);
        printf("Registro não encontrado!");
        textcolor (BRANCO);
    }
    else
    {
        textcolor(CIANO);
        printf("\n\n\t");
        printf(" %d registro(s) encontrado(s)",cont_encontrados);
    }

    textcolor(BRANCO);
    printf("\n\n\n\t");
    system("pause");
    clrscr();
}

void lista_total(no *inicio, int cont_total)
{
    no *aux;
    aux=inicio;
    textcolor (CIANO);
    gotoxy(1,25);
    printf("Total de registros: %d", cont_total);
    gotoxy(3,2);
    textcolor (VERDE);
    printf("LISTA DOS REGISTROS");
    while(aux->prox != NULL)
    {

        printf("\n\n\t");
        textcolor (ROSA);
        printf("ID do PET: %d",aux->id);
        textcolor (BRANCO);
        printf("\n\t");
        printf("Nome: %s",aux->nome);
        printf("\n\t");
        printf("Espécie: %s",aux->especie);
        printf("\n\t");
        printf("Raça: %s",aux->raca);
        printf("\n\t");
        printf("Sexo (f ou m): %c",aux->sexo);
        printf("\n\t");
        printf("Idade: %d",aux->idade);
        printf("\n\t");
        printf("Características Gerais: %s",aux->carac_g);
        aux=aux->prox;
    }


        printf("\n\n\t\t\t");
        textcolor (VERMELHO);
        printf("--------FIM DA LISTA--------");

        textcolor (BRANCO);
        printf("\n\n\n\t");
        system("pause");
        clrscr();


}


void salvar_arquivo(no *inicio, FILE *arq, FILE *cont, int cont_total, int num_id)
{
    no *aux;
    aux = inicio;


    cont=fopen("Contadores.txt", "r+");

    fprintf(cont, "%d %d\n",cont_total,num_id);

    //printf("Total de Registros %d | Último ID registrado: %d\n\n\n",cont_total,num_id);

    fclose(cont);



    arq=fopen("Arquivo_PETS.txt", "r+");

    while(aux->prox != NULL)
    {
        fprintf(arq, "%d %s %s %s %c %d %s\n",aux->id,aux->nome,aux->especie,aux->raca,aux->sexo,aux->idade,aux->carac_g);

        //printf("%d %s %s %s %c %d %s\n",aux->id,aux->nome,aux->especie,aux->raca,aux->sexo,aux->idade,aux->carac_g);

        aux=aux->prox;
    }

    fclose(arq);
}
