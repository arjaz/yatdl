#include <iostream>
#include <fstream>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/string.hpp>
#include <boost/program_options.hpp>

namespace po = boost::program_options;

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

void deleteList(std::vector<std::string> *list, std::string path) {
    list->clear();
    saveList(list, path);
}

void removeElement(std::vector<std::string> *list, int i) {
    list->erase(list->begin() + i);
}

void addElement(std::vector<std::string> *list, std::string element) {
    list->push_back(element);
}

void printList(std::vector<std::string> *list) {
    for (size_t i = 0; i < list->size(); ++i) {
        std::cout << "Task " << i << ":\t" << list->at(i) << std::endl;
    }
}

int main(int argc, char *argv[]) {
    std::string path;
    auto tsks = new std::vector<std::string>(loadList(path));

    po::options_description desc("Allowed options");
    desc.add_options()
        ("help,h", "Prints help message")
        ("load,l", "Loads list")
        ("path,p", po::value<std::string>()->default_value("lst.obj"), "Specifies path")
    ;

    try {

        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);

        if (vm.count("help")) {
            std::cout << desc << std::endl;
            delete tsks;
            return 1;
        }

        saveList(tsks, path);
    } catch (po::error &e) {
        std::cerr << "Eror: " << e.what() << std::endl << std::endl;
        std::cerr << desc << std::endl;
    }
    delete tsks;
    return 0;
}
