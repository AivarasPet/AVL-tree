#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

typedef char kintamasis;

struct Node
{
    int id;
    kintamasis * vardas;
    struct Node * left;
    struct Node * right;
    struct Node * tevas;
}
typedef Node;

///topnode - virsunes adresas

void insert(Node ** rootAdress, int id, char * vardas, Node ** topNode);
Node * randaEl(Node * root, int id);
void printEl(Node * root, int id);
void printTree(Node *root, int space); ///space = 0 !!!
void deleteEl(Node ** topNode, int id);

#endif // HEADER_H_INCLUDED
