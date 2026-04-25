#include<iostream>
#include<string>
#include<vector>

#define HASH_SIZE 100;

struct Node
{
    std::string key;
    std::string value;
    Node *next;
};

struct HashTable
{
    std::vector<Node*> list = std::vector<Node*>(100, nullptr);
};

unsigned int HashCode(std::string &key) {
    unsigned long hash = 5381;
    for (char c : key)
        hash = ((hash << 5) + hash) + c;
    return hash % HASH_SIZE;
}

Node* CreateNode(std::string &key, std::string &value)
{
    Node *node = new Node();
    node->key = key;
    node->value = value;
    node->next = nullptr;
    return node;   
}

void InsertNode(HashTable &hash, std::string &key, std::string &value)
{
    unsigned int index = HashCode(key);
    Node *node = hash.list[index];

    if(node == NULL)
    {
        hash.list[index] = CreateNode(key, value);
    }else{
        while(node)
        {
            if(node->next == NULL)
            {
                node->next = CreateNode(key, value);
                break;
            }
            node = node->next;
        }
    }
}

std::string Search(HashTable &hash, std::string key)
{
    unsigned int index = HashCode(key);
    Node *node = hash.list[index];
    while(node)
    {
        if(node->key == key)return node->value;
        node = node->next;
    }
    return "";
}

int main()
{
    
    return 0;
}