// Arduino script for sending an email by @ctigeek.
 
#include <SPI.h>
#include <Ethernet.h>
 
EthernetClient  client;
signed long next;
 
int connectToServer() {
   Serial.println(F("Connecting to server..."));
   
   if (!client.connect("smtp.server.com",587))
     return 0;
 
   Serial.println(F("connected to mail server."));   
   return 1; 
}
 
int waitForReply() {
  next = millis() + 5000;
  while(client.available()==0)
  {
    if (next - millis() < 0)
      return 0;
  }
  int size;
  while((size = client.available()) > 0)
  {
    uint8_t* msg = (uint8_t*)malloc(size);
    size = client.read(msg,size);
    Serial.write(msg,size);
    free(msg);
  }
  return 1;
}
 
int sendAndWaitForReply(char* txtToSend) {
    next = millis() + 5000;
    client.println(txtToSend);
    Serial.println(txtToSend);
    if (!waitForReply()) 
       return 0;
    
    return 1;
}
 
void justSend(const __FlashStringHelper* txtToSend) {
    client.println(txtToSend);
    Serial.println(txtToSend);
}
 
int sendAndWaitForReply(const __FlashStringHelper* txtToSend) {
    next = millis() + 5000;
    client.println(txtToSend);
    Serial.println(txtToSend);
    if (!waitForReply()) 
       return 0;
    
    return 1;
}
 
int sendEmail() {
  if (!connectToServer())
    return 0;
  
  if (!waitForReply())
    return 0;
  
  if (!sendAndWaitForReply(F("EHLO Arduino")))
    return 0;
              
  if (!sendAndWaitForReply(F("AUTH login "))) //enter base64 encoded email address here
    return 0;
  
  if (!sendAndWaitForReply(F(""))) //enter base64 encoded password here
    return 0;
  
  if (!sendAndWaitForReply(F("MAIL FROM:<your email address here>")))
    return 0;
  
  if (!sendAndWaitForReply(F("RCPT TO:<recipients email address here.>")))
    return 0; 
    
  if (!sendAndWaitForReply(F("DATA")))
    return 0;
  
  justSend(F("MIME-Version: 1.0"));
  justSend(F("From: sender@domain.com"));
  justSend(F("To: recipient@domain.com"));
  justSend(F("Subject: Arduino!"));
  justSend(F("Content-type: text/plain; charset=us-ascii"));
  justSend(F("")); //this separates the headers from the body.
 
  justSend(F("Arduinos are so small!"));
 
  if (!sendAndWaitForReply(F("."))) //this means EOF to the smtp server.
    return 0;
  if (!sendAndWaitForReply(F("QUIT")))
    return 0;
    
  return 1;
}
 
void setup() {
  Serial.begin(9600);
  uint8_t mac[6] = {0x00,0x01,0x02,0x03,0x04,0x05};
  Ethernet.begin(mac);
 
  Serial.print(F("localIP: "));
  Serial.println(Ethernet.localIP());
 
  sendEmail();
}
 
void loop() {
  
}

