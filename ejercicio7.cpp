#include <iostream>
#include <pthread.h>
#include <time.h>

int a[20];

void merge(int low, int mid, int high)
{
    int* left = new int[mid - low + 1];
    int* right = new int[high - mid];


    int n1 = mid - low + 1;
    int n2 = high - mid;
    int i;
    int j;

    for (i = 0; i < n1; i++)
        left[i] = a[i + low];

    for (i = 0; i < n2; i++)
        right[i] = a[i + mid + 1];

    int k = low;
    i = j = 0;


    while (i < n1 && j < n2) {
        if (left[i] <= right[j])
            a[k++] = left[i++];
        else
            a[k++] = right[j++];
    }


    while (i < n1) {
        a[k++] = left[i++];
    }


    while (j < n2) {
        a[k++] = right[j++];
    }
}

// funcion merge
void merge_sort(int low, int high)
{
    int mid = low + (high - low) / 2;
    if (low < high) {
        merge_sort(low, mid);
        merge_sort(mid + 1, high);
        merge(low, mid, high);
    }
}


using namespace std;


int part = 0;

void* merge_sort(void* arg)
{
    int thread_part = part++;

    int low = thread_part * (20 / 4);
    int high = (thread_part + 1) * (20 / 4) - 1;

    int mid = low + (high - low) / 2;
    if (low < high) {
        merge_sort(low, mid);
        merge_sort(mid + 1, high);
        merge(low, mid, high);
    }
}


int main()
{
    // array aleatoreo
    for (int i = 0; i < 20; i++)
        a[i] = rand() % 100;


    clock_t t1, t2;

    t1 = clock();
    pthread_t threads[4];

    for (unsigned int & thread : threads)
        pthread_create(&thread, nullptr, merge_sort,
                       (void*)nullptr);

    for (unsigned int thread : threads)
        pthread_join(thread, nullptr);


    merge(0, (20 / 2 - 1) / 2, 20 / 2 - 1);
    merge(20/ 2, 20/2 + (20-1-20/2)/2, 20 - 1);
    merge(0, (20 - 1)/2, 20 - 1);

    t2 = clock();


    for (int i : a)
        cout << i << " ";


    cout << "\nTime taken: " << (t2 - t1) /(double)CLOCKS_PER_SEC << endl;

    return 0;
}