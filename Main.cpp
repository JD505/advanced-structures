#include "get_info.h"
#include "assign_hospital.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

void pause();
void title();
void addingPatt();
char* getString();
int getInt();
void insert();
bool checkHospital(char* name);
bool chekNameHospital(vagas* list_vagas, char hospitalName[]);

int main(void)

{
    int page = 0;
   
    
    while (true) {
        if (page==0 ||page == 1 || page == 2 || page == 3 || page == 4 || page == 5 || page == 6 || page == 7 || page == 8 ) {
            switch (page)
            {

            case 0: {

                title();
                printf(" Menu: \n");
                printf(" 1: Show patients \n");
                printf(" 2: Show Hospitals \n");
                printf(" 3: Add Patient \n");
                printf(" 4: Add Hospital \n");
                printf(" 5: Remove Patient \n");
                printf(" 6: Remove Hospital \n");
                printf(" 7: Assign surgeries\n");               
                printf(" 8: Exit \n ");

                insert();
                page = getInt();

            }break;
            case 1: {

                title();

                patient* pat = NULL;
                pat = readText(pat);

                listar_patient(pat);
                
                pause();
                page = 0;

            }break;

            case 2:
            {
                title();

                vagas* list_vagas = NULL;
                list_vagas = readVagas(list_vagas);

                listar_vagas(list_vagas);

                pause();
                page = 0;

            }break;

            case 3: {

                title();
                addingPatt();
                page = 0;

            }break;

            case 4:
            {
                title();

                char nameHospital[100]; char auxName[100];
                bool flag_check_Hospital = false;

                while (flag_check_Hospital == false) {

                    printf("Insert Hospital Name: ");
                    insert();

                    scanf("%s", &auxName);
                    flag_check_Hospital = checkHospital(auxName);

                    if (flag_check_Hospital == true)  strcpy(nameHospital, auxName);
                    else printf("\nHospital already assigned.\n");
                }

                int number;
                printf("Insert number of surgical vacancies: ");

                insert();
                number = getInt();

                addHospital(toLower(nameHospital), number);
                printf("Add other hospital? \n1-Yes \n0-No return to menu");
                insert();

                int temp = -1;
                temp = getInt();
                if (temp == 0) page = 0;

            }break;

            case 5:
            {
                title();
                patient* pat = NULL;
                pat = readText(pat);
                listar_patient(pat);

                int number = 0;
                printf("Insert the number of the patient to be removed: \n(-1 to return to menu)");
                insert();

                int temp = -2;
                temp = getInt();

                if (temp > -1) number = temp;
                else page = 0;

                removePatient(number);
            }break;

            case 6:
            {
                title();

                vagas* list_vagas = NULL;
                list_vagas = readVagas(list_vagas);
                listar_vagas(list_vagas);

                char name[100];
                printf("Insert the Hospital name to be removed: ");
                insert();
                
                scanf("%s", &name);
                
                if (removeHospital(name) == false) printf("Hospital Not found.");
                
                printf("\nRemove other hospital? \n1-Yes \n0-No");
                insert();

                int temp = -1;
                temp = getInt();
                if (temp == 0) page = 0;

            }break;
            
            case 7:
            {
                title();                               
              
                coloc* placed = NULL;
                patient* patt = NULL;

                patt = readText(patt);

                vagas* hospital = NULL;
                hospital = readVagas(hospital);

                if (numPatient(patt) == 0) {
                    printf("No patient available, please add a patient to assign surgeries.\n");
                }
                else if (numHospital(hospital) == 0) {
                    printf("No hospital or vacancies available, please add a Hospital to assign surgeries.\n");
                }
                else {
                    placed = select(patt, hospital);

                    FILE* file;
                    char hospitalName[30];
                    
                    coloc* notPlaced = NULL;
                    notPlaced = crescente(placed);

                    vagas* list_vagas = NULL;
                    list_vagas = readVagas(list_vagas);

                    listar_vagas(list_vagas);

                    printf("Insert the name of the Hospital to export assign patients: ");
                    insert();
                    scanf("%s", &hospitalName);

                    while (chekNameHospital(list_vagas, toLower(hospitalName)) == false) {

                        printf("Hospital not available. \nInsert the name of the Hospital to export assign patients: ");
                        scanf("%s", &hospitalName);
                    }                                       
                     
                    createFile(hospitalName);
                    printf("\nCreating file. \n");
                    printf("File : %s Created.\n", hospitalName);
                    colocados(placed, hospitalName);
                    naoColocados(notPlaced, hospitalName);                    

                }
                pause();

                page = 0;
            }break;

            case 8: {
                return 0;
            }break;                      
            }

        }else return 0;
        
    }
 
}
void pause() {
   
    printf("Press [Enter] to continue . . .");
    fflush(stdout);
    _getch();
   
}
void title() {
    system("cls");
    printf("***************************************** Hospital Management System ************************************\n\n");
    printf("                                          ---     Surgery       --- \n\n\n");

}
void insert() {
    printf("\n ->");
}
char* getString() {
    char buffer[256];

    while(true) {

        fgets(buffer, sizeof(buffer), stdin);
        if (strcmp(buffer, "\n") != NULL) break;           
    }
  
    char* s = getTextBetween(buffer, buffer, "\n", 0);      
    return(s);
}
int getInt() {
   
    int num;
    char* enter = NULL;

    while(true)
    {   
       char c;
       int a = scanf("%d", &num) ; 
       while ((c = getchar()) != '\n' && c != EOF); // to flush stdin
      
        if (a==1) return(num);
        else {
            num = NULL;
            printf("Please insert a number.");            
        }
       
    }          
}
int num_check(int num) {
    patient* pat = NULL;
    pat = readText(pat);

    while (pat != NULL) {
        if (num == pat->number) return (-1);

        pat = pat->seguinte;
    }
    return(num);
}
void addingPatt() {    
    bool flag = false;
    patient* patt = (patient*)malloc(sizeof(patient));
    
    if (patt != NULL) {
       
        while (flag == false) {
            
            printf("Insert patient name: \n");
            char* st = toLower(getString());
            
            if ( st != NULL) {
                flag = true;
                patt->name = st;
            }
        } 
       
        flag = false;
        while (flag == false) {

            printf("Insert patient number: \n");

            int num = NULL;
            num = getInt();
           
            if (num_check(num) != -1) {
                flag = true;
                patt->number = num;

            }else printf("This number is already assigned. \n");
            
        }
            
        fflush(stdin);
        
        printf("Insert Hospital name (preference 1): \n");
        patt->pref1 = toLower(getString());
        fflush(stdin);

        printf("Insert distance to preference 1: \n");
        patt->dist_pref1 = getInt();
        fflush(stdin);

        int temp = -1;
        printf("Add another preference?\n1-Yes\n0-NO\n ");
        temp = getInt();
        fflush(stdin);

        if (temp == 1) {
                    
            flag = false;
            while (flag == false) {

                printf("Insert Hospital name (preference 2): \n");
              
                char* str=toLower(getString());            
                
                if (strcmp(str,patt->pref1)!=0 && str !=NULL) {
                    flag = true;
                    patt->pref2 = str;                    
                }
                else printf("This preference is already assigned. \n");

            }

            printf("Insert distance to preference 2: \n");
            patt->dist_pref2 = getInt();
            fflush(stdin);

            temp = -1;
            printf("Add another preference?\n1-Yes\n0-NO\n ");
            temp= getInt();
            fflush(stdin);

            if (temp == 1) {

                flag = false;
                while (flag == false) {

                    printf("Insert Hospital name (preference 3): \n");

                    fflush(stdin);
                    char* str = toLower(getString());

                    if ((strcmp(str,patt->pref1)!=0) && (strcmp(str,patt->pref2)!=0)) {
                        flag = true;
                        patt->pref3 = str;
                    }
                    else {
                        printf("This preference is already assigned. \n");
                        str = NULL;
                    }
                }

                printf("Insert distance to preference 3: \n");
                patt->dist_pref3 = getInt();
                fflush(stdin);

                temp = -1;
                printf("Add another preference?\n1-Yes\n0-NO\n ");
                temp= getInt();
                fflush(stdin);

                if (temp == 1) {

                    flag = false;
                    while (flag == false) {

                        printf("Insert Hospital name (preference 4): \n");

                        char* str = toLower(getString());

                        if ((strcmp(str, patt->pref1) != 0) && (strcmp(str, patt->pref2) != 0) && (strcmp(str, patt->pref3) != 0))  {
                            flag = true;
                            patt->pref4 = str;
                        }
                        else printf("This preference is already assigned. \n");

                    }

                    printf("Insert distance to preference 4: \n");
                    patt->dist_pref4= getInt();
                    fflush(stdin);

                    temp = -1;
                    printf("Add another preference?\n1-Yes\n0-NO\n ");
                    temp = getInt();
                    fflush(stdin);

                    if (temp == 1) {

                        flag = false;
                        while (flag == false) {

                            printf("Insert Hospital name (preference 5): \n");

                            char* str = toLower(getString());

                            if (strcmp(str, patt->pref1) != 0 && (strcmp(str, patt->pref2) != 0) && (strcmp(str, patt->pref3) != 0) &&  (strcmp(str,patt->pref4)!=0)) {
                                flag = true;
                                patt->pref5 = str;
                            }
                            else printf("This preference is already assigned. \n");

                        }

                        printf("Insert distance to preference 5: \n");                       
                        patt->dist_pref5= getInt();
                        fflush(stdin);

                        addPatient(patt);
                    }
                    else {
                        
                        patt->pref5 = NULL;                       
                        patt->dist_pref5 = NULL;
                        addPatient(patt);
                    }
                }
                else {                   
                    
                    patt->pref4 = NULL;
                    patt->pref5 = NULL;
                 
                    patt->dist_pref4 = NULL;
                    patt->dist_pref5 = NULL;
                    addPatient(patt);
                } 
            }
            else {                
                
                patt->pref3 = NULL;
                patt->pref4 = NULL;
                patt->pref5 = NULL;
  
                patt->dist_pref3 = NULL;
                patt->dist_pref4 = NULL;
                patt->dist_pref5 = NULL;
                addPatient(patt);
            }
        }
        else {
            
            patt->pref2 = NULL;
            patt->pref3 = NULL;
            patt->pref4 = NULL;
            patt->pref5 = NULL;
           
            patt->dist_pref2 = NULL;
            patt->dist_pref3 = NULL;
            patt->dist_pref4 = NULL;
            patt->dist_pref5 = NULL;
                      
            addPatient(patt);
        }
            

    }
    else printf("Error, is not possible to insert a new patient.\n");
}
bool checkHospital(char* name) {

    vagas* listH = NULL;       
    listH = readVagas(listH);

    while (listH != NULL) {       
        if (strcmp(listH->nameHospital,(toLower(name)))==0) return false;
        
        listH = listH->seguinte;
    }
    return true;

}
bool chekNameHospital(vagas* list_vagas,char hospitalName[]) {
    
    while (list_vagas != NULL) {
        if (strcmp(hospitalName, list_vagas->nameHospital) == 0) {
            return(true);
        }
        list_vagas = list_vagas->seguinte;
    }
    return(false);
}
