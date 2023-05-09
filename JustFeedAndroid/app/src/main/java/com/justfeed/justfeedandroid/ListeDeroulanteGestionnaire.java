package com.justfeed.justfeedandroid;

import android.util.Log;
import android.view.MotionEvent;
import android.view.View;
import android.widget.AdapterView;

public class ListeDeroulanteGestionnaire implements AdapterView.OnItemSelectedListener, View.OnTouchListener
{
    /**
     * Constantes
     */
    private static final String TAG = "_ListeDeroulante";
    private final static String VALIDER  = "Valider"; //!< L'intervention est validée
    private final static String EN_COURS = "En cours"; //!< L'intervention est en cours
    private final static String AFAIRE   = "A faire"; //!< L'intervention est à faire

    /**
     * Attribut
     */
    private boolean interactionDetectee = false; //!< Attribut utilisé pour détecter l'interaction d'un utilisateur.
    private Intervention intervention; //!< Intervention où gérer l'évènement.

    /**
     * @brief Constructeur d'initialisation de la Classe ListeDeroulanteGestionnaire
     * @param intervention, l'intervention affichée
     */
    public ListeDeroulanteGestionnaire(Intervention intervention)
    {
        super();

        this.intervention = intervention;
    }

    @Override
    public boolean onTouch(View vue, MotionEvent event)
    {
        interactionDetectee = true;
        return false;
    }

    @Override
    public void onItemSelected(AdapterView<?> parent, View vue, int position, long id)
    {
        Log.d(TAG, "onItemSelected()");
        String nouvelEtat = parent.getItemAtPosition(position).toString();

        if(interactionDetectee)
        {
            switch (nouvelEtat)
            {
                case VALIDER:
                    Log.d(TAG, "valider");
                    ActiviteInterventions.modifierEtatIntervention("UPDATE `Intervention` SET `etat` = 'VALIDEES' WHERE `Intervention`.`idDistributeur` = "
                            +intervention.getIdentifiantDistribteur()+";", intervention, Intervention.Etats.VALIDEES);
                    break;
                case EN_COURS:
                    Log.d(TAG, "en cours");
                    ActiviteInterventions.modifierEtatIntervention("UPDATE `Intervention` SET `etat` = 'EN_COURS' WHERE `Intervention`.`idDistributeur` = "
                            +intervention.getIdentifiantDistribteur()+";", intervention, Intervention.Etats.EN_COURS);
                    break;
                case AFAIRE:
                    Log.d(TAG, "A faire");
                    ActiviteInterventions.modifierEtatIntervention("UPDATE `Intervention` SET `etat` = 'A_FAIRE' WHERE `Intervention`.`idDistributeur` = "
                            +intervention.getIdentifiantDistribteur()+";", intervention, Intervention.Etats.A_FAIRE);
                    break;
            }
        }
    }

    @Override
    public void onNothingSelected(AdapterView<?> adapterView){}
}
