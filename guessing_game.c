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
  int value_10 = 0;

  for (index = 0; index < str_length; index++) {
    value_10 *= INPUT_BASE;
    value_10 += CharToInt(str[index]);
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
void AnswerByPlayer(GAME_INFO* info) {
  const int answer_max = CharTo10Base(ANSWER_MAX);
  const int answer_min = CharTo10Base(ANSWER_MIN);
  int is_appropriate;

  do {
    printf("%s����%s�܂ł̐�����%d�i���œ��͂��Ă��������F", ANSWER_MIN, ANSWER_MAX, INPUT_BASE);
    // ��3�����̃o�b�t�@�T�C�Y�ɁA�z��̍ő啶������Ԃ�_countof�}�N�����g�p
    scanf_s("%s", info->player_input, (unsigned)_countof(info->player_input));
    ThroughRestBuffer();
    info->player_answer = CharTo10Base(info->player_input);
    is_appropriate = isAppropriateInput(info->player_input);
    // ���͂��K�؂łȂ����A�K�؂��͈͊O�̐��l�ł���� ���[�v���s
  } while ((is_appropriate == INAPPROPRIATE_INPUT) || (info->player_answer < answer_min) || (info->player_answer > answer_max));
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
  // �Q�[�����
  GAME_INFO info = {
    '\0'
  };
  // �v���C���[�̉𓚉�
  int answer_count = 0;
  // ����l�̍ő�l�E�ŏ��l
  const int answer_max = CharTo10Base(ANSWER_MAX);
  const int answer_min = CharTo10Base(ANSWER_MIN);

  // �����̐��l�𐶐�
  srand((unsigned)time(NULL));
  info.correct_answer = (rand() % (answer_max - answer_min + 1)) + answer_min;

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