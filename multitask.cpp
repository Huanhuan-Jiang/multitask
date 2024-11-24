#include <iostream>
#include <atomic>

std::atomic<bool> turn(0); // Flag to control which function runs

void my_sched_yield() {
    // This function can be used to yield control
    // In this case, it just switches the running flag
    turn = (turn + 1) % 2;
}

void hello_world() {
    std::cout << "Hello World started!" << std::endl;
    for (int i = 0; i < 10; i++) {
        while (turn == 0) { // Check if it's this function's turn
            std::cout << "Hello World: " << i << std::endl;
            my_sched_yield(); // Yield control
        }
    }
    std::cout << "Hello World finished!" << std::endl;
}

void good_morning() {
    std::cout << "Good Morning started!" << std::endl;
    for (int i = 0; i < 10; i++) {
        while (turn != 1) { // Check if it's this function's turn
            std::cout << "Good Morning: " << i << std::endl;
            my_sched_yield(); // Yield control
        }
    }
    std::cout << "Good Morning finished!" << std::endl;
}

int main() {
    // Start both functions in a way that they can yield control to each other
    hello_world();
    good_morning();
    
    return 0;
}