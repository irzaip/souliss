/**************************************************************************
Working Node 0 Azana

This node have 2 inputs and 2 relays

***************************************************************************/

#include "bconf/StandardArduino.h"          // Use a standard Arduino
#include "conf/ethW5100.h"                  // Ethernet through Wiznet W5100
#include "conf/Gateway.h"                   // The main node is the Gateway, we have just one node
#include "conf/Webhook.h"                   // Enable DHCP and DNS
#include "conf/DynamicAddressing.h"         // Use dynamic address

// Include framework code and libraries
#include <SPI.h>
#include <EEPROM.h>

#define MAC_INSKETCH
uint8_t MAC_ADDRESS[] = {0x1A, 0xA6, 0x49, 0x6B, 0xCC, 0x78};


/*** All configuration includes should be above this line ***/ 
#include "Souliss.h"

// Define the network configuration according to your router settings
uint8_t ip_address[4]  = {192, 168, 30, 78};
uint8_t subnet_mask[4] = {255, 255, 255, 0};
uint8_t ip_gateway[4]  = {192, 168, 30, 1};
#define Gateway_address 77
#define myvNet_address  ip_address[3]       // The last byte of the IP address (77) is also the vNet address
#define myvNet_subnet   0xFF00
#define myvNet_supern   Gateway_address




#define LIGHT1                  0           // This is the memory slot used for the execution of the logic
#define LIGHT2                  1           




void setup()
{   
    Initialize();

    // Get the IP address from DHCP
    // GetIPAddress();        
    // Set network parameters
    Souliss_SetIPAddress(ip_address, subnet_mask, ip_gateway);    
                      
    Set_SimpleLight(LIGHT1);        // Define a simple LED light logic
    Set_SimpleLight(LIGHT2);        // Define a simple LED light logic
    
    // We connect a pushbutton between 5V and pin2 with a pulldown resistor 
    // between pin2 and GND, the LED is connected to pin9 with a resistor to
    // limit the current amount
    pinMode(2, INPUT);                  // Hardware pulldown required
    pinMode(3, INPUT);
    pinMode(6,OUTPUT);                  // This is the LED Display
    pinMode(7,OUTPUT);
    pinMode(8,OUTPUT);                  // This is the Relay
    pinMode(9, OUTPUT);                 // 
      
}

void loop()
{ 
    // Here we start to play
    EXECUTEFAST() {                     
        UPDATEFAST();   
        
        FAST_510ms() {   // We process the logic and relevant input and output every 50 milliseconds

            DigIn(2, Souliss_T1n_ToggleCmd, LIGHT1);            // Use the pin2 as ON/OFF toggle command
            Logic_SimpleLight(LIGHT1);                          // Drive the LED as per command
            DigOut(8, Souliss_T1n_Coil, LIGHT1);                // Use the pin9 to give power to the LED according to the logic
            DigOut(7,Souliss_T1n_Coil, LIGHT1);

            
            DigIn(3, Souliss_T1n_ToggleCmd, LIGHT2);            // Use the pin2 as ON/OFF toggle command
            Logic_SimpleLight(LIGHT2);                          // Drive the LED as per command
            DigOut(9, Souliss_T1n_Coil, LIGHT2);                // Use the pin9 to give power to the LED according to the logic
            DigOut(6,Souliss_T1n_Coil, LIGHT2);


        } 
              
        // Here we process all communication with other nodes
        FAST_PeerComms();   
        
    }
} 
