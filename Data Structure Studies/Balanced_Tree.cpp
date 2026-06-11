#include<bits/stdc++.h>

using namespace std;

class Node
{
public:
    int value;
    Node* left;
    Node* right;

    Node()
    {
        value = 0;
        left = NULL;
        right = NULL;

    }
    Node(int value)
    {
        this->value = value;
        this->left = NULL;
        this->right = NULL;
    }

};
class Tree
{
private:
    Node* root;
public:
    Tree()
    {
        root = NULL;
    }
    void InsertNode(int value)
    {
        Node* newNode = new Node(value);
        Node* pivot = root;
        Node* pivot2 = root;

        if(root==NULL)
        {
            root = newNode;
            return;
        }

        while(pivot!=NULL)
        {
            pivot2 = pivot;

            if(newNode->value < pivot2->value)
                pivot = pivot->left;

            if(newNode->value > pivot2->value)
                pivot = pivot->right;
        }

        if(newNode->value < pivot2->value)
            pivot2->left = newNode;

        if(newNode->value > pivot2->value)
            pivot2->right = newNode;

    }
    Node* Get_Root()
    {
        return root;
    }

    void PrintTree(Node* node)
    {
        if(node != NULL)
        {
            cout<<node->value<<" ";
            PrintTree(node->left);
            PrintTree(node->right);
        }
    }
    void Binary_Seach_Tree(int asked_value)
    {
        if(root == NULL)
        {
            cout<<"arvore inexistente";
            return;
        }
        Node* pivot = root;
        Node* pivot2 = root;

        while(asked_value != pivot2->value)
        {
            pivot2 = pivot;

            if(asked_value < pivot2->value)
                pivot = pivot->left;

            if(asked_value > pivot2->value)
                pivot = pivot2->right;

            if(pivot == NULL)
            {
                cout<<"Numero inexistente";
                return;
            }
        }

        cout<<"numero encontrado";

    }
    void Std_Search_Tree(int asked_value, Node* node)
    {
        if(node == NULL)
        {
           // cout<<"arvore inexistente";
            return;
        }
        if(asked_value == node->value)
        {
            cout<<"valor encontrado";
            return;
        }
        Std_Search_Tree(asked_value, node->left);
        Std_Search_Tree(asked_value, node->right);
    }

};

int main()
{
    Tree t;
    clock_t start, end_t;
    for(int i = 0; i<100000; i++)
    {
        t.InsertNode(i);
    }

    start = clock();
    t.Binary_Seach_Tree(9999);
    //t.Std_Search_Tree(99999, t.Get_Root());
    end_t = clock();
    cout<<"\n";
    double time_taken = double(end_t-start) / double(CLOCKS_PER_SEC);
    cout<<"tempo Binary Search: " << fixed << time_taken << setprecision(5);
    cout<< "sec";
   // t.PrintTree(t.Get_Root());

    return 0;
}
