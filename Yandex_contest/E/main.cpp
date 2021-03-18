#include <fstream>

int main()
{
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");
    std::string A, B;

    bool result = true;
    in >> A >> B;
    if (A.size() != B.size())
    {
        out << 0;
        return 0;
    }
    int size = A.size();
    int Achar[33], Bchar[33];
    for(int i = 0; i < 33; i++)
    {
        Achar[i] = 0;
        Bchar[i] = 0;
    }
    for (int i = 0; i < size; i++)
    {
        Achar[A[i] - 'a']++;
        Bchar[B[i] - 'a']++;
    }
    for(int i = 0; i < 33; i++)
    {
        if(Achar[i] != Bchar[i])
            result = false;
    }
    if (result)
        out << 1;
    else
        out << 0;
    

    
}