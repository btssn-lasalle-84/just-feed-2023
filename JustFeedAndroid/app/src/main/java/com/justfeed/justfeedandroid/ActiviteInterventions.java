package com.justfeed.justfeedandroid;

import androidx.appcompat.app.AppCompatActivity;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import android.os.Bundle;
import android.util.Log;

import java.util.List;

public class ActiviteInterventions extends AppCompatActivity {
    /**
     * Constantes
     */
    private static final String TAG = "_Interventions"; //!< TAG pour les logs (cf. Logcat)

    /**
     * Attributs
     */
    List<Intervention> listeInterventions;
    BaseDeDonnees baseDeDonnees;
    private RecyclerView vueListeInterventions; //!< Affichage des Interventions
    private RecyclerView.Adapter adapteurIntervention;  //!< Remplit les vues des Interventions
    private RecyclerView.LayoutManager layoutVueListeInterventions; //!< Positionne les vues

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_interventions);

        baseDeDonnees      = new BaseDeDonnees();
        listeInterventions = baseDeDonnees.recupererInterventions();

        initialiserVueInterventions();
        afficherInterventions();
    }

    /**
     * @brief Méthode appelée au démarrage après le onCreate() ou un restart
     * après un onStop()
     */
    @Override
    protected void onStart()
    {
        super.onStart();
        Log.d(TAG, "onStart()");
    }

    /**
     * @brief Méthode appelée après onStart() ou après onPause()
     */
    @Override
    protected void onResume()
    {
        super.onResume();
        Log.d(TAG, "onResume()");
    }

    /**
     * @brief Méthode appelée après qu'une boîte de dialogue s'est affichée (on
     * reprend sur un onResume()) ou avant onStop() (activité plus visible)
     */
    @Override
    protected void onPause()
    {
        super.onPause();
        Log.d(TAG, "onPause()");
    }

    /**
     * @brief Méthode appelée lorsque l'activité n'est plus visible
     */
    @Override
    protected void onStop()
    {
        super.onStop();
        Log.d(TAG, "onStop()");
    }

    /**
     * @brief Méthode appelée à la destruction de l'application (après onStop()
     * et détruite par le système Android)
     */
    @Override
    protected void onDestroy()
    {
        super.onDestroy();
        Log.d(TAG, "onDestroy()");
    }

    private void initialiserVueInterventions()
    {
        this.vueListeInterventions       = (RecyclerView)findViewById(R.id.listeInterventions);
        this.vueListeInterventions.setHasFixedSize(true);
        this.layoutVueListeInterventions = new LinearLayoutManager(this);
        this.vueListeInterventions.setLayoutManager(this.layoutVueListeInterventions);
        this.adapteurIntervention        = new InterventionAdapter(this.listeInterventions);
        this.vueListeInterventions.setAdapter(this.adapteurIntervention);
    }

    private void afficherInterventions()
    {
        // this.adapteurIntervention.notifyDataSetChanged();
    }
}