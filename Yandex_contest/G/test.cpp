#include <fstream>
#include <iostream>

using namespace std;
int N = -1;
int main()
{
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");
    in >> N;
    cout << N;
}