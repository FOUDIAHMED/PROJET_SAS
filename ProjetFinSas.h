#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

typedef struct{
    int id;
    char titre[20];
    char description[100];
    char statut[20];
    time_t deadline;
}tache;
struct noeud{
	tache Task;
	struct noeud* filsG;
	struct noeud* filsD;
};
typedef struct noeud noeud,*arbreB;

struct tm saisirDeadline() {
    struct tm deadline = {0};
	time_t dead;
	int differenceInDays;
    do{
    	printf("Enter year: ");
    	scanf("%d", &(deadline.tm_year));
		
	}while(deadline.tm_year<2023);
    deadline.tm_year-=1900;
	do{printf("Enter month (1-12): ");
    scanf("%d", &(deadline.tm_mon));
   
	}while(deadline.tm_mon<0 ||deadline.tm_mon>12);
     deadline.tm_mon-=1;
   do{printf("Enter day (1-31): ");
    scanf("%d", &(deadline.tm_mday));
   } while(deadline.tm_mday<0 || deadline.tm_mday>30);

    return deadline;
}


void afficherTache(tache t){
    printf("\nl identifiant est :%d",t.id);
    printf("\ndescription:%s",t.description);
    printf("\ntitre:%s",t.titre);
    printf("\nstatut:%s",t.statut);
    char deadlineStr[20];
	size_t result = strftime(deadlineStr, sizeof(deadlineStr), "%d/%m/%Y %H:%M:%S", localtime(&t.deadline));
	if (result != 0) {
	    printf("\ndeadline:%s", deadlineStr);
	} else {
	    printf("\nFailed to format deadline.\n");
	}
}
void stockArbreToFile(FILE* f,arbreB a){
	if(a!=NULL){
		stockArbreToFile(f,a->filsG);
		char formattedDeadline[20];  
    
    	strftime(formattedDeadline, sizeof(formattedDeadline), "%Y/%m/%d", localtime(&a->Task.deadline));
		fprintf(f,"%d %s %s %s %s\n", a->Task.id, a->Task.titre, a->Task.description,
            a->Task.statut, formattedDeadline);
        
        stockArbreToFile(f,a->filsD);
	}
}

int differenceInDays(tache t) {
    time_t currentTime = time(NULL); 
    double differenceInSeconds =(double)difftime(t.deadline, currentTime);

    int differenceInDays = (int)(differenceInSeconds / (60 * 60 * 24));

    return differenceInDays;
}

void afficher_moin_3day(arbreB a){
	if(a!=NULL){
		if(differenceInDays(a->Task)<=3){
    		afficherTache(a->Task);
		}
		afficher_moin_3day(a->filsG);
		afficher_moin_3day(a->filsD);
	}
}

tache creerTache(){
    tache t;
    struct tm Deadline;
    printf("\ntu peu saisir l identifiant:");
    scanf("%d",&t.id);
    printf("\ntu peu saisir le titre:");
    scanf("%s",t.titre);
    printf("\ntu peut saisir la description:");
    scanf("%s",t.description);
    printf("\ntu peut saisir le statut:");
	
    int x;
    do{
    	printf("\nil y a trois chois de statut tu peut choisir le nombre de quelque statut entre 1 et 2 et 3\n1:todo \n2:doing\n3:done\n ");
    	scanf("%d",&x);
        if(x==1){
            strcpy(t.statut,"todo");
            break;
        }else if(x==2){
            strcpy(t.statut,"doing");
            break;
        }else if(x==3){
            strcpy(t.statut,"done");
            break;
        }
    }while(x < 1 || x > 3);
	Deadline=saisirDeadline();
    t.deadline=mktime(&Deadline);
    return t;
}

arbreB creerNoeud(tache t){
	arbreB a=(noeud*)malloc(sizeof(noeud));
	a->Task=t;
	a->filsG=NULL;
	a->filsD=NULL;
	return a;
}


int nbnoeud(arbreB a){
	if(a==NULL)
		return 0;
	return 1+nbnoeud(a->filsG)+nbnoeud(a->filsD);
}
arbreB AjoutTacheABR(arbreB a,tache t)
{
	if(a==NULL)
	   return creerNoeud(t);
	else if(a->Task.id > t.id)
	   a->filsG=AjoutTacheABR(a->filsG,t);
	else if(a->Task.id<t.id)
	   a->filsD=AjoutTacheABR(a->filsD,t);
	
return a;
}

void rechercherId(arbreB a,int id){
	if(a!=NULL){
		if(a->Task.id==id){
			afficherTache(a->Task);
		}
		if(a->Task.id>id){
			rechercherId(a->filsG,id);
		}else{
			rechercherId(a->filsD,id);
		}
	}
}

void rechercherTit(arbreB a,char tit[]){
	if(a!=NULL){
		if(strcmp(a->Task.titre,tit)==0){
			afficherTache(a->Task);
		}
		rechercherTit(a->filsG,tit);
		rechercherTit(a->filsD,tit);
	}
}

void copierTab(arbreB a,tache* tab,int* i){
	if(a!=NULL){
		copierTab(a->filsG,tab,i);
		tab[*i]=a->Task;
		(*i)++;
		copierTab(a->filsD,tab,i);
	}
}

arbreB AjoutTacheDeadline(arbreB a,tache t)
{
	if(a==NULL)
	   return creerNoeud(t);
	else if(a->Task.deadline > t.deadline)
	   a->filsG=AjoutTacheDeadline(a->filsG,t);
	else 
	   a->filsD=AjoutTacheDeadline(a->filsD,t);
	
return a;
}
void afficherArbre(arbreB a){
	if(a!=NULL){
		afficherArbre(a->filsG);
		afficherTache(a->Task);
		afficherArbre(a->filsD);
	}
}

void trieParDeadline(arbreB a){
	arbreB b=NULL;
	tache* tab=malloc(nbnoeud(a)*sizeof(tache));
	int i,n;
	copierTab(a,tab,&n);
	for(i=0;i<n;i++)
		b=AjoutTacheDeadline(b,tab[i]);
	afficherArbre(b);
	
}


arbreB AjoutTacheTitre(arbreB a,tache t)
{
	if(a==NULL)
	   return creerNoeud(t);
	else if(strcmp(a->Task.titre,t.titre)>=0)
	   a->filsG=AjoutTacheTitre(a->filsG,t);
	else 
	   a->filsD=AjoutTacheTitre(a->filsD,t);
	
return a;
}
void trieParTitre(arbreB a){
	arbreB b=NULL;
	tache* tab=malloc(nbnoeud(a)*sizeof(tache));
	int i,n;
	copierTab(a,tab,&n);
	for(i=0;i<n;i++)
		b=AjoutTacheTitre(b,tab[i]);
	afficherArbre(b);
}
arbreB ajoutPlusieurTaches(arbreB a,int nombreTaches){
	int i;
	tache t;
	for(i=0;i<nombreTaches;i++){
		t=creerTache();
		a=AjoutTacheABR(a,t);
	}
	return a;	
}
arbreB MaxArbreRech(arbreB a)
{
if(a->filsD == NULL)
	return a;
return MaxArbreRech(a->filsD);
}
arbreB supprimerRacine(arbreB a)
{
	arbreB tmp;
	arbreB supprimerElt(int v, arbreB a);
	if(a->filsG == NULL)
		return a->filsD;
	if(a->filsD == NULL)
		return a->filsG;
	tmp = MaxArbreRech(a->filsG);
	a->Task= tmp->Task;
	a->filsG = supprimerElt(tmp->Task.id, a->filsG);
return a;
}

arbreB supprimerElt(int identifiant, arbreB a)
{
	if(a== NULL)
		return a;
	if(identifiant == a->Task.id)
		return supprimerRacine(a);
	if(identifiant < a->Task.id)
		a->filsG = supprimerElt(identifiant, a->filsG);
	else
		a->filsD = supprimerElt(identifiant, a->filsD);
	return a;
}

void modifierTacheDes(arbreB a,int id){
	if(a!=NULL){
		if(a->Task.id==id){
			printf("\ntu peut modifier la description : ");
			char desc[100];
			scanf("%s",desc);
			strcpy(a->Task.description,desc);
		}
		if(a->Task.id>id){
			modifierTacheDes(a->filsG,id);
		}
		if(a->Task.id<id){
			modifierTacheDes(a->filsD,id);
		}	
	}
}
void modifierTacheDeadline(arbreB a,int id){
	if(a!=NULL){
		if(a->Task.id==id){
			struct tm d=saisirDeadline();
			a->Task.deadline=mktime(&d);
		}
		if(a->Task.id>id){
			modifierTacheDeadline(a->filsG,id);
		}
		if(a->Task.id<id){
			modifierTacheDeadline(a->filsD,id);
		}	
	}
}
void modifierStat(arbreB a, int id) {
    if (a != NULL) {
        if (a->Task.id == id) {
            int x;
            do {
                printf("\nchoisir le statut que tu peux modifier : 1, 2 ou 3\n1: todo\n2: doing\n3: done\n");
                scanf("%d", &x);
                if (x == 1) {
                    strcpy(a->Task.statut, "todo");
                } else if (x == 2) {
                    strcpy(a->Task.statut, "doing");
                } else if (x == 3) {
                    strcpy(a->Task.statut, "done");
                }

            } while (x < 1 || x > 3);  // Corrected the condition here
        }
        if (a->Task.id > id) {
            modifierStat(a->filsG, id);
        }
        if (a->Task.id < id) {
            modifierStat(a->filsD, id);
        }
    }
}



int  nombreTacheIncomplet(arbreB a){
	if(a==NULL){
		return 0;
	}
	if(strcmp(a->Task.statut,"doing")==0||strcmp(a->Task.statut,"todo")==0)
		return 1+nombreTacheIncomplet(a->filsG)+nombreTacheIncomplet(a->filsD);
	return nombreTacheIncomplet(a->filsG)+nombreTacheIncomplet(a->filsD);
}

int  nombreTacheComplet(arbreB a){
	if(a==NULL){
		return 0;
	}
	if(strcmp(a->Task.statut,"done")==0)
		return 1+nombreTacheIncomplet(a->filsG)+nombreTacheIncomplet(a->filsD);
	return nombreTacheIncomplet(a->filsG)+nombreTacheIncomplet(a->filsD);
}

void nombreJourJusqDelai(arbreB a){
	if(a!=NULL){
		afficherTache(a->Task);
		printf("\nle nombre de jour restant au delai de cette tache est :%d\n",differenceInDays(a->Task));
		nombreJourJusqDelai(a->filsG);
		nombreJourJusqDelai(a->filsD);
		
	}
}
