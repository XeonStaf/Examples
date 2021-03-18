#include <fstream>

using namespace std;

int n1 = 0;
int arr[1000001];
int pushIndex[1000001];
ifstream in("priorityqueue.in");
ofstream out("priorityqueue.out");

void Heapify(int i)
{
    int smallest;
    int l = 2 * i;
    int r = 2 * i + 1;
    if (l <= n1 and arr[l] < arr[i])
        smallest = l;
    else
        smallest = i;
    if (r <= n1 and arr[r] < arr[smallest])
        smallest = r;
    if (smallest != i)
    {
        swap(arr[i], arr[smallest]);
        Heapify(smallest);
    }
}

void extractMin()
{
    if (n1 < 1)
        out << "*\n";
    else
    {
        out << arr[1] << "\n";
        arr[1] = arr[n1];
        n1--;
        Heapify(1);
    }
}

void decreaseKey(int i, int y)
{
    arr[i] = y;
    while (i > 1 and arr[i] < arr[i / 2])
    {
        swap(arr[i], arr[i / 2]);
        i = i / 2;
    }
}

void push(int x)
{
    n1++;
    arr[n1] = 2147483647;
    decreaseKey(n1, x);
}

int main()
{
    string q;
    int par, par2, index, c = 1;

    while (in >> q)
    {
        if (q == "push")
        {
            in >> par;
            pushIndex[c] = par;
            push(par);
        }
        if (q == "extract-min")
        {
            extractMin();
            pushIndex[c] = -1;
        }
        if (q == "decrease-key")
        {
            in >> par >> par2;
            for (int i = 1; i <= n1; i++)
                if (arr[i] == pushIndex[par])
                {
                    index = i;
                    break;
                }
            decreaseKey(index, par2);
            pushIndex[par] = par2;
            pushIndex[c] = -1;
        }
        c++;
    }

    in.close();
    out.close();
    return 0;
}
