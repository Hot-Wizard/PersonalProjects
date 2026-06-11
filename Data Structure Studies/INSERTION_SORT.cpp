#include<iostream>

using namespace std;

int main(){

    int principal[10] = {0}, secundario[10] = {0};
    string principal_list[10] = {"pedro", "digao", "allan", "enzo", "daniel","camilla","nicole","albini", "leticia","robson"};
    string secundario_list[10] = {""};
    int index = 0;

    for(int i = 0;i<10;i++){
        cout<<"digite o "<<i+1<<" numero do vetor:"<<endl;
        cin>>principal[i];
    }

    while(index<10)
    {
        int i = 0;
        for(i=0;i<index;i++){
            //cout<<principal[index]<<'<'<<secundario[i]<<endl;
            if(principal[index]<secundario[i]){
               // cout<<"passa pra frente:"<<endl;
                for(int x = 9; x>i-2;x--){
                    secundario[x] = secundario[x-1];
                    secundario_list[x] = secundario_list[x-1];
                }
               break;
            }
        }
        secundario_list[i]= principal_list[index];
        secundario[i] = principal[index];

      index++;
    }

for(int i = 0;i<10;i++){
        cout<<secundario_list[i]<<":"<<secundario[i]<<" ";
    }


    return 0;
}
