#include <iostream>
#include <fstream>
#include <stdexcept>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/string.hpp>
#include <boost/program_options.hpp>

std::list<std::string> loadList(std::string path) {
    std::list<std::string> result;
    std::ifstream ifs(path);
    boost::archive::text_iarchive ia(ifs);
    ia >> result;
    return result;
}

void saveList(std::list<std::string> list, std::string path) {
    std::ofstream ofs(path);
    boost::archive::text_oarchive oa(ofs);
    oa << list;
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
    std::list<std::string> tsks;

    try {
        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);

        if (vm.count("help")) {
            std::cout << desc << std::endl;
            return 0;
        }

        if (vm.count("path")) {
            path = vm["path"].as<std::string>();
        }

        if (vm.count("delete")) {
            std::remove(path.c_str());
            std::cout << "List at " << path << " was deleted" << std::endl;
            return 0;
        }

        try {
            tsks = loadList(path);
        } catch (const boost::archive::archive_exception &e) {}

        if (vm.count("load")) {
            int i = 0;
            for (const auto &x : tsks) {
                std::cout << "Task " << i++ << ":\t" << x << std::endl;
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
                size_t rm = vm["remove"].as<int>();
                if (!(rm >= 0 && rm < tsks.size())) throw(std::out_of_range("balh"));
                tsks.erase(next(tsks.begin(), rm));
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
