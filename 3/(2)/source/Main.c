#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <windows.h>

// ���B���i�ק�
// �w�q�`��
#define SIZE 1000        // �̲��H���}�C���j�p
#define RANGE_START 1    // �d�򪺰_�l�Ʀr
#define RANGE_END 10000  // �d�򪺵����Ʀr

// ���B���i�ק�
// �b����ŧi�p�ƾ�
static int linearSearch_count = 0;
static int binarySearch_count = 0;
static int newSearch_count = 0;


// ���B���i�ק�
// �įണ�ɭp����
double calculate_improvement(double original, double optimized) {
    return ((original - optimized) / original) * 100.0;
}

// ���B���i�ק�
// Fisher-Yates �~�P�t��k���
void fisherYatesShuffle(int arr[], int size) {
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

// ���B���i�ק�
// �ͦ��������H���Ʋժ����
void generateUniqueRandomArray(int arr[], int size, int rangeStart, int rangeEnd, unsigned int seed) {
    if (rangeEnd - rangeStart + 1 < size) {
        printf("���~�G���w�d�򤺪��Ʀr�����H�ͦ��һݼƶq���������H����\n");
        return;
    }

    srand(seed);
    int* allNumbers = (int*)malloc((rangeEnd - rangeStart + 1) * sizeof(int));
    if (allNumbers == NULL) {
        printf("���~�G�O������t����\n");
        return;
    }

    for (int i = 0; i < rangeEnd - rangeStart + 1; i++) {
        allNumbers[i] = i + rangeStart;
    }

    fisherYatesShuffle(allNumbers, rangeEnd - rangeStart + 1);

    for (int i = 0; i < size; i++) {
        arr[i] = allNumbers[i];
    }

    free(allNumbers);
}


// ���B���i�ק�
// �ɶ����q���
double get_high_resolution_time() {
    LARGE_INTEGER frequency;
    LARGE_INTEGER count;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&count);
    return ((double)count.QuadPart / (double)frequency.QuadPart);
}


// ���B���i�ק�
// ��w�Ƨ� (bubbleSort) ���
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// �u�ʷj�M (linearSearch) ��ơA�Цb�����g�d�ҵ{����linearSearch���
int linearSearch(int arr[], int size, int target) {
    linearSearch_count = 0;
    for (int i = 0; i < size; i++) {
        linearSearch_count++;
        if (arr[i] == target) {
            return i;
        }
    }
    return -1;
}


// �G���j�M (binarySearch) ��ơA�Цb�����g�d�ҵ{����binarySearch���
int binarySearch(int arr[], int size, int target) {
    binarySearch_count = 0;
    int left = 0;
    int right = size - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        binarySearch_count++;

        if (arr[mid] == target) {
            return mid;
        }

        if (arr[mid] < target) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return -1;
}

// �s�j�M�t��k (newSearch) ��ơA�Цb�����g�s���j�M�t��k�{��
int newSearch(int arr[], int size, int target) {
    newSearch_count = 0;
    int left = 0;
    int right = size - 1;

    while (left <= right && target >= arr[left] && target <= arr[right]) {
        newSearch_count++;

        // ���ȷj�M��m�p��
        int pos = left + ((double)(target - arr[left]) / (arr[right] - arr[left]) * (right - left));

        // �T�O��m���V��
        if (pos < left) pos = left;
        if (pos > right) pos = right;

        if (arr[pos] == target) {
            return pos;
        }

        if (arr[pos] < target) {
            left = pos + 1;
        }
        else {
            right = pos - 1;
        }

        // �ʺA�����ܤG���j�M
        if (right - left < 10) {
            while (left <= right) {
                newSearch_count++;
                int mid = left + (right - left) / 2;
                if (arr[mid] == target) {
                    return mid;
                }
                if (arr[mid] < target) {
                    left = mid + 1;
                }
                else {
                    right = mid - 1;
                }
            }
            return -1;
        }
    }
    return -1;
}


// ���B���i�ק�A���i�H�ק�int newSearchResult = newSearch();�̪��ѼƩI�s
int main(void) {
    int arr[SIZE];
    generateUniqueRandomArray(arr, SIZE, RANGE_START, RANGE_END, 12345);
    bubbleSort(arr, SIZE);

    printf("�e20�Ӥw�ƧǥB�����ƪ��H���ơG\n");
    for (int i = 0; i < 20; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n\n");

    double start_time;
    double end_time;
    int target = 6164;  // �j�M�ؼ�


    // �u�ʷj�M���ɶ�����
    start_time = get_high_resolution_time();
    int linearSearchResult = linearSearch(arr, SIZE, target);
    end_time = get_high_resolution_time();
    double linearSearchResult_time = (end_time - start_time) * 1000000.0;

    // �G���j�M���ɶ�����t_time = get_high_resolution_time();
    int binarySearchResult = binarySearch(arr, SIZE, target);
    end_time = get_high_resolution_time();
    double binarySearchResult_time = (end_time - start_time) * 1000000.0;

    // �s�j�M�t��k���ɶ�����
    start_time = get_high_resolution_time();
    int newSearchResult = newSearch(arr, SIZE, target);
    end_time = get_high_resolution_time();
    double newSearch_time = (end_time - start_time) * 1000000.0;

    // �p��u��/�s�j�M�t��k�įണ�ɦʤ���
    double linear_new_improvement = calculate_improvement(linearSearchResult_time, newSearch_time);
    // �p��G��/�s�j�M�t��k�įണ�ɦʤ���
    double binary_new_improvement = calculate_improvement(binarySearchResult_time, newSearch_time);

    printf("�u�ʷj�M���G�G������� %d\n", linearSearchResult);
    printf("�u�ʷj�M����ɶ��G%.4f microseconds\n", linearSearchResult_time);
    printf("�u�ʷj�M���榸�ơG%d\n\n", linearSearch_count);

    printf("�G���j�M���G�G������� %d\n", binarySearchResult);
    printf("�G���j�M����ɶ��G%.4f microseconds\n", binarySearchResult_time);
    printf("�G���j�M���榸�ơG%d\n\n", binarySearch_count);

    printf("�s�j�M�t��k�j�M���G�G������� %d\n", newSearchResult);
    printf("�s�j�M�t��k����ɶ��G%.4f microseconds\n", newSearch_time);
    printf("�s�j�M�t��k���榸�ơG%d\n\n", newSearch_count);

    printf("�s�j�M�t��k��u�ʮįണ��: %.4f%%\n", linear_new_improvement);
    printf("�s�j�M�t��k��G���įണ��: %.4f%%\n", binary_new_improvement);

    return 0;
}
