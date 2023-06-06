package com.justfeed.justfeedandroid;

import android.app.AlertDialog;
import android.app.Dialog;
import android.content.DialogInterface;
import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.widget.EditText;
import android.widget.Spinner;
import android.widget.TextView;

import androidx.fragment.app.DialogFragment;

/**
 * @brief Définition de la classe DialogueDistributeur
 * @details La classe DialogueDistributeur permet à l'opérateur de modifier le
 * prix d'un bac du distributeur
 * @author Fargier Mayeul
 * @version 1.1
 */

public class DialogueDistributeur extends DialogFragment
{
    /**
     * Constantes
     */
    private final String TAG = "_DiaglogueDistributeur";

    /**
     * Attributs
     */
    private EditText prix; //!< Nouveau prix du produit

    @Override
    public Dialog onCreateDialog(Bundle savedInstanceState)
    {
        AlertDialog.Builder constructeur = new AlertDialog.Builder(getActivity());
        LayoutInflater inflater = requireActivity().getLayoutInflater();
        constructeur.setView(inflater.inflate(R.layout.dialogue, null));
        prix = (EditText) getView().findViewById(R.id.nouveauPrix);
        constructeur.setMessage(R.string.app_name)
                .setPositiveButton(R.string.valider, new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface interfaceDialogue, int id) {
                        Log.d(TAG, "Nouveau prix : "+prix.getText());
                    }
                })
                .setNegativeButton(R.string.annuler, new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface interfaceDialogue, int id) {
                        Log.d(TAG, "Annuler");
                    }
                });

        return constructeur.create();
    }
}
