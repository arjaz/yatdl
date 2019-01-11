#include <string>
#include "List.h"
#include "Task.h"

List::List() : name(""), tasks(std::vector<Task>()) {}

List::List(std::string name) : name(name), tasks(std::vector<Task>()) {}

List::List(std::string name, std::vector<Task> tasks) : name(name), tasks(tasks) {}

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

List::~List() = default; 
