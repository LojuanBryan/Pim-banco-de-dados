#ifndef PRODUTO_H_INCLUDED
#define PRODUTO_H_INCLUDED

#include "registro.h"

#define LIMITE_CARACTERES   (60)

struct Produto
{
    int id;
    char nome[ LIMITE_CARACTERES ];
    int estoque;
    float preco_unitario;
    char valido;
};

typedef struct Produto produto;

void exibir_produto( produto* prod );
void anexar_produto( produto* registro );
int ler_produto( produto* registro, int pos );
produto cadastrar_produto();
void apagar_todos_produtos();
void listar_produtos();
produto obter_produto( int id );
void atualizar_produto( int id, produto* novo );
void atualizar_estoque( int id, int estoque );
void deletar_produto( int id );
void truncar_arquivo_produtos();


#endif // PRODUTO_H_INCLUDED
