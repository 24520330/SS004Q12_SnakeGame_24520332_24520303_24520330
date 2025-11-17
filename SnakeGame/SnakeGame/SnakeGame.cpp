
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
int gameSpeed = 150;

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

    //Di chuyển con trỏ tới góc trên trái để vẽ lại
    COORD coord;
    coord.X = 0;
    coord.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    // Vẽ tường TRÊN khu vực chơi, sử dụng kí tự "#"
    for (int i = 0; i < WIDTH + 2; ++i) cout << '#';
    cout << '\n';

    // Vẽ các hàng trong khu vực chơi
    for (int y = 0; y < HEIGHT; ++y) {
        // Vẽ tường TRÁI
        cout << '#';
        for (int x = 0; x < WIDTH; ++x) {
            if (x == headX && y == headY) {
                // Vẽ đầu rắn
                cout << 'O';
            }
            else if (x == fruitX && y == fruitY) {
                // Vẽ thức ăn
                cout << 'F';
            }
            else {
                // Kiểm tra đuôi
                bool printed = false;
                for (int k = 0; k < tailLength; ++k) {
                    if (tailX[k] == x && tailY[k] == y) {
                        cout << 'o';
                        printed = true;
                        break;
                    }
                }
                if (!printed) cout << ' ';
            }
        }
        // Vẽ tường PHẢI
        cout << '#';
        cout << '\n';
    }

    //Vẽ tường DƯỚI khu vực chơi, sử dụng kí tự "#"
    for (int i = 0; i < WIDTH + 2; ++i) cout << '#';
    cout << '\n';

    // Hiển thị điểm và tốc độ hiện tại
    cout << "Score: " << score << "    Speed: " << gameSpeed << "ms (use +/- to adjust)" << '\n';
}


void Input() {
    //Up(W), Down(S), Left(A), Right(D), Quit(X) 
    if (_kbhit()) {
        char ch = _getch();
        // Chuyển thành chữ hoa để xử lý cả chữ thường và hoa
        if (ch >= 'a' && ch <= 'z') ch = ch - 'a' + 'A';

        //"W" để di chuyển lên (nếu đang di chuyển xuống thì không thể thực hiện)
        if (ch == 'W' && dir != DOWN) dir = UP;
        //"A" để di chuyển trái (nếu đang di chuyển phải thì không thể thực hiện)
        else if (ch == 'A' && dir != RIGHT) dir = LEFT;
        //"D" để di chuyển phải (nếu đang di chuyển trái thì không thể thực hiện)
        else if (ch == 'D' && dir != LEFT) dir = RIGHT;
        //"S" để di chuyển xuống (nếu đang di chuyển lên thì không thể thực hiện)
        else if (ch == 'S' && dir != UP) dir = DOWN;
        //"X" để thoát chương trình 
        else if (ch == 'X') gameOver = true;
        // '+' giảm thời gian Sleep -> nhanh hơn; '-' tăng thời gian -> chậm hơn
        else if (ch == '+' || ch == '=') {
            if (gameSpeed > 20) gameSpeed -= 10;
        }
        else if (ch == '-') {
            if (gameSpeed < 2000) gameSpeed += 10;
        }
    }
}
void Logic() {
    //Di chuyển đuôi (Cập nhập cho đuôi đi theo đầu)
    //Phần đuôi đầu tiên đi theo đầu, các phần đuôi tiếp theo đi theo đuôi trước nó

    //Di chuyển đầu (Di chuyển theo hướng Input())

    //Va chạm tường (Kiểm tra nếu đầu rắn chạm tường thì xuất hiện ở hướng đối diện)

    //Tự va chạm với thân rắn (Kiểm tra nếu đầu rắn va chạm với bất kì phần đuôi rắn thì kết thúc chương trình)

    //Va chạm với thức ăn 
    //Kiểm tra nếu đầu rắn chạm thức ăn thì tăng điểm
    //Thêm đuôi
    //Tạo thức ăn tiếp theo không trùng với thân rắn (đầu, đuôi)
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