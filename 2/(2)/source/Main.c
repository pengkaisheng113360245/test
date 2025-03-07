#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

// 此處不可修改
#define N 1000

// 此處不可修改
// 在全域宣告計數器
static int bubbleSort_count = 0;
static int opt_bubbleSort_count = 0;

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

// 此處不可修改
// 陣列複製函數
void copyArray(int source[], int dest[], int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = source[i];
    }
}

// 原始氣泡排序 (bubbleSort) 函數請在此撰寫範例程式的bubbleSort函數
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

// 優化後氣泡排序 (optimized_bubbleSort) 函數請在此重新撰寫優化後的程式
void optimized_bubbleSort(int arr[], int n) {
    opt_bubbleSort_count = 0; // 初始化計數器
    int left = 0;             // 左邊界
    int right = n - 1;        // 右邊界

    while (left < right) {
        int newRight = left;  // 記錄最後交換的位置
        int newLeft = right;  // 記錄最早交換的位置

        // 從左到右進行比較並記錄新右邊界
        for (int i = left; i < right; i++) {
            opt_bubbleSort_count++;
            if (arr[i] > arr[i + 1]) {
                int temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
                newRight = i;
            }
        }
        right = newRight; // 更新右邊界

        // 從右到左進行比較並記錄新左邊界
        for (int i = right; i > left; i--) {
            opt_bubbleSort_count++;
            if (arr[i] < arr[i - 1]) {
                int temp = arr[i];
                arr[i] = arr[i - 1];
                arr[i - 1] = temp;
                newLeft = i;
            }
        }
        left = newLeft; // 更新左邊界
    }
}

// 此處不可修改
// 產生近似排序的陣列函數
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

// 此處不可修改
int main() {
    int original[N];
    int arr1[N];
    int arr2[N];
    double start_time, end_time,time_used;

    srand(time(NULL));
    printf("生成 %d 個隨機數\n", N);

    // 生成測試資料
    generateNearlySortedArray(original, N);

    // 複製原始測試資料，確保兩種排序方法使用相同的測試資料
    copyArray(original, arr1, N);
    copyArray(original, arr2, N);

    printf("\n原始陣列前100個數字：\n");
    for (int i = 0; i < 100; i++) {
        printf("%d ", original[i]);
    }
    printf("...\n");

    // 執行原始 bubbleSort 並記錄時間
    start_time = get_high_resolution_time();
    bubbleSort(arr1, N);
    end_time = get_high_resolution_time();
    double bubbleSort_time = (end_time - start_time) * 1000000.0;

    // 執行優化後 optimized_bubbleSort 並記錄時間
    start_time = get_high_resolution_time();
    optimized_bubbleSort(arr2, N);
    end_time = get_high_resolution_time();
    double optimized_bubbleSort_time = (end_time - start_time) * 1000000.0;

    // 計算氣泡排序效能提升百分比
    double bubbleSort_improvement = calculate_improvement(bubbleSort_time, optimized_bubbleSort_time);

    printf("\n原始氣泡排序後前20個數字：\n");
    for (int i = 0; i < 20; i++) {
        printf("%d ", arr1[i]);
    }
    printf("...\n");
    printf("原始氣泡排序執行時間：%.4f microseconds\n", bubbleSort_time);
    printf("原始氣泡排序後執行次數: %d\n\n", bubbleSort_count);

    printf("優化後氣泡排序後前20個數字：\n");
    for (int i = 0; i < 20; i++) {
        printf("%d ", arr2[i]);
    }
    printf("...\n");
    printf("優化後氣泡排序執行時間：%.4f microseconds\n", optimized_bubbleSort_time);
    printf("優化後氣泡排序後執行次數: %d\n\n", opt_bubbleSort_count);

    printf("氣泡排序效能提升: %.4f%%\n", bubbleSort_improvement);

    return 0;
}
