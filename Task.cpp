#include <boost/serialization/string.hpp>
#include "Task.h"

Task::Task() = default;

Task::Task(std::string name) : name(name), content("") {}

Task::Task(std::string name, std::string content) : name(name), content(content) {}

Task::Task(const Task &that) = default;

Task::Task(Task &&that) = default;

Task &Task::operator=(const Task &that) = default;

std::string Task::getName() const {
    return name;
}

void Task::setName(std::string name) {
    this->name = name;
}

std::string Task::getContent() const {
    return content;
}

void Task::setContent(std::string content) {
    this->content = content;
}

Task::~Task() = default;
