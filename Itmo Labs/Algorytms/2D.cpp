#include <fstream>

using namespace std;

int main()
{
    int n;
    fstream in("antiqs.in");
    fstream out("antiqs.out");
    in >> n;
    int Array[n];
    for (int i = 0; i < n; i++)
    {
        Array[i] = i + 1;
        swap(Array[i], Array[i / 2]);
    }
    for (int i = 0; i < n; i++)
        out << Array[i] << " ";
    return 0;
}