#include <iostream>
#include <fstream>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/string.hpp>
#include <boost/program_options.hpp>

std::vector<std::string> loadList(std::string path) {
    std::vector<std::string> result;
    try {
        std::ifstream ifs(path);
        boost::archive::text_iarchive ia(ifs);
        ia >> result;
    } catch (boost::archive::archive_exception) {
        std::cerr << "Error: file " << path << " is not accessible" << std::endl;
    }
    return result;
}

void saveList(std::vector<std::string> list, std::string path) {
    try {
        std::ofstream ofs(path);
        boost::archive::text_oarchive oa(ofs);
        oa << list;
    } catch (boost::archive::archive_exception) {
        std::cerr << "Error: file " << path << " is not accessible" << std::endl;
    }
}

int main(int argc, char *argv[]) {
    namespace po = boost::program_options;

    std::string path("lst.obj");

    po::options_description desc("Allowed options");
    desc.add_options()
        ("help,h", "Prints help message")
        ("load,l", "Loads list")
        ("delete,d", "Deletes list")
        ("add,a", po::value<std::string>(), "Adds task")
        ("remove,r", po::value<int>(), "Removes task")
        ("path,p", po::value<std::string>()->default_value("lst.obj"), "Specifies path")
        ;
    std::vector<std::string> tsks(loadList(path));

    try {
        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);

        if (vm.count("help")) {
            std::cout << desc << std::endl;
            return 0;
        }

        if (vm.count("delete")) {
            saveList(std::vector<std::string>(), path);
            std::cout << "List at " << path << " was deleted" << std::endl;
            return 0;
        }

        if (vm.count("load")) {
            for (size_t i = 0; i < tsks.size(); ++i) {
                std::cout << "Task " << i << ":\t" << tsks.at(i) << std::endl;
            }
            return 0;
        }

        if (vm.count("add")) {
            tsks.push_back(vm["add"].as<std::string>());
            saveList(tsks, path);
            return 0;
        }

        if (vm.count("remove")) {
            try {
                tsks.erase(tsks.begin() + vm["remove"].as<int>());
            } catch (const std::out_of_range &e) {
                std::cerr << "Error: no task with given number found" << std::endl;
            }
            saveList(tsks, path);
            return 0;
        }
    } catch (const po::error &e) {
        std::cerr << "Error: " << e.what() << std::endl << std::endl;
        std::cerr << desc << std::endl;
    }
    return 0;
}
