/**
 * @file VueIntervention.java
 * @brief Déclaration de la classe VueIntervention
 * @author FARGIER Mayeul
 */

package com.justfeed.justfeedandroid;

import static com.justfeed.justfeedandroid.Intervention.Etats.A_FAIRE;

import android.content.Context;
import android.graphics.Color;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Spinner;
import android.widget.TextView;

import androidx.cardview.widget.CardView;
import androidx.recyclerview.widget.RecyclerView.ViewHolder;

/**
 * @brief Définition de la classe VueIntervention.
 * @details La classe VueIntervention \c VueIntervention permet de gérer les vues
 * pour afficher des interventions.
 * @author Fargier Mayeul
 * @version 0.1
 */
public class VueIntervention extends ViewHolder {
    /**
     * Constantes
     */
    private final static String ROUGE    = "#ed3734"; //!< L'intervention n'a pas été effectuée
    private final static String VERT     = "#4eea48"; //!< L'intervention a été effectuée
    private final static String BLEU     = "#039dfc"; //!< L'intervention est en cours
    private final static String TAG      = "_VueIntervention"; //!< TAG pour le débug
    /**
     * Membres statiques
     */
    private static Intervention.Etats etatAfiltrer = A_FAIRE; //!< pour trier les interventions.
    private static Context contexte; //!< attribut qui contient le contexte de l'application.
    private static boolean interactionDetectee = false; //!< attribut utilisé pour détecter évènement.
    /**
     * Ressources GUI
     */
    private final TextView identifiantDistributeur; //!< attribut GUI qui affiche l'identifiant du
    //!< distributeur où intervenir.
    private final TextView
            dateIntervention; //!< attribut GUI qui affiche l'heure de l'intervention.
    private final TextView
            aRemplir; //!< attribut GUI qui affiche si le distributeur doit être rempli.
    private final TextView
            aDepanner; //!< attribut GUI qui affiche si le distributeur doit être dépanné.
    private final CardView
            carteIntervention; //!< attribut GUI qui contient les informations sur une intervention.
    private final Spinner
            menuEtats; //!< attribut GUI d'une liste déroulante pour trier les interventions.
    private final Spinner
            listeEtats; //!< attribut GUI d'une liste déroulante pour changer l'état d'une intervention.

    public VueIntervention(final View itemView) {
        super(itemView);

        identifiantDistributeur = ((TextView) itemView.findViewById(R.id.identifiantDistributeur));
        dateIntervention = ((TextView) itemView.findViewById(R.id.dateIntervention));
        aRemplir = ((TextView) itemView.findViewById(R.id.aRemplir));
        aDepanner = ((TextView) itemView.findViewById(R.id.aDepanner));
        carteIntervention = ((CardView) itemView.findViewById(R.id.carteIntervention));
        menuEtats = ((Spinner) itemView.findViewById(R.id.menuEtats));
        listeEtats = ((Spinner) itemView.findViewById(R.id.listeEtats));
    }

    public void afficherInterventions(Intervention intervention) {
        if (menuEtats != null)
            etatAfiltrer = Intervention.Etats.valueOf(menuEtats.getSelectedItem().toString());
        if (etatAfiltrer == intervention.getEtat() && etatAfiltrer != Intervention.Etats.TOUTES) {
            carteIntervention.setVisibility(View.VISIBLE);
            switch (intervention.getEtat()) {
                case VALIDEES:
                    carteIntervention.setCardBackgroundColor(Color.parseColor(VERT));
                    break;
                case A_FAIRE:
                    carteIntervention.setCardBackgroundColor(Color.parseColor(ROUGE));
                    break;
                case EN_COURS:
                    carteIntervention.setCardBackgroundColor(Color.parseColor(BLEU));
                    break;
            }
            identifiantDistributeur.setText("Distributeur : " + intervention.getNomDistribteur());
            if (intervention.estADepanner()) {
                aDepanner.setText("Bacs à dépanner (Hygrométrie > " + Intervention.SEUIL_HUMIDITE +
                        "%) : \n" + intervention.recupererBacsADepanner());
            }
            if (intervention.estARemplir()) {
                aRemplir.setText("Bac(s) à remplir : \n" + intervention.recupererBacsARemplir());
            }
            dateIntervention.setText("Date de l'intervention : " +
                    Intervention.formaterDate(intervention.getDateIntervention()));
        } else if (etatAfiltrer == Intervention.Etats.TOUTES) {
            Log.d(TAG, "TOUTES");
            carteIntervention.setVisibility(View.VISIBLE);
            switch (intervention.getEtat()) {
                case VALIDEES:
                    carteIntervention.setCardBackgroundColor(Color.parseColor(VERT));
                    break;
                case A_FAIRE:
                    carteIntervention.setCardBackgroundColor(Color.parseColor(ROUGE));
                    break;
                case EN_COURS:
                    carteIntervention.setCardBackgroundColor(Color.parseColor(BLEU));
                    break;
            }
            identifiantDistributeur.setText("Distributeur : " + intervention.getNomDistribteur());
            if (intervention.estADepanner()) {
                aDepanner.setText("Bacs à dépanner (Hygrométrie > " + Intervention.SEUIL_HUMIDITE +
                        "%) : \n" + intervention.recupererBacsADepanner());
            }
            if (intervention.estARemplir()) {
                aRemplir.setText("Bac(s) à remplir : \n" + intervention.recupererBacsARemplir());
            }
            dateIntervention.setText("Date de l'intervention : " +
                    Intervention.formaterDate(intervention.getDateIntervention()));
        } else {
            carteIntervention.setVisibility(View.GONE);
        }
        afficherListeDeroulante(intervention);
    }

    public void afficherListeDeroulante(Intervention intervention) {

        if(intervention.getEtat() == A_FAIRE)
        {
            ArrayAdapter<CharSequence> listeAdapteur = ArrayAdapter.createFromResource(contexte,
                    R.array.listeEtatsAFaire, android.R.layout.simple_spinner_item);
            listeAdapteur.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
            this.listeEtats.setAdapter(listeAdapteur);
        }
        else if(intervention.getEtat() == Intervention.Etats.EN_COURS)
        {
            ArrayAdapter<CharSequence> listeAdapteur = ArrayAdapter.createFromResource(contexte,
                    R.array.listeEtatsEnCours, android.R.layout.simple_spinner_item);
            listeAdapteur.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
            this.listeEtats.setAdapter(listeAdapteur);
        }
        else if(intervention.getEtat() == Intervention.Etats.VALIDEES)
        {
            ArrayAdapter<CharSequence> listeAdapteur = ArrayAdapter.createFromResource(contexte,
                    R.array.listeEtatsValider, android.R.layout.simple_spinner_item);
            listeAdapteur.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
            this.listeEtats.setAdapter(listeAdapteur);
        }

        ListeDeroulanteGestionnaire gestionnaire = new ListeDeroulanteGestionnaire(intervention);
        this.listeEtats.setOnTouchListener(gestionnaire);
        this.listeEtats.setOnItemSelectedListener(gestionnaire);
    }

    /**
     * @brief Méthode pour récuérer l'état qui permet de trier les interventions.
     */
    public static Intervention.Etats getEtatAFiltrer(Intervention.Etats nouvelEtat) {
        return etatAfiltrer;
    }

    // Mutateurs

    /**
     * @brief Méthode pour modifier l'état qui permet de trier les interventions.
     */
    public static void changerEtatAFiltrer(Intervention.Etats nouvelEtat) {
        etatAfiltrer = nouvelEtat;
    }

    /**
     * @brief Méthode pour modifier le contexte.
     */
    public static void setContext(Context nouveauContexte){ contexte = nouveauContexte; }
}