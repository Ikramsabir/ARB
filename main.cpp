
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;
using namespace chrono;

struct Noeud
{
    int valeur;
    Noeud* gauche;
    Noeud* droite;
};

Noeud* CreerNoeud(int x) {
    Noeud* p = new Noeud;
    p->valeur = x;
    p->gauche = NULL;
    p->droite = NULL;
    return p;
}


Noeud* Inserer(Noeud* A, int x) {
    if (A == NULL)
        return CreerNoeud(x);

    Noeud* p = A;

    while (true) {
        if (x < p->valeur) {
            if (p->gauche == NULL) {
                p->gauche = CreerNoeud(x);
                break;
            }
            p = p->gauche;
        }
        else if (x > p->valeur) {
            if (p->droite == NULL) {
                p->droite = CreerNoeud(x);
                break;
            }
            p = p->droite;
        }
        else {
            break;
        }
    }

    return A;
}


Noeud* Recherche(Noeud* A, int x) {
    if (A == NULL)
        return NULL;

    if (A->valeur == x)
        return A;

    if (x < A->valeur)
        return Recherche(A->gauche, x);

    return Recherche(A->droite, x);
}

Noeud* Suppression(Noeud* A, int x) {
    if (A == NULL)
        return NULL;

    if (x < A->valeur)
        A->gauche = Suppression(A->gauche, x);

    else if (x > A->valeur)
        A->droite = Suppression(A->droite, x);

    else {
        if (A->gauche == NULL) {
            Noeud* p = A->droite;
            delete A;
            return p;
        }
        else if (A->droite == NULL) {
            Noeud* p = A->gauche;
            delete A;
            return p;
        }
        else {
            Noeud* p = A->droite;

            while (p->gauche != NULL)
                p = p->gauche;

            A->valeur = p->valeur;
            A->droite = Suppression(A->droite, p->valeur);
        }
    }

    return A;
}

int main() {
    Noeud* A = NULL;
    Noeud* B = NULL;

    map<int, int> M1;
    map<int, int> M2;

    int n, x;
    srand(time(NULL));

    cout << "Donner le nombre de noeuds : ";
    cin >> n;

    if (n <= 0) {
        cout << "Le nombre doit etre positif.";
        return 0;
    }

    vector<int> T(n);

    for (int i = 0; i < n; i++)
        T[i] = i + 1;

    vector<int> T_aleatoire = T;
    random_shuffle(T_aleatoire.begin(), T_aleatoire.end());

    auto debut = high_resolution_clock::now();

    for (int i = 1; i <= n; i++)
        A = Inserer(A, i);

    auto fin = high_resolution_clock::now();

    cout << "\n===== ABR MANUELLE ORDONNEE =====" << endl;
    cout << "Temps insertion : "
         << duration_cast<nanoseconds>(fin - debut).count()
         << " nanosecondes" << endl;

    debut = high_resolution_clock::now();

    for (int i = 0; i < n; i++)
        B = Inserer(B, T_aleatoire[i]);

    fin = high_resolution_clock::now();

    cout << "\n===== ABR MANUELLE ALEATOIRE =====" << endl;
    cout << "Temps insertion : "
         << duration_cast<nanoseconds>(fin - debut).count()
         << " nanosecondes" << endl;

    debut = high_resolution_clock::now();

    for (int i = 1; i <= n; i++)
        M1.insert({i, i});

    fin = high_resolution_clock::now();

    cout << "\n===== MAP ORDRE D'INSERTION TRIE =====" << endl;
    cout << "Temps insertion : "
         << duration_cast<nanoseconds>(fin - debut).count()
         << " nanosecondes" << endl;

    debut = high_resolution_clock::now();

    for (int i = 0; i < n; i++)
        M2.insert({T_aleatoire[i], T_aleatoire[i]});

    fin = high_resolution_clock::now();

    cout << "\n===== MAP ORDRE D'INSERTION ALEATOIRE =====" << endl;
    cout << "Temps insertion : "
         << duration_cast<nanoseconds>(fin - debut).count()
         << " nanosecondes" << endl;

    cout << "\nDonner la valeur a rechercher : ";
    cin >> x;

    debut = high_resolution_clock::now();
    Noeud* p = Recherche(A, x);
    fin = high_resolution_clock::now();

    cout << "\nRecherche ABR ordonnee : "
         << duration_cast<nanoseconds>(fin - debut).count()
         << " nanosecondes" << endl;

    debut = high_resolution_clock::now();
    Noeud* q = Recherche(B, x);
    fin = high_resolution_clock::now();

    cout << "Recherche ABR aleatoire : "
         << duration_cast<nanoseconds>(fin - debut).count()
         << " nanosecondes" << endl;

    debut = high_resolution_clock::now();
    auto r1 = M1.find(x);
    fin = high_resolution_clock::now();

    cout << "Recherche map ordre trie : "
         << duration_cast<nanoseconds>(fin - debut).count()
         << " nanosecondes" << endl;

    debut = high_resolution_clock::now();
    auto r2 = M2.find(x);
    fin = high_resolution_clock::now();

    cout << "Recherche map ordre aleatoire : "
         << duration_cast<nanoseconds>(fin - debut).count()
         << " nanosecondes" << endl;

    cout << "\nDonner la valeur a supprimer : ";
    cin >> x;

    debut = high_resolution_clock::now();
    A = Suppression(A, x);
    fin = high_resolution_clock::now();

    cout << "\nSuppression ABR ordonnee : "
         << duration_cast<nanoseconds>(fin - debut).count()
         << " nanosecondes" << endl;

    debut = high_resolution_clock::now();
    B = Suppression(B, x);
    fin = high_resolution_clock::now();

    cout << "Suppression ABR aleatoire : "
         << duration_cast<nanoseconds>(fin - debut).count()
         << " nanosecondes" << endl;

    debut = high_resolution_clock::now();
    M1.erase(x);
    fin = high_resolution_clock::now();

    cout << "Suppression map ordre trie : "
         << duration_cast<nanoseconds>(fin - debut).count()
         << " nanosecondes" << endl;

    debut = high_resolution_clock::now();
    M2.erase(x);
    fin = high_resolution_clock::now();

    cout << "Suppression map ordre aleatoire : "
         << duration_cast<nanoseconds>(fin - debut).count()
         << " nanosecondes" << endl;

    return 0;
}
