#include<vector>
#include<cmath>
#include<iostream>
#include<ctime>
#include<memory>

#define TURN_LEFT "left"
#define TURN_RIGHT "right"
#define GO_FOWARD "forward"
#define GO_BACKWARD "backward"

#define DEFAULTPLAYERLIFE 100
#define DEFAULTPLAYERORIENTATION 90
#define DEFAULTPLAYERDAMAGE 15
/*
Map tile -> EnemyCreator -> Enemy object
Enemy object -> Combat -> modifies Life
Life -> controls death
unique_ptr -> controls memory
*/

enum TileEncounter//Tipe of Tyles in the _mapTemplate
{
    EMPT,
    TREE,
    GOBL,
    ORCS
};

class Life//everything that involves life: damage, cure, dying...
{
    private:
    int _totalLife;
    int _currentLife;
    public:
    Life(int defaultLife) : _totalLife(defaultLife), _currentLife(defaultLife){}//life obj constructor
    
    void Damage(int dmg)//counts the damage
    {
        _currentLife -= dmg;
        if(_currentLife < 0)_currentLife = 0;
    }
    bool IsDead()//if current life == 0 returns true
    {
        return _currentLife == 0;
    }
};


////////////////////////////////////////////////////////////////////////////////////////////////////////ENEMIES 
class Enemy//Default Enemy Class, Cannot be instantiated alone, Segmentation Fault error
{
    public:
    Life _life;
    int _damage;
    Enemy(int hp, int dmg) : _life(hp), _damage(dmg){}//Enenmy Constructor
    virtual std::string Name() = 0;//polymorphism, function chosen in runtime
    //TODO make methods that can be overwritten by the polymorphs class
    virtual ~Enemy() = default;//destructor of the polymorpism, avoid memory leak, Free the Polymorphism class too, thats why its virtual
};
class Goblin : public Enemy//Class that heirs the enemy class can have n of those
{
    public:
    Goblin() : Enemy(30, 5) {}
    std::string Name() override {return "Goblin";}//rewrites the Name(), polymorphism. Name must be implemented
};
class Orc : public Enemy
{
    public:
    Orc() : Enemy(50, 10){}
    std::string Name() override {return "Orc";}
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Combat//actions that can be done during combat
{
    private:
    Life& _player;//players life object, players combat atribute and methods
    Enemy& _enemy;
    void CombatActions(std::string command)
    {
        if(command == "attack")
        {
            std::cout<<"You Attacked the "<< _enemy.Name() <<"\n";
            _enemy._life.Damage(DEFAULTPLAYERDAMAGE);
        }
    }
    public:

    Combat(Life& p, Enemy& e) : _player(p), _enemy(e) {}
    static int PseudoRandomNumberGenerator(int dice, int throws)
    {
        int result = 0;
        int currDice;
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        for(int i = 0; i < throws; i++)
        {
            currDice = std::rand() % dice + 1;
            std::cout<<i+1<<"° throw:"<<currDice<<"\n";
            result += currDice;
        }
        return result;
    }
    bool CombatPhase()
    {
        std::cout << "Encountered " << _enemy.Name() << "\n";
        std::string command;
        while (!_enemy._life.IsDead())//while the enemy is not dead
        {
            std::cout<<"What do you wanna do against the "<<  _enemy.Name() <<"\n";
            std::getline(std::cin, command);
            CombatActions(command);
        }
        return _enemy._life.IsDead();
        
        //TODO make the combat, after destroy the tile
    }
};
class EnemyCreator//Returns a object that heirs the enemy class
{
public:
    static std::unique_ptr<Enemy> Create(TileEncounter type)//smart pointer to the polymorphed class in fuction to the type tile encountered
    {
        switch(type)
        {
            case GOBL: return std::make_unique<Goblin>();//returns a Enemy pointer that points to the goblin
            case ORCS: return std::make_unique<Orc>();//returns a smart pointer Enemy that pointers to the orc
            default: return nullptr;
        }
    }
};

class Map
{
  private:
    std::vector<std::vector<TileEncounter>> _mapTemplate;//map in question
    int _rows, _cols;//size of the map
  public:
    Map(int rows, int cols)//resize creates a usable map template
    {
        //TODO make a dinamic world constructor
        _rows = rows;
        _cols = cols;
        _mapTemplate = {{TREE, TREE, TREE, TREE, TREE},
                        {TREE, EMPT, EMPT, GOBL, TREE},
                        {TREE, EMPT, EMPT, EMPT, TREE},
                        {TREE, EMPT, EMPT, EMPT, TREE},
                        {TREE, TREE, TREE, TREE, TREE}};
    }
    //I am using cartessian rotational logic here so i gotta translate the output
    //to matrix addressing logic, the following method does that
    std::pair<int, int> GetsAdressMatrix(int x, int y)//Translate the cartessian position to the matrix position and returns its adress.
    {
        int matrixRow = abs(_rows - 1 - y);
        int matrixCol = x;

        if(matrixRow < 0 || matrixRow >= _rows || matrixCol < 0 || matrixCol >= _cols)//detect if its out of bounds
            return {-1, -1}; // out of bounds
        
        return {matrixRow, matrixCol};
    }
    bool CheckFrontOf(int x, int y, Life playerCurrentLife)//checks the matrix index and do something based on its value
    {
        auto [mX, mY] = GetsAdressMatrix(x,y);
        switch(_mapTemplate[mX][mY])//if it encounters {-1 -1} gonna through an exeption
        {
            case EMPT :
                return false;
            case TREE :
            {
                std::cout<<"You encountered a Tree, Find Another Way\n";
                return true;
            }
            //TODO fix the error if it goes outside of the map it interprete it as a enemy
            default://Enemy Encounter case
            {
                std::unique_ptr enemy = EnemyCreator::Create(_mapTemplate[mX][mY]);//enemy is automatically dealocated when out of scope
                Combat combat(playerCurrentLife, *enemy);//combat class instantiation
                if(combat.CombatPhase())
                {
                    _mapTemplate[mX][mY] = EMPT;//combat loop
                    return false;
                }
                return true;
            }
        }
    }
};
class MovementSexual
{
    private:
        Map& _map;//reference to the map
        Life _life;//players life
        std::pair<int, int> _position; //cartesian player position
        int _orientationAngle; // 0,90,180,270
        double DegToRad(double deg)//degrees to rad converter
        {
            return deg * M_PI / 180.0;
        }
        void RotateOrientation(std::string command)//alters the _orientationAngle in function to the command
        {
            if(command == TURN_LEFT)//plus 90 degrees to the _orientationAngle
            {
                if(_orientationAngle + 90 > 360)_orientationAngle = _orientationAngle + 90 - 360;
                else _orientationAngle+=90;
            }
            if(command == TURN_RIGHT)//plus 270 degrees to the _orientationAngle
            {
                if(_orientationAngle + 270 > 360)_orientationAngle = _orientationAngle + 270 - 360;
                else _orientationAngle+=270;
            }
            if(command == GO_BACKWARD)//plus 180 degrees to the _orientationAngle
            {
                if(_orientationAngle + 180 > 360)_orientationAngle = _orientationAngle + 180 - 360;
                else _orientationAngle+=180;
            }
        }
        void GoFoward(std::string command, int orientationX, int orientationY)
        {
            if(command == GO_FOWARD)//goes forward in the cartessian plane
            {
                if(_map.CheckFrontOf(_position.first + orientationX, _position.second + orientationY, _life))//if theres something in front of the player, gonna trigger something
                    return;//if it founds something just gonna return after the trigged action
                _position.first  += orientationX;
                _position.second += orientationY;
            }
        }
    public:
        MovementSexual(int x, int y, int defaultOrientation,Map& map) : _map(map), _life(DEFAULTPLAYERLIFE)//Player Position Constructor
        {
            _position = {x, y};
            _orientationAngle = defaultOrientation;
        }
        
        std::pair<int,int> GetCartesianPosition()//Returns the Player Cartesian Position
        {
            return _position;
        }
        void SensualMoves()
        {
            std::string input;
            std::cout<<"Where to go?\n";
            std::getline(std::cin, input);
        
            RotateOrientation(input);//Alters the _AngleOrientation
        
            double rad = DegToRad(_orientationAngle);//Gets the rad of the _AngleOrientation
        
            int dx = (int) std::round(cos(rad));//x part of the unitary orientation vector, works because I am only using angles that can be divided by 90
            int dy = (int) std::round(sin(rad));//y part of the unitary orientation vector, works because I am only using angles that can be divided by 90
        
            GoFoward(input, dx, dy);
        }
};

class Player : public MovementSexual//has the life object of the player and the movement methods and atributtes
{
  private:
  public: 
    Player(int posx, int posy, int defaultOrientation, Map& map) : MovementSexual(posx, posy, defaultOrientation, map)
    {}
};

int main()
{
    Combat::PseudoRandomNumberGenerator(20, 10);
    Map map(5, 5);
    Player player(2, 2, DEFAULTPLAYERORIENTATION, map);
    while (true)
    {
        auto pos = player.GetCartesianPosition();
        player.SensualMoves();
    }
    return 0;
}
