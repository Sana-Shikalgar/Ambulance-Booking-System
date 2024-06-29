#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include"graph.h"
#include"hash_p.h"
#include"hash_h.h"
#include"amb.h"

int main(){
	int choice = 0;
	char username[20], password[15];
	load_accounts();

	while(1){
		printf("Menu\n");
		printf("1. Emergency\n");
		printf("2. Log In\n");
		printf("3. Sign Up\n");
		printf("4. Exit\n");

		printf("Enter your choice: ");
		scanf("%d", &choice);

		switch(choice){
			case 1:
				emergency();
				break;
			
			case 2:
				printf("Enter username: ");
			        scanf("\n%[^\n]s", username);
        			printf("Enter password: ");
        			scanf("%s", password);

				if(login(username, password)){
					printf("Logged in successfully as %s.\n", username);
					after_login();
                		}                			
				else
					printf("Invalid username or password.\n");
				break;
			
			case 3:
				if(new_user()){
					printf("User account created successfully.\nWelcome to our services!\n");
					after_login();
				}
				break;
			
			case 4:
				break;
			
			default:
				printf("Oops! You have entered incorrect option!\nPlease try again.\n");
				break;
		}

		if(choice == 4)
			break;
		else{
			getchar();
			getchar();
			system("clear");
			continue;
		}
	}

	return 0;
}



/*int main(){	
	char loc[32];
	node* hosp = NULL;
	loc[0] = '\0';
	
	printf("Enter your location: ");
	scanf("%[^\n]s", loc);
	
	printf("%s\n", loc);

	hosp = search_hospital(loc);
	if(hosp){
                printf("The nearest hospital near you is: %s\n", hosp->name);
                printf("Number of available ambulances are %d\n", hosp->amb);
                printf("Would you like to proceed?\n");
                //scanf("%d", &choice);
        }
        
	return 0;
}*/
