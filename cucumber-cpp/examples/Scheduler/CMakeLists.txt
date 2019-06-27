project(Scheduler)

include_directories(${CUKE_INCLUDE_DIRS} src)

add_library(Scheduler STATIC src/Scheduler)
add_library(ITimer STATIC src/ITimer)
add_library(Task STATIC src/Task)

target_include_directories(Scheduler INTERFACE src)


if(TARGET GTest::GTest)
    add_executable(GTestSchedulerSteps features/step_definitions/GTestSchedulerSteps)
    target_link_libraries(GTestSchedulerSteps PRIVATE Scheduler cucumber-cpp GTest::GTest)
endif()

if(TARGET Boost::unit_test_framework)
    add_executable(BoostSchedulerSteps features/step_definitions/BoostSchedulerSteps)
    target_link_libraries(BoostSchedulerSteps PRIVATE Scheduler cucumber-cpp Boost::unit_test_framework)
endif()

