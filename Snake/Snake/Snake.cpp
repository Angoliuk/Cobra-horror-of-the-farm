#include <iostream>
#include <ctime>
#include <vector>
#include <conio.h>

using namespace std;

class gameClass {
private:

    int sizeOfBorders = 25;
    int width = this->sizeOfBorders * 4;
    int height = this->sizeOfBorders;

    int x, y, score;  //Координаты и щёт игрока
    int numOfFruits = 1;
    int* mouseX = new int[numOfFruits];
    int* mouseY = new int[numOfFruits];
    string head = "^";

    int nTail;                        //Длина хвоста
    int tailX[99], tailY[99];

    enum MoveDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
    MoveDirection dir;

public:

    bool GameOver;
    void fruitSpawn() {
        for (int i = 0; i < this->numOfFruits; i++)
        {
            this->mouseX[i] = rand() % this->width;
            this->mouseY[i] = rand() % this->height;

        }
    }
    void Setup() {          //Настройка параметров
        cout << "Enter height of farm from 15 to 40" << endl;
        cin >> this->sizeOfBorders;
        cout << "Enter number of fruits from 1 to 5" << endl;
        cin >> this->numOfFruits;
        this->GameOver = false;
        if (this->numOfFruits > 5 || this->sizeOfBorders > 40 || this->sizeOfBorders < 15)
        {
            this->GameOver = true;
        };
        this->dir = STOP;
        this->x = this->width / 2 - 1;
        this->y = this->height / 2 - 1;
        this->fruitSpawn();
        this->score = 0;
    }
    void Draw() {           //прорисовка карты и змейки

        system("cls");      //Очистка консоли

        for (int i = 0; i < this->width + 1; i++)           //Верхняя Граница
            cout << "_";
        cout << endl;

        for (int i = 0; i < this->height; i++) {
            for (int j = 0; j < this->width; j++) {     //Боковые границы

                bool fruitSpawn = false;
                for (int n = 0; n < this->numOfFruits; n++)
                {
                    if (this->mouseX[n] == j && this->mouseY[n] == i) {
                        fruitSpawn = true;
                    };
                }

                if (j == 0 || j == this->width - 1)
                    cout << "|";

                if (i == y && j == x)                      //Змейка
                    cout << this->head;
                else if (fruitSpawn)       //Фрукты
                    cout << '*';
                else {
                    bool print = false;

                    for (int k = 0; k < this->nTail; k++) {
                        if (this->tailX[k] == j && this->tailY[k] == i) {
                            print = true;
                            cout << this->head;
                        }
                    }
                    if (!print)
                        cout << " ";
                }
            }
            cout << endl;
        }


        for (int i = 0; i < this->width + 1; i++)            //Нижняя граница
            cout << "`";
        cout << endl;

        cout << "Score : " << this->score << endl << "Current lenght : " << this->nTail << endl;
    }
    void Input() {         //Слежка за нажатием

        if (_kbhit()) {
            switch (_getch())
            {
            case 'a':
                if (this->dir != RIGHT)
                {
                    this->head = "<";
                    this->dir = LEFT;
                }
                break;
            case 'd':
                if (this->dir != LEFT)
                {
                    this->head = ">";
                    this->dir = RIGHT;
                }
                break;
            case 'w':
                if (this->dir != DOWN)
                {
                    this->head = "^";
                    this->dir = UP;
                }
                break;
            case 's':
                if (this->dir != UP)
                {
                    this->head = "v";
                    this->dir = DOWN;
                }
                break;
            case 'x':
                this->GameOver = true;
                break;
            }
        }
    }
    void logic() {

        int prevX = this->tailX[0];         //Придыдущая позиция По X 
        int prevY = this->tailY[0];         //Придыдущая позиция По Y
        int prev2X, prev2Y;
        this->tailX[0] = this->x;
        this->tailY[0] = this->y;

        for (int i = 1; i < this->nTail; i++) {
            prev2X = this->tailX[i];
            prev2Y = this->tailY[i];
            this->tailX[i] = prevX;
            this->tailY[i] = prevY;
            prevX = prev2X;
            prevY = prev2Y;
        }

        switch (dir)
        {
        case LEFT:
            this->x--;
            break;
        case RIGHT:
            this->x++;
            break;
        case UP:
            this->y--;
            break;
        case DOWN:
            this->y++;
            break;
        }


        for (int i = 0; i < this->nTail; i++) {
            if (this->tailX[i] == this->x && this->tailY[i] == this->y || this->x == -1 || this->y == -1 || this->x == width || this->y == height)
                GameOver = true;
        }

        for (int i = 0; i < this->numOfFruits; i++)
        {
            if (this->x == this->mouseX[i] && this->y == this->mouseY[i]) {
                this->score += 10;
                this->mouseX[i] = rand() % this->width;
                this->mouseY[i] = rand() % this->height;
                this->nTail++;
            }
        }
        if (this->nTail == 99)
        {
            this->GameOver = true;
            cout << "You Win!";
        }
    }
    int builder() {
        Setup();
        while (!GameOver)
        {
            Draw();
            Input();
            logic();
        }
        return 0;
    }
};

int main()
{
    gameClass snakeGame;
    snakeGame.builder();
    
}

