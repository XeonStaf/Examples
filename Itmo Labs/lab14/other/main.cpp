#include <fstream>

using namespace std;

int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");
    int x, row = 1, width = 12;
    while(in >> x)
    {
        if(x == 0)
            out << 0;
            else
            out << 1;
        if(row == width)
        {
            row = 0;
            out << endl;
        }
        row++;
            
    }
}