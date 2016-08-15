/**************************************************************************
Working Node 2 Azana

with relay shield DFROBOT
Only 4 outputs.
    
***************************************************************************/
#include "bconf/StandardArduino.h"          // Use a standard Arduino
#include "conf/ethW5100.h"                  // Ethernet through Wiznet W5100
//#include "conf/DynamicAddressing.h"         // Use dynamic address


// Include framework code and libraries
#include <SPI.h>
#include <EEPROM.h>

#define MAC_INSKETCH
uint8_t MAC_ADDRESS[] = {0x1A, 0xA6, 0x49, 0x6B, 0xCC, 0x80};


/*** All configuration includes should be above this line ***/ 
#include "Souliss.h"


uint8_t ip_address[4]  = {192, 168, 30, 80};
uint8_t subnet_mask[4] = {255, 255, 255, 0};
uint8_t ip_gateway[4]  = {192, 168, 30, 1};
#define Gateway_address 77
#define myvNet_address  ip_address[3]  
#define myvNet_subnet   0xFF00
#define myvNet_supern   Gateway_address


#define LIGHT1                  4           // This is the memory slot used for the execution of the logic
#define LIGHT2                  5           // This is the memory slot used for the execution of the logic
#define LIGHT3                  6
#define LIGHT4                  7         

void setup()
{   

    //Serial.begin(115200);
    Initialize();

    // Get the IP address from DHCP
    //GetIPAddress();  
    //Set IP address                        
    Souliss_SetIPAddress(ip_address, subnet_mask, ip_gateway);

    SetAddress(0xAB02, 0xFF00, 0x0001);

    
    Set_SimpleLight(LIGHT1);        // Define a simple LED light logic
    Set_SimpleLight(LIGHT2);        // Define a simple LED light logic
    Set_SimpleLight(LIGHT3);        // Define a simple LED light logic
    Set_SimpleLight(LIGHT4);        // Define a simple LED light logic
    
    // we connect relay at this output
    pinMode(2,OUTPUT);                  // This is the Relay 1
    pinMode(3,OUTPUT);
    pinMode(4,OUTPUT);                  // This is the Relay 3
    pinMode(5, OUTPUT);                 // 

} 

void loop()
{ 
    // Here we start to play
    EXECUTEFAST() {                     
        UPDATEFAST();   
        
        FAST_510ms() {   // We process the logic and relevant input and output every 50 milliseconds
        
            Logic_SimpleLight(LIGHT1);                          // Drive the LED as per command
            DigOut(2, Souliss_T1n_Coil, LIGHT1);                // Use the pin9 to give power to the LED according to the logic

            
            Logic_SimpleLight(LIGHT2);                          // Drive the LED as per command
            DigOut(3, Souliss_T1n_Coil, LIGHT2);                // Use the pin9 to give power to the LED according to the logic

            Logic_SimpleLight(LIGHT3);                          // Drive the LED as per command
            DigOut(4, Souliss_T1n_Coil, LIGHT3);                // Use the pin9 to give power to the LED according to the logic

            Logic_SimpleLight(LIGHT4);                          // Drive the LED as per command
            DigOut(5, Souliss_T1n_Coil, LIGHT4);                // Use the pin9 to give power to the LED according to the logic

        } 
        
        // Here we process all communication with other nodes
        FAST_PeerComms();   
        
    }

} 
