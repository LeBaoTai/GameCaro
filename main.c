#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_SIZE 15

const char HORZ = 196;
const char VERT = 179;
const char TL   = 218;
const char TM   = 194;
const char TR   = 191;
const char BL   = 192;
const char BM   = 193;
const char BR   = 217;
const int numW  = 3;             // Width for writing out an integer
const int charW = 1;             // Width for writing out a character
const int numPerLine = 15;
const char VERT_START = 195;
const char VERT_END = 180;
const char VERT_MID = 197;
const char* inputCommand = "Previous move/Next move/Stop [p/n/s]: ";
const char* endOfHistory = "This is the end of the match.\nPrevious move/Next move/Stop [p/n/s]: ";
const char* startOfGame = "This is the start of the match.\nPrevious move/Next move/Stop [p/n/s]: ";
const char* invalidInput = "Illegal input, please try again: ";

enum Stone{NA, X, O};

struct Move {
    int row;
    int col;
    enum Stone stone;
} newMove;

static char* lineString( char left, char mid, char right, char horz, int wcell, int ncell ) {
    static char result[100];
    strcpy(result, "");
    char cell[10];
    for(int i = 0; i < wcell; i++){
        cell[i] = horz;
    }
    cell[wcell] = '\0';
    strncat(result,&left,1);
    char cellMid[20];
    strcpy(cellMid, cell);
    strncat(cellMid, &mid,1);
    for ( int i = 0; i < ncell - 1; i++ )
        strcat(result, cellMid);
    char cellRight[20];
    strcpy(cellRight, cell);
    strncat(cellRight, &right,1);
    strcat(result, cellRight);
    return result;
}

void displayBoard(enum Stone arr[][15], int size) {
    system("cls");
    //UPPERLINE
    printf("   ");
    for(int i = 0; i < size; i++) {
        printf("  %c ", (char)(i + 'a'));
    }
    printf("\n");
    printf("   %s\n", lineString( TL, TM, TR, HORZ, 3, numPerLine ));

    //MIDDLE
    for(int i = 0; i < size; i++) {
        printf("%2d %c", size - i, VERT);
        for(int j = 0; j < size; j++) {
            if(arr[i][j] == NA) printf("   %c", VERT);
            if(arr[i][j] == X) printf(" X %c", VERT);
            if(arr[i][j] == O) printf(" O %c", VERT);
        }
        printf("\n");
        if(i != size - 1) printf("   %s\n", lineString( VERT_START, VERT_MID, VERT_END, HORZ, 3, numPerLine ));
    }

    //UNDERLINE
    printf("   %s\n", lineString( BL, BM, BR, HORZ, 3, numPerLine ));
}

void displayBoardSimple(enum Stone arr[][15], int size) {
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++) {
            printf("%d", arr[i][j]);
        }
    }
    printf("\n");
}

bool makeMove(enum Stone board[][15], int size, char* playerMove, bool isFirstPlayerTurn) {
    //BEGIN TODO
    int rowNum;
    int columnNum;
    bool checkMove = false;

    // kiem tra chuoi nhap co dung khong
    if (strlen(playerMove) == 2 ) {
        columnNum = (int)playerMove[1] - 97;
        rowNum = 63 - (int)playerMove[0];
    }
    else if (strlen(playerMove) == 3) {
        int rowNum1 = (int)playerMove[0];
        int rowNum2 = (int)playerMove[1];
        rowNum = 102 - (rowNum1 + rowNum2);
        columnNum = (int)playerMove[2] - 97;
    }
    else return false;

    // kiem tra chuoi nhap co nam trong ban co kh
    if ((rowNum < size && rowNum >= 0) && (columnNum < size && columnNum >=0)){
        if (board[rowNum][columnNum] == NA) {
            board[rowNum][columnNum] = (isFirstPlayerTurn ? X : O);

            // lay vi tri hien tao de check chien thang
            newMove.col = columnNum;
            newMove.row = rowNum;
            newMove.stone = board[rowNum][columnNum];
        }
        else return false;
        return true;
    }
    else {
        return false;
    }
    //END TODO
}

bool hasWon(enum Stone board[][15], int size, bool isFirstPlayerTurn) {
    //BEGIN TODO
    bool result = false;

    int count = 0;
    int left = 0, right = 0, above = 0, below = 0;
    int rightAbove = 0, rightBelow = 0, leftAbove = 0, leftBelow = 0;

    enum Stone ortherPlayerStone = (!isFirstPlayerTurn ? X : O);

    // kiem tra tren duoi
    for (int i = newMove.row - 1; i >= 0; i--) {
        if (board[i][newMove.col] == newMove.stone) {
            above++;
            count++;
        }
        else break;
    }
    for (int j = newMove.row + 1; j < size; j++) {
        if (board[j][newMove.col] == newMove.stone) {
            below++;
            count++;
        }
        else break;
    }
    
    // kiem tra trai phai 
    for (int i = newMove.col - 1; i >=0 ; i--) {
        if (board[newMove.row][i] == newMove.stone) {
            left++;
            count++;
        }
        else break;
    }
    for (int i = newMove.col + 1; i < size ; i++) {
        if (board[newMove.row][i] == newMove.stone) {
            right++;
            count++;
        }
        else break;
    }

    result = count >= 4 ? true : false;
    if (result) {
        if (left + right == count || below + above == count) {
            if ((board[newMove.row][newMove.col - left - 1] == ortherPlayerStone &&
                board[newMove.row][newMove.col + right + 1] == ortherPlayerStone) ||

                (board[newMove.row + below + 1][newMove.col] == ortherPlayerStone &&
                board[newMove.row - above - 1][newMove.col] == ortherPlayerStone )
                )
                result = false;       
        }
    }
    if (result)
        return result;
    else count = 0;

    //kiem tra cheo
    // cheo phai tren
    for (int i = newMove.row - 1, j = newMove.col + 1; i >= 0 && j < size; i--, j++) {
        if (board[i][j] == newMove.stone) {
            rightAbove++;
            count++;
        }
        else break;
    }

    // cheo trai tren
    for (int i = newMove.row - 1, j = newMove.col - 1; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j] == newMove.stone) {
            leftAbove++;
            count++;
        }
        else break;
    }

    // cheo phai duoi
    for (int i = newMove.row + 1, j = newMove.col + 1; i < size && j < size; i++, j++) {
        if (board[i][j] == newMove.stone) {
            rightBelow++;
            count++;
        }
        else break;
    }

    //cheo trai duoi
    for (int i = newMove.row + 1, j = newMove.col - 1; i < size && j >= 0; i++, j--) {
        if (board[i][j] == newMove.stone) {
            leftBelow++;
            count++;
        }
        else break;
    }

    // kiem tran chan 2 dau
    result = count >= 4 ? true : false;
    if (result) {
        if (leftAbove + rightBelow == count || leftBelow + rightAbove == count) {
            if ((board[newMove.row - leftAbove - 1][newMove.col - leftAbove - 1] == ortherPlayerStone &&
                board[newMove.row + rightAbove + 1][newMove.col + rightBelow + 1] == ortherPlayerStone) ||

                (board[newMove.row + leftBelow + 1][newMove.col - leftBelow - 1] == ortherPlayerStone &&
                board[newMove.row - rightAbove - 1][newMove.col + rightAbove + 1] == ortherPlayerStone )
                )
                result = false;       
        }
    }

    return result;
    //END TODO
}

void displayHistory(char* history, int numOfMoves) {
    //BEGIN TODO
    enum Stone game[15][15];
    for(int i = 0; i < MAX_SIZE; i++) {
        for(int j = 0; j < MAX_SIZE; j++) {
            game[i][j] = NA;
        }
    }
    
    int count = 0, index = 0, k = 0;
    char move[30][10];
    char t[10];
    char test[10];

    bool fistMove = true;
    
    while (history[index] != '\0'){
		if (history[index] >= 'a' && history[index] <= 'o') {
			int columnNum, rowNum;
			if (index - count == 1 || index - count == 2) {
				if (history[index - 2] == 49) {
                    int j = 0;
                    for (int i = count; i <= index; i++, j++) {
                        test[j] = history[i];
                    }
                    test[j++] = '\0';
                    // printf("%d %d: ", index, count);
                    // printf("%s\n", test);
                    strcat(move[k++], test);
				}
				else {
                    int j = 0;
                    for (int i = count + 1; i <= index; i++, j++) {
                        test[j] = history[i];
                    }
                    test[j++] = '\0';
                    // printf("%d %d: ", index, count);
                    // printf("%s\n", test);
                    strcat(move[k++], test);
				}
			}
			else if (index - count == 3) {
                int j = 0;
                for (int i = count + 1; i <= index; i++, j++) {
                    test[j] = history[i];
                }
                // printf("%d %d: ", index, count);
                // printf("%s\n", test);
                strcat(move[k++], test);
			}
			count = index;
		}
		index++;
	}

    for (int i = 0; i < k;) {
        char choice;
        printf("Previous move/Next move/Stop [p/n/s]: ");
        fflush(stdin);
        scanf("%c", &choice);
        if (choice == 'p') {
            displayBoard (game, MAX_SIZE);
            continue;
        } 
        else if (choice == 'n') {
            int columnNum, rowNum;
            if (strlen(move[i]) == 2 ) {
                columnNum = (int)move[i][1] - 97;
                rowNum = 63 - (int)move[i][0];
            }
            else if (strlen(move[i]) == 3) {
                int rowNum1 = (int)move[i][0];
                int rowNum2 = (int)move[i][1];
                rowNum = 102 - (rowNum1 + rowNum2);
                columnNum = (int)move[i][2] - 97;
            }

            game[rowNum][columnNum] = fistMove ? X : O;
            fistMove = !fistMove;
            i++;

            displayBoard(game, MAX_SIZE);
        }
        else if (choice == 's') break;
        else {
            printf("Invalid input!!! Try again\n");
        }

        // printf("%d %d\n", rowNum, columnNum);
    }

    printf("End of history\n");

    //END TODO
}

void startGame() {
    enum Stone game[15][15];
    for(int i = 0; i < MAX_SIZE; i++) {
        for(int j = 0; j < MAX_SIZE; j++) {
            game[i][j] = NA;
        }
    }
    displayBoard(game, MAX_SIZE);
    char playerMove[50];
    bool player1Turn = true;
    printf("Player 1 turn: ");
    while(true) {
        scanf("%s", playerMove);
        if(strcmp(playerMove,"ff") == 0) {
            printf("%s", ((player1Turn) ? "Player 2 won " : "Player 1 won "));
            break;
        }
        else if(makeMove(game, MAX_SIZE, playerMove, player1Turn)){
            if(hasWon(game, MAX_SIZE, player1Turn)) {
                displayBoard(game, MAX_SIZE);
                printf("%s", ((player1Turn) ? "Player 1 won " : "Player 2 won "));
                return;
            }
            player1Turn = !player1Turn;
            displayBoard(game, MAX_SIZE);
            printf("%s", ((player1Turn) ? "Player 1 turn: " : "Player 2 turn: "));
        } 
        else {
            printf("Illegal move, please try again: ");
        }
    }
}

int main()
{
    printf("Welcome to Gomoku!\n");
    printf("1. Play game\n");
    printf("2. History\n");
    printf("3. Exit\n");
    printf("Please select mode [1/2/3]: ");
    int mode;
    while(true){
        scanf("%d", &mode);
        if(mode == 1) {
            startGame();
            system("pause");
            return 0;
        } 
        else if (mode == 2) {
            int numOfMoves;
            printf("Please enter number of moves: ");
            scanf("%d", &numOfMoves);
            char history[700];
            printf("Please enter history: ");
            scanf("%s", history);
            displayHistory(history, numOfMoves);
            system("pause");
            return 0;
        } 
        else if (mode == 3) {
            return 0;
        }   
        else {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            printf("Invalid mode, please try again: ");
            system("pause");
        }
    }

    return 0;
}