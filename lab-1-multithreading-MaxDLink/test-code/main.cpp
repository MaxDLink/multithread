// main.cpp
#include "test-set-one.h"
#include "test-set-two.h"
#include "test-set-three.h"

int main() {
    test_set_one();
    // Call function from test-set-two.cpp here
    test_set_two();
    // Call function from test-set-three.cpp here
    test_set_three();

    return 0;
}
