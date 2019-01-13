#include <fstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include "List.h"
#include "Task.h"

List::List() = default;

List::List(std::vector<Task> tasks) : tasks(tasks) {}

List::List(const List &that) = default;

List::List(List &&that) = default;

List &List::operator=(const List &that) = default;

void List::removeTask(int i) {
    tasks.erase(tasks.begin() + i);
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

Task* List::getTaskp(int i) {
    return &tasks[i];
}

int List::size() const {
    return tasks.size();
}

void List::addTask(Task task) {
    tasks.push_back(task);
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
