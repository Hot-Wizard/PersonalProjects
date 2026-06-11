#include<windows.h>
#include<iostream>
#include<thread>
#include<vector>
using namespace std;

wstring pieces[7];//wide string to allocate de pieces;
//Field Size;
int fieldWidth{12};
int fieldHeight{18};
unsigned char *field = nullptr;//unsigned char is used to 0 represents eampty space and to allocate this dinamycly;

//Console Screen
int screenWidth{60};//60
int screenHeight{80};//80
int Rotate(int px, int py, int &rotationState)
{
    switch(rotationState%4)
    {
        case 0: return py * 4 + px;//0;
        case 1: return 12 + py - (4 * px);//90;
        case 2: return 15 - (4 * py) - px;//180;
        case 3: return 3 - py + (px * 4);//270;
    }
    if(rotationState>4)rotationState=0;
    return 0;
}
bool FitPiece(int piece, int CurrentRotationState, int px, int py)
{
    for(int i = 0; i < 4; ++i)//bounds da peca;
    {
        for(int j = 0; j < 4; ++j)//bounds da peca;
        {
            //Get index into piece;
            int rot = Rotate(i, j, CurrentRotationState);//pega o rotation state dp pixel peca;
            //Get index into field;
            int place = (py + j) * fieldWidth + (px + i);//pega a localizacao do pixel da peca no mapa;
            if((px + i >= 0 && px + i < fieldWidth) && (py + j >= 0 && py + j < fieldHeight))//checa dentro dos bounds do mapa;
            {
                if(pieces[piece][rot] == L'▓' && field[place] != 0)return false;//verifica se ha espaço, se nao retorna false;
            }
        }
    }
    return true;
}
int main()
{
    //Output
    bool lineExists{false};
    vector<int> lines;
    //Input
    bool getKey[4];
    bool isHolding{false};
    //create the pieces;
    int currentPiece{0};
    int currentRotation{0};
    int currentX{6};
    int currentY{0};
    int speed{20};
    int speedCounter{0};
    bool fDown{false};
    //I piece;
    pieces[0].append(L"..▓.");//dots represents empty space;
    pieces[0].append(L"..▓.");
    pieces[0].append(L"..▓.");
    pieces[0].append(L"..▓.");
    //L piece;
    pieces[1].append(L"....");//dots represents empty space;
    pieces[1].append(L".▓▓.");
    pieces[1].append(L"..▓.");
    pieces[1].append(L"..▓.");
    //J piece;
    pieces[2].append(L"....");//dots represents empty space;
    pieces[2].append(L".▓▓.");
    pieces[2].append(L".▓..");
    pieces[2].append(L".▓..");
    //Z piece;
    pieces[3].append(L"..▓.");//dots represents empty space;
    pieces[3].append(L".▓▓.");
    pieces[3].append(L".▓..");
    pieces[3].append(L"....");
    //S piece;
    pieces[4].append(L".▓..");//dots represents empty space;
    pieces[4].append(L".▓▓.");
    pieces[4].append(L"..▓.");
    pieces[4].append(L"....");
    //T piece;
    pieces[5].append(L"..▓.");//dots represents empty space;
    pieces[5].append(L".▓▓.");
    pieces[5].append(L"..▓.");
    pieces[5].append(L"....");
    //O piece;
    pieces[6].append(L".▓▓.");//dots represents empty space;
    pieces[6].append(L".▓▓.");
    pieces[6].append(L"....");
    pieces[6].append(L"....");

    //Inicialize the Field Array;
    field = new unsigned char [fieldWidth * fieldHeight];//create the field buffer;
    for(int i = 0; i < fieldWidth; ++i)//board boundary;
    {
        for(int j = 0; j < fieldHeight; ++j)//board boundary;
        {
            //fill all the field with the number 0 unless its a border, then fill with letter nine;
            field[j * fieldWidth + i] = (i == 0 || i == fieldWidth - 1 || j == fieldHeight - 1) ? 3 : 0;
        }
    }

    //Creates the Screen;
    wchar_t *screen = new wchar_t[screenWidth * screenHeight];//creates the screen buffer;
    for(int i = 0; i < screenWidth * screenHeight; ++i)screen[i] = L' ';//inicialize the screen buffer with empty space;
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);//creates the buffer;
    SetConsoleActiveScreenBuffer(console);//active the screen buffer;
    DWORD bytesWritten{0};


    //GAME LOOP;
    bool gameOver = false;
    while(!gameOver)
    {
        //Time Control;
        this_thread::sleep_for(50ms);//pausa um pouco o tempo;
        speedCounter++;//conta os ticks de tempo;
        fDown = (speed==speedCounter);//forca a peca para baixo se o ticks ficar igual a speed;
        //User Input;
        for(int i = 0; i < 4; ++i)                                //R    L    DZ
            getKey[i] = (0x8000 & GetAsyncKeyState((unsigned char)("\x27\x25\x28Z"[i]))) != 0;//Array que armazena as possiveis chaves de Input;
        if(getKey[0] && FitPiece(currentPiece, currentRotation, currentX+1, currentY))currentX++;//se a tecla for pressionada o index do vetor vira true se nao false;
        if(getKey[1] && FitPiece(currentPiece, currentRotation, currentX-1, currentY))currentX--;//se a tecla for pressionada o index do vetor vira true se nao false;
        if(getKey[2] && FitPiece(currentPiece, currentRotation, currentX, currentY+1))currentY++;//se a tecla for pressionada o index do vetor vira true se nao false;
        if(getKey[3])
        {
            if(!isHolding && FitPiece(currentPiece, currentRotation+1, currentX, currentY))currentRotation++;
            isHolding=true;//verifica se a tecla rotate este sendo pressionada;
            speedCounter = 0;//reseta o speed counter;
        }else{
            isHolding = false;//verifica se a tecla rotate este sendo pressionada;
        }
        //Game Logic;
        if(fDown)//se a peca for forcada para baixo...
        {
            if(FitPiece(currentPiece, currentRotation, currentX, currentY+1))
            {
                currentY++;//joga a peca para baixo se puder;
            }
            else//se nao puder;
            {
                for(int i = 0; i < 4; ++i)
                {
                    for(int j = 0; j < 4; ++j)
                    {
                        if(pieces[currentPiece][Rotate(i, j, currentRotation)] != L'.')
                        {
                            field[(currentY + j) * fieldWidth + (currentX + i)] = 3;//fixa a peca no mapa;
                        }
                    }
                }
                //Line Checker
                for(int j = 0; j < 4; ++j)
                {
                    if(currentY + j < fieldHeight - 1)
                    {
                        lineExists = true;
                        for(int i = 1; i < fieldWidth - 1; ++i)
                        {
                            lineExists &= (field[(currentY + j) * fieldWidth + i]) != 0;
                        }
                        if(lineExists)
                        {
                            for(int i = 1; i < fieldWidth - 1; ++i)
                            {
                                field[(currentY + j) * fieldWidth + i] = 2;
                            }
                            lines.push_back(currentY + j);
                        }
                    }
                }
                currentPiece = rand()%7;//pega outra peca;
                currentRotation = 0;//reseta a posicao;
                currentX = 6;//reseta o x;
                currentY = 0;//reseta o y;
                gameOver = !FitPiece(currentPiece, currentRotation, currentX, currentY);//verifica se ha espaco para a criacao de outra peca, se nao perdeu;
            }
            speedCounter = 0;

        }
        //Draw Field;
        for(int i = 0; i < fieldWidth; ++i)
        {
            for(int j = 0; j < fieldHeight; ++j)
            {
                screen[(j) * screenWidth + (i)] = L" ▓~#"[field[j * fieldWidth + i]];//desenha o mapa com 0 e # nas bordas;
            }
        }
        //Draw Current Piece;
        for(int i = 0; i < 4; ++i)
        {
            for(int j = 0; j < 4; ++j)
            {
                if(pieces[currentPiece][Rotate(i, j, currentRotation)] != L'.')
                {
                    screen[(currentY + j) * screenWidth + (currentX + i)] = 178;
                }
            }
        }
        //Output;
        if(!lines.empty())
        {
            WriteConsoleOutputCharacter(console, (const char*)screen, screenWidth * screenHeight,{0,0}, &bytesWritten);
            this_thread::sleep_for(200ms);
            for(int &l : lines)
            {
                for(int i = 1; i < fieldWidth; ++i)
                {

                    for(int j = l; j > 0; --j)
                    {
                        field[j * fieldWidth + i] = field[(j - 1) * fieldWidth + i];
                    }
                    field[i] = 0;
                }
            }
            lines.clear();

        }
        //Display the Screen;
        WriteConsoleOutputCharacter(console, (const char*)screen, screenWidth * screenHeight,{0,0}, &bytesWritten);
    }

    return 0;
}
