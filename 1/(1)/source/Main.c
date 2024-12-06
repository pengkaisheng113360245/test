#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

// ���B���i�ק�A���i�H�ק�optimization_shuffle();�Poptimization_deal();���ѼƩw�q
void shuffle(int wDeck[][13]);
void deal(const int wDeck[][13], const char* wFace[], const char* wSuit[]);
void optimization_shuffle();
void optimization_deal();
double get_high_resolution_time();

// ���B���i�ק�
// �b����ŧi�p�ƾ�
static int shuffle_count = 0;
static int deal_count = 0;
static int opt_shuffle_count = 0;
static int opt_deal_count = 0;

// ���B���i�ק�
// �ɶ����q���
double get_high_resolution_time() {
    LARGE_INTEGER frequency;
    LARGE_INTEGER count;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&count);
    return (double)count.QuadPart / (double)frequency.QuadPart;
}

// ���B���i�ק�
// �įണ�ɭp����
double calculate_improvement(double original, double optimized) {
    return ((original - optimized) / original) * 100.0;
}

// ��l�~�P (shuffle) ��ơA�Цb�����g�d�ҵ{����shuffle���
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

// ��l�o�P (deal) ��ơA�Цb�����g�d�ҵ{����deal���
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

// �u�ƫ�~�P (optimization_shuffle) ��ơA�Цb�����s���g�u�ƫ᪺�{��
void optimization_shuffle() {

}

// �u�ƫ�o�P (optimization_deal) ��ơA�Цb�����s���g�u�ƫ᪺�{��
void optimization_deal() {

}

// ���B���i�ק�A���i�H�s�W�ŧi��ק�optimization_shuffle();�Poptimization_deal();���ѼƩI�s
int main(void) {
    const char* suit[4] = { "Hearts", "Diamonds", "Clubs", "Spades" };
    const char* face[13] = {
        "Ace", "Deuce", "Three", "Four",
        "Five", "Six", "Seven", "Eight",
        "Nine", "Ten", "Jack", "Queen", "King"
    };
    int deck[4][13] = { 0 };
    double start_time, end_time;

    // ��l���H���ƥͦ���
    srand((unsigned int)time(0));

    // �����l shuffle �ðO���ɶ�
    start_time = get_high_resolution_time();
    shuffle(deck);
    end_time = get_high_resolution_time();
    double shuffle_time = (end_time - start_time) * 1000000.0;

    // �����u�ƫ� optimization_shuffle �ðO���ɶ�
    start_time = get_high_resolution_time();
    optimization_shuffle();
    end_time = get_high_resolution_time();
    double optimized_shuffle_time = (end_time - start_time) * 1000000.0;

    // �����l deal �ðO���ɶ�
    start_time = get_high_resolution_time();
    deal(deck, face, suit);
    end_time = get_high_resolution_time();
    double deal_time = (end_time - start_time) * 1000000.0;

    // �����u�ƫ� optimization_deal �ðO���ɶ�
    start_time = get_high_resolution_time();
    optimization_deal();
    end_time = get_high_resolution_time();
    double optimized_deal_time = (end_time - start_time) * 1000000.0;

    // �p��~�P/�o�P�įണ�ɦʤ���
    double shuffle_improvement = calculate_improvement(shuffle_time, optimized_shuffle_time);
    double deal_improvement = calculate_improvement(deal_time, optimized_deal_time);

    // �̫ᥴ�L�ɶ�������G
    printf("��l�~�P����ɶ�: %.4f microseconds\n", shuffle_time);
    printf("��l�~�P���榸��: %d\n", shuffle_count);

    /* ��@�u�Ƶ��G�A�ݮ������q����
    printf("�u�Ƭ~�P����ɶ�: %.4f microseconds\n", optimized_shuffle_time);
    printf("�u�Ƭ~�P���榸��: %d\n", opt_shuffle_count);
    printf("�~�P�įണ��: %.4f%%\n\n", shuffle_improvement);
    */

    printf("��l�o�P����ɶ�: %.4f microseconds\n", deal_time);
    printf("��l�o�P���榸��: %d\n", deal_count);

    /* ��@�u�Ƶ��G�A�ݮ������q����
    printf("�u�Ƶo�P����ɶ�: %.4f microseconds\n", optimized_deal_time);
    printf("�u�Ƶo�P���榸��: %d\n", opt_deal_count);
    printf("�o�P�įണ��: %.4f%%\n", deal_improvement);
    */

    return 0;
}