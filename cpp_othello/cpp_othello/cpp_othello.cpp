#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#define SIZE 8
using namespace std;


struct Logic {
    int** dat;
    int player = 0;
    int dir = 0; // 1 = 우 2 = 좌 3 = 하 4 = 상
    int count = 0;

    void input_pos();
    void create_board();
    void delete_board();
    void init_board();
    void reverse_stone(int, int, int);
    bool put_stone(int, int);
    bool check(int, int);
    bool game_over();
};

void Logic::create_board() {
    dat = new int* [SIZE];
    dat[0] = new int[SIZE * SIZE];
    for (int i = 1; i < SIZE; i++) dat[i] = dat[i - 1] + SIZE;

    memset(dat[0], 0, sizeof(int) * SIZE* SIZE);
}
void Logic::delete_board() {
    delete[] dat[0];
    delete[] dat;
}
void Logic::init_board() {
    dat[3][4] = 1;
    dat[4][3] = 1;
    dat[3][3] = 2;
    dat[4][4] = 2;
}
void Logic::input_pos() {
    char x_pos;
    char y_pos;
    cin >> x_pos >> y_pos;
    x_pos -= '0';
    y_pos -= '0';
    if ((x_pos <= 7 && x_pos >= 0) && (y_pos >= 0 && y_pos <= 7)) {
        if (put_stone(x_pos, y_pos) == 1) {
        dat[x_pos][y_pos] = player + 1;
        reverse_stone(x_pos,y_pos,dir);
        player = 1 - player;
    }
    }
}

void Logic::reverse_stone(int x,int y,int dir) {
    int tmp = 0;
    if (dir == 1 && player == 0) { //백, 우
        while (dat[x][y] != 2) {
            dat[x][y+tmp] = 1;
            tmp++;
        }
    }
    else if (dir == 2 && player == 0) { //백, 좌
        while (dat[x][y] != 2) {
            dat[x][y - tmp] = 1;
            tmp++;
        }
    }
}

bool Logic::put_stone(int x,int y) {
    if (dat[x][y] > 0) return false;
    if (check(x, y)==1) return true;




    return false;
}

bool Logic::check(int x, int y) {
     //좌표가 들어왔을 때 1.상하 2. 좌우 3. 대각선으로 검사하여 반대돌이 있고 그 뒤에 자신의 돌이 있으면 true;
    //1. 좌우
    if (player == 0) {//백일때
        for (int i = y; i < SIZE - 1; i++) { // 오른쪽 검사
            if (dat[x][y + 1] == 2 && dat[x][i + 1] == 1) {
                dir = 1; return true;
            }
        }
        for (int i = y; i > 1; i--) { // 좌측 검사
            if (dat[x][y - 1] == 2 && dat[x][i - 1] == 1) {
                dir = 2; return true;
            }
        }
        for (int i = x; i < SIZE - 1; i++) { // 아래쪽 검사
            if (dat[x + 1][y] == 2 && dat[i + 1][y] == 1) {
                dir = 3; return true;
            }
        }
        for (int i = x; i > 1; i--) { // 위쪽 검사
            if (dat[x - 1][y] == 2 && dat[i - 1][y] == 1) {
                dir = 4; return true;
            }
        }
        //대각선검사..
        for (int i = y, j = 0; i < SIZE - 1; i++,j++) {
            if (dat[x + 1][y + 1] == 2 && dat[x+j][i + 1] == 1) return true;
        }
    }
    else if (player == 1) {//흑일때
        for (int i = y; i < SIZE - 1; i++) { // 오른쪽 검사
            if (dat[x][y + 1] == 1 && dat[x][i + 1] == 2) return true;
        }
        for (int i = y; i > 1; i--) { // 좌측 검사
            if (dat[x][y - 1] == 1 && dat[x][i - 1] == 2) return true;
        }
        for (int i = x; i < SIZE - 1; i++) { // 아래쪽 검사
            if (dat[x + 1][y] == 1 && dat[i + 1][y] == 2) return true;
        }
        for (int i = x; i > 1; i--) { // 위쪽 검사
            if (dat[x - 1][y] == 1 && dat[i - 1][y] == 2) return true;
        }
    }
    return false;


}

bool Logic::game_over() {
    return true;
}

struct Render {
    int** dat;

    void setdata(int**);
    void board_print();
    void topindex();
};


void Render::board_print() {
    system("cls");
    const char* pos[3];
    pos[0] = "  ";
    pos[1] = "●";
    pos[2] = "○";
    int x, y;
    topindex();
    cout << "┌─┬─┬─┬─┬─┬─┬─┬─┐" << endl;
    for (x = 0; x < SIZE; x++) {
        for (y = 0; y < SIZE; y++) {

            if (dat[x][y] == 0) {
                if (y == 0) cout << "│" << pos[0] << "│";
                else cout << pos[0] << "│";
            }

            else if (dat[x][y] == 1) {
                if (y == 0) cout << "│" << pos[1] << "│";
                else cout << pos[1] << "│";
            }

            else if (dat[x][y] == 2) {
                if (y == 0) cout << "│" << pos[2] << "│";
                else cout << pos[2] << "│";
            }
        }
        cout << x << endl;
        if (x == SIZE - 1) cout << "└─┴─┴─┴─┴─┴─┴─┴─┘" << endl;
        else cout << "├─┼─┼─┼─┼─┼─┼─┼─┤" << endl;
    }
}


void Render::topindex() {
    cout << "   0   1   2   3   4   5   6   7" << endl;
}

void Render::setdata(int** ptr) {
    dat = ptr;
}


int main()
{
    Logic lg;
    lg.create_board();
    Render rd;
    rd.setdata(lg.dat);
    lg.init_board();

    while (lg.game_over()) {
        rd.board_print();

        if (lg.player == 0) cout << "백 차례입니다." << endl;
        else cout << "흑 차례입니다." << endl;
        cout << "Input Position : ";
        lg.input_pos();
    }
   
    lg.delete_board();
}
