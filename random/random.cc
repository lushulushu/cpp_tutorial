#include <vector>
#include <cstdlib>
#include <string>
#include <cstring>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

bool RandomSelectAndClean(std::vector<std::string> *list, size_t count) {
    bool ret = false;
    if (nullptr != list && !list->empty()) {
        ret = true;
        size_t size = list->size();
        if (size > count) {
            for (size_t i = 0; i < count; ++i) {
                std::srand(time(nullptr) + clock());
                size_t random = std::rand() % (size - i);
                std::swap(list[0][random], list[0][size - i - 1]);
            }
            list->erase(list->begin(), list->begin() + size - count);
        }
    }
    return ret;
}

int main() {
    std::vector<std::string> texts;
    char headStr[10] = "test_";
    for (int i = 0; i < 8; i++) {
        char tail[5];
        char *tail_char = itoa(i, tail, 10);
        texts.push_back(strcpy(headStr, tail_char));
    }
    size_t count = 3;
    RandomSelectAndClean(&texts, count);
    return 0;
}