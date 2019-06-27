project(SchedulerBDD)

include_directories(${CUKE_INCLUDE_DIRS} src)

add_library(SchedulerBDD src/Scheduler src/ITimer src/Task src/PinStateMock src/IPinState)

if(GMOCK_FOUND)
    add_executable(SchedulerBDDSteps features/step_definitions/SchedulerBDDSteps)
    target_link_libraries(SchedulerBDDSteps SchedulerBDD cucumber-cpp GTest::GTest)
endif()
