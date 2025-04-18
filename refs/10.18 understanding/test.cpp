#include <random>

template <class T>
T generate_input();

template <>
int generate_input<int>() {
}

namespace fuzzer {
template <class... T>
void And(T...) {}

}  // namespace fuzzer

class A {
public:
    void f(int) {}
    void g() {}
};

void f() {}

void g() {}

int main() {
    int min = 10;
    int max = 100;

    // Create a random number generator
    std::random_device rd;                            // Seed generator
    std::mt19937 gen(rd());                           // Mersenne Twister engine seeded with random_device
    std::uniform_int_distribution<> distr(min, max);  // Define the distribution range

    int a = 0;

    // Generate random numbers
    for (int i = 0; i < 10; ++i) {
        a = distr(gen);
    }

    return 1;
}
