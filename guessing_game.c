#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ����l�̍ŏ��l�E�ő�l
#define ANSWER_MIN (1)
#define ANSWER_MAX (100)

int main(void) {
  // �v���C���[�̓��͕ێ�
  char input[10] = {'\0'};
  // �v���C���[�̉�
  int player_answer;
  // �Q�[���̐���
  int correct_answer;
  // �v���C���[�̉𓚉�
  int count = 0;

  // �����̐��l�𐶐�
  srand((unsigned) time(NULL));
  correct_answer = rand() % ANSWER_MAX + ANSWER_MIN;

  do {
    // �v���C���[����
    printf("1����100�܂ł̐�������͂��Ă��������F");
    scanf_s("%9s", input, (unsigned) (sizeof(input) / sizeof(input[0])));
    player_answer = atoi(input);
    if ((player_answer < ANSWER_MIN) || (player_answer > ANSWER_MAX)) {
      printf("\a�y���Ӂz1�ȏ�100�ȉ��̐�������͂��Ă��������B\n\n");
      continue;
    }
    count++;

    // ���딻��E�\��
    printf("���Ȃ��̉�\"%d\"��", player_answer);
    if (player_answer < correct_answer) {
      puts("Small");
    } else if (player_answer > correct_answer) {
      puts("Big");
    } else {
      puts("Bingo!");
      printf("���Ȃ���%d��ڂŐ������܂����B", count);
    }
    printf("\n");
  } while (player_answer != correct_answer);

  return 0;
}