#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <any>
#include "utils/utils.h"
#include "demos/importsTest.h"


using std::cout, std::endl, std::cin, std::string;
using std::vector;
using std::array;

int main()
{
    std::any i{1};
    std::any d{3.0111};
    std::any f{3.0111f};
    std::any s{"abcd"};
    cout << (i.type() == typeid(int)) << endl;
    cout << (d.type() == typeid(double)) << endl;
    cout << (f.type() == typeid(float)) << endl;
    cout << (s.type() == typeid(const char *)) << endl;
    importsTest();
    return 0;
}
