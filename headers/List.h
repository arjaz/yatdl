#pragma once

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/vector.hpp>
#include "Task.h"

class List {
private:
    std::vector<Task> tasks;
    
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & tasks;
    }

public:
    List();
    List(std::vector<Task> tasks);
    List(const List &that);
    List(List &&that);
    List &operator=(const List &that);

    void removeTask(int i);
    std::vector<Task> getTasks() const;
    void setTasks(std::vector<Task> tasks);
    Task getTask(int i) const;
    Task* getTaskp(int i);
    int size() const;
    void addTask(Task task);

    void save(std::string path);
    void load(std::string path);

    virtual ~List();
};
