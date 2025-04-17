#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct admin {
    char code[20];
    char name[50];
    char time[10];
    char date[20];
    int cost;
    float rating;
    int numseats_R;
    int numseats_V;
    int numseats_P;
};

struct book{
	char mcode[20];
	char fullname[50];
	int seats;
	char type;
	char mobile[12];  //0322810058 mobile has 11 integers 
	int total_amt;
	int receiptno;
	char pay[10];
};

struct MemberDiscount {
    char level[10];
    float discounts[3][3]; // 2D array to store discounts for movie tickets, snacks, and drinks
}; 

struct member {
    char mem_id[10];
    char username[20];
    char password[20];
    char name[50];
    char email[50];
    char membershipType[10];
    char paymentType[10];
    int price;
};

#define ADMIN_ID "admin"
#define ADMIN_PASSWORD "admin123"

void insert_details(int n);
void deleteMovie();
void updateMovie();
void viewAll();
void eraseDataFile();
int movieCodeExists(char code[]);
void registerMember();
int validatePassword(char *password);
void displayMemberInfo(const char *username, const char *password);
int loginMember(const char *username, const char *password);
void book_ticket();
void updateSeats(char movie_code[], char seatType, int numSeatsBooked);
int ReceiptNum ();
void displayReceiptByReceiptNumber(int receiptNumber);
void cancelbooking();
void updateSeatscancel(char movie_code[], char seatType, int numSeatsBooked);
void initializeDiscounts(struct MemberDiscount **discounts);
void freeDiscounts(struct MemberDiscount *discounts);
void displayDiscounts(struct MemberDiscount *discounts, int size);
void memberbook_ticket(struct MemberDiscount *discounts, int discountSize,const char *username, const char *password);

int main() {
    int modech;
    char choice;
    struct MemberDiscount *discounts = NULL;
    do {
    	system("cls");
        printf("\n\t    =====================================================================================================");
    	printf("\n");
        printf("\t\t\t\t\t     WELCOME TO MOVIE TICKET BOOKING ");
        printf("\n");
        printf("\t    =====================================================================================================\n");
        printf("\n\n\t\t\t\t1. Administrator");
        printf("\n\t\t\t\t2. User");
        printf("\n\t\t\t\t3. Member");
        printf("\n\t\t\t\t0. Exit");
        printf("\n\n\t\t\t\t\tEnter mode: ");
        scanf("%d", &modech);

        if (modech == 1) {
            // Administrator mode
            system("cls");
            char enteredID[20], enteredPassword[20];
            char ch1;
            int z;
			printf("\t\t\t************************************************************************\n");
			printf("\t\t\t\t\t\tADMIN VERIFICATION\n");
			printf("\t\t\t************************************************************************\n");
            printf("\n\t\t\t\tEnter Administrator ID: ");
            scanf("%s", enteredID);

            printf("\t\t\t\tEnter Administrator Password: ");
            scanf("%s", enteredPassword);

            if (strcmp(enteredID, ADMIN_ID) == 0 && strcmp(enteredPassword, ADMIN_PASSWORD) == 0) {
                do {
                	system("cls");
                    printf("\nYou have logged in as administrator\n\n");
                    printf("\n\t    =====================================================================================================");
                    printf("\n");
                    printf("\t\t\t\t\t        MOVIE TICKET BOOKING ");
                    printf("\n");
                    printf("\t    =====================================================================================================\n");

                    printf("\n\t\t\tPress <1> Insert Movies (Admin Only)");
                    printf("\n\t\t\tPress <2> Update Movies (Admin Only)");
                    printf("\n\t\t\tPress <3> Delete Movies (Admin Only)");
                    printf("\n\t\t\tPress <4> Cancel Booking (Admin Only)");
                    printf("\n\t\t\tPress <5> Insert Discounts for Members (Admin Only)");
                    printf("\n\t\t\tPress <6> View All Movies Available (Admin Only)");
                    printf("\n\t\t\tPress <7> Delete Data files of movies and bookings (at end of the day)");
                    printf("\n\n\t\t\t\tEnter your choice: ");
                    scanf("%d", &z);
                    printf("\n");
                    switch (z) {
                        case 1:
                        	int n;
                        	system("cls");
                        	printf("Enter number of movies you want to insert: ");
                        	scanf("%d",&n);
                            insert_details(n);
                            break;
                        case 2:
                            updateMovie();
                            break;
                        case 3:
                            deleteMovie();
                            break;
                        case 4:
                            cancelbooking();
                            break;
                        case 5:
                            initializeDiscounts(&discounts);
                            break;
                        case 6:
                            viewAll();
                            break;
                        case 7:
                            eraseDataFile();
                            freeDiscounts(discounts);
                            break;
                        default:
                            printf("\nInvalid choice!");
                            break;
                    }
                    printf("\nDo you want to return to the main menu? (y/n): ");
                    scanf(" %c", &ch1);
                } while (ch1 == 'y');
            } else {
                printf("\nInvalid Administrator ID or Password. Access denied!");
            }
        } else if (modech == 2) {
            // User menu
            char ch2;
            int userChoice;
            do {
            	system("cls");
                printf("\n");
				printf("\n\t\t---------------------- WELCOME TO MIRRORED MEMORIES MOVIE HOUSE ----------------------");
                printf("\n\n\n");

                printf("\n\t\t\tPress <1> View All Movies Available");
                printf("\n\t\t\tPress <2> Book Ticket");
                printf("\n\t\t\tPress <3> Reservation Info(Receipt)");
                printf("\n\t\t\tPress <4> Cancel Booking");
                printf("\n\t\t\tPress <5> Apply for Membership");

                printf("\n\n\t\t\t\tEnter your Choice: ");
                scanf("%d", &userChoice);

                switch (userChoice) {
                    case 1:
                        viewAll();
                        break;
                    case 2:
                        book_ticket();
                        break;
                    case 3:
                    	system("cls");
                    	int receiptNumber;
                    	printf("Enter your RECEIPT NUMBER: ");
                    	scanf("%d",&receiptNumber);
                        displayReceiptByReceiptNumber(receiptNumber);
                        break;
                    case 4:
                    	cancelbooking();
                    	break;
                    case 5:
                        registerMember();
                        break;
                    default:
                        printf("Wrong choice!\n");
                        break;
                }
                printf("\nDo you want to return to the main menu? (y/n): ");
                scanf(" %c", &ch2);
            } while (ch2 == 'y');
        } else if (modech == 3) {
            // Member mode
            system("cls");
            char ch3;
            int correct = 0;
            int memberChoice;
            char enteredUsername[20], enteredPassword[20];
            printf("\t\t\t************************************************************************\n");
			printf("\t\t\t\t\t\tMEMBER VERIFICATION\n");
			printf("\t\t\t************************************************************************\n");
            
            printf("\n\t\t\t\tEnter your username: ");
            scanf("%s", enteredUsername);

            printf("\t\t\t\tEnter your password: ");
            scanf("%s", enteredPassword);

            correct = loginMember(enteredUsername, enteredPassword);

            if (correct == 1) {
	            do {
	            	system("cls");
	            	printf("\nYou have logged in as member\n");
                	printf("\n");
					printf("\n\t\t---------------------- Welcome to Mirrored Memories Club ----------------------");
                	printf("\n\n\n");
	
	                printf("\n\t\t\tPress <1> View Member Discounts");
	                printf("\n\t\t\tPress <2> View your Membership Information");
	                printf("\n\t\t\tPress <3> View All Movies Available");
	                printf("\n\t\t\tPress <4> Member Booking");
	                printf("\n\t\t\tPress <5> View Receipt");
	                printf("\n\t\t\tPress <6> Cancel Movie Booking");
	
	                printf("\n\n\t\t\t\tEnter your Choice: ");
	                scanf("%d", &memberChoice);
	
	                switch (memberChoice) {
	                    case 1:
	                    	displayDiscounts(discounts, 3);
	                        break;
	                    case 2:
                            displayMemberInfo(enteredUsername, enteredPassword);
	                        break;
	                    case 3:
	                    	viewAll();
	                    	break;
	                    case 4:
	                    	memberbook_ticket(discounts, 3, enteredUsername, enteredPassword);
	                        break;
	                    case 5:
	                    	system("cls");
	                    	int receiptNumber;
	                    	printf("Enter your RECEIPT NUMBER: ");
	                    	scanf("%d",&receiptNumber);
	                        displayReceiptByReceiptNumber(receiptNumber);
	                        break;
						case 6:
							cancelbooking();
							break;	                        
	                    default:
	                        printf("Invalid choice!\n");
	                        break;
	                }
	                printf("\nDo you want to return to the main menu? (y/n): ");
	                scanf(" %c", &ch3);
	            } while (ch3 == 'y');
        	}
        } else if(modech == 0){
        	return 0;
		}else {
            printf("\nEnter a valid choice!!");
        }
        printf("\nDo you want to change user? (y/n): ");
        scanf(" %c", &choice);
    } while (choice == 'y');
    return 0;
}

int movieCodeExists(char code[]) {
    FILE *fp;
    struct admin mov;
    int check = 0;

    fp = fopen("data.txt", "r");

    if (fp == NULL) {
        return 0; // Assume code doesn't exist if the file doesn't exist
    }

    // Updated format specifier to match the data structure
    while (fscanf(fp, "%s %s %s %s %d %f %d %d %d", mov.code, mov.name, mov.date, mov.time, &mov.cost, &mov.rating, &mov.numseats_R, &mov.numseats_V, &mov.numseats_P) != EOF) {
        if (strcmp(mov.code, code) == 0) {
            check = 1; // Code exists
            break;  // Added break to exit the loop once the code is found
        }
    }

    fclose(fp);
    return check; // Code doesn't exist
}


void insert_details(int n) {		//RECURSION
    
    if(n == 0){
    	return;
	}
	else{
	    FILE *fp;
	    struct admin mov;
	    fp = fopen("data.txt", "a");
		if (fp == NULL) {
	        printf("File not Found\n");
	    } else {
	        	printf("\nEnter details for the movie:\n");
	            printf("Enter movie code: ");
	            scanf("%s", mov.code);
	
	            if (movieCodeExists(mov.code)) {
	                printf("Movie code already exists. Exiting ...\n");
	                return;
	            } else {
	                printf("Enter name: ");
	                scanf(" %s", mov.name);
	                printf("Enter Release Date: ");
	                scanf("%s", mov.date);
	                printf("Enter Show Time: ");
	                scanf("%s", mov.time);
	                printf("Enter Ticket Price: ");
	                scanf("%d", &mov.cost);
	                printf("Enter Rating: ");
	                scanf("%f", &mov.rating);
	                printf("Enter Number of Regular Seats: ");
	                scanf("%d", &mov.numseats_R);
	                printf("Enter Number of VIP Seats: ");
	                scanf("%d", &mov.numseats_V);
	                printf("Enter Number of Premium Seats: ");
	                scanf("%d", &mov.numseats_P);
	
	                fprintf(fp, "%s %s %s %s %d %.2f %d %d %d\n", mov.code, mov.name, mov.date, mov.time, mov.cost, mov.rating, mov.numseats_R, mov.numseats_V, mov.numseats_P);
	                printf("\nRecords inserted successfully\n");
	            }
	    	}
	
	    fclose(fp);
	    return insert_details(n-1);
	}
}


void updateMovie() {
	system("cls");
    FILE *fp, *temp;
    struct admin mov;
    char codeToUpdate[20];
    int found = 0;

    fp = fopen("data.txt", "r");
    temp = fopen("temp.txt", "w");

    if (fp == NULL || temp == NULL) {
        printf("Error opening file for update\n");
        return;
    }

    printf("Enter the movie code to update: ");
    scanf("%s", codeToUpdate);

    while (fscanf(fp, "%s %s %s %s %d %f %d %d %d", mov.code, mov.name, mov.date, mov.time, &mov.cost, &mov.rating, &mov.numseats_R, &mov.numseats_V, &mov.numseats_P) != EOF) {
        if (strcmp(mov.code, codeToUpdate) == 0) {
            printf("Enter updated details for the movie:\n");

            printf("Enter name: ");
            scanf(" %s", mov.name);
            printf("Enter Release Date: ");
            scanf("%s", mov.date);
            printf("Enter Show Time: ");
            scanf("%s", mov.time);
            printf("Enter Ticket Price: ");
            scanf("%d", &mov.cost);
            printf("Enter Rating: ");
            scanf("%f", &mov.rating);
            printf("Enter Number of Regular Seats: ");
            scanf("%d", &mov.numseats_R);
            printf("Enter Number of VIP Seats: ");
            scanf("%d", &mov.numseats_V);
            printf("Enter Number of Premium Seats: ");
            scanf("%d", &mov.numseats_P);

            fprintf(temp, "%s %s %s %s %d %.2f %d %d %d\n", mov.code, mov.name, mov.date, mov.time, mov.cost, mov.rating, mov.numseats_R, mov.numseats_V, mov.numseats_P);

            printf("Movie updated successfully\n");
            found = 1;
        } else {
			fprintf(temp, "%s %s %s %s %d %.2f %d %d %d\n", mov.code, mov.name, mov.date, mov.time, mov.cost, mov.rating, mov.numseats_R, mov.numseats_V, mov.numseats_P);
        }
    }

    if (!found) {
        printf("Movie with code %s not found\n", codeToUpdate);
    }

    fclose(fp);
    fclose(temp);

    remove("data.txt");
    rename("temp.txt", "data.txt");
}


void deleteMovie() {
	system("cls");
    FILE *fp, *temp;
    struct admin mov;
    char codeToDelete[20];
    int found = 0;

    fp = fopen("data.txt", "r");
    temp = fopen("temp.txt", "w");

    if (fp == NULL || temp == NULL) {
        printf("Error opening file for deletion\n");
        return;
    }

    printf("Enter the movie code to delete: ");
    scanf("%s", codeToDelete);

    while (fscanf(fp, "%s %s %s %s %d %f %d %d %d", mov.code, mov.name, mov.date, mov.time, &mov.cost, &mov.rating, &mov.numseats_R, &mov.numseats_V, &mov.numseats_P) != EOF) {
        if (strcmp(mov.code, codeToDelete) == 0) {
            printf("Movie deleted successfully\n");
            found = 1;
        } else {
			fprintf(temp, "%s %s %s %s %d %.2f %d %d %d\n", mov.code, mov.name, mov.date, mov.time, mov.cost, mov.rating, mov.numseats_R, mov.numseats_V, mov.numseats_P);
        }
    }

    if (!found) {
        printf("Movie with code %s not found\n", codeToDelete);
    }

    fclose(fp);
    fclose(temp);

    remove("data.txt");
    rename("temp.txt", "data.txt");
}


void viewAll() {
	system("cls");
    FILE *fp;
    struct admin mov;

    fp = fopen("data.txt", "r");

    if (fp == NULL) {
        printf("There are no records available!\n");
        return;
    }

    printf("\n=============================================================================================================================\n");
    printf("\t\t\t\t\t   Movie Magic Unlocked: Your Selection, Your Way.\n");
    printf("=============================================================================================================================\n");
    printf("\n Price of VIP is 200 more than Regular Price");
    printf("\n Price of Premium is 500 more than Regular Price\n\n");
    printf("%-10s%-17s%-17s%-12s%-12s%-12s%-15s%-15s%-15s\n", "Code", "Name", "Release Date", "Time", "Price", "Rating", "Reg_Seats", "VIP_Seats", "Premium_Seats");
	while (fscanf(fp, "%s %s %s %s %d %f %d %d %d", mov.code, mov.name, mov.date, mov.time, &mov.cost, &mov.rating, &mov.numseats_R, &mov.numseats_V, &mov.numseats_P) != EOF) {
    	printf("%-10s%-17s%-17s%-12s%-12d%-12.2f%-15d%-15d%-15d\n", mov.code, mov.name, mov.date, mov.time, mov.cost, mov.rating, mov.numseats_R, mov.numseats_V, mov.numseats_P);
	}

    fclose(fp);
}


void eraseDataFile() {
	system("cls");
    // Function to erase or truncate the data file
    FILE *fp;

    fp = fopen("data.txt", "w");  // Open the file in write mode (truncating it)
    
    if (fp == NULL) {
        printf("Error opening the data file for erasing!\n");
    } else {
        printf("Data file erased successfully!\n");
        fclose(fp);
    }
    
    FILE *bookfp;

    bookfp = fopen("book.txt", "w");  // Open the file in write mode (truncating it)
    
    if (bookfp == NULL) {
        printf("Error opening the booking file for erasing!\n");
    } else {
        printf("Booking file erased successfully!\n");
        fclose(bookfp);
    }
    printf("Goodbye! Have a great day :)");
    printf("\n\t\t------------------------------------------------------------------");
}


int validatePassword(char *password) {
    int length = strlen(password);
    if (length < 8) {
        return 0;
    }

    int hasUpperCase = 0;
    for (int i = 0; i < length; ++i) {
        if (isupper(password[i])) {
            hasUpperCase = 1;
            break;
        }
    }

    return hasUpperCase;
}

// Function to generate a unique member ID
int generateMemberID() {
    static int memberID = 20003;
    return memberID++;
}

void registerMember() {
    system("cls");
    FILE *fp;
    struct member m;
    char ch;

    fp = fopen("members.txt", "a");

    if (fp == NULL) {
        printf("File not Found\n");
    } else {
        do {
            printf("\nEnter details for membership registration:\n");

            // Generate a unique member ID
            sprintf(m.mem_id, "%d", generateMemberID());
            printf("Enter username: ");
            scanf("%s", m.username);

            // Validate and set password
            while (1) {
                printf("Create a password (8 characters with at least one capital letter): ");
                scanf("%s", m.password);

                if (validatePassword(m.password)) {
                    printf("Password set successfully!\n");
                    break;
                } else {
                    printf("Invalid password format. Try again.\n");
                }
            }

            printf("Enter full name: ");
            scanf("%s", m.name);

            printf("Enter email: ");
            scanf("%s", m.email);

            // Ask for membership type
            printf("Membership Prices\nGOlD --> Rs.2000 monthly\nSILVER --> Rs.1500 monthly\nBRONZE --> Rs.1000 monthly\n");
            printf("Choose membership type (gold/silver/bronze): ");
            scanf("%s", m.membershipType);

            // Ask for payment type
            printf("Choose payment method (Cash/Card): ");
            scanf("%s", m.paymentType);

            // Calculate discount based on membership type and payment type
            if (strcmp(m.membershipType, "gold") == 0) {
                m.price = 2000;
            } else if (strcmp(m.membershipType, "silver") == 0) {
                m.price = 1500;
            } else if (strcmp(m.membershipType, "bronze") == 0) {
                m.price = 1000;
            } else {
                printf("Invalid membership type.\n");
                printf("Registering not possible");
                return;
            }

            fprintf(fp, "%s %s %s %s %s %s %s %d\n", m.mem_id, m.username, m.password, m.name, m.email, m.membershipType, m.paymentType, m.price);

            printf("\nDo you want to register another member? (y/n): ");
            scanf(" %c", &ch);
        } while (ch == 'y');

        printf("\n\t\t\t\t        Membership registration completed successfully!\n");
        printf("\n\t\t\t-------------------------------------------------------------------------------\n");
    }

    fclose(fp);
}

int loginMember(const char *username, const char *password) {
    FILE *fp;
    struct member m;

    fp = fopen("members.txt", "r");

    if (fp == NULL) {
        printf("Error opening member file for login\n");
        return 0;
    }

    while (fscanf(fp, "%s %s %s %s %s %s %s %d", m.mem_id, m.username, m.password, m.name, m.email, m.membershipType, m.paymentType, &m.price) != EOF) {
        if (strcmp(m.username, username) == 0 && strcmp(m.password, password) == 0) {
            fclose(fp);
            return 1; // Correct username and password
        }
    }

    fclose(fp);
    return 0; // Incorrect username or password
}

void displayMemberInfo(const char *username, const char *password) {
	system("cls");
    FILE *fp;
    struct member m;

    fp = fopen("members.txt", "r");

    if (fp == NULL) {
        printf("Error opening member file for display\n");
        return;
    }

    while (fscanf(fp, "%s %s %s %s %s %s %s %d", m.mem_id, m.username, m.password, m.name, m.email, m.membershipType, m.paymentType, &m.price) != EOF) {
        if (strcmp(m.username, username) == 0 && strcmp(m.password, password) == 0) {
        	printf("\n");
			printf("\n\t\t---------------------- Your Membership Informatin ----------------------");
            printf("\n\n\n");
            printf("\n\t\t\t\t\tMember ID: %s", m.mem_id);
            printf("\n\t\t\t\t\tUsername: %s", m.username);
            printf("\n\t\t\t\t\tName: %s", m.name);
            printf("\n\t\t\t\t\tEmail: %s", m.email);
            printf("\n\t\t\t\t\tMembership Type: %s", m.membershipType);
            printf("\n\t\t\t\t\tPayment Type: %s", m.paymentType);
            printf("\n\t\t\t\t\tMemberShip Paymet: Rs.%d monthly", m.price);
            printf("\n\n");
            printf("\n\t\t------------------------------------------------------------------------\n\n");
            break;
        }
    }

    fclose(fp);
}

// Update seats function to be used in book_ticket
void updateSeats(char movie_code[], char seatType, int numSeatsBooked) {
	
    FILE *fp, *standby;
    struct admin mov;

    fp = fopen("data.txt", "r");
    standby = fopen("standby.txt", "w");

    if (fp == NULL || standby == NULL) {
        printf("Error opening file for update\n");
        return;
    }
	while (fscanf(fp, "%s %s %s %s %d %f %d %d %d", mov.code, mov.name, mov.date, mov.time, &mov.cost, &mov.rating, &mov.numseats_R, &mov.numseats_V, &mov.numseats_P) != EOF) {
        if (strcmp(mov.code, movie_code) == 0) {
            
		    switch (seatType) {
		        case 'R':
		            mov.numseats_R -= numSeatsBooked;
		            break;
		        case 'V':
		            mov.numseats_V -= numSeatsBooked;
		            break;
		        case 'P':
		            mov.numseats_P -= numSeatsBooked;
		            break;
		        default:
		            printf("Invalid seat type\n");
		    }
        fprintf(standby, "%s %s %s %s %d %.2f %d %d %d\n", mov.code, mov.name, mov.date, mov.time, mov.cost, mov.rating, mov.numseats_R, mov.numseats_V, mov.numseats_P);
	}else {
			fprintf(standby, "%s %s %s %s %d %.2f %d %d %d\n", mov.code, mov.name, mov.date, mov.time, mov.cost, mov.rating, mov.numseats_R, mov.numseats_V, mov.numseats_P);
        }
    }


    fclose(fp);
    fclose(standby);

    remove("data.txt");
    rename("standby.txt", "data.txt");
}

// Function to check seat availability for a given movie and seat type
int checkSeatAvailability(char movie_code[], char seatType, int numSeatsRequested) {
    FILE *fp;
    struct admin mov;
    int seatsAvailable = 0;

    fp = fopen("data.txt", "r");

    if (fp == NULL) {
        printf("Error opening file for seat availability check\n");
        return 0; // Returning 0 to indicate an error
    }

    while (fscanf(fp, "%s %s %s %s %d %f %d %d %d", mov.code, mov.name, mov.date, mov.time, &mov.cost, &mov.rating, &mov.numseats_R, &mov.numseats_V, &mov.numseats_P) != EOF) {
        if (strcmp(mov.code, movie_code) == 0) {
            switch (seatType) {
                case 'R':
                    seatsAvailable = (mov.numseats_R >= numSeatsRequested);
                    break;
                case 'V':
                    seatsAvailable = (mov.numseats_V >= numSeatsRequested);
                    break;
                case 'P':
                    seatsAvailable = (mov.numseats_P >= numSeatsRequested);
                    break;
                default:
                    printf("Invalid seat type\n");
                    fclose(fp);
                    return 0; // Returning 0 to indicate an error
            }
        }
    }

    fclose(fp);
    return seatsAvailable;
}

// Updated book_ticket function
void book_ticket() {
    system("cls");
    struct book movie;
    char movie_code[20];

    FILE *fp;
    struct admin mov;

    fp = fopen("data.txt", "r");

    if (fp == NULL) {
        printf("There are no records available!\n");
        return;
    }

    // Display available movies
    printf("\n=============================================================================================================================\n");
    printf("\t\t\t\t\t   Movie Magic Unlocked: Your Selection, Your Way.\n");
    printf("=============================================================================================================================\n");
    printf("\n Price of VIP is 200 more than Regular Price");
    printf("\n Price of Premium is 500 more than Regular Price\n\n");
    printf("%-10s%-17s%-17s%-12s%-12s%-12s%-15s%-15s%-15s\n", "Code", "Name", "Release Date", "Time", "Price", "Rating", "Reg_Seats", "VIP_Seats", "Premium_Seats");

    while (fscanf(fp, "%s %s %s %s %d %f %d %d %d", mov.code, mov.name, mov.date, mov.time, &mov.cost, &mov.rating, &mov.numseats_R, &mov.numseats_V, &mov.numseats_P) != EOF) {
        printf("%-10s%-17s%-17s%-12s%-12d%-12.2f%-15d%-15d%-15d\n", mov.code, mov.name, mov.date, mov.time, mov.cost, mov.rating, mov.numseats_R, mov.numseats_V, mov.numseats_P);
    }

    fclose(fp);

    // Get movie code for booking
    printf("\nEnter the movie code for booking: ");
    scanf("%s", movie_code);

    // Check if the entered movie code is valid
    int movieCodeValid = 0;
    FILE *fp2 = fopen("data.txt", "r");
    if (fp2 == NULL) {
        printf("File not found!\n");
        exit(1);
    } else {
        while (fscanf(fp2, "%s %s %s %s %d %f %d %d %d", mov.code, mov.name, mov.date, mov.time, &mov.cost, &mov.rating, &mov.numseats_R, &mov.numseats_V, &mov.numseats_P) != EOF) {
            if (strcmp(mov.code, movie_code) == 0) {
                movieCodeValid = 1;
                break;
            }
        }

        if (!movieCodeValid) {
            printf("\nInvalid movie code! Please enter a valid movie code.\n");
            fclose(fp2);
            return;
        }
    }
    fclose(fp2);

    FILE *bookfp = fopen("book.txt", "a");

    if (bookfp == NULL) {
        printf("File not Found\n");
        return;
    } else {
    	// Display available seats for the selected movie
    	printf("\nAvailable Seats:\n Regular: %d\n VIP: %d\n Premium: %d\n", mov.numseats_R, mov.numseats_V, mov.numseats_P);
    	printf("\nFill in the details For Booking Tickets:\n");
        printf("Your name: ");
        scanf("%s", movie.fullname);
        printf("Mobile number: ");
        scanf("%s", movie.mobile);

    	// Get the seat type for booking
    	printf("Enter seat type (R for Regular, V for VIP, P for Premium): ");
    	char seat_type;
    	scanf(" %c", &seat_type);

    	// Check if the entered seat type is valid
    	if (seat_type != 'R' && seat_type != 'V' && seat_type != 'P') {
        	printf("\nInvalid seat type! Please enter a valid seat type.\n");
       		return;
    	}
		movie.type = seat_type;
    	// Get the number of seats to book
    	printf("Enter the number of seats to book: ");
    	int num_seats;
    	scanf("%d", &num_seats);

    	// Check seat availability before booking
	    if (!checkSeatAvailability(movie_code, seat_type, num_seats)) {
	        printf("\nNot enough seats available for the selected type. Please choose a valid number.\n");
	        return;
	    }
	    movie.seats = num_seats;
	    
	    // Calculate the total cost based on the seat type
	    float cost;
	    switch (seat_type) {
	        case 'R':
	            cost = num_seats * mov.cost;
	            movie.total_amt = cost;
	            movie.receiptno = ReceiptNum();
	            break;
	        case 'V':
	            cost = num_seats * (mov.cost + 200); // VIP is 200 more than Regular
	            movie.total_amt = cost;
	            movie.receiptno = ReceiptNum();
	            break;
	        case 'P':
	            cost = num_seats * (mov.cost + 500); // Premium is 500 more than Regular
	            movie.total_amt = cost;
	            movie.receiptno = ReceiptNum();
	            break;
	        default:
	            printf("\nInvalid seat type!\n");
	            return;
	    }
	
	    // Update available seats and write booking details to book.txt
	    updateSeats(movie_code, seat_type, num_seats);
	    printf("Enter Payment Method(Cash or Card): ");
	    scanf("%s",movie.pay);

	    strcpy(movie.mcode, movie_code);
	}
		fprintf(bookfp, "%s %s %s %c %d %d %d %s\n", movie.mcode, movie.fullname, movie.mobile, movie.type, movie.seats, movie.total_amt, movie.receiptno, movie.pay);
	    fclose(bookfp);

    	printf("\nBooking successful!\n");
    	
		// Display booking Details
		printf("\n\n\n\t\t\t\t ******************* RECEIPT *********************\n");
		printf("\n\t\t\t\t        ********** ENJOY MOVIE **********\n");
				
		printf("\n\t\t\t\t\t   Name: %s", movie.fullname);
		printf("\n\t\t\t\t\t   Mobile Number: %s", movie.mobile);
		printf("\n\t\t\t\t\t   Movie Code: %s", movie.mcode);
		printf("\n\t\t\t\t\t   Movie Name: %s", mov.name);
		printf("\n\t\t\t\t\t   Total Seats: %d", movie.seats);
		printf("\n\t\t\t\t\t   Seat Type : %c", movie.type);
		if (movie.type == 'R')
			printf("\n\t\t\t\t\t   Cost per Ticket: Rs.%d", mov.cost);
		if (movie.type == 'V')
			printf("\n\t\t\t\t\t   Cost per Ticket: Rs.%d", mov.cost + 200);
		if (movie.type == 'P')
			printf("\n\t\t\t\t\t   Cost per Ticket: Rs.%d", mov.cost + 500);
		printf("\n\t\t\t\t\t   Total Amount: Rs.%d", movie.total_amt);
		printf("\n\t\t\t\t\t   Payment Method: %s", movie.pay);
		printf("\n\t\t\t\t\t   Receipt Number: %d", movie.receiptno);
		printf("\n\n");
		printf("\t\t\t\t************* Booking Successful! *************");
		printf("\n\n");
}
  
  
int ReceiptNum () {
  static int receiptnum = 1000;
  return receiptnum++;
}


void displayReceiptByReceiptNumber(int receiptNumber) {
    FILE *bookfp;
    struct book movie;
    struct admin mov;

    bookfp = fopen("book.txt", "r");

    if (bookfp == NULL) {
        printf("Error opening booking file for reading\n");
        return;
    }

    int found = 0;

    while (fscanf(bookfp, "%s %s %s %c %d %d %d %s", movie.mcode, movie.fullname, movie.mobile, &movie.type, &movie.seats, &movie.total_amt, &movie.receiptno, movie.pay) != EOF) {
        if (movie.receiptno == receiptNumber) {
            found = 1;

            // Find the corresponding movie details from data.txt
            FILE *datafp = fopen("data.txt", "r");
            if (datafp == NULL) {
                printf("Error opening data file for reading\n");
                fclose(bookfp);
                return;
            }

            while (fscanf(datafp, "%s %s %s %s %d %f %d %d %d", mov.code, mov.name, mov.date, mov.time, &mov.cost, &mov.rating, &mov.numseats_R, &mov.numseats_V, &mov.numseats_P) != EOF) {
        		if (movie.receiptno == receiptNumber) {
			    	
			    	// Display booking Details
				    printf("\n\n\n\t\t\t\t ******************* RECEIPT *********************\n");
				    printf("\n\t\t\t\t        ********** ENJOY MOVIE **********\n");
				
				    printf("\n\t\t\t\t\t   Name: %s", movie.fullname);
				    printf("\n\t\t\t\t\t   Mobile Number: %s", movie.mobile);
				    printf("\n\t\t\t\t\t   Movie Code: %s", movie.mcode);
				    printf("\n\t\t\t\t\t   Movie Name: %s", mov.name);
				    printf("\n\t\t\t\t\t   Total Seats: %d", movie.seats);
				    printf("\n\t\t\t\t\t   Seat Type : %c", movie.type);
				    if (movie.type == 'R')
				        printf("\n\t\t\t\t\t   Cost per Ticket: Rs.%d", mov.cost);
				    if (movie.type == 'V')
				        printf("\n\t\t\t\t\t   Cost per Ticket: Rs.%d", mov.cost + 200);
				    if (movie.type == 'P')
				        printf("\n\t\t\t\t\t   Cost per Ticket: Rs.%d", mov.cost + 500);
				    printf("\n\t\t\t\t\t   Total Amount: %d", movie.total_amt);
				    printf("\n\t\t\t\t\t   Payment Method: %s", movie.pay);
				    printf("\n\t\t\t\t\t   Receipt Number: %d", movie.receiptno);
				    printf("\n\n");
				    printf("\t\t\t\t************* Booking Successful! *************");
				    printf("\n\n");
                    break;
                }
            }

            fclose(datafp);
            break;
        }
    }

    fclose(bookfp);

    if (!found) {
        printf("Receipt number %d not found\n", receiptNumber);
    }
}


void cancelbooking() {
	system("cls");
    FILE *fp, *temp;
    struct book movie;
    int receipt;
    char movi[20];
    
    int found = 0;

    fp = fopen("book.txt", "r");
    temp = fopen("temp.txt", "w");

    if (fp == NULL || temp == NULL) {
        printf("Error opening file for deletion\n");
        return;
    }

    printf("Enter your receipt number to cancel booking: ");
    scanf("%d", &receipt);

  	while (fscanf(fp, "%s %s %s %c %d %d %d %s", movie.mcode, movie.fullname, movie.mobile, &movie.type, &movie.seats, &movie.total_amt, &movie.receiptno, movie.pay) != EOF) {
        if (movie.receiptno == receipt) {
        	strcpy(movi, movie.mcode);
        	char seat = movie.type;
        	int numseats = movie.seats;
        	updateSeatscancel(movi, seat, numseats); 
            printf("Booking Cancelled Successfully\n");
            strcpy(movie.mcode, movi);
            found = 1;
        } else {
			fprintf(temp, "%s %s %s %c %d %d %d %s", movie.mcode, movie.fullname, movie.mobile, movie.type, movie.seats, movie.total_amt, movie.receiptno, movie.pay);
        }
    }

    if (!found) {
        printf("Movie with receipt number %d not found\n", receipt);
    }

    fclose(fp);
    fclose(temp);

    remove("book.txt");
    rename("temp.txt", "book.txt");
}

// Update seats function to be used in book_ticket
void updateSeatscancel(char movie_code[], char seatType, int numSeatsBooked) {
	
    FILE *fp, *standby;
    struct admin mov;

    fp = fopen("data.txt", "r");
    standby = fopen("standby.txt", "w");

    if (fp == NULL || standby == NULL) {
        printf("Error opening file for update\n");
        return;
    }
	while (fscanf(fp, "%s %s %s %s %d %f %d %d %d", mov.code, mov.name, mov.date, mov.time, &mov.cost, &mov.rating, &mov.numseats_R, &mov.numseats_V, &mov.numseats_P) != EOF) {
        if (strcmp(mov.code, movie_code) == 0) {
            
		    switch (seatType) {
		        case 'R':
		            mov.numseats_R += numSeatsBooked;
		            break;
		        case 'V':
		            mov.numseats_V += numSeatsBooked;
		            break;
		        case 'P':
		            mov.numseats_P += numSeatsBooked;
		            break;
		        default:
		            printf("Invalid seat type\n");
		    }
        fprintf(standby, "%s %s %s %s %d %.2f %d %d %d\n", mov.code, mov.name, mov.date, mov.time, mov.cost, mov.rating, mov.numseats_R, mov.numseats_V, mov.numseats_P);
	}else {
			fprintf(standby, "%s %s %s %s %d %.2f %d %d %d\n", mov.code, mov.name, mov.date, mov.time, mov.cost, mov.rating, mov.numseats_R, mov.numseats_V, mov.numseats_P);
        }
    }


    fclose(fp);
    fclose(standby);

    remove("data.txt");
    rename("standby.txt", "data.txt");
}


void initializeDiscounts(struct MemberDiscount **discounts) {
	system("cls");
    // Allocate memory for three discount levels
    *discounts = (struct MemberDiscount *)malloc(3 * sizeof(struct MemberDiscount));

    // Initialize discounts for movie tickets
    for (int i = 0; i < 3; ++i) {
        printf("Enter discount for %s level (in percentage):\n", i == 0 ? "Gold" : (i == 1 ? "Silver" : "Bronze"));
        strcpy((*discounts)[i].level, (i == 0 ? "Gold" : (i == 1 ? "Silver" : "Bronze")));
        
        for (int j = 0; j < 3; ++j) {
            printf("Enter discount for ");
            switch (j) {
                case 0:
                    printf("Regular Seats: ");
                    break;
                case 1:
                    printf("VIP Seats: ");
                    break;
                case 2:
                    printf("Premium Seats: ");
                    break;
            }
            scanf("%f", &(*discounts)[i].discounts[i][j]);
        }
    }
    
}

void freeDiscounts(struct MemberDiscount *discounts) {
    free(discounts);
}

void displayDiscounts(struct MemberDiscount *discounts, int size) {
	system("cls");
    printf("\t\t\t---------------------Discount Levels:---------------------\n");
    for (int i = 0; i < size; ++i) {
        printf("\n\t\t\t\t%s:\n", discounts[i].level);
        printf("\t\t\t\t\tRegular Seats: %.2f%%\n", discounts[i].discounts[i][0] );
        printf("\t\t\t\t\tVIP Seats: %.2f%%\n", discounts[i].discounts[i][1] );
        printf("\t\t\t\t\tPremium Seats: %.2f%%\n", discounts[i].discounts[i][2] );
    }
    printf("\t\t\t----------------------------------------------------------\n");
}



void memberbook_ticket(struct MemberDiscount *discounts, int discountSize, const char *username, const char *password) {
    system("cls");
    struct book movie;
    char movie_code[20];

    FILE *fp;
    struct admin mov;

    fp = fopen("data.txt", "r");

    if (fp == NULL) {
        printf("There are no records available!\n");
        return;
    }

    printf("\n=============================================================================================================================\n");
    printf("\t\t\t\t\t    Movie Magic Unlocked: Your Selection, Your Way\n");
    printf("=============================================================================================================================\n");
    printf("\n Price of VIP is 200 more than Regular Price");
    printf("\n Price of Premium is 500 more than Regular Price\n\n");
    printf("%-10s%-17s%-17s%-12s%-12s%-12s%-15s%-15s%-15s\n", "Code", "Name", "Release Date", "Time", "Price", "Rating", "Reg_Seats", "VIP_Seats", "Premium_Seats");

    // Display available movies
    while (fscanf(fp, "%s %s %s %s %d %f %d %d %d", mov.code, mov.name, mov.date, mov.time, &mov.cost, &mov.rating, &mov.numseats_R, &mov.numseats_V, &mov.numseats_P) != EOF) {
        printf("%-10s%-17s%-17s%-12s%-12d%-12.2f%-15d%-15d%-15d\n", mov.code, mov.name, mov.date, mov.time, mov.cost, mov.rating, mov.numseats_R, mov.numseats_V, mov.numseats_P);
    }

    fclose(fp);

    // Get movie code for booking
    printf("\nEnter the movie code for booking: ");
    scanf("%s", movie_code);

    // Check if the entered movie code is valid
    int movieCodeValid = 0;
    FILE *fp2 = fopen("data.txt", "r");
    if (fp2 == NULL) {
        printf("File not found!\n");
        exit(1);
    } else {
        while (fscanf(fp2, "%s %s %s %s %d %f %d %d %d", mov.code, mov.name, mov.date, mov.time, &mov.cost, &mov.rating, &mov.numseats_R, &mov.numseats_V, &mov.numseats_P) != EOF) {
            if (strcmp(mov.code, movie_code) == 0) {
                movieCodeValid = 1;
                break;
            }
        }

        if (!movieCodeValid) {
            printf("\nInvalid movie code! Please enter a valid movie code.\n");
            fclose(fp2);
            return;
        }
    }
    fclose(fp2);

    FILE *bookfp = fopen("book.txt", "a");

    if (bookfp == NULL) {
        printf("File not Found\n");
        return;
    } else {
        // Display available seats for the selected movie
        printf("\nAvailable Seats:\n Regular: %d\n VIP: %d\n Premium: %d\n", mov.numseats_R, mov.numseats_V, mov.numseats_P);
        printf("\nFill in the details For Booking Tickets:\n");
        printf("Your name: ");
        scanf("%s", movie.fullname);
        printf("Mobile number: ");
        scanf("%s", movie.mobile);

        // Get the seat type for booking
        printf("Enter seat type (R for Regular, V for VIP, P for Premium): ");
        char seat_type;
        scanf(" %c", &seat_type);
        int j = 0;

        // Check if the entered seat type is valid
        if (seat_type != 'R' && seat_type != 'V' && seat_type != 'P') {
            printf("\nInvalid seat type! Please enter a valid seat type.\n");
            return;
        }

        if (seat_type == 'R') {
            j = 0;
        } else if (seat_type == 'V') {
            j = 1;
        } else if (seat_type == 'P') {
            j = 2;
        }

        // Get the number of seats to book
        printf("Enter the number of seats to book: ");
        int num_seats;
        scanf("%d", &num_seats);

        // Check seat availability before booking
        if (!checkSeatAvailability(movie_code, seat_type, num_seats)) {
            printf("\nNot enough seats available for the selected type. Please choose a valid number.\n");
            return;
        }
        movie.seats = num_seats;

        FILE *fp;
        struct member m;

        fp = fopen("members.txt", "r");

        if (fp == NULL) {
            printf("Error opening member file for display\n");
            return;
        }
        int i = 3;
        while (fscanf(fp, "%s %s %s %s %s %s %s %d", m.mem_id, m.username, m.password, m.name, m.email, m.membershipType, m.paymentType, &m.price) != EOF) {
            if (strcmp(m.username, username) == 0 && strcmp(m.password, password) == 0) {
                if (strcmp(m.membershipType, "gold") == 0) {
                    i = 0;
                } else if (strcmp(m.membershipType, "silver") == 0) {
                    i = 1;
                } else if (strcmp(m.membershipType, "bronze") == 0) {
                    i = 2;
                }
            }
        }

        fclose(fp);

        float discountedrate;
        float discountedcost;

        // Apply discounts based on the customer's level
        switch (i) {
            case 0:
            	discountedrate = (discounts[0].discounts[0][j] / 100 ) * mov.cost;
            	discountedcost = mov.cost - discountedrate;
                break;
            case 1:
                discountedrate = (discounts[1].discounts[1][j] / 100 ) * mov.cost;
                discountedcost = mov.cost - discountedrate;
                break;
            case 2:
                discountedrate = (discounts[2].discounts[2][j] / 100 ) * mov.cost;
                discountedcost = mov.cost - discountedrate;
                break;
        }

        float cost;
        cost = num_seats * discountedcost;

        movie.total_amt = cost;
        movie.receiptno = ReceiptNum();

        // Update available seats and write booking details to book.txt
        updateSeats(movie_code, seat_type, num_seats);

        strcpy(movie.mcode, movie_code);
        movie.type = seat_type;
        printf("Enter Payment Method(Cash or Card): ");
        scanf("%s",movie.pay);
        fprintf(bookfp, "%s %s %s %c %d %d %d %s\n", movie.mcode, movie.fullname, movie.mobile, movie.type, movie.seats, movie.total_amt, movie.receiptno, movie.pay);
        fclose(bookfp);

        printf("\nBooking successful!\n");

        // Display booking Details
		printf("\n\n\n\t\t\t\t ******************* RECEIPT *********************\n");
		printf("\n\t\t\t\t        ********** ENJOY MOVIE **********\n");

        printf("\n\t\t\t\t\t   Name: %s", movie.fullname);
        printf("\n\t\t\t\t\t   Mobile Number: %s", movie.mobile);
        printf("\n\t\t\t\t\t   Movie Code: %s", movie.mcode);
        printf("\n\t\t\t\t\t   Movie Name: %s", mov.name);
        printf("\n\t\t\t\t\t   Total Seats: %d", movie.seats);
        printf("\n\t\t\t\t\t   Seat Type : %c", movie.type);
        if (movie.type == 'R')
            printf("\n\t\t\t\t\t   Cost per Ticket: Rs.%d", mov.cost);
        else if (movie.type == 'V')
            printf("\n\t\t\t\t\t   Cost per Ticket: Rs.%d", mov.cost + 200);
        else if (movie.type == 'P')
            printf("\n\t\t\t\t\t   Cost per Ticket: Rs.%d", mov.cost + 500);
        printf("\n\t\t\t\t\t   Discount Applied: Rs.%.2f",discountedrate);
        printf("\n\t\t\t\t\t   Total Amount: Rs.%d", movie.total_amt);
        printf("\n\t\t\t\t\t   Payment Method: %s", movie.pay);
        printf("\n\t\t\t\t\t   Receipt Number: %d", movie.receiptno);
        printf("\n\n");
		printf("\t\t\t\t************* Booking Successful! *************");
        printf("\n\n");
    }
}
