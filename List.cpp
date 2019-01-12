#include <fstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/vector.hpp>
#include "List.h"
#include "Task.h"

List::List() = default;

List::List(std::string name) : name(name), tasks(std::vector<Task>()) {}

List::List(std::string name, std::vector<Task> tasks) : name(name), tasks(tasks) {}

List::List(const List &that) = default;

List::List(List &&that) = default;

List &List::operator=(const List &that) = default;

std::string List::getName() const {
    return name;
}

void List::setName(std::string name) {
    this->name = name;
}

std::vector<Task> List::getTasks() const {
    return tasks;
}

void List::setTasks(std::vector<Task> tasks) {
    this->tasks = tasks;
}

Task List::getTask(int i) const {
    return tasks[i];
}

int List::size() const {
    return tasks.size();
}

void List::addTask(Task task) {
    tasks.push_back(task);
}

void List::addTask(std::string name, std::string content) {
    tasks.push_back(Task(name, content));
}

void List::save(std::string path) {
    std::ofstream ofs(path);

    boost::archive::text_oarchive oa(ofs);
    oa << *this;

    ofs.close();
}

void List::load(std::string path) {
    std::ifstream ifs(path);

    boost::archive::text_iarchive ia(ifs);
    ia >> *this;

    ifs.close();
}

List::~List() = default; 
