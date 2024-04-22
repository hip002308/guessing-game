#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 正解値の最小値・最大値
#define ANSWER_MIN (1)
#define ANSWER_MAX (100)

int main(void) {
  // プレイヤーの入力保持
  char input[10] = {'\0'};
  // プレイヤーの解答
  int player_answer;
  // ゲームの正解
  int correct_answer;
  // プレイヤーの解答回数
  int count = 0;

  // 正解の数値を生成
  srand((unsigned) time(NULL));
  correct_answer = rand() % ANSWER_MAX + ANSWER_MIN;

  do {
    // プレイヤー入力
    printf("1から100までの数字を入力してください：");
    scanf_s("%9s", input, (unsigned) (sizeof(input) / sizeof(input[0])));
    player_answer = atoi(input);
    if ((player_answer < ANSWER_MIN) || (player_answer > ANSWER_MAX)) {
      printf("\a【注意】1以上100以下の数字を入力してください。\n\n");
      continue;
    }
    count++;

    // 正誤判定・表示
    printf("あなたの解答\"%d\"は", player_answer);
    if (player_answer < correct_answer) {
      puts("Small");
    } else if (player_answer > correct_answer) {
      puts("Big");
    } else {
      puts("Bingo!");
      printf("あなたは%d回目で正解しました。", count);
    }
    printf("\n");
  } while (player_answer != correct_answer);

  return 0;
}