#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Structure to store the coordinates of the points
typedef struct {
    int x;
    int y;
} Point;

// Global variables to store your location
int your_x, your_y;

// Function to read data from input
Point* ReadData(int n) {
    Point *points = (Point *)malloc(n * sizeof(Point));
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &points[i].x, &points[i].y);
    }
    return points;
}

// Function to compare two points
int compareTo(Point *ptrPt1, Point *ptrPt2) {
    int dist1 = (ptrPt1->x - your_x) * (ptrPt1->x - your_x) + (ptrPt1->y - your_y) * (ptrPt1->y - your_y);
    int dist2 = (ptrPt2->x - your_x) * (ptrPt2->x - your_x) + (ptrPt2->y - your_y) * (ptrPt2->y - your_y);

    if (dist1 != dist2) return dist1 - dist2;
    if (ptrPt1->x != ptrPt2->x) return ptrPt1->x - ptrPt2->x;
    return ptrPt1->y - ptrPt2->y;
}

// Insertion sort function
void insertionSort(Point *arr, int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        Point key = arr[i];
        int j = i - 1;
        while (j >= left && compareTo(&arr[j], &key) > 0) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Merge function for merge sort
void merge(Point *arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    Point *L = (Point *)malloc(n1 * sizeof(Point));
    Point *R = (Point *)malloc(n2 * sizeof(Point));

    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int i = 0; i < n2; i++) R[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (compareTo(&L[i], &R[j]) <= 0) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    free(L);
    free(R);
}

// Recursive merge sort function
void mergeSort(Point *arr, int left, int right, int t) {
    if (right - left + 1 <= t) {
        insertionSort(arr, left, right);
    } else {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid, t);
        mergeSort(arr, mid + 1, right, t);
        merge(arr, left, mid, right);
    }
}

// Wrapper sort function
void sort(Point *arr, int length, int t) {
    mergeSort(arr, 0, length - 1, t);
}

// Binary search function
int binarySearch(Point *arr, int left, int right, Point target) {
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid].x == target.x && arr[mid].y == target.y) return mid;
        if (compareTo(&arr[mid], &target) < 0) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

int main() {
    int n, s, t;
    scanf("%d %d %d %d %d", &your_x, &your_y, &n, &s, &t);

    Point *shops = ReadData(n);
    Point *queries = (Point *)malloc(s * sizeof(Point));
    for (int i = 0; i < s; i++) {
        scanf("%d %d", &queries[i].x, &queries[i].y);
    }

    sort(shops, n, t);

    for (int i = 0; i < n; i++) {
        printf("%d %d\n", shops[i].x, shops[i].y);
    }

    for (int i = 0; i < s; i++) {
        int index = binarySearch(shops, 0, n - 1, queries[i]);
        if (index != -1) {
            printf("%d %d found at rank %d\n", queries[i].x, queries[i].y, index + 1);
        } else {
            printf("%d %d not found\n", queries[i].x, queries[i].y);
        }
    }

    free(shops);
    free(queries);

    return 0;
}
