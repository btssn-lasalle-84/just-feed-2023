package com.justfeed.justfeedandroid;

import android.util.Log;
import android.view.MotionEvent;
import android.view.View;
import android.widget.AdapterView;

public class ListeDeroulanteGestionnaire
  implements AdapterView.OnItemSelectedListener, View.OnTouchListener
{
    /**
     * Constantes
     */
    private static final String TAG      = "_ListeDeroulante";
    private final static String TERMINER = "Terminer"; //!< L'intervention est validée
    private final static String DEMARRER = "Démarrer"; //!< L'intervention est en cours
    private final static String AFAIRE   = "A faire";  //!< L'intervention est à faire
    private final static String RECOMMENCER =
      "Recommencer"; //!< L'opérateur recommence l'intervention

    /**
     * Attribut
     */
    private static int aRemplir; //!< Ancien état aRemplir de l'intervention
    private static int aDepanner; //!< Ancien état aDepanner de l'intervention
    private boolean interactionDetectee =
      false; //!< Attribut utilisé pour détecter l'interaction d'un utilisateur.
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
        String nouvelleAction = parent.getItemAtPosition(position).toString();

        if(interactionDetectee)
        {
            switch(nouvelleAction)
            {
                case TERMINER:
                    Log.d(TAG, "Terminer");
                    if(intervention.estARemplir())
                    {
                        aRemplir = 1;
                    }
                    else
                    {
                        aRemplir = 0;
                    }
                    if(intervention.estADepanner())
                    {
                        aDepanner = 1;
                    }
                    else
                    {
                        aDepanner = 0;
                    }
                    Log.d(TAG, "A depanner :"+aDepanner+" A remplir : "+aRemplir);
                    ActiviteInterventions.modifierEtatIntervention(
                      "UPDATE `Intervention` SET `etat` = 'VALIDEE', `aRemplir` = 0, `aDepanner` = 0 WHERE `Intervention`.`idDistributeur` = " +
                        intervention.getIdentifiantDistribteur() + ";",
                      intervention,
                      Intervention.Etats.VALIDEE);
                    break;
                case DEMARRER:
                    Log.d(TAG, "Démarrer");
                    ActiviteInterventions.modifierEtatIntervention(
                      "UPDATE `Intervention` SET `etat` = 'EN_COURS' WHERE `Intervention`.`idDistributeur` = " +
                        intervention.getIdentifiantDistribteur() + ";",
                      intervention,
                      Intervention.Etats.EN_COURS);
                    break;
                case AFAIRE:
                    Log.d(TAG, "A faire");
                    ActiviteInterventions.modifierEtatIntervention(
                      "UPDATE `Intervention` SET `etat` = 'A_FAIRE' WHERE `Intervention`.`idDistributeur` = " +
                        intervention.getIdentifiantDistribteur() + ";",
                      intervention,
                      Intervention.Etats.A_FAIRE);
                    break;
                case RECOMMENCER:
                    Log.d(TAG, "Recommencer");
                    ActiviteInterventions.modifierEtatIntervention(
                      "UPDATE `Intervention` SET `etat` = 'A_FAIRE', `aRemplir` = "+aRemplir
                              +
                              ", `aDepanner` = "+aDepanner+" WHERE `Intervention`.`idDistributeur` = " +
                        intervention.getIdentifiantDistribteur() + ";",
                      intervention,
                      Intervention.Etats.A_FAIRE);
                    break;
            }
        }
    }

    @Override
    public void onNothingSelected(AdapterView<?> adapterView)
    {
    }
}
