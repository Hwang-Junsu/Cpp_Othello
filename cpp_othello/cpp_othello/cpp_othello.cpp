#include <iostream>
#include <cstdlib>
#define SIZE 8
using namespace std;


struct Logic {
    int** dat;
    int player = 0;
    int count = 0;
    int dx[8] = { -1, 1, 0, 0, -1, 1, 1, -1 }; // 0.상  1.하  2.좌  3.우  4.우상  5.우하  6.좌하  7.좌상
    int dy[8] = { 0, 0, -1, 1, 1, 1, -1 ,-1 };

    void input_pos();
    void create_board();
    void delete_board();
    void init_board();
    void reverse_stone(int, int);
    bool put_stone(int, int);
    bool check(int, int);
    bool game_over();
};

void Logic::create_board() {
    dat = new int* [SIZE];
    dat[0] = new int[SIZE * SIZE];
    for (int i = 1; i < SIZE; i++) dat[i] = dat[i - 1] + SIZE;

    memset(dat[0], 0, sizeof(int) * SIZE * SIZE);
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
            player = 1 - player;
            count = 0;
        }
    }
}

void Logic::reverse_stone(int x, int y) {
        if (dat[x][y] == 1) dat[x][y] = 2;
        else if (dat[x][y] == 2) dat[x][y] = 1;

        count++;
}

bool Logic::put_stone(int x, int y) {
    if (dat[x][y] > 0) return false;
    if (check(x, y) == 1) return true;
    return false;
}

bool Logic::check(int x, int y) {
    int nx = 0, ny = 0;
    int check = 0; // 다음돌이 다른색인가 ?
    if (player == 0) {
        for (int i = 0; i < 8; i++) { //i는 dir변수 조작
            for (int j = 1; j < 7; j++) { // j는 좌표 조작
                nx = x + (dx[i] * j); ny = y + (dy[i] * j);
                if (nx < 0 || nx >= SIZE || ny < 0 || nx >= SIZE) break;

                if (j == 1 && dat[nx][ny] == 2) check = 1; //다음돌은 다른색인가?
                if (check == 1 && dat[nx][ny] == 0) break;
                if (check == 1 && dat[nx][ny] == 1) {
                    while (dat[x + dx[i]][y + dy[i]] != 1) {
                        nx -= dx[i]; ny -= dy[i];
                        reverse_stone(nx, ny);
                    }
                }
            }
        }
        if (count > 0) return true;
    }
    else if (player == 1) {
        for (int i = 0; i < 8; i++) { //i는 dir변수 조작
            for (int j = 1; j < 7; j++) { // j는 좌표 조작
                nx = x + (dx[i] * j); ny = y + (dy[i] * j);
                if (nx < 0 || nx >= SIZE || ny < 0 || nx >= SIZE) break;

                if (j == 1 && dat[nx][ny] == 1) check = 1;
                if (check == 1 && dat[nx][ny] == 0) break;
                if (check == 1 && dat[nx][ny] == 2) {
                    while (dat[x + dx[i]][y + dy[i]] != 2) {
                        nx -= dx[i]; ny -= dy[i];
                        reverse_stone(nx, ny);
                    }
                }
            }
        }
        if (count > 0) return true;
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