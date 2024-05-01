#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <wctype.h>

// ����l�̍ŏ��l�E�ő�l
#define ANSWER_MIN (1)
#define ANSWER_MAX (100)
// COUNT_DIGITS�}�N���̈������ɐ��l�ɒu�������邽�߂�STRING�}�N�������܂���
#define STRING(str) (#str)
// �����𕶎���ɂ��Ă��̌�����Ԃ�
#define COUNT_DIGITS(value) (_countof(STRING(value)) - 1)
// �����̑�������Ԃ�
#define DIGITS_MAX ((((-ANSWER_MIN) < ANSWER_MAX) ? COUNT_DIGITS(ANSWER_MAX) : (COUNT_DIGITS(ANSWER_MIN) - 1)) - 2)
// ����(DIGIT_MAX) + ����(1) + �k������(1)
#define INPUT_ARRAY_SIZE (DIGITS_MAX + 2)
// �������ۂ���\��
#define DIGIT (1)
#define NOT_DIGIT (0)

// �c��̓��̓o�b�t�@��ǂݔ�΂�
void ThroughRestBuffer() {
  char buffer = getchar();
  while (buffer != '\n') {
    buffer = getchar();
  }
}

// �����l�Ȃ�DIGIT�A����ȊO��NOT_DIGIT��Ԃ�
int isDigits(char str[]) {
  int idx;
  int str_length = (int)strlen(str);
  int char_count = 0;

  for (idx = 0; idx < str_length; idx++) {
    if (!iswdigit(str[idx])) {
      char_count++;
    }
  }
  // ������0�Ȃ�ΐ����łȂ��A�擪�������Ȃ琮���̉\��
  if ((str_length == 0) || (str[0] == '-') || (str[0] == '+')) {
    char_count--;
  }

  if (char_count) {
    return NOT_DIGIT;
  }
  return DIGIT;
}

// �����̓��͂����߂�
int AnswerByPlayer() {
  char answer_input[INPUT_ARRAY_SIZE] = {
    '\0'
  };
  int player_answer = ANSWER_MIN - 1;
  int is_digit;

  do {
    printf("%d����%d�܂ł̐�������͂��Ă��������F", ANSWER_MIN, ANSWER_MAX);
    // ��3�����̃o�b�t�@�T�C�Y�ɁA�z��̍ő啶������Ԃ�_countof�}�N�����g�p
    scanf_s("%s", answer_input, (unsigned)_countof(answer_input));
    ThroughRestBuffer();
    player_answer = atoi(answer_input);
    is_digit = isDigits(answer_input);
    // �����łȂ����A�������͈͊O�̐��l�ł���� true
  } while ((is_digit == NOT_DIGIT) || (player_answer < ANSWER_MIN) || (player_answer > ANSWER_MAX));

  return player_answer;
}

// ���胁�b�Z�[�W��\������
void PrintJudgeMessage(int diff) {
  static char const * const judge_messages[] = {
    "Small",
    "Bingo!",
    "Big"
  };
  // ����(-1 or 0 or +1)�Ɣz��̗v�f��Ή��t����
  int idx = (diff > 0) - (diff < 0) + 1;
  printf("%s", judge_messages[idx]);
}

int main(void) {
  // �v���C���[�̉�
  int player_answer;
  // �Q�[���̐���
  int correct_answer;
  // �v���C���[�̉𓚉�
  int answer_count = 0;

  // �����̐��l�𐶐�
  srand((unsigned)time(NULL));
  correct_answer = (rand() % (ANSWER_MAX - ANSWER_MIN + 1)) + ANSWER_MIN;

  printf("�����ăQ�[���ł��B\n");
  do {
    // �v���C���[����
    player_answer = AnswerByPlayer();
    answer_count++;

    // ����\��
    int answer_diff = player_answer - correct_answer;
    printf("���Ȃ��̉�\"%d\"��", player_answer);
    PrintJudgeMessage(answer_diff);
    printf("\n\n");
  } while (player_answer != correct_answer);

  printf("���Ȃ���%d��ڂŐ������܂����B\n", answer_count);

  return 0;
}