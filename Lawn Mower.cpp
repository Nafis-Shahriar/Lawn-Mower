#include<stdio.h>
#include<graphics.h>
#include<string.h>
#include<iostream>
#include<bits/stdc++.h>

using namespace std;

int ar[500][500],ri,rj;
char my_name[15];
int LEFT,top,RIGHT,bottom,point=-1,final_point;
int mv[2]= {26,-26};
void level_1();
void level_2();
void level_3();
void initialize(int lvl);

void print_fence();
void draw_bg();
void highscr();
void print_grass(int i,int j);
void print_stone(int i,int j);
void print_dot(int i,int j);
void print_tree(int i,int j);
void show_leaderboard();

int move_cutter(int k,char c);
int difficulty();
int intro();
int level();

int main()
{
    int gd = DETECT,gm;
    initgraph(&gd, &gm, "C:\\TC\\BGI");
    setbkcolor(BLUE);
    int k=0;
    char pnt[100];
    char pp[100];
    char ppp[100];
    int intr=intro();
    while(intr==2)
    {
        show_leaderboard();
        getch();
        intr=intro();
    }
    if(intr==3)return 0;
    cleardevice();
    outtextxy(130,130,"Enter Your Name: ");
    scanf("%s",my_name);
    int q,d=difficulty();
    int lvl=1;
    while(1)
    {
        initialize(lvl);
        while(1)
        {
            print_fence();
            draw_bg();
            settextstyle(8, 0, 1);
            sprintf(pnt,"POINTS = %2d",point);
            outtextxy(80, 50, pnt);
            char c;
            if(kbhit())
            {
                c=getch();
            }
            q=move_cutter(k,c);
            if(q==1)
            {
                cleardevice();
                break;
            }
            if(point==final_point)
            {
                cleardevice();
                q=0;
                break;
            }
            for(int i=93; i<=418; i+=26)
            {
                for(int j=93; j<=418; j+=26)
                {
                    if(ar[i][j]==1)print_stone(i,j);
                    else if(ar[i][j]==-1)print_dot(i,j);
                    else if(ar[i][j]==2)print_tree(i,j);
                    else if((i!=93||j!=93)&&ar[i][j]==0)
                        print_grass(i,j);
                }
            }
            delay(d*100);
        }
        if(q==1)
        {
            Beep(1000,1000);
            outtextxy(150,200,"GAME OVER");
            sprintf(pp,"Your Score = %d",point);
            outtextxy(150, 225, pp);
            freopen("Leader Board.txt","r",stdin);
            char name[20][20];
            int scr;
            for(int i=0; i<5; i++)
                gets(name[i]);
            cin>>scr;
            sprintf(ppp,"High Score = %d",scr);
            outtextxy(150, 250, ppp);

            break;
        }
        else
        {
            outtextxy(150,180,"LEVEL COMPLETE");
            sprintf(ppp,"Your Score = %d",point);
            outtextxy(150, 205, ppp);
            outtextxy(150,230,"Press any key to continue...");
            getch();
            getch();
            lvl++;
        }
    }

    getch();

    return 0;
}

int intro()
{
    settextstyle(4, 0, 2);
    outtextxy(120,130,"Welcome To Lawn Mower Game");
    cleardevice();
    outtextxy(200,170,"Press 1 to PLAY.");
    outtextxy(200,195,"Press 2 to see The leaderboard.");
    outtextxy(200,220,"Press 3 to Exit.");
    char ch=getch();
    Beep(2500,100);
    cleardevice();
    int i=ch-48;
    return i;
}

void initialize(int lvl)
{
    LEFT=80;
    top=80;
    RIGHT=106;
    bottom=106;
    ri=249;
    rj=249;
    int c=0,i=0,k=0;
    if(lvl==1)
        level_1();
    if(lvl==2)
        level_2();
    if(lvl==3)
        level_3();
}

void print_fence()
{
    setfillstyle(SOLID_FILL, 2);
    for(int i=0; i<4; i++)
    {
        rectangle(79-i, 79-i, 419+i, 419+i);
    }
}

void draw_bg()
{
    setfillstyle(SOLID_FILL,2);
    bar(80, 80, 418, 418);
}

void print_grass(int i,int j)
{
    line(j, i-7, j, i+10);
    line(j+10, i, j, i+10);
    line(j-10, i, j, i+10);
}

void print_stone(int i,int j)
{
    setfillstyle(SOLID_FILL, 8);
    circle(j,i,11);
    floodfill(j, i, WHITE);
}

void print_tree(int i,int j)
{
    setfillstyle(SOLID_FILL, 6);
    circle(j+13,i+13,26);
    floodfill(j+13, i+13, WHITE);
}

void print_dot(int i,int j)
{
    circle(j,i,2);
}

int move_cutter(int k,char c)
{
    int f=0;
    if(ar[(top+bottom)/2][(LEFT+RIGHT)/2]!=-1&&ar[(top+bottom)/2][(LEFT+RIGHT)/2]<2)
    {
        ar[(top+bottom)/2][(LEFT+RIGHT)/2]=-1;
        point+=1;
    }
    if(c==80)
    {
        top+=26;
        bottom+=26;
        f=1;
    }
    else if(c==72)
    {
        top-=26;
        bottom-=26;
        f=1;
    }
    else if(c==77)
    {
        LEFT+=26;
        RIGHT+=26;
        f=1;
    }
    else if(c==75)
    {
        LEFT-=26;
        RIGHT-=26;
        f=1;
    }
    if(ar[(top+bottom)/2][(LEFT+RIGHT)/2]>=1)return 1;

    else if(LEFT<80||RIGHT>418||top<80||bottom>418)return 1;

    setfillstyle(SOLID_FILL,14);

    bar(LEFT,top,RIGHT,bottom);
    if(f==1&&ar[(top+bottom)/2][(LEFT+RIGHT)/2]!=-1)
        Beep(1500,50);
    return 0;
}


int difficulty()
{
    cleardevice();
    settextstyle(4, 0, 2);
    outtextxy(180,130,"Enter Difficulty");
    settextstyle(3, 0, 1);
    outtextxy(200,170,"Press 1 for Easy.");
    outtextxy(200,195,"Press 2 for Medium.");
    outtextxy(200,220,"Press 3 for Hard.");
    char ch=getch();
    Beep(2500,100);
    int d=4-(ch-48);
    cleardevice();
    return d;
}

int  level()
{
    outtextxy(80,50,"Which Level ");
    outtextxy(80,60,"Enter 1 for Level 1");
    outtextxy(80,70,"Enter 2 for Level 2");
    outtextxy(80,80,"Enter 3 for Level 3");
    char ch=getch();
    Beep(2500,100);
    int lvl=ch-48;
    cleardevice();
    return lvl;
}

void level_1()
{
    memset(ar,0,sizeof(ar));
    final_point=156;
    ar[93+26][93+26]=1;
    ar[93+2*26][93+5*26]=1;
    ar[93+8*26][93+4*26]=1;
    ar[93+2*26][93+26]=1;
    ar[93+26][93+9*26]=1;
    ar[93+5*26][93+5*26]=1;
    ar[93+7*26][93+7*26]=1;
    ar[93+8*26][93+10*26]=1;

    ar[93+11*26][93+2*26]=3;
    ar[93+10*26][93+2*26]=2;
    ar[93+11*26][93+3*26]=3;
    ar[93+10*26][93+3*26]=3;

}

void level_2()
{
    memset(ar,0,sizeof(ar));
    final_point=308;
    ar[93+26][93+26]=1;
    ar[93+2*26][93+5*26]=1;
    ar[93+4*26][93+4*26]=1;
    ar[93+2*26][93+26]=1;
    ar[93+26][93+5*26]=1;
    ar[93+5*26][93+5*26]=1;
    ar[93+11*26][93+11*26]=1;
    ar[93+8*26][93+10*26]=1;
    ar[93+7*26][93+7*26]=1;

    ar[93+2*26][93+10*26]=3;
    ar[93+3*26][93+10*26]=3;
    ar[93+2*26][93+9*26]=2;
    ar[93+3*26][93+9*26]=3;

    ar[93+10*26][93+2*26]=3;
    ar[93+9*26][93+2*26]=2;
    ar[93+10*26][93+3*26]=3;
    ar[93+9*26][93+3*26]=3;
}

void level_3()
{
    memset(ar,0,sizeof(ar));
    final_point=458;

    ar[93+26][93+26]=1;
    ar[93+2*26][93+5*26]=1;
    ar[93+8*26][93+4*26]=1;
    ar[93+2*26][93+26]=1;
    ar[93+26][93+9*26]=1;
    ar[93+5*26][93+5*26]=1;
    ar[93+7*26][93+7*26]=1;
    ar[93+8*26][93+10*26]=1;
}
void show_leaderboard()
{
    cleardevice();
    char name[10][20],str[10],st[10];
    int scr[10];
    freopen("Leader Board.txt","r",stdin);
    for(int i=0; i<5; i++)
        gets(name[i]);
    for(int i=0; i<5; i++)
        cin>>scr[i];
    int j=0;
    settextstyle(4, 0, 2);
    outtextxy(130,130,"Leader Board");
    settextstyle(3, 0, 2);
    for(int i=0; i<5; i++,j+=25)
    {
        strcpy(str,name[i]);
        sprintf(st,"%s",str);
        outtextxy(160,180+j,st);
    }
    j=0;
    for(int i=0; i<5; i++,j+=25)
    {
        sprintf(st,"%d",scr[i]);
        outtextxy(260,180+j,st);
    }
}
void highscr()
{
    char name[10][20],str[10],st[10];
    int scr[10];
    freopen("Leader Board.txt","r",stdin);
    for(int i=0; i<5; i++)
        gets(name[i]);
    for(int i=0; i<5; i++)
        cin>>scr[i];
    for(int i=0; i<5; i++)
    {
        if(scr[i]>point)
        {
            for(int j=4; j>i; j--)
            {
                scr[j]=scr[j-1];
                strcpy(name[j],name[j-1]);
            }
            scr[i]=point;
            strcpy(name[i],my_name);
        }
    }
    for(int i=0; i<5; i++)
        puts(name[i]);
    for(int i=0; i<5; i++)
        cout<<scr[i];
    return ;
}
