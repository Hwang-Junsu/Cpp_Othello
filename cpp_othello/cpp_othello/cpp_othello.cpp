#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#define SIZE 8
using namespace std;


struct Logic {
    int** dat;

    void input_pos();
    void create_board();
    void delete_board();
    void init_board();
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
    dat[3][4] = 2;
    dat[4][3] = 2;
    dat[3][3] = 1;
    dat[4][4] = 1;
}
void Logic::input_pos() {
    char x_pos;
    char y_pos;
    cin >> x_pos >> y_pos;
    x_pos -= '0';
    y_pos -= '0';
    dat[x_pos][y_pos] = 1;
}
bool Logic::game_over() {
    return true;
    
}

struct Render {
    int** dat;

    void setdata(int**);
    void board_print();
    void stone_print();
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

void Render::stone_print() {

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
    int cnt = 5;

    while (lg.game_over()) {
        rd.board_print();
        lg.input_pos();
    }
   
    lg.delete_board();
}
