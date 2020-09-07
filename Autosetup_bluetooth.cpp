/*=================================================================================================
/* Project name: Chronomètre
 * Description:

 * Test configuration:
     MCU:             MJ-Arduino
     Dev.Board:
     Oscillator:      HS- 16.0000 MHz Crystal
     Ext. Modules:
     SW:              Codeblocks


 /*
 The posible baudrates are:
 1-------1200
 2-------2400
 3-------4800
 4-------9600
 5-------19200
 6-------38400
 7-------57600
 8-------115200

 How to use:  juste put the NAME and the baudrate in the bluetoothSetup() function.
              Download the programm (unplug the RX blutooth pin during the process)
              Connect the RX bluetooth after the process, reset the card and wait util LED_13
              When the LED_13 is high, the setup is done.

 =================================================================================================*/


// =============================================================================
//                         Directives
// =============================================================================

#include <Arduino.h>
#include <Wire.h>
//#include <type_common.h>
//#include <OLED_OO.h>   /// !!!

/// définition des lignes pour l'afficheur OLED
#define L_CYCLE        0
#define L_PUISSANCE    4
#define L_ETAT         4
#define L_TEMPS        6
#define L_COURS        6


// =============================================================================
//                         Global Variables used
// =============================================================================

bool done=false;                   // drapeau indiquant la réussite du SETUP du module HC06

char receiveFrame[2];              // tableau servant pour dépiler le buffer RX
byte i,res;                        // index i pour naviger dans le tableau

bool valid=false;                  // drapeau permettant la détection de "OK"

char txtOK[2] = {'O','K'};         // texte de qualification




// ==========================================================================================================================
//                       interrupt programm
// ==========================================================================================================================



// ==========================================================================================================================
//                       function declaration-implementation
// ==========================================================================================================================

//--------------------------------------------------------------------------------------------------------------------------

void setup(void)
{

 pinMode(13, OUTPUT);delay(100);digitalWrite(13, 0);

 valid=false;









}

//---------------------------------------------------------------------------------------------------------------------------
void serialreceive()

{
      /* code qui permet de dépiler le buffer RX "cours Transmission de donnée" page 4*/
       while (Serial.available())                 // le buffer est-il vide ?
       {
       receiveFrame[i] = Serial.read();           // receiveFrame[i] = le 1er octet du buffer
       i++;                                       // Pst incrémentation de l'indexe du tableau

      /* On vérifie si deux caractères sont tombés dans le buffer*/
      if (i == 2)                                // si index = 2    la trame est capturée
        {

         res=strncmp(receiveFrame,txtOK,2);      // On regarde si les deux tableaux sont indentiques
         if (res==0) valid = true;
         i = 0;                                  //  iitialisation de i
        }

      }

}

//-----------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------
void bluetoothSetup()
{


Serial.print("AT+PIN0000");            // mot d passe pour apparié = 0000
delay(1000);
Serial.print("AT+NAMEPOELE_GICQ");    // On change le nom = HC06+numéro du poste+vitesse"
delay(1000);
Serial.print("AT+BAUD8");              // Vitesse = 115200
delay(1000);
digitalWrite(13, 1);
done=true;
}
//-----------------------------------------------------------------------------------------------------------



//==========================================================================================================================
//                               Main function
//===========================================================================================================================

void loop()
{

  if (valid==false) {Serial.begin(1200);delay(500);Serial.print("AT");delay(1000);serialreceive();}
  if (valid==false) {Serial.begin(2400);delay(500);Serial.print("AT");delay(1000);serialreceive();}
  if (valid==false) {Serial.begin(4800);delay(500);Serial.print("AT");delay(1000);serialreceive();}
  if (valid==false) {Serial.begin(9600);delay(500);Serial.print("AT");delay(1000);serialreceive();}
  if (valid==false) {Serial.begin(19200);delay(500);Serial.print("AT");delay(1000);serialreceive();}
  if (valid==false) {Serial.begin(38400);delay(500);Serial.print("AT");delay(1000);serialreceive();}
  if (valid==false) {Serial.begin(57600);delay(500);Serial.print("AT");delay(1000);serialreceive();}
  if (valid==false) {Serial.begin(115200);delay(500);Serial.print("AT");delay(1000);serialreceive();}


  if ((valid==true)&&(done==false)) bluetoothSetup();





}







