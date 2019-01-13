#include <boost/serialization/string.hpp>
#include "Task.h"

Task::Task() = default;

Task::Task(std::string content) : content(content) {}

Task::Task(const Task &that) = default;

Task::Task(Task &&that) = default;

Task &Task::operator=(const Task &that) = default;

std::string Task::getContent() const {
    return content;
}

void Task::setContent(std::string content) {
    this->content = content;
}

Task::~Task() = default;
