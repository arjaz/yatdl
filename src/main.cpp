#include <iostream>
#include <string>
#include <cxxopts.hpp>
#include "Task.h"
#include "List.h"

int main(int argc, char *argv[]) {
    cxxopts::Options options(argv[0], "Terminal todo list application");
    options
        .positional_help("[optional args]")
        .show_positional_help();

    options.add_options()
        ("d,delete", "Delete list")
        ("l,load", "Load current tasks")
        ("a,add", "Add task", cxxopts::value<std::string>())
        ("r,remove", "Remove task by index", cxxopts::value<int>())
        ("p,path", "Specify custom path to list", cxxopts::value<std::string>()->default_value("lst.obj"))
        ;

    auto result = options.parse(argc, argv);

    std::string path;
    List lst;
   
    path = result["path"].as<std::string>();

    try {
        lst.load(path);
    } catch (boost::archive::archive_exception &e) {}

    if (result.count("delete")) {
        lst = List();
        lst.save(path);
    }

    if (result.count("remove")) {
        lst.removeTask(result["remove"].as<int>());
    }

    if (result.count("add")) {
        lst.addTask(result["add"].as<std::string>());
    }
    
    if (result.count("load")) {
        for (int i = 0; i < lst.size(); ++i) {
            std::cout << "Task " << i << ":\t" << lst.getTask(i).getContent() << std::endl;
        }
    }

    lst.save(path);

    return 0;
}
