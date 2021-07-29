#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <ctype.h>


typedef struct tr{ //Structure Train stores all the data related to train
  char dest[20];   //destination station of a particular train
  int count;      //stores the no. of NON_AC seats left in train
  char tr_name[40]; //stores train name
  char tr_no[20];   //stores train no.
  int cost;         //stores the cost per NON_AC seat
  int ac_cost;      //stores the cost per AC seat
  int ac_count;     //stores the no. of AC seats left in train
  char dep_time[20]; //stores the time of departure of train
  char arr_time[20];// stores the time of arrival of train
  int seat[216];    //indicates if a particular seat is booked or not
  /*if seat[i]=0->seat is not Booked
    if seat[i]=1-> seat is Booked
    we have fixed the total no. of seats in a train to be 216
    72->AC
    144->NON_AC*/
  struct tr *next; //stores the address to the next node
}train;

struct car{ //Structure car is used in print() function
  train *tr;//stores a header of a linklist of structure train
  int i;    //has been used to store the no. of nodes in the linklist headed by train*tr
};

typedef struct user //Structure user stores all details per user for a ticket
{
  char id[40];      //stores userid of user
  train *a;         //stores the address for that node of train which this user has booked
  char name[40];    //stores the name of user
  int pin;          //stores user pin
  char tr_no[20];   //stores the tr_no of the train user has booked
  int PNR;          //stores PNR of the ticket
  char status[10];  //stores status of ticket 'Cancelled' or 'Confirmed'
  int seatno;       //stores seat_no booked
  char coach[2];    //stores the coach booked
  /*we have 3 coaches: A1,B1 and B2
  A1->AC
  B1,B2->NON_AC*/
  struct user *next;//stores the address to the next node
}usr;
//MODULE  1----
usr * loaduserlist();
//loads on deatils of all users and tickets and returns the head pointer of the link list thus created
train * loadtrain();
//loads on details of all trains and returns the head pointer of the link list thus created
void readSeat(struct tr*);
//reads up the Seat.txt file to have record of all seats booked and all seats left
void bookTicket(struct tr *header,struct user *headus);
//searches the train by destination and books ticket for user as per user's interest.
int checkexistence(char *z, struct user *headus);
//checks if this user has booked a ticked previously or is a new user by userid
int checkexistence1(int z,struct user *add, struct user *headus);
//checks if the pin entered by the existing user is correct
bool allotSeat(struct user*,int w);
//allots the seat and coach to the user as per user's interest
int yourticket(usr *ab, int m);
//gathers up all the details at one place and prints it to ticket
void cancel(struct tr *header,struct user *headus);
//is used to cancel a confirmed ticket and print the refund amount
bool detailsVerified(struct user *p);
//verifies the details provided by the user

//MODULE 2-----
void enquiryMenu();
//prints the enquiry menu
int searchbyno(char *z);
//searches for a train by its no.
int searchbydest();
//searches for trains by destination
void ticketDetail(struct user* headus);
//prints the details of a ticket by PNR
struct car print(train * header,char*dest, int para, int nth);
//print function is a multipurpose function which can book train ticket, cancel ticket , return the structure of a ticket, returns count of trains available for a particular destination, print the no. of trains to a particular destination
void saveuserchanges(usr *headern);
//saves up all the user details back to files
void savetrainchanges(train* a);
//saves all the train details back to files
void saveseatchanges(struct tr*);
//saves up all the data to Seat.txt
char *strupp(char *z);
//this function is used to change a string to uppercase
char *choi;
int choice;
int main()
{
  struct tr *header;
  struct user *headus;
  header=loadtrain();
  readSeat(header);
  headus=loaduserlist();
  char str1[50];
        int i=0;
        system("clear");
        printf("\t\t\t              ────────────────────────────\n");
        printf("\t\t\t               Railway Reservation System\n");
        printf("\t\t\t              ────────────────────────────\n\n\n\n");
        printf("\t\t\t     ╔═══════════════════════════════════════════╗\n");
        printf("\t\t\t     ║                                           ║\n");
        printf("\t\t\t     ║          1. Seat Booking                  ║\n");
        printf("\t\t\t     ║                                           ║\n");
        printf("\t\t\t     ║          2. Seat Cancellation             ║\n");
        printf("\t\t\t     ║                                           ║\n");
        printf("\t\t\t     ║          3. Enquiry                       ║\n");
        printf("\t\t\t     ║                                           ║\n");
        printf("\t\t\t     ║          4. Ticket Detail                 ║\n");
        printf("\t\t\t     ║                                           ║\n");
        printf("\t\t\t     ║          5. Exit                          ║\n");
        printf("\t\t\t     ║                                           ║\n");
        printf("\t\t\t     ╚═══════════════════════════════════════════╝\n");
        printf("\n-:>\t");
        choi=(char*)malloc(10);
        scanf("%s",choi);
        choice=atoi(choi);
        printf("\n\n");
        switch (choice)
        {
        default:
                printf("Not a valid input, try again" );
                setvbuf(stdout, NULL, _IONBF, 0);
                while (i<3) {
                        sleep(1);
                        printf(".");
                        i++;
                }
                printf("\e[1;1H\e[2J");
                main();

        case 1: system("clear");
                bookTicket(header,headus); //a function of seatbooking;
                break;
        case 2: cancel(header,headus);//a function of seat Cancellation;
                break;
        case 3:
   	 printf("\e[1;1H\e[2J");
         repeat:
         enquiryMenu();
	switch(choice)
	{
	 default:
                printf("Not a valid input, try again" );
                setvbuf(stdout, NULL, _IONBF, 0);
                while (i<3) {
                        sleep(1);
                        printf(".");
                        i++;
                }
                printf("\e[1;1H\e[2J");
                enquiryMenu();
                break;

	case 1:                  printf("Please Enter Train No. : ");
                    scanf("%s",str1);
                    int v=  searchbyno(str1);
                    if(v==1)
                    {
                            printf("\n\nPress 1 to search again, any other input will be take you back to Main Menu\n\n->\t");
                            int choice;
                            char el[10];
                            scanf("%s", el);
                            choice=atoi(el);
                            if(choice==1)
                            {
                                    setvbuf(stdout, NULL, _IONBF, 0);
                                    printf("Loading Search Menu");
                                    int sec=0;
                                    while (sec<3) {
                                            sleep(1);
                                            printf(".");
                                            sec++;
                                    }
                                    printf("\n");
                                    system("clear");
                                    enquiryMenu();
                            }
                    } setvbuf(stdout, NULL, _IONBF, 0);
                    printf("Returning To Main Menu");
                    int sec=0;
                    setvbuf(stdout, NULL, _IONBF, 0);
                    while (sec<3) {
                            sleep(1);
                            printf(".");
                            sec++;
                    }
                    printf("\n");
                    system("clear");
                    main();
                    goto repeat;
                    break;

	case 2:          v=  searchbydest();
                  if(v==1)
                  {
            printf("\n\nPress 1 to search again, any other input will be take you back to Main Menu\n\n->\t");
            choice;
            char el[10];
            scanf("%s", el);
            choice=atoi(el);
            if(choice==1)
            {
                    setvbuf(stdout, NULL, _IONBF, 0);
                    printf("Loading Search Menu");
                    int sec=0;
                    while (sec<3) {
                            sleep(1);
                            printf(".");
                            sec++;
                    }
                    printf("\n");
                    system("clear");
                    enquiryMenu();
            }
    }
    setvbuf(stdout, NULL, _IONBF, 0);
    printf("Returning To Main Menu");
    sec=0;
    setvbuf(stdout, NULL, _IONBF, 0);
    while (sec<3) {
            sleep(1);
            printf(".");
            sec++;
    }
    printf("\n");
    system("clear");
    main();
    goto repeat;
    break;


        case 3: sec=0;
                setvbuf(stdout, NULL, _IONBF, 0);
                printf("Loading Railway Reservation Console");
                while (sec<3) {
                        sleep(1);
                        printf(".");
                        sec++;
                }
                system("clear");
                main();
                break;
        case 4: system("clear");
                exit(0);
                break;
	}
	break;
        case 4: ticketDetail(headus);break;//a function of Ticket Detail;

        break;
        case 5:printf("\e[1;1H\e[2J");
        exit(0);
        break;
        }
}
usr * loaduserlist()// function used to load all the database from the files in a linked list of train type
{
FILE *id, *pin, *pnr,*name;
FILE *st,*sn,*co,*tr;
id = fopen("username.txt", "r+");
pin  = fopen("pin.txt", "r+");
pnr = fopen("PNR.txt","r+");
name=fopen("Name.txt","r+");
st=fopen("Status.txt","r+");
sn=fopen("Seatno.txt","r+");
co=fopen("Coach.txt","r+");
tr =fopen("TrainNoBooked.txt","r+");
usr *header, *trans, *loader;
header = (usr*)malloc(sizeof(usr));
int cnt;
for(trans = header, cnt =0;;trans = trans->next )//accessing linked list
{
  loader = (usr*)malloc(sizeof(usr));
  if(loader == NULL)// if memory allocation is not possible
  {
    printf("data not available");
    exit(0);
  }
  if(fgets(loader->id,40,id) == NULL) //checks if the file is finished or not
  {
    break;
  }
  if(loader->id[strcspn(loader->id, "\n")+1] == '\n') // if there  is a double \n in end then it will make last \n = \0
  loader->id[strcspn(loader->id, "\n")+1] = '\0';
  fgets(loader->name,40,name); //pickes up a line from file handled by 'name'
  fscanf(pin,"%d\n", &loader->pin); //pickes up a line from file handled by 'pin'
  fscanf(pnr,"%d\n",&loader->PNR); //pickes up a line from file handled by 'pnr'
  fgets(loader->status,11,st); //pickes up a line from file handled by 'st'
  loader->status[strcspn(loader->status,"\n")]='\0';// trims \n from end
  fscanf(sn,"%d\n",&loader->seatno);//pickes up a line from file handled by 'sn'
  fgets(loader->coach,4,co);//pickes up a line from file handled by 'co'
  loader->coach[strcspn(loader->coach,"\n")]='\0';
  fgets(loader->tr_no,20,tr);//pickes up a line from file handled by 'tr'
  loader->next = NULL;
  trans->next = loader; //connects loader to linked list node
  cnt++;
}
if(cnt==0) header->next=NULL;
fclose(id);//closing file handlers
fclose(pin);
fclose(pnr);
fclose(st);
fclose(sn);
fclose(co);
fclose(tr);
fclose(name);
return header;
}
int checkexistence(char *z, struct user *headus) // checks if userid passed by '*z' matches with id in any node of 'headus' header linked list
{
	if(headus->next==NULL) return 0;
  usr *trans;
  for(trans = headus->next;trans!=NULL;trans = trans->next)//accessing linked list
  {
    if (!strcmp(trans->id,z)) return 1;//checks userid == to id member in usr structure
    else continue;
  }
return 0;
}
int checkexistence1(int z,struct user *add, struct user *headus) // pin entered by the user is passed by z and userid entered is passed by *add, whereas headus passes the header of complete linked list of user details
{
	if (headus->next==NULL) return 0;
  usr *trans;
  for(trans = headus->next;trans!=NULL;trans = trans->next)
  {
    if (trans->pin == z&&(strcmp(add->id,trans->id)==0))//checks if pin entered by a user matches the pin in linked list and userid entered matches the corresponding id in linked list
    {
      strcpy(add->name,trans->name); // if id and pin matches then we will copy the corresponding name from the file.
      return 1;
    }
    else continue;
  }
return 0;
}
void savetrainchanges(train* a)
{
train  *temp; int cont;
FILE *train_dest, *train_count, *train_tr_name, *train_tr_no, *train_cost;
FILE *train_dep_time,*train_arr_time,*train_ac_cost,*train_ac_count;
train_dest = fopen("Traindes1.txt", "w+");// opening file handlers from given files
train_count = fopen("Seatcount1.txt", "w+");
train_tr_no = fopen("Trainno1.txt", "w+");
train_tr_name = fopen("Trainname1.txt", "w+");
train_cost = fopen("Seatcost1.txt", "w+");
train_dep_time = fopen("Deptime1.txt", "w+");
train_arr_time = fopen("Arrtime1.txt", "w+");
train_ac_count = fopen("AC_count1.txt", "w+");
train_ac_cost = fopen("AC_cost1.txt", "w+");
for(temp = a->next, cont=0;;temp = temp->next)// accessing linked list
{
  fputs(temp->dest,train_dest);// putting edited linked list members to files using file handlers one by one
  fputs(temp->tr_name,train_tr_name);
  fputs(temp->dep_time,train_dep_time);
  fputs(temp->arr_time,train_arr_time);
  fputs(temp->tr_no,train_tr_no);
  fprintf(train_cost,"%d\n", temp->cost);
  fprintf(train_count,"%d\n",temp->count);
  fprintf(train_ac_cost,"%d\n", temp->ac_cost);
  fprintf(train_ac_count,"%d\n", temp->ac_count);
  cont++; //keeping track of no. of nodes
  if(temp->next == NULL)
  {
    break;
  }
}
fclose(train_dest);//closing file handlers
fclose(train_count);
fclose(train_tr_no);
fclose(train_tr_name);
fclose(train_cost);
fclose(train_ac_cost);
fclose(train_ac_count);
fclose(train_dep_time);
fclose(train_arr_time);
saveseatchanges(a);//calling function
remove("Traindes.txt");//removing original files from which database was loaded initially
remove("Seatcount.txt");
remove("Trainno.txt");
remove("Trainname.txt");
remove("Seatcost.txt");
remove("Deptime.txt");
remove("Arrtime.txt");
remove("AC_count.txt");
remove("AC_cost.txt");
rename("Traindes1.txt", "Traindes.txt"); // now renaming all the new files to which edited linked list was dumped to the name of old files, so that we can again load trains from loadtrain()
rename("Seatcount1.txt", "Seatcount.txt");
rename("Trainno1.txt", "Trainno.txt");
rename("Trainname1.txt", "Trainname.txt");
rename("Seatcost1.txt", "Seatcost.txt");
rename("Deptime1.txt", "Deptime.txt");
rename("Arrtime1.txt", "Arrtime.txt");
rename("AC_count1.txt", "AC_count.txt");
rename("AC_cost1.txt", "AC_cost.txt");
}
struct car print(train * header,char*dest, int para, int nth)
{
  train *trans;//this is train pointer which is used as a temperory pointer for accessing linked list
  int cnt=1;
  struct car car_tr;
  for(trans = header->next;trans != NULL;trans = trans->next)//loop used for iteration
  {
    if(!strcmp(trans->dest,dest))//condition which checks if passed destination is same as the destination selected by
    {
      cnt++;//keeping track of count of trains in a particular destination
      if(para ==1)//if para passed is 1 then function will print the linked list where destination passed is same as destination in structure
		{
			printf("\n%d)   Train number:  %s     Train name:  %s     Train Source: DELHI\n     Train departure time:  %s     Train destination:  %s     Train Arrival time:  %s     Seats Available in NON-AC coach:  %d\n     Cost(in rupees) of NON-AC:  %d\n     Seats Available in AC coach:  %d\n     Cost(in rupees) of AC:  %d\n\n", cnt-1, trans->tr_no,trans->tr_name,trans->dep_time, trans->dest, trans->arr_time,  trans->count, trans->cost, trans->ac_count, trans->ac_cost);
		}
	  else if(para == 2)//if para passed is 2 then function will return the train details selected by user which is passed by nth
		{
			if(cnt-1 == nth)
			{
				car_tr.tr = trans;
				break;
			}
		}
	  else if(para == 3)// if para passed is 3 then function will return the train details with ac seat count reduced by 1 i.e. book the AC ticket for the particular selection(nth selection)
	  {
		if(cnt-1 == nth)
		{ trans->ac_count--;
		  car_tr.tr = trans;
		  break;
		}
	  }
	  else if(para == 4)//if para passed is 4 then function will return the train details with seat count reduced by 1 i.e. book the ticket for the particular selection(nth selection)
	  {
		if(cnt-1 == nth)
		{ trans->count--;
		  car_tr.tr = trans;
		  break;
		}
	  }
	  else if(para == 5)//if para passed is 5 then function will return the train details with ac seat count increased by 1 i.e. cancel the AC ticket for the particular selection(nth selection)
	  {
		if(cnt-1 == nth)
		{ trans->ac_count++;
		  car_tr.tr = trans;
		  break;
		}
	  }
	  else if(para == 6)//if para passed is 6 then function will return the train details with seat count increased by 1 i.e. cancel the ticket for the particular selection(nth selection)
	  {
		if(cnt-1 == nth)
		{ trans->count++;
		  car_tr.tr = trans;
		  break;
		}
	  }
	  else// if para passed is >6 or <1 then this else can be used to return only the no. of trains going to a particular destination as in every iteration 'cnt' is increasing
	  continue;
	}
	else
	continue;
  }
car_tr.i = cnt-1;
return car_tr; // returning the complete car structure
}
int yourticket(usr *ab, int m)
{
  FILE *Ticket;
  char z[] = ".txt",nam[40],trn[40];
  strcpy(nam,ab->id);
  strcpy(trn,ab->a->tr_no);
  nam[strcspn(nam, "\n")] = '\0';
  trn[strcspn(trn, "\n")] = '\0';
  strcat(nam,"_");
  strcat(trn,"_");
  strcat(nam,trn);
  char pnr[5];
  sprintf(pnr,"%d",ab->PNR);
  strcat(nam,pnr);
  strcat(nam,z);
  char loc[] = "Tickets/";
  strcpy(ab->tr_no,ab->a->tr_no);
  strcat(loc,nam);
  Ticket = fopen(loc,"w+");
  int l=0;
  fprintf(Ticket,"Name of Passanger: %s\n",ab->name);
  l=strlen(ab->coach);
  l=50-(l-2); //this ensures that the next entry on ticket is made after leaving space for 50 chars to give ticket a real looking format
  fprintf(Ticket,"Train booked: %s",ab->a->tr_name);
  for(int i=0;i<l;i++) putc(' ',Ticket);
  fprintf(Ticket,"Train number: %s",ab->a->tr_no);
  fprintf(Ticket,"Train departure time: %s", ab->a->dep_time);
  for(int i=0;i<l;i++) putc(' ',Ticket);
  fprintf(Ticket,"From: DELHI\n");
  fprintf(Ticket,"Train arrival time: %s",ab->a->arr_time);
  for(int i=0;i<l;i++) putc(' ',Ticket);
  fprintf(Ticket,"To  : %s",ab->a->dest);
  ab->coach[strcspn(ab->coach,"\n")]='\0';
  fprintf(Ticket,"Coach no. : %s\n",ab->coach);
  for(int i=0;i<l;i++) putc(' ',Ticket);
  fprintf(Ticket, "Seat no. booked :   %d\n",ab->seatno);
  fprintf(Ticket,"PNR:  %d\n",ab->PNR);
  fprintf(Ticket,"Status: %s\n",ab->status);
  if (m==1)
  {
    fprintf(Ticket,"Ticket cost: INR %d.00\n",ab->a->ac_cost);
  }
  else
  {
    fprintf(Ticket,"Ticket cost: INR %d.00\n",ab->a->cost);
  }
  fclose(Ticket);
  return 1;
}
void saveuserchanges(usr *headern)// works almost same to savetrainchanges //'headern' consists of the edited linked list of user details which can be used to dumpdata back to file. So that changes can be saved
{
  FILE *id, *pin, *pnr,*name;
  FILE *st,*sn,*co,*tr;
  id = fopen("username1.txt", "w+"); //opening file handlers
  pin  = fopen("pin1.txt", "w+");
  pnr = fopen("PNR1.txt", "w+");
  name=fopen("Name1.txt","w+");
  st=fopen("Status1.txt","w+");
  sn=fopen("Seatno1.txt","w+");
  co=fopen("Coach1.txt","w+");
  tr=fopen("TrainNoBooked1.txt","w+");
 usr *temp;
 for(temp = headern->next;temp != NULL;temp = temp->next)//accessing linked list
 {
   fputs(temp->id, id);// putting edited linked list members to files using file handlers one by one
   fputs(temp->name,name);
   fprintf(pin,"%d\n",temp->pin);
   fprintf(pnr,"%d\n", temp->PNR);
   fputs(temp->status,st);
   putc('\n',st);
   fputs(temp->tr_no,tr);
   fprintf(sn,"%d\n",temp->seatno);
   temp->coach[strcspn(temp->coach,"\n")]='\0';
   fputs(temp->coach,co);
   putc('\n',co);
 }
 fclose(id);//closing file handlers
 fclose(name);
 fclose(pin);
 fclose(pnr);
 fclose(st);
 fclose(sn);
 fclose(co);
 fclose(tr);
 remove("username.txt");//removing original files from which data was intially loaded
 remove("pin.txt");
 remove("PNR.txt");
 remove("Status.txt");
 remove("Seatno.txt");
 remove("Coach.txt");
 remove("TrainNoBooked.txt");
 rename("username1.txt","username.txt");// now renaming all the new files to which edited linked list was dumped to the name of old files, so that we can again use loaduserlist() function for loading database
 rename("pin1.txt","pin.txt");
 rename("PNR1.txt","PNR.txt");
 rename("Status1.txt","Status.txt");
 rename("Seatno1.txt","Seatno.txt");
 rename("Coach1.txt","Coach.txt");
 rename("Name1.txt","Name.txt");
 rename("TrainNoBooked1.txt","TrainNoBooked.txt");
}
void bookTicket(struct tr *header,struct user *headus)
{
  train  *trans, *header2, *trans2, *loader;
  char input[20];
  char *inpupp;
  char s[] = "Sorry, but no result found";
        printf("\t\t\t\t         ────────────────────────────\n");
        printf("\t\t\t\t          Railway Reservation System\n");
        printf("\t\t\t\t         ────────────────────────────\n\n");
        printf("\t\t\t\t\t         ────────────\n");
        printf("\t\t\t\t\t         Seat Booking\n");
        printf("\t\t\t\t\t         ────────────\n\n\n\n");
  printf("Hi user, please enter the required fields\n\n");
  setvbuf(stdout, NULL, _IONBF, 0);
  printf("Source Station:\t");
  char *source;
  source=(char*)malloc(30);
  scanf("%s",source);
  source=strupp(source);
  printf("Destination Station:\t");
  scanf("%s",input);
  setvbuf(stdout, NULL, _IONBF, 0);
  if(strcmp(source,"DELHI")!=0)
  {
    printf("No trains found, Please try again");
     int sec=0;
     setvbuf(stdout, NULL, _IONBF, 0);
                while (sec<3) {
                        sleep(1);
                        printf(".");
                        sec++;
                }
                printf("\n");
                system("clear");
        bookTicket(header,headus);
  }
  header2 = (train*)malloc(sizeof(train));
  for(trans = header->next, trans2 = header2;trans != NULL;trans = trans->next)
  // this for loop is helping us in making a linked list which contain the data for different destinations
  { inpupp = strupp(input);
    inpupp = strstr(trans->dest, inpupp);
    if(inpupp != NULL) // if input = mum then strupp
    // (input) = MUM and strstr will return common string from MUM and trans->dest
    // and then strlen willl count the no. of characters in string returned by
    // strstr in this case it is 3 (MUM)
    {
      if(strcmp(trans->dest, s)) //there is a constraint that all the destination should be written out together
      {
        strcpy(s, trans->dest);
        loader = (train*)malloc(sizeof(train));
        strcpy(loader->dest, trans->dest);
        loader->next = NULL;
        trans2->next = loader;
        trans2 = trans2 ->next;
      }
    }
  }
  int i = 1;int v=0;
  // this for loop is going to print the header2 linked list obtained above
  for(trans2 = header2->next;trans2 != NULL;trans2 = trans2->next,i++)
  {
    printf("\n%d. %s\n",i, trans2->dest);
    v++;
  }
  if(v==0)
  {
    printf("Sorry, No trains found, Please try again");
     int sec=0;
                while (sec<3) {
                        sleep(1);
                        printf(".");
                        sec++;
                }
                printf("\n");
                system("clear");
                bookTicket(header,headus);
  }
  int choice;
  printf("Please select a destination:\t");
  char el[10];
  scanf("%s", el);
  choice=atoi(el);
  if(choice<=i-1 && choice>0)
  {
  int cnt =0;
  for(trans2 = header2->next;cnt<choice-1;cnt++, trans2 = trans2->next);
  printf("\n\n%d trains are going from DELHI to %s",print(header,trans2->dest,0,0).i,trans2->dest);
  cnt = print(header,trans2->dest,1,0).i;
  //we are going to choose the nth element which of the linked list using a function
  train *choosedtrain;
  int trainchoosed;
  printf("\n\nPlease enter the serial no. of the train to proceed:\t");
  scanf("%s", el);
  trainchoosed=atoi(el);
  if(trainchoosed<=cnt && trainchoosed>0)
  {
  choosedtrain = print(header,trans2->dest,2,trainchoosed).tr;
  printf("\nYour choice:\n\nTrain number:  %sTrain name:  %sTrain destination:  %sTrain Arrival time:  %sTrain departure time:  %s",choosedtrain->tr_no,choosedtrain->tr_name, choosedtrain->dest, choosedtrain->arr_time, choosedtrain->dep_time);
  printf("\n1) AC  -  Cost:  %d \n2) NON-AC -  Cost:   %d\n",choosedtrain->ac_cost, choosedtrain->cost);
  int w;
  printf("\nPlease select type of coach:\t");
  scanf("%s", el);
  w=atoi(el);
  if(w==1 || w==2)
  {
  printf("\nPlease enter your UserId:\t");
  struct user add;
  setvbuf(stdin, NULL, _IONBF, 0);
  fgets(add.id,100,stdin);
  usr *temp; int check;
  if(headus->next!=NULL&&checkexistence(add.id,headus))//checkexistence checks if this userid is a new one or not
  {
    printf("\nPlease enter your PIN(4 digit only):\t");
    scanf("%d",&check);
    int re;
    re = checkexistence1(check,&add,headus);//checks if the pin entered matches the one in records
    if(re ==1)
    {
      printf("\nUser Verified\n");
      add.pin = check;
    }
    else if(re==0)
    {
      printf("\nSorry Invalid User\n");
      printf("You will have to try again\n");
      main();
    }
  }
  else
  {
    printf("\n─*─*─*─*─*─*─\n");
    printf("Hi New User!!\n");
    printf("─*─*─*─*─*─*─\n\n");
    printf("Please enter you full name:\n");
    setvbuf(stdin, NULL, _IONBF, 0);
    fgets(add.name,40,stdin);
    strcpy(add.name,strupp(add.name));
    printf("Please enter a new PIN(4 digit only):\t");
    scanf("%d",&add.pin);
  }
    add.a = choosedtrain;
    add.next = NULL;
    headus->PNR=0;
    for(temp = headus;temp->next!=NULL;temp = temp->next);
    add.PNR = temp->PNR+1;//incremental PNR
    temp->next = &add;
    if(allotSeat(&add,w))
    {
      strcpy(add.status,"Confirmed");
  if (w==1){
    choosedtrain = print(header,trans2->dest,3,trainchoosed).tr;
}
else if(w==2){
  choosedtrain = print(header,trans2->dest,4,trainchoosed).tr;
}
printf("\nTicket's Booked\n");
int ticketresponse;
ticketresponse = yourticket(&add,w);
if (ticketresponse ==1)
{
  printf("\nYour ticket is printed\nPlease check it in Tickets folder\n");
  printf("Please make sure you do not forget your userid and pin as these will be required if you ever want to cancel your ticket.\n");
  int sec=0;
  int timer=3;
  printf("\n\nGoing back to main menu in .");
  while (sec<3) {
          printf("%d",timer);
          printf(".");
          sleep(2);
          sec++;
          timer--;

  }
  saveuserchanges(headus);
  savetrainchanges(header);
  main();
}
}
  }
  else
  {
                printf("Invalid Option, Please try again");
                int sec=0;
                while (sec<3) {
                        sleep(1);
                        printf(".");
                        sec++;
                }
                printf("\n");
                system("clear");
                bookTicket(header,headus);
  }
  }
  else
  {
                printf("Invalid Option, Please try again");
                int sec=0;
                while (sec<3) {
                        sleep(1);
                        printf(".");
                        sec++;
                }
                printf("\n");
                system("clear");
                bookTicket(header,headus);
  }
  }
  else
  {
                printf("Invalid Option, Please try again");
                int sec=0;
                while (sec<3) {
                        sleep(1);
                        printf(".");
                        sec++;
                }
                printf("\n");
                system("clear");
                bookTicket(header,headus);
  }
}
bool detailsVerified(struct user *p)//checks the pin and useid enetered by the user
{
  char un[40];
  int pin;
  printf("Enter your userid: ");
  setvbuf(stdin, NULL, _IONBF, 0);
  fgets(un,40,stdin);
  printf("\n");
  printf("Enter your pin: ");
  scanf("%d",&pin);
  printf("\n");
  if((strcmp(un,p->id)==0)&&(pin==p->pin))
  {
    return true;
  }
  else
  {
    printf("Invalid credentials");
  }
  return false;
}
void cancel(struct tr *header,struct user *headus)
{
        printf("\t\t\t\t         ────────────────────────────\n");
        printf("\t\t\t\t          Railway Reservation System\n");
        printf("\t\t\t\t         ────────────────────────────\n\n");
        printf("\t\t\t\t\t         ─────────────────\n");
        printf("\t\t\t\t\t         Seat Cancellation\n");
        printf("\t\t\t\t\t         ─────────────────\n\n\n\n");
        printf("Enter the PNR of the ticket you want to cancel:\t");
        int pnr=0;
        scanf("%d",&pnr);
        bool found=false;
        struct user *current;
        current=headus->next;
        while(current!=NULL)
        {
          if(current->PNR==pnr)
          {
            found=true;
            break;
          }
          current=current->next;
        }
        if(found)
        {
          if(detailsVerified(current))
          {
	           int w=1;
	           float amtref=0.0F;
	           int i=current->seatno;
	           if(strcmp(current->coach,"B1")==0)
	           {
		             i=i+72;w=2;//because seats of B1 stars from 73
	           }
	           if(strcmp(current->coach,"B2")==0)
	            {
		              i=i+144;w=2;//because seats of B2 starts from 145
	            }
	             strcpy(current->status,"Cancelled");
	             struct tr *currenttr;
	             currenttr=header->next;
	             while(true)
	             {
		             if(strcmp(currenttr->tr_no,current->tr_no)==0) break;
		            currenttr=currenttr->next;
	             }
              if(currenttr->seat[i-1]==1) currenttr->seat[i-1]=0;
              else
              {
                printf("This ticket has already been camcelled \n");
                main();
              }
              if(w==2)
	            {
		              currenttr->count++;
		              amtref=0.5F*currenttr->cost;
	            }
	            if(w==1)
	            {
		              currenttr->ac_count++;
		              amtref=0.5F*currenttr->ac_cost;
	            }
              current->a=currenttr;
	            saveuserchanges(headus);
	            yourticket(current,w);
	            savetrainchanges(header);
	            printf("Ticket Cancelled Succesfully\n");
	            printf("Your Refund Amount: INR %.2f\n",amtref);
              printf("\n\nPress 1 to cancel another ticket, any other input will get you back to main screen\n\n->\t");
              char opt[10];
              scanf("%s",opt);
              int opot;
              opot=atoi(opt);
              if(opot==1)
              {
                      setvbuf(stdout, NULL, _IONBF, 0);
                      printf("Loading Cancel Ticekt console");
                      int sec=0;
                      while (sec<3) {
                              sleep(1);
                              printf(".");
                              sec++;
                      }
                      system("clear");
                      cancel(header,headus);
              }
              else
              {
                      int sec=0;
                      setvbuf(stdout, NULL, _IONBF, 0);
                      printf("Loading Railway Management System console");
                      while (sec<3) {
                              sleep(1);
                              printf(".");
                              sec++;
                      }
                      system("clear");
                      main();
              }
      }
}
else
{
      printf("This PNR doesn't exist.\n");
      printf("\n\nPress 1 to try again, any other input will get you back to main screen\n\n->\t");
      char opt[10];
      scanf("%s",opt);
      int opot;
      opot=atoi(opt);
      if(opot==1)
      {
              setvbuf(stdout, NULL, _IONBF, 0);
              printf("Loading Cancel Ticket console");
              int sec=0;
              while (sec<3) {
                      sleep(1);
                      printf(".");
                      sec++;
              }
              system("clear");
              cancel(header,headus);
      }
      else
      {
              int sec=0;
              setvbuf(stdout, NULL, _IONBF, 0);
              printf("Loading Railway Management System console");
              while (sec<3) {
                      sleep(1);
                      printf(".");
                      sec++;
              }
              system("clear");
              main();
      }
}
main();
}
bool allotSeat(struct user *t,int w)
{//w indicates AC or NON_AC 
/*In our matrix AC:A1=1 to 72
	    NON_AC:B1=73 to 144
	    NON_AC:B2=145 to 216*/
  printf("\n\nChoose the type of seat that you want:->\n\n");
  printf("1.Side Lower\n2.Lower\n");
  printf("3.Side Upper\n4.Upper\n");
  printf("5:Middle\n");
  char el[10];
  printf("\n\n-->\t");
  scanf("%s", el);
  setvbuf(stdin, NULL, _IONBF, 0);
  int s;
  s=atoi(el);
  if(s>5 || s<=0)
  {
    printf("Invalid Option, Please try again");
     int sec=0;
                while (sec<3) {
                        sleep(1);
                        printf(".");
                        sec++;
                }
                printf("\n");
                system("clear");
                main();
  }
  bool flag=false;
  switch(s)
  {
    case 1: s=7;break;//these are the actual seat numbers on train like SideLower=7 in AC 3 TIER of indian railways 
    case 2: s=1;break;
    case 3: s=8;break;
    case 4: s=3;break;
    case 5: s=2;break;
    default: printf(" Try again.\n");exit(0);break;
  }
  int i=(72*(w-1))+s;//after this i is the seat no. of first seat of user's interest
  if(w==1)
  {
    for(;i<=72;i+=8)
    {
      if(t->a->seat[i-1]==0)
      {
        t->a->seat[i-1]=1;//changing seat[i-1]=1 to book the seat if it was not previously booked
        flag=true;
        break;
      }
    }
    if(flag)
    {
      t->coach[0]='A';
      t->coach[1]='1';
      t->coach[2]='\0';
      t->seatno=i;
      return true;
    }
  }
  if(w==2)
  {
    for(;i<=216;i+=8)
    {
      if(t->a->seat[i-1]==0)
      {
        t->a->seat[i-1]=1;
        flag=true;
        break;
      }
    }
    if(flag)
    {
      if(i>72&&i<145)
      {
        i=i-72;
        t->coach[0]='B';
        t->coach[1]='1';
        t->coach[2]='\0';
        t->seatno=i;
        return true;
      }
      if(i>144)
      {
        i=i-144;
        t->coach[0]='B';
        t->coach[1]='2';
        t->coach[2]='\0';
        t->seatno=i;
        return true;
      }
    }
  }
    switch(s)
    {
      case 1: s=4;break; //this is used because lower seats are (1,9,17,...) and also (4,12,20,..)
      case 2: s=5;break;
      case 3: s=6;break;
      default: printf(" Try again.\n");exit(0);break;
    }
    i=(72*(w-1))+s;
    if(w==1)
    {
      for(;i<=72;i+=8)
      {
        if(t->a->seat[i-1]==0)
        {
          t->a->seat[i-1]=1;
          flag=true;
          break;
        }
      }
      if(flag)
      {
        t->coach[0]='A';
        t->coach[1]='1';
        t->coach[2]='\0';
        t->seatno=i;
        return true;
      }
    }
    if(w==2)
    {
      for(;i<=216;i+=8)
      {
        if(t->a->seat[i-1]==0)
        {
          t->a->seat[i-1]=1;
          flag=true;
          break;
        }
      }
      if(flag)
      {
        if(i>72&&i<145)
        {
          i=i-72;
          t->coach[0]='B';
          t->coach[1]='1';
          t->coach[2]='\0';
          t->seatno=i;
          return true;
        }
        if(i>144)
        {
          i=i-144;
          t->coach[0]='B';
          t->coach[1]='2';
          t->coach[2]='\0';
          t->seatno=i;
          return true;
        }
      }
    }
    return false;
}
void saveseatchanges(struct tr* head)
{
  FILE *fp;
  fp=fopen("Seat1.txt","w+");
  struct tr* current;
  current=head->next;
  while(current!=NULL)
  {
    for(int j=0;j<216;j++)
    {
      if(j!=215)
      {
        fprintf(fp,"%d ",current->seat[j]);
      }
      if(j==215)
      {
        fprintf(fp,"%d\n",current->seat[j]);
      }
    }
    current=current->next;
  }
  remove("Seat.txt");
  rename("Seat1.txt","Seat.txt");
  fclose(fp);
}
void readSeat(struct tr* head)
{
  FILE *fp;
  fp=fopen("Seat.txt","r");
  struct tr* current;
  current=head->next;
  while(current!=NULL)
  {
    for(int j=0;j<216;j++)
    {
      char ch[1];
      ch[0]=fgetc(fp);
      current->seat[j]=atoi(ch);
      ch[0]=fgetc(fp);
    }
    current=current->next;
  }
  fclose(fp);
}
void enquiryMenu()
{

         //a function of Enquiry;
        printf("\t\t\t              ────────────────────────────\n");
        printf("\t\t\t               Railway Reservation System\n");
        printf("\t\t\t              ────────────────────────────\n\n\n\n");
        printf("\t\t\t\t\t         ────────────\n");
        printf("\t\t\t\t\t         Train Search\n");
        printf("\t\t\t\t\t         ────────────\n\n\n\n");
        printf("\t\t\t     ╔═══════════════════════════════════════════╗\n");
        printf("\t\t\t     ║                                           ║\n");
        printf("\t\t\t     ║          1. Search By Train No.           ║\n");
        printf("\t\t\t     ║                                           ║\n");
        printf("\t\t\t     ║          2. Search By Destination         ║\n");
        printf("\t\t\t     ║                                           ║\n");
        printf("\t\t\t     ║          3. Return To Previous Menu       ║\n");
        printf("\t\t\t     ║                                           ║\n");
        printf("\t\t\t     ║          4. Exit                          ║\n");
        printf("\t\t\t     ║                                           ║\n");
        printf("\t\t\t     ╚═══════════════════════════════════════════╝\n");
        printf("\n-:>\t");
        scanf("%s",choi);
        choice=atoi(choi);
        if(choice<0 || choice >4)
        {
          setvbuf(stdout, NULL, _IONBF, 0);
          printf("Invalid Input,  PLease try again");
          int sec=0;
                        while (sec<3) {
                                sleep(1);
                                printf(".");
                                sec++;
                        }
                        printf("\n");
                        system("clear");
                        enquiryMenu();
        }

}
int searchbydest(){
train *header, *trans, *header2, *trans2, *loader;
  header = loadtrain();
  char input[20];
  char *source;
  source=(char*)malloc(30);
  char *inpupp;
  char s[] = "Sorry, but no result found";
  system("clear");
        printf("\t\t\t              ────────────────────────────\n");
        printf("\t\t\t               Railway Reservation System\n");
        printf("\t\t\t              ────────────────────────────\n\n\n\n");
        printf("\t\t\t     ╔═══════════════════════════════════════════╗\n");
        printf("\t\t\t     ║                                           ║\n");
        printf("\t\t\t     ║            HI USER                        ║\n");
        printf("\t\t\t     ║                                           ║\n");
        printf("\t\t\t     ║                                           ║\n");
        printf("\t\t\t     ╚═══════════════════════════════════════════╝\n");
        printf("\nSource-:>\t"); scanf("%s",source);
        printf("\nDestination-:>\t"); scanf("%s",input);
        source=strupp(source);
  // this for loop is helping us in making a linked list which contain the data for different destinations
  header2 = (train*)malloc(sizeof(train));

  for(trans = header->next, trans2 = header2;trans != NULL;trans = trans->next)
  { inpupp = strupp(input);

    inpupp = strstr(trans->dest, inpupp);

    if(inpupp != NULL) // if input = mum then strupp
    // (input) = MUM and strstr will return common string from MUM and trans->dest
    // and then strlen willl count the no. of characters in string returned by
    // strstr in this case it is 3 (MUM)
    {
      if(strcmp(trans->dest, s)) //there is a constraint that all the destination should be written out together
      {
        strcpy(s, trans->dest);
        loader = (train*)malloc(sizeof(train));
        strcpy(loader->dest, trans->dest);
        loader->next = NULL;
        trans2->next = loader;
        trans2 = trans2 ->next;
      }
    }
  }
int i = 1;
int j=0;
  // this for loop is going to print the header2 linked list obtained above
  if(strcmp(source,"DELHI")!=0)
  {
          printf("No trains found for such inputs\n\n");
          return 0;
  }
  for(trans2 = header2->next;trans2 != NULL;trans2 = trans2->next,i++)
  {
    printf("%d. %s",i, trans2->dest);
  }
  int choice;
  printf("\nPlease Select a Destination : ");
  scanf("%d", &choice);
  int cnt =0;
  for(trans2 = header2->next;cnt<choice-1;cnt++, trans2 = trans2->next);
  printf("\n\t\t\tHi '%d' no. of trains are going to  %s",print(header,trans2->dest,0,0).i,trans2->dest);
  cnt = print(header,trans2->dest,1,0).i;
  //we are going to choose the nth element which of the linked list using a function
return 1;
}
train * loadtrain()
{
FILE *train_dest, *train_count, *train_tr_name, *train_tr_no, *train_cost, *train_dep_time, *train_arr_time, *train_ac_cost, *train_ac_count;
train *header, *trans, *loader;
train_dest = fopen("Traindes.txt", "r+");//opening file handlers
train_count = fopen("Seatcount.txt", "r+");
train_tr_no = fopen("Trainno.txt", "r+");
train_tr_name = fopen("Trainname.txt", "r+");
train_cost = fopen("Seatcost.txt", "r+");
train_dep_time = fopen("Deptime.txt", "r+");
train_arr_time = fopen("Arrtime.txt", "r+");
train_ac_count = fopen("AC_count.txt", "r+");
train_ac_cost = fopen("AC_cost.txt", "r+");

header = (train*)malloc(sizeof(train));

for(trans = header;;trans = trans->next )//accessing the linked list
{
  loader = (train*)malloc(sizeof(train));
  if(loader == NULL) //exit program if memory is not available for alllocation
  {
    printf("data not available");
    exit(0);
  }
  if(fgets(loader->dest,19,train_dest) == NULL)//checks if a line points to something or not
  {
    break;
  }
  fgets(loader->tr_name,40,train_tr_name);//picks lines from files to a member of structure
  fgets(loader->dep_time,20,train_dep_time);
  fgets(loader->arr_time,20,train_arr_time);
  fgets(loader->tr_no,20,train_tr_no);
  fscanf(train_cost,"%d\n", &loader->cost);
  fscanf(train_count,"%d\n",&loader->count);
  fscanf(train_ac_cost,"%d\n", &loader->ac_cost);
  fscanf(train_ac_count,"%d\n", &loader->ac_count);
  loader->next = NULL;
  trans->next = loader;//connects the loader to the linked list thus adding a node each time
}
return header;
}
char *strupp(char *string)//function is used to change the string to uppercase
{
    for(int n=0;*(string+n)!='\0';n++)
    {
        *(string + n) = toupper(*(string+n));//one alphabet is changed to uppercase individually in each iteration
    }
    return string;
}
int searchbyno(char *z){  //this function print the train details by taking in train number as a string

		int num;
		if (strlen(z) != 5 )//this condition checks if the train no. is of 5 digits only
		{
			printf("\nPlease enter a valid train no of 5 digits- ");
			scanf("%s",z);
			return searchbyno(z);// calls the function again and again until user passes 5 digit string
		}
		num = atoi(z); //converting string to a number
		int iy;
        train *a;
        train *trans;
		a = loadtrain();//loading database
		int cnt=1; iy = 0;
		for(trans = a->next;trans != NULL;trans = trans->next)//accessing linked list
		 {
		   if(num == atoi(trans->tr_no))//checks if train no in linked list matches to the train no passed
		   { iy = 1;
			   cnt++;
			   printf("\n%d)   Train number:  %s     Train name:  %s     Train Source: DELHI\n     Train departure time:  %s     Train destination:  %s     Train Arrival time:  %s     Seats Available in NON-AC coach:  %d\n     Cost(in rupees) of NON-AC:  %d\n     Seats Available in AC coach:  %d\n     Cost(in rupees) of AC:  %d\n\n", cnt-1, trans->tr_no,trans->tr_name,trans->dep_time, trans->dest, trans->arr_time,  trans->count, trans->cost, trans->ac_count, trans->ac_cost);
			 return 1;
		   }
		 }
		 if(iy != 1)//tells that program was not able to enter the above if i.e. there are no train no. which matches the passed train number
		 {
		   printf("\nSorry but there's no train like that\n");
		   return 0;
		 }
	 }

void ticketDetail(struct user* headus)
{
  printf("Enter the PNR of the ticket.\n");
  int pnr=0;
  char p[5];
  setvbuf(stdin, NULL, _IONBF, 0);
  fgets(p,5,stdin);
  pnr=atoi(p);
  struct user* current;
  current=headus->next;
  bool found=false;
  while(current!=NULL)
  {
    if(current->PNR==pnr)
    {
      found=true;
      break;
    }
    current=current->next;
  }
  if(found)
  {
      printf("Status of the ticket: %s\n",current->status);
      printf(".\n.\n.\n");
      printf("Additional information can not be provided without id and pin");
      printf(" because of privacy issues of passengers.\n");
      printf("Do you want additional info?\n");
      printf("1.Yes\n2.No\n");
      int w;
      setvbuf(stdin, NULL, _IONBF, 0);
      fgets(p,5,stdin);
      w=atoi(p);
      if(w==1)
      {
        if(detailsVerified(current))
        {
          printf("Name      : %s",current->name);
          printf("Train No. : %s",current->tr_no);
          printf("Status    : %s\n",current->status);
          printf("Coach     : %s\n",current->coach);
          printf("Seat No.  : %d\n",current->seatno);
          printf("\n\nPress 1 to view another ticket details, any other input will get you back to main screen\n\n->\t");
          char opt[10];
          scanf("%s",opt);
          int opot;
          opot=atoi(opt);
          if(opot==1)
          {
                  setvbuf(stdout, NULL, _IONBF, 0);
                  printf("Loading Ticket Detail console\n");
                  int sec=0;
                  while (sec<3) {
                          sleep(1);
                          printf(".");
                          sec++;
                  }
                  system("clear");
                  ticketDetail(headus);
          }
          else
          {
                  int sec=0;
                  setvbuf(stdout, NULL, _IONBF, 0);
                  printf("Loading Railway Management System console\n");
                  while (sec<3) {
                          sleep(1);
                          printf(".");
                          sec++;
                  }
                  system("clear");
          main();
        }
        }
      }
      else if(w==2)
      {
        printf("Ok....Returning back to main menu..\n");
        int sec=0;
        while (sec<3) {
                sleep(1);
                printf(".");
                sec++;
        }
        main();
      }
      else
      {
        printf("Enter a valid option only 1 and 2 allowed.");
        int sec=0;
        while (sec<3) {
                sleep(1);
                printf(".");
                sec++;
        }
        ticketDetail(headus);
      }
  }
  else
  {
    printf("No such PNR exists.\nGoing back to main menu\n");
    int sec=0;
    setvbuf(stdout, NULL, _IONBF, 0);
                   while (sec<3) {
                           sleep(1);
                           printf(".");
                           sec++;
                   }
    main();
  }
}
