#include <fstream>

int main()
{
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");
    long long int x, xPrev;
    long long int N;
    in >> N;
    if (N < 1)
        return 0;
    in >> x;
    out << x << "\n";
    for (int i = 0; i < N - 1; i++)
    {
        xPrev = x;
        in >> x;
        if (x != xPrev)
            out << x << "\n";
    }

}