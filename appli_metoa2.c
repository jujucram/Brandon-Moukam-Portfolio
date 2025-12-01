#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_POINTS 20  // Nombre maximum de points par itinéraire

//1) definition des structures de donnees
//stockage des infos d'un client
typedef struct {
    int id;
    char nom[30];
    char prenom[30];
} Client;

//stockage des infos pour un taxi
typedef struct {
    int num;
    char immatriculation[20];
    char marque[10];
    int nb_places;
    char localisation[30];
} Taxi;

typedef struct {
    char point[20];
} Taxi_point;

// Structure pour représenter un point dans un trajet
typedef struct {
    char lieu[50];      // nom du point
    float distance;     // distance vers le point suivant
} Point;

// Structure itineraire avec tableau de points
typedef struct {
    int num;
    Point trajets[MAX_POINTS];  // tableau de points
    int nb_points;              // nombre de points dans l'itinéraire
} Itineraire;

// Fonction pour ajouter un point à un itinéraire
void ajouter_point_itineraire(Itineraire* itin, char* lieu, float distance) {
    if (itin->nb_points < MAX_POINTS) {
        strcpy(itin->trajets[itin->nb_points].lieu, lieu);
        itin->trajets[itin->nb_points].distance = distance;
        itin->nb_points++;
    } else {
        printf("Erreur: Nombre maximum de points atteint pour cet itinéraire.\n");
    }
}

// Fonction pour initialiser les 5 itinéraires pré-définis
void initialiser_itineraires(Itineraire itin[], int* nb_itin) {
    // Itineraire 1: BORNE10 -> COMMISSARIAT_ODZA -> AUBERGE-BLEUE -> MBOG-ABANG -> HAPPY
    itin[0].num = 1;
    itin[0].nb_points = 0;
    ajouter_point_itineraire(&itin[0], "BORNE10", 2.5);
    ajouter_point_itineraire(&itin[0], "COMMISSARIAT_ODZA", 3.2);
    ajouter_point_itineraire(&itin[0], "AUBERGE-BLEUE", 1.8);
    ajouter_point_itineraire(&itin[0], "MBOG-ABANG", 1.8);
    ajouter_point_itineraire(&itin[0], "HAPPY", 0);

    // Itineraire 2: BORNE10 -> COMMISSARIAT_ODZA -> ADVENTISTE -> TROPICANA -> MBOG-ABANG -> HAPPY
    itin[1].num = 2;
    itin[1].nb_points = 0;
    ajouter_point_itineraire(&itin[1], "BORNE10", 2.5);
    ajouter_point_itineraire(&itin[1], "COMMISSARIAT_ODZA", 1.9);
    ajouter_point_itineraire(&itin[1], "ADVENTISTE", 2.3);
    ajouter_point_itineraire(&itin[1], "TROPICANA", 1.5);
    ajouter_point_itineraire(&itin[1], "MBOG-ABANG", 1.8);
    ajouter_point_itineraire(&itin[1], "HAPPY", 0);

    // Itineraire 3: BORNE10 -> COMMISSARIAT_ODZA -> ADVENTISTE -> TROPICANA -> CARREFOUR_DE_L'AMITIE -> HAPPY
    itin[2].num = 3;
    itin[2].nb_points = 0;
    ajouter_point_itineraire(&itin[2], "BORNE10", 2.5);
    ajouter_point_itineraire(&itin[2], "COMMISSARIAT_ODZA", 1.9);
    ajouter_point_itineraire(&itin[2], "ADVENTISTE", 2.3);
    ajouter_point_itineraire(&itin[2], "TROPICANA", 0.5);
    ajouter_point_itineraire(&itin[2], "CARREFOUR_DE_L'AMITIE", 1.4);
    ajouter_point_itineraire(&itin[2], "HAPPY", 0);

    // Itineraire 4: BORNE10 -> RUE_ANCIEN_MINISTRE -> AUBERGE-BLEUE -> MBOG-ABANG -> HAPPY
    itin[3].num = 4;
    itin[3].nb_points = 0;
    ajouter_point_itineraire(&itin[3], "BORNE10", 0.4);
    ajouter_point_itineraire(&itin[3], "RUE_ANCIEN_MINISTRE", 1.6);
    ajouter_point_itineraire(&itin[3], "AUBERGE-BLEUE", 1.8);
    ajouter_point_itineraire(&itin[3], "MBOG-ABANG", 1.8);
    ajouter_point_itineraire(&itin[3], "HAPPY", 0);

    // Itineraire 5: BORNE10 -> MINKAN -> COMMISSARIAT_ODZA -> AUBERGE-BLEUE -> MBOG-ABANG -> HAPPY
    itin[4].num = 5;
    itin[4].nb_points = 0;
    ajouter_point_itineraire(&itin[4], "BORNE10", 2.6);
    ajouter_point_itineraire(&itin[4], "MINKAN", 2.9);
    ajouter_point_itineraire(&itin[4], "COMMISSARIAT_ODZA", 4.2);
    ajouter_point_itineraire(&itin[4], "AUBERGE-BLEUE", 1.8);
    ajouter_point_itineraire(&itin[4], "MBOG-ABANG", 1.8);
    ajouter_point_itineraire(&itin[4], "HAPPY", 0);

    *nb_itin = 5;

    printf(" 5 itineraires ont ete automatiquement enregistres dans le systeme.\n");
}

//3 fonctions permettant d'enregistrer les informations
void client_registration(Client client[], int *nb_clients) {
    Client c;
    printf("Entrez l'ID du client : ");
    scanf("%d", &c.id);
    printf("\nEntrez le nom du client : ");
    scanf("%s", c.nom);
    printf("\nEntrez le prenom du client : ");
    scanf("%s", c.prenom);
    client[*nb_clients] = c;
    (*nb_clients)++;
}

//pour eviter les doublons(2 numeros identiques pour 2 taxis)
int existe_taxi(Taxi taxi[], int nb_taxis, int num) {
    for (int i = 0; i < nb_taxis; i++) {
        if (taxi[i].num == num)
            return 1;
    }
    return 0;
}

void taxi_registration(Taxi taxi[], int *nb_taxis) {
    printf("Taxis déjà enregistrés : ");
    if(*nb_taxis == 0) {
        printf("AUCUN");
    }
    for (int i = 0; i < *nb_taxis; i++) {
        printf("[%d] ", taxi[i].num);
    }
    printf("\n");

    Taxi t;
    do {
        printf("Entrez le numéro du taxi : ");
        scanf("%d", &t.num);
        if (existe_taxi(taxi, *nb_taxis, t.num)) {
            printf("Ce numéro de taxi existe déjà. Veuillez en entrer un autre.\n");
        }
    } while(existe_taxi(taxi, *nb_taxis, t.num));

    printf("Entrez l'immatriculation du taxi : ");
    scanf("%s", t.immatriculation);
    printf("Entrez la marque du taxi : ");
    scanf("%s", t.marque);
    printf("Entrez le nombre de places : ");
    scanf("%d", &t.nb_places);
    printf("Localisation du taxi : ");
    scanf("%s", t.localisation);
    taxi[*nb_taxis] = t;
    (*nb_taxis)++;
}

void trajet_registration(Itineraire* itin, int n) {
    char point[30];

    itin->nb_points = 0;

    for (int i = 0; i < n; i++) {
        printf("Point %d : ", i + 1);
        scanf("%s", point);

        float distance = 0;
        if (i != n - 1) {
            printf("Distance vers le point suivant : ");
            scanf("%f", &distance);
        }

        ajouter_point_itineraire(itin, point, distance);
    }
}

//4 fonction permettant d'enregistrer les itineraires
//pour eviter d'avoir 2 itineraires ayant un numero identique
int existe_itineraire(Itineraire itin[], int nb_itin, int num) {
    for (int i = 0; i < nb_itin; i++) {
        if (itin[i].num == num)
            return 1;
    }
    return 0;
}

void itineraire_registration(Itineraire itin[], int *nb_itin) {
    printf("Itineraires déjà enregistrés : ");
    if(*nb_itin == 0) {
        printf("AUCUN");
    }
    for (int i = 0; i < *nb_itin; i++) {
        printf("[%d] ", itin[i].num);
    }
    printf("\n");

    Itineraire i;
    do {
        printf("Entrez le numéro de l'itinéraire : ");
        scanf("%d", &i.num);
        if (existe_itineraire(itin, *nb_itin, i.num)) {
            printf("Ce numéro d'itinéraire existe déjà. Veuillez en entrer un autre.\n");
        }
    } while (existe_itineraire(itin, *nb_itin, i.num));

    int n;
    printf("Entrez le nombre de points pour cet itinéraire (max %d) : ", MAX_POINTS);
    scanf("%d", &n);

    if (n > MAX_POINTS) {
        printf("Nombre de points trop élevé. Maximum autorisé : %d\n", MAX_POINTS);
        n = MAX_POINTS;
    }

    trajet_registration(&i, n);
    itin[*nb_itin] = i;
    (*nb_itin)++;
}

//5) fonctions pour afficher les informations
void affichage_client(Client client[], int nb_clients) {
    if(nb_clients == 0) {
        printf("AUCUN CLIENT ENREGISTRÉ");
    }
    for (int i = 0; i < nb_clients; i++) {
        printf("ID : %d\nNom : %s\nPrenom: %s\n", client[i].id, client[i].nom, client[i].prenom);
    }
}

void affichage_taxi(Taxi taxi[], int nb_taxis) {
    if(nb_taxis == 0)
        printf("AUCUN TAXI ENREGISTRE\n");
    for (int i = 0; i < nb_taxis; i++) {
        printf("\nTaxi #%d\nImmatriculation : %s\nMarque : %s\nLocalisation: %s \nPlaces : %d\n",
               taxi[i].num, taxi[i].immatriculation, taxi[i].marque, taxi[i].localisation, taxi[i].nb_places);
    }
}

void affichage_trajet(Itineraire itin) {
    printf("Trajet : ");
    for (int i = 0; i < itin.nb_points; i++) {
        printf("%s", itin.trajets[i].lieu);
        if (i < itin.nb_points - 1) {
            printf(" --(%.1f km)--> ", itin.trajets[i].distance);
        }
    }
    printf("\n");
}

void affichage_itineraire(Itineraire itin[], int nb) {
    if(nb == 0) {
        printf("AUCUN ITINERAIRE");
    }
    for (int i = 0; i < nb; i++) {
        printf("\nItinéraire #%d\n", itin[i].num);
        affichage_trajet(itin[i]);
    }
}

//6 fonction pour trouver le plus court chemin
//pour chaque itineraire on somme les distances entre les points de son tableau de trajets
float distance_totale(Itineraire itin) {
    float total = 0;
    for (int i = 0; i < itin.nb_points; i++) {
        total += itin.trajets[i].distance;
    }
    return total;
}

void trouver_itineraire_plus_court(Itineraire itin[], int nb_itin) {
    if (nb_itin == 0) {
        printf("Aucun itinéraire enregistré.\n");
        return;
    }

    //on compare ces distances
    int index_min = 0;
    float min_distance = distance_totale(itin[0]);

    for (int i = 1; i < nb_itin; i++) {
        float d = distance_totale(itin[i]);
        if (d < min_distance) {
            min_distance = d;
            index_min = i;
        }
    }

    //affichage de l'itineraire avec la plus courte distance
    printf("\n>>> Itinéraire le plus court : #%d (%.2f km)\n",
           itin[index_min].num, min_distance);
    affichage_trajet(itin[index_min]);
}

//7 algorithme pour reserver un taxi
void prendre_taxi(Itineraire itin[], int nb_itin, Taxi taxi[], int nb_taxis) {
    int num_itin;
    //on choisit un itineraire par son numero
    printf("Entrez le numéro de l'itinéraire souhaité : ");
    scanf("%d", &num_itin);

    int trouve = 0;
    for (int i = 0; i < nb_itin; i++) {
        if (itin[i].num == num_itin) {
            trouve = 1;
            printf("Itinéraire trouvé :\n");
            affichage_trajet(itin[i]);
            break;
        }
    }

    if (!trouve) {
        printf("Itinéraire non trouvé.\n");
        return;
    }

    //on affiche les taxis disponible
    printf("\nTAXIS DISPONIBLES :\n");
    if(nb_taxis == 0) {
        printf("AUCUN TAXI ENREGISTRE");
    } else {
        affichage_taxi(taxi, nb_taxis);
        //on choisit un taxi
        //si le nombre de places > 0 on réserve et on décrémente
        int choix;
        printf("Entrez le numéro du taxi à réserver : ");
        scanf("%d", &choix);
        trouve = 0;
        for (int i = 0; i < nb_taxis; i++) {
            if (taxi[i].num == choix) {
                trouve = 1;
                if (taxi[i].nb_places > 0) {
                    taxi[i].nb_places--;
                    printf("Taxi réservé avec succès.\n");
                } else {
                    printf("Taxi plein.\n");
                }
                break;
            }
        }
        if (!trouve) {
            printf("Taxi non trouvé.\n");
        }
    }
}

int main() {
    Client client[100];
    Taxi taxi[100];
    Itineraire itin[100];
    int nb_clients = 0, nb_taxis = 0, nb_itin = 0;

    printf("===   BIENVENUE SUR METOA   ===\n\n");
    // Initialisation automatique des 5 itinéraires
    printf("=== INITIALISATION DU SYSTEME METOA ... ===\n");
    initialiser_itineraires(itin, &nb_itin);//appel de la fonction avec itineraires enregistrés
    printf("Systeme pret a l'utilisation !\n");

    int choix;
    do {
        printf("\n===== MENU METOA =====\n");
        printf("1. Enregistrer un client\n");
        printf("2. Enregistrer un taxi\n");
        printf("3. Enregistrer un itineraire\n");
        printf("4. Afficher les clients\n");
        printf("5. Afficher les taxis\n");
        printf("6. Afficher les itineraires\n");
        printf("7. Reserver un taxi\n");
        printf("8. Trouver l itineraire le plus court\n");
        printf("0. Quitter\n");
        printf("Choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1: client_registration(client, &nb_clients); break;
            case 2: taxi_registration(taxi, &nb_taxis); break;
            case 3: itineraire_registration(itin, &nb_itin); break;
            case 4: affichage_client(client, nb_clients); break;
            case 5: affichage_taxi(taxi, nb_taxis); break;
            case 6: affichage_itineraire(itin, nb_itin); break;
            case 7: prendre_taxi(itin, nb_itin, taxi, nb_taxis); break;
            case 8: trouver_itineraire_plus_court(itin, nb_itin); break;
            case 0: printf("Merci d'avoir utilisé Metoa.\n"); break;
            default: printf("Choix invalide.\n");
        }

    } while (choix != 0);

    return 0;
}
