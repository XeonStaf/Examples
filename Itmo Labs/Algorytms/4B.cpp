#include <fstream>

using namespace std;

struct queue
{
    int Queue[1000001];
    int PHead = 0;
    int PTail = 0;
    void Push(int x)
    {
        Queue[PTail] = x;
        if (PTail == 1000000)
            PTail = 0;
        else
            PTail++;
    };

    int Insert()
    {
        int x = Queue[PHead];
        if (PHead == 1000000)
            PHead = 0;
        else
            PHead++;
        return x;
    };
};

int main()
{
    ifstream in("queue.in");
    ofstream out("queue.out");
    queue Task;
    int M, x;
    char q;
    in >> M;
    for (int k = 0; k < M; k++)
    {
        in >> q;
        if (q == '+')
        {
            in >> x;
            Task.Push(x);
        }
        else
            out << Task.Insert() << "\n";
    }
    return 0;
}
