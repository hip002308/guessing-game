#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
	char input[10] = { '\0' };
	int answer_player;
	int correct_answer;
	int count = 0;

	// �����̐��l�������_���Őݒ肷��
	srand((unsigned) time (NULL));
	correct_answer = rand() % 100 + 1;

	do {
		printf("1����100�܂ł̐�������͂��Ă��������B�F");
		scanf_s("%9s", input, (unsigned) (sizeof(input) / sizeof(input[0])));
		answer_player = atoi(input);
		if ((answer_player < 1) || (answer_player > 100)) {
			printf("\a�y���Ӂz1�ȏ�100�ȉ��̐�������͂��Ă��������B\n");
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

	printf("���Ȃ���%d��ڂŐ������܂���", count);

	return 0;
}