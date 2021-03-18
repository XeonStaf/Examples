#include <fstream>
#include <set>
#include <iostream>
std::set <std::string> Answer;
int N;
void create (std::string x, char y)
{
    int open = 0, free = 0;
    x = x + y;
    int size = x.size();
    if (size == 2 * N)
    {
        Answer.insert(x);
    }
    else
    {
        for (int i = 0; i < size; i++)
            if (x[i] == '(')
            {
                open++;
                free++;
            }
            else
                free--;
        if (free > 0)
            create(x, ')');
        if (open < N)
            create(x, '(');  
    }
}

int main()
{
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");
    in >> N;
    std::string x = "";
    create(x, '(');
    for (std::set <std::string>::iterator it = Answer.begin(); it != Answer.end(); it++)
        out << *it << "\n";
}