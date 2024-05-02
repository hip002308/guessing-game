#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <wctype.h>

// 入力は何進数か
#define INPUT_BASE (2)
// 正解値の最小値・最大値
#define ANSWER_MIN ("0")
#define ANSWER_MAX ("11111111")
// 引数の桁数(符号も含む場合がある)を返す
#define COUNT_DIGITS(val_str) (_countof(val_str) - 1)
// 桁数の多い方を返す
#define DIGITS_MAX ((COUNT_DIGITS(ANSWER_MIN) < COUNT_DIGITS(ANSWER_MAX)) ? COUNT_DIGITS(ANSWER_MAX) : COUNT_DIGITS(ANSWER_MIN))
// 桁数(DIGIT_MAX) + 符号(1) + ヌル文字(1)
#define INPUT_ARRAY_SIZE (DIGITS_MAX + 2)
// 整数か否かを表す
#define DIGIT (1)
#define NOT_DIGIT (-1)
// INPUT_BASE進数か否かを表す
#define CORRECT_BASE (1)
#define INCORRECT_BASE (0)
// プレイヤーの入力が正しいか否かを表す
#define APPROPRIATE_INPUT (1)
#define INAPPROPRIATE_INPUT (0)

// ゲーム情報を格納する
typedef struct {
  // 正解値の最小値
  int answer_min;
  // 正解値の最大値
  int answer_max;
  // ゲームの正解
  int correct_answer;
} GAME_INFO;

// 残りの入力バッファを読み飛ばす
void ThroughRestBuffer() {
  char buffer = getchar();
  while (buffer != '\n') {
    buffer = getchar();
  }
}

// 文字(0~9a~zA~Z)を数値(0~35)に変換
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

// INPUT_BASE進数の文字列を10進数にして返す
int CharTo10Base(char str[]) {
  int index;
  int str_length = (int)strlen(str);
  // 符号があるかを読む
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

// 整数値ならDIGIT、それ以外はNOT_DIGITを返す
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
  // 長さが0ならば整数でない、先頭が符号なら整数の可能性
  if ((str_length == 0) || (str[0] == '-') || (str[0] == '+')) {
    char_count--;
  }

  if (char_count) {
    return NOT_DIGIT;
  }
  return DIGIT;
}

// INPUT_BASE進数に適合した文字列かどうか
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

// 入力が指示通り行われているか
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

// 答えの入力を求める
int AnswerByPlayer(GAME_INFO const * const info) {
  char player_input[INPUT_ARRAY_SIZE];
  int player_answer;
  int is_appropriate;

  do {
    printf("%dから%dまでの整数を%d進数で入力してください：", info->answer_min, info->answer_max, INPUT_BASE);
    // 第3引数のバッファサイズに、配列の最大文字数を返す_countofマクロを使用
    scanf_s("%s", player_input, (unsigned)_countof(player_input));
    ThroughRestBuffer();
    player_answer = CharTo10Base(player_input);
    is_appropriate = isAppropriateInput(player_input);
    // 入力が適切でないか、適切かつ範囲外の数値であれば ループ続行
  } while ((is_appropriate == INAPPROPRIATE_INPUT) || (player_answer < info->answer_min) || (player_answer > info->answer_max));

  printf("あなたの解答\"%s\"：", player_input);
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
  int index = (diff > 0) - (diff < 0) + 1;
  printf("%s", judge_messages[index]);
}

int main(void) {
  // プレイヤーの解答
  int player_answer;
  // プレイヤーの解答回数
  int answer_count = 0;
  // 正解値の最小値・最大値
  int const answer_min = CharTo10Base(ANSWER_MIN);
  int const answer_max = CharTo10Base(ANSWER_MAX);

  // 正解の数値を生成
  srand((unsigned)time(NULL));
  // ゲーム情報を格納
  GAME_INFO const info = {
    answer_min,
    answer_max,
    (rand() % (answer_max - answer_min + 1)) + answer_min
  };

  printf("数当てゲームです。\n");
  do {
    // プレイヤー入力
    player_answer = AnswerByPlayer(&info);
    answer_count++;

    // 正誤表示
    int answer_diff = player_answer - info.correct_answer;
    PrintJudgeMessage(answer_diff);
    printf("\n\n");
  } while (player_answer != info.correct_answer);

  printf("あなたは%d回目で正解しました。\n", answer_count);

  return 0;
}