#include <fstream>

using namespace std;

void QSort(int Array[], int left, int right, int k)
{
    int key = Array[(left + right) / 2];
    int i = left;
    int j = right;
    while (i <= j)
    {
        while (Array[i] < key)
            i++;
        while (Array[j] > key)
            j--;
        if (i <= j)
        {
            swap(Array[i], Array[j]);
            i++;
            j--;
        }
    }
    if (left <= k and k <= j)
        QSort(Array, left, j, k);
    if (i <= k and k <= right)
        QSort(Array, i, right, k);
}

int main()
{
    fstream in("kth.in");
    fstream out("kth.out");
    int A, B, C, n, k;
    in >> n >> k >> A >> B >> C;
    int Array[n];
    in >> Array[0] >> Array[1];

    for (int i = 2; i < n; i++)
        Array[i] = A * Array[i - 2] + B * Array[i - 1] + C;
    QSort(Array, 0, n - 1, k - 1);
    
    out << Array[k - 1];
    return 0;
}
