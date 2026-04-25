#include<iostream>
#include<string>
#include<unordered_map>
#include<utility>
#include<vector>

class DataBase
{
    private:
        std::unordered_map <int, std::vector<std::pair<std::string, int>>> base;
    public:
        std::pair<std::string, int> CollumnCreator(std::string collumnName, int info)
        {
            return std::pair<std::string, int>(collumnName, info);
        }
        void Insert(int index, std::pair<std::string, int> info)
        {
            if(base.find(index) != base.end())
            {
                std::cout<<"choosen key already contains a value"<<std::endl;
                return;
            }
            //ELSE
            base[index].push_back(info);
            std::cout<<"Value added to the Database"<<std::endl;

        }

        void Delete()
        {

        }

        void Update()
        {

        }

        int Select()
        {

        }
};

int main()
{



    return 0;
}