//
// Created by clay on 4/9/16.
//

#ifndef NEWANIMAL_EXECUTOR_H
#define NEWANIMAL_EXECUTOR_H

#include <vector>
#include <map>
#include <string>

#include "System.h"

using namespace std;

class ExecutorInterface {
public:

    virtual void setCli(vector<string>& cli) = 0;
    virtual int run(map<string, string>& parameters) = 0;

};

class Executor : public ExecutorInterface {
private:
    vector<string> command;

    SystemInterface *sys;

public:

    Executor();
    Executor(SystemInterface*);

    virtual void setCli(vector<string>& cli);
    virtual int run(map<string, string>& parameters);

};


#endif //NEWANIMAL_EXECUTOR_H
