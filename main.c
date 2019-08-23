#include <stdio.h>
#include <stdlib.h>
#include<conio.h>
#include<windows.h>
#include<stdlib.h>
#include<time.h>
#define N 20 // row
#define M 40 //column
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
int i,j, X,Y,G,head,tail,Game,Food,a,b,move,dir='d';Score =0;HighScore=0;Speed=80; // a,b used in food
int field[N][M];
FILE *f;
void snakeInitialisation()
{
    f=fopen("HighScore.txt","r");
    fscanf(f,"%d",&HighScore);
    fclose(f);
    for(i=0;i<N;i++)
    {
        for(j=0;j<M;j++)
        {
            field[i][j] = 0;
    }}

X = N/2;Y=M/2;G =Y; head =5;tail=1;Game=0;Food=0; //  0 for start ,1 for end
    for(i=0;i<head;i++)
    {
        G++;
        field[X][G - head]=i+1;
    }

}
void print()
{

    for(i=0;i<=M+1;i++)
 {
     if(i==0)
        printf("%c",201);
     else if(i==M+1)
        printf("%c",187);
     else
        printf("%c",205);
 }
 printf(" CURRENT SCORE:%d HIGHSCORE:%d",Score,HighScore);
 printf("\n");
 for(i=0;i<N;i++)
 {
     printf("%c",186);
     for(j=0;j<M;j++)
     {

         if(field[i][j]==0) printf(" ");
         if(field[i][j]>0&&field[i][j]!=head) printf("%c",176);
         if(field[i][j]==head) printf("%c",178);
         if(field[i][j]==-1) printf("%c",15);
         if(j==M-1) printf("%c\n",186);
     }
 }
 for(i=0;i<=M+1;i++)
 {
     if(i==0)
        printf("%c",200);
     else if(i==M+1)
        printf("%c",188);
     else
        printf("%c",205);
 }

}
void ResetScreenPosition(){
    HANDLE hOut;
    COORD Position;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    Position.X =0;
    Position.Y =0;
    SetConsoleCursorPosition(hOut,Position);

}
void Foods()
{
    srand(time(0)); //to make it unpredictable
    a =1+rand() % 18; // rand() used for providing any random number
    b = 1+ rand() % 38; // 48,28 for avoiding the case of food at boundary
    if(Food ==0 && field[a][b] ==0)
    {
        field[a][b] =-1;
        Food = 1;
        if(Speed>10 && Score!=0) Speed -= 15;
    }
}
int get_key()
{
    if(_kbhit())
        return _getch();
    else
        return -1;
}
void movement()
{
   move = get_key();
   move = tolower(move);
   if(((move =='d'|| move == 'a')|| (move == 'w'|| move == 's')) && (abs(dir-move))>5) dir = move;
   switch(dir){
   case 'd':  //right
    Y++;
    if(field[X][Y]!=0 && field[X][Y]!=-1) GameOver();
    if(Y==M) Y=0;
    if(field[X][Y]==-1){
            Food = 0;
            tail -= 2;
            Score+=5;
            }
    head++;
    field[X][Y] = head;
    break;
   case 'a': //left
    Y--;
    if(field[X][Y]!=0 && field[X][Y]!=-1) GameOver();
    if(Y==-1) Y = M-1;
    if(field[X][Y]==-1){
            Food = 0;
            tail -= 2;
            Score+=5;
            }
    head++;
    field[X][Y]= head;
    break;
    case 'w': //up
    X--;
    if(field[X][Y]!=0 && field[X][Y]!=-1) GameOver();
    if(X==0) X = N-1;
    if(field[X][Y]==-1){
            Food = 0;
            tail -= 2;
            Score+=5;
            }
    head++;
    field[X][Y]= head;
    break;
    case 's': //down
        X++;
        if(field[X][Y]!=0 && field[X][Y]!=-1) GameOver();
        if(X==N) X=0;
        if(field[X][Y]==-1){
            Food = 0;
            tail -= 2;
            Score+=5;
            }
        head++;
        field[X][Y] = head;
   }

}
void debugtail()
{
    for(i=0;i<N;i++){
        for(j=0;j<M;j++){
            if(field[i][j]==tail)
                field[i][j]=0;
        }
    }
    tail++;

}
void GameOver()
{
    printf("\a");
    Sleep(1500);
    system("Cls");
    if(Score>HighScore){
        printf("     New HighScore %d!!!!!!!!\n\n",Score);
        system("pause");
        f= fopen("HighScore.txt","w");
        fprintf(f,"%d",Score);
    }
    printf("\n\n                  GAME OVER !!!!!!!!!");
    printf("         SCORE :%d \n\n",Score);
    printf("         PRESS ENTER TO PLAY AGAIN OR ESC TO EXIT");
    getch();
    while(1){
        move = get_key();
        if(move ==13){
            Game =0;
            snakeInitialisation();
            break;
        }
        else if(move ==27)
        {
            Game =1;
            break;
        }
        system("Cls");
    }

}

int main()
{
    snakeInitialisation();
    while(Game==0){
 print();
 ResetScreenPosition();
 Foods();
 movement();
 debugtail();
 Sleep(Speed);
    }


}
