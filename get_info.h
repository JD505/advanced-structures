#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define _CRT_NONSTDC_NO_DEPRECATE

#define FILE_NAME_PATIENT "patient_information.txt"
#define FILE_NAME_HOSPITAL "hospital_information.txt"

typedef struct patient
{
    int number;
    char* name;

    char* pref1;
    char* pref2;
    char* pref3;
    char* pref4;
    char* pref5;

    bool Cpref1;
    bool Cpref2;
    bool Cpref3;
    bool Cpref4;
    bool Cpref5;

    int dist_pref1;
    int dist_pref2;
    int dist_pref3;
    int dist_pref4;
    int dist_pref5;

    struct patient* seguinte;
} patient;

typedef struct vagas
{
    char* nameHospital;
    int numVagas;

    struct vagas* seguinte;
} vagas;

typedef struct coloc {

    char* hospital;
    int nVagas;

    patient* colocado;
    patient* naoColocado;
    bool impat;
    struct coloc* seguinte;
}coloc;

char* toLower(char* s) {
    if (s != NULL) {
        for (char* p = s; *p; p++) *p = tolower(*p);
        return s;
    }
    else return(s);
}

// function to remove text between arguments
char* getTextBetween(char line[], const char start[], const char end[], int selector)
{

    int size = strlen(line);
    char* lineCopy = (char*)malloc(size + 1);

    if (lineCopy != 0) {

        strcpy(lineCopy, line);

        if (strstr(lineCopy, start) != NULL) { // check if "start" exists

            char* data = strstr(lineCopy, start);

            if (selector == 1)
                data = strtok(data + (strlen(start)), end);

            else
                data = strtok(data, end);

            return(data);
        }
    }
    return(NULL);
}

// ******************************* patient ***************************************************************
// add value in list
// get infomation from file
// number of patients
// show list
// add patient
// remove patient
patient* inserirInicio(patient* inicio, int number, char* name, char* pref1, int dist_pref1, char* pref2, 
    int dist_pref2, char* pref3, int dist_pref3, char* pref4, int dist_pref4, char* pref5, int dist_pref5)
{
    patient* novo = (patient*)malloc(sizeof(patient));

    if ((number != NULL) && (name != NULL) && (pref1 != NULL) && (dist_pref1 != NULL) && (dist_pref1 > 0)) { //check if name, numer, pref1, distance 1 is ok

        novo->number = number;
        novo->name = toLower(name);

        novo->pref1 = toLower(pref1);
        novo->dist_pref1 = dist_pref1;

        novo->Cpref1 = false;
        novo->Cpref2 = false;
        novo->Cpref3 = false;
        novo->Cpref4 = false;
        novo->Cpref5 = false;

        if ((pref2 != NULL) && (dist_pref2 != NULL) && (dist_pref2 > 0)) { //check pref2

            novo->pref2 = toLower(pref2);
            novo->dist_pref2 = dist_pref2;

            if ((pref3 != NULL) && (dist_pref3 != NULL) && (dist_pref3 > 0)) {

                novo->pref3 = toLower(pref3);
                novo->dist_pref3 = dist_pref3;

                if ((pref4 != NULL) && (dist_pref4 != NULL) && (dist_pref4 > 0)) {

                    novo->pref4 = toLower(pref4);
                    novo->dist_pref4 = dist_pref4;

                    if ((pref5 != NULL) && (dist_pref5 != NULL) && (dist_pref5 > 0)) {

                        novo->pref5 = toLower(pref5);
                        novo->dist_pref5 = dist_pref5;
                    }
                    else {

                        novo->pref5 = NULL;
                        novo->dist_pref5 = NULL;
                    }
                }
                else {

                    novo->pref4 = NULL;
                    novo->pref5 = NULL;

                    novo->dist_pref4 = NULL;
                    novo->dist_pref5 = NULL;
                }

            }
            else {

                novo->pref3 = NULL;
                novo->pref4 = NULL;
                novo->pref5 = NULL;

                novo->dist_pref3 = NULL;
                novo->dist_pref4 = NULL;
                novo->dist_pref5 = NULL;
            }

        }
        else { // write null if pref2 or distance 2 is not ok

            novo->pref2 = NULL;
            novo->pref3 = NULL;
            novo->pref4 = NULL;
            novo->pref5 = NULL;

            novo->dist_pref2 = NULL;
            novo->dist_pref3 = NULL;
            novo->dist_pref4 = NULL;
            novo->dist_pref5 = NULL;

        }

    }

    novo->seguinte = inicio;

    return(novo);
}

patient* readText(patient* lista) {

    FILE* fp;
    fp = fopen(FILE_NAME_PATIENT, "r");

    if (fp == NULL) { // check if file exists
        perror("No file found");
        return NULL;
    }

    bool flag_error_read = false;
    char buffer[256];

    while (fgets(buffer, 256 - 1, fp)) //read line by line 
    {
        char* pref2 = NULL;
        char* pref3 = NULL;
        char* pref4 = NULL;
        char* pref5 = NULL;

        int dist2 = NULL;
        int dist3 = NULL;
        int dist4 = NULL;
        int dist5 = NULL;

        // Remove trailing newline
        buffer[strcspn(buffer, "\n")] = 0;

        if ((strstr(buffer, "number") != NULL) && (strstr(buffer, "name") != NULL) && (strstr(buffer, "pref1") != NULL)) {

            char* num = (getTextBetween(buffer, "number:", ";", 1));
            int number = atoi(num);

            char* name = (getTextBetween(buffer, "name:", ";", 1));

            char* pref1 = (getTextBetween(buffer, "pref1:", "-", 1));
            char* dist_1 = (getTextBetween(buffer, (getTextBetween(buffer, "pref1:", "-", 0)), ";", 1));
            int dist1 = atoi(dist_1 + 1);

            if (strstr(buffer, "pref2") != NULL) {

                pref2 = (getTextBetween(buffer, "pref2:", "-", 1));
                char* dist_2 = (getTextBetween(buffer, (getTextBetween(buffer, "pref2:", "-", 0)), ";", 1));
                dist2 = atoi(dist_2 + 1);

                if (strstr(buffer, "pref3") != NULL) {

                    pref3 = (getTextBetween(buffer, "pref3:", "-", 1));
                    char* dist_3 = (getTextBetween(buffer, (getTextBetween(buffer, "pref3:", "-", 0)), ";", 1));
                    dist3 = atoi(dist_3 + 1);

                    if (strstr(buffer, "pref4") != NULL) {

                        pref4 = (getTextBetween(buffer, "pref4:", "-", 1));
                        char* dist_4 = (getTextBetween(buffer, (getTextBetween(buffer, "pref4:", "-", 0)), ";", 1));
                        dist4 = atoi(dist_4 + 1);

                        if (strstr(buffer, "pref5") != NULL) {

                            pref5 = (getTextBetween(buffer, "pref5:", "-", 1));
                            char* dist_5 = (getTextBetween(buffer, (getTextBetween(buffer, "pref5:", "-", 0)), ";", 1));
                            dist5 = atoi(dist_5 + 1);
                        }

                    }

                }

            }

            lista = inserirInicio(lista, number, name, pref1, dist1, pref2, dist2, pref3, dist3, pref4, dist4, pref5, dist5);

        }
        else {
            flag_error_read = true;
        }

    }

    if (flag_error_read == true) {
        printf("Errors occurred while reading the file.\n");
    }

    fclose(fp);
    return (lista);
}

int numPatient(patient* patt) {
    patient* aux = patt;
    int contador = 0;
    while (aux!= NULL) {
        contador++;
        aux = aux->seguinte;
    }
    return(contador);
}
void listar_patient(patient* inicio)
{
    patient* aux = inicio;
    while (aux != NULL)
    {
        if ((aux->number != NULL) && (aux->name != NULL)) {

            printf("Number: %d \n", aux->number);
            printf("Name: %s \n", aux->name);
        }

        if ((aux->dist_pref1 != NULL) && (aux->pref1 != NULL)) {

            printf("Preference 1: %s, ", aux->pref1);
            printf("Distance: %d \n", aux->dist_pref1);
        }

        if ((aux->dist_pref2 != NULL) && (aux->pref2 != NULL)) {

            printf("Preference 2: %s, ", aux->pref2);
            printf("Distance: %d \n", aux->dist_pref2);
        }

        if ((aux->dist_pref3 != NULL) && (aux->pref3 != NULL)) {

            printf("Preference 3: %s, ", aux->pref3);
            printf("Distance: %d \n", aux->dist_pref3);
        }

        if (aux->dist_pref4 != NULL && aux->pref4 != NULL) {

            printf("Preference 4: %s, ", aux->pref4);
            printf("Distance: %d \n", aux->dist_pref4);
        }

        if (aux->dist_pref5 != NULL && aux->pref5 != NULL) {

            printf("Preference 5: %s, ", aux->pref5);
            printf("Distance: %d \n", aux->dist_pref5);
        }
        aux = aux->seguinte;
        printf("---------------------------------------------------\n\n");
    }

}

void addPatient(patient* patt) {

    FILE* fp;
    fp = fopen(FILE_NAME_PATIENT, "a");

    if (patt->number != NULL && patt->name != NULL && patt->pref1 != NULL && patt->dist_pref1 != NULL) {

        fprintf(fp, "number:%d;name:%s;pref1:%s-%d;", patt->number, patt->name, patt->pref1, patt->dist_pref1);

        if (patt->pref2 != NULL && patt->dist_pref2 != NULL) {

            fprintf(fp, "pref2:%s-%d;", patt->pref2, patt->dist_pref2);

            if (patt->pref3 != NULL && patt->dist_pref3 != NULL) {

                fprintf(fp, "pref3:%s-%d;", patt->pref3, patt->dist_pref3);

                if (patt->pref4 != NULL && patt->dist_pref4 != NULL) {

                    fprintf(fp, "pref4:%s-%d;", patt->pref4, patt->dist_pref4);

                    if (patt->pref5 != NULL && patt->dist_pref5 != NULL) {

                        fprintf(fp, "pref5:%s-%d;", patt->pref5, patt->dist_pref5);
                    }
                }
            }
        }
    }
    fprintf(fp, "\n");
    fclose(fp);
}
void removePatient(int number) {

    FILE* fp;
    fp = fopen(FILE_NAME_PATIENT, "r+");

    char bufferAux[256] = "";

    if (fp != NULL) { // check if file exists

        char buffer[256];

        while (fgets(buffer, 256 - 1, fp)) //read line by line 
        {

            if ((strstr(buffer, "number") != NULL)) {

                char* auxNum = (getTextBetween(buffer, "number:", ";", 1));
                int lineNum = atoi(auxNum);

                if (lineNum != number) {

                    strcat(bufferAux, buffer);
                }
            }

        }

        fclose(fp);

        FILE* novo;
        novo = fopen(FILE_NAME_PATIENT, "w");

        if (bufferAux != NULL) {
            fprintf(novo, "%s", bufferAux);
        }

        fclose(novo);
    }
    else {

        perror("No file found");
    }



}


//******************************* vagas *******************************************************************
// add value in list
// get infomation from file
// number of hospitals
// show list
// add Hospital 
// remove hospital
vagas* insertVagas(vagas* inicio, char* hospital, int num_vagas) {

    vagas* novo = (vagas*)malloc(sizeof(vagas));

    if ((hospital != NULL) && (num_vagas != NULL) ) {

        novo->nameHospital = hospital;
        novo->numVagas = num_vagas;
    }
    
    novo->seguinte = inicio;

    return(novo);
}

vagas* readVagas(vagas* lista_vagas) {

    FILE* fp;
    fp = fopen(FILE_NAME_HOSPITAL, "r");

    if (fp == NULL) { // check if file exists
        perror("No file found");
        return NULL;
    }

    bool flag_error_read = false;
    char buffer[256];

    while (fgets(buffer, 256 - 1, fp)) //read line by line 
    {        

        // Remove trailing newline
        buffer[strcspn(buffer, "\n")] = 0;

        if ((strstr(buffer, "hospital") != NULL) && (strstr(buffer, "vagas") != NULL)) {           

            char* hospital = (getTextBetween(buffer, "hospital:", ";", 1));
            
            char* num = (getTextBetween(buffer, "vagas:", ";", 1));
            int numVagas = atoi(num);
            
            lista_vagas = insertVagas(lista_vagas, hospital, numVagas);
        }
        else {
            flag_error_read = true;
        }        
    }

    if (flag_error_read == true) {
        printf("Errors occurred while reading the file.\n");
    }

    fclose(fp);
    return (lista_vagas);


}

int numHospital(vagas* hospital) {
    
    vagas* aux = hospital; 
    int contador = 0;
    while (aux != NULL) {
       
        if(aux->numVagas>0) contador++;       
       
        aux = aux->seguinte;
    }
    return(contador);
}

void listar_vagas(vagas* inicio)
{
    vagas* aux = inicio;
    while (aux != NULL)
    {
        if ((aux->nameHospital != NULL) && (aux->numVagas != NULL)) {

            printf("Hospital Name: %s -> ", aux->nameHospital);
            printf("Vacancies: %d \n", aux->numVagas);
        }

        aux = aux->seguinte;
    }
    printf("\n");
}

void addHospital(char hospital[], int numVagas) {

    FILE* fp;
    fp = fopen(FILE_NAME_HOSPITAL, "a");

    if ((hospital != NULL) && numVagas != NULL) {

        fprintf(fp, "hospital:%s;vagas:%d;\n", hospital, numVagas);
    }
    fclose(fp);
}
bool removeHospital(char hospital[]) {

    bool flag = false;
    FILE* fp;
    fp = fopen(FILE_NAME_HOSPITAL, "r+");
    char bufferAux[256] = "";

    if (fp != NULL) { // check if file exists

        char buffer[256];

        while (fgets(buffer, 256 - 1, fp)) //read line by line 
        {
            if ((strstr(buffer, toLower(hospital)) == NULL)) {

                strcat(bufferAux, buffer);
            }
            else flag = true;
        }

        fclose(fp);

        FILE* novo;
        novo = fopen(FILE_NAME_HOSPITAL, "w");

        if (bufferAux != NULL) {
            fprintf(novo, "%s", bufferAux);
        }

        fclose(novo);
    }
    else {

        flag = false;
    }

    return(flag);
}


