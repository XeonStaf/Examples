#include <fstream>

using namespace std;


void MaxHeapify(int arr[], int i, int &n)
{
    int largest;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < n and arr[l] > arr[i])
        largest = l;
    else
        largest = i;
    if (r < n and arr[r] > arr[largest])
        largest = r;
    if (largest != i)
    {
        swap(arr[i], arr[largest]);
        MaxHeapify(arr, largest, n);
    }
}

void BuildMaxHeap(int arr[], int &n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        MaxHeapify(arr, i, n);
}

void HeapSort(int arr[], int &n)
{
    BuildMaxHeap(arr, n);
    for (int i = n - 1; i > 0; i--)
    {
        swap(arr[0], arr[i]);
        n--;
        MaxHeapify(arr, 0, n);
    }
}
int main()
{
    int n,n_cpy;
    ifstream in("sort.in");
    ofstream out("sort.out");
    in >> n;
    n_cpy = n;
    int arr[n];

    for (int i = 0; i < n; i++)
        in >> arr[i];

    HeapSort(arr, n);

    for (int i = 0; i < n_cpy; i++)
        out << arr[i] << " ";
    return 0;
}
