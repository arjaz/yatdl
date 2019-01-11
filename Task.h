#pragma once

#include <string>

class Task {
private:
    std::string const name;
    std::string content;

public:
    Task();
    explicit Task(std::string name);
    Task(std::string name, std::string content);

    std::string getName() const;
    std::string getContent() const;
    void setContent(std::string content);

    virtual ~Task();
};
