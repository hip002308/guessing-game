#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <wctype.h>

// ���͉͂��i����
#define INPUT_BASE (2)
// ����l�̍ŏ��l�E�ő�l
#define ANSWER_MIN (0)
#define ANSWER_MAX (11111111)
// COUNT_DIGITS�}�N���̈������ɐ��l�ɒu�������邽�߂�STRING�}�N�������܂���
#define STRING(str) (#str)
// �����𕶎���ɂ��Ă��̌�����Ԃ�
#define COUNT_DIGITS(value) (_countof(STRING(value)) - 1)
// �����̑�������Ԃ�
#define DIGITS_MAX ((((-ANSWER_MIN) < ANSWER_MAX) ? COUNT_DIGITS(ANSWER_MAX) : (COUNT_DIGITS(ANSWER_MIN) - 1)) - 2)
// ����(DIGIT_MAX) + ����(1) + �k������(1)
#define INPUT_ARRAY_SIZE (DIGITS_MAX + 2)
// �����𐔒l�ɂ���
#define CTOI(character) (character - '0')
// �������ۂ���\��
#define DIGIT (1)
#define NOT_DIGIT (0)
// INPUT_BASE�i�����ۂ���\��
#define CORRECT_BASE (1)
#define INCORRECT_BASE (0)
// �v���C���[�̓��͂����������ۂ���\��
#define APPROPRIATE_INPUT (1)
#define INAPPROPRIATE_INPUT (0)

// �Q�[�������i�[����
typedef struct {
  // �v���C���[�̓���
  char player_input[INPUT_ARRAY_SIZE];
  // �v���C���[�̉�
  int player_answer;
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

// �����l�Ȃ�DIGIT�A����ȊO��NOT_DIGIT��Ԃ�
int isDigits(char str[]) {
  int index;
  int str_length = (int)strlen(str);
  int char_count = 0;

  for (index = 0; index < str_length; index++) {
    if (!iswdigit(str[index])) {
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
    int value = CTOI(str[index]);
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
void AnswerByPlayer(GAME_INFO* info) {
  info->player_answer = ANSWER_MIN - 1;
  int is_appropriate;

  do {
    printf("%d����%d�܂ł̐�����%d�i���œ��͂��Ă��������F", ANSWER_MIN, ANSWER_MAX, INPUT_BASE);
    // ��3�����̃o�b�t�@�T�C�Y�ɁA�z��̍ő啶������Ԃ�_countof�}�N�����g�p
    scanf_s("%s", info->player_input, (unsigned)_countof(info->player_input));
    ThroughRestBuffer();
    info->player_answer = atoi(info->player_input);
    is_appropriate = isAppropriateInput(info->player_input);
    // ���͂��K�؂łȂ����A�K�؂��͈͊O�̐��l(�ǂ�Ȑi���ł�10�i���ŕ]��)�ł���� ���[�v���s
  } while ((is_appropriate == INAPPROPRIATE_INPUT) || (info->player_answer < ANSWER_MIN) || (info->player_answer > ANSWER_MAX));
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

// INPUT_BASE�i���̕������10�i���ɂ��ĕԂ�
int CharTo10Base(char str[]) {
  int index;
  int str_length = (int)strlen(str);
  int value_10 = 0;

  for (index = 0; index < str_length; index++) {
    value_10 *= INPUT_BASE;
    value_10 += CTOI(str[index]);
  }

  return value_10;
}

// INPUT_BASE�i����10�i���ɂ��ĕԂ�
int IntTo10Base(int value_n_base) {
  char str_n_base[INPUT_ARRAY_SIZE];
  _snprintf_s(str_n_base, INPUT_ARRAY_SIZE, INPUT_ARRAY_SIZE - 1, "%d", value_n_base);
  int value_10 = CharTo10Base(str_n_base);
  return value_10;
}

int main(void) {
  // �Q�[�����
  GAME_INFO info = {
    '\0'
  };
  // �v���C���[�̉𓚉�
  int answer_count = 0;
  // �}�N���ő�l�iINPUT_BASE�i���\�L�j��int�^�ɂ���
  int const input_max = IntTo10Base(ANSWER_MAX);
  // �}�N���ŏ��l�iINPUT_BASE�i���\�L�j��int�^�ɂ���
  int const input_min = IntTo10Base(ANSWER_MIN);

  // �����̐��l�𐶐�
  srand((unsigned)time(NULL));
  info.correct_answer = (rand() % (input_max - input_min + 1)) + input_min;

  printf("�����ăQ�[���ł��B\n");
  do {
    // �v���C���[����
    AnswerByPlayer(&info);
    info.player_answer = CharTo10Base(info.player_input);
    answer_count++;

    // ����\��
    int answer_diff = info.player_answer - info.correct_answer;
    printf("���Ȃ��̉�\"%s\"��", info.player_input);
    PrintJudgeMessage(answer_diff);
    printf("\n\n");
  } while (info.player_answer != info.correct_answer);

  printf("���Ȃ���%d��ڂŐ������܂����B\n", answer_count);

  return 0;
}