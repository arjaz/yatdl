#pragma once

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/string.hpp>

class Task {
private:
    std::string name;
    std::string content;

    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & name;
        ar & content;
    }

public:
    Task();
    explicit Task(std::string name);
    Task(std::string name, std::string content);
    Task(const Task &that);
    Task(Task &&that);
    Task &operator=(const Task &that);

    std::string getName() const;
    void setName(std::string name);
    std::string getContent() const;
    void setContent(std::string content);

    virtual ~Task();
};
