#pragma once

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/vector.hpp>
#include "Task.h"

class List {
private:
    std::string name;
    std::vector<Task> tasks;
    
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & name;
        ar & tasks;
    }

public:
    List();
    explicit List(std::string name);
    List(std::string name, std::vector<Task> tasks);
    List(const List &that);
    List(List &&that);
    List &operator=(const List &that);

    std::string getName() const;
    void setName(std::string name);
    std::vector<Task> getTasks() const;
    void setTasks(std::vector<Task> tasks);
    Task getTask(int i) const;
    int size() const;
    void addTask(Task task);
    void addTask(std::string name, std::string content);

    void save(std::string path);
    void load(std::string path);

    virtual ~List();
};
