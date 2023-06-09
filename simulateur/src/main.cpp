/**
 *
 * @file src/main.cpp
 * @brief Simulateur the-things-uno just-feed
 * @author Thierry Vaira
 * @version 0.1
 */

#include <Arduino.h>
#include <TheThingsNetwork.h>
#include <DHT.h>

/**
 * @def DISTRIBUTEUR_1
 * @brief Définit le distributeur n°1
 */
#define DISTRIBUTEUR_1
// #define DISTRIBUTEUR_2

// 2022
// AppId : just-feed

#ifdef DISTRIBUTEUR_1
// DevicesId : distributeur-1-sim
const char* appEui = "70B3D57ED003FFB5";
const char* appKey = "6CB9F3E06DD4F5151F8486E06FE41275"; //
#endif

#ifdef DISTRIBUTEUR_2
// DevicesId : distributeur-2-sim
const char* appEui = "70B3D57ED003FFB5";
const char* appKey = "ED66BC2C532875FFF2174BB11BB20DAC";
#endif

/*
  enum ttn_response_t
  {
    TTN_ERROR_SEND_COMMAND_FAILED = (-1),
    TTN_ERROR_UNEXPECTED_RESPONSE = (-10),
    TTN_SUCCESSFUL_TRANSMISSION = 1,
    TTN_SUCCESSFUL_RECEIVE = 2
  };
*/

/**
 * @def loraSerial
 * @brief Définit l'interface LoRa
 */
#define loraSerial Serial1
/**
 * @def debugSerial
 * @brief Définit le débuggage sur la liaison série
 */
#define debugSerial Serial
/**
 * @def freqPlan
 * @brief Définit la fréquence LoRa
 */
#define freqPlan TTN_FP_EU868

// un cycle conprend l'envoi des plusieurs ports
/**
 * @def PERIODE
 * @brief Définit la période d'envoi en ms des données
 */
#define PERIODE 60000 // en ms attente avant prochain cycle
/**
 * @def TEMPO
 * @brief Définit la temporistation en ms entre deux cycles d'envoi
 */
#define TEMPO          20000 // en ms attente entre deux envois dans un cycle
#define NB_ERREURS_MAX 3

#ifdef DISTRIBUTEUR_1
/**
 * @def NB_BACS
 * @brief Définit le nombre de bacs du distributeur
 */
#define NB_BACS 4

#define LEDPIN   13
#define LEDROUGE 12
#define DHTPIN   4
#define DHTTYPE  DHT11
// #define VBATPIN     A0
// #define LUMINOSITE  A1
// #define LM35        A2
#endif

#ifdef DISTRIBUTEUR_2
/**
 * @def NB_BACS
 * @brief Définit le nombre de bacs du distributeur
 */
#define NB_BACS 2

#define LEDPIN  4
#define DHTPIN  7
#define DHTTYPE DHT22
// #define VBATPIN     A0
#endif

/*
  Port 1 : Remplissage des bacs % Entier Entier 1 octet pour chaque bac
  Port 2 : Humidité intérieure % Entier Entier 1 octet
  Port 3 : Maintenance prédictive
 */

#define PORT_REMPLISSAGE 1
#define PORT_HYGROMETRIE 2
#define PORT_MAINTENANCE 3

#define NB_BYTE_PORT_MAINTENANCE 4

#define SEUIL_HUMIDITE 15

TheThingsNetwork ttn(loraSerial, debugSerial, freqPlan); //!<
DHT              dht(DHTPIN, DHTTYPE); //!< le capteur d'humidité
bool             etatLed = false;      //!< l'état de la led
uint16_t         humidity;             //!< l'humidité
uint8_t remplissageBacs[NB_BACS];   //!< le niveau de remplissage en % de chaque
                                    //!< bac de produit
uint8_t hygrometrieBacs[NB_BACS];   //!< le niveau d'humidité relative en % de
                                    //!< chaque bac de produit
uint8_t demandeMaintenance = 0;     //!< demande de maintrnance si = 1

byte payloadBacs[NB_BACS];          //!< les données de remplissage des bacs
byte payloadEnvironnement[NB_BACS]; //!< les données d'environnement (humidité)
                                    //!< du distributeur
byte
  payloadMaintenance[NB_BYTE_PORT_MAINTENANCE]; //!< les données de maintenance

uint32_t compteurOperations = 0; //!< compteur les opérations de consommation
uint32_t totalDepassement   = 0; //!< total des dépassement seuil
uint32_t tempo              = TEMPO; //!<  cf. duty cycle et airtime calculators

void message(const byte* payload, size_t length, port_t port);
bool controlerReponse(ttn_response_t ttn_response);

/**
 * @brief Initialise les ressources
 *
 * @fn setup()
 */
void setup()
{
    loraSerial.begin(57600);
    debugSerial.begin(9600);

    // Attente max de 10s pour le port série
    while(!debugSerial && millis() < 10000)
        ;

#ifdef DISTRIBUTEUR_1
    debugSerial.println("-- DISTRIBUTEUR_1");
#endif

#ifdef DISTRIBUTEUR_1
    // pinMode(VBATPIN, INPUT);
    // pinMode(LUMINOSITE, INPUT);
    // pinMode(LM35, INPUT);
    digitalWrite(LEDPIN, LOW);
#endif

#ifdef DISTRIBUTEUR_2
    debugSerial.println("-- DISTRIBUTEUR_2");
#endif

#ifdef DISTRIBUTEUR_2
    // digitalWrite(LEDROUGE, LOW);
    // pinMode(VBATPIN, INPUT);
    digitalWrite(LEDPIN, LOW);
    digitalWrite(LED_BUILTIN, LOW);
#endif
    dht.begin();

    // Pour les messages reçus
    ttn.onMessage(message);

    debugSerial.println("-- STATUS");
    ttn.showStatus();

    debugSerial.println("-- JOIN");
    ttn.join(appEui, appKey);

    randomSeed(millis());

    // initialise le remplissage des bacs
    for(int i = 0; i < NB_BACS; ++i)
    {
        remplissageBacs[i] = 100;
    }

    // initialise le pourcentage d'humidité relative des bacs
    for(int i = 0; i < NB_BACS; ++i)
    {
        hygrometrieBacs[i] = 0;
    }
}

/**
 * @brief Boucle principale
 *
 * @fn loop()
 */
void loop()
{
    ttn_response_t ttn_response;
    bool           etat = true;

    debugSerial.println("-- SEND");

#ifdef DISTRIBUTEUR_1
    digitalWrite(LEDROUGE, HIGH);
#endif

#ifdef DISTRIBUTEUR_2
    digitalWrite(LED_BUILTIN, HIGH);
#endif

    // PORT_REMPLISSAGE :
    if(etat)
    {
        delay(tempo);

        debugSerial.print("-> Port : ");
        debugSerial.println(PORT_REMPLISSAGE);
        uint8_t consommation = 0;
        for(int i = 0; i < NB_BACS; ++i)
        {
            // remplir ?
            if(remplissageBacs[i] <= 5)
            {
                consommation = random(0, 3); // une chance sur 3 pour remplir
                if(consommation == 1)
                    remplissageBacs[i] = 100;
            }
            else                              // consommer ?
            {
                consommation = random(0, 10); // simule une petite consommation
                remplissageBacs[i] -= consommation;
                compteurOperations++;
                if(remplissageBacs[i] < 0)
                    remplissageBacs[i] = 0;
            }
            payloadBacs[i] = lowByte(remplissageBacs[i]);
            debugSerial.print("   Remplissage bac ");
            debugSerial.print(i + 1);
            debugSerial.print(" : ");
            debugSerial.println(remplissageBacs[i]);
        }

        ttn_response =
          ttn.sendBytes(payloadBacs, sizeof(payloadBacs), PORT_REMPLISSAGE);
        etat = controlerReponse(ttn_response);
    }

    // PORT_HYGROMETRIE : humidité
    if(etat)
    {
        delay(tempo);

        debugSerial.print("-> Port : ");
        debugSerial.println(PORT_HYGROMETRIE);

        for(int i = 0; i < NB_BACS; ++i)
        {
            humidity = dht.readHumidity(false);
            if(uint16_t(humidity / 10.) > SEUIL_HUMIDITE)
                totalDepassement++;
            if(i % 2)
                hygrometrieBacs[i] = lowByte(uint16_t(humidity / 10.) + i);
            else
                hygrometrieBacs[i] = lowByte(uint16_t(humidity / 10.) - i);
            payloadEnvironnement[i] = lowByte(hygrometrieBacs[i]);
            debugSerial.print("   Humidite bac ");
            debugSerial.print(i + 1);
            debugSerial.print(" : ");
            debugSerial.println(hygrometrieBacs[i]);
        }

        ttn_response = ttn.sendBytes(payloadEnvironnement,
                                     sizeof(payloadEnvironnement),
                                     PORT_HYGROMETRIE);
        etat         = controlerReponse(ttn_response);
    }

    // PORT_MAINTENANCE : maintenance
    if(etat)
    {
        delay(tempo);

        debugSerial.print("-> Port : ");
        debugSerial.println(PORT_MAINTENANCE);

        payloadMaintenance[0] = highByte(uint16_t(compteurOperations));
        payloadMaintenance[1] = lowByte(uint16_t(compteurOperations));
        payloadMaintenance[2] = highByte(uint16_t(totalDepassement));
        payloadMaintenance[3] = lowByte(uint16_t(totalDepassement));
        debugSerial.print("   Maintenance : ");
        debugSerial.print("   compteurOperations ");
        debugSerial.println(compteurOperations);
        debugSerial.print("   totalDepassement ");
        debugSerial.println(totalDepassement);

        ttn_response = ttn.sendBytes(payloadMaintenance,
                                     sizeof(payloadMaintenance),
                                     PORT_MAINTENANCE);
        etat         = controlerReponse(ttn_response);
    }

#ifdef DISTRIBUTEUR_1
    digitalWrite(LEDROUGE, LOW);
#endif

#ifdef DISTRIBUTEUR_2
    digitalWrite(LED_BUILTIN, LOW);
#endif

    delay(PERIODE);
}

void message(const byte* payload, size_t length, port_t port)
{
    debugSerial.println("-- RECEIVE");
    debugSerial.print("   Port : ");
    debugSerial.println(port);
    debugSerial.print("   Longueur : ");
    debugSerial.println(length);

    /*
    // 1 seul octet accepté
    if (length != 1)
    {
      return;
    }

    if (payload[0] == 0)
    {
      debugSerial.println("LED : off");
      digitalWrite(LEDPIN, LOW);
      etatLed = false;
    }
    else if (payload[0] == 1)
    {
      debugSerial.println("LED : on");
      digitalWrite(LEDPIN, HIGH);
      etatLed = true;
    }
    */
}

bool controlerReponse(ttn_response_t ttn_response)
{
    bool etat = false;
    switch(ttn_response)
    {
        case TTN_ERROR_SEND_COMMAND_FAILED:
            debugSerial.println("-- RESPONSE : TTN_ERROR_SEND_COMMAND_FAILED");
            tempo = TEMPO;
            etat  = false;
            break;
        case TTN_ERROR_UNEXPECTED_RESPONSE:
            debugSerial.println("-- RESPONSE : TTN_ERROR_UNEXPECTED_RESPONSE");
            etat = false;
            break;
        case TTN_SUCCESSFUL_TRANSMISSION:
            debugSerial.println("-- RESPONSE : TTN_SUCCESSFUL_TRANSMISSION");
            tempo = TEMPO;
            etat  = true;
            break;
        case TTN_SUCCESSFUL_RECEIVE:
            debugSerial.println("-- RESPONSE : TTN_SUCCESSFUL_RECEIVE");
            etat = true;
            break;
        default:
            debugSerial.println("-- RESPONSE : UNKNOWN_ERROR !");
            break;
    }

    return etat;
}
