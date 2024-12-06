#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

// ���B���i�ק�
#define N 1000

// ���B���i�ק�
// �b����ŧi�p�ƾ�
static int bubbleSort_count = 0;
static int opt_bubbleSort_count = 0;

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

// ���B���i�ק�
// �}�C�ƻs���
void copyArray(int source[], int dest[], int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = source[i];
    }
}

// ��l��w�Ƨ� (bubbleSort) ��ƽЦb�����g�d�ҵ{����bubbleSort���
void bubbleSort(int arr[], int n) {
    bubbleSort_count = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            bubbleSort_count++;
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// �u�ƫ��w�Ƨ� (optimized_bubbleSort) ��ƽЦb�����s���g�u�ƫ᪺�{��
void optimized_bubbleSort(int arr[], int n) {
    opt_bubbleSort_count = 0; // ��l�ƭp�ƾ�
    int left = 0;             // �����
    int right = n - 1;        // �k���

    while (left < right) {
        int newRight = left;  // �O���̫�洫����m
        int newLeft = right;  // �O���̦��洫����m

        // �q����k�i�����ðO���s�k���
        for (int i = left; i < right; i++) {
            opt_bubbleSort_count++;
            if (arr[i] > arr[i + 1]) {
                int temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
                newRight = i;
            }
        }
        right = newRight; // ��s�k���

        // �q�k�쥪�i�����ðO���s�����
        for (int i = right; i > left; i--) {
            opt_bubbleSort_count++;
            if (arr[i] < arr[i - 1]) {
                int temp = arr[i];
                arr[i] = arr[i - 1];
                arr[i - 1] = temp;
                newLeft = i;
            }
        }
        left = newLeft; // ��s�����
    }
}

// ���B���i�ק�
// ���ͪ���ƧǪ��}�C���
void generateNearlySortedArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = i * 5;
    }
    int numSwaps = n * 0.9;
    for (int i = 0; i < numSwaps / 2; i++) {
        int pos1 = rand() % (numSwaps / 2);
        int pos2 = rand() % (numSwaps / 2);

        int temp = arr[pos1];
        arr[pos1] = arr[pos2];
        arr[pos2] = temp;
    }
}

// ���B���i�ק�
int main() {
    int original[N];
    int arr1[N];
    int arr2[N];
    double start_time, end_time,time_used;

    srand(time(NULL));
    printf("�ͦ� %d ���H����\n", N);

    // �ͦ����ո��
    generateNearlySortedArray(original, N);

    // �ƻs��l���ո�ơA�T�O��رƧǤ�k�ϥάۦP�����ո��
    copyArray(original, arr1, N);
    copyArray(original, arr2, N);

    printf("\n��l�}�C�e100�ӼƦr�G\n");
    for (int i = 0; i < 100; i++) {
        printf("%d ", original[i]);
    }
    printf("...\n");

    // �����l bubbleSort �ðO���ɶ�
    start_time = get_high_resolution_time();
    bubbleSort(arr1, N);
    end_time = get_high_resolution_time();
    double bubbleSort_time = (end_time - start_time) * 1000000.0;

    // �����u�ƫ� optimized_bubbleSort �ðO���ɶ�
    start_time = get_high_resolution_time();
    optimized_bubbleSort(arr2, N);
    end_time = get_high_resolution_time();
    double optimized_bubbleSort_time = (end_time - start_time) * 1000000.0;

    // �p���w�ƧǮįണ�ɦʤ���
    double bubbleSort_improvement = calculate_improvement(bubbleSort_time, optimized_bubbleSort_time);

    printf("\n��l��w�Ƨǫ�e20�ӼƦr�G\n");
    for (int i = 0; i < 20; i++) {
        printf("%d ", arr1[i]);
    }
    printf("...\n");
    printf("��l��w�Ƨǰ���ɶ��G%.4f microseconds\n", bubbleSort_time);
    printf("��l��w�Ƨǫ���榸��: %d\n\n", bubbleSort_count);

    printf("�u�ƫ��w�Ƨǫ�e20�ӼƦr�G\n");
    for (int i = 0; i < 20; i++) {
        printf("%d ", arr2[i]);
    }
    printf("...\n");
    printf("�u�ƫ��w�Ƨǰ���ɶ��G%.4f microseconds\n", optimized_bubbleSort_time);
    printf("�u�ƫ��w�Ƨǫ���榸��: %d\n\n", opt_bubbleSort_count);

    printf("��w�ƧǮįണ��: %.4f%%\n", bubbleSort_improvement);

    return 0;
}
