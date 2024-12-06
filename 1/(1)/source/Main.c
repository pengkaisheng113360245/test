#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

// 此處不可修改，但可以修改optimization_shuffle();與optimization_deal();的參數定義
void shuffle(int wDeck[][13]);
void deal(const int wDeck[][13], const char* wFace[], const char* wSuit[]);
void optimization_shuffle();
void optimization_deal();
double get_high_resolution_time();

// 此處不可修改
// 在全域宣告計數器
static int shuffle_count = 0;
static int deal_count = 0;
static int opt_shuffle_count = 0;
static int opt_deal_count = 0;

// 此處不可修改
// 時間測量函數
double get_high_resolution_time() {
    LARGE_INTEGER frequency;
    LARGE_INTEGER count;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&count);
    return (double)count.QuadPart / (double)frequency.QuadPart;
}

// 此處不可修改
// 效能提升計算函數
double calculate_improvement(double original, double optimized) {
    return ((original - optimized) / original) * 100.0;
}

// 原始洗牌 (shuffle) 函數，請在此撰寫範例程式的shuffle函數
void shuffle(int wDeck[][13]) {
    shuffle_count=0;
    int row, column, card;

    for (card = 1; card <= 52; card++) 
    {
        do
        {
            row = rand() % 4;
            column = rand() % 13;
            shuffle_count++;
        } while (wDeck[row][column] != 0);

        wDeck[row][column] = card;
    }
}

// 原始發牌 (deal) 函數，請在此撰寫範例程式的deal函數
void deal(const int wDeck[][13], const char* wFace[], const char* wSuit[]) {
    deal_count=0;
    int row, column, card;

    for (card = 1; card <= 52; card++) {
        for (row = 0; row <= 3; row++) {
            for (column = 0; column <= 12; column++) {
                deal_count++;
                if (wDeck[row][column] == card) {
                    printf("%5s of %-8s%c", wFace[column], wSuit[row],
                        card % 2 == 0 ? '\n' : '\t');
                }
            }
        }
    }
}

// 優化後洗牌 (optimization_shuffle) 函數，請在此重新撰寫優化後的程式
void optimization_shuffle() {

}

// 優化後發牌 (optimization_deal) 函數，請在此重新撰寫優化後的程式
void optimization_deal() {

}

// 此處不可修改，但可以新增宣告跟修改optimization_shuffle();與optimization_deal();的參數呼叫
int main(void) {
    const char* suit[4] = { "Hearts", "Diamonds", "Clubs", "Spades" };
    const char* face[13] = {
        "Ace", "Deuce", "Three", "Four",
        "Five", "Six", "Seven", "Eight",
        "Nine", "Ten", "Jack", "Queen", "King"
    };
    int deck[4][13] = { 0 };
    double start_time, end_time;

    // 初始化隨機數生成器
    srand((unsigned int)time(0));

    // 執行原始 shuffle 並記錄時間
    start_time = get_high_resolution_time();
    shuffle(deck);
    end_time = get_high_resolution_time();
    double shuffle_time = (end_time - start_time) * 1000000.0;

    // 執行優化後 optimization_shuffle 並記錄時間
    start_time = get_high_resolution_time();
    optimization_shuffle();
    end_time = get_high_resolution_time();
    double optimized_shuffle_time = (end_time - start_time) * 1000000.0;

    // 執行原始 deal 並記錄時間
    start_time = get_high_resolution_time();
    deal(deck, face, suit);
    end_time = get_high_resolution_time();
    double deal_time = (end_time - start_time) * 1000000.0;

    // 執行優化後 optimization_deal 並記錄時間
    start_time = get_high_resolution_time();
    optimization_deal();
    end_time = get_high_resolution_time();
    double optimized_deal_time = (end_time - start_time) * 1000000.0;

    // 計算洗牌/發牌效能提升百分比
    double shuffle_improvement = calculate_improvement(shuffle_time, optimized_shuffle_time);
    double deal_improvement = calculate_improvement(deal_time, optimized_deal_time);

    // 最後打印時間比較結果
    printf("原始洗牌執行時間: %.4f microseconds\n", shuffle_time);
    printf("原始洗牌執行次數: %d\n", shuffle_count);

    /* 實作優化結果，需拿掉此段註解
    printf("優化洗牌執行時間: %.4f microseconds\n", optimized_shuffle_time);
    printf("優化洗牌執行次數: %d\n", opt_shuffle_count);
    printf("洗牌效能提升: %.4f%%\n\n", shuffle_improvement);
    */

    printf("原始發牌執行時間: %.4f microseconds\n", deal_time);
    printf("原始發牌執行次數: %d\n", deal_count);

    /* 實作優化結果，需拿掉此段註解
    printf("優化發牌執行時間: %.4f microseconds\n", optimized_deal_time);
    printf("優化發牌執行次數: %d\n", opt_deal_count);
    printf("發牌效能提升: %.4f%%\n", deal_improvement);
    */

    return 0;
}