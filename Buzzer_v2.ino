
// include the library code:
#include <LiquidCrystal.h>
#include <EEPROM.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);

//déclaration des variables
int pinBouton1, pinBouton2, pinBouton3, pinBouton4, pinBouton5, pinBouton6, pinBouton7, pinBouton8, pinBoutonOui, pinBoutonNon, pinBoutonReset, pinBoutonPoints, pinBoutonPun1, pinBoutonPun2;//déclaration des entrée bouton
int pointsEquipe1, pointsEquipe2, pointsEquipe3, pointsEquipe4, pointsEquipe5, pointsEquipe6, pointsEquipe7, pointsEquipe8; //variables de points des equipes
int stock1, stock2, stock3, stock4, stock5, stock6, stock7, stock8; //variables de points en attente de valid
int bloquage1, bloquage2, bloquage3, bloquage4, bloquage5, bloquage6, bloquage7, bloquage8; //variables des bloquages
int maintien1, maintien2, maintien3, maintien4, maintien5, maintien6, maintien7, maintien8, maintienPun1, maintienPun2; // variables de maintien (deja joué)
int nombreDePoints; // variable du nombre de points
int nombreDeJoueurs; // variable du nombre de joueurs
int etat1 = 0; // variable etat bouton1
int etat2 = 0; // variable etat bouton2
int etat3 = 0; // variable etat bouton3
int etat4 = 0; // variable etat bouton4
int etat5 = 0; // variable etat bouton5
int etat6 = 0; // variable etat bouton6
int etat7 = 0; // variable etat bouton7
int etat8 = 0; // variable etat bouton8
int etatOui = 0; // variable etat bouton oui
int etatNon = 0; // variable etat bouton non
int etatReset = 0; // variable etat bouton reset
int etatPoints = 0; // variable etat bouton Points
int etatPun1 = 0; // variable etat bouton Punition 1
int etatPun2 = 0; // variable etat bouton Punition 2
int pinLed1, pinLed2, pinLed3, pinLed4, pinLed5, pinLed6, pinLed7, pinLed8; //déclaration des sortie led
int t1, t2; // variables affichage LCD
int t3, t4; // variables clignottement leds
int t5, t6; // variables clignottement leds bloquage
int t7; // variable tempo reponse

//*************************Setup*************************************************************

void setup()
{

  //initialisation des variables
  Serial.begin(9600);
  pinBouton1 = 8;
  pinBouton2 = 9;
  pinBouton3 = 10;
  pinBouton4 = 11;
  pinBouton5 = 5;
  pinBouton6 = 4;
  pinBouton7 = 3;
  pinBouton8 = 2;
  pinBoutonOui = 51;
  pinBoutonNon = 47;
  pinBoutonReset = 49;
  pinBoutonPoints = 53;
  pinBoutonPun1 = 43;
  pinBoutonPun2 = 45;
  stock1, stock2, stock3, stock4, stock5, stock6, stock7, stock8 = 0;
  bloquage1, bloquage2, bloquage3, bloquage4, bloquage5, bloquage6, bloquage7, bloquage8 = 0;
  maintien1, maintien2, maintien3, maintien4, maintien5, maintien6, maintien7, maintien8, maintienPun1, maintienPun2 = 0;
  nombreDePoints = 1;
  nombreDeJoueurs = 2;
  pinLed1 = 28;
  pinLed2 = 29;
  pinLed3 = 30;
  pinLed4 = 31;
  pinLed5 = 25;
  pinLed6 = 24;
  pinLed7 = 23;
  pinLed8 = 22;
  t1 = 0;
  t2 = 0;
  t3 = 0;
  t4 = 0;
  t5 = 0;
  t6 = 0;
  t7 = 0;


  //mise en mode OUTPUT des pins 28 à 31 et positionnement en LOW (leds)
  for (int t = 28; t < 32; t++)
  {
    pinMode(t, OUTPUT);
    digitalWrite(t, LOW);
  }

  //mise en mode OUTPUT des pins 22 à 25 et positionnement en LOW (leds)
  for (int t = 22; t < 26; t++)
  {
    pinMode(t, OUTPUT);
    digitalWrite(t, LOW);
  }

  //mise en mode INPUT_PULLUP des pins 2 à 11 (boutons)
  for (int t = 2; t < 12; t++)
  {
    pinMode(t, INPUT_PULLUP);
  }

  pinMode(43, INPUT_PULLUP);
  pinMode(45, INPUT_PULLUP);
  pinMode(47, INPUT_PULLUP);
  pinMode(49, INPUT_PULLUP);
  pinMode(51, INPUT_PULLUP);
  pinMode(53, INPUT_PULLUP);

  //defini le nombre de colonnes et lignes du LCD
  lcd.begin(16, 2);
  lcd.clear();//reset LCD


  //******************************************************question reset **********************************************************************************


  boolean resetScores = 0;

  if (resetScores == 0)
  {
    do
    {


      // place le curseur colonne 13, ligne 0
      lcd.setCursor(0, 0);
      // Ecrit sur LCD.
      lcd.print("RESET DES SCORES?");
      // place le curseur colonne 0, ligne 1
      lcd.setCursor(0, 1);
      // Ecrit sur LCD.
      lcd.print("NON");
      // place le curseur colonne 15, ligne 1
      lcd.setCursor(13, 1);
      // Ecrit sur LCD.
      lcd.print("OUI");


      boolean etatPinBoutonOui = digitalRead(pinBoutonOui);
      boolean etatPinBoutonNon = digitalRead(pinBoutonNon);

      if (etatOui == 0) //attente boutonOui
      {
        if (!etatPinBoutonOui)//si boutonOui appuyé (donc le pin indique 0 car il est en mode INPUT_PULLUP)
        {
          lcd.clear();//reset LCD
          // on passe à l'état boutonOui pressé
          etatOui = 1;

          do
          {
            // place le curseur colonne 13, ligne 0
            lcd.setCursor(0, 0);
            // Ecrit sur LCD.
            lcd.print("ETES VOUS SUR?");
            // place le curseur colonne 0, ligne 1
            lcd.setCursor(0, 1);
            // Ecrit sur LCD.
            lcd.print("NON");
            // place le curseur colonne 15, ligne 1
            lcd.setCursor(13, 1);
            // Ecrit sur LCD.
            lcd.print("OUI");

            boolean etatPinBoutonOui = digitalRead(pinBoutonOui);
            boolean etatPinBoutonNon = digitalRead(pinBoutonNon);

            if (etatOui == 0) //attente boutonOui
            {
              if (!etatPinBoutonOui)//si boutonOui appuyé (donc le pin indique 0 car il est en mode INPUT_PULLUP)
              {
                // on passe à l'état boutonOui pressé
                etatOui = 1;
                // reset des points :
                pointsEquipe1 == 0;
                pointsEquipe2 == 0;
                pointsEquipe3 == 0;
                pointsEquipe4 == 0;
                pointsEquipe5 == 0;
                pointsEquipe6 == 0;
                pointsEquipe7 == 0;
                pointsEquipe8 == 0;
                EEPROM.update (1, pointsEquipe1); // maj point en memoire
                EEPROM.update (2, pointsEquipe2); // maj point en memoire
                EEPROM.update (3, pointsEquipe3); // maj point en memoire
                EEPROM.update (4, pointsEquipe4); // maj point en memoire
                EEPROM.update (5, pointsEquipe5); // maj point en memoire
                EEPROM.update (6, pointsEquipe6); // maj point en memoire
                EEPROM.update (7, pointsEquipe7); // maj point en memoire
                EEPROM.update (8, pointsEquipe8); // maj point en memoire
                resetScores = 1;
              }
            }
            else if (etatOui == 1) // boutonOui pressé
            {
              if (etatPinBoutonOui)//si boutonOui relaché (donc le pin indique 1 car il est en mode INPUT_PULLUP)
              {
                // on passe à l'état boutonOui relaché
                etatOui = 0;

              }
            }


            if (etatNon == 0) //attente boutonNon
            {
              if (etatPinBoutonNon)//(Bouton cablé en NC) si boutonNonappuyé (donc le pin indique 0 car il est en mode INPUT_PULLUP)
              {
                // on passe à l'état boutonNon pressé
                etatNon = 1;

              }
            }
            else if (etatNon == 1) // boutonNon pressé
            {
              if (!etatPinBoutonNon)// (Bouton cablé en NC) si boutonNon relaché (donc le pin indique 1 car il est en mode INPUT_PULLUP)
              {
                // on passe à l'état boutonNon relaché
                etatNon = 0;
                resetScores = 1;
              }
            }
          } while (resetScores == 0);

        }
      }
      else if (etatOui == 1) // boutonOui pressé
      {
        if (etatPinBoutonOui)//si boutonOui relaché (donc le pin indique 1 car il est en mode INPUT_PULLUP)
        {
          // on passe à l'état boutonOui relaché
          etatOui = 0;
          resetScores = 1;
        }
      }
      if (etatNon == 0) //attente boutonNon
      {
        if (etatPinBoutonNon)// (Bouton cablé en NC) si boutonNon appuyé (donc le pin indique 0 car il est en mode INPUT_PULLUP)
        {
          // on passe à l'état boutonNon pressé
          etatNon = 1;

        }
      }
      else if (etatNon == 1) // boutonNon pressé
      {
        if (!etatPinBoutonNon)// (Bouton cablé en NC) si boutonNon relaché (donc le pin indique 1 car il est en mode INPUT_PULLUP)
        {
          // on passe à l'état boutonNon relaché
          etatNon = 0;
          resetScores = 1;
        }
      }
    } while (resetScores == 0);

    boolean choixNombreJoueurs = 0;
    lcd.clear();//reset LCD
    do
    {

      // place le curseur colonne 13, ligne 0
      lcd.setCursor(0, 0);
      // Ecrit sur LCD.
      lcd.print("Nombre de joueurs");
      // place le curseur colonne 0, ligne 1
      lcd.setCursor(0, 1);
      // Ecrit sur LCD.
      lcd.print(nombreDeJoueurs);
      // place le curseur colonne 15, ligne 1
      lcd.setCursor(13, 1);
      // Ecrit sur LCD.
      lcd.print("OK");

      boolean etatPinBoutonOui = digitalRead(pinBoutonOui);
      boolean etatPinBoutonNon = digitalRead(pinBoutonNon);



      if (etatOui == 0) //attente boutonOui
      {
        if (!etatPinBoutonOui)//si boutonOui appuyé (donc le pin indique 0 car il est en mode INPUT_PULLUP)
        {

          // on passe à l'état boutonOui pressé
          etatOui = 1;
          choixNombreJoueurs = 1;

        }
      }
      else if (etatOui == 1) // boutonOui pressé
      {
        if (etatPinBoutonOui)//si boutonOui relaché (donc le pin indique 1 car il est en mode INPUT_PULLUP)
        {

          // on passe à l'état boutonOui relaché
          etatOui = 0;

        }
      }



      if (etatNon == 0) //attente boutonNon
      {
        if (etatPinBoutonNon)// (Bouton cablé en NC) si boutonNon appuyé (donc le pin indique 0 car il est en mode INPUT_PULLUP)
        {
          // on passe à l'état boutonNon pressé
          etatNon = 1;

          // choix du nombre de joueurs
          if (nombreDeJoueurs == 8)
          {
            nombreDeJoueurs = 0;
            lcd.clear();
          }
          if (nombreDeJoueurs == 7)
          {
            nombreDeJoueurs = 8;
          }
          if (nombreDeJoueurs == 6)
          {
            nombreDeJoueurs = 7;
          }
          if (nombreDeJoueurs == 5)
          {
            nombreDeJoueurs = 6;
          }
          if (nombreDeJoueurs == 4)
          {
            nombreDeJoueurs = 5;
          }
          if (nombreDeJoueurs == 3)
          {
            nombreDeJoueurs = 4;
          }
          if (nombreDeJoueurs == 2)
          {
            nombreDeJoueurs = 3;
          }
          if (nombreDeJoueurs == 0)
          {
            nombreDeJoueurs = 2;
          }
        }
      }
      else if (etatNon == 1) // boutonNon pressé
      {
        if (!etatPinBoutonNon)// (Bouton cablé en NC) si boutonNon relaché (donc le pin indique 1 car il est en mode INPUT_PULLUP)
        {
          // on passe à l'état boutonNon relaché
          etatNon = 0;
        }
      }

    } while (choixNombreJoueurs == 0 );
  }

  // lecture des points en memoire
  byte valeur1 = EEPROM.read(1);
  pointsEquipe1 = valeur1;
  byte valeur2 = EEPROM.read(2);
  pointsEquipe2 = valeur2;
  byte valeur3 = EEPROM.read(3);
  pointsEquipe3 = valeur3;
  byte valeur4 = EEPROM.read(4);
  pointsEquipe4 = valeur4;
  byte valeur5 = EEPROM.read(5);
  pointsEquipe5 = valeur5;
  byte valeur6 = EEPROM.read(6);
  pointsEquipe6 = valeur6;
  byte valeur7 = EEPROM.read(7);
  pointsEquipe7 = valeur7;
  byte valeur8 = EEPROM.read(8);
  pointsEquipe8 = valeur8;
  lcd.clear();//reset LCD

  
}

//*************************Loop*************************************************************

void loop()
{
  //lecture de l'état des boutons et stockage dans etatBouton
  boolean etatPinBouton1 = digitalRead(pinBouton1);
  boolean etatPinBouton2 = digitalRead(pinBouton2);
  boolean etatPinBouton3 = digitalRead(pinBouton3);
  boolean etatPinBouton4 = digitalRead(pinBouton4);
  boolean etatPinBouton5 = digitalRead(pinBouton5);
  boolean etatPinBouton6 = digitalRead(pinBouton6);
  boolean etatPinBouton7 = digitalRead(pinBouton7);
  boolean etatPinBouton8 = digitalRead(pinBouton8);
  boolean etatPinBoutonOui = digitalRead(pinBoutonOui);
  boolean etatPinBoutonNon = digitalRead(pinBoutonNon);
  boolean etatPinBoutonReset = digitalRead(pinBoutonReset);
  boolean etatPinBoutonPoints = digitalRead(pinBoutonPoints);
  boolean etatPinBoutonPun1 = digitalRead(pinBoutonPun1);
  boolean etatPinBoutonPun2 = digitalRead(pinBoutonPun2);


  //***************Affichage LCD*********************************************



 
  
  //*************************Affichage "BLIND TEST REVIVAL EMOTION" défilant*************************************************************

  //FAIRE DEFILER LE TEXTE DE GAUCHE A DROITE
  // On fait défiler de 13 cases (longueur du texte) vers la gauche
  // afin qu'il n'apparaisse plus
  //for (int positionCounter = 0; positionCounter < 13; positionCounter++)
  //{
  // défile à droite
  //lcd.scrollDisplayLeft();
  // on attend un peu
  //delay(150);
  //}

  //*************************Affichage des points *************************************************************

if ((stock1 == 0) & (stock2 == 0) & (stock3 == 0) & (stock4 == 0) & (stock5 == 0) & (stock6 == 0) & (stock7 == 0) & (stock8 == 0))
{
  //tempo LCD
  if (t1 < 300)
  {

    if (nombreDePoints < 10)
    {
      // place le curseur colonne 14, ligne 0
      lcd.setCursor(15, 0);
      // Ecrit sur LCD.
      lcd.print(nombreDePoints);
    }

    if ((nombreDePoints >9) && (nombreDePoints < 100))
    {
      // place le curseur colonne 13, ligne 0
      lcd.setCursor(14, 0);
      // Ecrit sur LCD.
      lcd.print(nombreDePoints);
     }
 
     if (nombreDePoints == 100)
     {
      // place le curseur colonne 12, ligne 0
      lcd.setCursor(13, 0);
      // Ecrit sur LCD.
       lcd.print(nombreDePoints);
     }
     
      lcd.setCursor(0,0);
      lcd.print("   BLIND TEST");
      lcd.setCursor(0,1);
      lcd.print("REVIVAL  EMOTION");
      
    // place le curseur colonne 0, ligne 0
    // lcd.setCursor(0, 0);
    // Ecrit sur LCD.
    // lcd.print("A");
    // place le curseur colonne 0, ligne 1
     //lcd.setCursor(0, 1);
    // ecrit pointsequipe1
    // lcd.print(pointsEquipe1);
    // place le curseur colonne 5, ligne 0
    // lcd.setCursor(4, 0);
    // Ecrit sur LCD.
    // lcd.print("B");
    // place le curseur colonne 5, ligne 1
     //lcd.setCursor(4, 1);
    //  ecrit pointsequipe2
    // lcd.print(pointsEquipe2);
    // if (nombreDeJoueurs > 2)
    //{
      // place le curseur colonne 9, ligne 0
      // lcd.setCursor(8, 0);
      // Ecrit sur LCD.
      // lcd.print("C");
      // place le curseur colonne 9, ligne 1
      // lcd.setCursor(8, 1);
      //  ecrit pointsequipe3
       //lcd.print(pointsEquipe3);
     //}
    // if (nombreDeJoueurs > 3)
     //{
      // place le curseur colonne 13, ligne 0
      // lcd.setCursor(12, 0);
      // Ecrit sur LCD.
      // lcd.print("D");
      // place le curseur colonne 13, ligne 1
       //lcd.setCursor(12, 1);
      // ecrit pointsequipe4
      // lcd.print(pointsEquipe4);
    // }
    // if (nombreDeJoueurs > 4)
     //{
      // t1 = t1 + 1;//tempo LCD
       //delay (1);//tempo LCD
     //}
   //}
  // else
  // {
    // if (t2 == 0)
     //{
      // lcd.clear();//reset LCD
     //}
     //if (nombreDePoints < 10)
     //{
      // place le curseur colonne 16, ligne 0
       //lcd.setCursor(15, 0);
      // Ecrit sur LCD.
      // lcd.print(nombreDePoints);
     //}

   //  if ((nombreDePoints > 9) && (nombreDePoints < 100))
    // {
      // place le curseur colonne 15, ligne 0
      // lcd.setCursor(14, 0);
      // Ecrit sur LCD.
       //lcd.print(nombreDePoints);
    // }
    // if (nombreDePoints == 100)
    // {
      // place le curseur colonne 14, ligne 0
       //lcd.setCursor(13, 0);
      // Ecrit sur LCD.
      // lcd.print(nombreDePoints);
    // }

    // if (nombreDeJoueurs > 4)
     //{
      // place le curseur colonne 0, ligne 0
      // lcd.setCursor(0, 0);
      // Ecrit sur LCD.
      // lcd.print("E");
      // place le curseur colonne 0, ligne 1
      // lcd.setCursor(0, 1);
      // ecrit pointsequipe5
      // lcd.print(pointsEquipe5);
    // }
    // if (nombreDeJoueurs > 5)
    // {
      // place le curseur colonne 5, ligne 0
      // lcd.setCursor(4, 0);
      // Ecrit sur LCD.
      // lcd.print("F");
      // place le curseur colonne 5, ligne 1
       //lcd.setCursor(4, 1);
      //  ecrit pointsequipe6
       //lcd.print(pointsEquipe6);

    // }
    // if (nombreDeJoueurs > 6)
    // {
      // place le curseur colonne 9, ligne 0
      // lcd.setCursor(8, 0);
      // Ecrit sur LCD.
      // lcd.print("G");
      // place le curseur colonne 9, ligne 1
      //lcd.setCursor(8, 1);
      //  ecrit pointsequipe7
     //  lcd.print(pointsEquipe7);
    // }
    // if (nombreDeJoueurs > 7)
    // {
      // place le curseur colonne 13, ligne 0
     //  lcd.setCursor(12, 0);
      // Ecrit sur LCD.
     // lcd.print("H");
      // place le curseur colonne 13, ligne 1
    //  lcd.setCursor(12, 1);
      // ecrit pointsequipe8
     // lcd.print(pointsEquipe8);
   // }
  //  t2 = t2 + 1;//tempo LCD
 //   delay (1);//tempo LCD
 // }
 // if (t2 == 300)//tempo LCD
//  {
//    t1 = 0;//tempo LCD
 //   t2 = 0;//tempo LCD
  }

}


//*******************************Affichage "a repondu" ************************************************************

if (stock1 >0)  
{
  // place le curseur colonne 0, ligne 0
      lcd.setCursor(0, 0);
      // Ecrit sur LCD.
      lcd.print("    Equipe A    ");
      // place le curseur colonne 0, ligne 1
      lcd.setCursor(0, 1);
      // Ecrit sur LCD.
      lcd.print("   a repondu    ");
}

if (stock2 >0)
{
  // place le curseur colonne 0, ligne 0
      lcd.setCursor(0, 0);
      // Ecrit sur LCD.
      lcd.print("    Equipe B    ");
      // place le curseur colonne 0, ligne 1
      lcd.setCursor(0, 1);
      // Ecrit sur LCD.
      lcd.print("   a repondu    ");
}
if (stock3 >0)
{
  // place le curseur colonne 0, ligne 0
      lcd.setCursor(0, 0);
      // Ecrit sur LCD.
      lcd.print("    Equipe C    ");
      // place le curseur colonne 0, ligne 1
      lcd.setCursor(0, 1);
      // Ecrit sur LCD.
      lcd.print("   a repondu    ");
}
if (stock4 >0)
{
  // place le curseur colonne 0, ligne 0
      lcd.setCursor(0, 0);
      // Ecrit sur LCD.
      lcd.print("    Equipe D    ");
      // place le curseur colonne 0, ligne 1
      lcd.setCursor(0, 1);
      // Ecrit sur LCD.
      lcd.print("   a repondu    ");
}
if (stock5 >0)
{
  // place le curseur colonne 0, ligne 0
      lcd.setCursor(0, 0);
      // Ecrit sur LCD.
      lcd.print("    Equipe E    ");
      // place le curseur colonne 0, ligne 1
      lcd.setCursor(0, 1);
      // Ecrit sur LCD.
      lcd.print("   a repondu    ");
}
if (stock6 >0)
{
  // place le curseur colonne 0, ligne 0
      lcd.setCursor(0, 0);
      // Ecrit sur LCD.
      lcd.print("    Equipe F     ");
      // place le curseur colonne 0, ligne 1
      lcd.setCursor(0, 1);
      // Ecrit sur LCD.
      lcd.print("   a repondu    ");
}
if (stock7 >0)
{
  // place le curseur colonne 0, ligne 0
      lcd.setCursor(0, 0);
      // Ecrit sur LCD.
      lcd.print("    Equipe G    ");
      // place le curseur colonne 0, ligne 1
      lcd.setCursor(0, 1);
      // Ecrit sur LCD.
      lcd.print("   a repondu    ");
}
if (stock8 >0)
{
  // place le curseur colonne 0, ligne 0
      lcd.setCursor(0, 0);
      // Ecrit sur LCD.
      lcd.print("    Equipe H    ");
      // place le curseur colonne 0, ligne 1
      lcd.setCursor(0, 1);
      // Ecrit sur LCD.
      lcd.print("   a repondu    ");
}

 
  //*****************************BOUTON1 (equipe A)****************************************************************

  if (etat1 == 0) //attente bouton1
  {
    // ************************** Fonction bouton 1 de cinq à huit joueurs  ********************************
    if ((!etatPinBouton1) && (stock1 == 0) && (stock2 == 0) && (stock3 == 0) && (stock4 == 0) && (stock5 == 0) && (stock6 == 0) && (stock7 == 0) && (stock8 == 0) && (maintien1 == 0) && (nombreDeJoueurs > 4))//si bouton1 appuyé (donc le pin indique 0 car il est en mode INPUT_PULLUP)
    {
      // on passe à l'état bouton1 pressé
      etat1 = 1;
      maintien1 = 1;
      // et on ajoute les points
      stock1 = stock1 + nombreDePoints;  
       //Allumage leds
      digitalWrite(pinLed1, HIGH);//on allume la LED 1 
        
    }
    // ************************** Fonction bouton 1 de deux à quatre joueurs  ********************************
    else if ((!etatPinBouton1) && (stock1 == 0) && (stock2 == 0) && (stock3 == 0) && (stock4 == 0) && (stock5 == 0) && (stock6 == 0) && (stock7 == 0) && (stock8 == 0) && (maintien1 == 0) && (nombreDeJoueurs < 5))//si bouton1 appuyé (donc le pin indique 0 car il est en mode INPUT_PULLUP)
    {
      // on passe à l'état bouton1 pressé
      etat1 = 1;
      maintien1 = 1;
      // et on ajoute les points
      stock1 = stock1 + nombreDePoints;  
       //Allumage leds
      digitalWrite(pinLed1, HIGH);//on allume la LED 1 
      digitalWrite(pinLed5, HIGH);//on allume la LED 5
        
    }
  }
  else if (etat1 == 1) // bouton1 pressé
  {
    if (etatPinBouton1)//si bouton1 relaché (donc le pin indique 1 car il est en mode INPUT_PULLUP)
    {
      // on passe à l'état bouton1 relaché
      etat1 = 0;
    }
  }

  //*****************************BOUTON2 (equipe B)****************************************************************

  if (etat2 == 0) //attente bouton2
  {
    // ************************** Fonction bouton 2 de cinq à huit joueurs  ********************************
    if ((!etatPinBouton2) && (stock1 == 0) && (stock2 == 0) && (stock3 == 0) && (stock4 == 0) && (stock5 == 0) && (stock6 == 0) && (stock7 == 0) && (stock8 == 0) && (maintien2 == 0) && (nombreDeJoueurs > 4)) //si bouton2 appuyé (donc le pin indique 0 car il est en mode INPUT_PULLUP)
    {
      // on passe à l'état bouton2 pressé
      etat2 = 1;
      maintien2 = 1;
      // et on ajoute les points
      stock2 = stock2 + nombreDePoints;
      //Allumage leds
      digitalWrite(pinLed2, HIGH);//on allume la LED 2
    }
    // ************************** Fonction bouton 2 de deux à quatre joueurs  ********************************
    else if ((!etatPinBouton2) && (stock1 == 0) && (stock2 == 0) && (stock3 == 0) && (stock4 == 0) && (stock5 == 0) && (stock6 == 0) && (stock7 == 0) && (stock8 == 0) && (maintien2 == 0) && (nombreDeJoueurs < 5)) //si bouton2 appuyé (donc le pin indique 0 car il est en mode INPUT_PULLUP)
    {
      // on passe à l'état bouton2 pressé
      etat2 = 1;
      maintien2 = 1;
      // et on ajoute les points
      stock2 = stock2 + nombreDePoints;
      //Allumage leds
      digitalWrite(pinLed2, HIGH);//on allume la LED 2
      digitalWrite(pinLed6, HIGH);//on allume la LED 6
    }
  }
  else if (etat2 == 1) // bouton2 pressé
  {
    if (etatPinBouton2)//si bouton2 relaché (donc le pin indique 1 car il est en mode INPUT_PULLUP)
    {
      // on passe à l'état bouton2 relaché
      etat2 = 0;
    }
  }

  //*****************************BOUTON3  (equipe C)****************************************************************

  if (etat3 == 0) //attente bouton3
  {
    // ************************** Fonction bouton 3 de cinq à huit joueurs  ********************************
    if ((!etatPinBouton3) && (stock1 == 0) && (stock2 == 0) && (stock3 == 0) && (stock4 == 0) && (stock5 == 0) && (stock6 == 0) && (stock7 == 0) && (stock8 == 0) && (maintien3 == 0) && (nombreDeJoueurs > 4)) //si bouton3 appuyé (donc le pin indique 0 car il est en mode INPUT_PULLUP)
    {
      // on passe à l'état bouton3 pressé
      etat3 = 1;
      maintien3 = 1;
      // et on ajoute les points
      stock3 = stock3 + nombreDePoints;
      //Allumage leds
      digitalWrite(pinLed3, HIGH);//on allume la LED 3
    }
    // ************************** Fonction bouton 3 de trois à quatre joueurs  ********************************
    else if ((!etatPinBouton3) && (stock1 == 0) && (stock2 == 0) && (stock3 == 0) && (stock4 == 0) && (stock5 == 0) && (stock6 == 0) && (stock7 == 0) && (stock8 == 0) && (maintien3 == 0) && (nombreDeJoueurs > 2) && (5 > nombreDeJoueurs)) //si bouton3 appuyé (donc le pin indique 0 car il est en mode INPUT_PULLUP)
    {
      // on passe à l'état bouton3 pressé
      etat3 = 1;
      maintien3 = 1;
      // et on ajoute les points
      stock3 = stock3 + nombreDePoints;
      //Allumage leds
      digitalWrite(pinLed3, HIGH);//on allume la LED 3
      digitalWrite(pinLed7, HIGH);//on allume la LED 7
    }
  }
  else if (etat3 == 1) // bouton3 pressé
  {
    if (etatPinBouton3)//si bouton3 relaché (donc le pin indique 1 car il est en mode INPUT_PULLUP)
    {
      // on passe à l'état bouton3 relaché
      etat3 = 0;
    }
  }

  //*****************************BOUTON4  (equipe D)****************************************************************

  if (etat4 == 0) //attente bouton4
  {
    // ************************** Fonction bouton 4 de cinq à huit joueurs  ********************************
    if ((!etatPinBouton4) && (stock1 == 0) && (stock2 == 0) && (stock3 == 0) && (stock4 == 0) && (stock5 == 0) && (stock6 == 0) && (stock7 == 0) && (stock8 == 0) && (maintien4 == 0) && (nombreDeJoueurs > 4))//si bouton4 appuyé (donc le pin indique 0 car il est en mode INPUT_PULLUP)
    {
    
      // on passe à l'état bouton4 pressé
      etat4 = 1;
      maintien4 = 1;
      // et on ajoute les points
      stock4 = stock4 + nombreDePoints;
      //Allumage leds
      digitalWrite(pinLed4, HIGH);//on allume la LED 4
    }
    // ************************** Fonction bouton 4 à quatre joueurs  ********************************
    else if ((!etatPinBouton4) && (stock1 == 0) && (stock2 == 0) && (stock3 == 0) && (stock4 == 0) && (stock5 == 0) && (stock6 == 0) && (stock7 == 0) && (stock8 == 0) && (maintien4 == 0) && (nombreDeJoueurs == 4))//si bouton4 appuyé (donc le pin indique 0 car il est en mode INPUT_PULLUP)
    {
    
      // on passe à l'état bouton4 pressé
      etat4 = 1;
      maintien4 = 1;
      // et on ajoute les points
      stock4 = stock4 + nombreDePoints;
      //Allumage leds
      digitalWrite(pinLed4, HIGH);//on allume la LED 4
      digitalWrite(pinLed8, HIGH);//on allume la LED 8
    }
  }
  else if (etat4 == 1) // bouton4 pressé
  {
    if (etatPinBouton4)//si bouton4 relaché (donc le pin indique 1 car il est en mode INPUT_PULLUP)
    {
      // on passe à l'état bouton4 relaché
      etat4 = 0;
    }
  }

  //*****************************BOUTON5  (equipe E)****************************************************************

  if (etat5 == 0) //attente bouton5
  {
    // ************************** Fonction bouton 5 de cinq à huit joueurs  ********************************
    if ((!etatPinBouton5) && (stock1 == 0) && (stock2 == 0) && (stock3 == 0) && (stock4 == 0) && (stock5 == 0) && (stock6 == 0) && (stock7 == 0) && (stock8 == 0) && (maintien5 == 0) && (nombreDeJoueurs > 4)) //si bouton5 appuyé (donc le pin indique 0 car il est en mode INPUT_PULLUP)
    {
      // on passe à l'état bouton5 pressé
      etat5 = 1;
      maintien5 = 1;
      // et on ajoute les points
      stock5 = stock5 + nombreDePoints;
      //Allumage leds
      digitalWrite(pinLed5, HIGH);//on allume la LED 5
    }
    // ************************** Fonction bouton 5 de deux à quatres joueurs  ********************************
    else if ((!etatPinBouton5) && (stock1 == 0) && (stock2 == 0) && (stock3 == 0) && (stock4 == 0) && (stock5 == 0) && (stock6 == 0) && (stock7 == 0) && (stock8 == 0) && (maintien1 == 0) && (nombreDeJoueurs <5)) //si bouton5 appuyé (donc le pin indique 0 car il est en mode INPUT_PULLUP)
    {
      // on passe à l'état bouton5 pressé
      etat5 = 1;
      maintien1 = 1;
      // et on ajoute les points
      stock1 = stock1 + nombreDePoints;
      //Allumage leds
      digitalWrite(pinLed5, HIGH);//on allume la LED 5
      digitalWrite(pinLed1, HIGH);//on allume la LED 1
    }
  }
  else if (etat5 == 1) // bouton5 pressé
  {
    if (etatPinBouton5)//si bouton5 relaché (donc le pin indique 1 car il est en mode INPUT_PULLUP)
    {
      // on passe à l'état bouton5 relaché
      etat5 = 0;
    }
    
  }
  //*****************************BOUTON6  (equipe F)****************************************************************

  if (etat6 == 0) //attente bouton6
  {
    // ************************** Fonction bouton 6 de six à huit joueurs  ********************************
    if ((!etatPinBouton6) && (stock1 == 0) && (stock2 == 0) && (stock3 == 0) && (stock4 == 0) && (stock5 == 0) && (stock6 == 0) && (stock7 == 0) && (stock8 == 0) && (maintien6 == 0) && (nombreDeJoueurs > 5)) //si bouton6 appuyé (donc le pin indique 0 car il est en mode INPUT_PULLUP)
    {
      // on passe à l'état bouton6 pressé
      etat6 = 1;
      maintien6 = 1;
      // et on ajoute les points
      stock6 = stock6 + nombreDePoints;
      //Allumage leds
      digitalWrite(pinLed6, HIGH);//on allume la LED 6
    }
    // ************************** Fonction bouton 6 de deux à quatre joueurs  ********************************
    else if ((!etatPinBouton6) && (stock1 == 0) && (stock2 == 0) && (stock3 == 0) && (stock4 == 0) && (stock5 == 0) && (stock6 == 0) && (stock7 == 0) && (stock8 == 0) && (maintien2 == 0) && (nombreDeJoueurs < 5)) //si bouton6 appuyé (donc le pin indique 0 car il est en mode INPUT_PULLUP)
    {
      // on passe à l'état bouton6 pressé
      etat6 = 1;
      maintien2 = 1;
      // et on ajoute les points
      stock2 = stock2 + nombreDePoints;
      //Allumage leds
      digitalWrite(pinLed6, HIGH);//on allume la LED 6
      digitalWrite(pinLed2, HIGH);//on allume la LED 2
    }
  }
  else if (etat6 == 1) // bouton6 pressé
  {
    if (etatPinBouton6)//si bouton6 relaché (donc le pin indique 1 car il est en mode INPUT_PULLUP)
    {
      // on passe à l'état bouton6 relaché
      etat6 = 0;
    }
  }

  //*****************************BOUTON7 (equipe G)****************************************************************

  if (etat7 == 0) //attente bouton7
  {
    // ************************** Fonction bouton 7 de sept à huit joueurs  ********************************
    if ((!etatPinBouton7) && (stock1 == 0) && (stock2 == 0) && (stock3 == 0) && (stock4 == 0) && (stock5 == 0) && (stock6 == 0) && (stock7 == 0) && (stock8 == 0) && (maintien7 == 0) && (nombreDeJoueurs > 6)) //si bouton7 appuyé (donc le pin indique 0 car il est en mode INPUT_PULLUP)
    {
      // on passe à l'état bouton7 pressé
      etat7 = 1;
      maintien7 = 1;
      // et on ajoute les points
      stock7 = stock7 + nombreDePoints;
      //Allumage leds
      digitalWrite(pinLed7, HIGH);//on allume la LED 7
    }
    // ************************** Fonction bouton 7 de trois à quatre joueurs  ********************************
    else if ((!etatPinBouton7) && (stock1 == 0) && (stock2 == 0) && (stock3 == 0) && (stock4 == 0) && (stock5 == 0) && (stock6 == 0) && (stock7 == 0) && (stock8 == 0) && (maintien3 == 0) && (nombreDeJoueurs > 2) && (5 > nombreDeJoueurs) ) //si bouton7 appuyé (donc le pin indique 0 car il est en mode INPUT_PULLUP)
    {
      // on passe à l'état bouton7 pressé
      etat7 = 1;
      maintien3 = 1;
      // et on ajoute les points
      stock3 = stock3 + nombreDePoints;
      //Allumage leds
      digitalWrite(pinLed7, HIGH);//on allume la LED 7
      digitalWrite(pinLed3, HIGH);//on allume la LED 3
    }
  }
  else if (etat7 == 1) // bouton4 pressé
  {
    if (etatPinBouton7)//si bouton7 relaché (donc le pin indique 1 car il est en mode INPUT_PULLUP)
    {
      // on passe à l'état bouton7 relaché
      etat7 = 0;
    }
  }

  //*****************************BOUTON8(equipe H)****************************************************************

  if (etat8 == 0) //attente bouton8
  {
    // ************************** Fonction bouton 8 pour huit joueurs  ********************************
    if ((!etatPinBouton8) && (stock1 == 0) && (stock2 == 0) && (stock3 == 0) && (stock4 == 0) && (stock5 == 0) && (stock6 == 0) && (stock7 == 0) && (stock8 == 0) && (maintien8 == 0) && (nombreDeJoueurs > 7)) //si bouton8 appuyé (donc le pin indique 0 car il est en mode INPUT_PULLUP)
    {
      // on passe à l'état bouton8 pressé
      etat8 = 1;
      maintien8 = 1;
      // et on ajoute les points
      stock8 = stock8 + nombreDePoints;
      //Allumage leds
      digitalWrite(pinLed8, HIGH);//on allume la LED 8
    }
    // ************************** Fonction bouton 8 pour quatre joueurs  ********************************
    else if ((!etatPinBouton8) && (stock1 == 0) && (stock2 == 0) && (stock3 == 0) && (stock4 == 0) && (stock5 == 0) && (stock6 == 0) && (stock7 == 0) && (stock8 == 0) && (maintien4 == 0) && (nombreDeJoueurs == 4)) //si bouton8 appuyé (donc le pin indique 0 car il est en mode INPUT_PULLUP)
    {
      // on passe à l'état bouton8 pressé
      etat8 = 1;
      maintien4 = 1;
      // et on ajoute les points
      stock4 = stock4 + nombreDePoints;
      //Allumage leds
      digitalWrite(pinLed8, HIGH);//on allume la LED 8
      digitalWrite(pinLed4, HIGH);//on allume la LED 4
    }
  }
  else if (etat8 == 1) // bouton8 pressé
  {
    if (etatPinBouton8)//si bouton8 relaché (donc le pin indique 1 car il est en mode INPUT_PULLUP)
    {
      // on passe à l'état bouton8 relaché
      etat8 = 0;
    }
  }

  //*****************************************tempo reponse************************************************************

   //if ((stock1 > 0) || (stock2 > 0) || (stock3 > 0) || (stock4 > 0) || (stock5 > 0) || (stock6 > 0) || (stock7 > 0) || (stock8 > 0))
   //{
    // if (t7 < 1000)
   //  {
      // t7 = t7 + 1;
     //  delay(1);
    // }
    // if (t7 == 1000)
    // {
     //  if (stock1 > 0)
      // {
       //  bloquage1 = 1;
      // }
      // if (stock2 > 0)
       //{
         //bloquage2 = 1;
      // }
      // if (stock3 > 0)
      // {
        // bloquage3 = 1;
      // }
      // if (stock4 > 0)
      // {
       //  bloquage4 = 1;
      // }
      // if (stock5 > 0)
      // {
      //   bloquage5 = 1;
      // }
      // if (stock6 > 0)
      // {
       //  bloquage6 = 1;
      // }
      // if (stock7 > 0)
      // {
       //  bloquage7 = 1;
      // }
      // if (stock8 > 0)
     //  {
      //   bloquage8 = 1;
      // }
      // et on reinitialise les stocks
     //  stock1 = 0;
      // stock2 = 0;
      // stock3 = 0;
      // stock4 = 0;
      // stock5 = 0;
      // stock6 = 0;
      // stock7 = 0;
     //  stock8 = 0;

      // Extinction des leds
      // digitalWrite(pinLed1, LOW); //on éteint la LED 1
      // digitalWrite(pinLed2, LOW); //on éteint la LED 2
      // digitalWrite(pinLed3, LOW); //on éteint la LED 3
      // digitalWrite(pinLed4, LOW); //on éteint la LED 4
      // digitalWrite(pinLed5, LOW); //on éteint la LED 5
      // digitalWrite(pinLed6, LOW); //on éteint la LED 6
     //  digitalWrite(pinLed7, LOW); //on éteint la LED 7
     //  digitalWrite(pinLed8, LOW); //on éteint la LED 8

     //  lcd.clear();//reset LCD
      
    //   t7 = 0;
      
   //  }
  // }
  //******************************Validation arbitre****************************************************


  //*****************************Bouton Oui*************************************************

  if (etatOui == 0) //attente boutonOui
  {
    if (!etatPinBoutonOui)//si boutonOui appuyé (donc le pin indique 0 car il est en mode INPUT_PULLUP)
    {
      if ((stock1 > 0) || (stock2 > 0) || (stock3 > 0) || (stock4 > 0) || (stock5 > 0) || (stock6 > 0) || (stock7 > 0) || (stock8 > 0))
      {
        // on passe à l'état boutonOui pressé
        etatOui = 1;

        // et on ajoute les points
        pointsEquipe1 = pointsEquipe1 + stock1;
        pointsEquipe2 = pointsEquipe2 + stock2;
        pointsEquipe3 = pointsEquipe3 + stock3;
        pointsEquipe4 = pointsEquipe4 + stock4;
        pointsEquipe5 = pointsEquipe5 + stock5;
        pointsEquipe6 = pointsEquipe6 + stock6;
        pointsEquipe7 = pointsEquipe7 + stock7;
        pointsEquipe8 = pointsEquipe8 + stock8;
        EEPROM.update (1, pointsEquipe1); // maj point en memoire
        EEPROM.update (2, pointsEquipe2); // maj point en memoire
        EEPROM.update (3, pointsEquipe3); // maj point en memoire
        EEPROM.update (4, pointsEquipe4); // maj point en memoire
        EEPROM.update (5, pointsEquipe5); // maj point en memoire
        EEPROM.update (6, pointsEquipe6); // maj point en memoire
        EEPROM.update (7, pointsEquipe7); // maj point en memoire
        EEPROM.update (8, pointsEquipe8); // maj point en memoire
        stock1 = 0;
        stock2 = 0;
        stock3 = 0;
        stock4 = 0;
        stock5 = 0;
        stock6 = 0;
        stock7 = 0;
        stock8 = 0;
        maintien1 = 0;
        maintien2 = 0;
        maintien3 = 0;
        maintien4 = 0;
        maintien5 = 0;
        maintien6 = 0;
        maintien7 = 0;
        maintien8 = 0;
        bloquage1 = 0;
        bloquage2 = 0;
        bloquage3 = 0;
        bloquage4 = 0;
        bloquage5 = 0;
        bloquage6 = 0;
        bloquage7 = 0;
        bloquage8 = 0;
        t7 = 0;

        // Extinction des leds
        digitalWrite(pinLed1, LOW); //on éteint la LED 1
        digitalWrite(pinLed2, LOW); //on éteint la LED 2
        digitalWrite(pinLed3, LOW); //on éteint la LED 3
        digitalWrite(pinLed4, LOW); //on éteint la LED 4
        digitalWrite(pinLed5, LOW); //on éteint la LED 5
        digitalWrite(pinLed6, LOW); //on éteint la LED 6
        digitalWrite(pinLed7, LOW); //on éteint la LED 7
        digitalWrite(pinLed8, LOW); //on éteint la LED 8

        lcd.clear();//reset LCD
      }
    }
  }
  else if (etatOui == 1) // boutonOui pressé
  {
    if (etatPinBoutonOui)//si boutonOui relaché (donc le pin indique 1 car il est en mode INPUT_PULLUP)
    {

      // on passe à l'état boutonOui relaché
      etatOui = 0;
    }
  }

  //*****************************Bouton Non*************************************************

  if (etatNon == 0) //attente boutonNon
  {
    if (etatPinBoutonNon)// (Bouton cablé en NC) si boutonNonappuyé (donc le pin indique 0 car il est en mode INPUT_PULLUP)
    {
      // on passe à l'état boutonNon pressé
      etatNon = 1;
      if (stock1 > 0)
      {
        bloquage1 = 1;
      }
      if (stock2 > 0)
      {
        bloquage2 = 1;
      }
      if (stock3 > 0)
      {
        bloquage3 = 1;
      }
      if (stock4 > 0)
      {
        bloquage4 = 1;
      }
      if (stock5 > 0)
      {
        bloquage5 = 1;
      }
      if (stock6 > 0)
      {
        bloquage6 = 1;
      }
      if (stock7 > 0)
      {
        bloquage7 = 1;
      }
      if (stock8 > 0)
      {
        bloquage8 = 1;
      }
      // et on reinitialise les stocks
      stock1 = 0;
      stock2 = 0;
      stock3 = 0;
      stock4 = 0;
      stock5 = 0;
      stock6 = 0;
      stock7 = 0;
      stock8 = 0;
      t7 = 0;

      // Extinction des leds
      digitalWrite(pinLed1, LOW); //on éteint la LED 1
      digitalWrite(pinLed2, LOW); //on éteint la LED 2
      digitalWrite(pinLed3, LOW); //on éteint la LED 3
      digitalWrite(pinLed4, LOW); //on éteint la LED 4
      digitalWrite(pinLed5, LOW); //on éteint la LED 5
      digitalWrite(pinLed6, LOW); //on éteint la LED 6
      digitalWrite(pinLed7, LOW); //on éteint la LED 7
      digitalWrite(pinLed8, LOW); //on éteint la LED 8

      lcd.clear();//reset LCD
    }
  }
  else if (etatNon == 1) // boutonNon pressé
  {
    if (!etatPinBoutonNon)// (Bouton cablé en NC) si boutonNon relaché (donc le pin indique 1 car il est en mode INPUT_PULLUP)
    {

      // on passe à l'état boutonNon relaché
      etatNon = 0;
    }
  }

  //*****************************Bouton Reset*************************************************

  if (etatReset == 0) //attente boutonReset
  {
    if (!etatPinBoutonReset) //si boutonReset appuyé (donc le pin indique 0 car il est en mode INPUT_PULLUP)
    {
      // on passe à l'état boutonReset pressé
      etatReset = 1;

      // et on reinitialise les maintiens et les stocks
      maintien1 = 0;
      maintien2 = 0;
      maintien3 = 0;
      maintien4 = 0;
      maintien5 = 0;
      maintien6 = 0;
      maintien7 = 0;
      maintien8 = 0;
      bloquage1 = 0;
      bloquage2 = 0;
      bloquage3 = 0;
      bloquage4 = 0;
      bloquage5 = 0;
      bloquage6 = 0;
      bloquage7 = 0;
      bloquage8 = 0;
      stock1 = 0;
      stock2 = 0;
      stock3 = 0;
      stock4 = 0;
      stock5 = 0;
      stock6 = 0;
      stock7 = 0;
      stock8 = 0;
      t7 = 0;

      //extinction des leds
      digitalWrite(pinLed1, LOW);//on eteind la LED 1
      digitalWrite(pinLed3, LOW);//on eteind la LED 3
      digitalWrite(pinLed4, LOW);//on eteind la LED 4
      digitalWrite(pinLed5, LOW);//on eteind la LED 5
      digitalWrite(pinLed6, LOW);//on eteind la LED 6
      digitalWrite(pinLed7, LOW);//on eteind la LED 7
      digitalWrite(pinLed2, LOW);//on eteind la LED 2
      digitalWrite(pinLed8, LOW);//on eteind la LED 8

      lcd.clear();//reset LCD
    }
  }
  else if (etatReset == 1) // boutonReset pressé
  {
    if (etatPinBoutonReset)//si boutonReset relaché (donc le pin indique 1 car il est en mode INPUT_PULLUP)
    {

      // on passe à l'état boutonReset relaché
      etatReset = 0;
    }
  }
  //*******************************Bouton des points*********************************

  if (etatPoints == 0) //attente boutonPoints
  {
    if (!etatPinBoutonPoints)//si boutonPoints appuyé (donc le pin indique 0 car il est en mode INPUT_PULLUP)
    {
      // on passe à l'état boutonPointspressé
      etatPoints = 1;

      if (nombreDePoints == 100)
      {
        nombreDePoints = 0;
        lcd.clear();
      }
      if (nombreDePoints == 10)
      {
        nombreDePoints = 100;
      }
      if (nombreDePoints == 5)
      {
        nombreDePoints = 10;
      }
      if (nombreDePoints == 2)
      {
        nombreDePoints = 5;
      }
      if (nombreDePoints == 1)
      {
        nombreDePoints = 2;
      }
      if (nombreDePoints == 0)
      {
        nombreDePoints = 1;
      }
    }
  }
  else if (etatPoints == 1) // boutonPoints pressé
  {
    if (etatPinBoutonPoints)//si boutonPoints relaché (donc le pin indique 1 car il est en mode INPUT_PULLUP)
    {
      // on passe à l'état boutonPoints relaché
      etatPoints = 0;
    }
  }

  //*******************************Boutons de punitions*********************************

  //**********************************Punition Equipe 1 ****************************************

  if (etatPun1 == 0) //attente boutonPun1
  {
    if ((!etatPinBoutonPun1) & (maintienPun1 == 0)) //si boutonPun1 appuyé (donc le pin indique 0 car il est en mode INPUT_PULLUP)
    {

      etatPun1 = 1;
      lcd.clear();//reset LCD

      do {
        maintienPun1 = 1;
        etatPinBoutonPun1 = digitalRead(pinBoutonPun1);
        etatPinBoutonPun2 = digitalRead(pinBoutonPun2);

        
        
       if (nombreDeJoueurs > 3 )
{
        // place le curseur colonne 0, ligne 0
        lcd.setCursor(0, 0);
        // Ecrit sur LCD.
        lcd.print("[A]  B   C   D   ");
        // place le curseur colonne 2, ligne 1
        lcd.setCursor(1, 1);
        // ecrit pointsequipe1
        lcd.print(pointsEquipe1);
        // place le curseur colonne 06, ligne 1
        lcd.setCursor(5, 2);
        // ecrit pointsequipe2
        lcd.print(pointsEquipe2);
        // place le curseur colonne 10, ligne 1
        lcd.setCursor(9, 2);
        // ecrit pointsequipe3
        lcd.print(pointsEquipe3);
        // place le curseur colonne 14, ligne 1
        lcd.setCursor(13, 2);
        // ecrit pointsequipe4
        lcd.print(pointsEquipe4);
}

if (nombreDeJoueurs == 3 )
{
        // place le curseur colonne 0, ligne 0
        lcd.setCursor(0, 0);
        // Ecrit sur LCD.
        lcd.print("[A]  B   C       ");
        // place le curseur colonne 2, ligne 1
        lcd.setCursor(1, 1);
        // ecrit pointsequipe1
        lcd.print(pointsEquipe1);
        // place le curseur colonne 06, ligne 1
        lcd.setCursor(5, 2);
        // ecrit pointsequipe2
        lcd.print(pointsEquipe2);
        // place le curseur colonne 10, ligne 1
        lcd.setCursor(9, 2);
        // ecrit pointsequipe3
        lcd.print(pointsEquipe3);      
}

if (nombreDeJoueurs == 2 )
{
        // place le curseur colonne 0, ligne 0
        lcd.setCursor(0, 0);
        // Ecrit sur LCD.
        lcd.print("[A]  B           ");
        // place le curseur colonne 2, ligne 1
        lcd.setCursor(1, 1);
        // ecrit pointsequipe1
        lcd.print(pointsEquipe1);
        // place le curseur colonne 06, ligne 1
        lcd.setCursor(5, 2);
        // ecrit pointsequipe2
        lcd.print(pointsEquipe2);
       
}
        if (etatPun2 == 0) //attente boutonPun2
        {
          if ((!etatPinBoutonPun2) & (maintienPun2 == 0)) //si boutonPun2 appuyé (donc le pin indique 0 car il est en mode INPUT_PULLUP)
          {
            // on passe à l'état boutonPun2 pressé
            etatPun2 = 1;
            maintienPun2 = 1;
            Punition(1);
          }
        }
        else if (etatPun2 == 1) // boutonPun2 pressé
        {
          if (etatPinBoutonPun2)//si boutonPun2 relaché (donc le pin indique 1 car il est en mode INPUT_PULLUP)
          {
            // on passe à l'état boutonPun2 relaché
            etatPun2 = 0;
            maintienPun2 = 0;
          }
        }


        if (etatPinBoutonPun1)//si BoutonPun1 relaché (donc le pin indique 1 car il est en mode INPUT_PULLUP)
        {
          // on passe à l'état BoutonPun1 relaché
          etatPun1 = 0;

        }

        if (etatPun1 == 0) //attente boutonPun1
        {
          if (!etatPinBoutonPun1)
          {
            etatPun1 = 1;
            maintienPun1 = 0;
          }
        }
      } while (maintienPun1 == 1);

      etatPun1 = 1;


      //**********************************Punition Equipe 2 ****************************************
      
      do {
        maintienPun1 = 1;
        etatPinBoutonPun1 = digitalRead(pinBoutonPun1);
        etatPinBoutonPun2 = digitalRead(pinBoutonPun2);


        

        
        if (nombreDeJoueurs > 3 )
{
        // place le curseur colonne 0, ligne 0
        lcd.setCursor(0, 0);
        // Ecrit sur LCD.
        lcd.print(" A  [B]  C   D   ");
        // place le curseur colonne 2, ligne 1
        lcd.setCursor(1, 1);
        // ecrit pointsequipe1
        lcd.print(pointsEquipe1);
        // place le curseur colonne 06, ligne 1
        lcd.setCursor(5, 2);
        // ecrit pointsequipe2
        lcd.print(pointsEquipe2);
        // place le curseur colonne 10, ligne 1
        lcd.setCursor(9, 2);
        // ecrit pointsequipe3
        lcd.print(pointsEquipe3);
        // place le curseur colonne 14, ligne 1
        lcd.setCursor(13, 2);
        // ecrit pointsequipe4
        lcd.print(pointsEquipe4);
}

if (nombreDeJoueurs == 3 )
{
        // place le curseur colonne 0, ligne 0
        lcd.setCursor(0, 0);
        // Ecrit sur LCD.
        lcd.print(" A  [B]  C       ");
        // place le curseur colonne 2, ligne 1
        lcd.setCursor(1, 1);
        // ecrit pointsequipe1
        lcd.print(pointsEquipe1);
        // place le curseur colonne 06, ligne 1
        lcd.setCursor(5, 2);
        // ecrit pointsequipe2
        lcd.print(pointsEquipe2);
        // place le curseur colonne 10, ligne 1
        lcd.setCursor(9, 2);
        // ecrit pointsequipe3
        lcd.print(pointsEquipe3);      
}

if (nombreDeJoueurs == 2 )
{
        // place le curseur colonne 0, ligne 0
        lcd.setCursor(0, 0);
        // Ecrit sur LCD.
        lcd.print(" A  [B]          ");
        // place le curseur colonne 2, ligne 1
        lcd.setCursor(1, 1);
        // ecrit pointsequipe1
        lcd.print(pointsEquipe1);
        // place le curseur colonne 06, ligne 1
        lcd.setCursor(5, 2);
        // ecrit pointsequipe2
        lcd.print(pointsEquipe2);
       
}

        if (etatPun2 == 0) //attente boutonPun2
        {
          if ((!etatPinBoutonPun2) & (maintienPun2 == 0)) //si boutonPun2 appuyé (donc le pin indique 0 car il est en mode INPUT_PULLUP)
          {
            // on passe à l'état boutonPun2 pressé
            etatPun2 = 1;
            maintienPun2 = 1;
            Punition(2);
          }
        }
        else if (etatPun2 == 1) // boutonPun2 pressé
        {
          if (etatPinBoutonPun2)//si boutonPun2 relaché (donc le pin indique 1 car il est en mode INPUT_PULLUP)
          {
            // on passe à l'état boutonPun2 relaché
            etatPun2 = 0;
            maintienPun2 = 0;
          }
        }

        if (etatPinBoutonPun1)//si BoutonPun1 relaché (donc le pin indique 1 car il est en mode INPUT_PULLUP)
        {
          // on passe à l'état BoutonPun1 relaché
          etatPun1 = 0;

        }

        if (etatPun1 == 0) //attente boutonPun1
        {
          if (!etatPinBoutonPun1)
          {
            etatPun1 = 1;
            maintienPun1 = 0;
          }
        }
      } while (maintienPun1 == 1);
      etatPun1 = 1;

      //**********************************Punition Equipe 3 ****************************************
      if (nombreDeJoueurs > 2 )
      {
        
        do {
          maintienPun1 = 1;
          etatPinBoutonPun1 = digitalRead(pinBoutonPun1);
          etatPinBoutonPun2 = digitalRead(pinBoutonPun2);


         

        if (nombreDeJoueurs > 3 )
{
        // place le curseur colonne 0, ligne 0
        lcd.setCursor(0, 0);
        // Ecrit sur LCD.
        lcd.print(" A   B  [C]  D   ");
        // place le curseur colonne 2, ligne 1
        lcd.setCursor(1, 1);
        // ecrit pointsequipe1
        lcd.print(pointsEquipe1);
        // place le curseur colonne 06, ligne 1
        lcd.setCursor(5, 2);
        // ecrit pointsequipe2
        lcd.print(pointsEquipe2);
        // place le curseur colonne 10, ligne 1
        lcd.setCursor(9, 2);
        // ecrit pointsequipe3
        lcd.print(pointsEquipe3);
        // place le curseur colonne 14, ligne 1
        lcd.setCursor(13, 2);
        // ecrit pointsequipe4
        lcd.print(pointsEquipe4);
}

if (nombreDeJoueurs == 3 )
{
        // place le curseur colonne 0, ligne 0
        lcd.setCursor(0, 0);
        // Ecrit sur LCD.
        lcd.print(" A   B  [C]      ");
        // place le curseur colonne 2, ligne 1
        lcd.setCursor(1, 1);
        // ecrit pointsequipe1
        lcd.print(pointsEquipe1);
        // place le curseur colonne 06, ligne 1
        lcd.setCursor(5, 2);
        // ecrit pointsequipe2
        lcd.print(pointsEquipe2);
        // place le curseur colonne 10, ligne 1
        lcd.setCursor(9, 2);
        // ecrit pointsequipe3
        lcd.print(pointsEquipe3);      
}



          if (etatPun2 == 0) //attente boutonPun2
          {
            if ((!etatPinBoutonPun2) & (maintienPun2 == 0)) //si boutonPun2 appuyé (donc le pin indique 0 car il est en mode INPUT_PULLUP)
            {
              // on passe à l'état boutonPun2 pressé
              etatPun2 = 1;
              maintienPun2 = 1;
              Punition(3);
            }
          }
          else if (etatPun2 == 1) // boutonPun2 pressé
          {
            if (etatPinBoutonPun2)//si boutonPun2 relaché (donc le pin indique 1 car il est en mode INPUT_PULLUP)
            {
              // on passe à l'état boutonPun2 relaché
              etatPun2 = 0;
              maintienPun2 = 0;
            }
          }

          if (etatPinBoutonPun1)//si BoutonPun1 relaché (donc le pin indique 1 car il est en mode INPUT_PULLUP)
          {
            // on passe à l'état bBoutonPun1 relaché
            etatPun1 = 0;

          }

          if (etatPun1 == 0) //attente boutonPun1
          {
            if (!etatPinBoutonPun1)
            {
              etatPun1 = 1;
              maintienPun1 = 0;
            }
          }
        } while (maintienPun1 == 1);

        etatPun1 = 1;

      }
      //**********************************Punition Equipe 4 ****************************************
      if (nombreDeJoueurs > 3 )
      {
       
        do {
          maintienPun1 = 1;
          etatPinBoutonPun1 = digitalRead(pinBoutonPun1);
          etatPinBoutonPun2 = digitalRead(pinBoutonPun2);


          

        // place le curseur colonne 0, ligne 0
        lcd.setCursor(0, 0);
        // Ecrit sur LCD.
        lcd.print(" A   B   C  [D]    ");
        // place le curseur colonne 2, ligne 1
        lcd.setCursor(1, 1);
        // ecrit pointsequipe1
        lcd.print(pointsEquipe1);
        // place le curseur colonne 06, ligne 1
        lcd.setCursor(5, 2);
        // ecrit pointsequipe2
        lcd.print(pointsEquipe2);
        // place le curseur colonne 10, ligne 1
        lcd.setCursor(9, 2);
        // ecrit pointsequipe3
        lcd.print(pointsEquipe3);
        // place le curseur colonne 14, ligne 1
        lcd.setCursor(13, 2);
        // ecrit pointsequipe4
        lcd.print(pointsEquipe4);

          if (etatPun2 == 0) //attente boutonPun2
          {
            if ((!etatPinBoutonPun2) & (maintienPun2 == 0)) //si boutonPun2 appuyé (donc le pin indique 0 car il est en mode INPUT_PULLUP)
            {
              // on passe à l'état boutonPun2 pressé
              etatPun2 = 1;
              maintienPun2 = 1;
              Punition(4);
            }
          }
          else if (etatPun2 == 1) // boutonPun2 pressé
          {
            if (etatPinBoutonPun2)//si boutonPun2 relaché (donc le pin indique 1 car il est en mode INPUT_PULLUP)
            {
              // on passe à l'état boutonPun2 relaché
              etatPun2 = 0;
              maintienPun2 = 0;
            }
          }

          if (etatPinBoutonPun1)//si BoutonPun1 relaché (donc le pin indique 1 car il est en mode INPUT_PULLUP)
          {
            // on passe à l'état BoutonPun1 relaché
            etatPun1 = 0;

          }

          if (etatPun1 == 0) //attente boutonPun1
          {
            if (!etatPinBoutonPun1)
            {
              etatPun1 = 1;
              maintienPun1 = 0;
            }
          }
        } while (maintienPun1 == 1);
        etatPun1 = 1;

      }
      //**********************************Punition Equipe 5 ****************************************
      if (nombreDeJoueurs > 4 )
      {
        lcd.clear();//reset LCD
        do {
          maintienPun1 = 1;
          etatPinBoutonPun1 = digitalRead(pinBoutonPun1);
          etatPinBoutonPun2 = digitalRead(pinBoutonPun2);


       

           if (nombreDeJoueurs ==8  )
{
        // place le curseur colonne 0, ligne 0
        lcd.setCursor(0, 0);
        // Ecrit sur LCD.
        lcd.print("[E]  F   G   H   ");
        // place le curseur colonne 2, ligne 1
        lcd.setCursor(1, 1);
        // ecrit pointsequipe5
        lcd.print(pointsEquipe5);
        // place le curseur colonne 06, ligne 1
        lcd.setCursor(5, 2);
        // ecrit pointsequipe6
        lcd.print(pointsEquipe6);
        // place le curseur colonne 10, ligne 1
        lcd.setCursor(9, 2);
        // ecrit pointsequipe7
        lcd.print(pointsEquipe7);
        // place le curseur colonne 14, ligne 1
        lcd.setCursor(13, 2);
        // ecrit pointsequipe8
        lcd.print(pointsEquipe8);
}

if (nombreDeJoueurs == 7 )
{
        // place le curseur colonne 0, ligne 0
        lcd.setCursor(0, 0);
        // Ecrit sur LCD.
        lcd.print("[E]  F   G       ");
        // place le curseur colonne 2, ligne 1
        lcd.setCursor(1, 1);
        // ecrit pointsequipe5
        lcd.print(pointsEquipe5);
        // place le curseur colonne 06, ligne 1
        lcd.setCursor(5, 2);
        // ecrit pointsequipe6
        lcd.print(pointsEquipe6);
        // place le curseur colonne 10, ligne 1
        lcd.setCursor(9, 2);
        // ecrit pointsequipe7
        lcd.print(pointsEquipe7);      
}

if (nombreDeJoueurs ==6 )
{
        // place le curseur colonne 0, ligne 0
        lcd.setCursor(0, 0);
        // Ecrit sur LCD.
        lcd.print("[E]  F           ");
        // place le curseur colonne 2, ligne 1
        lcd.setCursor(1, 1);
        // ecrit pointsequipe5
        lcd.print(pointsEquipe5);
        // place le curseur colonne 06, ligne 1
        lcd.setCursor(5, 2);
        // ecrit pointsequipe6
        lcd.print(pointsEquipe6);
}

if (nombreDeJoueurs ==5 )
{
        // place le curseur colonne 0, ligne 0
        lcd.setCursor(0, 0);
        // Ecrit sur LCD.
        lcd.print("[E]              ");
        // place le curseur colonne 2, ligne 1
        lcd.setCursor(1, 1);
        // ecrit pointsequipe5
        lcd.print(pointsEquipe5);
        
}
          if (etatPun2 == 0) //attente boutonPun2
          {
            if ((!etatPinBoutonPun2) & (maintienPun2 == 0)) //si boutonPun2 appuyé (donc le pin indique 0 car il est en mode INPUT_PULLUP)
            {
              // on passe à l'état boutonPun2 pressé
              etatPun2 = 1;
              maintienPun2 = 1;
              Punition(5);
            }
          }
          else if (etatPun2 == 1) // boutonPun2 pressé
          {
            if (etatPinBoutonPun2)//si boutonPun2 relaché (donc le pin indique 1 car il est en mode INPUT_PULLUP)
            {
              // on passe à l'état boutonPun2 relaché
              etatPun2 = 0;
              maintienPun2 = 0;
            }
          }
          if (etatPinBoutonPun1)//si BoutonPun1 relaché (donc le pin indique 1 car il est en mode INPUT_PULLUP)
          {
            // on passe à l'état BoutonPun1 relaché
            etatPun1 = 0;

          }

          if (etatPun1 == 0) //attente boutonPun1
          {
            if (!etatPinBoutonPun1)
            {
              etatPun1 = 1;
              maintienPun1 = 0;
            }
          }
        } while (maintienPun1 == 1);

        etatPun1 = 1;

      }
      //**********************************Punition Equipe 6 ****************************************
      if (nombreDeJoueurs > 5 )
      {
        lcd.clear();//reset LCD
        do {
          maintienPun1 = 1;
          etatPinBoutonPun1 = digitalRead(pinBoutonPun1);
          etatPinBoutonPun2 = digitalRead(pinBoutonPun2);
          
           if (nombreDeJoueurs ==8  )
{
        // place le curseur colonne 0, ligne 0
        lcd.setCursor(0, 0);
        // Ecrit sur LCD.
        lcd.print(" E  [F]  G   H   ");
        // place le curseur colonne 2, ligne 1
        lcd.setCursor(1, 1);
        // ecrit pointsequipe5
        lcd.print(pointsEquipe5);
        // place le curseur colonne 06, ligne 1
        lcd.setCursor(5, 2);
        // ecrit pointsequipe6
        lcd.print(pointsEquipe6);
        // place le curseur colonne 10, ligne 1
        lcd.setCursor(9, 2);
        // ecrit pointsequipe7
        lcd.print(pointsEquipe7);
        // place le curseur colonne 14, ligne 1
        lcd.setCursor(13, 2);
        // ecrit pointsequipe8
        lcd.print(pointsEquipe8);
}

if (nombreDeJoueurs == 7 )
{
        // place le curseur colonne 0, ligne 0
        lcd.setCursor(0, 0);
        // Ecrit sur LCD.
        lcd.print(" E  [F]  G       ");
        // place le curseur colonne 2, ligne 1
        lcd.setCursor(1, 1);
        // ecrit pointsequipe5
        lcd.print(pointsEquipe5);
        // place le curseur colonne 06, ligne 1
        lcd.setCursor(5, 2);
        // ecrit pointsequipe6
        lcd.print(pointsEquipe6);
        // place le curseur colonne 10, ligne 1
        lcd.setCursor(9, 2);
        // ecrit pointsequipe7
        lcd.print(pointsEquipe7);      
}

if (nombreDeJoueurs ==6 )
{
        // place le curseur colonne 0, ligne 0
        lcd.setCursor(0, 0);
        // Ecrit sur LCD.
        lcd.print(" E  [F]           ");
        // place le curseur colonne 2, ligne 1
        lcd.setCursor(1, 1);
        // ecrit pointsequipe5
        lcd.print(pointsEquipe5);
        // place le curseur colonne 06, ligne 1
        lcd.setCursor(5, 2);
        // ecrit pointsequipe6
        lcd.print(pointsEquipe6);
}

          if (etatPun2 == 0) //attente boutonPun2
          {
            if ((!etatPinBoutonPun2) & (maintienPun2 == 0)) //si boutonPun2 appuyé (donc le pin indique 0 car il est en mode INPUT_PULLUP)
            {
              // on passe à l'état boutonPun2 pressé
              etatPun2 = 1;
              maintienPun2 = 1;
              Punition(6);
            }
          }
          else if (etatPun2 == 1) // boutonPun2 pressé
          {
            if (etatPinBoutonPun2)//si boutonPun2 relaché (donc le pin indique 1 car il est en mode INPUT_PULLUP)
            {
              // on passe à l'état boutonPun2 relaché
              etatPun2 = 0;
              maintienPun2 = 0;
            }
          }
          if (etatPinBoutonPun1)//si BoutonPun1 relaché (donc le pin indique 1 car il est en mode INPUT_PULLUP)
          {
            // on passe à l'état BoutonPun1 relaché
            etatPun1 = 0;

          }

          if (etatPun1 == 0) //attente boutonPun1
          {
            if (!etatPinBoutonPun1)
            {
              etatPun1 = 1;
              maintienPun1 = 0;
            }
          }
        } while (maintienPun1 == 1);
        etatPun1 = 1;

      }
      //**********************************Punition Equipe 7 ****************************************
      if (nombreDeJoueurs > 6 )
      {
        lcd.clear();//reset LCD
        do {
          maintienPun1 = 1;
          etatPinBoutonPun1 = digitalRead(pinBoutonPun1);
          etatPinBoutonPun2 = digitalRead(pinBoutonPun2);

                    if (nombreDeJoueurs ==8  )
{
        // place le curseur colonne 0, ligne 0
        lcd.setCursor(0, 0);
        // Ecrit sur LCD.
        lcd.print(" E   F  [G]  H   ");
        // place le curseur colonne 2, ligne 1
        lcd.setCursor(1, 1);
        // ecrit pointsequipe5
        lcd.print(pointsEquipe5);
        // place le curseur colonne 06, ligne 1
        lcd.setCursor(5, 2);
        // ecrit pointsequipe6
        lcd.print(pointsEquipe6);
        // place le curseur colonne 10, ligne 1
        lcd.setCursor(9, 2);
        // ecrit pointsequipe7
        lcd.print(pointsEquipe7);
        // place le curseur colonne 14, ligne 1
        lcd.setCursor(13, 2);
        // ecrit pointsequipe8
        lcd.print(pointsEquipe8);
}

if (nombreDeJoueurs == 7 )
{
        // place le curseur colonne 0, ligne 0
        lcd.setCursor(0, 0);
        // Ecrit sur LCD.
        lcd.print(" E   F  [G]      ");
        // place le curseur colonne 2, ligne 1
        lcd.setCursor(1, 1);
        // ecrit pointsequipe5
        lcd.print(pointsEquipe5);
        // place le curseur colonne 06, ligne 1
        lcd.setCursor(5, 2);
        // ecrit pointsequipe6
        lcd.print(pointsEquipe6);
        // place le curseur colonne 10, ligne 1
        lcd.setCursor(9, 2);
        // ecrit pointsequipe7
        lcd.print(pointsEquipe7);      
}


          if (etatPun2 == 0) //attente boutonPun2
          {
            if ((!etatPinBoutonPun2) & (maintienPun2 == 0)) //si boutonPun2 appuyé (donc le pin indique 0 car il est en mode INPUT_PULLUP)
            {
              // on passe à l'état boutonPun2 pressé
              etatPun2 = 1;
              maintienPun2 = 1;
              Punition(7);
            }
          }
          else if (etatPun2 == 1) // boutonPun2 pressé
          {
            if (etatPinBoutonPun2)//si boutonPun2 relaché (donc le pin indique 1 car il est en mode INPUT_PULLUP)
            {
              // on passe à l'état boutonPun2 relaché
              etatPun2 = 0;
              maintienPun2 = 0;
            }
          }

          if (etatPinBoutonPun1)//si BoutonPun1 relaché (donc le pin indique 1 car il est en mode INPUT_PULLUP)
          {
            // on passe à l'état BoutonPun1 relaché
            etatPun1 = 0;

          }

          if (etatPun1 == 0) //attente boutonPun1
          {
            if (!etatPinBoutonPun1)
            {
              etatPun1 = 1;
              maintienPun1 = 0;
            }
          }
        } while (maintienPun1 == 1);

        etatPun1 = 1;

      }
      //**********************************Punition Equipe 8 ****************************************
      if (nombreDeJoueurs > 7 )
      {
        lcd.clear();//reset LCD
        do {
          maintienPun1 = 1;
          etatPinBoutonPun1 = digitalRead(pinBoutonPun1);
          etatPinBoutonPun2 = digitalRead(pinBoutonPun2);

          // place le curseur colonne 0, ligne 0
        lcd.setCursor(0, 0);
        // Ecrit sur LCD.
        lcd.print(" E   F   G  [H]    ");
        // place le curseur colonne 2, ligne 1
        lcd.setCursor(1, 1);
        // ecrit pointsequipe5
        lcd.print(pointsEquipe5);
        // place le curseur colonne 06, ligne 1
        lcd.setCursor(5, 2);
        // ecrit pointsequipe6
        lcd.print(pointsEquipe6);
        // place le curseur colonne 10, ligne 1
        lcd.setCursor(9, 2);
        // ecrit pointsequipe7
        lcd.print(pointsEquipe7);
        // place le curseur colonne 14, ligne 1
        lcd.setCursor(13, 2);
        // ecrit pointsequipe8
        lcd.print(pointsEquipe8);

          if (etatPun2 == 0) //attente boutonPun2
          {
            if ((!etatPinBoutonPun2) & (maintienPun2 == 0)) //si boutonPun2 appuyé (donc le pin indique 0 car il est en mode INPUT_PULLUP)
            {
              // on passe à l'état boutonPun2 pressé
              etatPun2 = 1;
              maintienPun2 = 1;
              Punition(8);
            }
          }
          else if (etatPun2 == 1) // boutonPun2 pressé
          {
            if (etatPinBoutonPun2)//si boutonPun2 relaché (donc le pin indique 1 car il est en mode INPUT_PULLUP)
            {
              // on passe à l'état boutonPun2 relaché
              etatPun2 = 0;
              maintienPun2 = 0;
            }
          }

          if (etatPinBoutonPun1)//si BoutonPun1 relaché (donc le pin indique 1 car il est en mode INPUT_PULLUP)
          {
            //on passe à l'état BoutonPun1 relaché
            etatPun1 = 0;

          }

          if (etatPun1 == 0) //attente boutonPun1
          {
            if (!etatPinBoutonPun1)
            {
              etatPun1 = 1;
              maintienPun1 = 0;

            }
          }
        } while (maintienPun1 == 1);
      }

      EEPROM.update (1, pointsEquipe1); // maj point en memoire
      EEPROM.update (2, pointsEquipe2); // maj point en memoire
      EEPROM.update (3, pointsEquipe3); // maj point en memoire
      EEPROM.update (4, pointsEquipe4); // maj point en memoire
      EEPROM.update (5, pointsEquipe5); // maj point en memoire
      EEPROM.update (6, pointsEquipe6); // maj point en memoire
      EEPROM.update (7, pointsEquipe7); // maj point en memoire
      EEPROM.update (8, pointsEquipe8); // maj point en memoire
      delay (2500);
      etatPun1 = 0;
      lcd.clear();//reset LCD

    }
  }
  //****************************************LEDS****************************************************************


  if (stock1 > 0) //equipe 1 a repondu
  {
    if (t3 < 50)
    {
      digitalWrite(pinLed2, HIGH);//on allume la LED 2
      if (nombreDeJoueurs > 2)
      {
        digitalWrite(pinLed3, HIGH);//on allume la LED 3
      }
      if (nombreDeJoueurs > 3)
      {
        digitalWrite(pinLed4, HIGH);//on allume la LED 4
      }
      if ((nombreDeJoueurs > 4) || (nombreDeJoueurs < 5))
      {
        digitalWrite(pinLed5, HIGH);//on allume la LED 5
      }
      if ((nombreDeJoueurs > 5) || (nombreDeJoueurs < 5))
      {
        digitalWrite(pinLed6, HIGH);//on allume la LED 6
      }
      if ((nombreDeJoueurs > 6) || ((nombreDeJoueurs < 5) && (nombreDeJoueurs > 2)))
      {
        digitalWrite(pinLed7, HIGH);//on allume la LED 7
      }
      if ((nombreDeJoueurs > 7) || (nombreDeJoueurs == 4))
      {
        digitalWrite(pinLed8, HIGH);//on allume la LED 8
      }
      t3 = t3 + 1; //tempo clignotage
      delay (1); //tempo clignotage
    }
    else
    {
      digitalWrite(pinLed2, LOW);//on eteind la LED 2
      digitalWrite(pinLed3, LOW);//on eteind la LED 3
      digitalWrite(pinLed4, LOW);//on eteind la LED 4
      if(nombreDeJoueurs > 4)
       {
      digitalWrite(pinLed5, LOW);//on eteind la LED 5
       }
      digitalWrite(pinLed6, LOW);//on eteind la LED 6
      digitalWrite(pinLed7, LOW);//on eteind la LED 7
      digitalWrite(pinLed8, LOW);//on eteind la LED 8
      t4 = t4 + 1; //tempo clignotage
      delay (1); //tempo clignotage
    }
    if (t4 == 50) //tempo clignotage
    {
      t3 = 0; //tempo clignotage
      t4 = 0; //tempo clignotage
    }


  }
  if (stock2 > 0) //equipe 2 a repondu
  {
    if (t3 < 50)
    {
      digitalWrite(pinLed1, HIGH);//on allume la LED 1
      if (nombreDeJoueurs > 2)
      {
        digitalWrite(pinLed3, HIGH);//on allume la LED 3
      }
      if (nombreDeJoueurs > 3)
      {
        digitalWrite(pinLed4, HIGH);//on allume la LED 4
      }
      if ((nombreDeJoueurs > 4) || (nombreDeJoueurs < 5))
      {
        digitalWrite(pinLed5, HIGH);//on allume la LED 5
      }
      if ((nombreDeJoueurs > 5) || (nombreDeJoueurs < 5))
      {
        digitalWrite(pinLed6, HIGH);//on allume la LED 6
      }
      if ((nombreDeJoueurs > 6) || ((nombreDeJoueurs < 5) && (nombreDeJoueurs > 2)))
      {
        digitalWrite(pinLed7, HIGH);//on allume la LED 7
      }
      if ((nombreDeJoueurs > 7) || (nombreDeJoueurs == 4))
      {
        digitalWrite(pinLed8, HIGH);//on allume la LED 8
      }
      t3 = t3 + 1; //tempo clignotage
      delay (1); //tempo clignotage
    }
    else
    {
      digitalWrite(pinLed1, LOW);//on eteind la LED 1
      digitalWrite(pinLed3, LOW);//on eteind la LED 3
      digitalWrite(pinLed4, LOW);//on eteind la LED 4
      digitalWrite(pinLed5, LOW);//on eteind la LED 5
      if(nombreDeJoueurs > 4)
       {
      digitalWrite(pinLed6, LOW);//on eteind la LED 6
       }
      digitalWrite(pinLed7, LOW);//on eteind la LED 7
      digitalWrite(pinLed8, LOW);//on eteind la LED 8
      t4 = t4 + 1; //tempo clignotage
      delay (1); //tempo clignotage
    }
    if (t4 == 50) //tempo clignotage
    {
      t3 = 0; //tempo clignotage
      t4 = 0; //tempo clignotage
    }
  }
  
  if (stock3 > 0) //equipe 3 a repondu
  {
    if (t3 < 50)
    {
      digitalWrite(pinLed1, HIGH);//on allume la LED 1
      digitalWrite(pinLed2, HIGH);//on allume la LED 2
      if (nombreDeJoueurs > 3)
      {
        digitalWrite(pinLed4, HIGH);//on allume la LED 4
      }
      if ((nombreDeJoueurs > 4) || (nombreDeJoueurs < 5))
      {
        digitalWrite(pinLed5, HIGH);//on allume la LED 5
      }
      if ((nombreDeJoueurs > 5) || (nombreDeJoueurs < 5))
      {
        digitalWrite(pinLed6, HIGH);//on allume la LED 6
      }
      if ((nombreDeJoueurs > 6) || ((nombreDeJoueurs < 5) && (nombreDeJoueurs > 2)))
      {
        digitalWrite(pinLed7, HIGH);//on allume la LED 7
      }
      if ((nombreDeJoueurs > 7) || (nombreDeJoueurs == 4))
      {
        digitalWrite(pinLed8, HIGH);//on allume la LED 8
      }
      t3 = t3 + 1; //tempo clignotage
      delay (1); //tempo clignotage
    }
    else
    {

      digitalWrite(pinLed1, LOW);//on eteind la LED 1
      digitalWrite(pinLed2, LOW);//on eteind la LED 2
      digitalWrite(pinLed4, LOW);//on eteind la LED 4
      digitalWrite(pinLed5, LOW);//on eteind la LED 5
      digitalWrite(pinLed6, LOW);//on eteind la LED 6
      if(nombreDeJoueurs > 4)
       {
      digitalWrite(pinLed7, LOW);//on eteind la LED 7
       }
      digitalWrite(pinLed8, LOW);//on eteind la LED 8
      t4 = t4 + 1; //tempo clignotage
      delay (1); //tempo clignotage
    }
    if (t4 == 50) //tempo clignotage
    {
      t3 = 0; //tempo clignotage
      t4 = 0; //tempo clignotage
    }
  }
  
  if (stock4 > 0) //equipe 4 a repondu
  {
    if (t3 < 50)
    {
      digitalWrite(pinLed1, HIGH);//on allume la LED 1
      if (nombreDeJoueurs > 2)
      {
        digitalWrite(pinLed3, HIGH);//on allume la LED 3
      }
      digitalWrite(pinLed2, HIGH);//on allume la LED 2
      if ((nombreDeJoueurs > 4) || (nombreDeJoueurs < 5))
      {
        digitalWrite(pinLed5, HIGH);//on allume la LED 5
      }
      if ((nombreDeJoueurs > 5) || (nombreDeJoueurs < 5))
      {
        digitalWrite(pinLed6, HIGH);//on allume la LED 6
      }
      if ((nombreDeJoueurs > 6) || ((nombreDeJoueurs < 5) && (nombreDeJoueurs > 2)))
      {
        digitalWrite(pinLed7, HIGH);//on allume la LED 7
      }
      if ((nombreDeJoueurs > 7) || (nombreDeJoueurs == 4))
      {
        digitalWrite(pinLed8, HIGH);//on allume la LED 8
      }
      t3 = t3 + 1; //tempo clignotage
      delay (1); //tempo clignotage
    }
    else
    {
      digitalWrite(pinLed1, LOW);//on eteind la LED 1
      digitalWrite(pinLed3, LOW);//on eteind la LED 3
      digitalWrite(pinLed2, LOW);//on eteind la LED 2
      digitalWrite(pinLed5, LOW);//on eteind la LED 5
      digitalWrite(pinLed6, LOW);//on eteind la LED 6
      digitalWrite(pinLed7, LOW);//on eteind la LED 7
     if(nombreDeJoueurs > 4)
       {
      digitalWrite(pinLed8, LOW);//on eteind la LED 8
       }
      t4 = t4 + 1; //tempo clignotage
      delay (1); //tempo clignotage
    }
    if (t4 == 50) //tempo clignotage
    {
      t3 = 0; //tempo clignotage
      t4 = 0; //tempo clignotage
    }
  }
  
  if (stock5 > 0) //equipe 5 a repondu
  {
    if (t3 < 50)
    {
      digitalWrite(pinLed1, HIGH);//on allume la LED 1
      if (nombreDeJoueurs > 2)
      {
        digitalWrite(pinLed3, HIGH);//on allume la LED 3
      }
      if (nombreDeJoueurs > 3)
      {
        digitalWrite(pinLed4, HIGH);//on allume la LED 4
      }
      digitalWrite(pinLed2, HIGH);//on allume la LED 2
      if (nombreDeJoueurs > 5)
      {
        digitalWrite(pinLed6, HIGH);//on allume la LED 6
      }
      if (nombreDeJoueurs > 6)
      {
        digitalWrite(pinLed7, HIGH);//on allume la LED 7
      }
      if (nombreDeJoueurs > 7)
      {
        digitalWrite(pinLed8, HIGH);//on allume la LED 8
      }
      t3 = t3 + 1; //tempo clignotage
      delay (1); //tempo clignotage
    }
    else
    {
      if(nombreDeJoueurs > 4)
      {
      digitalWrite(pinLed1, LOW);//on eteind la LED 1
      }
      digitalWrite(pinLed3, LOW);//on eteind la LED 3
      digitalWrite(pinLed4, LOW);//on eteind la LED 4
      digitalWrite(pinLed2, LOW);//on eteind la LED 2
      digitalWrite(pinLed6, LOW);//on eteind la LED 6
      digitalWrite(pinLed7, LOW);//on eteind la LED 7
      digitalWrite(pinLed8, LOW);//on eteind la LED 8
      t4 = t4 + 1; //tempo clignotage
      delay (1); //tempo clignotage
    }
    if (t4 == 50) //tempo clignotage
    {
      t3 = 0; //tempo clignotage
      t4 = 0; //tempo clignotage
    }
  }
  
  if (stock6 > 0) //equipe 6 a repondu
  {
    if (t3 < 50)
    {
      digitalWrite(pinLed1, HIGH);//on allume la LED 1
      if (nombreDeJoueurs > 2)
      {
        digitalWrite(pinLed3, HIGH);//on allume la LED 3
      }
      if (nombreDeJoueurs > 3)
      {
        digitalWrite(pinLed4, HIGH);//on allume la LED 4
      }
      if (nombreDeJoueurs > 4)
      {
        digitalWrite(pinLed5, HIGH);//on allume la LED 5
      }
      digitalWrite(pinLed2, HIGH);//on allume la LED 2
      if (nombreDeJoueurs > 6)
      {
        digitalWrite(pinLed7, HIGH);//on allume la LED 7
      }
      if (nombreDeJoueurs > 7)
      {
        digitalWrite(pinLed8, HIGH);//on allume la LED 8
      }
      t3 = t3 + 1; //tempo clignotage
      delay (1); //tempo clignotage
    }
    else
    {
      digitalWrite(pinLed1, LOW);//on eteind la LED 1
      digitalWrite(pinLed3, LOW);//on eteind la LED 3
      digitalWrite(pinLed4, LOW);//on eteind la LED 4
      digitalWrite(pinLed5, LOW);//on eteind la LED 5
     if(nombreDeJoueurs > 4)
       {
      digitalWrite(pinLed2, LOW);//on eteind la LED 2
       }
      digitalWrite(pinLed7, LOW);//on eteind la LED 7
      digitalWrite(pinLed8, LOW);//on eteind la LED 8
      t4 = t4 + 1; //tempo clignotage
      delay (1); //tempo clignotage
    }
    if (t4 == 50) //tempo clignotage
    {
      t3 = 0; //tempo clignotage
      t4 = 0; //tempo clignotage
    }
  }
  
  if (stock7 > 0) //equipe 7 a repondu
  {
    if (t3 < 50)
    {
      digitalWrite(pinLed1, HIGH);//on allume la LED 1
      if (nombreDeJoueurs > 2)
      {
        digitalWrite(pinLed3, HIGH);//on allume la LED 3
      }
      if (nombreDeJoueurs > 3)
      {
        digitalWrite(pinLed4, HIGH);//on allume la LED 4
      }
      if (nombreDeJoueurs > 4)
      {
        digitalWrite(pinLed5, HIGH);//on allume la LED 5
      }
      if (nombreDeJoueurs > 5)
      {
        digitalWrite(pinLed6, HIGH);//on allume la LED 6
      }
      digitalWrite(pinLed2, HIGH);//on allume la LED 2
      if (nombreDeJoueurs > 7)
      {
        digitalWrite(pinLed8, HIGH);//on allume la LED 8
      }
      t3 = t3 + 1; //tempo clignotage
      delay (1); //tempo clignotage
    }
    else
    {
      digitalWrite(pinLed1, LOW);//on eteind la LED 1
      if(nombreDeJoueurs > 4)
       {
      digitalWrite(pinLed3, LOW);//on eteind la LED 3
       }
      digitalWrite(pinLed4, LOW);//on eteind la LED 4
      digitalWrite(pinLed5, LOW);//on eteind la LED 5
      digitalWrite(pinLed6, LOW);//on eteind la LED 6
      digitalWrite(pinLed2, LOW);//on eteind la LED 2
      digitalWrite(pinLed8, LOW);//on eteind la LED 8
      t4 = t4 + 1; //tempo clignotage
      delay (1); //tempo clignotage
    }
    if (t4 == 50) //tempo clignotage
    {
      t3 = 0; //tempo clignotage
      t4 = 0; //tempo clignotage
    }
  }
  
  if (stock8 > 0) //equipe 8 a repondu
  {
    if (t3 < 50)
    {
      digitalWrite(pinLed1, HIGH);//on allume la LED 1
      if (nombreDeJoueurs > 2)
      {
        digitalWrite(pinLed3, HIGH);//on allume la LED 3
      }
      if (nombreDeJoueurs > 3)
      {
        digitalWrite(pinLed4, HIGH);//on allume la LED 4
      }
      if (nombreDeJoueurs > 4)
      {
        digitalWrite(pinLed5, HIGH);//on allume la LED 5
      }
      if (nombreDeJoueurs > 5)
      {
        digitalWrite(pinLed6, HIGH);//on allume la LED 6
      }
      if (nombreDeJoueurs > 6)
      {
        digitalWrite(pinLed7, HIGH);//on allume la LED 7
      }
      digitalWrite(pinLed2, HIGH);//on allume la LED 2
      t3 = t3 + 1; //tempo clignotage
      delay (1); //tempo clignotage
    }
    else
    {
      digitalWrite(pinLed1, LOW);//on eteind la LED 1
      digitalWrite(pinLed3, LOW);//on eteind la LED 3
      if(nombreDeJoueurs > 4)
       {
      digitalWrite(pinLed4, LOW);//on eteind la LED 4
       }
      digitalWrite(pinLed5, LOW);//on eteind la LED 5
      digitalWrite(pinLed6, LOW);//on eteind la LED 6
      digitalWrite(pinLed7, LOW);//on eteind la LED 7
      digitalWrite(pinLed2, LOW);//on eteind la LED 2
      t4 = t4 + 1; //tempo clignotage
      delay (1); //tempo clignotage
    }
    if (t4 == 50) //tempo clignotage
    {
      t3 = 0; //tempo clignotage
      t4 = 0; //tempo clignotage
    }
  }
  
  //***************************************clignotage bloquage************************************************************************************************************
  
  if ((stock1 == 0) & (stock2 == 0) & (stock3 == 0) & (stock4 == 0) & (stock5 == 0) & (stock6 == 0) & (stock7 == 0) & (stock8 == 0))
  {
    if (t5 < 50)//tempo clignotage bloquage

    {
      if (bloquage1 > 0)
      {
        if (nombreDeJoueurs > 4)
        {
        digitalWrite(pinLed1, HIGH);//on allume la LED 1
        }
        if (nombreDeJoueurs < 5)
        {
        digitalWrite(pinLed1, HIGH);//on allume la LED 1
        digitalWrite(pinLed5, HIGH);//on allume la LED 5
        }
      }
      if (bloquage2 > 0)

      {
        if (nombreDeJoueurs > 4)
        {
        digitalWrite(pinLed2, HIGH);//on allume la LED 2
        }
        if (nombreDeJoueurs < 5)
        {
        digitalWrite(pinLed2, HIGH);//on allume la LED 1
        digitalWrite(pinLed6, HIGH);//on allume la LED 5
        }
      }
      if (bloquage3 > 0)
      {
        if (nombreDeJoueurs > 4)
        {
        digitalWrite(pinLed3, HIGH);//on allume la LED 3
        }
        if ((2 < nombreDeJoueurs) && ( nombreDeJoueurs< 5))
        {
        digitalWrite(pinLed3, HIGH);//on allume la LED 3
        digitalWrite(pinLed7, HIGH);//on allume la LED 7
        }
      }
      if (bloquage4 > 0)
      {
        if (nombreDeJoueurs > 4)
        {
        digitalWrite(pinLed4, HIGH);//on allume la LED 4
        }
        if (nombreDeJoueurs == 4)
        {
        digitalWrite(pinLed4, HIGH);//on allume la LED 4
        digitalWrite(pinLed8, HIGH);//on allume la LED 8
        }
      }
      if (bloquage5 > 0)
      {
        digitalWrite(pinLed5, HIGH);//on allume la LED 5
      }
      if (bloquage6 > 0)
      {
        digitalWrite(pinLed6, HIGH);//on allume la LED 6
      }
      if (bloquage7 > 0)
      {
        digitalWrite(pinLed7, HIGH);//on allume la LED 7
      }
      if (bloquage8 > 0)
      {
        digitalWrite(pinLed8, HIGH);//on allume la LED 8
      }
      t5 = t5 + 1; //tempo clignotage bloquage
      delay (1); //tempo clignotage bloquage
    }
    else
    {
      if (bloquage1 > 0)
      {
        if (nombreDeJoueurs > 4)
        {
        digitalWrite(pinLed1, LOW);//on eteind la LED 1
        }
        if (nombreDeJoueurs < 5)
        {
        digitalWrite(pinLed1, LOW);//on eteind la LED 1
        digitalWrite(pinLed5, LOW);//on eteind la LED 5
        }
      }
      if (bloquage2 > 0)
      {
        if (nombreDeJoueurs > 4)
        {
        digitalWrite(pinLed2, LOW);//on eteind la LED 2
        }
        if (nombreDeJoueurs < 5)
        {
        digitalWrite(pinLed2, LOW);//on eteind la LED 2
        digitalWrite(pinLed6, LOW);//on eteind la LED 6
        }
      }
      if (bloquage3 > 0)
      {
        if (nombreDeJoueurs > 4)
        {
        digitalWrite(pinLed3, LOW);//on eteind la LED 3
        }
        if ((2 < nombreDeJoueurs) && ( nombreDeJoueurs< 5))
        {
        digitalWrite(pinLed3, LOW);//on eteind la LED 3
        digitalWrite(pinLed7, LOW);//on eteind la LED 7
        }
      }
      if (bloquage4 > 0)
      {
        if (nombreDeJoueurs > 4)
        {
        digitalWrite(pinLed4, LOW);//on eteind la LED 4
        }
        if (nombreDeJoueurs == 4)
        {
        digitalWrite(pinLed4, LOW);//on eteind la LED 4
        digitalWrite(pinLed8, LOW);//on eteind la LED 8
        }
      }
      if (bloquage5 > 0)
      {
        digitalWrite(pinLed5, LOW);//on eteind la LED 5
      }
      if (bloquage6 > 0)
      {
        digitalWrite(pinLed6, LOW);//on eteind la LED 6
      }
      if (bloquage7 > 0)
      {
        digitalWrite(pinLed7, LOW);//on eteind la LED 7
      }
      if (bloquage8 > 0)
      {
        digitalWrite(pinLed8, LOW);//on eteind la LED 8
      }
      t6 = t6 + 1; //tempo clignotage bloquage
      delay (1); //tempo clignotage bloquage
    }
    if (t6 == 50) //tempo clignotage bloquage
    {
      t5 = 0; //tempo clignotage bloquage
      t6 = 0; //tempo clignotage bloquage
    }
  }
//**********test*******
// Serial.println(digitalRead(pinBouton8));
}

//*****************************Fonctions**********************************************************
void Punition(int nombre)
{
  if (nombre == 1)
  {
    pointsEquipe1-- ;
    lcd.clear();//reset LCD
    if (pointsEquipe1 < 0)
    {
      pointsEquipe1 = 0;
    }
  }
  if (nombre == 2)
  {
    pointsEquipe2--;
    lcd.clear();//reset LCD
    if (pointsEquipe2 < 0)
    {
      pointsEquipe2 = 0;
    }
  }
  if (nombre == 3)
  {
    pointsEquipe3 = pointsEquipe3 - 1;
    lcd.clear();//reset LCD
    if (pointsEquipe3 < 0)
    {
      pointsEquipe3 = 0;
    }
  }
  if (nombre == 4)
  {
    pointsEquipe4--;
    lcd.clear();//reset LCD
    if (pointsEquipe4 < 0)
    {
      pointsEquipe4 = 0;
    }
  }
  if (nombre == 5)
  {
    pointsEquipe5--;
    lcd.clear();//reset LCD
    if (pointsEquipe5 < 0)
    {
      pointsEquipe5 = 0;
    }
  }
  if (nombre == 6)
  {
    pointsEquipe6--;
    lcd.clear();//reset LCD
    if (pointsEquipe6 < 0)
    {
      pointsEquipe6 = 0;
    }
  }
  if (nombre == 7)
  {
    pointsEquipe7 = pointsEquipe7 - 1;
    lcd.clear();//reset LCD
    if (pointsEquipe7 < 0)
    {
      pointsEquipe7 = 0;
    }
  }
  if (nombre == 8)
  {
    pointsEquipe8--;
    lcd.clear();//reset LCD
    if (pointsEquipe7 < 0)
    {
      pointsEquipe7 = 0;
    }
  }
}
