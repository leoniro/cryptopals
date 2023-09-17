#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
    vector<bool> v1 = {false, false, true, true};
    vector<bool> v2 = {false, true, false, true};
    cout << v1;
    return 0;
}

void hello()
{
    vector<string> msg {"Hello", "C++", "World", "from", "VS Code", "and the C++ extension!"};
    
    for (const string& word : msg)
    {
        cout << word << " ";
    }
    cout << endl;
}

int char2int(char c)
{
    
    return c;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &v) {
  for (const auto &x : v) {
    os << '[' << x << ']';
  }
  return os;
}