#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void displayHistory(char* history, int numOfMoves) {
    //BEGIN TODO
	int index = 0, count = 0;
	char move[20][5], k = 0;



	// while (history[index] != '\0'){
	// 	// printf("%d\n", index);
	// 	if (history[index] >= 'a' && history[index] <= 'o') {
	// 		strncpy(move[k][5], history[index], 2);
	// 		k++;
	// 		int columnNum, rowNum;
	// 		if (index - count == 1 || index - count == 2) {
	// 			if (history[index - 2] == 49) {
	// 				int rowNum1 = (int)history[index-2];
	// 				int rowNum2 = (int)history[index-1];
	// 				rowNum = 102 - (rowNum1 + rowNum2);
	// 				columnNum = (int)history[index] - 97;
	// 			}
	// 			else {
	// 				columnNum = (int)history[index] - 97;
	// 				rowNum = 63 - (int)history[index - 1];
	// 			}
	// 		}
	// 		else if (index - count == 3) {
	// 			int rowNum1 = (int)history[index-2];
	// 			int rowNum2 = (int)history[index-1];
	// 			rowNum = 102 - (rowNum1 + rowNum2);
	// 			columnNum = (int)history[index] - 97;
	// 		}
			
	// 		printf("%d %d\n", rowNum, columnNum);
	// 		count = index;
	// 	}
	// 	index++;
	// }
    

	// for (int i = 0; i < k; i++) {
	// 	printf("%s\n", move[i][5]);
	// }
    //END TODO
}

int main() {
	// int numbersOfHistory;
	// char history[700];

	// // scanf("%d", &numbersOfHistory);
	// scanf("%s", history);
	// displayHistory(history, numbersOfHistory);

	

	system("pause");
	return 0;
}