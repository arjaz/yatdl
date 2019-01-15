#include <iostream>
#include <fstream>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/string.hpp>
#include <cxxopts.hpp>

std::vector<std::string> loadList(std::string path) {
    std::vector<std::string> result;
    try {
        std::ifstream ifs(path);
        boost::archive::text_iarchive ia(ifs);
        ia >> result;
    } catch (boost::archive::archive_exception) {}
    return result;
}

void saveList(std::vector<std::string> *list, std::string path) {
    try {
        std::ofstream ofs(path);
        boost::archive::text_oarchive oa(ofs);
        oa << *list;
    } catch (boost::archive::archive_exception) {}
}

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
    
    path = result["path"].as<std::string>();
    std::cout << path << std::endl;

    auto tsks = new std::vector<std::string>(loadList(path));

    if (result.count("delete")) {
        tsks->clear();
        saveList(tsks, path);
    }

    if (result.count("remove")) {
        tsks->erase(tsks->begin() + result["remove"].as<int>());
    }

    if (result.count("add")) {
        tsks->push_back(result["add"].as<std::string>());
    }
    
    if (result.count("load")) {
        for (unsigned long i = 0; i < tsks->size(); ++i) {
            std::cout << "Task " << i << ":\t" << tsks->at(i) << std::endl;
        }
    }

    saveList(tsks, path);
    delete tsks;

    return 0;
}
