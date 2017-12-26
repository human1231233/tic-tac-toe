////tic-tac-toe
#include <iostream>
#include <random>
#include <ctime>
#include <chrono>
#include <memory.h>

#define DEBUG
bool gameLoop_bool = true;
const size_t BOARDSIZE = 3;
const size_t DEFAULTVALUE = 17;
const size_t MAX_MOVE_n = 5;
int board[BOARDSIZE][BOARDSIZE];
std::default_random_engine dre(time(NULL)); //!change time(NULL) with chrono !!!
std::uniform_int_distribution<int> random_second(0,2);

int check(int (&board_)[BOARDSIZE][BOARDSIZE]);
void restart(const int defaultValue);
void drawBoard();
void input(const int* xy, const int playerValue);
int* playerInput();
int *botInput(int bot_value, int player_value);
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


int check(int (&board_)[BOARDSIZE][BOARDSIZE])
{
        for(int i = 0; i < BOARDSIZE; i++)
        {
            if(board_[i][0] == board_[i][1] &&
               board_[i][1] == board_[i][2] && board_[i][2] != DEFAULTVALUE)
                return 1;
            else if(board_[0][i] == board_[1][i] &&
                    board_[1][i] == board_[2][i] && board_[2][i] != DEFAULTVALUE )
                return 1;
            else if(board_[0][0] == board_[1][1] &&
                    board_[1][1] == board_[2][2] && board_[2][2] != DEFAULTVALUE)
                return 1;
            else if(board_[2][0] == board_[1][1] &&
                    board_[1][1] == board_[0][2] && board_[0][2] != DEFAULTVALUE)
                return 1;
        }

    return 0;
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
        //!input(botInput(firstPlayer_value, secondPlayer_value), firstPlayer_value);
        if(check(board))
        {
            std::cout << std::endl;
            std::cout << "YOU HAVE WON !!!" << std::endl;
            break;
        }
        ++moveCounter;
        if(moveCounter>=MAX_MOVE_n){ std::cout << "\nDRAW!" << std::endl; break;}
        std::cout << "\nEnemy's move: " << std::endl;
        input(botInput(secondPlayer_value, firstPlayer_value),  secondPlayer_value);
        if(check(board))
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



#ifdef DEBUG
int *botInput(int bot_value, int player_value)
{
    int boardAnalist[BOARDSIZE][BOARDSIZE];
    int botXY[2];
    memcpy(boardAnalist, board, sizeof(board));
    for(int i = 0; i < BOARDSIZE; ++i)
    {
        std::cout << "i in first loop: " << i << "\n";
        for(int g = 0; g < BOARDSIZE; ++g)
        {
            //!boardAnalist[g][i] != DEFAULTVALUE &&
            //!boardAnalist[g][i] != bot_value
            if(boardAnalist[g][i] == 0)
            {
                std::cout << "Last player move has been found\n";
                int j=1;
                while(i+j<3)
                {
                    std::cout << "Entered the while loop\n";

                    if(boardAnalist[i+j][g] == DEFAULTVALUE)
                    {
                        boardAnalist[i+j][g] = player_value;
                        std::cout << "Here it is DEFAULTVALUE!\n";
                        if(check(boardAnalist))
                        {
                            botXY[0] = g, botXY[1] = i+j;
                            std::cout << "X: " << botXY[1] << "Y: " << botXY[0] << std::endl;
                            return botXY;
                        }
                    }
                    memcpy(boardAnalist, board, sizeof(board));
                    ++j;
                }
                j=1;
                while(g+j<3)
                {
                    std::cout << "Entered the second while loop\n";

                    if(boardAnalist[i][g+j] == DEFAULTVALUE)
                    {
                        boardAnalist[i][g+j] = player_value;
                        if(check(boardAnalist))
                        {
                            botXY[0] = g+j, botXY[1] = i;
                            std::cout << "X: " << botXY[1] << "Y: " << botXY[0] << std::endl;
                            return botXY;
                        }
                    }
                    memcpy(boardAnalist, board, sizeof(board));
                    ++j;
                }

            }

         }
      }

    memcpy(boardAnalist, board, sizeof(board));
    botXY[0] = random_second(dre);
    botXY[1] = random_second(dre);
    while(board[botXY[1]][botXY[0]] != DEFAULTVALUE)
    {
        std::cout << "return random values!\n";
        botXY[0] = random_second(dre);
        botXY[1] = random_second(dre);
    }
    return botXY;
}
#endif //DEBUG


