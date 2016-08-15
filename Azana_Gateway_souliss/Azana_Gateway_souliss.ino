/**************************************************************************
Working Node 0 Azana
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
uint8_t MAC_ADDRESS[] = {0x1A, 0xA6, 0x49, 0x6B, 0xCC, 0x77};


/*** All configuration includes should be above this line ***/ 
#include "Souliss.h"

// Define the network configuration according to your router settings
uint8_t ip_address[4]  = {192, 168, 30, 77};
uint8_t subnet_mask[4] = {255, 255, 255, 0};
uint8_t ip_gateway[4]  = {192, 168, 30, 1};
#define Gateway_address 77
#define myvNet_address  ip_address[3]       // The last byte of the IP address (77) is also the vNet address
#define myvNet_subnet   0xFF00
#define myvNet_supern   Gateway_address


#define Peer_address1    78
#define Peer_address2    79
#define Peer_address3    80



void setup()
{   
    Initialize();

    // Get the IP address from DHCP
    // GetIPAddress();        

    // Set network parameters
    Souliss_SetIPAddress(ip_address, subnet_mask, ip_gateway);    
                      
    SetAsGateway(myvNet_address);      // Set this node as gateway for SoulissApp  

    // This node as gateway will get data from the Peer
    SetAsPeerNode(Peer_address1, 1); 
    SetAsPeerNode(Peer_address2, 2); 
    SetAsPeerNode(Peer_address3, 3); 
    
    // This node will serve all the others in the network providing an address
    //SetAddressingServer();
}

void loop()
{ 
    // Here we start to play
    EXECUTEFAST() {                     
        UPDATEFAST();   
        
        FAST_510ms() {   // We process the logic and relevant input and output every 50 milliseconds
        } 
              
        // Here we handle here the communication with Android, commands and notification
        // are automatically assigned to LIGHT1
        FAST_GatewayComms();                                        
        
    }
    
} 
