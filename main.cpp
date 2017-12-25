////tic-tac-toe

#include <iostream>
#include <random>
#include <ctime>
#include <chrono>

bool gameLoop_bool = true;
const size_t BOARDSIZE = 3;
const size_t DEFAULTVALUE = 17;
const size_t MAX_MOVE_n = 5;
int board[BOARDSIZE][BOARDSIZE];
std::default_random_engine dre(time(NULL)); //!change time(NULL) with chrono !!!
std::uniform_int_distribution<int> random_second(0,2);

int check();
void restart(const int defaultValue);
void drawBoard();
void input(const int* xy, const int playerValue);
int* playerInput();
int* botInput();
//!concentrate
void gameLoop(const int firstPlayer_value, const int secondPlayer_value);


int main()
{
    restart(DEFAULTVALUE);
//!improve this to chrono when you can

    int firstPlayer_value = 0;
    int secondPlayer_value = 1;
    gameLoop(firstPlayer_value, secondPlayer_value);


return 0;
}


int check()
{
        for(int i = 0; i < BOARDSIZE; i++)
        {
            if(board[i][0] == board[i][1] &&
               board[i][1] == board[i][2] && board[i][2] != DEFAULTVALUE)
                return 1;
            else if(board[0][i] == board[1][i] &&
                    board[1][i] == board[2][i] && board[2][i] != DEFAULTVALUE )
                return 1;
            else if(board[0][0] == board[1][1] &&
                    board[1][1] == board[2][2] && board[2][2] != DEFAULTVALUE)
                return 1;
            else if(board[2][0] == board[1][1] &&
                    board[1][1] == board[0][2] && board[0][2] != DEFAULTVALUE)
                return 1;
        }

    return 0;
    const size_t MAX_MOVE_n = 5;
}

void restart(const int defaultValue)
{
    for(int i = 0; i < BOARDSIZE; i++)
    {
        for(int g = 0; g < BOARDSIZE; g++)
        {
            board[i][g] = defaultValue;
        }
    }
}

void drawBoard()
{
    system("color a");
    system("cls");
    for(int i = 0; i < BOARDSIZE; i++)
    {
        std::cout << std::endl << "|";
        for(int g = 0; g < BOARDSIZE; g++)
            std::cout << " " << board[i][g] << " |";
    }
}


void input(const int* xy, const int playerValue)
{
    board[xy[1]][xy[0]] = playerValue;
    drawBoard();
}


void gameLoop(const int firstPlayer_value, const int secondPlayer_value)
{
    restart(DEFAULTVALUE);
    drawBoard();
    size_t moveCounter = 0;
    while(gameLoop_bool)
    {
        input(playerInput(), firstPlayer_value);
        if(check())
        {
            std::cout << std::endl;
            std::cout << "YOU HAVE WON !!!" << std::endl;
            break;
        }
        ++moveCounter;
        if(moveCounter>=MAX_MOVE_n){ std::cout << "\nDRAW!" << std::endl; break;}
        std::cout << "\nEnemy's move: " << std::endl;
        input(botInput(), secondPlayer_value);
        if(check())
        {
            std::cout << "\nCOMPUTER HAS WON !!!" << std::endl;
            break;
        }
    }
}

int* playerInput()
{
    int input[2];
    std::cout << "\nInput x: "; std::cin >> input[0];
    std::cout << "Input y: "; std::cin >> input[1];
    if(input[0] > 2 || input[0] < 0 || input[1] > 2 || input[1] < 0 || board[input[1]][input[0]] != DEFAULTVALUE){
        std::cout << "Wrong Input!" << std::endl;
        drawBoard();
        playerInput();
    }
    else
        return input;
}

int* botInput()
{
    int botXY[2];
    botXY[0] = random_second(dre);
    botXY[1] = random_second(dre);
    while(board[botXY[1]][botXY[0]] != DEFAULTVALUE)
    {
        botXY[0] = random_second(dre);
        botXY[1] = random_second(dre);
    }
    return botXY;
}

int *testBotInput()
{
    int botXY[2];

}

