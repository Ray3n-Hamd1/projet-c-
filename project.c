#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include <sys/types.h>
ssize_t getline(char ** buffer, size_t * size,FILE * fp) {
    int c;
    char *cs = NULL;
	int buffsize = 8;
	
	if(*buffer != NULL){
		free(*buffer);
		*buffer = NULL;
	}

	int length = 0;
	cs = (char*) malloc(buffsize);
	while ((c = getc(fp)) != EOF) {
		if(c == '\r') continue;
		
		if(++length+1 >= buffsize){
			buffsize *= 2;
			cs = (char *)realloc(cs, buffsize);
		}
			
		if ((*(cs + length - 1) = c) == '\n') {
			*(cs + length) = '\0';
			*buffer = cs;
			break;
		}
	}
	return (ssize_t)(*size = length);
}

ssize_t getdelim(char **restrict buffer, size_t *restrict size, int delim,
                FILE *restrict fp) {
    int c;
    char *cs = NULL;
	int buffsize = 8;
	
	if(*buffer != NULL){
		free(*buffer);
		*buffer = NULL;
	}

	int length = 0;
	cs = (char*) malloc(buffsize);
	while ((c = getc(fp)) != EOF) {
		if(c == '\r') continue;
		
		if(length+1 >= buffsize){
			buffsize *= 2;
			cs = (char *)realloc(cs, buffsize);
		}
		length++;
			
		if ((*(cs + length - 1) = c) == delim) {
			*(cs + length) = '\0';
			*buffer = cs;
			break;
		}
	}

	return (ssize_t)(*size = length);
}

typedef struct date
{ int day;
  int month;
  int year;
}date;

typedef struct Location {
    int id;
    date datestart;
    date datefinish;
    char details[200];
}Location;


typedef struct LocationNode{
    Location location;
    char details[200];
    struct LocationNode* Next;
}LocationNode;



typedef struct  Car
{ char plate[20];
  int state;
  int isloaned;
  LocationNode* history;
  char details[200];
}Car;

typedef struct CarNode{
    Car car;
    struct CarNode* next;

}CarNode;



CarNode *listecar= NULL;
LocationNode* inserQ(Location location,LocationNode* head){
    LocationNode* new= malloc(sizeof(LocationNode));
    new->location=location;
    new->Next=NULL;
    if (head==NULL){
        return(new);
    }
    LocationNode* cur=head;
    while (cur->Next!=NULL){
        cur=cur->Next;
    }
    cur->Next=new;
    return(head);
}

LocationNode* insertLocation(Location location,LocationNode* head){
    LocationNode* new= malloc(sizeof(LocationNode));
    new->location= location;
    strcpy(new->details,"");
    new->Next=head;
    return (new);
}
LocationNode* pop(LocationNode* head){
    LocationNode* cur = head;
    cur=head->Next;
    free(head);
    return(cur);
}


CarNode* insertCar(Car car, CarNode* head){
    CarNode* new= malloc(sizeof(CarNode));
    new->car = car;
    new->next= head;
    return(new);
}
CarNode* deleteCar(CarNode* head,char plate[]){
    CarNode* cur = head ;
    if (strcmp((head->car).plate,plate)==0){
        cur = head->next;
        free(head);
        return(cur);
    }
    CarNode* prev = NULL;
    while (cur != NULL ){
        Car carnow= cur->car ;
        if (strcmp(carnow.plate,plate)==0){
            prev->next = cur->next;
            free(cur);
            break;
        }
        prev = cur;
        cur = cur->next;
    }
    return(head);
}

void modifystate(char plate[],CarNode* liste){
     CarNode* cur= liste;
    while (cur!=NULL){
        Car carnow=cur->car;
        if(strcmp(carnow.plate,plate)==0){
            if(carnow.state==0){
                carnow.state=1;
            }
            else{
                carnow.state=0;
            }
            break;

		}
		cur=cur->next;
	}
}

void ModifyCar(char plate[],CarNode* liste,char details[]){
    CarNode* cur= liste;
    while (cur!=NULL){
        Car carnow=cur->car;
        if(strcmp(carnow.plate,plate)==0){
            strcpy(carnow.details,details);
            break;

		}
		cur=cur->next;
	}
}

void CancelRental(char plate[],CarNode*liste,char reason[200]){
     CarNode* cur= liste;
     while (cur!=NULL){
        Car carnow=cur->car;
        if(strcmp(carnow.plate,plate)==0){
             strcpy(carnow.details, "this rental is canceled for ");
             strcat(carnow.details, reason);
             carnow.isloaned= 0;
        }
        cur=cur->next;
        
    }
}

void CarDetails(char plate[], CarNode* liste){
    CarNode* cur= liste;
    while (cur!=NULL){
        Car carnow=cur->car;
        if(strcmp(carnow.plate,plate)==0){
            puts(carnow.details);
            if(carnow.state==0){
                if(carnow.isloaned==1){
                puts("the car is loaned");
                puts("the car is broken ");
                }
            else {
                puts("the car in not loaned");
                puts("the car is broken ");
                
            }
            }
            else { if(carnow.isloaned==1){
                puts("the car is loaned");
                puts("the car is not broken");
                }
            else {
                puts("the car in not loaned");
                puts("the car is not broken");
                }
            }

        break;   
		}
		cur=cur->next;
	}
}

void Locationprint(LocationNode* liste){
    LocationNode* cur= liste;
    while(cur!=NULL){
      Location locationnow=cur->location;
      printf("the id of the persone who loaned the: %d",locationnow.id);
      printf("the loan started on the %d/%d/%d", (locationnow.datestart).day,(locationnow.datestart).month,(locationnow.datestart).year);
      printf("the loan ended on the %d/%d/%d/",(locationnow.datefinish).day,(locationnow.datefinish).month,(locationnow.datefinish).year);
      cur=cur->Next;
    }
}
void HistoryCar(CarNode* liste){
    CarNode* cur = liste;
    while (cur!=NULL){
        Car carnow= cur->car;
        LocationNode* locationnow=carnow.history;
        printf("the car:");
        CarDetails(carnow.plate,liste);
        Locationprint(locationnow);
        cur=cur->next;
    }
}

void savecars(FILE* f ){
    CarNode* cur= listecar;
    while (cur!=NULL){
        Car carnow=cur->car;
        fprintf(f,"%s\n%d\n%d\n%s\n",carnow.plate,carnow.state,carnow.isloaned,carnow.details);
        LocationNode* listelocation=carnow.history;
        LocationNode* prev = listelocation;
        while(prev!=NULL){
            Location locationnow= prev->location;
            fprintf(f,"%d\n%d/%d/%d\n%d/%d/%d\n%s\n",locationnow.id,locationnow.datestart.day,locationnow.datestart.month,locationnow.datestart.year,locationnow.datefinish.day,locationnow.datefinish.month,locationnow.datefinish.year,prev->details);
            prev=prev->Next;
        }
        fprintf(f,"stop\n");
        cur=cur->next;
    }
}
void loadcars(FILE* f){
    char* plate=NULL;
    size_t size;
    while(getline(&plate,&size,f)!=0){
		plate[--size] = '\0';
        Car carnow;
		plate[size] = '\0';
        strncpy(carnow.plate,plate,20);
        char* state=NULL;
        getline(&state,&size,f);
        carnow.state=atoi(state);
        char* isloaned=NULL;
        getline(&isloaned,&size,f);
        carnow.isloaned=atoi(isloaned);
        char* details=NULL;
        getline(&details,&size,f);
		details[--size] = '\0';
        strncpy(carnow.details,details,200);
        char* line=NULL;
        carnow.history=NULL;
        while(getline(&line,&size,f)!=0){
            if (strcmp(line,"stop\n")==0){
                break;
            }
            Location locationnow;
            locationnow.id=atoi(line);
            char* dsd=NULL;
            getdelim(&dsd, &size,'/', f);
            dsd[size-1]='\0';
            locationnow.datestart.day=atoi(dsd);
            char* dsm=NULL;
            getdelim(&dsm, &size,'/', f);
            dsm[size-1]='\0';
            locationnow.datestart.month=atoi(dsm);
            char* dsy=NULL;
            getdelim(&dsy, &size,'\n', f);
            dsy[size-1]='\0';
            locationnow.datestart.year=atoi(dsy);
            char* dfd=NULL;
            getdelim(&dfd, &size,'/', f);
            dfd[size-1]='\0';
            locationnow.datefinish.day=atoi(dfd);
            char* dfm=NULL;
            getdelim(&dfm, &size,'/', f);
            dfm[size-1]='\0';
            locationnow.datefinish.month=atoi(dfm);
            char* dfy=NULL;
            getdelim(&dfy, &size,'\n', f);
            dfy[size-1]='\0';
            locationnow.datefinish.year=atoi(dfy);
            char* details = NULL;
            getline(&details,&size,f);
            details[--size]='\0';
            strncpy(locationnow.details,details,200);
            carnow.history=inserQ(locationnow,carnow.history);
            }
         listecar=insertCar(carnow,listecar);
         }
     }
CarNode* loancar(int id,char plate[],date datestart,date datefinish,CarNode* liste){
    CarNode* cur = liste;
    while(cur!=NULL){
        if(strcmp(cur->car.plate,plate)==0){
            Location location;
            (location).id=id;
            (location).datestart=datestart;
            (location).datefinish=datefinish;
            cur->car.history=insertLocation(location,cur->car.history);
            cur->car.isloaned=1;
            
            break;
        }
      cur=cur->next;  
    }
    return(liste);
}
CarNode* AddCar(char plate[],char details[],CarNode* liste){
    Car carnow;
    strcpy(carnow.plate,plate);
    strcpy(carnow.details,details);
    carnow.isloaned=0;
    carnow.state=1;
    carnow.history=NULL;
    return insertCar(carnow,liste) ;
    
}
void readString(char* buff, size_t size){
	int s = read(0, buff, size);
	if(s < 0) return;
	
	buff[s-1] = '\0';
}
int readInt(){
	char buff[200];
	readString(buff, 199);
	return atoi(buff);
}

int main(){
    int y;
    FILE* f;
    f=fopen("carlocation.txt","r");
    loadcars(f);
    fclose(f);
    char plate[20];
    int id=000;
    int n=7;
    while(n!=0){
    printf("welcome to car renting agency how can i help you: (press)\n 1- rent a car \n2-see the details about a car \n3-delete a broken car\n4-update the state or the details of a vehicule\n5-show the history of locations\n6-cancel renting a car\n7-Add a car\n0-to exit ");
    n=readInt();
    switch(n)
    {
        case 1 :
                 printf("give me ur id :\n the plate of the car you want to rent:\n");
                 id=readInt();
                 readString(plate,19);
                 date datestart;
                 printf("the rental starts on day:\n month:\nyear:");
                 datestart.day=readInt();
                 datestart.month=readInt();
                 datestart.year=readInt();
                 date datefinish;
                 printf("the rental ends on day:\n month:\nyear:");
                 datefinish.day=readInt();
                 datefinish.month=readInt();
                 datefinish.year=readInt();
                 listecar=loancar(id,plate,datestart,datefinish,listecar);
                 break;
        case 2 : 
                 printf(" the plate of the car you want to get its description:\n");
                 readString(plate,19);
                 CarDetails(plate,listecar);
                 break;
        case 3 :
                 printf(" the plate of the car you want to delete:\n");
                 readString(plate,19);
                 listecar=deleteCar(listecar,plate);
                 break;
        case 4 : printf(" the plate of the car you want to chage the details or the state:\n");
                 readString(plate,19);
                 printf("do you want to change:1-the state\n2-the details:");
                 int x; 
                 x=readInt();
                 if (x==2){
                 char details[200];
                 printf("the new details about the car:\n");
                 readString(details,199);
                 ModifyCar(plate,listecar,details);
                 }
                 else{modifystate(plate,listecar);
                 }
                 break;
        case 5 : HistoryCar(listecar);
                break;
        case 6 : printf(" the plate of the car you want to cancel renting:\n");
                 readString(plate,19);
                 char reason[200];
                 printf("can you please give me the reason why you cancelled the rental :");
                 readString(reason,199);
                 CancelRental(plate,listecar,reason);
                 break;
        case 7 : printf("givee me the plate and the description of the car you want to add");
                 char plate[20];
                 char details[200];
                 readString(plate,19);
                 readString(details,199);
                 listecar=AddCar(plate,details,listecar);
                 break;

    }
    }
    f=fopen("carlocation.txt","w");
    savecars(f);
    fclose(f);
    return 0;
}












