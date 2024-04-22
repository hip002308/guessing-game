#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 正解値の最小値・最大値
#define ANSWER_MIN (1)
#define ANSWER_MAX (100)

// 残りの入力バッファを読み飛ばす
void ThroughRestBuffer() {
  char buffer = getchar();
  while (buffer != '\n') {
    buffer = getchar();
  }
}

// 数字の文字列を数値にして返す(先頭が文字列の場合、ANSWER_MIN - 1を返す)
int AtoiWithinRange(char str[]) {
  int ret = atoi(str);
  if (ret == 0 && str[0] != '0') {
    ret = ANSWER_MIN - 1;
  }
  return ret;
}

// 答えの入力を求める
int AnswerByPlayer() {
  char answer_input[10] = {'\0'};
  int player_answer;
  while (1) {
    printf("%dから%dまでの数字を入力してください：", ANSWER_MIN, ANSWER_MAX);
    // 第3引数のバッファサイズに、配列の最大文字数を返す_countofマクロを使用
    scanf_s("%9s", answer_input, (unsigned)_countof(answer_input));
    ThroughRestBuffer();
    player_answer = AtoiWithinRange(answer_input);
    if ((player_answer >= ANSWER_MIN) && (player_answer <= ANSWER_MAX)) {
      break;
    }
    printf("\a【注意】%d以上%d以下の数字を入力してください。\n\n", ANSWER_MIN, ANSWER_MAX);
  }
  return player_answer;
}

// 答えを生成する
int GenerateAnswer() {
  return (rand() % (ANSWER_MAX - ANSWER_MIN + 1)) + ANSWER_MIN;
}

int main(void) {
  // プレイヤーの解答
  int player_answer;
  // ゲームの正解
  int correct_answer;
  // プレイヤーの解答回数
  int answer_count = 0;

  // 正解の数値を生成
  srand((unsigned) time(NULL));
  correct_answer = GenerateAnswer();

  printf("数当てゲームです。\n");
  while (1) {
    // プレイヤー入力
    player_answer = AnswerByPlayer();
    answer_count++;

    // 正誤判定・表示
    printf("あなたの解答\"%d\"は", player_answer);
    int diff = player_answer - correct_answer;
    if (diff > 0) {
      printf("Big\n");
    }
    else if (diff < 0) {
      printf("Small\n");
    }
    else {
      printf("Bingo!\n");
      printf("あなたは%d回目で正解しました。\n", answer_count);
      break;
    }
    printf("\n");
  }

  return 0;
}