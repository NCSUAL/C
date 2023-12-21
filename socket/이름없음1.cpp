#define _CRT_NONSTDC_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <stdio.h>
#include <conio.h>
#include <winsock2.h>
#include <windows.h>
#include <time.h>
#include <string.h>

#define randomize() srand((unsigned)time(NULL))
#define random(n) (rand() % (n))
#define delay(n) Sleep(n)
#define clrscr() system("cls")
#define gotoxy(x,y) { COORD Cur = {x, y}; \
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),Cur);}
#define showcursor(bShow) { CONSOLE_CURSOR_INFO CurInfo = {20, bShow}; \
   SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&CurInfo); }


enum { ESC = 27, LEFT = 75, RIGHT = 77, UP = 72, DOWN = 80 };
#define putsxy(x, y, s) {gotoxy(x, y);puts(s);}
#define BX 5
#define BY 1
#define BW 10
#define BH 20

void Win_OR_Lose(BOOL WIN_OR_LOSE, SOCKET Sock);
//������ ������ 
void GAME_OVER(SOCKET Sock);
void DrawScreen();
BOOL ProcessKey();
void PrintBrick(BOOL Show);
void PrintNextBrick(BOOL Show);
void PrintHoldBrick(BOOL Show);
void Setcolor(HANDLE hconsole, int brick);
int GetAround(int x, int y, int b, int r);
BOOL MoveDown();
void TestFull();

//���� -> �ο����� ��Ÿ�� 
void tetris(int headcount, SOCKET socket);
void Print_expect(BOOL Show);
int main_UI(); 
int choose_UI();
void multi_tetris_main();
int Room_UI();

void client_socket(int random);
int Room_password();
void multigame_wait();

struct Point {
    int x, y;
};
struct Point Shape[][4][4] = {
   { { 0,0,1,0,2,0,-1,0 },{ 0,0,0,1,0,-1,0,-2 },{ 0,0,1,0,2,0,-1,0 },{ 0,0,0,1,0,-1,0,-2 } },
   { { 0,0,1,0,0,1,1,1 },{ 0,0,1,0,0,1,1,1 },{ 0,0,1,0,0,1,1,1 },{ 0,0,1,0,0,1,1,1 } },
   { { 0,0,-1,0,0,-1,1,-1 },{ 0,0,0,1,-1,0,-1,-1 },{ 0,0,-1,0,0,-1,1,-1 },{ 0,0,0,1,-1,0,-1,-1 } },
   { { 0,0,-1,-1,0,-1,1,0 },{ 0,0,-1,0,-1,1,0,-1 },{ 0,0,-1,-1,0,-1,1,0 },{ 0,0,-1,0,-1,1,0,-1 } },
   { { 0,0,-1,0,1,0,-1,-1 },{ 0,0,0,-1,0,1,-1,1 },{ 0,0,-1,0,1,0,1,1 },{ 0,0,0,-1,0,1,1,-1 } },
   { { 0,0,1,0,-1,0,1,-1 },{ 0,0,0,1,0,-1,-1,-1 },{ 0,0,1,0,-1,0,-1,1 },{ 0,0,0,-1,0,1,1,1 } },
   { { 0,0,-1,0,1,0,0,1 },{ 0,0,0,-1,0,1,1,0 },{ 0,0,-1,0,1,0,0,-1 },{ 0,0,-1,0,0,-1,0,1 } },
};

typedef struct send_data {
    int send_board[BW + 2][BH + 2];
    int send_nextBrick;
    int send_One_chance;
    int send_REMOVE_BRICK;
    int send_REMOVE_ROT;
    int send_PREESED_HOLD;
    int send_speed;
    int send_nx;
    int send_ny;
    int send_brick;
    int send_rot;
    int send_game_over;
    int send_score;
} Send_data;

typedef struct recv_data {
    int recv_board[BW + 2][BH + 2];
    int recv_nextBrick;
    int recv_One_chance;
    int recv_REMOVE_BRICK;
    int recv_REMOVE_ROT;
    int recv_PREESED_HOLD;
    int recv_speed;
    int recv_nx;
    int recv_ny;
    int recv_brick;
    int recv_rot;
    int recv_game_over;
    int recv_score;
} Recv_data;

enum { EMPTY, BRICK, WALL, EXPECT };
char arTile[4][4] = { " ","��","��","��" };
int board[BW + 2][BH + 2];
int color_board[BW + 2][BH + 2];
int nx, ny;
int brick, rot;
int score = 0;
int n = 20;
int speed = 1;
int scoreRange = 50;
int nextBrick;
BOOL ONE_CHANCE = TRUE;
BOOL PREESED_HOLD = FALSE;
BOOL COUNT_SCORE = TRUE;
BOOL CHANGE_BRICK = TRUE;
//���� brick 
int REMOVE_BRICK;
//���� rot
int REMOVE_ROT;
//�ѹ��� ȭ�� ���� 
BOOL cleanScreen = FALSE;
//���� ���� ����
BOOL GAMEEND = FALSE;

//Main 
int main() {

    //���� ���ѹݺ�
    for (;;) {

        board[BW + 2][BH + 2];
        color_board[BW + 2][BH + 2];
        brick, rot;
        score = 0;
        n = 20;
        speed = 1;
        scoreRange = 50;
        nextBrick;
        ONE_CHANCE = TRUE;
        PREESED_HOLD = FALSE;
        COUNT_SCORE = TRUE;
        CHANGE_BRICK = TRUE;
        //���� brick 
        REMOVE_BRICK;
        //���� rot
        REMOVE_ROT;
        //�ѹ��� ȭ�� ���� 
        cleanScreen = FALSE;
        //���� ���� ����
        GAMEEND = FALSE;

        // mainUi
        int key = main_UI();
        // ȭ�� ���� ����
        clrscr();

        //Ui 
        int number = choose_UI();
        if (number == 49) {

            //���� -> �ο����� ��Ÿ�� 
            tetris(1, INVALID_SOCKET);
        }
        else if (number == 50) {
            multi_tetris_main();
        }
        else {
            //ȭ�� ���� ���� 
            clrscr();

        }
    }

}

// ����ȭ�� Ui
int main_UI() {
    // Ŀ�� ��ġ ����
    gotoxy(0, 8)
        // mainUi ����
        char mainUi[5][100] = {
            "\t\t\t\t   _                 _                  _     ",
            "\t\t\t\t  | |_      ___     | |_      _ __     (_)     ___ ",
            "\t\t\t\t  | __|    / _ \\    | __|    | '__|    | |    / __|",
            "\t\t\t\t  | |_    |  __/    | |_     | |       | |    \\__ \\",
            "\t\t\t\t   \\__|    \\___|     \\__|    |_|       |_|    |___/",
    };
    // mainUi ǥ��
    for (int i = 0; i < 5; i++) {
        printf("%s\n", mainUi[i]);
    }

    // Ŀ�� ��ġ ����
    gotoxy(40, 20)
        // !! ������Ʈ ǥ��
        printf("�ƹ� Ű�� ������ ������ ���۵˴ϴ�.");
    //Ŀ�� �����
    showcursor(FALSE);
    // Ű �Է� ���
    int key = _getch();
    // ���� Ű ��ȯ
    return key;
}

//���� UI 
int choose_UI() {
    gotoxy(0, 4)
        //���� ���� ����
        char Ui[9][100] = {
                "\t\t\t   _      ____     ___                                          ",
                "\t\t\t /' \\    /\\  _`\\  /\\_ \\                                         ",
                "\t\t\t/\\_, \\   \\ \\ \\L\\ \\\\//\\ \\       __      __  __       __    _ __  ",
                "\t\t\t\\/_/\\ \\   \\ \\ ,__/  \\ \\ \\    /'__`\\   /\\ \\/\\ \\    /'__`\\ /\\`'__\\",
                "\t\t\t   \\ \\ \\   \\ \\ \\/    \\_\\ \\_ /\\ \\L\\.\\_ \\ \\ \\_\\ \\  /\\  __/ \\ \\ \\/",
                "\t\t\t    \\ \\_\\   \\ \\_\\    /\\____\\\\ \\__/\\.\\_ \\/`____ \\ \\ \\____\\ \\ \\_\\ ",
                "\t\t\t     \\/_/    \\/_/    \\/____/ \\/__/\\/_/  `/___/> \\ \\/____/  \\/_/ ",
                "\t\t\t                                           /\\___/                ",
                "\t\t\t                                           \\/__/                 "
    };
    for (int a = 0; a < 9; a++) {
        printf("%s\n", Ui[a]);
    }

    //���� ���� ���� 
    char Ui_2[9][120] = {
       "\t\t\t   ___      ____     ___                                                  ",
       "\t\t\t /'___`\\   /\\  _`\\  /\\_ \\                                                 ",
       "\t\t\t/\\_\\ /\\ \\  \\ \\ \\L\\ \\\\//\\ \\       __      __  __       __    _ __    ____  ",
       "\t\t\t\\/_/// /__  \\ \\ ,__/  \\ \\ \\    /'__`\\   /\\ \\/\\ \\    /'__`\\ /\\`'__\\ /',__\\ ",
       "\t\t\t   // /_\\ \\  \\ \\ \\/    \\_\\ \\_ /\\ \\L\\.\\_ \\ \\ \\_\\ \\  /\\  __/ \\ \\ \\/ /\\__, `\\",
       "\t\t\t  /\\______/   \\ \\_\\    /\\____\\\\ \\__/\\.\\  \\/`____ \\ \\ \\____\\ \\ \\_\\  \\/\\____/",
       "\t\t\t  \\/_____/     \\/_/    \\/____/ \\/__/\\/_/  `/___/> \\ \\/____/  \\/_/  \\/___/ ",
       "\t\t\t                                             /\\___/                        ",
       "\t\t\t                                             \\/__/                         "
    };

    for (int a = 0; a < 9; a++) {
        printf("%s\n", Ui_2[a]);
    }

    putsxy(40, 25, "Ű���忡�� �ο����� �Է��� �ּ���.");

    // Ŀ�� �����
    showcursor(FALSE);
    // Ű �Է� ���
    int number = _getch();
    // �Էµ� Ű ��ȯ
    return number;
}

//��Ƽ
void multi_tetris_main() {

    //�� UI and �� ���� or ���� 
    int choose_number = Room_UI();

    if (choose_number == 1) {
        //ȭ�� ���� ���� 
        clrscr();

        //Ŭ���̾�Ʈ 
        client_socket(0);
    }
    else if (choose_number == 2) {
        //�н����� �Է�
        int password = Room_password();

        if (password == 0) {
            multi_tetris_main();
        }
        else {
            client_socket(password);
        }

        //socket
    }
    else {
        //ȭ�� ���� ���� 
        clrscr();
    }
}
//��Ƽ

//����
//����ó�� 
void Error(char* message);

void client_socket(int random) {

    //window socket api
    WSADATA wsadata;

    int result = WSAStartup(MAKEWORD(2, 2), &wsadata);

    //wsadata �ʱ�ȭ �� ��ȿ�� Ȯ�� 
    if (result != 0) {
        Error("window socket api error");
    }
    else {
        printf("wsa ������ �����Խ��ϴ�\n");
    }

    //���� ����
    SOCKET Sock = socket(PF_INET, SOCK_STREAM, 0);


    //���� ��ȿ�� �˻�
    if (Sock == INVALID_SOCKET) {
        Error("���� ����\n");
    }
    else {
        printf("���� ����\n");
    }

    //SOCKET + address +internet
    SOCKADDR_IN client_server;

    //�ʱ�ȭ
    memset(&client_server, 0, sizeof(client_server));

    //���� �Է� 
    client_server.sin_family = AF_INET;
    client_server.sin_addr.s_addr = inet_addr("15.165.140.192");
    client_server.sin_port = htons(4000);

    //connect ��ȿ�� Ȯ��
    if (connect(Sock, (SOCKADDR*)&client_server, sizeof(client_server)) == SOCKET_ERROR) {
        Error("connect error\n");
    }
    else {
        printf("������ �����մϴ�.\n");

        //���� ���� ���� 

        //ȭ�� ���� ���� 
        clrscr();

        //������
        if (random != 0) {
            char Result_client_connect[3];
            int recv_status = recv(Sock, Result_client_connect, sizeof(Result_client_connect), 0);



            //recv ��ȿ�� �˻� 
            if (recv_status == SOCKET_ERROR) {
                Error("recv �Լ� Error");
            }

            Result_client_connect[2] = '\0';

            if (strcmp(Result_client_connect, "OK") == 0) {
                tetris(2, Sock);
            }
            else {
                printf("%s", Result_client_connect);
            }

        }


        //�氳��
        else {
            //�� ��ȣ 
            char Room_Password[6];

            //recv ��ȿ�� �˻� 
            int Recv_Password_Result = recv(Sock, Room_Password, sizeof(Room_Password), 0);

            if (Recv_Password_Result == SOCKET_ERROR) {
                Error("recv �Լ� Error");
            }

            //��Ƽ���� ���� 
            multigame_wait(Room_Password, Sock);

        }
    }

}

//����ó�� 
void Error(char* message) {
    //ȭ�� ���� ���� 
    clrscr();

    printf("%s", message);

    putsxy(40, 25, "����Ϸ��� �ƹ� Ű�� �����ʽÿ� . . . ");

    _getch();


    multi_tetris_main();
}
//����

//��Ƽ���� ���� 
void multigame_wait( SOCKET Sock) {
    showcursor(FALSE);

    putsxy(45, 13, "������ ��ٸ��� �ֽ��ϴ�");

    //Ŭ���̾�Ʈ 2 ���� ���� 
    char Result_client2_connect[2];

    int recv_status = recv(Sock, Result_client2_connect, sizeof(Result_client2_connect), 0);

    //recv �Լ� ��ȿ�� 
    if (recv_status == SOCKET_ERROR) {
        Error("recv �Լ� Error");
    }

    //Ÿ�� �ƿ�
    if (atoi(Result_client2_connect) == 0) {
        Error("10�ʰ� �Ѿ� ���ư��ϴ�");
    }
    //���� ����  
    else {

        //2�� �÷��� 
        tetris(2, Sock);
    }
}
//��Ƽ���� ���� 

//�� UI
int Room_UI() {
    //ȭ�� ���� ���� 
    clrscr();

    putsxy(35, 10, "�� ����");
    putsxy(37, 11, "1��");

    putsxy(55, 10, "�� ����");
    putsxy(57, 11, "2��");

    putsxy(75, 10, "���ư���");
    putsxy(77, 11, "3��");

    putsxy(40, 20, "Ű���忡�� ��ȣ�� �Է��� �ּ���.");

    showcursor(FALSE);

    //�� ���� or ���� 
    int choose_number = getch();

    if (choose_number == 49) {
        return 1;
    }
    else if (choose_number == 50) {
        return 2;
    }
    else if (choose_number == 51) {
        return 3;
    }
    else {
        return Room_UI();
    }
}
//�� UI


//�н����� 
int Room_password() {
    clrscr();
    int password;

    putsxy(30, 10, "���ȣ�� �Է��� �ּ���");
    putsxy(80, 10, "���ư���");
    putsxy(80, 11, "0�Է�");

    //Ŀ�� ��ġ �ȱ��
    gotoxy(30, 18);

    printf(">>>>>>>");
    scanf_s("%d", &password);

    if (password == 0) {
        return 0;
    }
    else {
        //��ȣ ��ȿ�� �˻� 
        return password;
    }
}
//�н�����

void tetris(int headcount, SOCKET Sock) {
    int nFrame, nStay;
    int x, y;

    // ȭ�� Ŀ�� ����
    showcursor(FALSE);
    // ���� �߻��� ���� �ʱ�ȭ
    randomize();
    // ȭ�� ����
    clrscr();

    // �����ڸ��� ��, �������� �� �������� �ʱ�ȭ�Ѵ�.
    for (x = 0; x < BW + 2; x++) {
        for (y = 0; y < BH + 2; y++) {
            if (y == 0 || y == BH + 1 || x == 0 || x == BW + 1) {
                board[x][y] = WALL;
                color_board[x][y] = EMPTY;
            }
            else {
                board[x][y] = EMPTY;
                color_board[x][y] = EMPTY;
            }
        }
    }

    gotoxy(31, BY + 4);
    printf("+-  N E X T  -+ \n");
    gotoxy(31, BY + 5);
    printf("|             | ");
    gotoxy(31, BY + 6);
    printf("|             | ");
    gotoxy(31, BY + 7);
    printf("|             | ");
    gotoxy(31, BY + 8);
    printf("|             | ");
    gotoxy(31, BY + 9);
    printf("+-------------+ ");

    gotoxy(31, BY + 11);
    printf("+-  H O L D  -+ \n");
    gotoxy(31, BY + 12);
    printf("|             | ");
    gotoxy(31, BY + 13);
    printf("|             | ");
    gotoxy(31, BY + 14);
    printf("|             | ");
    gotoxy(31, BY + 15);
    printf("|             | ");
    gotoxy(31, BY + 16);
    printf("+-------------+ ");
    gotoxy(31, BY + 18);
    printf("  H(h):  hold");

    brick = random(sizeof(Shape) / sizeof(Shape[0]));

    if (headcount == 1) {

        DrawScreen();
        nFrame = 20;

        // ��ü ���� ����
        for (; 1;) {

            gotoxy(31, BY + 1);
            printf("score :     %d", score);

            // �ӵ� ���
            if (score >= scoreRange) {
                n += 10;           // delay�� �����ؼ� �ӵ� ���
                speed += 1;        // �ӵ� level 1 ���
                scoreRange += 50;  // �ӵ� ���� 50 ���
            }

            gotoxy(31, BY + 2);
            printf("speed :     %d", speed);

            nx = BW / 2;
            ny = 3;
            rot = 0;
            PrintBrick(TRUE);

            PrintNextBrick(FALSE);
            nextBrick = random(sizeof(Shape) / sizeof(Shape[0]));
            PrintNextBrick(TRUE);

            // ���� ��ġ�� �ٸ� ����� ������ ���� ����
            if (GetAround(nx, ny, brick, rot) != EMPTY) break;

            // ���� �ϳ��� �ٴڿ� ���� �������� ����
            nStay = nFrame;
            for (; 2;) {
                if (--nStay == 0) {
                    nStay = nFrame;
                    if (MoveDown()) break;
                }
                if (ProcessKey()) break;
                delay(1000 / n);
            }
            if (COUNT_SCORE == FALSE) {
                COUNT_SCORE = TRUE;
            }
            else {
                // ���� �ϳ��� �ٴڿ� ������ 1�� �߰�
                score += 1;
            }

            if (CHANGE_BRICK == TRUE) {
                brick = nextBrick;
            }
            else {
                brick = REMOVE_BRICK;
                rot = REMOVE_ROT;
                CHANGE_BRICK = TRUE;
            }
        }
        clrscr();

        gotoxy(0, 8)
            char gameover[6][226] = {
               "\t\t\t\t  __ _   __ _  _ __ ___    ___    ___  __   __  ___  _ __ ",
               "\t\t\t\t / _` | / _` || '_ ` _ \\  / _ \\  / _ \\ \\ \\ / / / _ \\| '__|",
               "\t\t\t\t| (_| || (_| || | | | | ||  __/ | (_) | \\ V / |  __/| |",
               "\t\t\t\t \\__, | \\__,_||_| |_| |_| \\___|  \\___/   \\_/   \\___||_|",
               "\t\t\t\t  __/ |",
               "\t\t\t\t |___/"
        };
        for (int a = 0; a < 6; a++) {
            printf("%s\n", gameover[a]);
        }
        gotoxy(40, 20)
            printf("�ƹ� Ű�� ������ ù ȭ������ ���ư��ϴ�.");

        _getch();
        clrscr();
        showcursor(TRUE);
    }

    //��Ƽ���� 
    else if (headcount == 2) {

        //���� �ؽ�Ʈ
        gotoxy(80, BY + 4);
        printf("+-  N E X T  -+ \n");
        gotoxy(80, BY + 5);
        printf("|             | ");
        gotoxy(80, BY + 6);
        printf("|             | ");
        gotoxy(80, BY + 7);
        printf("|             | ");
        gotoxy(80, BY + 8);
        printf("|             | ");
        gotoxy(80, BY + 9);
        printf("+-------------+ ");

        gotoxy(80, BY + 11);
        printf("+-  H O L D  -+ \n");
        gotoxy(80, BY + 12);
        printf("|             | ");
        gotoxy(80, BY + 13);
        printf("|             | ");
        gotoxy(80, BY + 14);
        printf("|             | ");
        gotoxy(80, BY + 15);
        printf("|             | ");
        gotoxy(80, BY + 16);
        printf("+-------------+ ");

        //Ÿ�� UI �׸��� �Լ� 
        DrawScreen();
        nFrame = 20;

        // ��ü ���� ����

        Send_data send_data;

        //���� ������ �ʱ�ȭ
        memset(&send_data, 0, sizeof(send_data));

        //���� ������ �ν��Ͻ� ����
        Recv_data recv_data;

        //���� ������ �ʱ�ȭ
        memset(&recv_data, 0, sizeof(recv_data));

        //nextBrick ��ȯ�� �����ϴ� stack 
        int stack_change_nextBrick = -1;

        //speed ��ȯ�� �����ϴ� stack
        int stack_change_speed = -1;

        //���� ��ȯ�� �����ϴ� stack
        int stack_change_score = -1;

        //brick rot nx ny ��ȯ�� �����ϴ� stack
        int stack_change_4_location[4] = { -1,-1,-1,-1 };

        //�迭 ��ȯ�� �����ϴ� stack 
        int stack_board[BW + 2][BH + 2];

        //Ȧ�� ����ߴ��� ����
        BOOL HOLD_USE = FALSE;

        //�迭 �ʱ�ȭ
        for (x = 0; x < BW + 2; x++) {
            for (y = 0; y < BH + 2; y++) {
                if (y == 0 || y == BH + 1 || x == 0 || x == BW + 1) {
                    stack_board[x][y] = WALL;
                }
                else {
                    stack_board[x][y] = EMPTY;
                }
            }
        }

        //�� ��� 
        for (int x = 0; x < BW + 2; x++) {
            for (int y = 0; y < BH + 2; y++) {
                putsxy(50 + BX + x * 2, BY + y, arTile[stack_board[x][y]]);
            }
        }

        for (; 1;) {
            //������ �������� ���� 
            if (GAMEEND == TRUE) {
                break;
            }

            gotoxy(31, BY);
            printf("<     ��    >");

            gotoxy(31, BY + 1);
            printf("score :     %d", score);

            if (score >= scoreRange) {
                n += 10;
                speed += 1;
                scoreRange += 50;
            }

            gotoxy(31, BY + 2);
            printf("speed :     %d", speed);

            nx = BW / 2;
            ny = 3;
            rot = 0;
            PrintBrick(TRUE);

            PrintNextBrick(FALSE);
            nextBrick = random(sizeof(Shape) / sizeof(Shape[0]));
            PrintNextBrick(TRUE);

            if (GetAround(nx, ny, brick, rot) != EMPTY) {

                //������ ���� �������� ���� ������ ���� ���¿��� score�� ���溸�� Ŭ�� �̱� �۰ų� ������ ��  
                if (recv_data.recv_game_over == 1 && score > recv_data.recv_score) {
                    Win_OR_Lose(TRUE, Sock);
                    break;
                }
                else if (recv_data.recv_game_over == 1 && score <= recv_data.recv_score) {
                    Win_OR_Lose(FALSE, Sock);
                    break;
                }

                //������ ������ ����͸� �Ҽ� ���� 
                GAME_OVER(Sock);
            };

            // ���� �ϳ��� �ٴڿ� ���� �������� ����
            nStay = nFrame;


            for (; 2;) {
                if (--nStay == 0) {
                    nStay = nFrame;
                    if (MoveDown()) break;
                }
                if (ProcessKey()) break;
                delay(1000 / n);


                for (int a = 0; a < BW + 2; a++) {
                    for (int b = 0; b < BH + 2; b++) {
                        send_data.send_board[a][b] = htonl(board[a][b]);
                    }
                }

                send_data.send_One_chance = htonl(ONE_CHANCE ? 1 : 0);
                send_data.send_PREESED_HOLD = htonl(PREESED_HOLD ? 1 : 0);
                send_data.send_REMOVE_BRICK = htonl(REMOVE_BRICK);
                send_data.send_REMOVE_ROT = htonl(REMOVE_ROT);
                send_data.send_speed = htonl(speed);
                send_data.send_brick = htonl(brick);
                send_data.send_nx = htonl(nx);
                send_data.send_ny = htonl(ny);
                send_data.send_rot = htonl(rot);

                send_data.send_nextBrick = htonl(nextBrick);
                send_data.send_game_over = htonl(0);
                send_data.send_score = htonl(score);

                int send_data_result = send(Sock, (char*)&send_data, sizeof(send_data), 0);
                int recv_data_result = recv(Sock, (char*)&recv_data, sizeof(recv_data), 0);

                for (int a = 0; a < BW + 2; a++) {
                    for (int b = 0; b < BH + 2; b++) {
                        recv_data.recv_board[a][b] = htonl(recv_data.recv_board[a][b]);
                    }
                }

                recv_data.recv_One_chance = htonl(recv_data.recv_One_chance);
                recv_data.recv_PREESED_HOLD = htonl(recv_data.recv_PREESED_HOLD);
                recv_data.recv_REMOVE_BRICK = htonl(recv_data.recv_REMOVE_BRICK);
                recv_data.recv_REMOVE_ROT = htonl(recv_data.recv_REMOVE_ROT);
                recv_data.recv_speed = htonl(recv_data.recv_speed);
                recv_data.recv_brick = htonl(recv_data.recv_brick);
                recv_data.recv_nx = htonl(recv_data.recv_nx);
                recv_data.recv_ny = htonl(recv_data.recv_ny);
                recv_data.recv_rot = htonl(recv_data.recv_rot);
                recv_data.recv_nextBrick = htonl(recv_data.recv_nextBrick);
                recv_data.recv_game_over = htonl(recv_data.recv_game_over);
                recv_data.recv_score = htonl(recv_data.recv_score);


                if (recv_data_result == SOCKET_ERROR) {
                    Error("recv �Լ� Error");
                }

                //���� next
                if (stack_change_nextBrick != recv_data.recv_nextBrick && stack_change_nextBrick != -1) {
                    for (int i = 0; i < 4; i++) {
                        gotoxy(87 + Shape[stack_change_nextBrick][0][i].x * 2, BY + 7 + Shape[stack_change_nextBrick][0][i].y);
                        puts(arTile[EMPTY]);
                    }
                    stack_change_nextBrick = recv_data.recv_nextBrick;
                }
                else {
                    for (int i = 0; i < 4; i++) {
                        gotoxy(87 + Shape[stack_change_nextBrick][0][i].x * 2, BY + 7 + Shape[stack_change_nextBrick][0][i].y);
                        puts(arTile[BRICK]);
                    }
                    stack_change_nextBrick = recv_data.recv_nextBrick;
                }


                //���� hold
                if (recv_data.recv_PREESED_HOLD == 1 && recv_data.recv_One_chance == 1) {
                    for (int i = 0; i < 4; i++) {
                        gotoxy(87 + Shape[recv_data.recv_REMOVE_BRICK][recv_data.recv_REMOVE_ROT][i].x * 2, BY + 14 + Shape[recv_data.recv_REMOVE_BRICK][recv_data.recv_REMOVE_ROT][i].y);
                        puts(arTile[BRICK]);
                    }
                }
                else if (recv_data.recv_One_chance == 0 && recv_data.recv_PREESED_HOLD == 1 && HOLD_USE == FALSE) {
                    for (int i = 0; i < 4; i++) {
                        gotoxy(87 + Shape[recv_data.recv_REMOVE_BRICK][recv_data.recv_REMOVE_ROT][i].x * 2, BY + 14 + Shape[recv_data.recv_REMOVE_BRICK][recv_data.recv_REMOVE_ROT][i].y);
                        puts(arTile[EMPTY]);
                    }

                    //Ȧ�� ��� ���� 
                    HOLD_USE = TRUE;
                }

                //���� ���� ���� 
                if (recv_data.recv_game_over == 0) {
                    gotoxy(80, BY);
                    printf("<     ����    >");

                    //���ð� recv.score�� ��ġ�ϴ��� �Ǵ�
                    if (stack_change_score != recv_data.recv_score) {
                        gotoxy(81, BY + 1);
                        printf("score :     %d", recv_data.recv_score);
                    }

                    //���ð� recv.speed�� ��ġ�ϴ��� �Ǵ�
                    if (stack_change_score != recv_data.recv_speed) {
                        gotoxy(81, BY + 2);
                        printf("speed :     %d", recv_data.recv_speed);
                    }


                    //���ð� �迭�� ��ġ�ϴ��� �Ǵ�
                    BOOL STACK_equal_BOARD = TRUE;
                    for (int a = 0; a < BW + 2; a++) {
                        for (int b = 0; b < BH + 2; b++) {
                            if (stack_board[a][b] != recv_data.recv_board[a][b]) {
                                STACK_equal_BOARD = FALSE;
                                stack_board[a][b] = recv_data.recv_board[a][b];
                            }
                        }
                    }

                    //������ �迭�� ��ġ���� ������ ��� 
                    if (STACK_equal_BOARD == FALSE) {
                        for (int x = 0; x < BW + 2; x++) {
                            for (int y = 0; y < BH + 2; y++) {
                                putsxy(50 + BX + x * 2, BY + y, arTile[stack_board[x][y]]);
                            }
                        }
                    }

                    //���� ��� ���� ���� 
                    //brick rot nx ny ��ȯ�� �����ϴ� stack 
                    for (int i = 0; i < 4; i++) {
                        gotoxy(50 + BX + (Shape[stack_change_4_location[0]][stack_change_4_location[1]][i].x + stack_change_4_location[2]) * 2, BY + Shape[stack_change_4_location[0]][stack_change_4_location[1]][i].y + stack_change_4_location[3]);
                        puts(arTile[EMPTY]);
                    }

                    //�ٲ� ������ ���� 
                    stack_change_4_location[0] = recv_data.recv_brick;

                    stack_change_4_location[1] = recv_data.recv_rot;

                    stack_change_4_location[2] = recv_data.recv_nx;

                    stack_change_4_location[3] = recv_data.recv_ny;

                    for (int i = 0; i < 4; i++) {
                        gotoxy(50 + BX + (Shape[stack_change_4_location[0]][stack_change_4_location[1]][i].x + stack_change_4_location[2]) * 2, BY + Shape[stack_change_4_location[0]][stack_change_4_location[1]][i].y + stack_change_4_location[3]);
                        puts(arTile[BRICK]);
                    }

                }

                //���� ������ ���� 
                else if (recv_data.recv_game_over == 1) {

                    //�ؽ�Ʈ ����� 
                    gotoxy(80, BY);
                    printf("                    ");
                    //board ����� 
                    if (cleanScreen == FALSE) {
                        for (int x = 0; x < BW + 2; x++) {
                            for (int y = 0; y < BH + 2; y++) {
                                putsxy(50 + BX + x * 2, BY + y, arTile[EMPTY]);
                            }
                        }
                        for (int x = 80; x < 100; x++) {
                            for (int y = BY; y < 20; y++) {
                                putsxy(x, y, arTile[EMPTY]);
                            }
                        }
                        cleanScreen = TRUE;
                    }

                    if (score > recv_data.recv_score) {
                        Win_OR_Lose(TRUE, Sock);
                        send_data.send_game_over = htonl(1);

                        send(Sock, (char*)&send_data, sizeof(send_data), 0);
                        break;
                    }
                    else {
                        gotoxy(50, 2);
                        printf("������ %d�� �̻��̸� �̱�ϴ�!", recv_data.recv_score);
                    }
                }


            }

            if (COUNT_SCORE == FALSE) {
                COUNT_SCORE = TRUE;
            }
            else {
                score += 1;
            }

            if (CHANGE_BRICK == TRUE) {
                brick = nextBrick;
            }
            else {
                brick = REMOVE_BRICK;
                rot = REMOVE_ROT;
                CHANGE_BRICK = TRUE;
            }

        }
    }


}

void DrawScreen()
{
    HANDLE hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
    for (int x = 0; x < BW + 2; x++) {
        for (int y = 0; y < BH + 2; y++) {
            //���� ä������ ���� ����� �����ϰ� 
            if (color_board[x][y] != 0) {
                //���� �ο� 
                SetConsoleTextAttribute(hconsole, color_board[x][y]);
                putsxy(BX + x * 2, BY + y, arTile[board[x][y]]);
                //�ʱ�ȭ 
                SetConsoleTextAttribute(hconsole, 15);
            }
            else {
                putsxy(BX + x * 2, BY + y, arTile[board[x][y]]);
            }
        }
    }
}

BOOL ProcessKey()
{
    if (kbhit()) {
        // getch �Լ��� ����ڰ� Ű�� ���� �� �ش� Ű�� ASCII ���� ��ȯ�ϴ� �Լ�
        int ch = getch();
        if (ch == 0xE0 || ch == 0) {
            ch = getch();
            switch (ch) {
            case LEFT:
                if (GetAround(nx - 1, ny, brick, rot) == EMPTY) {
                    PrintBrick(FALSE);
                    Print_expect(FALSE);
                    nx--;
                    Print_expect(TRUE);
                    PrintBrick(TRUE);

                }
                break;
            case RIGHT:
                if (GetAround(nx + 1, ny, brick, rot) == EMPTY) {
                    PrintBrick(FALSE);
                    Print_expect(FALSE);
                    nx++;
                    Print_expect(TRUE);
                    PrintBrick(TRUE);
                }
                break;
            case UP:
                if (GetAround(nx, ny, brick, (rot + 1) % 4) == EMPTY) {
                    PrintBrick(FALSE);
                    Print_expect(FALSE);
                    rot = (rot + 1) % 4;
                    Print_expect(TRUE);
                    PrintBrick(TRUE);
                }
                break;
            case DOWN:
                if (MoveDown()) {
                    return TRUE;
                }
                break;
            }
        }
        else if (ch == 'h' || ch == 'H') {
            if (PREESED_HOLD == FALSE) {

                Print_expect(FALSE);
                PrintBrick(FALSE);

                REMOVE_BRICK = brick;
                REMOVE_ROT = rot;

                PrintHoldBrick(TRUE);
                PREESED_HOLD = TRUE;
                COUNT_SCORE = FALSE;
                return TRUE;
            }
            //��ȸ�� ���ٸ� 
            else if (ONE_CHANCE == TRUE) {
                PrintBrick(FALSE);
                Print_expect(FALSE);
                PrintHoldBrick(FALSE);

                //��ȸ ���ֱ� 
                ONE_CHANCE = FALSE;
                COUNT_SCORE = FALSE;
                CHANGE_BRICK = FALSE;
                return TRUE;
            }
        }
        else {
            switch (ch) {
            case ' ':
                while (MoveDown() == FALSE) { ; }
                return TRUE;
            case ESC:
                exit(0);
            }
        }
    }
    return FALSE;
}

void PrintBrick(BOOL Show)
{
    //�ڵ� ����ü ����
    HANDLE hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
    Setcolor(hconsole, brick);
    for (int i = 0; i < 4; i++) {
        gotoxy(BX + (Shape[brick][rot][i].x + nx) * 2, BY + Shape[brick][rot][i].y + ny);
        puts(arTile[Show ? BRICK : EMPTY]);
    }
    //�Ͼ� -> 15 
    SetConsoleTextAttribute(hconsole, 15);
}

//���� ��� ������ �����ϵ��� 
void Print_expect(BOOL Show) {
    int Y = ny;
    while (GetAround(nx, Y + 1, brick, rot) == EMPTY) {
        Y++;
    }
    for (int i = 0; i < 4; i++) {
        gotoxy(BX + (Shape[brick][rot][i].x + nx) * 2, BY + Shape[brick][rot][i].y + Y);
        puts(arTile[Show ? EXPECT : EMPTY]);
    }
}


void PrintNextBrick(BOOL Show) {
    //�ڵ� ����ü ����
    HANDLE hconsole = GetStdHandle(STD_OUTPUT_HANDLE);

    Setcolor(hconsole, nextBrick);

    for (int i = 0; i < 4; i++) {
        gotoxy(38 + Shape[nextBrick][0][i].x * 2, BY + 7 + Shape[nextBrick][0][i].y);
        puts(arTile[Show ? BRICK : EMPTY]);
    }

    //�Ͼ� -> 15 
    SetConsoleTextAttribute(hconsole, 15);
}

//����
void GAME_OVER(SOCKET Sock) {

    Send_data send_data;
    memset(&send_data, 0, sizeof(send_data));

    //�����ʹ� ��� ����
    Recv_data recv_data;
    memset(&recv_data, 0, sizeof(recv_data));

    //�迭 ��ȯ�� �����ϴ� stack 
    int stack_board[BW + 2][BH + 2];
    //brick rot nx ny ��ȯ�� �����ϴ� stack
    int stack_change_4_location[4] = { -1,-1,-1,-1 };

    while (1) {

        send_data.send_game_over = htonl(1);
        send_data.send_score = htonl(score);

        send(Sock, (char*)&send_data, sizeof(send_data), 0);

        recv(Sock, (char*)&recv_data, sizeof(recv_data), 0);

        for (int a = 0; a < BW + 2; a++) {
            for (int b = 0; b < BH + 2; b++) {
                recv_data.recv_board[a][b] = htonl(recv_data.recv_board[a][b]);
            }
        }
        recv_data.recv_brick = htonl(recv_data.recv_brick);
        recv_data.recv_nx = htonl(recv_data.recv_nx);
        recv_data.recv_ny = htonl(recv_data.recv_ny);
        recv_data.recv_rot = htonl(recv_data.recv_rot);

        recv_data.recv_game_over = htonl(recv_data.recv_game_over);
        recv_data.recv_score = htonl(recv_data.recv_score);



        //���ð� �迭�� ��ġ�ϴ��� �Ǵ�
        BOOL STACK_equal_BOARD = TRUE;
        for (int a = 0; a < BW + 2; a++) {
            for (int b = 0; b < BH + 2; b++) {
                if (stack_board[a][b] != recv_data.recv_board[a][b]) {
                    STACK_equal_BOARD = FALSE;
                    stack_board[a][b] = recv_data.recv_board[a][b];
                }
            }
        }

        //������ �迭�� ��ġ���� ������ ��� 
        if (STACK_equal_BOARD == FALSE) {
            for (int x = 0; x < BW + 2; x++) {
                for (int y = 0; y < BH + 2; y++) {
                    putsxy(50 + BX + x * 2, BY + y, arTile[stack_board[x][y]]);
                }
            }
        }

        //���� ��� ���� ���� 
        //brick rot nx ny ��ȯ�� �����ϴ� stack 
        for (int i = 0; i < 4; i++) {
            gotoxy(50 + BX + (Shape[stack_change_4_location[0]][stack_change_4_location[1]][i].x + stack_change_4_location[2]) * 2, BY + Shape[stack_change_4_location[0]][stack_change_4_location[1]][i].y + stack_change_4_location[3]);
            puts(arTile[EMPTY]);
        }

        //�ٲ� ������ ���� 
        stack_change_4_location[0] = recv_data.recv_brick;

        stack_change_4_location[1] = recv_data.recv_rot;

        stack_change_4_location[2] = recv_data.recv_nx;

        stack_change_4_location[3] = recv_data.recv_ny;

        for (int i = 0; i < 4; i++) {
            gotoxy(50 + BX + (Shape[stack_change_4_location[0]][stack_change_4_location[1]][i].x + stack_change_4_location[2]) * 2, BY + Shape[stack_change_4_location[0]][stack_change_4_location[1]][i].y + stack_change_4_location[3]);
            puts(arTile[BRICK]);
        }

        if (score < (int)recv_data.recv_score) {
            Win_OR_Lose(FALSE, Sock);
            break;
        }


    }


}

//����
void Win_OR_Lose(BOOL WIN_OR_LOSE, SOCKET Sock) {
    clrscr();

    gotoxy(30, 5);
    printf(WIN_OR_LOSE ? "�¸�" : "�й�");

    _getch();
    clrscr();
    GAMEEND = TRUE;
}

//Ȧ�� ��� 
void PrintHoldBrick(BOOL Show)
{
    //�ڵ� ����ü ����
    HANDLE hconsole = GetStdHandle(STD_OUTPUT_HANDLE);

    Setcolor(hconsole, brick);
    for (int i = 0; i < 4; i++) {
        gotoxy(38 + Shape[REMOVE_BRICK][REMOVE_ROT][i].x * 2, BY + 14 + Shape[REMOVE_BRICK][REMOVE_ROT][i].y);
        puts(arTile[Show ? BRICK : EMPTY]);
    }

    //�Ͼ� -> 15 
    SetConsoleTextAttribute(hconsole, 15);
}

//���� ���� 
void Setcolor(HANDLE hconsole, int brick) {

    //���� �ο� 
    switch (brick) {
    case 1: // brick 1 -> �Ķ�
        SetConsoleTextAttribute(hconsole, 1);
        break;
    case 2: // brick 2 -> �ʷ�
        SetConsoleTextAttribute(hconsole, 2);
        break;
    case 3: // brick 3 -> �ϴ�
        SetConsoleTextAttribute(hconsole, 11);
        break;
    case 4: // brick 4 -> ���
        SetConsoleTextAttribute(hconsole, 14);
        break;
    case 5: // brick 5 -> ����
        SetConsoleTextAttribute(hconsole, 13);
        break;
    case 6: // brick 6 -> ȸ��
        SetConsoleTextAttribute(hconsole, 8);
        break;
    default: // brick 0 -> ������
        SetConsoleTextAttribute(hconsole, 4);
    }

}

int GetAround(int x, int y, int b, int r)
{
    int k = EMPTY;

    // ������ ������ Ÿ�� ��� �� ���� ū ���� ã�´�.
    for (int i = 0; i < 4; i++) {
        k = max(k, board[x + Shape[b][r][i].x][y + Shape[b][r][i].y]);
    }
    return k;
}

BOOL MoveDown() {
    // �ٴڿ� ������� ����á���� �����ϰ� TRUE�� �����Ѵ�.
    if (GetAround(nx, ny + 1, brick, rot) != EMPTY) {
        TestFull();
        return TRUE;
    }

    // ���� ���߿� �� ������ ��ĭ �Ʒ��� ������.
    Print_expect(FALSE);
    PrintBrick(FALSE);
    ny++;
    Print_expect(TRUE);
    PrintBrick(TRUE);

    return FALSE;
}

void TestFull()
{
    // �ٴڿ� �������� ���� ���
    for (int i = 0; i < 4; i++) {
        board[nx + Shape[brick][rot][i].x][ny + Shape[brick][rot][i].y] = BRICK;

        switch (brick) {
        case 1: // brick 1 -> �Ķ�
            color_board[nx + Shape[brick][rot][i].x][ny + Shape[brick][rot][i].y] = 1;
            break;
        case 2: // brick 2 -> �ʷ�
            color_board[nx + Shape[brick][rot][i].x][ny + Shape[brick][rot][i].y] = 2;
            break;
        case 3: // brick 3 -> �ϴ�
            color_board[nx + Shape[brick][rot][i].x][ny + Shape[brick][rot][i].y] = 11;
            break;
        case 4: // brick 4 -> ���
            color_board[nx + Shape[brick][rot][i].x][ny + Shape[brick][rot][i].y] = 14;
            break;
        case 5: // brick 5 -> ����
            color_board[nx + Shape[brick][rot][i].x][ny + Shape[brick][rot][i].y] = 13;
            break;
        case 6: // brick 6 -> ȸ��
            color_board[nx + Shape[brick][rot][i].x][ny + Shape[brick][rot][i].y] = 8;
            break;
        default: // brick 0 -> ������
            color_board[nx + Shape[brick][rot][i].x][ny + Shape[brick][rot][i].y] = 4;
        }

    }

    // �������� ������ ���� ����
    for (int y = 1; y < BH + 1; y++) {
        BOOL bFull = TRUE;
        for (int x = 1; x < BW + 1; x++) {
            if (board[x][y] == EMPTY) {
                bFull = FALSE;
                break;
            }
        }
        // ������ ���� á���� �� ���� �����Ѵ�.
        if (bFull) {
            for (int ty = y; ty > 1; ty--) {
                for (int x = 1; x < BW + 1; x++) {
                    board[x][ty] = board[x][ty - 1];

                    color_board[x][ty] = color_board[x][ty - 1];
                }
            }
            score += 10;
            DrawScreen();
            delay(200);
        }
    }
}
//��Ʈ���� �� 
