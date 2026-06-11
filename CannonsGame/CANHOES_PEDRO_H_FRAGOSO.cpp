#include<iostream>
#include<cmath>
#include<conio.h>
#include<windows.h>
#include<cstdlib>
#include<time.h>
#include<fstream>
#include<string>
#include"MD5.h"

#define PI 3.14159
#define G 20

typedef struct{
    bool b[8]={0};
}BITE;
using namespace std;
////////////////////////////////////////////////////////////////////////////////////////////////

BITE bin(int &num, BITE bi)
{
    int index = 0;
    while(num>0)
    {
        bi.b[index] = num%2;
        num /= 2;
        index++;
    }
    index--;

    return bi;
}
////////////////////////////////////////////////////////////////////////////////////////////////
void bubble_sort(int dec_list[20], string lista[20])
{
    string aux_lista;
    int aux = 0;

    for(int x = 0; x<20-1; x++){
        for(int i = 0;i<(20-1-x);i++){
            if(dec_list[i]>dec_list[i+1]){
                aux = dec_list[i];
                dec_list[i] = dec_list[i+1];
                dec_list[i+1] = aux;

                aux_lista = lista[i];
                lista[i] = lista[i+1];
                lista[i+1] = aux_lista;
            }
        }
    }
    for(int i = 19;i>=0;i--){
        //system("cls");
        cout<<lista[i]<<" "<<dec_list[i]<<"\n";
     }
}
////////////////////////////////////////////////////////////////////////////////////////////////
void hall_da_fama(string champ, int points)
{
//// barra em binario 00101111
   BITE bi;
   BITE bi_dec;
   MD5 md5;

    fstream hall;
    fstream best_of_five;
    int index = 0;
    int ascii_num = 0;
    int pontuacao = points;

    hall.open("hall_of_fame.txt", ios::app);
    if(hall.is_open())
    {
    for(int i = 0; i<champ.length(); i++)
    {
        ascii_num = (int)champ[i];
        bi=bin(ascii_num, bi);
        for(int h=7;h>=0;h--){
            hall<<bi.b[h];
        }
    }

    hall<<"00101111";

    //hall<<"00000010";

    bi_dec=bin(pontuacao, bi_dec);
    for(int h=7;h>=0;h--){
        hall<<bi_dec.b[h];
    }

    hall<<endl;

    hall.close();

    }else{
        cout<<"erro ao escrever no arquivo";
    }

    best_of_five.open("best_of_five.txt", ios::out);

    if(best_of_five.is_open())
    {
    best_of_five<<(md5.digestFile("hall_of_fame.txt"));
    }else{
        cout<<"erro ao escrever o mdf";
    }
    best_of_five.close();

}
int bin_to_int(string line)
{
    int inteiro = 0;
    int base = 1;
    int index = 0;

    for(int i = 7; i>=0;i--)
    {
    base = pow(2, 7-i);
    inteiro = inteiro + (line[i]-'0')*base;
    }

    return inteiro;
}
void get_hall(){
    MD5 md5;
    fstream hall;
    fstream best_of_five;
    string line;
    string line_md5;
    int inteiro = 0;
    int length = 8;
    string mdf;
    string mdfive;
    string lista[20] = {"a"};
    int dec_list[20] = {0};
    bool dec = false;
    int index = 0;
    string letter;

    hall.open("hall_of_fame.txt", ios::in);
    mdfive = (md5.digestFile("hall_of_fame.txt"));
    best_of_five.open("best_of_five.txt");

    while(getline(best_of_five, line_md5))
    {
        mdf = line_md5;
    }

string a_champ;
if(mdf == mdfive)
{
    while(getline(hall, line))
    {
            for(int i = 0; i<line.length(); i+=8)
            {
                    inteiro = bin_to_int(line.substr(i, 8));
                    if(inteiro==47)
                    {
                        dec=true;
                    }else if(dec==true)
                    {
                        dec_list[index] = inteiro;
                        lista[index] = a_champ;
                        index++;
                    }else{
                        letter = (char)inteiro;
                        a_champ.append(letter);
                    }
            }
        dec = false;
        a_champ.erase();
    }
    bubble_sort(dec_list, lista);
}else{
    //cout<<mdf<<endl;
    //cout<<mdfive<<endl;
    cout<<"o arquivo foi alterado";
}
    hall.close();
    best_of_five.close();

}

////////////////////////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////DESLOCAMENTO EM TELA///////////////////////////////////////
void gotoxy(int x, int y)
{
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){x,y});
}

void del(int x, int y)
{
    gotoxy(x, y);
    cout<<" ";
}

void draw(int x, int y, int aparence)
{
    gotoxy(x, y);
    cout<<(char)aparence;
}
/////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////

void gauge_speed(int &speed)
{
    int gauge_x = 11;
    int go_back = -1;
    char espace = 'q';
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);

    while(1){
        Sleep(50);
        gotoxy(gauge_x, 27);
        if(gauge_x<=12)
        {
            if(go_back==1)
            {
                cout<<" ";
            }else{
                SetConsoleTextAttribute(hCon, FOREGROUND_GREEN);
                cout<<(char)219;
            }
        }else if((gauge_x>12)&&(gauge_x<=24))
        {
            if(go_back==1)
            {
                cout<<" ";
            }else{
            SetConsoleTextAttribute(hCon, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
            cout<<(char)219;
            }
        }else if((gauge_x>24)&&(gauge_x<=36))
        {
            if(go_back==1)
            {
                cout<<" ";
            }else{
            SetConsoleTextAttribute(hCon, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
            cout<<(char)219;
            }
        }else if((gauge_x>36)&&(gauge_x<=48))
        {
            if(go_back==1)
            {
                cout<<" ";
            }else{
                SetConsoleTextAttribute(hCon, FOREGROUND_INTENSITY | FOREGROUND_RED);
                cout<<(char)219;
            }
        }else if((gauge_x>48)&&(gauge_x<=60))
        {
           if(go_back==1)
           {
               cout<<" ";
           }else{
                SetConsoleTextAttribute(hCon, FOREGROUND_RED);
                cout<<(char)219;
           }
        }
        if(gauge_x==61){
                go_back *= -1;
        }else if((gauge_x>=10)&&(go_back==-1))
        {
            gauge_x++;
        }
        if(go_back==1)
        {
          gauge_x--;
        }
        if(gauge_x==10)
        {
            go_back *= -1;
        }
        if(kbhit())
        {
            espace = getch();
            if(espace == (char)32);
                speed = gauge_x;
                break;
        }

    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////CALCULA AS PROPRIEDADES DO VENTO
void get_wind(int &vx_wind, int &vy_wind )
{
    gotoxy(0, 25);
    cout<<"                                         ";
    gotoxy(0, 26);
    cout<<"                                         ";

    int v_wind = rand()%10;
    gotoxy(0, 25);
    cout<<"intensidade do vento: "<<v_wind<<"m/s*s";
    int w_wind = rand()%8;

/*
    N = 0
    NE = 1
    E = 2
    SE = 3
    S = 4
    SW = 5
    W = 6
    NW = 7
*/

    switch(w_wind)
    {
    case 0:
        vy_wind = v_wind;
        gotoxy(0, 26);
        cout<<"vento sentido: N";
        break;
    case 1:
        vy_wind = v_wind/2;
        vx_wind = v_wind/-2;
        gotoxy(0, 26);
        cout<<"vento sentido: NE";
        break;
    case 2:
        vx_wind = v_wind*(-1);
        gotoxy(0, 26);
        cout<<"vento sentido: E";
        break;
    case 3:
        vy_wind = v_wind/-2;
        vx_wind = v_wind/-2;
        gotoxy(0, 26);
        cout<<"vento sentido: SE";
        break;
    case 4:
        vy_wind = v_wind*(-1);
        gotoxy(0, 26);
        cout<<"vento sentido: S";
        break;
    case 5:
        vy_wind = v_wind/-2;
        vx_wind = v_wind/2;
        gotoxy(0, 26);
        cout<<"vento sentido: SW";
        break;
    case 6:
        vx_wind = v_wind;
        gotoxy(0, 26);
        cout<<"vento sentido: W";
        break;
    case 7:
        vy_wind = v_wind/2;
        vx_wind = v_wind/2;
        gotoxy(0, 26);
        cout<<"vento sentido: NW";
        break;
    default:
        break;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////O ANGULO DO MOVIMENTO
void get_angulo(double &angulo)
{
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hCon, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    gotoxy(0, 28);
    cout<<"angulo: "<<angulo;
   do{
    if(kbhit())
    {
        char SETINHA = getch();
        if(SETINHA == (char)72)
        {
            if(angulo+1 == 80)
            {
                angulo = angulo;
            }else
            {
            angulo++;
            gotoxy(0, 28);
            cout<<"angulo: "<<angulo;
            }
        }
         if(SETINHA == (char)80)
        {
            if(angulo == 0)
            {
                angulo = angulo;
            }else
            {
            angulo--;
            gotoxy(0, 28);
            cout<<"angulo: "<<angulo;
            }
        }
    }
}while(getch()!=char(32));
}

/////////////////////////////////////LANCAMENTO DA PARTICULA ESQUERDA/////////////////////////////////////
void lancamento_L(int &x, int &y, int speed, double a, int vy_wind, int vx_wind, int b, int c, int &vidas, int &hits, int mapa[24][123], bool &hit)
{
    int v[2] = {0};
    int y0 = y;
    hit = false;
    int x0 = x;
    float t = 0.0;
    a = (a*PI)/180;
    //cout<<a<<" ";

    v[0] = speed*cos(a);
    v[1] = speed*sin(a);

    //cout<<v[0]<<" "<<v[1]<<" ";

    while(1)
    {
       del(x, y);

        x = x0 + v[0]*t + ((vx_wind/2)) * (t*t);
        y = y0 - v[1]*t + ((G + vy_wind)/2) * (t*t);

    if(y>=0)
    {
        for(int i = 0; i<2; i++)//verica em uma area se tank azul esta perto;
        {
            for(int z = 0; z<10; z++)
            {
                if(x==b+z && y==c+i)
                    {
                            hit = true;
                    }
            }
            cout<<endl;
        }
    }

        if(hit==true)
        {
            hits++;
            vidas--;
            break;
        }

    if(y>=0)
    {
        if((mapa[y][x]==(char)35)||(mapa[y][x]==(char)123)||(mapa[y][x]==(char)125)||(mapa[y][x]==(char)124)||(mapa[y][x]==(char)47)||(mapa[y][x]==(char)92)||(mapa[y][x]==(char)45)||(mapa[y][x]==(char)44)||(mapa[y][x]==(char)95))
        {
          //cout<<mapa[y][x];
          break;
        }
    }

        if((y > y0+2)||(x >= 123)){
            //cout<<"saiu do mpa";
            break;
        }else if(y >= 0){
           draw(x, y, 79);
        }

        t = t + 0.01;
        Sleep(2);
    }
    x = x0;
    y = y0;

}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void lancamento_R(int &x, int &y, int speed, double a, int vy_wind, int vx_wind, int b, int c, int &vidas, int &hits, int mapa[24][123], bool &hit)
{
    int v[2] = {0};
    int y0 = y;
    hit = false;
    int x0 = x;
    float t = 0.0;
    a = (a*PI)/180;
    //cout<<a<<" ";

    v[0] = speed*cos(a);
    v[1] = speed*sin(a);

    //cout<<v[0]<<" "<<v[1]<<" ";

    while(1)
    {
       del(x, y);

        x = x0 - v[0]*t + ((vx_wind/2)) * (t*t);
        y = y0 - v[1]*t + ((G + vy_wind)/2) * (t*t);

    if(y>=0)
    {
        for(int i = 0; i<3; i++)//verica em uma area se tank vermelho foi atingido;
        {
            for(int z = 0; z<11; z++)
            {
                if(x==b-z && y==c+i)
                    {
                        hit = true;
                    }
            }
            cout<<endl;
        }
    }

        if(hit==true)
        {
            hits++;
            vidas--;
            break;
        }

    if(y>=0)
    {
         if((mapa[y][x]==(char)35)||(mapa[y][x]==(char)123)||(mapa[y][x]==(char)125)||(mapa[y][x]==(char)124)||(mapa[y][x]==(char)47)||(mapa[y][x]==(char)92)||(mapa[y][x]==(char)45)||(mapa[y][x]==(char)44)||(mapa[y][x]==(char)95))
        {
          //cout<<mapa[y][x];
          break;
        }
    }


        if((y > y0+2)||(x <= 0)){
            // cout<<"saiu do mpa";
            break;
        }else if(y >= 0){
           draw(x, y, 79);
        }

        t = t + 0.01;
        Sleep(2);
    }
    x = x0;
    y = y0;

}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void get_vidas(int lifes, int red_or_blue)
{
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    if(red_or_blue==1)
    {
        gotoxy(0, 24);
        cout<<"                                          ";
        SetConsoleTextAttribute(hCon, FOREGROUND_INTENSITY | FOREGROUND_RED);
        gotoxy(0, 24);
        for(int a = lifes; a>0; a--)
        {
            cout<<"S2 ";
        }
    }else{
        gotoxy(107, 24);
        cout<<"                                          ";
        SetConsoleTextAttribute(hCon, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
        gotoxy(107, 24);
        for(int a = lifes; a>0; a--)
        {
            cout<<" S2";
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////RAMDOMIZA A POSICAO DOS CANHOES
void draw_cannon(int &x, int y, int cannon_L[3][12], int cannon_R[3][12], int red_or_blue)
{
    int i, z;
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);

    if(red_or_blue==1)
    {
            for(i = 0; i<3; i++){
                gotoxy(x-11, y+i);
                    for(z = 0; z<12; z++){
                        cout<<" ";
                }
                cout<<endl;
            }

            do{
                x = rand()%41;
            }while(x<12);

            SetConsoleTextAttribute(hCon, FOREGROUND_INTENSITY | FOREGROUND_RED);
            for(i = 0; i<3; i++){
                gotoxy(x-11, y+i);
                    for(z = 0; z<12; z++){
                        cout<<(char)cannon_L[i][z];
                    }
                cout<<endl;
            }

    }else{
            for(i = 0; i<3; i++){
                gotoxy(x, y+i);
                    for(z = 0; z<12; z++){
                        cout<<" ";
                }
                cout<<endl;
            }

            do{
                x = rand()%110;
            }while(x<=82);

            SetConsoleTextAttribute(hCon, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
            for(i = 0; i<3; i++){
                gotoxy(x, y+i);
                    for(z = 0; z<12; z++){
                        cout<<(char)cannon_R[i][z];
                    }
                cout<<endl;
            }
    }

}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void menu (int &index)
{
    index=0;
    int z, i;
    char SETINHA = 'a';
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(hCon, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
    gotoxy(56, 25);
    cout<<"PRECIONE <ESPACO> PARA SELECIONAR";

    int title [6][42] = {{32,95,95,95,95,95,95,95,32,32,95,95,32,32,32,32,95,95,32,32,32,95,95,32,95,95,32,95,95,32,92,92,32,32,95,95,95,95,95,32,32,32},
                        {124,32,32,32,32,32,32,32,124,32,47,95,92,32,32,32,124,124,92,32,32,124,124,32,124,124,32,47,47,32,32,32,32,47,32,95,95,95,95,92},
                        {39,39,39,124,32,124,39,39,39,47,47,95,92,92,32,32,124,124,92,92,32,124,124,32,124,124,47,47,32,32,32,32,40,32,40,95,95,95,95,32},
                        {32,32,32,124,32,124,32,32,47,47,45,45,45,92,92,32,124,124,32,92,92,124,124,32,124,124,92,92,32,32,32,32,32,92,95,95,95,32,32,92},
                        {32,95,95,124,95,124,95,47,47,95,95,95,95,95,92,92,124,124,95,95,92,124,124,95,124,124,95,92,92,95,32,32,32,95,95,95,32,41,32,32,41,32},
                        {32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,47,95,95,95,95,95,47,32,32}};


    for(i = 0; i<6; i++){
       gotoxy(53, 10+i);
        for(z = 0; z<42; z++){
          cout<<(char)title[i][z];
        }
        cout<<endl;
    }


    SetConsoleTextAttribute(hCon, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    gotoxy(65, 18);
    cout<<"HALL DA FAMA";
    gotoxy(65, 19);
    cout<<"CREDITO";
    gotoxy(65, 20);
    cout<<"CONTROLES";
    SetConsoleTextAttribute(hCon, FOREGROUND_INTENSITY | FOREGROUND_RED);
    gotoxy(65, 17);
    cout<<"JOGAR";

    do{
    if(kbhit())
    {
        char SETINHA = getch();
        if(SETINHA == (char)80)
        {
            if(index+1 > 3)
            {
                index = index;
            }else
            {
            index++;
                if(index==0)
                {
                    SetConsoleTextAttribute(hCon, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                    gotoxy(65, 20);
                    cout<<"CONTROLES";
                    gotoxy(65, 19);
                    cout<<"CREDITOS";
                    gotoxy(65, 18);
                    cout<<"HALL DA FAMA";
                    SetConsoleTextAttribute(hCon, FOREGROUND_INTENSITY | FOREGROUND_RED);
                    gotoxy(65, 17);
                    cout<<"JOGAR";
                }
                if(index==1)
                {
                    SetConsoleTextAttribute(hCon, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                    gotoxy(65, 17);
                    cout<<"JOGAR";
                    gotoxy(65, 19);
                    cout<<"CREDITOS";
                    gotoxy(65, 20);
                    cout<<"CONTROLES";
                    SetConsoleTextAttribute(hCon, FOREGROUND_INTENSITY | FOREGROUND_RED);
                    gotoxy(65, 18);
                    cout<<"HALL DA FAMA";
                }
                if(index==2)
                {
                    SetConsoleTextAttribute(hCon, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                    gotoxy(65, 17);
                    cout<<"JOGAR";
                    gotoxy(65, 18);
                    cout<<"HALL DA FAMA";
                    gotoxy(65, 20);
                    cout<<"CONTROLES";
                    SetConsoleTextAttribute(hCon, FOREGROUND_INTENSITY | FOREGROUND_RED);
                    gotoxy(65, 19);
                    cout<<"CREDITOS";
                }
                if(index==3)
                {
                    SetConsoleTextAttribute(hCon, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                    gotoxy(65, 17);
                    cout<<"JOGAR";
                    gotoxy(65, 18);
                    cout<<"HALL DA FAMA";
                    gotoxy(65, 19);
                    cout<<"CREDITOS";
                    SetConsoleTextAttribute(hCon, FOREGROUND_INTENSITY | FOREGROUND_RED);
                    gotoxy(65, 20);
                    cout<<"CONTROLES";
                }
            }
        }
         if(SETINHA == (char)72)
        {
            if(index-1 < 0)
            {
                index = index;
            }else
            {
            index--;
            if(index==0)
                {
                   SetConsoleTextAttribute(hCon, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                    gotoxy(65, 19);
                    cout<<"CREDITOS";
                    gotoxy(65, 18);
                    cout<<"HALL DA FAMA";
                    gotoxy(65, 20);
                    cout<<"CONTROLES";
                    SetConsoleTextAttribute(hCon, FOREGROUND_INTENSITY | FOREGROUND_RED);
                    gotoxy(65, 17);
                    cout<<"JOGAR";
                }
                if(index==1)
                {
                    SetConsoleTextAttribute(hCon, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                    gotoxy(65, 17);
                    cout<<"JOGAR";
                    gotoxy(65, 19);
                    cout<<"CREDITOS";
                    gotoxy(65, 20);
                    cout<<"CONTROLES";
                    SetConsoleTextAttribute(hCon, FOREGROUND_INTENSITY | FOREGROUND_RED);
                    gotoxy(65, 18);
                    cout<<"HALL DA FAMA";
                }
                if(index==2)
                {
                    SetConsoleTextAttribute(hCon, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                    gotoxy(65, 17);
                    cout<<"JOGAR";
                    gotoxy(65, 18);
                    cout<<"HALL DA FAMA";
                    gotoxy(65, 20);
                    cout<<"CONTROLES";
                    SetConsoleTextAttribute(hCon, FOREGROUND_INTENSITY | FOREGROUND_RED);
                    gotoxy(65, 19);
                    cout<<"CREDITOS";
                }
                if(index==3)
                {
                    SetConsoleTextAttribute(hCon, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                    gotoxy(65, 17);
                    cout<<"JOGAR";
                    gotoxy(65, 18);
                    cout<<"HALL DA FAMA";
                    gotoxy(65, 19);
                    cout<<"CREDITOS";
                    SetConsoleTextAttribute(hCon, FOREGROUND_INTENSITY | FOREGROUND_RED);
                    gotoxy(65, 20);
                    cout<<"CONTROLES";
                }
            }
        }
    }
}while(getch()!=char(32));
}

void draw_mapa(int &choose_map, int mapa_1[24][123], int mapa_2[24][123], int mapa_3[24][123], int mapa_4[24][123], int mapa_5[24][123])
{
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    system("cls");
    SetConsoleTextAttribute(hCon, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    int z = 0;
    gotoxy(0, 0);

    if(choose_map>=5)
    {
        choose_map=0;
    }

    if(choose_map==0)
    {
        for(int i = 0; i<24; i++)
        {
            for(z = 0; z<123; z++)
            {
                cout<<(char)mapa_1[i][z];
            }
            cout<<endl;
        }
    }
    if(choose_map==1)
    {
        for(int i = 0; i<24; i++)
        {
            for(z = 0; z<123; z++)
            {
                cout<<(char)mapa_2[i][z];
            }
            cout<<endl;
        }
    }
    if(choose_map==2)
    {
        for(int i = 0; i<24; i++)
        {
            for(z = 0; z<123; z++)
            {
                cout<<(char)mapa_3[i][z];
            }
            cout<<endl;
        }
    }
    if(choose_map==3)
    {
        for(int i = 0; i<24; i++)
        {
            for(z = 0; z<123; z++)
            {
                cout<<(char)mapa_4[i][z];
            }
            cout<<endl;
        }
    }
    if(choose_map==4)
    {
        for(int i = 0; i<24; i++)
        {
            for(z = 0; z<123; z++)
            {
                cout<<(char)mapa_5[i][z];
            }
            cout<<endl;
        }
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(){

    //envia um ALT + ENTER para o console (tela cheia)
    keybd_event ( VK_MENU, 0x36, 0, 0 );
    keybd_event ( VK_RETURN, 0x1C, 0, 0 );
    keybd_event ( VK_RETURN, 0x1C, KEYEVENTF_KEYUP, 0 );
    keybd_event ( VK_MENU, 0x38, KEYEVENTF_KEYUP, 0 );

    double angulo = 45;
    int vx_wind = 0;
    int vy_wind = 0;
    int opcao = 0;
    int points = 1;
    srand(time(NULL));

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
string line;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////// //VARIAVEIS DOS CANHOES

typedef struct//Canhao da esquerda
{
    int x, y, speed, lifes, hits;
    bool hit;
}Cannon_Left;
Cannon_Left cl;
cl.x = 12;
cl.y = 20;
cl.hits = 0;
cl.lifes = 5;
cl.speed = 40;
cl.hit = false;

typedef struct//Canhao da direita
{
    int x, y, speed, lifes, hits;
    bool hit;
}Cannon_Right;
Cannon_Right cr;
cr.x = 108;
cr.y = 20;
cr.hits = 0;
cr.lifes = 5;
cr.speed = 40;
cr.hit = false;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////CONFIGURA OS OBJETOS "FRONT-END"
    CONSOLE_CURSOR_INFO ConCurInf; //este � o objeto que configura o cursor
    ConCurInf.dwSize = 0; //este � o tamanho do cursor, que vai de 0% a 100%
    ConCurInf.bVisible = FALSE; //este atributo o deixa visivel ou n�o
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ConCurInf);

    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);//objeto que configura as cores dos caracteres

    /*
    BLACK             = 0,
    DARKBLUE          = FOREGROUND_BLUE,
    DARKGREEN         = FOREGROUND_GREEN,
    DARKCYAN          = FOREGROUND_GREEN | FOREGROUND_BLUE,
    DARKRED           = FOREGROUND_RED,
    DARKMAGENTA       = FOREGROUND_RED | FOREGROUND_BLUE,
    DARKYELLOW        = FOREGROUND_RED | FOREGROUND_GREEN,
    DARKGRAY          = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
    GRAY              = FOREGROUND_INTENSITY,
    BLUE              = FOREGROUND_INTENSITY | FOREGROUND_BLUE,
    GREEN             = FOREGROUND_INTENSITY | FOREGROUND_GREEN,
    CYAN              = FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE,
    RED               = FOREGROUND_INTENSITY | FOREGROUND_RED,
    MAGENTA           = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE,
    YELLOW            = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN,
    WHITE             = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
    */

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
int basea  [24][123] = {{35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35}};
*/
int mapa_1 [24][123] = {{35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35,35,35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35,35,35,35,35,35,35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35,35,35,35,35,35,35,35,35,35,35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35,35,35,35,35,35,35,35,35,35,35,35,35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35}};



int mapa_2 [24][123] =  {{35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,46,32,32,32,32,46,32,32,32,32,32,46,32,32,32,32,32,46,32,32,32,32,46,32,32,32,46,42,32,32,46,32,32,46,32,32,32,32,46,32,46,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,46,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,46,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35,32,32,32,46,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,46,32,46,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,42,32,32,35,32,32,46,32,32,32,32,46,32,32,32,32,32,32,46,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,46,46,32,46,32,46,32,32,32,32,35,35,35,32,32,32,46,32,32,32,32,46,32,32,32,32,32,32,46,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,42,32,46,32,32,32,32,32,32,32,32,32,42,32,35,35,35,35,35,32,32,32,32,32,32,32,32,32,32,46,32,32,32,32,32,32,32,32,46,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,46,32,32,32,32,32,46,32,32,32,46,32,32,32,32,32,35,35,35,35,35,32,32,32,32,32,32,42,32,32,32,32,42,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,46,32,32,32,32,32,32,32,32,32,32,32,32,35,35,35,35,35,32,46,32,46,32,32,32,32,32,32,32,32,32,32,42,46,32,46,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,46,32,32,46,32,46,32,32,46,32,46,32,35,35,35,35,35,46,32,32,32,32,32,32,32,46,35,35,35,35,35,32,32,32,32,32,32,32,46,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,46,32,35,35,32,32,32,32,32,32,35,35,35,35,35,32,32,32,32,46,32,32,32,32,35,35,35,35,35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,46,32,46,32,32,32,32,32,35,35,35,46,32,32,32,46,35,35,35,35,35,32,32,42,32,32,32,35,32,32,35,35,35,35,35,46,32,32,32,46,32,46,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,42,32,32,32,32,46,35,35,35,32,32,32,32,35,35,35,35,35,32,32,32,32,32,35,35,32,32,35,35,35,35,35,46,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,46,32,35,35,35,35,35,32,46,32,35,35,35,35,35,32,32,32,32,35,35,35,32,46,35,35,35,35,35,32,32,32,35,35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35,35,35,35,35,35,32,32,35,35,35,35,35,32,42,32,35,35,35,35,32,32,35,35,35,35,35,32,32,35,35,35,35,32,46,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,46,32,35,35,35,35,32,32,35,35,35,35,35,35,32,32,35,35,35,35,35,32,32,35,35,35,35,35,32,32,35,35,35,35,35,32,32,35,35,35,35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35,35,35,35,32,32,35,35,35,35,35,35,32,46,35,35,35,35,35,32,32,35,35,35,35,35,46,32,35,35,35,35,35,46,32,35,35,35,35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,46,32,32,35,35,35,35,32,46,35,35,35,35,35,35,32,32,35,35,35,35,35,32,32,35,35,35,35,35,32,32,35,35,35,35,35,32,32,35,35,35,35,32,46,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,46,35,35,35,35,32,32,35,35,35,35,35,35,32,32,35,35,35,35,35,32,32,35,35,35,35,35,32,32,35,35,35,35,35,32,32,35,35,35,35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,46,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,46,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35}};



int mapa_3 [24][123] = {{35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,124,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,92,124,32,32,32,32,124,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,92,124,32,32,32,45,32,32,32,92,124,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,45,45,45,92,32,32,32,32,92,32,32,32,124,32,124,32,47,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,92,124,32,32,32,44,32,32,124,32,124,47,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,46,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,45,45,45,92,32,44,32,32,32,32,39,32,47,45,45,45,44,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,124,32,32,32,32,32,32,32,32,123,32,32,32,32,32,32,125,32,32,32,32,32,32,32,32,124,32,32,32,32,32,32,32,32,46,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,92,124,32,124,45,45,45,32,32,32,32,32,123,32,32,32,32,32,32,125,32,32,32,32,32,45,45,32,124,47,32,32,32,32,32,32,32,32,32,32,32,32,46,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,46,32,32,32,32,32,32,45,45,92,32,44,32,32,32,32,32,46,32,32,32,125,32,32,32,32,123,32,32,32,46,32,32,32,32,92,44,45,45,45,32,32,32,46,32,32,32,32,32,46,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,46,32,32,32,32,32,32,32,32,46,32,32,32,32,125,32,32,32,32,32,32,32,32,32,32,125,32,32,32,32,123,32,46,32,32,32,32,32,32,32,125,32,32,32,32,32,32,32,32,46,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,46,32,32,32,32,32,32,32,32,32,32,123,32,46,32,46,32,32,46,32,32,123,32,32,32,32,32,32,125,32,32,46,32,32,46,32,32,123,32,32,32,46,32,32,32,32,32,32,32,32,32,46,32,32,46,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,46,32,32,32,32,32,46,32,32,32,32,32,32,125,32,32,32,32,46,32,32,32,32,123,32,32,32,32,32,32,125,32,32,32,32,32,32,32,32,125,32,32,32,32,32,32,32,32,32,32,32,46,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,46,32,32,32,32,32,32,47,32,44,92,32,32,32,32,32,32,47,47,32,32,32,32,32,32,32,32,92,92,46,32,32,32,47,32,32,32,92,32,32,32,32,46,32,32,32,46,32,32,32,32,46,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,46,32,32,32,32,32,32,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,32,32,32,32,32,32,32,32,46,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35}};


int mapa_4 [24][123] = {{35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,45,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,45,32,45,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,47,32,32,32,92,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,45,45,32,32,32,32,32,45,45,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,47,32,32,32,32,32,32,32,32,32,92,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,47,45,45,32,92,32,47,92,32,47,92,32,47,32,45,45,92,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,47,32,32,32,32,32,35,32,32,35,32,32,35,32,32,32,32,32,92,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,47,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,92,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,47,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,92,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,47,45,45,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,45,45,92,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,47,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,92,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,47,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,92,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,47,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,92,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,47,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,92,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,47,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,92,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35}};


int mapa_5[24][123] = {{35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,124,35,35,35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,124,35,35,35,35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,124,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35,32,35,32,35,32,35,32,35,32,35,32,35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35,35,35,35,35,35,35,35,35,35,35,35,35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,124,32,32,32,32,32,32,32,32,32,32,32,124,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,95,95,95,124,95,95,95,95,95,95,95,95,95,95,95,124,95,95,95,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,124,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,124,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,124,32,32,32,32,32,32,32,32,35,35,35,32,32,32,32,32,32,32,32,124,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,124,32,32,32,32,32,32,32,32,35,32,35,32,32,32,32,32,32,32,32,124,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35,35,32,35,35,32,35,35,32,32,124,32,32,32,32,32,32,32,123,35,35,35,125,32,32,32,32,32,32,32,124,32,32,32,35,35,32,35,35,32,35,35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,124,35,35,35,35,35,124,32,32,32,124,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,124,32,32,32,124,35,35,35,35,35,124,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,124,35,35,35,35,35,124,45,45,32,45,45,32,45,45,32,45,45,32,45,45,32,45,45,32,45,45,32,45,45,45,32,45,45,124,35,35,35,35,35,124,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,124,35,35,35,35,35,124,32,32,45,32,32,45,32,32,45,32,32,45,32,32,45,32,32,45,32,32,45,32,32,32,45,32,32,124,35,35,35,35,35,124,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,124,35,35,35,35,35,124,32,32,124,32,32,124,32,32,124,32,32,124,32,32,124,32,32,124,32,32,124,32,32,32,124,32,32,124,35,35,35,35,35,124,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,124,35,35,35,35,35,124,32,32,124,32,32,124,32,32,124,32,32,124,32,32,124,32,32,124,32,32,124,32,32,32,124,32,32,124,35,35,35,35,35,124,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,124,35,35,35,35,35,124,32,32,124,32,32,124,32,32,124,32,32,124,32,32,124,32,32,124,32,32,124,32,32,32,124,32,32,124,35,35,35,35,35,124,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,35},
                        {35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35}};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////CANHAO DA ESQUERDA

int tank_L [3][12] = {{32,32,95,95,95,32,32,32,32,32,32},
                     {32,47,32,32,32,92,61,61,61,61,175},
                     {59,40,48,48,48,48,41,32,32,32,32}};

//////////////////////////////////////////////////////////////////////////////////////////////////
/*
175 = �
174 = �
61 = =
92 = \
47 = /
95 = _
59 = ;
48 = 0
*/
//////////////////////////////////////////////////////////////////////////////////////////////////CANHAO DA DIREITA
int tank_R [3][12] = {{32,32,32,32,32,32,95,95,95,32,32},
                     {174,61,61,61,61,47,32,32,32,92,32},
                     {32,32,32,32,123,40,48,48,48,48,41}};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Sleep(20);
system("cls");
menu(opcao);
system("cls");

int num_turns = 0;
int index_map = 0;
if(opcao == 0)
{

    while(1)
    {

    if(num_turns==0)
    {
        draw_mapa(index_map, mapa_1, mapa_2, mapa_3, mapa_4, mapa_5);
    }else if(cl.hit == true || cr.hit == true)
    {
        index_map++;
        draw_mapa(index_map, mapa_1, mapa_2, mapa_3, mapa_4, mapa_5);
    }

        get_vidas(cl.lifes, 1);
        get_vidas(cr.lifes, 2);

        draw_cannon(cl.x, cl.y, tank_L, tank_R, 1);
        draw_cannon(cr.x, cr.y, tank_L, tank_R, 2);

        gotoxy(0, 27);
        SetConsoleTextAttribute(hCon, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        cout<<"GAUGE:";

        SetConsoleTextAttribute(hCon, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        get_wind(vx_wind, vy_wind);

        if(cl.lifes<=0)
        {
            system("cls");
            SetConsoleTextAttribute(hCon, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
            cout<<"!!!o tank azul venceu!!!\n";
            points = (5+(-cr.lifes-5))*-100/num_turns;
            cout<<"seus pontos: "<<points;
            break;
        }

        //TURNO DO VERMELHO(ESQUERDA)
            get_angulo(angulo);
            gauge_speed(cl.speed);

            SetConsoleTextAttribute(hCon, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            if(index_map==0){
                lancamento_L(cl.x, cl.y, cl.speed, angulo, vy_wind, vx_wind, cr.x, cr.y, cr.lifes, cl.hits, mapa_1, cl.hit);
            }

            if(index_map==1){
                lancamento_L(cl.x, cl.y, cl.speed, angulo, vy_wind, vx_wind, cr.x, cr.y, cr.lifes, cl.hits, mapa_2, cl.hit);
            }

            if(index_map==2){
                lancamento_L(cl.x, cl.y, cl.speed, angulo, vy_wind, vx_wind, cr.x, cr.y, cr.lifes, cl.hits, mapa_3, cl.hit);
            }

            if(index_map==3){
                lancamento_L(cl.x, cl.y, cl.speed, angulo, vy_wind, vx_wind, cr.x, cr.y, cr.lifes, cl.hits, mapa_4, cl.hit);
            }

            if(index_map==4){
                lancamento_L(cl.x, cl.y, cl.speed, angulo, vy_wind, vx_wind, cr.x, cr.y, cr.lifes, cl.hits, mapa_5, cl.hit);
            }

            get_vidas(cr.lifes, 2);

            gotoxy(9, 27);
            cout<<"                                                                                                    ";
        //TURNO DO AZUL(DIREITA)
        if((cl.hit == false) && (cr.lifes>0))
        {
            get_angulo(angulo);
            gauge_speed(cr.speed);

            SetConsoleTextAttribute(hCon, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

            if(index_map==0)
            {
                lancamento_R(cr.x, cr.y, cr.speed, angulo, vy_wind, vx_wind, cl.x, cl.y, cl.lifes, cr.hits, mapa_1, cr.hit);
            }
            if(index_map==1)
            {
                lancamento_R(cr.x, cr.y, cr.speed, angulo, vy_wind, vx_wind, cl.x, cl.y, cl.lifes, cr.hits, mapa_2, cr.hit);
            }
            if(index_map==2)
            {
                lancamento_R(cr.x, cr.y, cr.speed, angulo, vy_wind, vx_wind, cl.x, cl.y, cl.lifes, cr.hits, mapa_3, cr.hit);
            }
            if(index_map==3)
            {
                lancamento_R(cr.x, cr.y, cr.speed, angulo, vy_wind, vx_wind, cl.x, cl.y, cl.lifes, cr.hits, mapa_4, cr.hit);
            }
            if(index_map==4)
            {
                lancamento_R(cr.x, cr.y, cr.speed, angulo, vy_wind, vx_wind, cl.x, cl.y, cl.lifes, cr.hits, mapa_5, cr.hit);
            }

            gotoxy(9, 27);
            cout<<"                                                                                                     ";
        }else if(cr.lifes<=0)
        {
            system("cls");
            SetConsoleTextAttribute(hCon, FOREGROUND_INTENSITY | FOREGROUND_RED);
            cout<<"!!!o tank vermelho ganhou!!!\n";
            points = (5+(-cl.lifes-5))*-100/num_turns;
            cout<<"seus pontos: "<<points;
            break;
        }
        num_turns++;
    }
    SetConsoleTextAttribute(hCon, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    cout<<endl;
    cout<<"DIGITE O NOME DO CAMPEAO(UTILIZE UNDERLINE PARA OS ESPACOS): ";
    cin>>line;
    hall_da_fama(line, points);

}
if(opcao == 1)
{
    SetConsoleTextAttribute(hCon, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    get_hall();
}
if(opcao == 2)
{
    SetConsoleTextAttribute(hCon, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    cout<<"AUTOR: PEDRO HENRIQUE FRAGOSO DE JOGOS DIGITAIS 1.\n";
    cout<<"COM AJUDA DE LUAN (MONITOR), PEDRO(MONITOR) e DR.ALBINI.";
}
if(opcao == 3)
{
    SetConsoleTextAttribute(hCon, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    gotoxy(0, 0);
    cout<<"NO SEU TURNO VOCE DEVERA PRIMEIRO DEFINIR O ANGULO DE LANCAMENTO.\n";
    cout<<"PARA ISSO VOCE DEVERA USAR AS SETINHAS PARA AUMENTAR OU DIMINUIR O ANGULO.\n";
    cout<<"QUANDO ENCONTRAR O ANGULO DESEJADO PRESSIONE <ESPACO>.\n";
    cout<<"COM O ANGULO DEFINIDO O GAUGE APARECERA E FICARA OCILANDO.\n";
    cout<<"QUANTO MAIS PROXIMA DO VERDE A COR FOR, MAIS FRACA SERA A VELOCIDADE INICIAL DO PROJETIL.\n";
    cout<<"QUANTO MAIS PROXIMO DO VERMELHO, MAIOR SERA A VELOCIDADE INICIAL.\n";
    cout<<"NO MOMENTO QUE O GAUGE ESTIVER NA FORCA DESEJADA PRESSIONE <ESPACO> PARA DISPARAR O CANHAO.\n";

}

 return 0;
}
