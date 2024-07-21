#include <iostream>
#include <sstream>

int main()
{
    std::string str = "123 45.6 789";
    std::stringstream ss(str);

    int a;
    float b;

    ss >> a; // 提取整数
    ss >> b; // 提取浮点数

    std::cout << "整数: " << a << std::endl;
    std::cout << "浮点数: " << b << std::endl;

    return 0;
}
