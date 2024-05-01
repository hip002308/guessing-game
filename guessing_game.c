#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <wctype.h>

// 入力は何進数か
#define INPUT_BASE (2)
// 正解値の最小値・最大値
#define ANSWER_MIN (0)
#define ANSWER_MAX (11111111)
// COUNT_DIGITSマクロの引数を先に数値に置き換えるためにSTRINGマクロをかませる
#define STRING(str) (#str)
// 引数を文字列にしてその桁数を返す
#define COUNT_DIGITS(value) (_countof(STRING(value)) - 1)
// 桁数の多い方を返す
#define DIGITS_MAX ((((-ANSWER_MIN) < ANSWER_MAX) ? COUNT_DIGITS(ANSWER_MAX) : (COUNT_DIGITS(ANSWER_MIN) - 1)) - 2)
// 桁数(DIGIT_MAX) + 符号(1) + ヌル文字(1)
#define INPUT_ARRAY_SIZE (DIGITS_MAX + 2)
// 文字を数値にする
#define CTOI(character) (character - '0')
// 整数か否かを表す
#define DIGIT (1)
#define NOT_DIGIT (0)
// INPUT_BASE進数か否かを表す
#define CORRECT_BASE (1)
#define INCORRECT_BASE (0)
// プレイヤーの入力が正しいか否かを表す
#define APPROPRIATE_INPUT (1)
#define INAPPROPRIATE_INPUT (0)

// ゲーム情報を格納する
typedef struct {
  // プレイヤーの入力
  char player_input[INPUT_ARRAY_SIZE];
  // プレイヤーの解答
  int player_answer;
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

// 整数値ならDIGIT、それ以外はNOT_DIGITを返す
int isDigits(char str[]) {
  int index;
  int str_length = (int)strlen(str);
  int char_count = 0;

  for (index = 0; index < str_length; index++) {
    if (!iswdigit(str[index])) {
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
    int value = CTOI(str[index]);
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
void AnswerByPlayer(GAME_INFO* info) {
  info->player_answer = ANSWER_MIN - 1;
  int is_appropriate;

  do {
    printf("%dから%dまでの整数を%d進数で入力してください：", ANSWER_MIN, ANSWER_MAX, INPUT_BASE);
    // 第3引数のバッファサイズに、配列の最大文字数を返す_countofマクロを使用
    scanf_s("%s", info->player_input, (unsigned)_countof(info->player_input));
    ThroughRestBuffer();
    info->player_answer = atoi(info->player_input);
    is_appropriate = isAppropriateInput(info->player_input);
    // 入力が適切でないか、適切かつ範囲外の数値(どんな進数でも10進数で評価)であれば ループ続行
  } while ((is_appropriate == INAPPROPRIATE_INPUT) || (info->player_answer < ANSWER_MIN) || (info->player_answer > ANSWER_MAX));
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

// INPUT_BASE進数の文字列を10進数にして返す
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

// INPUT_BASE進数を10進数にして返す
int IntTo10Base(int value_n_base) {
  char str_n_base[INPUT_ARRAY_SIZE];
  _snprintf_s(str_n_base, INPUT_ARRAY_SIZE, INPUT_ARRAY_SIZE - 1, "%d", value_n_base);
  int value_10 = CharTo10Base(str_n_base);
  return value_10;
}

int main(void) {
  // ゲーム情報
  GAME_INFO info = {
    '\0'
  };
  // プレイヤーの解答回数
  int answer_count = 0;
  // マクロ最大値（INPUT_BASE進数表記）をint型にする
  int const input_max = IntTo10Base(ANSWER_MAX);
  // マクロ最小値（INPUT_BASE進数表記）をint型にする
  int const input_min = IntTo10Base(ANSWER_MIN);

  // 正解の数値を生成
  srand((unsigned)time(NULL));
  info.correct_answer = (rand() % (input_max - input_min + 1)) + input_min;

  printf("数当てゲームです。\n");
  do {
    // プレイヤー入力
    AnswerByPlayer(&info);
    info.player_answer = CharTo10Base(info.player_input);
    answer_count++;

    // 正誤表示
    int answer_diff = info.player_answer - info.correct_answer;
    printf("あなたの解答\"%s\"は", info.player_input);
    PrintJudgeMessage(answer_diff);
    printf("\n\n");
  } while (info.player_answer != info.correct_answer);

  printf("あなたは%d回目で正解しました。\n", answer_count);

  return 0;
}