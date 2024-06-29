#include<stdbool.h>
#define MAX_USERS 100
#define SIZE 3

//Structure to store user details
typedef struct User{
	char name[20];
	char password[20];
}User;

void load_accounts();
void save_account();
int new_user();
bool login(char *username, char *password);

void after_login();
void emergency();
void not_emergency();
void search_hospital(int *minDistances, node **nearestHospitals, char *name);
void book_ambulance(node* hosp, int dist);
void book_ambulance2(node* hosp, int dist,int* time);

