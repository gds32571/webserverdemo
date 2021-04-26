//***********************************
// All of the webserver handlers except for the example "inline" server

// the root web page
void handleRoot() {
//  digitalWrite(led, 1);
  String message = "I am a web server!\n";
  message += "running " + String(progname) +", version " + String(myVersion) + "\n";
  message += "This is the root\n";
  message += "Running for " + String(millis()/1000) + " seconds\n";
  server.send(200, "text/plain", message);
//  digitalWrite(led, 0);
}

// this handler allows direct control of GPIO pins on the EP8266
// with direct access from a web page.  A manually typed in URL will work
void handleGPIO(){
  String message = "GPIO control\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }

  message += "GPIO " + server.arg(0) + "\n";
  message += "STATE " + server.arg(1) + "\n";

// pick one of these sets of server commands, depending on whether
// you want to see the result of the command, or you want 
// to be redirected (as from and to the control page) 

// manual, showing results   
//  server.send(200, "text/plain", message);
// or linked
  server.sendHeader("Location", "./control");     // Add a header to respond with a new location for the browser to go to the home page again
  server.send(303);                          // Send it back to the browser with an HTTP status 303 (See Other) to redirect


  int myGPIO = server.arg(0).toInt();
  int mySTATE = server.arg(1).toInt();

// this could have been done a different way, but this method
// allows you to do completely different things for each GPIO pin controlled
// see https://github.com/gds32571/antsw2/blob/master/antsw2-public.ino for an example

  switch (myGPIO){
     case 12:
       pinMode(myGPIO, OUTPUT); 
       digitalWrite(myGPIO, mySTATE);  
//       digitalWrite(led, !digitalRead(led));
       Serial.println("pin " + server.arg(0) + " set to " + server.arg(1)); 
       break;  
     case 13:
       pinMode(myGPIO, OUTPUT); 
       digitalWrite(myGPIO, mySTATE);  
//       digitalWrite(led, !digitalRead(led));
       Serial.println("pin " + server.arg(0) + " set to " + server.arg(1)); 
       break;  
     case 14:
       pinMode(myGPIO, OUTPUT); 
       digitalWrite(myGPIO, mySTATE);  
//       digitalWrite(led, !digitalRead(led));
       Serial.println("pin " + server.arg(0) + " set to " + server.arg(1)); 
       break;  
     default:
       pinMode(myGPIO, OUTPUT); 
       Serial.println("Invalid pin");
//       digitalWrite(led, 0);
  }
       
}

//*************************************************
void handleControl() {                     // If a GET request is made to URI /control

  String message = "<html>This is " + String(WiFi_hostname) + "<br>"
                   + "Running " + String(progname) + " " + String(myVersion) + "<br><br>"
                   + "<a href=./GPIO?ctl=12&state=1>" + "GPIO 12 On  </a>  <br>"
                   + "<a href=./GPIO?ctl=12&state=0>" + "GPIO 12 Off </a>  <br>"
                   + "<a href=./GPIO?ctl=13&state=1>" + "GPIO 13 On  </a>  <br>"
                   + "<a href=./GPIO?ctl=13&state=0>" + "GPIO 13 Off </a>  <br>"
                   + "<a href=./GPIO?ctl=14&state=1>" + "GPIO 14 On  </a>  <br>"
                   + "<a href=./GPIO?ctl=14&state=0>" + "GPIO 14 Off </a>  <br>"
                   + "<a href=./control>" + "/control</a>     to display this page<br></html>";

  server.send(200, "text/html", message);
}

 
void handleNotFound(){
//  digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
//  digitalWrite(led, 0);
}
