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

int main(int argc, char* argv[])
{
    typedef std::function<void(const std::string&, const int&d)> ExampleFunction;
    Object instance;
    std::string str("World");
    int d = 6;
    ExampleFunction f = std::bind(&Object::hello, &instance,
                                  std::placeholders::_1);

    //instance.hello(str)
    f(str, d);

    f = std::bind(&goodbye, std::placeholders::_1, std::placeholders::_2);
    //goodbye(str, d)
    f(str, d);
    return 0;
}