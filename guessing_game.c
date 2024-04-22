#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
	char input[10] = { '\0' };
	int answer_player;
	int correct_answer;
	int count = 0;

	// 答えの数値をランダムで設定する
	srand((unsigned) time (NULL));
	correct_answer = rand() % 100 + 1;

	do {
		printf("1から100までの数字を入力してください。：");
		scanf_s("%9s", input, (unsigned) (sizeof(input) / sizeof(input[0])));
		answer_player = atoi(input);
		if ((answer_player < 1) || (answer_player > 100)) {
			printf("\a【注意】1以上100以下の数字を入力してください。\n");
			continue;
		}

		if (answer_player < correct_answer) {
			puts("Small");
		}
		else if (answer_player > correct_answer) {
			puts("Big");
		}
		else {
			puts("Bingo!");
		}
		count++;
	} while (answer_player != correct_answer);

	printf("あなたは%d回目で正解しました", count);

	return 0;
}