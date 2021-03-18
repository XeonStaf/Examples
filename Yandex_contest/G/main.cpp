#include <fstream>

int Answer = 1001;

struct City
{
    int x;
    int y;
};

int N;

void Go(int now, int need, int past, int last, int *Matrix)
{
    if (Matrix[now * N + need] == 1)
    {
        past++;
        if (Answer > past)
            Answer = past;
        return;
    }

    for (int i = 0; i < N; i++)
        if (i != now && i != last && Matrix[now * N + i] == 1)
            Go(i, need, past + 1, now, Matrix);

}


int main()
{
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");
    in >> N;
    City Citys[N];
    int k, now, need;
    for (int i = 0; i < N; i++)
        in >> Citys[i].x >> Citys[i].y;
    in >> k >> now >> need;
    int Matrix[N * N];
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (abs(Citys[i].x - Citys[j].x) + abs(Citys[i].y - Citys[j].y)  <= k)
                {
                    Matrix[i * N + j] = 1;
                    Matrix[j * N + i] = 1;
                }
                else
                {
                    Matrix[i * N + j] = 0;
                    Matrix[j * N + i] = 0;
                }
    
    Go(now - 1, need - 1, 0, -1, Matrix);

    if (Answer == 1001)
        out << -1;
    else
        out << Answer;
    out.close();
    in.close();
    return 0;         
}