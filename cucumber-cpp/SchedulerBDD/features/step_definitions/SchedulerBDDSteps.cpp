#include <gtest/gtest.h>
#include <cucumber-cpp/autodetect.hpp>

#include <Scheduler.h>
#include <Task.h>
#include <ITimer.h>

using cucumber::ScenarioScope;

struct SchedulerCtx {
    Scheduler scheduler;
    Task task;
    ITimer timer;
    PinStateMock pinstatemock;
};

GIVEN("^I have added a task into the scheduler for pin number (\\d+)$") {
    REGEX_PARAM(unsigned int, n);
    ScenarioScope<SchedulerCtx> context;

    context->task.pin = n;
}

GIVEN("^I have entered target state as (\\d*)$") {
    REGEX_PARAM(unsigned int, s);
    ScenarioScope<SchedulerCtx> context;

    context->task.targetState = s;
    
}

GIVEN("^I have entered execution time at ([+-]?([0-9]*[.])?[0-9]+)$") {
    REGEX_PARAM(double, eT);
    ScenarioScope<SchedulerCtx> context;

    context->task.executionTime = eT;
    context->scheduler.addTask(context->task);
}

GIVEN("^Actual time is ([+-]?([0-9]*[.])?[0-9]+)$") {
    REGEX_PARAM(double, aT);
    ScenarioScope<SchedulerCtx> context;

    context->timer.currentTime = aT;
}

WHEN("^The time reaches ([+-]?([0-9]*[.])?[0-9]+)$") {
    REGEX_PARAM(double, rT);
    ScenarioScope<SchedulerCtx> context;

    context->timer.currentTime = rT;
    context->scheduler.runAvailableTasks(context->timer, context->pinstatemock);
}

THEN("^The state of pin should be (\\d*)$") {
    REGEX_PARAM(double, expected);
    ScenarioScope<SchedulerCtx> context;
		
    EXPECT_EQ(expected, context->pinstatemock.getOutPinState(context->task.pin) );
}
