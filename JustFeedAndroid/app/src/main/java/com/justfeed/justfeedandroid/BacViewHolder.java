package com.justfeed.justfeedandroid;

import android.content.res.Resources;
import android.graphics.drawable.Drawable;
import android.view.View;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;
import androidx.core.content.ContextCompat;
import androidx.core.content.res.ResourcesCompat;
import androidx.recyclerview.widget.RecyclerView;

public class BacViewHolder extends RecyclerView.ViewHolder
{
    private final int RECTANGLE_PLEIN = 300;

    private final TextView prix;
    private final TextView poidsActuel;
    private final TextView produit;
    private final TextView hydrometrie;

    public BacViewHolder(final View itemView)
    {
        super(itemView);

        prix        = ((TextView)itemView.findViewById(R.id.prix));
        poidsActuel = ((TextView)itemView.findViewById(R.id.poidsActuel));
        produit     = ((TextView)itemView.findViewById(R.id.produit));
        hydrometrie = ((TextView)itemView.findViewById(R.id.hydrometrie));
    }

    public void afficherBac(Bac bac)
    {
        /**
         * @bug division par zéro
         */
        /*int pourcentageRestant   = (int)(bac.getPoidsActuel() / bac.getPoidsTotalBac())*100;
        int remplissageRectangle = RECTANGLE_PLEIN / (pourcentageRestant / 100);*/

        prix.setText(String.format("%.2f €", bac.getTypeProduit().getPrix()));
        produit.setText(bac.getTypeProduit().getNom());
        hydrometrie.setText(Integer.toString(bac.getHydrometrie()));
        /*poidsActuel.setHeight(remplissageRectangle);*/
    }
}
