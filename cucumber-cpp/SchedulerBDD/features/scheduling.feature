# language: en
Feature: Scheduling
  Adding a new task into a scheduler
  With a execution time
  Execution of a task is expected at a given time

  Scenario Outline: Add task and check if executed
    Given I have added a task into the scheduler for pin number <input_1> 
    And I have entered target state as <input_2>
    And I have entered execution time at <input_3>
    And Actual time is <input_4>
    When The time reaches <input_5>
    Then The state of pin should be <output>

  Examples:
    | input_1 | input_2 | input_3 | input_4 | input_5 | output |
    | 1       | 1       | 9.30    | 8.00    | 10.59   | 0      |
    | 1       | 1       | 9.30    | 8.00    | 10.59   | 1      |
    | 2       | 1       | 8.30    | 1       | 10      | 1      |
    | 3       | 0       | 9       | 1       | 2	      | 0      |
    | 4       | 1       | 10.59   | 10.00   | 10.30   | 0      |
