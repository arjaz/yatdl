#pragma once

#include <vector>
#include <string>
#include "Task.h"

class List {
private:
    std::string name;
    std::vector<Task> tasks;

public:
    List();
    explicit List(std::string name);
    List(std::string name, std::vector<Task> tasks);

    std::vector<Task> getTasks() const;
    void setTasks(std::vector<Task> tasks);
    Task getTask(int i) const;
    int size() const;
    void addTask(Task task);

    virtual ~List();
};
