#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

typedef struct
{
    float x;
    float y;
    float z;
} Vrh;

typedef struct
{
    float ni;
    float nj;
    float nk;
    Vrh vrhovi[3];
    unsigned short boja;
} Trokut;

typedef struct
{
    Trokut *niz_trokuta;
    unsigned int broj_trokuta;
} Objekt3D;

Objekt3D *vrati_objekt3D(FILE *fp)
{
    Objekt3D *objekt3d = (Objekt3D *)malloc(sizeof(Objekt3D));
    fseek(fp, 80, SEEK_SET);
    fread(&(objekt3d->broj_trokuta), 4, 1, fp); //zapisan broj trokuta iz datoteke
    objekt3d->niz_trokuta = (Trokut *)malloc(sizeof(Trokut) * objekt3d->broj_trokuta + 1);
    int i = 0;
    while (!feof(fp))
    {
        fread(&(objekt3d->niz_trokuta[i++]), 50, 1, fp);
    }
    return objekt3d;
}

void zapisi_binarnu(Objekt3D *objekt3d, FILE *fp)
{
    int nula[20] = {0};
    fwrite(nula, sizeof(int), 20, fp);                            //zapisi nule
    fwrite(&objekt3d->broj_trokuta, sizeof(unsigned int), 1, fp); //zapisi broj trokuta
    for (int i = 0; i < objekt3d->broj_trokuta; i++)
    { //zapisi ostatak strukture
        fwrite(&objekt3d->niz_trokuta[i], 1, 50, fp);
    }
}
void zapisi_tekstualnu(Objekt3D *objekt3d, FILE *fp)
{

    fprintf(fp, "solid OpenSCAD Model \n");
    for (int i = 0; i < objekt3d->broj_trokuta; i++)
    {
        fprintf(fp, "  facet normal %f %f %f \n", objekt3d->niz_trokuta[i].ni, objekt3d->niz_trokuta[i].nj, objekt3d->niz_trokuta[i].nk);
        fprintf(fp, "    outer loop \n");

        for (int j = 0; j < 3; j++)
        {
            fprintf(fp, "      vertex %f %f %f\n", objekt3d->niz_trokuta[i].vrhovi[j].x, objekt3d->niz_trokuta[i].vrhovi[j].y, objekt3d->niz_trokuta[i].vrhovi[j].z);
        }
        fprintf(fp, "  endloop \n");
        fprintf(fp, "endfacet \n");
    }
    fprintf(fp, "endsolid OpenSCAD_Model ");
}

void zatvori(Objekt3D *objekt3d)
{
    free(objekt3d->niz_trokuta);
    free(objekt3d);
}
int main()
{
    Objekt3D *vrati_objekt3D(FILE * fp);

    /*         PROVJERA VRATI OBJEKT3D      */
    FILE *fp1 = fopen("primjerbin.stl", "rb"); //read binary
    Objekt3D *objekt3d = vrati_objekt3D(fp1);
    fclose(fp1);
    /*            PROVJERA ZAPISI BINARNU    */
    FILE *fp2 = fopen("primjerbin2.stl", "wb");
    zapisi_binarnu(objekt3d, fp2);
    fclose(fp2);
    /*          PROVJERA ZAPISI TEKSUTALNU    */
    FILE *fp3 = fopen("primjertxt2.stl", "w+");
    zapisi_tekstualnu(objekt3d, fp3);
    fclose(fp3);
    zatvori(objekt3d);
}
