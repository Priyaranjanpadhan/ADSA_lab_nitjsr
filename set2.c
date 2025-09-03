#include<stdio.h>
#include<stdlib.h>

//Insertion sort
void insertionSort(int arr[]){
    for (int i = 0; i < 8; i++)
    {
        int j = i;
        while (j > 0 && arr[j - 1] > arr[j])
        {
            int temp = arr[j];
            arr[j] = arr[j - 1];
            arr[j - 1] = temp;
            j--;
        }
    }
}

//Bubble sort
void bubbleSort(int arr[]){
    for(int i = 7; i > 0; i--){
        for(int j = 0; j < i; j++){
            if(arr[j] > arr[j + 1]){
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
         }
    }
}

//Selection sort
void selectionSort(int arr[]){
    for(int i = 0; i < 7; i++){
        int min = i;
        for(int j = i + 1; j < 8; j++){
            if(arr[min] > arr[j]){
                min = j;
            }
        }
        int temp = arr[i];
        arr[i] = arr[min];
        arr[min] = temp;
    }
}

//shell Sort
void shellSort(int arr[], int n){
    int gap = n / 2;
    while(gap > 0){
        for(int i = gap; i < n; i++){
            int j = i;
            while(j >= gap && arr[j - gap] > arr[j]){
                int temp = arr[j - gap];
                arr[j - gap] = arr[j];
                arr[j] = temp;
                j -= gap;
            }
        }
        gap /= 2;
    }
}

//Merge sort
void merge(int arr[], int low, int mid, int high){
    int nl = mid - low + 1; //length of left subarray
    int nr = high - mid; //length of right subarray

    int L[nl]; //a new left subarray
    int R[nr]; //a new right subarray

    for(int i = 0; i < nl; i++){ //copying into left subarray
        L[i] = arr[low + i];
    }
    for (int j = 0; j < nr; j++) //copying into right subarray 
    {
        R[j] = arr[j + mid + 1];
    }

    int i = 0 ,j = 0; //initialize i and j to 0
    int k = low; //side pointer which will keep track of p index
    
    while (i < nl && j < nr)
    {
        if(L[i] <= R[j]){
            arr[k] = L[i];
            i++;
        }
        else{
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < nl) //Remaining left array
    {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < nr) //Remaining right array
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[],int p, int r){
    if (p >= r)
    {
        return;
    }
    int q = (p + r)/2; //finding the mid element

    mergeSort(arr,p,q); //recursively calling mergesort
    mergeSort(arr,q+1,r); //recursively calling mergesort
    merge(arr,p,q,r); //calling merge fuction
}

//Quick Sort
int pivot(int arr[], int low, int high){
    int pivot = arr[low];
    int i = low;
    int j = high;

    while (i < j)
    {
        while (arr[i] <= pivot && i < high)
        {
            i++;
        }
        while (arr[j] > pivot && j > low)
        {
            j--;
        }
        if (i < j)
        {
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[low];
    arr[low] = arr[j];
    arr[j] = temp;
    return j;
}
void quickSort(int arr[], int low, int high){
    if (low < high)
    {
        int pivotPoint = pivot(arr,low,high);
        quickSort(arr,low,pivotPoint - 1);
        quickSort(arr,pivotPoint + 1, high); 
    }
    
}

//heap sort
void maxHeapify(int arr[], int i,int n){
    int largest = i;
    int left = 2*i + 1;
    int right = 2*i + 2;

    if (left <n && arr[left] > arr[largest])
        largest = left;

    if(right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i)
    {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        maxHeapify(arr,largest,n);
    }
}

void buildHeap(int arr[], int n){
    for (int i = n/2 - 1; i >= 0; i--)
    {
        maxHeapify(arr, i, n);
    }
}

void heapSort(int arr[], int n){
    buildHeap(arr,n);
    for (int i = n-1; i > 0; i--)
    {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        maxHeapify(arr, 0, i);
    } 
}

//counting sort
void countingSort(int arr[], int n, int k) {
    int *B = (int *)malloc((n + 1) * sizeof(int));   // Output array 
    int *C = (int *)malloc((k + 1) * sizeof(int));   // Count array

    for (int i = 0; i <= k; i++) { //Initialize count array C[0..k] = 0
        C[i] = 0;
    }

    for (int j = 0; j < n; j++) { //Count frequencies
        C[arr[j]]++;
    }

    for (int i = 1; i <= k; i++) { //C[i] = number of elements <= i
        C[i] += C[i - 1];
    }

    for (int j = n-1; j >= 0; j--) { //Place into output array B (right-to-left for stability)
        B[C[arr[j]] - 1] = arr[j];
        C[arr[j]] = C[arr[j]] - 1;   // decrement to handle duplicates
    }

    for (int i = 0; i < n; i++) { //Copy B back to A (if needed)
        arr[i] = B[i];
    }
    free(B);
    free(C);
}

//radix sort
void countingSortByDigit(int arr[], int n, int exp) {
    int output[n];
    int count[10] = {0}; // Digits 0–9

    for (int i = 0; i < n; i++) { // Count digit frequencies
        int digit = (arr[i] / exp) % 10;
        count[digit]++;
    }

    for (int i = 1; i < 10; i++) {// Prefix sums
        count[i] += count[i - 1];
    }

    for (int i = n - 1; i >= 0; i--) { // Place into output
        int digit = (arr[i] / exp) % 10;
        output[count[digit] - 1] = arr[i];
        count[digit]--;
    }

    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
}

void radixSort(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) max = arr[i];
    }

    for (int exp = 1; max / exp > 0; exp *= 10) {
        countingSortByDigit(arr, n, exp);
    }
}

//Merge sort without using recursion

// Structure for stack frame
typedef struct {
    int l, r;
    int toMerge; // 0 = divide step, 1 = merge step
} Frame;

// Merge function
void mergeStack(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    free(L);
    free(R);
}

// Iterative merge sort using stack
void mergeSortIterativeStack(int arr[], int n) {
    Frame *stack = (Frame *)malloc(n * 2 * sizeof(Frame));
    int top = -1;

    // Push the whole array
    stack[++top] = (Frame){0, n - 1, 0};

    while (top >= 0) {
        Frame cur = stack[top--];

        if (cur.l >= cur.r) continue;

        if (cur.toMerge) {
            int mid = (cur.l + cur.r) / 2;
            mergeStack(arr, cur.l, mid, cur.r);
        } else {
            int mid = (cur.l + cur.r) / 2;

            // First push merge marker
            stack[++top] = (Frame){cur.l, cur.r, 1};

            // Then push right half
            stack[++top] = (Frame){mid + 1, cur.r, 0};

            // Then push left half
            stack[++top] = (Frame){cur.l, mid, 0};
        }
    }
    free(stack);
}

//merge sort using loop
void mergeLoop(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    free(L);
    free(R);
}

// Iterative (bottom-up) merge sort
void mergeSortIterative(int arr[], int n) {
    // size = subarray size to merge
    for (int size = 1; size < n; size *= 2) {
        // pick starting point of subarrays
        for (int left = 0; left < n - 1; left += 2 * size) {
            int mid = left + size - 1;
            int right = (left + 2 * size - 1 < n - 1) ? left + 2 * size - 1 : n - 1;

            if (mid < right) // merge only if valid
                mergeLoop(arr, left, mid, right);
        }
    }
}

int main(){
    int arr[] = {4, 3, 6, 2, 1, 7, 5, 11};
    int n = 8;
    // insertion(arr);
    // bubbleSort(arr);
    // selectionSort(arr);
    // shellSort(arr,8);
    // mergeSort(arr,0,7);
    // quickSort(arr,0,7);
    //heapSort(arr,8);
    // int k = 11;//max number in array
    // countingSort(arr,n,k);
    //radixSort(arr,n);
    //mergeSortIterativeStack(arr,n);
    mergeSortIterative(arr,n);
    for (int i = 0; i < 8; i++)
    {
        printf("%d ", arr[i]);
    }
}