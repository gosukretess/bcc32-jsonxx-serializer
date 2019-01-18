# bcc32-jsonxx-serializer
Bcc-32-jsonxx-serializer is super simple c++ json serializer written to work with bcc32 compiler under Borland C++ Builder 6. It supports all three structures of JSON (Objects, Arrays and Values), but as values **it supports only strings**.

Whole logic is based on one class - JsonNode. Using it you create tree structure which should reflect the JSON structure you want to create. 

JsonNode class members:

    std::string Name;
    NodeType Type;
    std::list<JsonNode*> ValueList;
    std::string Value;

There are three node types:

 - Object - should have other JsonNodes in ValueList
 - Array - should have other JsonNodes in ValueList
 - Data - should have string in Value field

Usage example:

    // Create flight JSON object
    JsonNode* flight =  new  JsonNode("Flight", Object);
    
	// Add data-value pairs to flight object
    flight->AddDataElement("DepartureAirport", "JFK");
    flight->AddDataElement("ArrivalAirport", "LHR");
    
    // Create StartTime object
    JsonNode* flightStartTime = new JsonNode("StartTime", Object);
    
    // Add name-value pairs to StartTime object
    flightStartTime->AddDataElement("Scheduled", "2018-05-15T19:00:00Z");
    flightStartTime->AddDataElement("Estimated", "2018-05-15T19:10:00Z");
    
    // Add StartTime object to flight
    flight->AddNode(flightStartTime);
    
    // Serialize flight object - return JSON string
    flight ->Serialize();

Above code will generate following string:

    "DepartureAirport": "JFK",
    "ArrivalAirport": "LHR",
    "StartTime": {
            "Estimated": "2018-05-15T19:00:00Z",
            "Scheduled": "2018-05-15T19:10:00Z"
    }
    
To make it correct JSON you just have to wrap the result in object brackets: "{" and "}"