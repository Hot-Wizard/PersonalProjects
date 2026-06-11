#include<iostream>
/*
//criacao do no da arvore/estrutura;
struct noDaArvore
{
    int valor;
    struct noDaArvore* esquerda;
    struct noDaArvore* direita;
};

//para nao repetir muitas vezes noDaArvore referenciamos como no;
typedef struct noDaArvore no;

////////////////////////////////////////////////////////
//funcao que retorna o no;
no* insert_no(int valor, no*esq, no*dir)
{
    //aloca o no em um espaco de memoria de maneira dinamica;
    no* n = (no*)malloc(sizeof(no));

    if(n==NULL)
        exit(1);

    n->valor = valor;
    n->esquerda = esq;
    n->direita = dir;

    return n;
}
////////////////////////////////////////////////////////
//imprime
void printPreOrdem(no* n)
{
    //imprime o no apenas se ele nao for nulo
    if(n != NULL)
    {
        //imprime em ordem: raiz; filho da esquerda; filho da esquerda do filho da esquerda, filho da direita do filho da direita, filho da direita, filho da esquerda do filho da direita e nulo, filho da direita do filho da direita;
        std::cout<<n->valor<<" ";
        printPreOrdem(n->esquerda);
        printPreOrdem(n->direita);
    }
}
int main()
{
    no*n = insert_no(45,insert_no(10,insert_no(5,insert_no(100, insert_no(30, NULL, NULL), insert_no(60, NULL, NULL)),NULL),insert_no(15, NULL,NULL)), insert_no(50, insert_no(20, NULL, NULL), NULL));

    printPreOrdem(n);

    free(n);
    return 0;
}
*/
/*
struct noDaArvore
{
    int valor;
    struct noDaArvore* left;
    struct noDaArvore* right;
};

noDaArvore* create_knot(int valor, noDaArvore* left, noDaArvore* right)
{
    noDaArvore* no = (noDaArvore*)malloc(sizeof(no));

    if(no == NULL)
        exit(1);

    no->valor = valor;
    no->left = left;
    no->right = right;

    return no;
}

void print_no(noDaArvore* no)
{
    if(no != NULL)
    {
        std::cout<<no->valor<<" ";
        print_no(no->left);
        print_no(no->right);

    }
}

void delete_no(noDaArvore* no)
{

}
int main()
{

    return 0;
}
*/

struct knot
{
  int value;
  struct knot* left;
  struct knot* right;
};

knot* create_knot(int value, knot* left, knot* right)
{
    knot* tree_knot = (knot*)malloc(sizeof(tree_knot));

    if(tree_knot == NULL)
        exit(1);

    tree_knot->value = value;
    tree_knot->left = left;
    tree_knot->right = right;

    return tree_knot;
}

void print_knot(knot* knot)
{
   if(knot != NULL)
   {
       std::cout<<knot->value<<" ";
       print_knot(knot->left);
       print_knot(knot->right);
   }
}

int main()
{
    knot* a = create_knot(50, create_knot(40, NULL, NULL), create_knot(80, NULL, create_knot(70, NULL, NULL)));
    print_knot(a);
    free(a);
    return 0;
}

/*
class Knot
{
public:
    int value;
    Knot* left;
    Knot* right;

    Knot()
    {
        value = 0;
        left = NULL;
        right = NULL;
    }
    Knot(int value)
    {
        this->value = 0;
        left = NULL;
        right = NULL;
    }

};
class Tree
{
private:
    Knot* root;
public:
    Tree()
    {
        root = NULL;
    }
    void CreateKnot(int value)
    {
        Knot* newKnot = new Knot(value);
        Knot* pivot = root;
        Knot* pivot1 = NULL;

        if(root == NULL)
        {
            root = newKnot;
            return;
        }
    }

    void Print_Tree()
    {
        Knot* pivot = root;
        if(pivot == NULL)
        {
            std::cout<<"there is no tree";
            return;
        }
        std::cout<<pivot->value;
        while(pivot != NULL)
        {
            std::cout<<pivot->value<<" ";
            pivot = pivot->left;
        }
        std::cout<<"\n";
        while(pivot != NULL)
        {
            std::cout<<pivot->value;
            pivot = pivot->right;
        }
    }
};

int main()
{
    Tree n;
    n.CreateKnot(4);
    n.Print_Tree();

    return 0;
}
*/
