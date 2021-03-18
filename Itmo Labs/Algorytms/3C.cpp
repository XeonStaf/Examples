#include <fstream>

using namespace std;

int main()
{
    ifstream in("radixsort.in");
    ofstream out("radixsort.out");
    int m, n, k;
    in >> n >> m >> k;
    string arr[n], arrReady[n];
    int arrCount[26];
    int index = m - 1, indexR;

    for (int i = 0; i < n; i++)
        in >> arr[i];

    for(int j = 0; j < k; j++)
    {
        for (int i = 0; i < 26; i++)
            arrCount[i] = 0;
        for (int i = 0; i < n; i++)
            arrCount[int(arr[i][index]) - int('a')]++;
        for( int i = 1; i < 26; i++)
            arrCount[i] += arrCount[i - 1];
        for (int i = n - 1; i >= 0; i--)
        {
            indexR = int(arr[i][index]) - int('a');
            arrReady[arrCount[indexR] - 1] = arr[i];
            arrCount[indexR]--;
        }
        index--;
        for (int i = 0; i < n; i++)
            arr[i] = arrReady[i];
    }

    for(int i = 0; i < n; i++)
        out << arrReady[i] << "\n";

    return 0;
}
