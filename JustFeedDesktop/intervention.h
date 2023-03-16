#ifndef INTERVENTION_H
#define INTERVENTION_H
#include <ctime>

class Intervention
{
private:
    time_t heureIntervention;
    int numeroIntervention;
    float tempsTrajet;
    int poidsARemplir;
    bool aIntervenir;
    float localisation;
public:
    Intervention();
};

#endif // INTERVENTION_H
