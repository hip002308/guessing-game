#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <wctype.h>

// 正解値の最小値・最大値
#define ANSWER_MIN (1)
#define ANSWER_MAX (100)
// COUNT_DIGITSマクロの引数を先に数値に置き換えるためにSTRINGマクロをかませる
#define STRING(str) (#str)
// 引数を文字列にしてその桁数を返す
#define COUNT_DIGITS(value) (_countof(STRING(value)) - 1)
// 桁数の多い方を返す
#define DIGITS_MAX ((((-ANSWER_MIN) < ANSWER_MAX) ? COUNT_DIGITS(ANSWER_MAX) : (COUNT_DIGITS(ANSWER_MIN) - 1)) - 2)
// 桁数(DIGIT_MAX) + 符号(1) + ヌル文字(1)
#define INPUT_ARRAY_SIZE (DIGITS_MAX + 2)
// 整数か否かを表す
#define DIGIT (1)
#define NOT_DIGIT (0)

// 残りの入力バッファを読み飛ばす
void ThroughRestBuffer() {
  char buffer = getchar();
  while (buffer != '\n') {
    buffer = getchar();
  }
}

// 整数値ならDIGIT、それ以外はNOT_DIGITを返す
int isDigits(char str[]) {
  int idx;
  int str_length = (int)strlen(str);
  int char_count = 0;

  for (idx = 0; idx < str_length; idx++) {
    if (!iswdigit(str[idx])) {
      char_count++;
    }
  }
  // 長さが0ならば整数でない、先頭が符号なら整数の可能性
  if ((str_length == 0) || (str[0] == '-') || (str[0] == '+')) {
    char_count--;
  }

  if (char_count) {
    return NOT_DIGIT;
  }
  return DIGIT;
}

// 答えの入力を求める
int AnswerByPlayer() {
  char answer_input[INPUT_ARRAY_SIZE] = {
    '\0'
  };
  int player_answer = ANSWER_MIN - 1;
  int is_digit;

  do {
    printf("%dから%dまでの整数を入力してください：", ANSWER_MIN, ANSWER_MAX);
    // 第3引数のバッファサイズに、配列の最大文字数を返す_countofマクロを使用
    scanf_s("%s", answer_input, (unsigned)_countof(answer_input));
    ThroughRestBuffer();
    player_answer = atoi(answer_input);
    is_digit = isDigits(answer_input);
    // 整数でないか、整数かつ範囲外の数値であれば true
  } while ((is_digit == NOT_DIGIT) || (player_answer < ANSWER_MIN) || (player_answer > ANSWER_MAX));

  return player_answer;
}

// 判定メッセージを表示する
void PrintJudgeMessage(int diff) {
  static char const * const judge_messages[] = {
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

  // 正解の数値を生成
  srand((unsigned)time(NULL));
  correct_answer = (rand() % (ANSWER_MAX - ANSWER_MIN + 1)) + ANSWER_MIN;

  printf("数当てゲームです。\n");
  do {
    // プレイヤー入力
    player_answer = AnswerByPlayer();
    answer_count++;

    // 正誤表示
    int answer_diff = player_answer - correct_answer;
    printf("あなたの解答\"%d\"は", player_answer);
    PrintJudgeMessage(answer_diff);
    printf("\n\n");
  } while (player_answer != correct_answer);

  printf("あなたは%d回目で正解しました。\n", answer_count);

  return 0;
}