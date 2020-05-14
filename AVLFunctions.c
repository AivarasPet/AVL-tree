#include <stdio.h>
#include <stdlib.h>
#include "header.h"

void balansuot(Node * root, Node **topNode)
{
            int skirtumas = aukstis(root->right) - aukstis(root->left);

            Node * antrasNode, * treciasNode, *extraSaka = (Node *) malloc(sizeof(Node));

            if(skirtumas < -1)  //subroota i virsu, o roota i desine
            {
                if(aukstis(root->left->left) < aukstis(root->left->right)) ///trecias i kaire (priesinga puse)
                {
                    if(root->left->right != NULL)
                    {
                        Node * antrasNode = root->left;
                        Node * treciasNode = root->left->right;
                        Node * trecioRight = treciasNode->right;
                        Node * trecioLeft = treciasNode->left;
                        root->left = treciasNode; ///apkeicia 3->2
                        treciasNode->left = antrasNode; ///apkeicia 2->3
                        antrasNode->left = trecioLeft;

                        treciasNode->tevas = root;       ///priskiriamas tevas antram
                        antrasNode->tevas = treciasNode; ///priskiriamas tevas treciam
                        antrasNode->right = trecioRight;
                        //printf("pointeriai rl-e %p %p\n", antrasNode->left, antrasNode->right);
                    }
                }

                Node * antrasNode = root->left;
                if(root->tevas != NULL)
                {
                    perTeva(root, antrasNode);
                }
                else ///jei nera tevo tampa virsune
                {
                    *topNode = root->left;
                }
                antrasNode->tevas = root->tevas; ///antram nodui priskiria pirmo teva
                root->tevas = antrasNode;
                extraSaka = antrasNode->right;
                if(extraSaka != NULL) extraSaka->tevas = root;
                antrasNode->right = root; ///perstumia pirma i antra is kaires
                root->left = extraSaka; ///priskiria odd node kairei naujo root posakei
            }

            else if(skirtumas > 1) ///antras nodeas desinej, tai tikrinam ar trecias i desine ar kaire eis nuo tresio
            {
                if(aukstis(root->right->left) > aukstis(root->right->right)) ///trecias i kaire (priesinga puse)
                {
                    if(root->right->left != NULL)
                    {
                        Node * antrasNode = root->right;
                        Node * treciasNode = root->right->left;
                        Node * trecioRight = treciasNode->right;
                        Node * trecioLeft = treciasNode->left;
                        root->right = treciasNode; ///apkeicia 3->2
                        treciasNode->right = antrasNode; ///apkeicia 2->3
                        antrasNode->right = trecioRight;
                        treciasNode->tevas = root;       ///priskiriamas tevas antram
                        antrasNode->tevas = treciasNode; ///priskiriamas tevas treciam
                        antrasNode->left = trecioLeft;
                    }
                }

                Node * antrasNode = root->right;
                if(root->tevas != NULL)
                {
                    perTeva(root, antrasNode);
                }
                else ///jei nera tevo tampa virsune
                {
                    *topNode = root->right;
                }
                antrasNode->tevas = root->tevas; ///antram nodui priskiria pirmo teva
                root->tevas = antrasNode;
                extraSaka = antrasNode->left;
                antrasNode->left = root; ///perstumia pirma i antra is kaires
                root->right = extraSaka; ///priskiria odd node kairei naujo root posakei
                if(extraSaka != NULL) extraSaka->tevas = root;
            }
}


void balansavimas(Node * root, Node ** topNode)
{
    Node * tevas = root->tevas;
     //printf(" ---- po inserto %d --------\ %d %d", pradinis->id, pradinis->left->id, pradinis->right->id);
    int abbs = abs(aukstis(root->left) - aukstis(root->right));
    if(abbs > 1) balansuot(root, topNode);
    if(tevas != NULL) balansavimas(tevas, topNode);
}


int aukstis(Node * root)
{
    int h = 0, a, b;
    if(root != NULL)
    {
        //printf("rootas %d \n", root->id);
        a = aukstis(root->left);
        b = aukstis(root->right);
        if(a<b) h = b;
        else h = a;
        h++; ///maziausias 1etas
    }
    return h;
}

void insert(Node ** rootAdress, int id, char * vardas, Node ** topNode)
{
    Node ** subroot;
    Node * root = *(rootAdress);
    int arPirmas = 0;

    if(root != NULL)
    {
        if(root->id == id)
        {
        printf("toks elementas jau egzisutuoja \n");
        return;
        }
        if(id < root->id ) { subroot = &(root->left);  }
        else {subroot = &(root->right); }
    }
    else {subroot = &(root); arPirmas = 1; }

    if(*subroot == NULL)
    {
        *subroot = (Node*) malloc(sizeof(Node));
        (*subroot)->id = id;
        (*subroot)->left = NULL;
        (*subroot)->right = NULL;
        (*subroot)->tevas = root;
        (*subroot)->vardas = vardas;
        if(arPirmas == 1) {*topNode = *subroot; root = *subroot; root->tevas = NULL;}
        //if(root->tevas != NULL) printf("ka tik idejo %d, o tevas : %d \n", (*subroot)->id, (*subroot)->tevas->id);
        if(root!=NULL) balansavimas(root, topNode);
    }
    else insert(subroot, id, vardas, topNode);
}

Node * randaEl(Node * root, int id)
{
    if(root == NULL) {printf("elementas nerastas \n"); return NULL;}
    if(root->id == id)
    {
        return root;
    }
    if(id < root->id) return randaEl(root->left, id);
    else return randaEl(root->right, id);
    return NULL;
}

void printEl(Node * root, int id)
{
    Node * rastas = randaEl(root, id);
    if(rastas != NULL)
        printf("%d %s \n", id, rastas->vardas);

}

void printTree(Node *root, int space)
{
    if (root == NULL)
        return;

    space += 10;

    printTree(root->right, space);

    for (int i = 10; i < space; i++)
        printf(" ");
    printf("%d\n", root->id);

    printTree(root->left, space);
}

void perTeva(Node * root, Node * value) {
    if(root->tevas != NULL)
    {
        if(root->tevas->left == root) ///jei pirmas jo tevui is kaires ...
            root->tevas->left = value;
        else if(root->tevas->right == root) ///jei pirmas jo tevui is desintes
            root->tevas->right = value;
    }
}


void deleteEl(Node ** topNode, int id)
{
    Node * root = randaEl(*topNode, id);
    if(root == NULL) return;

    if(root->left == NULL && root->right == NULL)
    {
        if(root == *topNode) {free(root); *topNode = NULL;}
        else {perTeva(root, NULL); free(root);}
        if(root->tevas != NULL) balansavimas(root->tevas, topNode);
        return;
    }


    Node * node = root;
    int arKaire = 1, arKeistTopa = 0;
    if(node->left != NULL && node->right != NULL)
    {
        if(aukstis(node->left) >= aukstis(node->left)) {arKaire = 0; node = node->left;}
        else {arKaire = 1; node = node->right;}
        if(arKaire == 0) {while( node->right != NULL) node = node->right;}
        else { while(node->left != NULL ) node = node->left; }
    }
    else if(node->left!=NULL && node->right == NULL) node = node->left;
    else if(node->left==NULL && node->right != NULL) node = node->right;

    //printf(" apkeis su %d \n", node->id);
    perTeva(node, NULL);
    perTeva(root, node);
    node->left = root->left; node->right = root->right; node->tevas = root->tevas;
    if(node->left != NULL) node->left->tevas = node;
    if(node->right != NULL) node->right->tevas = node;
    if(root == *topNode) *topNode = node;
    if(node != NULL) balansavimas(node, topNode);
    free(root);
}
