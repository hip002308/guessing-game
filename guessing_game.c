#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

// ����l�̍ŏ��l�E�ő�l�E�ő包���A�z��̌���
#define ANSWER_MIN (1)
#define ANSWER_MAX (100)
#define DIGITS_MAX (3)
#define INPUT_ARRAY_SIZE (DIGITS_MAX + 2)

// �c��̓��̓o�b�t�@��ǂݔ�΂�
void ThroughRestBuffer() {
  char buffer = getchar();
  while (buffer != '\n') {
    buffer = getchar();
  }
}

// 0��Ԃ��ΐ����l�A����ȊO�͕�����Ƃ݂Ȃ�
int isString(char str[]) {
  int idx;
  int str_length = (int)strlen(str);
  int char_count = 0;

  for (idx = 0; idx < str_length; idx++) {
    if (!isdigit(str[idx])) {
      char_count++;
    }
  }
  // �擪�������Ȃ琮���̉\���A�k�������Ȃ當����
  if ((str[0] == '-') || (str[0] == '+') || (!str[0])) {
    char_count--;
  }

  return char_count;
}

// �����̓��͂����߂�
int AnswerByPlayer() {
  char answer_input[INPUT_ARRAY_SIZE];
  int player_answer;

  do {
    printf("%d����%d�܂ł̐�������͂��Ă��������F", ANSWER_MIN, ANSWER_MAX);
    // ��3�����̃o�b�t�@�T�C�Y�ɁA�z��̍ő啶������Ԃ�_countof�}�N�����g�p
    scanf_s("%s", answer_input, (unsigned)_countof(answer_input));
    ThroughRestBuffer();
    // �z��v�f���𒴂�����͂��A�����ȊO�̓��͂����ꂽ�ꍇ
    if (isString(answer_input)) {
      player_answer = ANSWER_MIN - 1;
      continue;
    }
    player_answer = atoi(answer_input);
  } while ((player_answer < ANSWER_MIN) || (player_answer > ANSWER_MAX));

  return player_answer;
}

// �덷�̕����ɉ�����JUDGE�񋓌^��Ԃ�
void PrintJudgeMessage(int diff) {
  static const char* judge_messages[] = {
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
  // �v���C���[�𓚂Ɛ����Ƃ̌덷
  int answer_diff;

  // �����̐��l�𐶐�
  srand((unsigned)time(NULL));
  correct_answer = (rand() % (ANSWER_MAX - ANSWER_MIN + 1)) + ANSWER_MIN;

  printf("�����ăQ�[���ł��B\n");
  do {
    // �v���C���[����
    player_answer = AnswerByPlayer();
    answer_count++;

    // ����\��
    answer_diff = player_answer - correct_answer;
    printf("���Ȃ��̉�\"%d\"��", player_answer);
    PrintJudgeMessage(answer_diff);
    printf("\n\n");
  } while (answer_diff);

  printf("���Ȃ���%d��ڂŐ������܂����B\n", answer_count);

  return 0;
}