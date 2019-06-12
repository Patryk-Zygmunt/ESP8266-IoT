#include "HTMLFactory.h"

HTMLFactory::HTMLFactory(){  
}


char* HTMLFactory::getHTML(int choice) {

    if(choice == 0){
      return "<h1>WELCOME !!!</h1> <br>"
             " <form action=\"/addEventScreen\" method=\"get\">"
                 "<input type=\"submit\" value=\"Add Another Event\"> "
                 "<button type=\"submit\" formaction=\"/setHourScreen\">Set Hour</button> "
                 "<button type=\"submit\" formaction=\"/printAllEvents\">Print all Events</button> "
             " </form> "; 
    }
    if(choice == 1){
     return " <form action=\"/addEvent\" method=\"post\">"
                "Device Pin: <input type=\"text\" name=\"pinNumber\">" 
                "Hour: <input type=\"text\" name=\"hour\">"
                "<input type=\"submit\" value=\"Add Event\"> "
            " </form> "; 
    }
    if(choice == 2){
       return " <form action=\"/setCurrentHour\" method=\"post\">"
                "Current Hour: <input type=\"text\" name=\"currentHour\">" 
                "<input type=\"submit\" value=\"Set Current Hour\"> "
            " </form> "; 
    }
    
}
