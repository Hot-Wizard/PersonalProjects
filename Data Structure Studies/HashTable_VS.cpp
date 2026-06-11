#include<iostream>
#include<cstring>

#define TABLE_SIZE 10

using namespace std;

class Node
{
public:
    string key;
    string data;
    Node* next;

    Node(string key, string data)
    {
        this->key = key;
        this->data = data;
        this->next = NULL;
    }
};

class HashTable
{
private:
    Node* hashTable[TABLE_SIZE];
public:
    static unsigned long KeyFunction(string str)
    {
        unsigned long i = 0;

        for(int j = 0; str[j]; j++)
            i += str[j];
            
        cout<<"KEY FUNCTION RODANDO\n";
        return i % TABLE_SIZE;
    }
    Node* CreateNode(string key, string data)
    {
        Node* newNode = new Node(key, data);
        cout<<"CREATE NODE RODANDO\n";
        return newNode;
    }

    void InsertNode(Node* newNode)
    {
        unsigned int index = KeyFunction(newNode->key);
        Node* pivot = hashTable[index];
        if(pivot == NULL)
        {
            hashTable[index] = newNode;
            cout<<"INSERT RODANDO E PIVOT ERA NULL "<<hashTable[index]->data<<"\n";
            return;
        }else
        {
            cout<<"NAO ERA O PRIMEIRO";
            while(pivot)
            {
                if(pivot->next==NULL)
                {
                    pivot->next = newNode;
                    cout<<"INSERT RODANDO E PIVOT NAO ERA NULL"<<pivot->data<<"\n";
                    return;
                }
                pivot = pivot->next;
                return;
            }
        }
    }
    string Search(string key)
    {
        unsigned int index = KeyFunction(key);
        Node* pivot = hashTable[index];
        while(pivot)
        {
            if(pivot->key == key)
            {
                cout<<"ENCONTRADO\n";
                return pivot->data;
            }
            pivot = pivot->next;
        }
        return "404";
    }



};
int main()
{
    HashTable h;

    h.InsertNode(h.CreateNode("ABACATE", "VOVO JUJU"));
    h.InsertNode(h.CreateNode("IRMAO", "JOREL"));
    h.InsertNode(h.CreateNode("TV", "VOVO JOJO"));

    cout<<h.Search("ABACATE");

    return 0;
}
