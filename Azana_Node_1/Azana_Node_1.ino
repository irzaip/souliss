/**************************************************************************
Working Node 1 Azana

This is a black box with 2 inputs and 2 outputs
but it's now is using only one
    
***************************************************************************/
#include "bconf/StandardArduino.h"          // Use a standard Arduino
#include "conf/ethW5100.h"                  // Ethernet through Wiznet W5100
#include "conf/DynamicAddressing.h"         // Use dynamic address


// Include framework code and libraries
#include <SPI.h>
#include <EEPROM.h>

#define MAC_INSKETCH
uint8_t MAC_ADDRESS[] = {0x1A, 0xA6, 0x49, 0x6B, 0xCC, 0x79};


/*** All configuration includes should be above this line ***/ 
#include "Souliss.h"


uint8_t ip_address[4]  = {192, 168, 30, 79};
uint8_t subnet_mask[4] = {255, 255, 255, 0};
uint8_t ip_gateway[4]  = {192, 168, 30, 1};
#define Gateway_address 77
#define myvNet_address  ip_address[3]  
#define myvNet_subnet   0xFF00
#define myvNet_supern   Gateway_address

#define Peer_address    79

#define LIGHT1                  2           // This is the memory slot used for the execution of the logic
#define LIGHT2                  3           // This is the memory slot used for the execution of the logic


void setup()
{   

    //Serial.begin(115200);
    Initialize();

    // Get the IP address from DHCP
    //GetIPAddress();  
    //Set IP address                        
    Souliss_SetIPAddress(ip_address, subnet_mask, ip_gateway);

    Set_SimpleLight(LIGHT1);        // Define a simple LED light logic
    Set_SimpleLight(LIGHT2);        // Define a simple LED light logic
    
    // We connect a pushbutton between 5V and pin2 with a pulldown resistor 
    // between pin2 and GND, the LED is connected to pin9 with a resistor to
    // limit the current amount
    pinMode(4, INPUT);                  // Hardware pulldown required
    pinMode(5, INPUT);
    pinMode(2,OUTPUT);                  // This is the LED Display
    pinMode(3,OUTPUT);
    pinMode(6,OUTPUT);                  // This is the Relay
    pinMode(7, OUTPUT);                 // 
    
    // This board request an address to the gateway at runtime, no need
    // to configure any parameter here.
    SetDynamicAddressing();
    GetAddress();   
    
} 

void loop()
{ 
    // Here we start to play
    EXECUTEFAST() {                     
        UPDATEFAST();   
        
        FAST_510ms() {   // We process the logic and relevant input and output every 50 milliseconds
        
            DigIn(4, Souliss_T1n_ToggleCmd, LIGHT1);            // Use the pin2 as ON/OFF toggle command
            Logic_SimpleLight(LIGHT1);                          // Drive the LED as per command
            DigOut(2, Souliss_T1n_Coil, LIGHT1);                // Use the pin9 to give power to the LED according to the logic
            DigOut(6,Souliss_T1n_Coil, LIGHT1);

            
            DigIn(5, Souliss_T1n_ToggleCmd, LIGHT2);            // Use the pin2 as ON/OFF toggle command
            Logic_SimpleLight(LIGHT2);                          // Drive the LED as per command
            DigOut(3, Souliss_T1n_Coil, LIGHT2);                // Use the pin9 to give power to the LED according to the logic
            DigOut(7,Souliss_T1n_Coil, LIGHT2);


        } 
        
        // Here we process all communication with other nodes
        FAST_PeerComms();   
        
    }
    
    EXECUTESLOW() { 
        UPDATESLOW();

        SLOW_10s() {
        //Serial.println("ok");
        }
        
        // Here we periodically check for a gateway to join
        SLOW_PeerJoin();    
    }
} 
