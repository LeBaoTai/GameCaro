#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void func(char* history, int numbOfHistory) {
    char move[30][10];
    char t[10];
    char test[10];
    // strcat(move[0], strncpy(t, history, 3));
    
    // test[0] = history[0];
    // test[1] = history[1];
    // strcat(move[1], strncpy(t, test, 3));

    // printf("%s\n", move[0]);
    // printf("%s\n", move[1]);

    int index = 0, count = 0, k = 0;

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

    for (int i = 0; i < k; i++) {
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

        printf("%d %d\n", rowNum, columnNum);
    }
}

int main() {

    char move[700];

    scanf("%s", move);
    func(move, 15);


    system("pause");
    return 0;
}