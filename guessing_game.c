#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ����l�̍ŏ��l�E�ő�l
#define ANSWER_MIN (1)
#define ANSWER_MAX (100)

#define TRUE 1

// ���̓o�b�t�@��ǂݔ�΂�
void ThroughRestBuffer() {
  char buffer = getchar();
  while (buffer != '\n') {
    buffer = getchar();
  }
}

// �����̕�����𐔒l�ɂ��ĕԂ�(�擪��������̏ꍇ�AANSWER_MIN - 1��Ԃ�)
int AtoiWithException(char str[]) {
  int ret = atoi(str);
  if (ret == 0 && str[0] != '0') {
    ret = ANSWER_MIN - 1;
  }
  return ret;
}

// �����̓��͂����߂�
void AnswerByPlayer(int* player_answer) {
  char player_answer_input[10] = {'\0'};
  while (TRUE) {
    printf("%d����%d�܂ł̐�������͂��Ă��������F", ANSWER_MIN, ANSWER_MAX);
    // �o�b�t�@�T�C�Y�ɍő啶������Ԃ�_countof�}�N�����g�p
    scanf_s("%s", player_answer_input, (unsigned)_countof(player_answer_input));
    ThroughRestBuffer();
    *player_answer = AtoiWithException(player_answer_input);
    if ((*player_answer >= ANSWER_MIN) && (*player_answer <= ANSWER_MAX)) {
      break;
    }
    printf("\a�y���Ӂz%d�ȏ�%d�ȉ��̐�������͂��Ă��������B\n\n", ANSWER_MIN, ANSWER_MAX);
  }
}

// ���茋�ʂ�\���i���������Ȃ�Big�A���Ȃ�Small�A0�Ȃ�Bingo�j
void PrintCheckResult(int diff) {
  if (diff > 0) {
    printf("Big\n");
  }
  else if (diff < 0) {
    printf("Small\n");
  }
  else {
    printf("Bingo!\n");
  }
  printf("\n");
}

// ���딻�������i�߂�l�F0�͐����A0�ȊO�͕s�����j
int CheckAnswer(int player_answer, int correct_answer) {
  int ret = player_answer - correct_answer;
  PrintCheckResult(ret);
  return ret;
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
  do {
    // �v���C���[����
    AnswerByPlayer(&player_answer);
    answer_count++;

    // ���딻��E�\��
    printf("���Ȃ��̉�\"%d\"��", player_answer);
  } while (CheckAnswer(player_answer, correct_answer));

  printf("���Ȃ���%d��ڂŐ������܂����B\n", answer_count);

  return 0;
}