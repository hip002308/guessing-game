#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ����l�̍ŏ��l�E�ő�l
#define ANSWER_MIN (1)
#define ANSWER_MAX (100)

// �c��̓��̓o�b�t�@��ǂݔ�΂�
void ThroughRestBuffer() {
  char buffer = getchar();
  while (buffer != '\n') {
    buffer = getchar();
  }
}

// �����̕�����𐔒l�ɂ��ĕԂ�(�擪��������̏ꍇ�AANSWER_MIN - 1��Ԃ�)
int AtoiWithinRange(char str[]) {
  int ret = atoi(str);
  if (ret == 0 && str[0] != '0') {
    ret = ANSWER_MIN - 1;
  }
  return ret;
}

// �����̓��͂����߂�
int AnswerByPlayer() {
  char answer_input[10] = {'\0'};
  int player_answer;
  while (1) {
    printf("%d����%d�܂ł̐�������͂��Ă��������F", ANSWER_MIN, ANSWER_MAX);
    // ��3�����̃o�b�t�@�T�C�Y�ɁA�z��̍ő啶������Ԃ�_countof�}�N�����g�p
    scanf_s("%9s", answer_input, (unsigned)_countof(answer_input));
    ThroughRestBuffer();
    player_answer = AtoiWithinRange(answer_input);
    if ((player_answer >= ANSWER_MIN) && (player_answer <= ANSWER_MAX)) {
      break;
    }
    printf("\a�y���Ӂz%d�ȏ�%d�ȉ��̐�������͂��Ă��������B\n\n", ANSWER_MIN, ANSWER_MAX);
  }
  return player_answer;
}

// �����𐶐�����
int GenerateAnswer() {
  return (rand() % (ANSWER_MAX - ANSWER_MIN + 1)) + ANSWER_MIN;
}

int main(void) {
  // �v���C���[�̉�
  int player_answer;
  // �Q�[���̐���
  int correct_answer;
  // �v���C���[�̉𓚉�
  int answer_count = 0;

  // �����̐��l�𐶐�
  srand((unsigned) time(NULL));
  correct_answer = GenerateAnswer();

  printf("�����ăQ�[���ł��B\n");
  while (1) {
    // �v���C���[����
    player_answer = AnswerByPlayer();
    answer_count++;

    // ���딻��E�\��
    printf("���Ȃ��̉�\"%d\"��", player_answer);
    int diff = player_answer - correct_answer;
    if (diff > 0) {
      printf("Big\n");
    }
    else if (diff < 0) {
      printf("Small\n");
    }
    else {
      printf("Bingo!\n");
      printf("���Ȃ���%d��ڂŐ������܂����B\n", answer_count);
      break;
    }
    printf("\n");
  }

  return 0;
}