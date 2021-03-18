#include <fstream>

using namespace std;

struct CustomStack
{
    int Data[100000];
    int P = -1;
    void Push(int x)
    {
        P++;
        Data[P] = x;
    }

    int Insert()
    {
        P--;
        return Data[P + 1];
    }

    void Calculation(char Operation)
    {
        int A = Insert();
        int B = Insert();
        int result;
        if (Operation == '+')
            result = A + B;
        if (Operation == '-')
            result = B - A;
        if (Operation == '*')
            result = A * B;
        Push(result);
    }
};


int main()
{
    ifstream in("postfix.in");
    ofstream out("postfix.out");
    CustomStack Task;
    string S;
    getline(in, S);
    
    for (int i = 0; i < S.size(); i++)
    {
        if (S[i] >= '0' and S[i] <= '9')
            Task.Push((int)(S[i] - '0'));
        if (S[i] == '+' or S[i] == '-' or S[i] == '*')
            Task.Calculation(S[i]);
    }

    out << Task.Insert();
    return 0;
}
