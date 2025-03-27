#include <stdio.h>
#include "structs.h"

int num_livres(char *name) {
    FILE *pf=fopen(name,"r");
    if (pf==NULL) {
        printf("Erreur d'ouverture du fichier %s\n",name);
        return 0;
    }
    int num=0;
    while(!feof(pf)) {
        livre l;
        fscanf(pf,"%s %s %s %d %d %d\n",l.code,l.titre,l.auteur,&l.annee,&l.nbExemplaires,&l.nbExemplairesDisponibles);
        num++;
    }
    fclose(pf);
    return num;
}


livre *livre_read(char *name) {
    FILE *pf=fopen(name,"r");
    int n = num_livres(name), i = 0; // nombre de livres
    livre livres[] = (livre *)malloc(n*sizeof(livre));
    if (pf==NULL) {
        printf("Erreur d'ouverture du fichier %s\n",name);
        return 0;
    }

    while(!feof(pf)) {
        livre l;
        fscanf(pf,"%s %s %s %d %d %d\n",l.code,l.titre,l.auteur,&l.annee,&l.nbExemplaires,&l.nbExemplairesDisponibles);
        livres[i] = l;
        i++;
    }
    return livres;
}


int etudiant_read(char *name) {
    FILE *pf=fopen(name,"r");
    if (pf==NULL) {
        printf("Erreur d'ouverture du fichier %s\n",name);
        return 0;
    }
    while(!feof(pf)) {
        etudiant e;
        fscanf(pf,"%s %s %s\n",e.prenom,e.nom,e.CNIE);
        printf("%s %s %s\n",e.prenom,e.nom,e.CNIE);
    }
    return 1;
}

int livre_write(char *name) {
    FILE *pf=fopen(name,"w");
    if (pf==NULL) {
        printf("Erreur d'ouverture du fichier %s\n",name);
        return 0;
    }
    livre l;
    printf("Donner le code du livre: ");
    scanf("%s",l.code);
    printf("Donner le titre du livre: ");
    scanf("%s",l.titre);
    printf("Donner l'auteur du livre: ");
    scanf("%s",l.auteur);
    printf("Donner l'annee du livre: ");
    scanf("%d",&l.annee);
    printf("Donner le nombre d'exemplaires du livre: ");
    scanf("%d",&l.nbExemplaires);
    printf("Donner le nombre d'exemplaires disponibles du livre: ");
    scanf("%d",&l.nbExemplairesDisponibles);
    fprintf(pf,"%s %s %s %d %d %d\n",l.code,l.titre,l.auteur,l.annee,l.nbExemplaires,l.nbExemplairesDisponibles);
    fclose(pf);
    return 1;
}

int etudiant_write(char *name) {
    FILE *pf=fopen(name,"w");
    if (pf==NULL) {
        printf("Erreur d'ouverture du fichier %s\n",name);
        return 0;
    }
    etudiant e;
    printf("Donner le prenom de l'etudiant: ");
    scanf("%s",e.prenom);
    printf("Donner le nom de l'etudiant: ");
    scanf("%s",e.nom);
    printf("Donner le CNIE de l'etudiant: ");
    scanf("%s",e.CNIE);
    fprintf(pf,"%s %s %s\n",e.prenom,e.nom,e.CNIE);
    fclose(pf);
    return 1;
}

livre *livre_search(char *name, char *code) {
    livre *l = ivre_read(name);
    int d = num_livres(name), g = 0;
    return search_decotomie(l, d, g, code);
}
int search_decotomie(livre *l, int d, int g, char *code) {
    if (d >= g) {
        int m = g + (d - g) / 2;
        if (strcmp(l[m].code,code)==0) {
            return m;
        }
        if (strcmp(l[m].code,code)>0) {
            return search_decotomie(l, m-1, g, code);
        }
        return search_decotomie(l, d, m+1, code);
    }
    return -1;
}