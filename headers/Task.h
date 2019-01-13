#pragma once

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/string.hpp>

class Task {
private:
    std::string content;

    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & content;
    }

public:
    Task();
    Task(std::string content);
    Task(const Task &that);
    Task(Task &&that);
    Task &operator=(const Task &that);

    std::string getContent() const;
    void setContent(std::string content);

    virtual ~Task();
};
