#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int dlta[29] = { // Sedgewick增量
1073643521, 603906049, 268386305, 150958081, 67084289,
37730305, 16764929, 9427969, 4188161, 2354689,
1045505, 587521, 260609, 146305, 64769,
36289, 16001, 8929, 3905, 2161,
929, 505, 209, 109, 41,
19, 5, 1, 0 }; //用 0 标记终点 

#define SHRT_MAX 1000000
#define MSORT_MAX_SIZE SHRT_MAX+1
int GlobalMsort[MSORT_MAX_SIZE];
void StraightInsertSort(int *, int);
void BInsertSort(int *, int);
void ShellInsert(int *, int, int);
void ShellSort(int *, int);
void BubbleSort(int *, int);
int Partition(int *, int, int);
void QSort(int *, int, int);
void QuickSort(int *, int);
void SelectSort(int *, int);
int SelectMinKey(int *, int, int);
void HeapAdjust(int *, int, int);
void HeapSort(int *, int);
void Merge(int *, int, int, int);
void MSort(int *, int, int);
void MergeSort(int *, int);
int LT(int, int);
void exchange(int *, int, int);
void PrintList(int *, int);

int main(void)
{
    int i, count;
    int *sort, *unsorted;
    clock_t start, finish;
    double elapsed_time;
    
    i = SHRT_MAX;
    printf("input count of integers (SHRT_MAX is %d):",i);
    scanf("%d", &count);
    getchar();
    
    sort = (int *)malloc((count+1)*sizeof(int));
    unsorted = (int *)malloc((count+1)*sizeof(int));
    srand((unsigned)time(NULL));
    for (int i=1; i<=count; i++)
        unsorted[i] = rand() * rand();
    printf("Unsorted %d entries.\n", count);
    PrintList(unsorted, count);

    // StraightInsertSort
    for (int i=1; i<=count; i++)
        sort[i] = unsorted[i];
    printf("\nStraightInsertSort");
    start = clock();
    StraightInsertSort(sort, count);
    finish = clock();
    elapsed_time = (double)(finish - start) / CLOCKS_PER_SEC;
    printf(" takes %6.3f seconds for %d integers.\n", elapsed_time, count);

    // BInsertSort
    for (int i=1; i<=count; i++)
        sort[i] = unsorted[i];
    printf("\nBInsertSort");
    start = clock();
    BInsertSort(sort, count);
    finish = clock();
    elapsed_time = (double)(finish - start) / CLOCKS_PER_SEC;
    printf(" takes %6.3f seconds for %d integers.\n", elapsed_time, count);

    // ShellSort
    for (int i=1; i<=count; i++)
        sort[i] = unsorted[i];
    printf("\nShellSort");
    start = clock();
    ShellSort(sort, count);
    finish = clock();
    elapsed_time = (double)(finish - start) / CLOCKS_PER_SEC;
    printf(" takes %6.3f seconds for %d integers.\n", elapsed_time, count);

    // BubbleSort
    for (int i=1; i<=count; i++)
        sort[i] = unsorted[i];
    printf("\nBubbleSort");
    start = clock();
    BubbleSort(sort, count);
    finish = clock();
    elapsed_time = (double)(finish - start) / CLOCKS_PER_SEC;
    printf(" takes %6.3f seconds for %d integers.\n", elapsed_time, count);

    // QuickSort
    for (int i=1; i<=count; i++)
        sort[i] = unsorted[i];
    printf("\nQuickSort");
    start = clock();
    QuickSort(sort, count);
    finish = clock();
    elapsed_time = (double)(finish - start) / CLOCKS_PER_SEC;
    printf(" takes %6.3f seconds for %d integers.\n", elapsed_time, count);

    // SelectSort
    for (int i=1; i<=count; i++)
        sort[i] = unsorted[i];
    printf("\nSelectSort");
    start = clock();
    SelectSort(sort, count);
    finish = clock();
    elapsed_time = (double)(finish - start) / CLOCKS_PER_SEC;
    printf(" takes %6.3f seconds for %d integers.\n", elapsed_time, count);

    // HeapSort
    for (int i=1; i<=count; i++)
        sort[i] = unsorted[i];
    printf("\nHeapSort");
    start = clock();
    HeapSort(sort, count);
    finish = clock();
    elapsed_time = (double)(finish - start) / CLOCKS_PER_SEC;
    printf(" takes %6.3f seconds for %d integers.\n", elapsed_time, count);

    // MergeSort
    for (int i=1; i<=count; i++)
        sort[i] = unsorted[i];
    printf("\nMergeSort");
    start = clock();
    MergeSort(sort, count);
    finish = clock();
    elapsed_time = (double)(finish - start) / CLOCKS_PER_SEC;
    printf(" takes %6.3f seconds for %d integers.\n", elapsed_time, count);

    printf("\nPress Enter to print the sorted result.\n");
    getchar();
    printf("Sorted %d entries.\n", count);
    PrintList(sort, count);
    
    free(sort);
    free(unsorted);
    return 0;
}

void StraightInsertSort(int *L, int length)
{
    for (int i = 2; i <= length; i++)
        if (LT(L[i], L[i-1])) {
            L[0] = L[i];
            L[i] = L[i-1];
            int j = i-2;
            for (; LT(L[0], L[j]); --j) // make sure p always equals j
                L[j+1] = L[j];
            L[j+1] = L[0];
        }
}

void BInsertSort(int *L, int length)
{
    for (int i = 2; i <= length; i++) {
        L[0] = L[i];
        int low = 1, high = i-1;
        while (low <= high) {
            int m = (low + high)/2;
            if (LT(L[0], L[m])) high = m-1;
            else low = m+1;
        }
        for (int j = i-1; j >= high+1; --j) L[j+1] = L[j];
        L[high+1] = L[0];
    }
}

void ShellInsert(int *L, int dk, int length)
{
    // straightinsertsort L
    for (int i = dk+1; i<=length; i++)
        if (LT(L[i], L[i-dk])) {
            L[0] = L[i];
            int j = i-dk;
            for (; j>0 && LT(L[0],L[j]); j-=dk)
                L[j+dk] = L[j];
            L[j+dk] = L[0];
        }
}

void ShellSort(int *L, int length)
{
    for (int i = 0; dlta[i]; i++)
        ShellInsert(L, dlta[i], length);
}

void BubbleSort(int *L, int length)
{
    for (int i = length; i > 1; i--)
        for (int j = 1; j < i; j++)
            if (LT(L[j+1], L[j])) exchange(L, j, j+1);
}

int Partition(int *L, int low, int high)
{
    L[0] = L[low];
    int pivotkey = L[low];
    while (low < high) {
        while (low<high && L[high]>=pivotkey) --high;
        L[low] = L[high];
        while (low<high && L[low]<=pivotkey) ++low;
        L[high] = L[low];
    }
    L[low] = L[0];
    return low;
}

void QSort(int *L, int low, int high)
{
    if (low < high) {
        int pivotloc = Partition(L, low, high);
        QSort(L, low, pivotloc-1);
        QSort(L, pivotloc+1, high);
    }
}

void QuickSort(int *L, int length)
{
    QSort(L, 1, length);
}

void SelectSort(int *L, int length)
{
    for (int i = 1; i < length; i++) {
        int j = SelectMinKey(L, i, length);
        if (i!=j) exchange(L, i, j);
    }
}

int SelectMinKey(int *L, int a, int length)
{
    for (int i = a; i <= length; i++)
        if (LT(L[i], L[a])) a = i;
    return a;
}

void HeapAdjust(int *L, int s, int m)
{
    int rc = L[s];
    for (int j = 2*s; j <= m; j*=2) {
        if (j<m && LT(L[j], L[j+1])) ++j;
        if (!LT(rc, L[j])) break;
        L[s] = L[j];
        s = j;
    }
    L[s] = rc;
}

void HeapSort(int *L, int length)
{
    for (int i = length/2; i > 0; --i)
        HeapAdjust(L, i, length);
    for (int i = length; i > 1; --i) {
        exchange(L, 1, i);
        HeapAdjust(L, 1, i-1);
    }
}

void Merge(int *TR, int first, int middle, int last)
{
    int i = first, j = middle+1, k = first;
    for (; i<=middle && j<=last; ++k) {
        if (LT(GlobalMsort[i],GlobalMsort[j])) TR[k] = GlobalMsort[i++];
        else TR[k] = GlobalMsort[j++];
    }
    if (i<=middle)
        for (int p = i; p <= middle; p++)
            TR[p-i+k] = GlobalMsort[p];
    if (j<=last)
        for (int p = j; p <= middle; p++)
            TR[p-j+k] = GlobalMsort[p];
    for (int p = first; p <= last; p++)
        GlobalMsort[p] = TR[p];
}

void MSort(int * TR, int s, int t)
{
    if (s == t) GlobalMsort[s] = TR[s];
    else {
        int m = (s+t)/2;
        MSort(TR, s, m);
        MSort(TR, m+1, t);
        Merge(TR, s, m, t);
    }
}

void MergeSort(int * L, int length)
{
    MSort(L, 1, length);
}

void exchange(int *L, int j, int k)
{
    int tmp = L[j];
    L[j] = L[k];
    L[k] = tmp;
}

void PrintList(int *L, int length)
{
    for (int i = 1; i <= length; i++)
        printf("%d ", L[i]);
    printf("\n");
}

int LT(int a, int b)
{
    if (a < b) return 1;
    return 0;
}
