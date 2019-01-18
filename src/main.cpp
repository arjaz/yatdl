#include <iostream>
#include <fstream>
#include <stdexcept>
#include <boost/filesystem.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/string.hpp>
#include <boost/program_options.hpp>

std::list<std::string> loadList(std::string PATH) {
    std::list<std::string> result;
    std::ifstream ifs(PATH);
    boost::archive::text_iarchive ia(ifs);
    ia >> result;
    return result;
}

void saveList(std::list<std::string> list, std::string PATH) {
    std::ofstream ofs(PATH);
    boost::archive::text_oarchive oa(ofs);
    oa << list;
}

int main(int argc, char *argv[]) {
    namespace po = boost::program_options;
    namespace fs = boost::filesystem;

    std::string const home = getenv("HOME");
    std::string const PATH(home + "/.arjaz/yatdl/lst.obj");
    std::string const DOT_PATH(home + "/.arjaz/");
    std::string const DOT_APP_PATH(home + "/.arjaz/yatdl/");
    if (!fs::exists(DOT_PATH)) {
        fs::create_directory(DOT_PATH);
    }
    if (!fs::exists(DOT_APP_PATH)) {
        fs::create_directory(DOT_APP_PATH);
    }

    po::options_description desc("Allowed options");
    desc.add_options()
        ("help,h", "Prints help message")
        ("load,l", "Loads list")
        ("delete,d", "Deletes list")
        ("add,a", po::value<std::string>(), "Adds task")
        ("remove,r", po::value<int>(), "Removes task")
        ;
    std::list<std::string> tasks;

    try {
        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);

        if (vm.count("help")) {
            std::cout << desc << std::endl;
            return 0;
        }

        if (vm.count("delete")) {
            std::remove(PATH.c_str());
            std::cout << "List was deleted" << std::endl;
            return 0;
        }

        try {
            tasks = loadList(PATH);
        } catch (const boost::archive::archive_exception &e) {}

        if (vm.count("load")) {
            size_t i = 0;
            for (const auto &x : tasks) {
                std::cout << "Task " << i++ << ":\t" << x << std::endl;
            }
            return 0;
        }

        if (vm.count("add")) {
            tasks.push_back(vm["add"].as<std::string>());
            saveList(tasks, PATH);
            return 0;
        }

        if (vm.count("remove")) {
            try {
                size_t rm = vm["remove"].as<int>();
                if (!(rm >= 0 && rm < tasks.size())) throw(std::out_of_range("balh"));
                tasks.erase(next(tasks.begin(), rm));
            } catch (const std::out_of_range &e) {
                std::cerr << "Error: no task with given number found" << std::endl;
            }
            saveList(tasks, PATH);
            return 0;
        }
    } catch (const po::error &e) {
        std::cerr << "Error: " << e.what() << std::endl << std::endl;
        std::cerr << desc << std::endl;
    }
    return 0;
}
