#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

// 正解値の最小値・最大値・最大桁数、配列の桁数
#define ANSWER_MIN (1)
#define ANSWER_MAX (100)
#define DIGITS_MAX (3)
#define INPUT_ARRAY_SIZE (DIGITS_MAX + 2)

// 残りの入力バッファを読み飛ばす
void ThroughRestBuffer() {
  char buffer = getchar();
  while (buffer != '\n') {
    buffer = getchar();
  }
}

// 0を返せば整数値、それ以外は文字列とみなす
int isString(char str[]) {
  int idx;
  int str_length = (int)strlen(str);
  int char_count = 0;

  for (idx = 0; idx < str_length; idx++) {
    if (!isdigit(str[idx])) {
      char_count++;
    }
  }
  // 先頭が符号なら整数の可能性、ヌル文字なら文字列
  if ((str[0] == '-') || (str[0] == '+') || (!str[0])) {
    char_count--;
  }

  return char_count;
}

// 答えの入力を求める
int AnswerByPlayer() {
  char answer_input[INPUT_ARRAY_SIZE];
  int player_answer;

  do {
    printf("%dから%dまでの整数を入力してください：", ANSWER_MIN, ANSWER_MAX);
    // 第3引数のバッファサイズに、配列の最大文字数を返す_countofマクロを使用
    scanf_s("%s", answer_input, (unsigned)_countof(answer_input));
    ThroughRestBuffer();
    // 配列要素数を超える入力か、数字以外の入力がされた場合
    if (isString(answer_input)) {
      player_answer = ANSWER_MIN - 1;
      continue;
    }
    player_answer = atoi(answer_input);
  } while ((player_answer < ANSWER_MIN) || (player_answer > ANSWER_MAX));

  return player_answer;
}

// 誤差の符号に応じたJUDGE列挙型を返す
void PrintJudgeMessage(int diff) {
  static const char* judge_messages[] = {
    "Small",
    "Bingo!",
    "Big"
  };
  // 符号(-1 or 0 or +1)と配列の要素を対応付ける
  int idx = (diff > 0) - (diff < 0) + 1;
  printf("%s", judge_messages[idx]);
}

int main(void) {
  // プレイヤーの解答
  int player_answer;
  // ゲームの正解
  int correct_answer;
  // プレイヤーの解答回数
  int answer_count = 0;
  // プレイヤー解答と正解との誤差
  int answer_diff;

  // 正解の数値を生成
  srand((unsigned)time(NULL));
  correct_answer = (rand() % (ANSWER_MAX - ANSWER_MIN + 1)) + ANSWER_MIN;

  printf("数当てゲームです。\n");
  do {
    // プレイヤー入力
    player_answer = AnswerByPlayer();
    answer_count++;

    // 正誤表示
    answer_diff = player_answer - correct_answer;
    printf("あなたの解答\"%d\"は", player_answer);
    PrintJudgeMessage(answer_diff);
    printf("\n\n");
  } while (answer_diff);

  printf("あなたは%d回目で正解しました。\n", answer_count);

  return 0;
}