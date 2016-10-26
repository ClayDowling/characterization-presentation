//
// Created by Clayton Dowling on 5/20/16.
//

#include <gmock/gmock.h>
#include "../Executor.h"
#include "MockSystem.h"

#include <vector>
#include <string>

using namespace ::testing;
using namespace std;

class testExecutor : public testing::Test {
public:
    unique_ptr<Executor> exe;
    NiceMock<MockSystem> sys;

    vector<string> cli;
    map<string, string> params;

    virtual void SetUp() {
        exe = make_unique<Executor>(&sys);
    }
};

TEST_F(testExecutor, run_withSingleArgCli_execvpCalledWithSingleArg)
{
    cli.push_back("ls");

    EXPECT_CALL(sys, fork())
                .WillOnce(Return(0));
    EXPECT_CALL(sys, execvp(StrEq("ls"), _));
    exe->setCli(cli);
    exe->run(params);
}

TEST_F(testExecutor, run_withSingleArgCli_waitpidCalledWithForkedPid)
{
    cli.push_back("ls");
    EXPECT_CALL(sys, fork())
            .WillOnce(Return(1));
    EXPECT_CALL(sys, waitpid(1, _, _));

    exe->setCli(cli);
    exe->run(params);
}

TEST_F(testExecutor, run_withFixedArguments_execvpCalledWithArgumentList)
{
    char* const* passedCli;

    cli.push_back("ls");
    cli.push_back("-l");
    EXPECT_CALL(sys, fork())
                .WillOnce(Return(0));
    EXPECT_CALL(sys, execvp(StrEq("ls"), _))
            .WillOnce(SaveArg<1>(&passedCli)); // Array matcher goes here

    exe->setCli(cli);
    exe->run(params);

    ASSERT_THAT(passedCli[0], StrEq("ls"));
    ASSERT_THAT(passedCli[1], StrEq("-l"));
}

TEST_F(testExecutor, run_withArgumentMatchingParameter_execvpCalledWithSubstitutedParameter)
{
    char* const* passedCli;

    cli.push_back("ls");
    cli.push_back("@FOLDER");
    params["@FOLDER"] = "/tmp";

    EXPECT_CALL(sys, fork())
            .WillOnce(Return(0));
    EXPECT_CALL(sys, execvp(StrEq("ls"), _))
            .WillOnce(SaveArg<1>(&passedCli)); // Array matcher goes here

    exe->setCli(cli);
    exe->run(params);

    ASSERT_THAT(passedCli[0], StrEq("ls"));
    ASSERT_THAT(passedCli[1], StrEq("/tmp"));
}

TEST_F(testExecutor, run_withArgumentNotMatchingParameter_execvpCalledWithoutSubstitutedParameter)
{
    char* const* passedCli;

    cli.push_back("ls");
    cli.push_back("@FOLDER");
    params["NOTFOLDER"] = "/tmp";

    EXPECT_CALL(sys, fork())
            .WillOnce(Return(0));
    EXPECT_CALL(sys, execvp(StrEq("ls"), _))
            .WillOnce(SaveArg<1>(&passedCli)); // Array matcher goes here

    exe->setCli(cli);
    exe->run(params);

    ASSERT_THAT(passedCli[0], StrEq("ls"));
    ASSERT_THAT(passedCli[1], StrEq("@FOLDER"));
}