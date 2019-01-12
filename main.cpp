#include <iostream>
#include <string>
#include "Task.h"
#include "List.h"

std::string about() {
    return "This is a console todo list used to store different tasks.";
}

int main(int argc, char *argv[]) {

    std::cout << argc << std::endl;

    if (argc == 1) {
        std::cout << about() << std::endl;
        return 0;
    }

    return 0;
}
