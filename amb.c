#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>
#include<time.h>
#include"hash_p.h"
#include"graph.h"
#include"hash_h.h"
#include"amb.h"
#define SIZE 3

//Global variables
User users[MAX_USERS];
int user_index = -1;
int user_count = 0;


//Save who all signed up and also logged in
//Save who all signed up and also logged in
void save_account(){
        FILE *file = fopen("user_accounts.txt", "a");
        if (file == NULL){
                printf("Error saving user accounts.\n");
                return;
        }

        for (int i = 0; i < MAX_USERS; i++){
                if (users[i].name){
                        fprintf(file, "%s\t", users[i].password);
                        fprintf(file, "%s\n", users[i].name);
                }
        }

        fclose(file);

        return; //User account history saved 
}

//Loads all info of all users from file
void load_accounts(){
        FILE *file = fopen("user_accounts.txt", "r");
        if (!file){
                //printf("No user accounts found. Creating a new file.\n");
                return;
        }

        int count = 0;

        while (fscanf(file, "%s\t%[^\n]", users[count].password, users[count].name) == 2){
                count++;
        }
        fclose(file);
}


//Check user name already exits in log in file. If yes, return the index it exists otherwise return -1
int find_index(char *username){
//       printf("%s\n", users[0].name);

        for (int i = 0; i < MAX_USERS; i++){
                if(!(users[i].name))
                        return -1;
                if(!(strcmp(users[i].name, username))){
                        //printf("%s\n", users[i].name);
                        return i;
                }
        }

        return -1;
}

//Add new user
int new_user(){
	User newUser;

    	printf("Enter new username: ");
    	scanf(" %[^\n]s", newUser.name);

    	int index = find_index(newUser.name);
    	if (index != -1){ //If the user name already exists
        	printf("Username already exists.\n");
        	return 0;
    	}

    	printf("Enter new password: ");
    	scanf(" %s", newUser.password);

    	for (int i = 0; i < MAX_USERS; i++){
        	if (strlen(users[i].name) == 0){
            		users[i] = newUser;
            		//printf("User account created successfully.\n");

            		// Append user signup information to the log file
            		FILE *signUpLog = fopen("signup_log.txt", "a");
            		if (!signUpLog){
                		printf("Error opening signup log file.\n");
                		return 0;
            		}
            		fprintf(signUpLog, "Username: %s\n", newUser.name);
            		fprintf(signUpLog, "Password: %s\n", newUser.password);
            		fprintf(signUpLog, "====================\n");
            		fclose(signUpLog);

            		save_account();
            		return 1;
        	}
    	}

    	printf("Maximum user account limit reached.\n");
	return 0;
}

//Log in function
bool login(char *username, char *password){
        int index = find_index(username);
        if (index != -1 && !(strcmp(users[index].password, password))){
                //printf("Logged in successfully as %s.\n", username);

                //Append user login information to the log file
                FILE *login_log = fopen("login_log.txt", "a");
                if (!(login_log)){
                        printf("Error opening login log file.\n");
                        return false;
                }
                fprintf(login_log, "Username: %s\n", username);
                fprintf(login_log, "====================\n");
                fclose(login_log);

                return true;
        }

        return false;
}

//To change the password
void changePassword()
{
    char username[50];
    char oldPassword[50];
    char newPassword[50];
    int userIndex;

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter old password: ");
    scanf("%s", oldPassword);

    userIndex = find_index(username);
    if (userIndex != -1 && strcmp(users[userIndex].password, oldPassword) == 0)
    {
        printf("Enter new password: ");
        scanf("%s", newPassword);
        strcpy(users[userIndex].password, newPassword);
        printf("Password changed successfully.\n");

        // Append user password change information to the log file
        FILE *passwordChangeLog = fopen("password_change_log.txt", "a");
        if (passwordChangeLog == NULL)
        {
            printf("Error opening password change log file.\n");
            return;
        }
        fprintf(passwordChangeLog, "Username: %s\n", username);
        fprintf(passwordChangeLog, "====================\n");
        fclose(passwordChangeLog);

        save_account();
    }
    else
    {
        printf("Invalid username or old password.\n");
    }
}

//To check if the mobile number is 10 digit
bool valid_mobile_number(char num[]){
	int l = strlen(num);
	
	if(l != 10) //If the length is not 10
		return false;

	for(int i = 0; i < l; i++){ //If all char are digits
		if(num[i] < '0' || num[i] > '9')
			return false;
	}

	return true;
}


//After Logging in
void after_login(){
	int op = 0;

	while (1){
		printf("\n=== User Menu ===\n");
                printf("1. Change password\n");
                printf("2. Book Ambulance\n");
                printf("3. Logout\n");

                printf("Enter your choice: ");
                scanf("%d", &op);

                switch (op){
                	case 1:
                        	changePassword();
                                break;
                        case 2:
                        	not_emergency();
                                break;
                        case 3:
                        	printf("Logged out.\n");
                                break;
                        default:
                        	printf("Invalid choice.\n");
                                break;
                }

                if (op == 3)
                	break;
                else{
                	getchar();
                        getchar();
                        system("clear");
			continue;
                }
	}

	return;
}


//Non Emergency 
void not_emergency(){
	//Declaration and memory allocation
	char *pick_up = (char *)malloc(sizeof(char) * 40);
	char *drop = (char *)malloc(sizeof(char) * 40);
	hash_p hp;
        graph g;
        hash_h h;
        node *hosp = NULL;
        int src, dest = -1;
        int dist = INT_MAX;

	//Initialiazation
        init_place(&hp, "locations.txt");
        init_graph(&g, "graph.txt");
        init_hosp(&h, "hospitals.txt");

	printf("Enter your pick up location: ");
        scanf("\n%[^\n]s", pick_up);
        src = find_source(hp, pick_up);
        if(src == -1){
                printf("Our services are yet to reach your area!\n");
		return;
	}
	
	printf("Enter the hospital: ");
        scanf("\n%[^\n]s", drop);
	hosp = find_dest(h, drop);
	if(!hosp){
		printf("Sorry! This hospital is still not registered with us.\n");
		return;
	}
        dest = hosp->ver;

	dist = dijkstra(g, src, dest);
	
	book_ambulance(hosp, dist);
	free(pick_up);
	free(drop);

        return;
}

//Emergency,will reach you in given time
void calculateTime(int *A,int distance) {
    double speed = 40.0;  
    double time = (double) distance / speed;

    int hours = (int) time;
    int minutes = (int) ((time - hours) * 60);
    A[0]= time;
    A[1]= minutes;
    return;

}

//Emergency
void emergency(){
	node* l1[3]; //Will store three nearest hospitals data
        int l2[3]; //Will store three nearest distance of resp hosp in l1
	int l3[3];		   //will store time
        node *hosp = NULL;
        int dist = INT_MAX;
	int op = -1;
	char *src = (char *)malloc(sizeof(char) * 40);

	src[0] = '\0';

        printf("Enter your location: ");
        scanf("\n%[^\n]s", src);

        search_hospital(l2, l1, src);
	if(!(l1[0]))
		return;

        printf("\nThe nearest hospitals are: \n");
        
	while(1){
		for(int i = 0; i < 3; i++){
			if((l1[i])){
                		printf("\n%d. %s. ", i+1, l1[i]->name);
				
				if(l2[i])
					printf("Distance from your location: %d km", l2[i]);
				else
					printf("You are already at location.");
			}
		}

        	printf("\nEnter which hospital would you prefer: ");
        	scanf("%d", &op);
		
		if(op <= 3 && op >=1)
			break;

		printf("Please enter correct option!\n");
	}

        hosp = l1[op-1];
        dist = l2[op-1];
	calculateTime(l3,dist);			//change here

        book_ambulance2(hosp, dist,l3);
	
	free(src);
	return;
}


//To find the nearest hospital
void search_hospital(int *minDistances,node **nearestHospitals,char *name){
        hash_p hp;
        graph g;
        hash_h h;
        node *p = NULL;
        int src, dest;
        int dist;
        int distances[SIZE]; // Array to store distances from the user's location to each hospital
        nearestHospitals[3]; // Array to store the three nearest hospitals
        minDistances[3];

        init_place(&hp, "locations.txt");
        init_graph(&g, "graph.txt");
        init_hosp(&h, "hospitals.txt");

        src = find_source(hp, name);
        if(src == -1){
                printf("Our services are yet to reach your area!\n");
        }
        // Initialize the arrays
    for (int i = 0; i < SIZE; i++) {
        distances[i] = INT_MAX;
        nearestHospitals[i] = NULL;
        minDistances[i] = INT_MAX;
    }
        for(int i = 0; i < SIZE; i++){
                if((h).head[i])
                        p = (h).head[i];
                else
                        p = NULL;

                while(p){
                        dest = p->ver;
                        dist = dijkstra(g, src, dest);
                        for (int j = 0; j < 3; j++) {
                                if (dist < minDistances[j]) {
                    // Shift the previous nearest hospitals to make space for the current one
                                        for (int k = 2; k > j; k--) {
                                                nearestHospitals[k] = nearestHospitals[k - 1];
                                                minDistances[k] = minDistances[k - 1];
                                        }
                                nearestHospitals[j] = p;
                                minDistances[j] = dist;
                            //    printf("%s",nearestHospitals[j]->name);
                                break;
                                }
                        }
                        p = p->next;
                }
        }


        return;
}

char *bookedTime(){
    struct tm* ptr;
    time_t t;
    t = time(NULL);
    ptr = localtime(&t);
    return asctime(ptr);
}

//Booking of Ambulance
void book_ambulance(node* hosp, int dist){
	char name[30];
	int age;
	char mobile_num[12];
	char loc[40];
	char timeB[10];
    	char dateB[10];
	
	if(hosp && hosp->amb){
		//Patient's name
		printf("Enter patient's name: ");
		scanf("\n%[^\n]s", name);

		//Patient's age
		printf("Enter patient's age: ");
		scanf("%d", &age);

		//Mobile number
		mobile_num[0] = '\0';
		while(!valid_mobile_number(mobile_num)){ //If the mobile number is less then 10
			printf("Enter mobile number: ");
			scanf("\n%s", mobile_num);

			if(valid_mobile_number(mobile_num))
				break;

			printf("Invaid mobile number!\n");
		}	

		//Pick up location
		printf("Enter pick up address: ");
		scanf("\n%[^\n]s", loc);

		printf("When do you want the ambulance to reach you?\n");
    		printf("Enter date in format \"dd-mm-yyyy\": ");
    		scanf(" %s",dateB);


    		printf("\nEnter time in format \"hh:mm pm/am\": ");
    		scanf(" %[^\n]s",timeB);

		char *Btime = bookedTime();
		// Generate and display receipt
	        printf("\n--- Receipt ---\n");
            	printf("Patient Name: %s\n", name);
            	printf("Patient Age: %d\n", age);
            	printf("Mobile Number: %s\n", mobile_num);
            	printf("Full Address: %s\n", loc);
            	printf("Hospital: %s\n", hosp->name);
		printf("Ambulance booked at: %s\n",Btime);
		printf("Ambulance booked for: %s , %s\n",timeB,dateB);
            	printf("---------------\n");

		printf("\nAMBULANCE BOOKED SUCCESSFULLY!\n");


            	// Append user ambulance booking information to the log file
            	FILE *fp = fopen("amb_logBook.txt", "a");
            	if (!fp){
                	printf("Error opening ambulance booking log file.\nPlease try again later\n");
                	return;
            	}

           	fprintf(fp, "Hospital: %s\n", hosp->name);
            	fprintf(fp, "Patient Name: %s\n", name);
            	fprintf(fp, "Patient Age: %d\n", age);
            	fprintf(fp, "Mobile Number: %s\n", mobile_num);
            	fprintf(fp, "Full Address of pick up: %s\n\n", loc);
		fprintf(fp, "Ambulance booked at: %s", Btime);
		
	}

	else
		printf("No ambulance available in this hospital!\nPlease try again\n");
		

	return;
}


//Booking of Ambulance
void book_ambulance2(node* hosp, int dist, int *time){
        char name[30];
        int age;
        char mobile_num[12];
        char loc[40];

        if(hosp && hosp->amb){
                //Patient's name
                printf("Enter patient's name: ");
                scanf("\n%[^\n]s", name);

                //Patient's age
                printf("Enter patient's age: ");
                scanf("%d", &age);

                //Mobile number
                mobile_num[0] = '\0';
                while(!valid_mobile_number(mobile_num)){ //If the mobile number is less then 10
                        printf("Enter mobile number: ");
                        scanf("\n%s", mobile_num);

                        if(valid_mobile_number(mobile_num))
                                break;

                        printf("Invaid mobile number!\n");
                }

                //Pick up location
                printf("Enter pick up address: ");
                scanf("\n%[^\n]s", loc);

		char *a = bookedTime();
                // Generate and display receipt
                printf("\n--- Receipt ---\n");
                printf("Patient Name: %s\n", name);
                printf("Patient Age: %d\n", age);
                printf("Mobile Number: %s\n", mobile_num);
                printf("Full Address: %s\n", loc);
                printf("Hospital: %s\n", hosp->name);
		printf("Ambulance booked at: %s",a);
                printf("---------------\n");

		printf("\nAMBULANCE BOOKED SUCCESSFULLY!\n");

		printf("will reach you in %d hour(s) %d minute(s)",time[0],time[1]);

                // Append user ambulance booking information to the log file
                FILE *fp = fopen("amb_logBook.txt", "a");
                if (!fp){
                        printf("Error opening ambulance booking log file.\nPlease try again later\n");
                        return;
                }

                fprintf(fp, "Hospital: %s\n", hosp->name);
                fprintf(fp, "Patient Name: %s\n", name);
                fprintf(fp, "Patient Age: %d\n", age);
                fprintf(fp, "Mobile Number: %s\n", mobile_num);
                fprintf(fp, "Full Address of pick up: %s\n\n", loc);

        }

        else
                printf("No ambulance available in this hospital!\nPlease try again\n");


        return;
}

