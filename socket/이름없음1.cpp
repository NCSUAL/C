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
//게임이 끝날때 
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

//인자 -> 인원수를 나타냄 
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
char arTile[4][4] = { " ","■","▩","□" };
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
//지운 brick 
int REMOVE_BRICK;
//지운 rot
int REMOVE_ROT;
//한번만 화면 지움 
BOOL cleanScreen = FALSE;
//게임 끝남 여부
BOOL GAMEEND = FALSE;

//Main 
int main() {

    //게임 무한반복
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
        //지운 brick 
        REMOVE_BRICK;
        //지운 rot
        REMOVE_ROT;
        //한번만 화면 지움 
        cleanScreen = FALSE;
        //게임 끝남 여부
        GAMEEND = FALSE;

        // mainUi
        int key = main_UI();
        // 화면 전부 지움
        clrscr();

        //Ui 
        int number = choose_UI();
        if (number == 49) {

            //인자 -> 인원수를 나타냄 
            tetris(1, INVALID_SOCKET);
        }
        else if (number == 50) {
            multi_tetris_main();
        }
        else {
            //화면 전부 지움 
            clrscr();

        }
    }

}

// 메인화면 Ui
int main_UI() {
    // 커서 위치 설정
    gotoxy(0, 8)
        // mainUi 정의
        char mainUi[5][100] = {
            "\t\t\t\t   _                 _                  _     ",
            "\t\t\t\t  | |_      ___     | |_      _ __     (_)     ___ ",
            "\t\t\t\t  | __|    / _ \\    | __|    | '__|    | |    / __|",
            "\t\t\t\t  | |_    |  __/    | |_     | |       | |    \\__ \\",
            "\t\t\t\t   \\__|    \\___|     \\__|    |_|       |_|    |___/",
    };
    // mainUi 표시
    for (int i = 0; i < 5; i++) {
        printf("%s\n", mainUi[i]);
    }

    // 커서 위치 설정
    gotoxy(40, 20)
        // !! 프롬포트 표시
        printf("아무 키나 누르면 게임이 시작됩니다.");
    //커서 숨기기
    showcursor(FALSE);
    // 키 입력 대기
    int key = _getch();
    // 눌린 키 반환
    return key;
}

//선택 UI 
int choose_UI() {
    gotoxy(0, 4)
        //글자 깨짐 방지
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

    //글자 깨짐 방지 
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

    putsxy(40, 25, "키보드에서 인원수를 입력해 주세요.");

    // 커서 숨기기
    showcursor(FALSE);
    // 키 입력 대기
    int number = _getch();
    // 입력된 키 반환
    return number;
}

//멀티
void multi_tetris_main() {

    //방 UI and 방 개설 or 입장 
    int choose_number = Room_UI();

    if (choose_number == 1) {
        //화면 전부 지움 
        clrscr();

        //클라이언트 
        client_socket(0);
    }
    else if (choose_number == 2) {
        //패스워드 입력
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
        //화면 전부 지움 
        clrscr();
    }
}
//멀티

//소켓
//에러처리 
void Error(char* message);

void client_socket(int random) {

    //window socket api
    WSADATA wsadata;

    int result = WSAStartup(MAKEWORD(2, 2), &wsadata);

    //wsadata 초기화 및 유효성 확인 
    if (result != 0) {
        Error("window socket api error");
    }
    else {
        printf("wsa 파일을 가져왔습니다\n");
    }

    //소켓 생성
    SOCKET Sock = socket(PF_INET, SOCK_STREAM, 0);


    //소켓 유효성 검사
    if (Sock == INVALID_SOCKET) {
        Error("소켓 에러\n");
    }
    else {
        printf("소켓 생성\n");
    }

    //SOCKET + address +internet
    SOCKADDR_IN client_server;

    //초기화
    memset(&client_server, 0, sizeof(client_server));

    //정보 입력 
    client_server.sin_family = AF_INET;
    client_server.sin_addr.s_addr = inet_addr("15.165.140.192");
    client_server.sin_port = htons(4000);

    //connect 유효성 확인
    if (connect(Sock, (SOCKADDR*)&client_server, sizeof(client_server)) == SOCKET_ERROR) {
        Error("connect error\n");
    }
    else {
        printf("서버에 접속합니다.\n");

        //서버 접속 성공 

        //화면 전부 지움 
        clrscr();

        //방입장
        if (random != 0) {
            char Result_client_connect[3];
            int recv_status = recv(Sock, Result_client_connect, sizeof(Result_client_connect), 0);



            //recv 유효성 검사 
            if (recv_status == SOCKET_ERROR) {
                Error("recv 함수 Error");
            }

            Result_client_connect[2] = '\0';

            if (strcmp(Result_client_connect, "OK") == 0) {
                tetris(2, Sock);
            }
            else {
                printf("%s", Result_client_connect);
            }

        }


        //방개설
        else {
            //방 번호 
            char Room_Password[6];

            //recv 유효성 검사 
            int Recv_Password_Result = recv(Sock, Room_Password, sizeof(Room_Password), 0);

            if (Recv_Password_Result == SOCKET_ERROR) {
                Error("recv 함수 Error");
            }

            //멀티게임 대기실 
            multigame_wait(Room_Password, Sock);

        }
    }

}

//에러처리 
void Error(char* message) {
    //화면 전부 지움 
    clrscr();

    printf("%s", message);

    putsxy(40, 25, "계속하려면 아무 키나 누르십시오 . . . ");

    _getch();


    multi_tetris_main();
}
//소켓

//멀티게임 대기실 
void multigame_wait( SOCKET Sock) {
    showcursor(FALSE);

    putsxy(45, 13, "상대방을 기다리고 있습니다");

    //클라이언트 2 접속 여부 
    char Result_client2_connect[2];

    int recv_status = recv(Sock, Result_client2_connect, sizeof(Result_client2_connect), 0);

    //recv 함수 유효성 
    if (recv_status == SOCKET_ERROR) {
        Error("recv 함수 Error");
    }

    //타임 아웃
    if (atoi(Result_client2_connect) == 0) {
        Error("10초가 넘어 돌아갑니다");
    }
    //접속 성공  
    else {

        //2인 플레이 
        tetris(2, Sock);
    }
}
//멀티게임 대기실 

//방 UI
int Room_UI() {
    //화면 전부 지움 
    clrscr();

    putsxy(35, 10, "방 개설");
    putsxy(37, 11, "1번");

    putsxy(55, 10, "방 입장");
    putsxy(57, 11, "2번");

    putsxy(75, 10, "돌아가기");
    putsxy(77, 11, "3번");

    putsxy(40, 20, "키보드에서 번호를 입력해 주세요.");

    showcursor(FALSE);

    //방 개설 or 입장 
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
//방 UI


//패스워드 
int Room_password() {
    clrscr();
    int password;

    putsxy(30, 10, "방번호를 입력해 주세요");
    putsxy(80, 10, "돌아가기");
    putsxy(80, 11, "0입력");

    //커서 위치 옴기기
    gotoxy(30, 18);

    printf(">>>>>>>");
    scanf_s("%d", &password);

    if (password == 0) {
        return 0;
    }
    else {
        //암호 유효성 검사 
        return password;
    }
}
//패스워드

void tetris(int headcount, SOCKET Sock) {
    int nFrame, nStay;
    int x, y;

    // 화면 커서 숨김
    showcursor(FALSE);
    // 난수 발생을 위한 초기화
    randomize();
    // 화면 지움
    clrscr();

    // 가장자리는 벽, 나머지는 빈 공간으로 초기화한다.
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

        // 전체 게임 루프
        for (; 1;) {

            gotoxy(31, BY + 1);
            printf("score :     %d", score);

            // 속도 상승
            if (score >= scoreRange) {
                n += 10;           // delay값 변경해서 속도 상승
                speed += 1;        // 속도 level 1 상승
                scoreRange += 50;  // 속도 범위 50 상승
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

            // 시작 위치에 다른 블록이 있으면 게임 종료
            if (GetAround(nx, ny, brick, rot) != EMPTY) break;

            // 벽돌 하나가 바닥에 닿을 때까지의 루프
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
                // 벽돌 하나가 바닥에 닿으면 1점 추가
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
            printf("아무 키나 누르면 첫 화면으로 돌아갑니다.");

        _getch();
        clrscr();
        showcursor(TRUE);
    }

    //멀티게임 
    else if (headcount == 2) {

        //상대방 넥스트
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

        //타일 UI 그리는 함수 
        DrawScreen();
        nFrame = 20;

        // 전체 게임 루프

        Send_data send_data;

        //보낼 데이터 초기화
        memset(&send_data, 0, sizeof(send_data));

        //받을 데이터 인스턴스 생성
        Recv_data recv_data;

        //받을 데이터 초기화
        memset(&recv_data, 0, sizeof(recv_data));

        //nextBrick 변환을 감지하는 stack 
        int stack_change_nextBrick = -1;

        //speed 변환을 감지하는 stack
        int stack_change_speed = -1;

        //점수 변환을 감지하는 stack
        int stack_change_score = -1;

        //brick rot nx ny 변환을 감지하는 stack
        int stack_change_4_location[4] = { -1,-1,-1,-1 };

        //배열 변환을 감지하는 stack 
        int stack_board[BW + 2][BH + 2];

        //홀드 사용했는지 여부
        BOOL HOLD_USE = FALSE;

        //배열 초기화
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

        //판 출력 
        for (int x = 0; x < BW + 2; x++) {
            for (int y = 0; y < BH + 2; y++) {
                putsxy(50 + BX + x * 2, BY + y, arTile[stack_board[x][y]]);
            }
        }

        for (; 1;) {
            //게임이 끝났는지 여부 
            if (GAMEEND == TRUE) {
                break;
            }

            gotoxy(31, BY);
            printf("<     나    >");

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

                //상대방이 먼저 끝난다음 나의 게임이 끝난 상태에서 score가 상대방보다 클시 이김 작거나 같으면 짐  
                if (recv_data.recv_game_over == 1 && score > recv_data.recv_score) {
                    Win_OR_Lose(TRUE, Sock);
                    break;
                }
                else if (recv_data.recv_game_over == 1 && score <= recv_data.recv_score) {
                    Win_OR_Lose(FALSE, Sock);
                    break;
                }

                //상대방의 게임을 모니터링 할수 있음 
                GAME_OVER(Sock);
            };

            // 벽돌 하나가 바닥에 닿을 때까지의 루프
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
                    Error("recv 함수 Error");
                }

                //상대방 next
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


                //상대방 hold
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

                    //홀드 사용 여부 
                    HOLD_USE = TRUE;
                }

                //상대방 게임 중임 
                if (recv_data.recv_game_over == 0) {
                    gotoxy(80, BY);
                    printf("<     상대방    >");

                    //스택과 recv.score가 일치하는지 판단
                    if (stack_change_score != recv_data.recv_score) {
                        gotoxy(81, BY + 1);
                        printf("score :     %d", recv_data.recv_score);
                    }

                    //스택과 recv.speed가 일치하는지 판단
                    if (stack_change_score != recv_data.recv_speed) {
                        gotoxy(81, BY + 2);
                        printf("speed :     %d", recv_data.recv_speed);
                    }


                    //스택과 배열이 일치하는지 판단
                    BOOL STACK_equal_BOARD = TRUE;
                    for (int a = 0; a < BW + 2; a++) {
                        for (int b = 0; b < BH + 2; b++) {
                            if (stack_board[a][b] != recv_data.recv_board[a][b]) {
                                STACK_equal_BOARD = FALSE;
                                stack_board[a][b] = recv_data.recv_board[a][b];
                            }
                        }
                    }

                    //스택이 배열과 일치하지 않으면 출력 
                    if (STACK_equal_BOARD == FALSE) {
                        for (int x = 0; x < BW + 2; x++) {
                            for (int y = 0; y < BH + 2; y++) {
                                putsxy(50 + BX + x * 2, BY + y, arTile[stack_board[x][y]]);
                            }
                        }
                    }

                    //현재 블록 상태 갱신 
                    //brick rot nx ny 변환을 감지하는 stack 
                    for (int i = 0; i < 4; i++) {
                        gotoxy(50 + BX + (Shape[stack_change_4_location[0]][stack_change_4_location[1]][i].x + stack_change_4_location[2]) * 2, BY + Shape[stack_change_4_location[0]][stack_change_4_location[1]][i].y + stack_change_4_location[3]);
                        puts(arTile[EMPTY]);
                    }

                    //바뀐 데이터 적용 
                    stack_change_4_location[0] = recv_data.recv_brick;

                    stack_change_4_location[1] = recv_data.recv_rot;

                    stack_change_4_location[2] = recv_data.recv_nx;

                    stack_change_4_location[3] = recv_data.recv_ny;

                    for (int i = 0; i < 4; i++) {
                        gotoxy(50 + BX + (Shape[stack_change_4_location[0]][stack_change_4_location[1]][i].x + stack_change_4_location[2]) * 2, BY + Shape[stack_change_4_location[0]][stack_change_4_location[1]][i].y + stack_change_4_location[3]);
                        puts(arTile[BRICK]);
                    }

                }

                //상대방 게임이 끝남 
                else if (recv_data.recv_game_over == 1) {

                    //텍스트 지우기 
                    gotoxy(80, BY);
                    printf("                    ");
                    //board 지우기 
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
                        printf("점수가 %d점 이상이면 이깁니다!", recv_data.recv_score);
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
            //벽과 채워지지 않은 블록을 제외하고 
            if (color_board[x][y] != 0) {
                //색깔 부여 
                SetConsoleTextAttribute(hconsole, color_board[x][y]);
                putsxy(BX + x * 2, BY + y, arTile[board[x][y]]);
                //초기화 
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
        // getch 함수는 사용자가 키를 누를 때 해당 키의 ASCII 값을 반환하는 함수
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
            //기회를 썻다면 
            else if (ONE_CHANCE == TRUE) {
                PrintBrick(FALSE);
                Print_expect(FALSE);
                PrintHoldBrick(FALSE);

                //기회 없애기 
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
    //핸들 구조체 정의
    HANDLE hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
    Setcolor(hconsole, brick);
    for (int i = 0; i < 4; i++) {
        gotoxy(BX + (Shape[brick][rot][i].x + nx) * 2, BY + Shape[brick][rot][i].y + ny);
        puts(arTile[Show ? BRICK : EMPTY]);
    }
    //하양 -> 15 
    SetConsoleTextAttribute(hconsole, 15);
}

//블럭이 어디 놓을지 예상하도록 
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
    //핸들 구조체 정의
    HANDLE hconsole = GetStdHandle(STD_OUTPUT_HANDLE);

    Setcolor(hconsole, nextBrick);

    for (int i = 0; i < 4; i++) {
        gotoxy(38 + Shape[nextBrick][0][i].x * 2, BY + 7 + Shape[nextBrick][0][i].y);
        puts(arTile[Show ? BRICK : EMPTY]);
    }

    //하양 -> 15 
    SetConsoleTextAttribute(hconsole, 15);
}

//승패
void GAME_OVER(SOCKET Sock) {

    Send_data send_data;
    memset(&send_data, 0, sizeof(send_data));

    //데이터는 계속 받음
    Recv_data recv_data;
    memset(&recv_data, 0, sizeof(recv_data));

    //배열 변환을 감지하는 stack 
    int stack_board[BW + 2][BH + 2];
    //brick rot nx ny 변환을 감지하는 stack
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



        //스택과 배열이 일치하는지 판단
        BOOL STACK_equal_BOARD = TRUE;
        for (int a = 0; a < BW + 2; a++) {
            for (int b = 0; b < BH + 2; b++) {
                if (stack_board[a][b] != recv_data.recv_board[a][b]) {
                    STACK_equal_BOARD = FALSE;
                    stack_board[a][b] = recv_data.recv_board[a][b];
                }
            }
        }

        //스택이 배열과 일치하지 않으면 출력 
        if (STACK_equal_BOARD == FALSE) {
            for (int x = 0; x < BW + 2; x++) {
                for (int y = 0; y < BH + 2; y++) {
                    putsxy(50 + BX + x * 2, BY + y, arTile[stack_board[x][y]]);
                }
            }
        }

        //현재 블록 상태 갱신 
        //brick rot nx ny 변환을 감지하는 stack 
        for (int i = 0; i < 4; i++) {
            gotoxy(50 + BX + (Shape[stack_change_4_location[0]][stack_change_4_location[1]][i].x + stack_change_4_location[2]) * 2, BY + Shape[stack_change_4_location[0]][stack_change_4_location[1]][i].y + stack_change_4_location[3]);
            puts(arTile[EMPTY]);
        }

        //바뀐 데이터 적용 
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

//승패
void Win_OR_Lose(BOOL WIN_OR_LOSE, SOCKET Sock) {
    clrscr();

    gotoxy(30, 5);
    printf(WIN_OR_LOSE ? "승리" : "패배");

    _getch();
    clrscr();
    GAMEEND = TRUE;
}

//홀드 출력 
void PrintHoldBrick(BOOL Show)
{
    //핸들 구조체 정의
    HANDLE hconsole = GetStdHandle(STD_OUTPUT_HANDLE);

    Setcolor(hconsole, brick);
    for (int i = 0; i < 4; i++) {
        gotoxy(38 + Shape[REMOVE_BRICK][REMOVE_ROT][i].x * 2, BY + 14 + Shape[REMOVE_BRICK][REMOVE_ROT][i].y);
        puts(arTile[Show ? BRICK : EMPTY]);
    }

    //하양 -> 15 
    SetConsoleTextAttribute(hconsole, 15);
}

//색상 변경 
void Setcolor(HANDLE hconsole, int brick) {

    //색상 부여 
    switch (brick) {
    case 1: // brick 1 -> 파랑
        SetConsoleTextAttribute(hconsole, 1);
        break;
    case 2: // brick 2 -> 초록
        SetConsoleTextAttribute(hconsole, 2);
        break;
    case 3: // brick 3 -> 하늘
        SetConsoleTextAttribute(hconsole, 11);
        break;
    case 4: // brick 4 -> 노란
        SetConsoleTextAttribute(hconsole, 14);
        break;
    case 5: // brick 5 -> 보라
        SetConsoleTextAttribute(hconsole, 13);
        break;
    case 6: // brick 6 -> 회색
        SetConsoleTextAttribute(hconsole, 8);
        break;
    default: // brick 0 -> 빨간색
        SetConsoleTextAttribute(hconsole, 4);
    }

}

int GetAround(int x, int y, int b, int r)
{
    int k = EMPTY;

    // 벽돌이 차지한 타일 모양 중 가장 큰 값을 찾는다.
    for (int i = 0; i < 4; i++) {
        k = max(k, board[x + Shape[b][r][i].x][y + Shape[b][r][i].y]);
    }
    return k;
}

BOOL MoveDown() {
    // 바닥에 닿았으면 가득찼는지 점검하고 TRUE를 리턴한다.
    if (GetAround(nx, ny + 1, brick, rot) != EMPTY) {
        TestFull();
        return TRUE;
    }

    // 아직 공중에 떠 있으면 한칸 아래로 내린다.
    Print_expect(FALSE);
    PrintBrick(FALSE);
    ny++;
    Print_expect(TRUE);
    PrintBrick(TRUE);

    return FALSE;
}

void TestFull()
{
    // 바닥에 내려앉은 벽돌 기록
    for (int i = 0; i < 4; i++) {
        board[nx + Shape[brick][rot][i].x][ny + Shape[brick][rot][i].y] = BRICK;

        switch (brick) {
        case 1: // brick 1 -> 파랑
            color_board[nx + Shape[brick][rot][i].x][ny + Shape[brick][rot][i].y] = 1;
            break;
        case 2: // brick 2 -> 초록
            color_board[nx + Shape[brick][rot][i].x][ny + Shape[brick][rot][i].y] = 2;
            break;
        case 3: // brick 3 -> 하늘
            color_board[nx + Shape[brick][rot][i].x][ny + Shape[brick][rot][i].y] = 11;
            break;
        case 4: // brick 4 -> 노란
            color_board[nx + Shape[brick][rot][i].x][ny + Shape[brick][rot][i].y] = 14;
            break;
        case 5: // brick 5 -> 보라
            color_board[nx + Shape[brick][rot][i].x][ny + Shape[brick][rot][i].y] = 13;
            break;
        case 6: // brick 6 -> 회색
            color_board[nx + Shape[brick][rot][i].x][ny + Shape[brick][rot][i].y] = 8;
            break;
        default: // brick 0 -> 빨간색
            color_board[nx + Shape[brick][rot][i].x][ny + Shape[brick][rot][i].y] = 4;
        }

    }

    // 수평으로 가득찬 벽돌 제거
    for (int y = 1; y < BH + 1; y++) {
        BOOL bFull = TRUE;
        for (int x = 1; x < BW + 1; x++) {
            if (board[x][y] == EMPTY) {
                bFull = FALSE;
                break;
            }
        }
        // 한줄이 가득 찼으면 이 줄을 제거한다.
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
//테트리스 끝 
