//
// Created by clay on 4/9/16.
//

#ifndef NEWANIMAL_MOCKSYSTEM_H
#define NEWANIMAL_MOCKSYSTEM_H

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../System.h"

using namespace ::testing;

class MockSystem : public SystemInterface {
public:
    MOCK_METHOD0(fork, pid_t());
    MOCK_METHOD2(execvp, int(const char*, char *const argv[]));
    MOCK_METHOD3(waitpid, pid_t(pid_t, int*, int));
};

#endif //NEWANIMAL_MOCKSYSTEM_H
