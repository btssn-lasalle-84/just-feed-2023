package com.justfeed.justfeedandroid;

import android.content.Context;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;

import org.eclipse.paho.android.service.MqttAndroidClient;
import org.eclipse.paho.client.mqttv3.DisconnectedBufferOptions;
import org.eclipse.paho.client.mqttv3.IMqttActionListener;
import org.eclipse.paho.client.mqttv3.IMqttDeliveryToken;
import org.eclipse.paho.client.mqttv3.IMqttToken;
import org.eclipse.paho.client.mqttv3.MqttCallbackExtended;
import org.eclipse.paho.client.mqttv3.MqttConnectOptions;
import org.eclipse.paho.client.mqttv3.MqttException;
import org.eclipse.paho.client.mqttv3.MqttMessage;

/**
 * @brief Définition de la classe ClientMQTT.
 * @details La classe ClientMQTT \c ClientMQTT permet d'etablir une communication
 * entre un serveur The Things Stack et une application Android
 * @author Fargier Mayeul
 * @version 1.1
 */
public class ClientMQTT
{
    /**
     * Constantes
     */
    private static final String TAG = "_ClientMQTT";

    /**
     * Constantes pour le Handler
     */
    public static final int TTN_CONNECTE   = 11;
    public static final int TTN_DECONNECTE = 12;
    public static final int TTN_MESSAGE    = 13;

    /**
     * Constantes QoS
     */
    private static final int QOS_1 = 0;
    private static final int QOS_2 = 1;
    private static final int QOS_3 = 2;

    /**
     * Attributs
     */
    private MqttAndroidClient mqttAndroidClient;
    private Handler           handler = null; //!< pour la communication entre classes
    private Context           context = null; //!< Context de l'application

    private String uriServeur; //!<  lien vers TTS
    private String clientId;   //!< Application ID

    private String nomUtilisateur; //!<  nom d'utilisateur
    private String motDePasse;     //!<  mot de passe TTS

    /**
     * @brief Constructeur de la classe ClientMQTT
     * @param context
     * @param handler
     */
    public ClientMQTT(Context context, final Handler handler)
    {
        Log.v(TAG, "[ClientMQTT()] clientId = " + clientId);
        this.handler = handler;
        this.context = context;

        // creerClientMQTTT(context, handler);
        // connecter();
    }

    /**
     * @brief Méthode pour créer le client MQTT
     */
    public void creerClientMQTTT()
    {
        Log.w(TAG, "creerClientMQTTT() uriServeur = " + uriServeur + " clientId = " + clientId);
        mqttAndroidClient = new MqttAndroidClient(context, uriServeur, clientId);
        mqttAndroidClient.setCallback(new MqttCallbackExtended() {
            @Override
            public void connectComplete(boolean b, String s)
            {
                Log.w(TAG,
                      "[ClientMQTT()] uriServeur = " + s +
                        " connecte = " + mqttAndroidClient.isConnected());
                Message msg    = Message.obtain();
                Bundle  bundle = new Bundle();
                bundle.putInt("etat", TTN_CONNECTE);
                msg.setData(bundle);
                handler.sendMessage(msg);
            }

            @Override
            public void connectionLost(Throwable throwable)
            {
                Log.w(TAG, "[connectionLost()]");
                Message msg = Message.obtain();
                Bundle  b   = new Bundle();
                b.putInt("etat", TTN_DECONNECTE);
                msg.setData(b);
                handler.sendMessage(msg);
            }

            @Override
            public void messageArrived(String topic, MqttMessage mqttMessage) throws Exception
            {
                Log.w(TAG,
                      "[messageArrived()] topic = " + topic +
                        " message = " + mqttMessage.toString());
                Message msg = Message.obtain();
                Bundle  b   = new Bundle();
                b.putInt("etat", TTN_MESSAGE);
                b.putString("topic", topic);
                b.putString("message", mqttMessage.toString());
                msg.setData(b);
                handler.sendMessage(msg);
            }

            @Override
            public void deliveryComplete(IMqttDeliveryToken iMqttDeliveryToken)
            {
                Log.w(TAG, "[deliveryComplete()]");
            }
        });
    }

    /**
     * @brief Méthode pour modifier le nom d'utilisateur
     * @param nomUtilisateur
     */
    public void changerNomUtilisateur(String nomUtilisateur)
    {
        this.nomUtilisateur = nomUtilisateur;
    }

    /**
     * @brief Méthode pour modifier le hostname
     * @param hostname
     */
    public void changerHostname(String hostname)
    {
        this.uriServeur = "tcp://" + hostname + ":1883";
    }

    /**
     * @brief Méthode pour modifier l'identifiant du client
     * @param clientId
     */
    public void changerClientId(String clientId)
    {
        this.clientId = clientId;
    }

    /**
     * @brief Méthode pour modifier le mot de passe de l'application
     * @param motDePasse
     */
    public void changerMotDePasse(String motDePasse)
    {
        this.motDePasse = motDePasse;
    }

    /**
     * @brief Méthode pour mettre en place les callbacks
     * @param callback le retour
     */
    public void setCallback(MqttCallbackExtended callback)
    {
        mqttAndroidClient.setCallback(callback);
    }

    /**
     * @brief Connexion au TTS
     */
    public void connecter()
    {
        MqttConnectOptions mqttConnectOptions = new MqttConnectOptions();
        mqttConnectOptions.setAutomaticReconnect(true);
        mqttConnectOptions.setCleanSession(false);
        mqttConnectOptions.setUserName(nomUtilisateur);
        mqttConnectOptions.setPassword(motDePasse.toCharArray());

        try
        {
            Log.d(TAG,
                  "[ClientMQTT()] uriServeur = " + uriServeur + " clientId = " + clientId +
                    " motdepasse = " + motDePasse);
            mqttAndroidClient.connect(mqttConnectOptions, null, new IMqttActionListener() {
                @Override
                public void onSuccess(IMqttToken asyncActionToken)
                {
                    DisconnectedBufferOptions disconnectedBufferOptions =
                      new DisconnectedBufferOptions();
                    disconnectedBufferOptions.setBufferEnabled(true);
                    disconnectedBufferOptions.setBufferSize(100);
                    disconnectedBufferOptions.setPersistBuffer(false);
                    disconnectedBufferOptions.setDeleteOldestMessages(false);
                    mqttAndroidClient.setBufferOpts(disconnectedBufferOptions);
                    Log.d(TAG,
                          "[onSuccess()] uriServeur = " + uriServeur + " clientId = " + clientId);
                }

                @Override
                public void onFailure(IMqttToken asyncActionToken, Throwable exception)
                {
                    Log.d(TAG,
                          "[onFailure()] uriServeur = " + uriServeur + " clientId = " + clientId +
                            " exception = " + exception.toString());
                }
            });
        }
        catch(MqttException e)
        {
            e.printStackTrace();
        }
    }

    /**
     * @brief Deconnexion du TTS
     */
    public void deconnecter()
    {
        if(!estConnecte())
            return;
        Log.d(TAG, "[deconnecter()] uriServeur = " + uriServeur + " clientId = " + clientId);
        try
        {
            IMqttToken disconToken = mqttAndroidClient.disconnect();
            disconToken.setActionCallback(new IMqttActionListener() {
                @Override
                public void onSuccess(IMqttToken asyncActionToken)
                {
                    Log.d(TAG,
                          "[onSuccess()] uriServeur = " + uriServeur + " clientId = " + clientId);
                }

                @Override
                public void onFailure(IMqttToken asyncActionToken, Throwable exception)
                {
                    Log.d(TAG,
                          "[onFailure()] uriServeur = " + uriServeur + " clientId = " + clientId +
                            " exception = " + exception.toString());
                }
            });
        }
        catch(MqttException e)
        {
            e.printStackTrace();
        }
    }

    /**
     * @brief Retourne l'état de connexion au serveur TTS
     * @return boolean
     */
    public boolean estConnecte()
    {
        Log.w(TAG, "[estConnecte()] " + mqttAndroidClient.isConnected());

        return mqttAndroidClient.isConnected();
    }

    /**
     * @brief S'abonne à un topic
     * @param deviceID le deviceID dans TTN
     */
    public boolean souscrireTopic(String deviceID)
    {
        // Vérifications
        if(mqttAndroidClient == null && !mqttAndroidClient.isConnected())
        {
            return false;
        }

        final String topicTTN = clientId + "/devices/" + deviceID + "/up";
        Log.w(TAG, "[souscrireTopic()] topic = " + topicTTN);
        try
        {
            final boolean[] retour = { false };
            mqttAndroidClient.subscribe(topicTTN, 0, null, new IMqttActionListener() {
                @Override
                public void onSuccess(IMqttToken asyncActionToken)
                {
                    Log.w(TAG, "[onSuccess()] topic = " + topicTTN);
                    retour[0] = true;
                }

                @Override
                public void onFailure(IMqttToken asyncActionToken, Throwable exception)
                {
                    Log.w(TAG, "[onFailure()] topic = " + topicTTN);
                    retour[0] = false;
                }
            });
            return retour[0];
        }
        catch(MqttException e)
        {
            Log.w(TAG, "Erreur topic = " + topicTTN);
            e.printStackTrace();
            return false;
        }
    }

    /**
     * @brief S'desabonne à un topic
     * @param deviceID le deviceID dans TTN
     */
    public boolean unsubscribe(String deviceID)
    {
        if(mqttAndroidClient == null && !mqttAndroidClient.isConnected())
        {
            return false;
        }
        final String topicTTN = clientId + "/devices/" + deviceID + "/up";
        Log.w(TAG, "[unsouscrireTopic()] topic = " + topicTTN);
        try
        {
            final boolean[] retour = { false };
            mqttAndroidClient.unsubscribe(topicTTN, null, null);

            return retour[0];
        }
        catch(MqttException e)
        {
            Log.w(TAG, "Erreur topic = " + topicTTN);
            e.printStackTrace();
            return false;
        }
    }
}
