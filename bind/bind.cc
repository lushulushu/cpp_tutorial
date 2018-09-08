#include <functional>
#include <string>
#include <iostream>

void goodbye(const std::string& s, const int& d)
{
    std::cout << "Goodbye " << s << " and " << d << '\n';
}

class Object {
public:
    void hello(const std::string& s)
    {
        std::cout << "Hello " << s << '\n';
    }
};

void isPlaceholderTest() {
    std::cout << std::is_placeholder<decltype(std::placeholders::_1)>::value << '\n';
    std::cout << std::is_placeholder<decltype(std::placeholders::_2)>::value << '\n';
    std::cout << std::is_placeholder<int>::value << '\n';
}

int main(int argc, char* argv[])
{
    typedef std::function<void(const std::string&, const int&d)> ExampleFunction;
    Object instance;
    std::string str("World");
    int d = 6;
    ExampleFunction f = std::bind(&Object::hello, &instance, std::placeholders::_1);

    //instance.hello(str)
    f(str, d);

    f = std::bind(&goodbye, std::placeholders::_1, std::placeholders::_2);
    //goodbye(str, d)
    f(str, d);

    std::cout << std::boolalpha << "--haha--" << "\n";
    std::cout << std::is_bind_expression<decltype(f)>::value << '\n'; //输出不该是true吗？

    auto increase_int = std::bind (std::plus<int>(),std::placeholders::_1,1);
    std::cout << std::is_bind_expression<decltype(increase_int)>::value << '\n';
    return 0;
}