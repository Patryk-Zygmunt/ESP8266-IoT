package steps;

import cucumber.api.java.Before;
import cucumber.api.java.en.And;
import cucumber.api.java.en.Then;
import cucumber.api.java.en.When;
import io.restassured.RestAssured;
import io.restassured.response.Response;
import static org.hamcrest.Matchers.*;
import static org.hamcrest.MatcherAssert.*;
import static io.restassured.RestAssured.*;

public class ApiTestsStepdefs {

    private final String URL = "http://localhost" ;
    private final  int PORT = 3000;
    private Response response;

    @Before
    public void initailzeURL(){
        RestAssured.baseURI = URL;
        RestAssured.port = PORT;
    }

    @When("(.*) send GET request for a resource '(.+)' to server")
    public void userMakeGet(String par1,String resource) {
       response = when().get(resource);
    }

    @When("user make POST request to adress {string} with body equals {string}")
    public void userMakePOSTRequestToAdressSchedulerWithBodyEquals(String resource, String body) {
       response =  given().contentType("application/json")
                .body(body)
                .when().post(resource);
    }



    @Then("server successfully return (.*) with code 200 OK")
    public void serverReturnAllPlannedEvents(String par1) {
        response.then()
                .statusCode(200);
    }

    @And("list contains value {string} equals {string}")
    public void listContainsValueThingEqualsGateString(String key, String value) {
       assertThat("Response contains value",  response.jsonPath().getList(key).contains(value));
    }

    @And("list contains value {string} equals {int}")
    public void listContainsValueThingEqualsGateInt(String key, int value) {
        assertThat("Response contains value",  response.jsonPath().getList(key).contains(value));
    }

}
