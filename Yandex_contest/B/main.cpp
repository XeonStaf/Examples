#include <fstream>

int main()
{
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");

    int result = 0;
    int N, lenghtNow = 0, x;
    in >> N;
    for (int i = 0; i < N; i++)
    {
        in >> x;
        if (x == 1)
            lenghtNow++;
        else
        {
            if (lenghtNow > result)
                result = lenghtNow;
            lenghtNow = 0;
        } 
    }
    if (lenghtNow > result)
        result = lenghtNow;
    out << result;
}