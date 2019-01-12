#include <iostream>
#include <string>
#include "Task.h"
#include "List.h"

constexpr const char* about() {
    return "This is a console todo list used to store different tasks.";
}

constexpr const char* errmsg() {
    return "Type 'h' for help, 'r' for reading, 'w' <TASK_NAME> <TASK_CONTENT> for writing, 'd' for deleting the list.";
}

constexpr const char* errload() {
    return "List is not created.";
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        std::cout << about() << std::endl;
        return 0;
    }
    
    List lst;
    lst.setName("Fuck");
    lst.addTask("Kiss", "Kiss Helga");
    lst.addTask("App", "Create Qt youtube desktop application");
    lst.save("lst.obj");

    switch(*argv[1]) {
        case 'r':
            try {
                lst.load("lst.obj");
            }
            catch (boost::archive::archive_exception &e) {
                std::cout << errload() << std::endl << errmsg() << std::endl;
                return -1;
            }
            for (auto x: lst.getTasks()) {
                std::cout << x.getName() << ":\t" << x.getContent() << std::endl;
            }
            break;
        case 'w':
            if (argc == 2) {
                std::cout << errmsg() << std::endl;
            }
            break;
        case 'd':
            remove("lst.obj");
            std::cout << "List was deleted" << std::endl;
            break;
        case 'h':
            std::cout << about() << std::endl << errmsg() << std::endl;
            break;
        default:
            std::cout << errmsg() << std::endl;
            break;
    }

    return 0;
}
