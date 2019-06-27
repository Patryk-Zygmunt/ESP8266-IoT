#include <cucumber-cpp/autodetect.hpp>
#include <gtest/gtest.h>

#include <Scheduler.h>
#include <Task.h>
#include <ITimer.h>

using cucumber::ScenarioScope;

struct SchedulerCtx {
    Scheduler *scheduler;
    Task *task;
    ITimer *timer;
    double actTime;
    bool result;
};

GIVEN("^I have added a task into the scheduler for pin number (\\d+)$") {
    REGEX_PARAM(unsigned int, n);
    ScenarioScope<SchedulerCtx> context;


    context->scheduler = new Scheduler();
    context->task = new Task();
    context->timer = new ITimer();
    context->task.pin = n;
}

GIVEN("^I have entered target state as (\\d*)$") {
    REGEX_PARAM(unsigned int, s);
    ScenarioScope<SchedulerCtx> context;

    if(s==0)
    	context->task.targetState = false;
    if(s==1)
    	context->task.targetState = true;
}

GIVEN("^I have entered execution time at (\\d*)$") {
    REGEX_PARAM(double, eT);
    ScenarioScope<SchedulerCtx> context;

    context->task.executionTime = eT;
    context->scheduler.addTask(context->task);
}

GIVEN("^Actual time is (\\d*)$") {
    REGEX_PARAM(double, aT);
    ScenarioScope<SchedulerCtx> context;

    context->actTime = aT;
}

WHEN("^The time reaches (\\d*)$") {
    REGEX_PARAM(double, rT);
    ScenarioScope<SchedulerCtx> context;

    context->actTime = rT;
}

THEN("^The state of pin should be (\\d*)$") {
    REGEX_PARAM(double, expected);
    ScenarioScope<SchedulerCtx> context;

    EXPECT_EQ(expected, context->scheduler.runAvailableTasks(context->timer));
}
