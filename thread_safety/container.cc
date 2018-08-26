#include <map>
#include <thread>

#include "utils/mutex.h"

static Mutex g_mutex;
static std::map<int, int> g_map;

void this_will_probably_crash_or_hang() {
    for (int i = 0; i < 10000; i++) {
        g_map[i] = i;
    }
}

void this_will_work() {
    for (int i = 0; i < 10000; i++) {
        g_mutex.Lock();
        g_map[i] = i;
        g_mutex.Unlock();
    }
}

int main() {
    std::thread th[10];

    for (auto &i : th) {
        std::thread t([]() {  this_will_work(); });
        i.swap(t);
    }

    for (auto &i : th) {
        i.join();
    }

    return 0;
}