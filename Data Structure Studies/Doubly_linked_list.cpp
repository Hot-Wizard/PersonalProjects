#include<iostream>
using namespace std;
class Node
{
public:
    int value;
    Node* next;
    Node* pre;

    Node()
    {
        value = 0;
        next = NULL;
        pre = NULL;
    }
    Node(int value)
    {
        this->value = value;
        this->next = NULL;
        this->pre = NULL;
    }
};
class Doubly_Linked_List
{
private:
    Node* head;
public:
    Doubly_Linked_List()
    {
        head = NULL;
    }
    void CreateNode(int value/*, int &times*/)
    {
        Node* newNode = new Node(value);
        Node* pivot = head;
        Node* pivot1 = NULL;

        if(head == NULL)
        {
            head = newNode;
            //std::cout<<newNode->pre<<" <- valor do antecessor / "<<times<<"\n";
            //times++;
            return;
        }

        while(pivot->next != NULL)
        {
            pivot = pivot->next;
        }

        pivot->next = newNode;
        newNode->pre = pivot;
        pivot1 = newNode->pre;

        //std::cout<<pivot1->value<</*" <- valor do antecessor / "/*<<times<<*/"\n";
        //times++;

    }
    void DeleteNode(int position)
    {
        Node* pivot = head;
        Node* pivot1 = NULL;
        Node* pivot2 = NULL;
        int listlen = 0;

        if(head == NULL)
        {
            std::cout<<"the list doesn't exist\n";
            return;
        }

        while(pivot!= NULL)
        {
            pivot = pivot->next;
            listlen++;
        }
        pivot = head;

        if(listlen<position)
        {
            std::cout<<"position is out of the bounds of the list.\n";
            return;
        }

        if(position==1)
        {
            head = head->next;
            delete pivot;
            return;
        }

        while(position-- > 1)
        {
            pivot1 = pivot;
            pivot = pivot->next;
        }
        pivot1->next = pivot->next;
        pivot2 = pivot->next;
        pivot2->pre = pivot1;

        delete pivot;
    }
    void PrintList_up()
    {
        Node* pivot = head;

        if(head == NULL)
        {
            std::cout<<"there is no list\n";
            return;
        }
        while(pivot != NULL)
        {
            std::cout<< pivot->value<< " ";
            pivot = pivot->next;
        }
    }
    void PrintList_down()
    {
        Node* pivot = head;

        if(head == NULL)
        {
            std::cout<<"there is no list\n";
            return;
        }

        while(pivot->next != NULL)
        {
            pivot = pivot->next;
        }

        while(pivot != NULL)
        {
            std::cout<< pivot->value<< " ";
            pivot = pivot->pre;
        }


    }
    void PrintChosen(int chosen)
    {
        int listlen = 0;
        Node* pivot = head;

        if(pivot == NULL)
        {
            std::cout<<"there is no list";
            return;
        }

        while(pivot != NULL)
        {
            pivot = pivot->next;
            listlen++;
        }

        pivot = head;
        if(listlen < chosen)
        {
            std::cout<<"out of the list's bounds";
            return;
        }
        while(chosen-- > 1)
        {
            pivot = pivot -> next;
        }
        std::cout<<pivot->value;
    }
};
int main()
{
    Doubly_Linked_List n;
    Doubly_Linked_List m;
    for(int i = 1; i<=5; i++)
    {
        n.CreateNode(i);
    }

    n.DeleteNode(3);

    n.PrintList_down();
    std::cout<<"\n";
    n.PrintList_up();
}
