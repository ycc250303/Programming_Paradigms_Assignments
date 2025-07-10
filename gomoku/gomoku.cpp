#define _CRT_SECURE_NO_WARNINGS
#include <random>
#include <cstdio>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <time.h>
#include <vector>

#define DEBUG_MODE 1// 调试模式开关

/*define status*/
typedef enum {
    Empty,
    Black,
    White
} Status;

/*define direction*/
typedef struct {
    int dx;
    int dy;
}Direction;

/*define point*/
typedef struct {
    int x;
    int y;
    int score;
}Point;



const Direction directions[8] = { {1, 0}, {0, 1}, {1, 1}, {1, -1} , {-1, 0} , {0, -1} , {-1, -1} , {-1, 1} }; //偏移方向
const int BOARD_SIZE = 12;              // 棋盘大小
const int EXPLORATION_DEPTH = 5;        // 探索深度
const int MAX_SCORE = 1000000000;       // 最大分数
const int MIN_SCORE = -1000000000;      // 最小分数
const int LIVE_FIVE = 10000000;         // 五连分数
const int LIVE_FOUR = 100000;           // 活四分数
const int BLOCK_FOUR = 1000;            // 冲四分数
const int LIVE_THREE = 1000;            // 活三分数
const int BLOCK_THREE = 100;            // 冲三分数
const int LIVE_TWO = 100;               // 活二分数
const int BLOCK_TWO = 10;               // 冲二分数
const int LIVE_ONE = 10;                // 活一分数
const int BLOCK_ONE = 1;                // 冲一分数


Status board[BOARD_SIZE][BOARD_SIZE];   //棋盘
Status myFlag;                          //我方棋子标志
Status enemyFlag;                       //敌方棋子标志
int myBoard[BOARD_SIZE][BOARD_SIZE];    //我方旗子得分
int enemyBoard[BOARD_SIZE][BOARD_SIZE]; //敌方旗子得分
int totalSteps;                         //总步数


/*
 * Function Name:
 * Function:
 * Input Parameters:
 * Return Value:
 */
inline bool isValidCoord(int x, int y) {
    return (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE);
}

/*
 * Function Name:   cmp
 * Function:        make the
 * Input Parameters:const Point& a
 *                  const Point& b
 * Return Value:    true / false
 */
inline bool cmp(const Point& a, const Point& b) {
    return a.score > b.score;
}

inline bool operator!=(const Direction& d1, const Direction& d2) {
    return (d1.dx != d2.dx || d1.dy != d2.dy);
}


#ifdef DEBUG_MODE
/*
 * Function Name:   printBoard
 * Function:        print the chessboard
 * Input Parameters:void
 * Return Value:    void
 */
void printBoard() {
    printf("   ");
    fflush(stdout);
    for (int i = 0; i < BOARD_SIZE; i++) {
        printf("%2d ", i);
        fflush(stdout);
    }

    printf("  Y\n  +");
    fflush(stdout);
    for (int i = 0; i < BOARD_SIZE; i++) {
        printf("--+");
        fflush(stdout);
    }
    printf("\n");
    fflush(stdout);
    for (int i = 0; i < BOARD_SIZE; i++) {
        printf("%2d|", i);
        fflush(stdout);
        for (int j = 0; j < BOARD_SIZE; j++) {
            printf("%s|", (board[i][j] == Empty ? "  " : (board[i][j] == Black ? "●" : "○")));
            fflush(stdout);
        }
        printf("\n  +");
        fflush(stdout);
        for (int i = 0; i < BOARD_SIZE; i++) {
            printf("--+");
            fflush(stdout);
        }
        printf("\n");
        fflush(stdout);
    }
    printf("X\n");
    fflush(stdout);
}
/*
 * Function Name:   printScore
 * Function:        print the score of chessboard
 * Input Parameters:void
 * Return Value:    void
 */
void printScore() {
    printf("   ");
    fflush(stdout);
    for (int i = 0; i < BOARD_SIZE; i++) {
        printf("%10d ", i);
        fflush(stdout);
    }
    printf("\n  +");
    fflush(stdout);
    for (int i = 0; i < BOARD_SIZE; i++) {
        printf("----------+");
        fflush(stdout);
    }
    printf("\n");
    fflush(stdout);
    for (int i = 0; i < BOARD_SIZE; i++) {
        printf("%2d|", i);
        fflush(stdout);
        for (int j = 0; j < BOARD_SIZE; j++) {
            printf("%s", (board[i][j] == Empty ? "  " : (board[i][j] == Black ? "●" : "○")));
            fflush(stdout);
            if (board[i][j] == myFlag) {
                printf("%8d", myBoard[i][j]);
                fflush(stdout);
            }
            else if (board[i][j] == enemyFlag) {
                printf("%8d", -enemyBoard[i][j]);
                fflush(stdout);
            }
            else {
                printf("        ");
                fflush(stdout);
            }
            printf("|");
            fflush(stdout);
        }
        printf("\n  +");
        fflush(stdout);
        for (int i = 0; i < BOARD_SIZE; i++) {
            printf("----------+");
            fflush(stdout);
        }
        printf("\n");
        fflush(stdout);
    }
}
#endif // DEBUG_MODE

/*
 * Function Name:   evaluateChessLink
 * Function:        evaluate the chess link
 * Input Parameters:int myCount
 *                  int enemyCount
 *                  int emptyCount
 *                  int emptyPos
 * Return Value:    int : the score of chesslink
 */
int evaluateChessLink(const int myCount,const int enemyCount,const int emptyCount,const int emptyPos) {

    if (emptyPos <= 0) {/*棋子全连*/
        if (myCount >= 5)
            return LIVE_FIVE;                               //五连
        if (enemyCount == 0) {/*两边无对方棋子*/
            if (myCount == 4)       return LIVE_FOUR;       //活四
            else if (myCount == 3)  return LIVE_THREE;      //活三
            else if (myCount == 2)  return LIVE_TWO;        //活二
            else if (myCount == 1)  return LIVE_ONE;        //活一
        }
        else if (enemyCount == 1) {/*两边有一个对方棋子*/
            if (myCount == 4)       return BLOCK_FOUR;      //冲四
            else if (myCount == 3)  return BLOCK_THREE;     //冲三
            else if (myCount == 2)  return BLOCK_TWO;       //冲二
            else if (myCount == 1)  return BLOCK_ONE;       //冲一
        }
    }
    else if (emptyPos == 1 || emptyPos == myCount - 1) {
        if (myCount >= 6)
            return LIVE_FIVE;                               //五连
        if (enemyCount == 0) {
            if (emptyCount == 1) {
                if (myCount == 5)       return LIVE_FOUR;       //活四
                else if (myCount == 4)  return BLOCK_FOUR;      //冲四
                else if (myCount == 3)  return LIVE_THREE;      //活三
                else if (myCount == 2)  return LIVE_TWO;        //活二
            }
            else if (emptyCount == 2) {
                if (myCount == 5)       return LIVE_FOUR;       //活四
                else if (myCount == 4)  return LIVE_THREE;      //活三
                else if (myCount == 3)  return BLOCK_THREE;     //冲三
                else if (myCount == 2)  return LIVE_TWO;        //活二
            }
        }
        else if (enemyCount == 1) {
            if (emptyCount == 1) {
                if (myCount == 5)       return BLOCK_FOUR;      //冲四
                else if (myCount == 4)  return BLOCK_FOUR;      //冲四
                else if (myCount == 3)  return BLOCK_THREE;     //冲三
                else if (myCount == 2)  return BLOCK_TWO;       //冲二
            }
            else if (emptyCount == 2) {
                if (myCount == 5)       return BLOCK_FOUR;      //冲四
                else if (myCount == 4)  return BLOCK_THREE;     //冲三
                else if (myCount == 3)  return BLOCK_TWO;       //冲二
                else if (myCount == 2)  return BLOCK_ONE;       //冲一
            }
        }
        else if (enemyCount == 2) {
            if (emptyCount == 1) {
                if (myCount == 5)       return BLOCK_FOUR;      //冲四
                else if (myCount == 4)  return BLOCK_FOUR;      //冲四
            }
            else if (emptyCount == 2) {
                if (myCount == 5)       return BLOCK_FOUR;      //冲四
                else if (myCount == 4)  return BLOCK_THREE;     //冲三
                else if (myCount == 3)  return BLOCK_TWO;       //冲二
            }
        }
    }
    else if (emptyPos == 2 || emptyPos == myCount - 2) {
        if (myCount >= 7)
            return LIVE_FIVE;                               //五连
        if (enemyCount == 0) {
            if (emptyCount == 1) {
                if (myCount == 6)       return LIVE_FOUR;       //活四
                else if (myCount == 5)  return BLOCK_FOUR;      //冲四
                else if (myCount == 4)  return BLOCK_FOUR;      //冲四
                else if (myCount == 3)  return LIVE_THREE;      //活三
            }
            else if (emptyCount == 2) {
                if (myCount == 6)       return LIVE_FOUR;       //活四
                else if (myCount == 5)  return LIVE_THREE;      //活三
                else if (myCount == 4)  return BLOCK_THREE;     //冲三
                else if (myCount == 3)  return BLOCK_THREE;     //冲三
            }
        }
        else if (enemyCount == 1) {
            if (emptyCount == 1) {
                if (myCount == 6)       return BLOCK_FOUR;      //冲四
                else if (myCount == 5)  return BLOCK_FOUR;      //冲四
                else if (myCount == 4)  return BLOCK_FOUR;      //冲四
                else if (myCount == 3)  return BLOCK_THREE;     //冲三
            }
            else if (emptyCount == 2) {
                if (myCount == 6)       return BLOCK_FOUR;      //冲四
                else if (myCount == 5)  return LIVE_THREE;      //活三
                else if (myCount == 4)  return BLOCK_THREE;     //冲三
                else if (myCount == 3)  return BLOCK_THREE;     //冲三
            }
        }
        else if (enemyCount == 2) {
            if (emptyCount == 1) {
                if (myCount == 6)       return BLOCK_FOUR;      //冲四
                else if (myCount == 5)  return BLOCK_FOUR;      //冲四
                else if (myCount == 4)  return BLOCK_FOUR;      //冲四
            }
            else if (emptyCount == 2) {
                if (myCount == 6)       return BLOCK_FOUR;      //冲四
                else if (myCount == 5)  return BLOCK_THREE;     //冲三
                else if (myCount == 4)  return BLOCK_THREE;     //冲三
                else if (myCount == 3)  return BLOCK_THREE;     //冲三
            }
        }
    }
    else if (emptyPos == 3 || emptyPos == myCount - 3) {
        if (myCount >= 8)
            return LIVE_FIVE;                               //五连
        if (enemyCount == 0) {
            if (emptyCount == 1) {
                if (myCount == 7)       return LIVE_FOUR;       //活四
                else if (myCount == 6)  return BLOCK_FOUR;      //冲四
                else if (myCount == 5)  return BLOCK_FOUR;      //冲四
                else if (myCount == 4)  return BLOCK_FOUR;      //冲四
            }
            else if (emptyCount == 2) {
                if (myCount == 7)       return LIVE_FOUR;       //活四
                else if (myCount == 6)  return LIVE_THREE;      //活三
                else if (myCount == 5)  return LIVE_THREE;      //活三
                else if (myCount == 4)  return LIVE_THREE;      //活三
            }
        }
        else if (enemyCount == 1) {
            if (emptyCount == 1) {
                if (myCount == 7)       return LIVE_FOUR;       //活四
                else if (myCount == 6)  return BLOCK_FOUR;      //冲四
                else if (myCount == 5)  return BLOCK_FOUR;      //冲四
                else if (myCount == 4)  return BLOCK_FOUR;      //冲四
            }
            else if (emptyCount == 2) {
                if (myCount == 7)       return LIVE_FOUR;       //活四
                else if (myCount == 6)  return LIVE_THREE;      //活三
                else if (myCount == 5)  return BLOCK_THREE;     //冲三
                else if (myCount == 4)  return BLOCK_THREE;     //冲三
            }
        }
        else if (enemyCount == 2) {
            if (emptyCount == 1) {
                if (myCount == 7)       return BLOCK_FOUR;      //冲四
                else if (myCount == 6)  return BLOCK_FOUR;      //冲四
                else if (myCount == 5)  return BLOCK_FOUR;      //冲四
                else if (myCount == 4)  return BLOCK_FOUR;      //冲四
            }
            else if (emptyCount == 2) {
                if (myCount == 7)       return BLOCK_FOUR;      //冲四
                else if (myCount == 6)  return BLOCK_THREE;     //冲三
                else if (myCount == 5)  return BLOCK_THREE;     //冲三
                else if (myCount == 4)  return BLOCK_THREE;     //冲三
            }
        }
    }
    else if (emptyPos == 4 || emptyPos == myCount - 4) {
        if (myCount >= 9)
            return LIVE_FIVE;                               //五连
        if (enemyCount == 0) {
            if (myCount == 8)       return LIVE_FOUR;       //活四
            else if (myCount == 7)  return LIVE_FOUR;       //活四
            else if (myCount == 6)  return LIVE_FOUR;       //活四
            else if (myCount == 5)  return LIVE_FOUR;       //活四
        }
        else if (enemyCount == 1) {
            if (myCount == 8)       return LIVE_FOUR;       //活四
            else if (myCount == 7)  return BLOCK_FOUR;      //冲四
            else if (myCount == 6)  return BLOCK_FOUR;      //冲四
            else if (myCount == 5)  return BLOCK_FOUR;      //冲四
        }
        else if (enemyCount == 2) {
            if (myCount == 8)       return BLOCK_FOUR;      //冲四
            else if (myCount == 7)  return BLOCK_FOUR;      //冲四
            else if (myCount == 6)  return BLOCK_FOUR;      //冲四
            else if (myCount == 5)  return BLOCK_FOUR;      //冲四
            else if (myCount == 4)  return BLOCK_FOUR;      //冲四
        }
    }
    else if (emptyPos == 5 || emptyPos == myCount - 5) {
        return LIVE_FIVE;                                   //五连
    }
    return 0;                                               //缺省
}

/*
 * Function Name:   evaluatePoint
 * Function:        evaluate the chess point
 * Input Parameters:int x
 *                  int y
 *                  Status flag
 * Return Value:    int : the score of chess point
 */
int evaluatePoint(const int x,const int y,const  Status flag) {
    int score = 0;
    int myCount = 1, enemyCount = 0, emptyCount = 0, emptyPos = -1;
    int deltaX, deltaY;
    /*explore the point in all directions*/
    for (int i = 0; i < 4; i++) {
        myCount = 1, enemyCount = 0, emptyCount = 0, emptyPos = -1;
        deltaX = directions[i].dx;
        deltaY = directions[i].dy;

        for (int curX = x + deltaX, curY = y + deltaY; true; curX += deltaX, curY += deltaY) {
            /*check the boundary*/
            if (!isValidCoord(curX, curY)) {
                enemyCount++;
                break;
            }
            /*check the chess*/
            if (board[curX][curY] == Empty) {
                if (emptyPos == -1 && (isValidCoord(curX + deltaX, curY + deltaY) && board[curX + deltaX][curY + deltaY] == flag)) {
                    emptyPos = myCount;
                    emptyCount = 1;
                    continue;
                }
                else if (emptyPos == -1 && (isValidCoord(curX + 2 * deltaX, curY + 2 * deltaY) && board[curX + 2 * deltaX][curY + 2 * deltaY] == flag)) {
                    emptyPos = myCount;
                    emptyCount = 2;
                    curX += deltaX;
                    curY += deltaY;
                    continue;
                }
                else {
                    break;
                }
            }
            else if (board[curX][curY] == flag) {
                myCount++;
                continue;
            }
            else {
                enemyCount++;
                break;
            }
        }
        //myCount
        /*explore the point in the opposite direction*/
        for (int curX = x - deltaX, curY = y - deltaY; true; curX -= deltaX, curY -= deltaY) {
            if (!isValidCoord(curX, curY)) {
                enemyCount++;
                break;
            }
            if (board[curX][curY] == Empty) {
                if (emptyPos == -1 && (isValidCoord(curX - deltaX, curY - deltaY) && board[curX - deltaX][curY - deltaY] == flag)) {
                    emptyPos = 0;
                    emptyCount = 1;
                    continue;
                }
                else if (emptyPos == -1 && (isValidCoord(curX - 2 * deltaX, curY - 2 * deltaY) && board[curX - 2 * deltaX][curY - 2 * deltaY] == flag)) {
                    emptyPos = 0;
                    emptyCount = 2;
                    curX -= deltaX;
                    curY -= deltaY;
                    continue;
                }
                else {
                    break;
                }
            }
            else if (board[curX][curY] == flag) {
                if (emptyPos != -1)
                    emptyPos++;
                myCount++;
                continue;
            }
            else {
                enemyCount++;
                break;
            }
        }
        score += evaluateChessLink(myCount, enemyCount, emptyCount, emptyPos);
    }
    return score;
}

/*
 * Function Name:   evaluateBoard
 * Function:        evaluate the chessboard
 * Input Parameters:void
 * Return Value:    int : the score of chessboard
 */
int evaluateBoard() {
    int score = 0;
    for (int x = 0; x < BOARD_SIZE; x++) {
        for (int y = 0; y < BOARD_SIZE; y++) {
            if (board[x][y] == myFlag) {
                score += myBoard[x][y];
            }
            else if (board[x][y] == enemyFlag) {
                score -= enemyBoard[x][y];
            }
        }
    }
    return score;
}


/*
 * Function Name:   updateScore
 * Function:        update the score of the point
 * Input Parameters:const int x
 *                  const int y
 * Return Value:    void
 */
void updateScore(const int x, const int y) {
    /*update the score of the point*/
    if (board[x][y] == myFlag) {
        myBoard[x][y] = evaluatePoint(x, y, myFlag);
    }
    else if (board[x][y] == enemyFlag) {
        enemyBoard[x][y] = evaluatePoint(x, y, enemyFlag);
    }
    else {
        myBoard[x][y] = 0;
        enemyBoard[x][y] = 0;
    }

    /*update the score of the link*/
    for (int i = 0; i < 8; i++) {
        int curX = x, curY = y;
        while (true) {
            curX += directions[i].dx;
            curY += directions[i].dy;
            if (!isValidCoord(curX, curY)) {
                break;
            }
            if (board[curX][curY] == myFlag) {
                myBoard[curX][curY] = evaluatePoint(curX, curY, myFlag);
            }
            else if (board[curX][curY] == enemyFlag) {
                enemyBoard[curX][curY] = evaluatePoint(curX, curY, enemyFlag);
            }
            else if (board[curX][curY] == Empty) {
                myBoard[x][y] = 0;
                enemyBoard[x][y] = 0;
            }
        }
    }
}

/*
 * Function Name:   chessDown
 * Function:        decide the chess
 * Input Parameters:const int x
 *                  const int y
 *                  const Status flag
 * Return Value:    void
 */
void chessDown(const int x, const int y, const Status flag) {
    board[x][y] = flag;
    updateScore(x, y);
}


/*
 * Function Name:   checkLiveFive
 * Function:        check if the chess link is a live five 
 * Input Parameters:const int x
 *                  const int y
 *                  const Status flag
 *                  const int flagCount
 * Return Value:    true / false
 */
bool checkLiveFive(const int x, const int y, const Status flag) {
    int curX, curY, count;
    for (int i = 0; i < 4; i++) {
        count = 1;
        curX = x + directions[i].dx;
        curY = y + directions[i].dy;
        while (isValidCoord(curX, curY) && board[curX][curY] == flag) {
            count++;
            curX += directions[i].dx;
            curY += directions[i].dy;
        }
        curX = x - directions[i].dx;
        curY = y - directions[i].dy;
        while (isValidCoord(curX, curY) && board[curX][curY] == flag) {
            count++;
            curX -= directions[i].dx;
            curY -= directions[i].dy;
        }
        if (count >= 5)
            return true;
    }
    return false;
}

/*
 * Function Name:   checkChessLink
 * Function:        check the chess link
 * Input Parameters:const int x
 *                  const int y
 *                  const Status flag
 *                  const int flagCount
 *                  const int emptyCount
 *                  Direction& dir
 * Return Value:    int : the number of chess link
 */
int checkChessLink(const int x, const int y, const Status flag, const int flagCount, const int emptyCount,Direction &dir) {
    int curX, curY, deltaX, deltaY, count, empty, emptyFlag;
    int linkCount = 0;
    for (int i = 0; i < 4; i++) {
        count = 1;
        empty = 0;
        emptyFlag = 0;
        deltaX = directions[i].dx;
        deltaY = directions[i].dy;
        curX = x + deltaX;
        curY = y + deltaY;
        while (isValidCoord(curX, curY)) {
            if (board[curX][curY] == flag) {
                count++;
            }
            else if (board[curX][curY] == Empty) {
                if (flagCount == 4 && emptyCount == 2) {
                    empty++;
                    break;
                }
                if ((isValidCoord(curX + deltaX, curY + deltaY) && board[curX + deltaX][curY + deltaY] == flag) && emptyFlag == 0) {
                    emptyFlag = 1;
                }
                else{
                    empty++;
                    break;
                }
         
            }
            else
                break;
            curX += deltaX;
            curY += deltaY;
        }

        curX = x - deltaX;
        curY = y - deltaY;
        while (isValidCoord(curX, curY)) {
            if (board[curX][curY] == flag)
                count++;
            else if (board[curX][curY] == Empty) {
                if (flagCount == 4 && emptyCount == 2) {
                    empty++;
                    break;
                }
                if ((isValidCoord(curX - deltaX, curY - deltaY) && board[curX - deltaX][curY - deltaY] == flag)&& emptyFlag ==0) {
                    emptyFlag = 1;
                }
                else {
                    empty++;
                    break;
                }
            }
            else
                break;
            curX -= deltaX;
            curY -= deltaY;
        }
        if (count >= flagCount && empty >= emptyCount) {
            linkCount++;
            dir = directions[i];
        }
    }
    return linkCount;
}


/*
 * Function Name:   checkNeighbour
 * Function:        check whether the point has neighbour
 * Input Parameters:const int x
 *                  const int y
 * Return Value:    true / false
 */
bool checkNeighbour(const int x, const int y, const int radius = 1) {
    int startX = std::max(0, x - radius);
    int endX = std::min(BOARD_SIZE - 1, x + radius);
    int startY = std::max(0, y - radius);
    int endY = std::min(BOARD_SIZE - 1, y + radius);

    for (int curX = startX; curX <= endX; curX++) {
        for (int curY = startY; curY <= endY; curY++) {
            if (curX == x && curY == y)
                continue;
            if (board[curX][curY] != Empty)
                return true;
        }
    }
    return false;
}

/*
 * Function Name:   noChoiceMove
 * Function:        check whether the next move has choice
 * Input Parameters:int& nextX
 *                  int& nextY
 *                  int& score
 * Return Value:    true / false
 */
bool noChoiceMove(int& nextX, int& nextY, int& score,const Status flag) {
    Status otherFlag = flag == myFlag ? enemyFlag : myFlag;
    /*first step*/
    if (totalSteps == 4) {
        nextX = 4;
        nextY = 4;
        return false;
    }
    if (totalSteps == 5) {
        if (board[4][4] == Black) {
            nextX = 7;
            nextY = 4;
            return false;
        }
        else if (board[7][7] == Black) {
            nextX = 4;
            nextY = 7;
            return false;
        }
        else if (board[4][7] == Black) {
            nextX = 7;
            nextY = 4;
            return false;
        }
        else if (board[7][4] == Black) {
            nextX = 4;
            nextY = 7;
            return false;
        }
    }

    /*check live five*/
    for (int x = 0; x < BOARD_SIZE; x++) {
        for (int y = 0; y < BOARD_SIZE; y++) {
            if (board[x][y] == Empty && checkLiveFive(x, y, flag)) {
                nextX = x;
                nextY = y;
                return false;
            }
        }
    }


    for (int x = 0; x < BOARD_SIZE; x++) {
        for (int y = 0; y < BOARD_SIZE; y++) {
            if (board[x][y] == Empty && checkLiveFive(x, y, otherFlag)) {
                nextX = x;
                nextY = y;
                return false;
            }
        }
    }

    /*check live four / live three and block four / double block four / double live three */
    Direction dir,dir1, dir2;
    dir1 = { 0,0 }, dir2 = { 0,0 };
    std::vector<Point> tempPoints1;
    for (int x = 0; x < BOARD_SIZE; x++) {
        for (int y = 0; y < BOARD_SIZE; y++) {
            if (board[x][y] == Empty && (checkChessLink(x, y, flag, 4, 2, dir)
                || (checkChessLink(x, y, flag, 4, 1, dir1) && checkChessLink(x, y, flag, 3, 2, dir2) && dir1 != dir2)
                || (checkChessLink(x, y, flag, 4, 1, dir1) && checkChessLink(x, y, flag, 4, 1, dir2) && dir1 != dir2))) {
                tempPoints1.push_back({ x, y, evaluatePoint(x, y, flag) });
            }
        }
    }
    /*choose the point which has higher score*/
    if (tempPoints1.size() > 0) {
        std::sort(tempPoints1.begin(), tempPoints1.end(), cmp);
        nextX = tempPoints1[0].x;
        nextY = tempPoints1[0].y;
        return false;
    }


    std::vector<Point> tempPoints2;
    for (int x = 0; x < BOARD_SIZE; x++) {
        for (int y = 0; y < BOARD_SIZE; y++) {
            if (board[x][y] == Empty && (checkChessLink(x, y, otherFlag, 4, 2, dir)
                || (checkChessLink(x, y, otherFlag, 4, 1, dir1) && checkChessLink(x, y, otherFlag, 3, 2, dir2) && dir1 != dir2)
                || (checkChessLink(x, y, otherFlag, 4, 1, dir1) && checkChessLink(x, y, otherFlag, 4, 1, dir2) && dir1 != dir2))) {
                tempPoints2.push_back({ x, y, evaluatePoint(x, y, otherFlag) });
            }
        }
    }
    if (tempPoints2.size() > 0) {
        std::sort(tempPoints2.begin(), tempPoints2.end(), cmp);
        nextX = tempPoints2[0].x;
        nextY = tempPoints2[0].y;
        return false;
    }

    /*check double live three */
    std::vector<Point> tempPoints3;
    for (int x = 0; x < BOARD_SIZE; x++) {
        for (int y = 0; y < BOARD_SIZE; y++) {
            if (board[x][y] == Empty && (checkChessLink(x, y, flag, 3, 2, dir) == 2)) {
                tempPoints3.push_back({ x, y, evaluatePoint(x, y, flag) });
            }
        }
    }
    if (tempPoints3.size() > 0) {
        std::sort(tempPoints3.begin(), tempPoints3.end(), cmp);
        nextX = tempPoints3[0].x;
        nextY = tempPoints3[0].y;
        return false;
    }

    std::vector<Point> tempPoints4;
    for (int x = 0; x < BOARD_SIZE; x++) {
        for (int y = 0; y < BOARD_SIZE; y++) {
            if (board[x][y] == Empty && (checkChessLink(x, y, otherFlag, 3, 2,dir) == 2)) {
                tempPoints4.push_back({ x, y, evaluatePoint(x, y, otherFlag) });
            }
        }
    }
    if (tempPoints4.size() > 0) {
        std::sort(tempPoints4.begin(), tempPoints4.end(), cmp);
        nextX = tempPoints4[0].x;
        nextY = tempPoints4[0].y;
        return false;
    }   

    /*have choice*/
    return true;
}



/*
 * Function Name:   assumeChessDown
 * Function:        assume the chess down
 * Input Parameters:Point nextMoves[]
 *                  int& moveNum
 *                  const Status flag
 * Return Value:    void
 */
void assumeChessDown(Point nextMoves[], int& moveNum, const Status flag) {
    moveNum = 0;
    for (int x = 0; x < BOARD_SIZE; x++) {
        for (int y = 0; y < BOARD_SIZE; y++) {
            if (board[x][y] == Empty && checkNeighbour(x, y)) {
                nextMoves[moveNum++] = { x,y,evaluatePoint(x, y, flag) };
            }
        }
    }
    std::sort(nextMoves, nextMoves + moveNum, cmp);
}

/*
 * Function Name:   alphaBeta
 * Function:        the alpha beta pruning algorithm
 * Input Parameters:const int depth
 *                  int alpha
 *                  int beta
 *                  const Status flag
 *                  int& nextX
 *                  int& nextY
 * Return Value:    int
 */
int alphaBeta(const int depth, int alpha, int beta, const Status flag, int& nextX, int& nextY) {
    if (depth == 0) {
        return -evaluateBoard();
    }

    int moveNum = 0, bestLocalX = -1, bestLocalY = -1, score = 0;
    Point nextMoves[BOARD_SIZE * BOARD_SIZE];
    assumeChessDown(nextMoves, moveNum, flag);
    if (moveNum == 0) {
        return -evaluateBoard();
    }

    if (!noChoiceMove(bestLocalX, bestLocalY, score, flag)) {
        chessDown(bestLocalX, bestLocalY, flag); 
        int evalScore = -alphaBeta(depth - 1, -beta, -alpha, (flag == myFlag) ? enemyFlag : myFlag, nextX, nextY);
        chessDown(bestLocalX, bestLocalY, Empty);
        if (depth == EXPLORATION_DEPTH && bestLocalX != -1 && bestLocalY != -1) {
            nextX = bestLocalX;
            nextY = bestLocalY;
        }
        return evalScore;
    }

    if (totalSteps >= 60) {
        if (depth <= 2)
            moveNum = moveNum > 10 ? 10 : moveNum;
        else if (depth <= 4)
            moveNum = moveNum > 20 ? 20 : moveNum;
    }

    for (int i = 0; i < moveNum; i++) {
        Point move = nextMoves[i];
        chessDown(move.x, move.y, flag);/*assume move*/
        score = -alphaBeta(depth - 1, -beta, -alpha, (flag == myFlag) ? enemyFlag : myFlag, nextX, nextY);
        chessDown(move.x, move.y, Empty); /*cancal move*/
        if (score >= beta) {
            return beta;/*cut off*/
        }
        if (score > alpha) {/*cut off*/
            alpha = score;
            bestLocalX = move.x;
            bestLocalY = move.y;
        }
    }

    if (depth == EXPLORATION_DEPTH && bestLocalX != -1 && bestLocalY != -1) {
        nextX = bestLocalX;
        nextY = bestLocalY;
    }
    return alpha;
}

/*
 * Function Name:   start
 * Function:        the start function
 * Input Parameters:void
 * Return Value:    void
 */
void start() {
    /*input the num of myflag*/
    int tempFlag;
    scanf("%d", &tempFlag);
    myFlag = (tempFlag == Black ? Black : White);
    enemyFlag = (tempFlag == Black ? White : Black);
    memset(board, Empty, sizeof(board));
    memset(myBoard, 0, sizeof(myBoard));
    memset(enemyBoard, 0, sizeof(enemyBoard));

    /*initialize*/
    chessDown(5, 5, White);
    chessDown(5, 6, Black);
    chessDown(6, 5, Black);
    chessDown(6, 6, White);
    totalSteps = 4;

    printf("OK\n");
    fflush(stdout);
}


/*
 * Function Name:   turn
 * Function:        decide the next chess
 * Input Parameters:void
 * Return Value:    void
 */
void turn() {

    int nextX = -1, nextY = -1, score = 0;
   if (noChoiceMove(nextX, nextY, score,myFlag)) {
        score = alphaBeta(EXPLORATION_DEPTH, MIN_SCORE, MAX_SCORE, myFlag, nextX, nextY);
    }

    if (nextX == -1 || nextY == -1) {
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                if (board[i][j] == Empty) {
                    nextX = i;
                    nextY = j;
                    break;
                }
            }
        }
    }

    chessDown(nextX, nextY, myFlag);// decide move
    totalSteps++;
    printf("%d %d\n", nextX, nextY);
    fflush(stdout);

#if DEBUG_MODE
    /*print the information of debug*/
    //printScore();
    printBoard();
    printf("DEBUG [nextX = %d nextY = %d score = %d]\n", nextX, nextY, score);
#endif // DEBUG_MODE
}

/*
 * Function Name:   place
 * Function:        input the enemychess
 * Input Parameters:void
 * Return Value:    void
 */
void place() {
    Point command = { 0, 0, 0 };
#if DEBUG_MODE
    while (true) {
        scanf("%d %d", &command.x, &command.y);
        if (!(board[command.x][command.y] == Empty)) {
            printf("This space has existed a chess,please choose other space!\n");
            continue;
        }
        break;
    }
#else
    scanf("%d %d", &command.x, &command.y);
#endif
    chessDown(command.x, command.y, enemyFlag);
    totalSteps++;
#if DEBUG_MODE
    printBoard();
#endif
}

bool checkEnd() {
    for (int x = 0; x < BOARD_SIZE; x++) {
        for (int y = 0; y < BOARD_SIZE; y++) {
            if (myBoard[x][y] >= LIVE_FIVE) {
                printf("Game over,you lose!\n");
                fflush(stdout);
                return true;
            }
            else if (enemyBoard[x][y] >= LIVE_FIVE) {
                printf("Game over,you win!\n");
                fflush(stdout);
                return true;
            }
        }
    }
    return false;
}

/*
 * Function Name:   main
 * Function:        main function
 * Return Value:    0
 */
int main() {
    char tag[10] = { 0 };
#ifdef DEBUG_MODE
    printf("Input “START 1/2” to start the game,“START 2” you go first ,“START Q” AI go first\n");
    fflush(stdout);
    printf("Input “ x y ” to make your chess down\n");
    fflush(stdout);
    printf("You can stop the game by yourself,please input “END” to stop the game\n");
    printf("Now let's enjoy the game!\n");
    fflush(stdout);
    while (true) {
        memset(tag, 0, sizeof(tag));
        scanf("%s", tag);
        if (strcmp(tag, "START") == 0) {
            start();
            printBoard();
            break;
        }
        if (strcmp(tag, "END") == 0) {
            return 0;
        }
        printf("Input “START 1 or 2” to start the game,“START 1” you go first ,“START 2” AI go first\n");
        fflush(stdout);
    }
  
    if (myFlag == Black) {
        while (true) {
            turn();
            if (checkEnd()) {
                system("pause");
                return 0;
            }
                
            printf("Wait for your step...\n");
            place();
            if (checkEnd()) {
                system("pause");
                return 0;
            }
            if (strcmp(tag, "END") == 0) {
                return 0;
            }
        }
    }
    else if (myFlag == White) {
        while (true) {
            printf("Wait for your step...\n");
            place();
            if (checkEnd()) {
                system("pause");
                return 0;
            }
            turn();
            if (checkEnd()) {
                system("pause");
                return 0;
            }
            if (strcmp(tag, "END") == 0) {
                return 0;
            }
        }
    }



#else
    while (true) {
        memset(tag, 0, sizeof(tag));
        scanf("%s", tag);
        if (strcmp(tag, "START") == 0) {
            start();
        }
        else if (strcmp(tag, "PLACE") == 0) {
            place();
        }
        else if (strcmp(tag, "TURN") == 0) {

#if DEBUG_MODE
            clock_t startTime = clock();
#endif // DEBUG_MODE
            turn();
#if DEBUG_MODE
            printf("DEBUG [Time = %ldms]\n", clock() - startTime);
            fflush(stdout);
#endif // DEBUG_MODE
        }
        else if (strcmp(tag, "END") == 0) {
            int status;
            scanf("%d", &status);
            return 0;
        }
    }
#endif
}

