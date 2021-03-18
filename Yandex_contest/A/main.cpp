#include <fstream>

int main()
{
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");
    std::string J, S;

    in >> J >> S;
    int Count[33];
    int result = 0;
    for(int i = 0; i < 33; i++)
        Count[i] = 0;
    for(int i = 0; i < J.size(); i++)
        Count[J[i] - 'a']++;
    for(int i = 0; i < S.size(); i++)
        if(Count[S[i] - 'a'] > 0)
            result++;
    out << result;
    return 0;
}