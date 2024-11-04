#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "registro.h"

void anexar_registro( char *nomeArquivo, void *registro, int num_bytes )
{
    FILE *arquivo= fopen( nomeArquivo, "ab" );
    fwrite( registro, num_bytes, 1, arquivo );
    fclose( arquivo );
}

int ler_registro( char *nomeArquivo, void *registro, int num_bytes, int pos )
{
    FILE *arquivo= fopen( nomeArquivo, "rb" );
    fseek( arquivo, pos, SEEK_SET );
    int registrosLidos= fread( registro, num_bytes, 1, arquivo );
    fclose( arquivo );
    return registrosLidos;      // Se tudo der certo, retorna 1.
}

int tamanho_arquivo( char *nomeArquivo )
{
    FILE *arquivo= fopen( nomeArquivo, "rb" );
    fseek( arquivo, 0, SEEK_END );
    int resultado= ftell( arquivo );
    fclose( arquivo );
    return resultado;
}



