#include <stdio.h>
#include <stdlib.h>

#include "produto.h"

int main()
{
    int opcao;

    while ( 1 )
    {
        printf( "\n\n Digite uma opcao: \n\n" );
        printf( "0- Sair.\n" );
        printf( "1- Cadastrar novo produto.\n" );
        printf( "2- Visualizar lista de produtos.\n" );
        printf( "3- Buscar produto.\n");
        printf( "4- Limpar lista de produtos.\n" );
        printf( "5- Atualizar estoque de produto.\n" );
        printf( "6- Deletar produto.\n" );
        printf( "7- Truncar arquivo de produtos.\n" );

        scanf( "%d", &opcao );

        switch ( opcao )
        {
        case 0:
            return 0;
        case 1:
            cadastrar_produto();
            break;
        case 2:
            listar_produtos();
            break;
        case 3:
            {
                int id;
                printf( "\n Digite o ID do registro a ser buscado: " );
                scanf( "%d", &id );
                produto resultado= obter_produto( id );
                exibir_produto( &resultado );
            }
            break;
        case 4:
            apagar_todos_produtos();
            break;
        case 5:
            {
                int id;
                printf( "\n Digite o ID do estoque a ser atualizado: " );
                scanf( "%d", &id );
                produto prod= obter_produto( id );
                if ( prod.valido )
                {
                    printf( "\n Digite o novo valor do estoque: " );
                    int estoque;
                    scanf( "%d", &estoque );
                    atualizar_estoque( id, estoque );
                }
            }
            break;
        case 6:
            {
                int id;
                printf( " Digite o ID do produto a ser desabilitado: " );
                scanf( "%d", &id );
                deletar_produto( id );
            }
            break;
        case 7:
            truncar_arquivo_produtos();
        }
    }

    return 0;
}
