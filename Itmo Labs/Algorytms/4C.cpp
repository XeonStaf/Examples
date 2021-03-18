#include <fstream>
#include <iostream>
#include <string>
using namespace std;

struct Stack
{
    int P = -1;
    char Data[10000];
    void Push(char x)
    {
        P++;
        Data[P] = x;
    };

    char Insert()
    {
        if (P != -1)
        {
            P--;
            return Data[P + 1];
        }
        else
        {
            return -1;
        }
    };
};

int main()
{
    ifstream in("brackets.in");
    ofstream out("brackets.out");
    Stack Task;
    string S;
    char q;
    bool ok;

    while (getline(in, S))
    {
        ok = true;
        for (int k = 0; k < S.size(); k++)
        {
            if (S[k] == '(' || S[k] == '[')
                Task.Push(S[k]);
            else
            {
                q = Task.Insert();
                if (!((S[k] == ')' && q == '(') || (S[k] == ']' && q == '[')))
                    ok = false;
            }
        }
        if (ok && Task.P == -1)
            out << "YES\n";
        else
            out << "NO\n";
        Task.P = -1;
    }
    in.close();
    out.close();
    return 0;
}
