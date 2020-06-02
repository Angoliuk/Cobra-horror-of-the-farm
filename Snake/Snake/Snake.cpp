#include <iostream>
#include <ctime>
#include <vector>
#include <conio.h>

using namespace std;

class gameClass {
public:
    const int width = 100;
    const int height = 25;

    int x, y, score;  //Координаты и щёт игрока
    int numOfFruits = 5;
    int mouseX[5];
    int mouseY[5];
    string head = "^";

    int nTail;                        //Длина хвоста
    int tailX[99], tailY[99];

    enum MoveDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
    MoveDirection dir;
    bool GameOver;
    void Setup() {          //Настройка параметров
        GameOver = false;
        dir = STOP;
        x = width / 2 - 1;
        y = height / 2 - 1;
        for (int i = 0; i < numOfFruits; i++)
        {
            mouseX[i] = rand() % width;
            mouseY[i] = rand() % height;

        }
        score = 0;
    }
    void Draw() {           //прорисовка карты и змейки

        system("cls");      //Очистка консоли

        for (int i = 0; i < width + 1; i++)           //Верхняя Граница
            cout << "_";
        cout << endl;

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {     //Боковые границы

                bool fruitSpawn = false;
                for (int n = 0; n < numOfFruits; n++)
                {
                    if (mouseX[n] == j && mouseY[n] == i) {
                        fruitSpawn = true;
                    };
                }

                if (j == 0 || j == width - 1)
                    cout << "|";

                if (i == y && j == x)                      //Змейка
                    cout << head;
                else if (fruitSpawn)       //Фрукты
                    cout << '*';
                else {
                    bool print = false;

                    for (int k = 0; k < nTail; k++) {
                        if (tailX[k] == j && tailY[k] == i) {
                            print = true;
                            cout << head;
                        }
                    }
                    if (!print)
                        cout << " ";
                }
            }
            cout << endl;
        }


        for (int i = 0; i < width + 1; i++)            //Нижняя граница
            cout << "`";
        cout << endl;

        cout << "Score : " << score << endl << "Current lenght : " << nTail << endl;
    }
    void Input() {         //Слежка за нажатием

        if (_kbhit()) {
            switch (_getch())
            {
            case 'a':
                if (dir != RIGHT)
                {
                    head = "<";
                    dir = LEFT;
                }
                break;
            case 'd':
                if (dir != LEFT)
                {
                    head = ">";
                    dir = RIGHT;
                }
                break;
            case 'w':
                if (dir != DOWN)
                {
                    head = "^";
                    dir = UP;
                }
                break;
            case 's':
                if (dir != UP)
                {
                    head = "v";
                    dir = DOWN;
                }
                break;
            case 'x':
                GameOver = true;
                break;
            }
        }
    }
    void logic() {

        int prevX = tailX[0];         //Придыдущая позиция По X 
        int prevY = tailY[0];         //Придыдущая позиция По Y
        int prev2X, prev2Y;
        tailX[0] = x;
        tailY[0] = y;

        for (int i = 1; i < nTail; i++) {
            prev2X = tailX[i];
            prev2Y = tailY[i];
            tailX[i] = prevX;
            tailY[i] = prevY;
            prevX = prev2X;
            prevY = prev2Y;
        }

        switch (dir)
        {
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        }


        for (int i = 0; i < nTail; i++) {
            if (tailX[i] == x && tailY[i] == y || x == -1 || y == -1 || x == width || y == height)
                GameOver = true;
        }

        for (int i = 0; i < numOfFruits; i++)
        {
            if (x == mouseX[i] && y == mouseY[i]) {
                score += 10;
                mouseX[i] = rand() % width;
                mouseY[i] = rand() % height;
                nTail++;
            }
        }
        if (nTail == 99)
        {
            GameOver = true;
            cout << "You Win!";
        }
    }
};

int main()
{
    gameClass snakeGame;
    snakeGame.Setup();
    while (!snakeGame.GameOver)
    {
        snakeGame.Draw();
        snakeGame.Input();
        snakeGame.logic();
    }
    return 0;
}

