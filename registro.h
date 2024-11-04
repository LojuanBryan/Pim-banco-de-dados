#ifndef REGISTRO_H_INCLUDED
#define REGISTRO_H_INCLUDED


void anexar_registro( char *nomeArquivo, void *registro, int num_bytes );
int ler_registro( char *nomeArquivo, void *registro, int num_bytes, int pos );

int tamanho_arquivo( char *nomeArquivo );


#endif // REGISTRO_H_INCLUDED
