//
// Created by Costi on 06-Mar-24.
//

#include "domain.h"
#include <string.h>
#include <stdlib.h>
/*
 * Creeaza o oferta noua.
 *
 * Parametri:
 *   - tip: tipul ofertei (char*)
 *   - destinatie: destinatia ofertei (char*)
 *   - data_plecarii: data plecarii (char*)
 *   - pret: pretul ofertei (float)
 *
 * Returneaza:
 *   oferta - o structura reprezentand o oferta cu specificatiile date
 */
oferta creeazaOferta(char *tip, char *destinatie, char *data_plecarii, float pret)
{
    // Allocate memory for oferta struct
    oferta o;

    // Allocate memory for tip string and copy value
    o.tip = malloc(strlen(tip) + 1);
    if (o.tip == NULL) {
        // Handle memory allocation failure
        exit(EXIT_FAILURE);
    }
    strcpy(o.tip, tip);

    // Allocate memory for destinatie string and copy value
    o.destinatie = malloc(strlen(destinatie) + 1);
    if (o.destinatie == NULL) {
        // Handle memory allocation failure
        exit(EXIT_FAILURE);
    }
    strcpy(o.destinatie, destinatie);

    // Allocate memory for data_plecarii string and copy value
    o.data_plecarii = malloc(strlen(data_plecarii) + 1);
    if (o.data_plecarii == NULL) {
        // Handle memory allocation failure
        exit(EXIT_FAILURE);
    }
    strcpy(o.data_plecarii, data_plecarii);

    o.pret = pret;

    return o;
}

/*oferta creeazaOferta(char *tip, char *destinatie, char *data_plecarii, float pret)
{
    oferta o;

    // Allocate memory for the tip field
    o.tip = (char*)malloc(strlen(tip) + 1);
    if (o.tip == NULL) {
        // Handle memory allocation failure
        return o;  // Return an offer with uninitialized fields
    }
    strcpy(o.tip, tip);

    // Allocate memory for the destinatie field
    o.destinatie = (char*)malloc(strlen(destinatie) + 1);
    if (o.destinatie == NULL) {
        // Handle memory allocation failure
        free(o.tip);  // Free previously allocated memory
        o.tip = NULL;
        return o;  // Return an offer with uninitialized fields
    }
    strcpy(o.destinatie, destinatie);

    // Allocate memory for the data_plecarii field
    o.data_plecarii = (char*)malloc(strlen(data_plecarii) + 1);
    if (o.data_plecarii == NULL) {
        // Handle memory allocation failure
        free(o.tip);          // Free previously allocated memory
        free(o.destinatie);   // Free previously allocated memory
        o.tip = NULL;
        o.destinatie = NULL;
        return o;  // Return an offer with uninitialized fields
    }
    strcpy(o.data_plecarii, data_plecarii);

    o.pret = pret;
    return o;
}*/

/*
 * Valideaza o oferta.
 *
 * Parametri:
 *   - o: oferta de validat (oferta)
 *
 * Returneaza:
 *   int - 1 daca oferta este valida, 0 altfel
 */
int valideazaOferta(oferta o)
{
    /*
     * validator pentru oferta
     */
    if ((strcmp(o.tip,"munte") != 0) && (strcmp(o.tip , "mare") != 0) && (strcmp(o.tip, "city break") != 0))
        return 0;
    if (strlen(o.destinatie) == 0)
        return 0;
    if (strlen(o.data_plecarii) == 0)
        return 0;
    if (o.pret < 0)
        return 0;

    return 1;
}

/*
 * Distruge o oferta.
 *
 * Parametri:
 *   - o: oferta de distrus (oferta*)
 */
void distrugeOferta(oferta *o)
{
    if (o!= NULL)
    {
        if(!o->destroyed)
        {
            free(o->tip);
            free(o->destinatie);
            free(o->data_plecarii);
            o->destroyed = 1;
            free(o);
        }
    }

}

oferta copyOferta(oferta* o)
{
    return creeazaOferta(o->tip, o->destinatie, o->data_plecarii, o->pret);
}