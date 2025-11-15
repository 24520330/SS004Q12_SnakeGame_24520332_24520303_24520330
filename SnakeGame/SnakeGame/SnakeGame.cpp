
#include <iostream>
#include <vector>
#include <conio.h>
#include <windows.h>
#include <ctime>

using namespace std;

const int WIDTH = 50; //chiều rộng khu vực chơi
const int HEIGHT = 20; //Chiều dài khu vực chơi

//Các biến toàn cục
bool gameOver;
int headX, headY, fruitX, fruitY, score;
int tailX[100], tailY[100];
int tailLength;
//Các hướng di chuyển
enum Direction { STOP, LEFT, RIGHT, UP, DOWN };
Direction dir;

//Thiết lập trạng thái ban đầu của game
void Setup() {
    gameOver = false;
    dir = STOP;
    headX = WIDTH / 2;
    headY = HEIGHT / 2;
    //Đảm bảo thức ăn xuất hiện trong khu vực chơi và không trùng với vị trí đầu rắn thời điểm ban đầu
    do {
        fruitX = rand() % WIDTH;
        fruitY = rand() % HEIGHT;
    } while (fruitX == headX && fruitY == headY);
    
    score = 0;
    tailLength = 0;
}

void Draw() {
    //Di chuyển con trỏ tới góc trên trái để vẽ lại
    COORD coord;
    coord.X = 0;
    coord.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

    //Vẽ tường TRÊN khu vực chơi, sử dụng kí tự "#"

    //Vẽ tường PHẢI khu vực chơi, sử dụng kí tự "#"

    //Vẽ tường TRÁI khu vực chơi, sử dụng kí tự "#"

    //Vẽ tường DƯỚI khu vực chơi, sử dụng kí tự "#"

    //Vẽ đầu rắn

    //Vẽ thức ăn

    //Vẽ đuôi rắn và khoảng trống 
    //Khoảng trống để ghi đè lên vị trí cũ đoạn đuôi cuối cùng đã đi qua, tránh để lại vệt dài trên màn hình
}

void Input() {
    //Up(W), Down(S), Left(A), Right(D), Quit(X) 

    //"W" để di chuyển lên (nếu đang di chuyển xuống thì không thể thực hiện)
    
    //"A" để di chuyển trái (nếu đang di chuyển phải thì không thể thực hiện)
    
    //"D" để di chuyển phải (nếu đang di chuyển trái thì không thể thực hiện)
    
    //"S" để di chuyển xuống (nếu đang di chuyển lên thì không thể thực hiện)
    
    //"X" để thoát chương trình 
}

void Logic() {
    // Di chuyển đuôi
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = headX;
    tailY[0] = headY;

    for (int i = 1; i < tailLength; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    // Di chuyển đầu
    switch (dir) {
    case LEFT: headX--; break;
    case RIGHT: headX++; break;
    case UP: headY--; break;
    case DOWN: headY++; break;
    default: break;
    }

    // Xuyên tường
    if (headX >= WIDTH) headX = 0;
    else if (headX < 0) headX = WIDTH - 1;

    if (headY >= HEIGHT) headY = 0;
    else if (headY < 0) headY = HEIGHT - 1;

    // Va chạm thân
    for (int i = 0; i < tailLength; i++) {
        if (tailX[i] == headX && tailY[i] == headY) {
            gameOver = true;
        }
    }

    // Ăn thức ăn
    if (headX == fruitX && headY == fruitY) {
        score++;
        tailLength++;

        // Tạo thức ăn mới không trùng đuôi
        bool valid;
        do {
            valid = true;
            fruitX = rand() % WIDTH;
            fruitY = rand() % HEIGHT;

            if (fruitX == headX && fruitY == headY) valid = false;

            for (int i = 0; i < tailLength; i++)
                if (tailX[i] == fruitX && tailY[i] == fruitY)
                    valid = false;

        } while (!valid);
    }
}

int main() {
    srand(time(0));

    //Ẩn con trỏ chuột
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);

    Setup();

    cout << "Use WASD to move, X to quit" << endl;
    cout << "Press any key to start" << endl;
    _getch();//Nhấn nút bất kì để bắt đầu game

    while (!gameOver) {
        Draw();
        Input();
        Logic();
        Sleep(50); //Tốc độ game (Giá trị càng nhỏ --> tốc độ càng tăng)
    }

    //Hiện lại con trỏ chuột
    info.bVisible = TRUE;
    SetConsoleCursorInfo(consoleHandle, &info);

    cout << "Game Over! Final Score: " << score << endl;
    _getch(); //Nhấn nút bất kì để thoát chương trình
    return 0;
}