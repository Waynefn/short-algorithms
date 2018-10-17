#define XX 40
#define YY 24

typedef struct {
    int bit[XX][YY];
    int headx, heady;
    int tailx, taily;

} Serpent;

using namespace std;
int DIRECTION=3;
//int LEVEL=1;
int LAST_DIRECTION;
int SCORE=0;
int PAUSE=0;
int HIGHSCORE;
int HCOUNT=0;
void userInput (void*) {
    char i;
    while (true) {
        i=getch();
        int t;
        if (i>96)i=i-32;
        switch (LAST_DIRECTION) {
        case 1:
            t=2;
            break;//up
        case 2:
            t=1;
            break;//down
        case 3:
            t=4;
            break;//right
        case 4:
            t=3;
            break;//left
        }
        switch (i) {
        case 87:
            DIRECTION=1;
            break;//up
        case 83:
            DIRECTION=2;
            break;//down
        case 68:
            DIRECTION=3;
            break;//right
        case 65:
            DIRECTION=4;
            break;//left
        case 'P':
            PAUSE=!PAUSE;
        }
        if (DIRECTION==t)DIRECTION=LAST_DIRECTION;
        Sleep (30);
    }
}
void print (int ( &bit)[XX][YY]) {
    int zero[YY]= {0};
    int over20[YY]= {0};
    for (int j=0; j<YY; j++) {
        bool flag=0;
        bool flag1=0;
        for (int i=0; i<XX; i++)
            if (bit[i][j]!=0) {
                if (i>=20 && flag==0)
                    over20[j]=1, flag1=1;
                flag=1;
                zero[j]=i;
            }
        if (flag==0) zero[j]=-1;
    }
    for (int j=0; j<YY; j++) {
        if (zero[j]==-1) {
            cout<<endl;
            continue;
        }
        for (int i=0; i<XX; i++) {
            if (zero[j]>0 && i==zero[j]+1) {
                cout<<endl;
                goto l1;
            }
            if (over20[j]==1) {
                cout<<"                                        ";
                over20[j]=0;
                i=20;
            }
            switch (bit[i][j]) {
            case 0:
                cout<<"  ";
                break;
            case -1:
                cout<<"○";
                break;
            case -2:
                if (HCOUNT!=30)cout<<"●";
                else {
                    cout<<"○";
                    bit[i][j]=-1;
                }
                break;
            //case -3:cout<<"＼";bit[i+1][j+1]=-3;bit[i-1][j-1]=-3;break;
            default:
                cout<<"■";
            }
        }
l1:
        ;
    }
    cout<<"=================================================="<<"SCORE:"<<SCORE<<"   "<<"LEVEL:"<< (int)20*SCORE/ (1000)+1;
    if (PAUSE==1)cout<<"  [PAUSE]";
}
void init (Serpent& snake) {
    memset (snake.bit, 0, sizeof (snake.bit));
    for (int i=0; i<5; i++)
        snake.bit[i][0]=i+1;
    snake.headx=4;
    snake.heady=0;
    snake.tailx =0;
    snake.taily =0;
    DIRECTION=3;
    SCORE=0;
    PAUSE=0;
    LAST_DIRECTION=3;
}
void starmenu() {
    cout<<"    ████████████████████████████████████████████████████████████████████████"<<endl;
    cout<<"    ████        ██  ██████  ██████  ██████  ██████  ██████      ████████████"<<endl;
    cout<<"    ██  ██████████    ████  ████  ██  ████  ████  ██████    ████  ██████████"<<endl;
    cout<<"    ██  ██████████  ██  ██  ██  ██████  ██  ██  ██████    ██████  ██████████"<<endl;
    cout<<"    ████      ████  ████    ██  ██████  ██    ████████  ████    ████████████"<<endl;
    cout<<"    ██████████  ██  ██████  ██          ██    ████████      ████████████████"<<endl;
    cout<<"    ██████████  ██  ██████  ██  ██████  ██  ██  ██████  ████████████████████"<<endl;
    cout<<"    ██  ██████  ██  ██████  ██  ██████  ██  ████  ████    ██████  ██████████"<<endl;
    cout<<"    ████      ████  ██████  ██  ██████  ██  ██████  ████        ████████████"<<endl;
    cout<<"    ████████████████████████████████████████████████████████████████████████"<<endl;
    cout<<endl;
    cout<<"                                 BY Zhixin Li"<<endl<<endl;
    cout<<endl;
}
void food (Serpent& snake) {
    int x, y;
    srand ((int)time (0));
    while (true) {
        x=rand()% (XX-1);
        y=rand()% (YY-1);
        if ( snake.bit[x][y]==0  ) {
            if ((SCORE+10*y)% 100==0)
                snake.bit[x][y]=-1;
            else {
                HCOUNT=0;
                snake.bit[x][y]=-3;
            }
            return;
        }
    }
}
int  move (Serpent& snake) {
    LAST_DIRECTION=DIRECTION;
    int DIRECTION=::DIRECTION ;
    int x=0, y=0;
    HCOUNT++;
    int movex=0, movey=0;
    int tailnum=snake.bit[snake.tailx][snake.taily];
    int headnum=snake.bit[snake.headx][snake.heady];
    switch (DIRECTION) {
    case 1:
        y--;
        break;//up
    case 2:
        y++;
        break;//down
    case 3:
        x++;
        break;//right
    case 4:
        x--;
        break;//left
    }
    movex=snake.headx+x;
    movey=snake.heady+y;
    if (movex>XX-1 || movex<0||movey>YY-1||movey<0)return 0;
    if (snake.bit[movex][movey]>0 )return 0;
    if (snake.bit[movex][movey]<0) {
        if (snake.bit[movex][movey]==-1)
            SCORE+=10;
        else SCORE+=100;
        food (snake);
        snake.bit[movex][movey]=headnum+1;
        snake.headx=movex;
        snake.heady=movey;
    }
    else {
        snake.bit[movex][movey]=headnum+1;
        snake.headx=movex;
        snake.heady=movey;
        snake.bit[snake.tailx][snake.taily]=0;
        if (snake.bit[snake.tailx+1][snake.taily]==tailnum+1)
            snake.tailx +=1;
        else if (snake.bit[snake.tailx][snake.taily+1]==tailnum+1)
            snake.taily +=1;
        else if (snake.bit[snake.tailx-1][snake.taily]==tailnum+1)
            snake.tailx -=1;
        else if (snake.bit[snake.tailx][snake.taily-1]==tailnum+1)
            snake.taily-=1;
    }
    return 1;
}

int _tmain (int argc, _TCHAR* argv[]) {
    FILE *fp=fopen ("d:\\HIGHSCORE.TXT", "rt");
    if (fp==NULL)HIGHSCORE=0;
    else {
        int h1, h2;
        fscanf (fp, "%XZZZ9001S54154TG%d", &h1, &h2);
        HIGHSCORE=5000-h1*10;
        if (h2!=HIGHSCORE || ( HIGHSCORE<0 && HIGHSCORE>5000))HIGHSCORE=0;
        fclose (fp);
    }
    int LEVEL;
    system ("cls");
    system ("color 0e");
    starmenu();
    cout<<"                                  HIGH SCORE:"<<HIGHSCORE<<endl;
    cout<<"\tA=LEFT"<<endl<<
        "\tS=DOWN"<<endl<<"\tD=RIGHT"<<endl<<
        "\tW=UP"<<endl<<"\tP=PAUSE"<<endl<<"\t●=100"<<endl<<"\t○=10"<<endl;
    cout<<endl;
    cout<<"                                ANY KEY TO START"<<endl;
    getch();
    Serpent snake;
loop:
    system ("cls");
    init (snake);
    _beginthread (userInput, 0, NULL);
    food (snake);
    while (true) {
        if (SCORE<1500) {
            LEVEL= (int)SCORE/ (200-SCORE/8)+1;
            Sleep (2* (99-LEVEL));
        }
        else	LEVEL=100;
        system ("cls");
        if (PAUSE!=1)
            if (move (snake)==0)break;
        print (snake.bit);
    }
    system ("cls");
    starmenu();
    cout<<"                           [[-----GAME OVER-----]]"<<endl<<endl;
    cout<<"                         SCORE:"<<SCORE<<"    ANY KEY TO RESTART"<<endl;
    if (SCORE>=HIGHSCORE) {
        cout<<endl<<endl<<"                  CONGRATULATEIONS !! BREAK THE RECORD!!"<<endl;
        HIGHSCORE=SCORE;
        FILE *fp=fopen ("d:\\HIGHSCORE.TXT", "wt");
        fprintf (fp, "%XZZZ9001S54154TG%d", (5000-HIGHSCORE)/10, SCORE);
        fclose (fp);
    }
    getch();
    goto loop;
    return 0;
}
