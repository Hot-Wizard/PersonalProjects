#include<iostream>
class Node
{
public:
    int value;
    Node* next;

    //common constructor
    Node()
    {
        value = 0;
        next = NULL;
    }
    //parameterised constructor
    Node(int value)
    {
        this->value = value;
        this->next = NULL;
    }

};

class LinkedList
{
private:
    Node* head;

public:
    LinkedList()
    {
        head = NULL;
    }
    void CreateNode(int value)
    {
        //insert a node with a chosen value in the end of the list

        //crate node
        Node* newNode = new Node(value);
        Node* temp = head;
        //se nao existir um node principal o newnNode vira o principal
        if(head == NULL)
        {
            head = newNode;
            return;
        }
        //vai ate o final da lista
        while(temp->next != NULL)
        {
            temp = temp->next;
        }

        //coloca o newNode no final
        temp->next = newNode;
    }
    void InsertNodeChosen(int point, int value)
    {
        Node* newNode = new Node(value);
        Node* temp = head;
        Node* temp1 = NULL;
        int listlen = 0;

        //se nao existir um node principal o newnNode vira o principal
        if(head == NULL)
        {
            std::cout<<"there is no list;\n";
            return;
        }
        while(temp != NULL)
        {
            temp = temp->next;
            listlen++;
        }
        temp = head;

        //se a posicao do node para ser deletado nao existir retorna
        if(listlen < point)
        {
            std::cout<<"Index out of the bounds of the list\n";
            return;
        }
        while(point-- > 1)
        {
            temp1 = temp;
            temp = temp->next;
        }

        temp1->next = newNode;
        newNode->next = temp;
    }
    void Delete_node(int nodeOffset)
    {
        //delete node at given position
        Node* temp1 = head;
        Node* temp2 = NULL;
        int listlen = 0;

        //se nao existir lista avisa e retorna
        if(head == NULL)
        {
            std::cout<<"list is empty.\n";
            return;
        }

        //Get the Length of the list;
        while(temp1 != NULL)
        {
            temp1 = temp1->next;
            listlen++;
        }

        //se a posicao do node para ser deletado nao existir retorna
        if(listlen < nodeOffset)
        {
            std::cout<<"Index out of the bounds of the array\n";
            return;
        }

        //redeclara a temp1
        temp1 = head;

        //deletando o head
        if(nodeOffset == 1)
        {
            head = head->next;
            delete temp1;
            return;
        }

        //procura o node da lista para ser deletado
        while(nodeOffset-- > 1)
        {
            temp2 = temp1;

            temp1 = temp1->next;
        }

        //muda o proximo ponteiro para o ponteiro antecessor
        temp2->next = temp1->next;

        delete temp1;
    }
    void PrintList()
    {
        Node* temp = head;

        if(head == NULL)
        {
            std::cout<<"there is no list\n";
            return;
        }
        while(temp != NULL)
        {
            std::cout<< temp->value<< " ";
            temp = temp->next;
        }
    }
    LinkedList SumList(LinkedList l, LinkedList l2)
    {
        LinkedList returned_list;
        Node* temp1 = l.head;
        Node* temp2 = l2.head;

        while(temp1 != NULL)
        {
            returned_list.CreateNode((temp1->value + temp2->value)%10);
            temp1 = temp1->next;
            temp2 = temp2->next;
        }

        return returned_list;
    }
};
int main()
{
    LinkedList link1;
    LinkedList link2;
    LinkedList returned_list;

    int input;

    for(int i = 0; i<6; i++)
    {
        if(i>=3)
        {
            std::cout<<"input the digits of the second list: \n";
            std::cin>>input;
            link2.CreateNode(input);
        }
        else
        {
            std::cout<<"input the digits of the first list: \n";
            std::cin>>input;
            link1.CreateNode(input);

        }
    }


    returned_list = returned_list.SumList(link1, link2);

    returned_list.PrintList();

    std::cout<<"\n";
}


/////////////////////////////////////////////////DOUBLE_LINKED_LIST
/*
#include <iostream>
struct node
{
    int value;
    struct node* pre;
    struct node* next;
};

node* create_node(int value, node* next)
{
    node* n = new node();

    n->value = value;
    n->next = next;
    next->pre = n;

    return n;
}

void print_list(node* n)
{
    if(n != NULL)
    {
       std::cout<<n->value<<" ";
       print_list(n->next);
    }
}

int main()
{
   node* n = create_node(20, create_node(40, NULL));
   print_list(n);
   free(n);

   return 0;
}
*/
