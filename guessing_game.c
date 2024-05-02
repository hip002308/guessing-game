#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <wctype.h>

// ���͉͂��i����
#define INPUT_BASE (2)
// ����l�̍ŏ��l�E�ő�l
#define ANSWER_MIN ("0")
#define ANSWER_MAX ("11111111")
// �����̌���(�������܂ޏꍇ������)��Ԃ�
#define COUNT_DIGITS(val_str) (_countof(val_str) - 1)
// �����̑�������Ԃ�
#define DIGITS_MAX ((COUNT_DIGITS(ANSWER_MIN) < COUNT_DIGITS(ANSWER_MAX)) ? COUNT_DIGITS(ANSWER_MAX) : COUNT_DIGITS(ANSWER_MIN))
// ����(DIGIT_MAX) + ����(1) + �k������(1)
#define INPUT_ARRAY_SIZE (DIGITS_MAX + 2)
// �������ۂ���\��
#define DIGIT (1)
#define NOT_DIGIT (-1)
// INPUT_BASE�i�����ۂ���\��
#define CORRECT_BASE (1)
#define INCORRECT_BASE (0)
// �v���C���[�̓��͂����������ۂ���\��
#define APPROPRIATE_INPUT (1)
#define INAPPROPRIATE_INPUT (0)

// �Q�[�������i�[����
typedef struct {
  // ����l�̍ŏ��l
  int answer_min;
  // ����l�̍ő�l
  int answer_max;
  // �Q�[���̐���
  int correct_answer;
} GAME_INFO;

// �c��̓��̓o�b�t�@��ǂݔ�΂�
void ThroughRestBuffer() {
  char buffer = getchar();
  while (buffer != '\n') {
    buffer = getchar();
  }
}

// ����(0~9a~zA~Z)�𐔒l(0~35)�ɕϊ�
int CharToInt(char character) {
  static char alpha[] = "0123456789abcdefghijklmnopqrstuvwxyz";
  char search[] = {
    (char)towlower(character),
    '\0'
  };
  char* pointer = strstr(alpha, search);
  if (pointer == NULL) {
    return NOT_DIGIT;
  }
  else {
    int value = (int)(pointer - alpha);
    return value;
  }
}

// INPUT_BASE�i���̕������10�i���ɂ��ĕԂ�
int CharTo10Base(char str[]) {
  int index;
  int str_length = (int)strlen(str);
  // ���������邩��ǂ�
  int value_10 = CharToInt(str[0]);
  if (value_10 == NOT_DIGIT) {
    value_10 = 0;
  }

  for (index = 1; index < str_length; index++) {
    value_10 *= INPUT_BASE;
    value_10 += CharToInt(str[index]);
  }

  if (str[0] == '-') {
    value_10 = -value_10;
  }

  return value_10;
}

// �����l�Ȃ�DIGIT�A����ȊO��NOT_DIGIT��Ԃ�
int isDigits(char str[]) {
  int index;
  int str_length = (int)strlen(str);
  int char_count = 0;

  for (index = 0; index < str_length; index++) {
    int value = CharToInt(str[index]);
    if (value == NOT_DIGIT) {
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

// INPUT_BASE�i���ɓK�����������񂩂ǂ���
int isCorrectBase(char str[]) {
  int index;
  int str_length = (int)strlen(str);

  for (index = 0; index < str_length; index++) {
    int value = CharToInt(str[index]);
    if (INPUT_BASE <= value) {
      return INCORRECT_BASE;
    }
  }

  return CORRECT_BASE;
}

// ���͂��w���ʂ�s���Ă��邩
int isAppropriateInput(char str[]) {
  int is_digit = isDigits(str);
  if (is_digit == NOT_DIGIT) {
    return INAPPROPRIATE_INPUT;
  }
  int is_correct_base = isCorrectBase(str);
  if (is_correct_base == INCORRECT_BASE) {
    return INAPPROPRIATE_INPUT;
  }
  return APPROPRIATE_INPUT;
}

// �����̓��͂����߂�
int AnswerByPlayer(GAME_INFO const * const info) {
  char player_input[INPUT_ARRAY_SIZE];
  int player_answer;
  int is_appropriate;

  do {
    printf("%d����%d�܂ł̐�����%d�i���œ��͂��Ă��������F", info->answer_min, info->answer_max, INPUT_BASE);
    // ��3�����̃o�b�t�@�T�C�Y�ɁA�z��̍ő啶������Ԃ�_countof�}�N�����g�p
    scanf_s("%s", player_input, (unsigned)_countof(player_input));
    ThroughRestBuffer();
    player_answer = CharTo10Base(player_input);
    is_appropriate = isAppropriateInput(player_input);
    // ���͂��K�؂łȂ����A�K�؂��͈͊O�̐��l�ł���� ���[�v���s
  } while ((is_appropriate == INAPPROPRIATE_INPUT) || (player_answer < info->answer_min) || (player_answer > info->answer_max));

  printf("���Ȃ��̉�\"%s\"�F", player_input);
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
  int index = (diff > 0) - (diff < 0) + 1;
  printf("%s", judge_messages[index]);
}

int main(void) {
  // �v���C���[�̉�
  int player_answer;
  // �v���C���[�̉𓚉�
  int answer_count = 0;
  // ����l�̍ŏ��l�E�ő�l
  int const answer_min = CharTo10Base(ANSWER_MIN);
  int const answer_max = CharTo10Base(ANSWER_MAX);

  // �����̐��l�𐶐�
  srand((unsigned)time(NULL));
  // �Q�[�������i�[
  GAME_INFO const info = {
    answer_min,
    answer_max,
    (rand() % (answer_max - answer_min + 1)) + answer_min
  };

  printf("�����ăQ�[���ł��B\n");
  do {
    // �v���C���[����
    player_answer = AnswerByPlayer(&info);
    answer_count++;

    // ����\��
    int answer_diff = player_answer - info.correct_answer;
    PrintJudgeMessage(answer_diff);
    printf("\n\n");
  } while (player_answer != info.correct_answer);

  printf("���Ȃ���%d��ڂŐ������܂����B\n", answer_count);

  return 0;
}