Feature: Testing a REST API
  Users should be able to submit GET and POST requests to a web service

  Scenario: Getting information from server
    When user send GET request for a resource '/scheduler' to server
    Then server successfully return list of planned events with code 200 OK
    And list contains value 'thing' equals 'gate'
    And list contains value 'action' equals 'turn off'
    And list contains value 'pin' equals 2



  Scenario: Adding new events to scheduler and getting in response updated list of events
    When user make POST request to adress '/scheduler' with body equals '{"date":"2019-06-26T08:41:00.854Z","pin":12,"thing":"gate two","action":"turn on"}'
    Then server successfully return list of updated events with code 200 OK
    And list contains value 'thing' equals 'gate two'
    And list contains value 'action' equals 'turn on'
    And list contains value 'pin' equals 12