
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "produto.h"

#define PRODUTO_VALIDO      (1)
#define PRODUTO_INVALIDO    (0)

#define AUTO_INCREMENTO_ID  (1)

static const char *nomeArquivoProduto= "produtos.dat";

static int obter_proximo_id();

void exibir_produto( produto* prod )
{
    printf( "\n ------------------------ " );
    printf( "\n ID:      %d", prod->id );
    printf( "\n NOME:    %s", prod->nome );
    printf( "\n PRECO:   %.2f", prod->preco_unitario );
    printf( "\n ESTOQUE: %d", prod->estoque );
    printf( "\n ------------------------ \n" );
}

void anexar_produto( produto* registro )
{
    anexar_registro( ( char* ) nomeArquivoProduto, registro, sizeof( produto ) );
}

int ler_produto( produto* registro, int pos )
{
    return ler_registro( ( char* ) nomeArquivoProduto, registro, sizeof( produto ), pos );
}

produto cadastrar_produto()
{
    produto novoProduto;
    printf( "\n Cadastro de novo produto: \n" );
    #if AUTO_INCREMENTO_ID
    novoProduto.id= obter_proximo_id() + 1;
    printf( " ID = %d\n", novoProduto.id );
    #else
    //printf( " Digite o ID: " ); scanf( "%d", &novoProduto.id );
    #endif // AUTO_INCREMENTO_ID
    printf( " Digite o nome: " );
    char nome[ LIMITE_CARACTERES ];
    fflush( stdin );
    gets( nome );
    strcpy( novoProduto.nome, nome );
    printf( " Digite o preco unitario: " );
    scanf( "%f", &novoProduto.preco_unitario );
    novoProduto.estoque= 0;
    novoProduto.valido= PRODUTO_VALIDO;
    anexar_produto( &novoProduto );
    return novoProduto;
}

void apagar_todos_produtos()
{
    FILE *arquivo= fopen( nomeArquivoProduto, "wb" );
    fclose( arquivo );
}

void listar_produtos()
{
    int contador= 0;
    if ( tamanho_arquivo( ( char* ) nomeArquivoProduto ) == 0 )
    {
        printf( "\n\n Lista de produtos vazia. \n\n" );
        return;
    }
    produto prod;
    FILE *arquivo= fopen( nomeArquivoProduto, "rb" );
    while ( fread( &prod, sizeof( produto ), 1, arquivo ) == 1 )
    {
        if ( prod.valido )
        {
            exibir_produto( &prod );
            ++contador;
        }
    }
    fclose( arquivo );
    printf( "\n Existe(m) %d registro(s) de produto(s).\n\n", contador );
}

produto obter_produto( int id )
{
    produto resultado;
    resultado.valido= PRODUTO_INVALIDO;
    if ( tamanho_arquivo( ( char* ) nomeArquivoProduto ) == 0 )
    {
        printf( "\n\n Lista de produtos vazia. \n\n" );
        return resultado;
    }
    FILE *arquivo= fopen( nomeArquivoProduto, "rb" );
    while ( fread( &resultado, sizeof( produto ), 1, arquivo ) == 1 )
    {
        if ( resultado.valido && resultado.id == id )
        {
            fclose( arquivo );
            return resultado;
        }
    }
    fclose( arquivo );
    printf( "\n Produto de ID %d nao encontrado.\n", id );
    resultado.valido= PRODUTO_INVALIDO;
    return resultado;
}

void atualizar_estoque( int id, int estoque )
{
    produto registro= obter_produto( id );
    if ( registro.valido )
    {
        registro.estoque= estoque;
        FILE *arquivo= fopen( ( char* ) nomeArquivoProduto, "rb+" );
        while ( fread( &registro, sizeof( produto ), 1, arquivo ) == 1 )
        {
            if ( registro.id == id )
            {
                registro.estoque= estoque;
                fseek( arquivo, (long) - sizeof( produto ), SEEK_CUR );
                fwrite( &registro, sizeof( produto ), 1, arquivo );
                break;
            }
        }
        fclose( arquivo );
    }
}

int obter_proximo_id()
{
    int id= 0;
    FILE *arquivo= fopen( nomeArquivoProduto, "rb" );
    produto registro;
    while ( fread( &registro, sizeof( produto ), 1, arquivo ) == 1 )
    {
        if ( registro.id > id )
        {
            id= registro.id;
        }
    }
    fclose( arquivo );
    return id;
}

void deletar_produto( int id )
{
    FILE *arquivo= fopen( nomeArquivoProduto, "rb+" );
    produto registro;
    while ( fread( &registro, sizeof( produto ), 1, arquivo ) == 1 )
    {
        if ( registro.id == id )
        {
            registro.valido= PRODUTO_INVALIDO;
            fseek( arquivo, (long) - sizeof( produto ), SEEK_CUR );
            fwrite( &registro, sizeof( produto ), 1, arquivo );
            break;
        }
    }
    fclose( arquivo );
}


void truncar_arquivo_produtos()
{
    int comprimento= tamanho_arquivo( ( char* ) nomeArquivoProduto );
    produto *primeiro= malloc( comprimento * sizeof( produto ) );
    produto *ponteiro= primeiro;
    FILE *arquivo= fopen( nomeArquivoProduto, "rb" );
    int contador_validos= 0;
    produto registro;
    while ( fread( &registro, sizeof( produto ), 1, arquivo ) == 1 )
    {
        if ( registro.valido )
        {
            *ponteiro= registro;
            ponteiro++;
            contador_validos++;
        }
    }
    fclose( arquivo );
    arquivo= fopen( nomeArquivoProduto, "wb" );
    ponteiro= primeiro;
    for ( int indice= 0; indice < contador_validos; indice++ )
    {
        fwrite( ponteiro++, sizeof( produto ), 1, arquivo );
    }
    free( primeiro );
    fclose( arquivo );
}



