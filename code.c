#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <ctype.h>
#define MAX_ATTEMPTS 3
#define locktime 10

// Function to clear the input buffer
void clearbuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Structure for users's profiles
struct User
{
    char username[35];
    char password[35];
    char securityQuestion[35];
    char securityAnswer[35];
    int emergency;
};

// Function to register a new user
void Userprofile()
{
    struct User newuser;

    printf("Enter username: ");
    scanf("%s", newuser.username);

    printf("Enter password: ");
    scanf("%s", newuser.password);

    printf("Enter security question: ");
    scanf("%s", newuser.securityQuestion);

    printf("Enter security answer: ");
    scanf("%s", newuser.securityAnswer);

    printf("Enter emergency code : ");
    scanf("%d", &newuser.emergency);

    FILE *file = fopen("userdata.txt", "a");
    if (file == NULL)
    {
        printf("Error...\n");
        return;
    }

    fprintf(file, " %s  %s  %s  %s %d\n", newuser.username, newuser.password, newuser.securityQuestion, newuser.securityAnswer, newuser.emergency);
    fclose(file);

    printf("ACCOUNT CREATED SUCCESSFULLY!\n");
}

// Function to check if the account exists
int check_profile(const char *username, const char *password)
{
    FILE *file = fopen("userdata.txt", "r");
    if (file == NULL)
    {
        return 0;
    }

    char line[50];
    while (fgets(line, sizeof(line), file) != NULL)
    {
        char storedname[35];
        char storedPassword[35];
        sscanf(line, "%s %s", storedname, storedPassword);

        if (strcmp(storedname, username) == 0 && strcmp(storedPassword, password) == 0)
        {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0; // Username doesn't exist.
}

// Function to sign in a user
int signIn()
{
    FILE *file1;
    char filename[50];
    time_t currentTime;
    time(&currentTime);
    char username[35];
    char password[35];
    printf("\nSigning in....\n");
    printf("USERNAME : ");
    scanf("%s", username);

    printf("PASSWORD : ");
    scanf("%s", password);
    if (!check_profile(username, password))
    {
        return;
    }
    sprintf(filename, "%s.txt", username);

    file1 = fopen(filename, "a");
    fprintf(file1, "Account login on : %s", ctime(&currentTime));
    fclose(file1);

    FILE *file = fopen("userdata.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file for reading.\n");
        return;
    }
}

// Encryption function
void encryption(char *inputfilename, char *outputfilename, char *password)
{
    FILE *inputfile, *outputfile;
    char ch;
    int key = 0;

    // To input a file in binary mode
    inputfile = fopen(inputfilename, "rb");
    if (inputfile == NULL)
    {
        printf("Error opening input file");
        exit(EXIT_FAILURE);
    }

    // To write in decrypted file in binary mode
    outputfile = fopen(outputfilename, "wb");
    if (outputfile == NULL)
    {
        printf("Error opening output file");
        fclose(inputfile);
        exit(EXIT_FAILURE);
    }

    while ((ch = fgetc(inputfile)) != EOF)
    {
        fputc(ch ^ password[key], outputfile);
        key = (key + 1) % strlen(password);
    }

    fclose(inputfile);
    fclose(outputfile);
}
int signout()
{
    printf("Signning out.....");
}

// Function to ensure the strength of password
int Passwordmeter(const char *password)
{
    int len = strlen(password);
    int strength = 0;

    if (len >= 7)
    {
        strength++;
    }
    int i;
    int uppercase = 0;
    int lowercase = 0;
    for (i = 0; i < len; i++)
    {
        if (isupper(password[i]))
        {
            uppercase = 1;
        }
        else if (islower(password[i]))
        {
            lowercase = 1;
        }
    }

    strength += uppercase;
    strength += lowercase;

    int number = 0;
    for (i = 0; i < len; i++)
    {
        if (isdigit(password[i]))
        {
            number = 1;
            break;
        }
    }

    strength += number;

    int specialchar = 0;
    for (i = 0; i < len; i++)
    {
        if (!isalnum(password[i]))
        {
            specialchar = 1;
            break;
        }
    }

    strength += specialchar;

    return strength;
}
// Password checker function
int passwordchecker(char *password)
{
    int length = strlen(password);
    int strength = Passwordmeter(password);

    int upperCase = 0;
    int lowerCase = 0;
    int digit = 0;
    int freq[256] = {0};
    int i;
    for (i = 0; password[i] != '\0'; ++i)
    {
        if (isupper(password[i]))
        {
            upperCase = 1;
        }
        else if (islower(password[i]))
        {
            lowerCase = 1;
        }
        else if (isdigit(password[i]))
        {
            digit = 1;
        }

        if (freq[password[i]] > 0)
        {
            return 0;
        }
        freq[password[i]]++;
    }
    printf("Password Strength: [%d/5]\n", strength);
    if (strength == 1)
    {
        printf("------------------------------------\n");
        printf("METER:\tvery very weak password :(\n ");
        printf("------------------------------------\n");
    }
    else if (strength == 2)
    {
        printf("------------------------------------\n");
        printf("Password could be more stronger!!!");
        printf("\n------------------------------------\n");
    }
    else if (strength == 3)
    {
        printf("------------------------------------\n");
        printf("METER:\tMedium :| \n");
        printf("------------------------------------\n");
    }
    else if (strength == 4)
    {
        printf("------------------------------------\n");
        printf("METER:\t*GOOD*\n");
        printf("------------------------------------\n");
    }
    else if (strength == 5)
    {
        printf("------------------------------------\n");
        printf("METER:\tEXECELLENT :)\n");
        printf("------------------------------------\n");
    }

    return (upperCase && lowerCase && digit && (i >= 7));
    return 1;
}

// Password setter function
char *passwordsetter(void)
{
    char sample[100];
    char *password;

    while (1)
    {
        printf("(should be of 7 characters containing uppercase,lowercase,digit,and symbol)\n Enter the password : ");
        scanf("%s", sample);

        if (passwordchecker(sample))
        {
            // dynamic memory allocation
            password = (char *)malloc(strlen(sample) + 1);
            strcpy(password, sample);
            printf("Password is valid.\n");
            return password;
        }
        else{
            printf("Please try again.\n");
        }
    }
}
// for setting reset password
char *passwordsetter2(void)
{
    char sample[100];
    char *password;

    while (1)
    {
        printf("(should be of 7 characters containing uppercase,lowercase,digit,and symbol)\n Enter the new password : ");
        scanf("%s", sample);

        if (passwordchecker(sample))
        {
            // dynamic memory allocation
            password = (char *)malloc(strlen(sample) + 1);
            strcpy(password, sample);
            printf("Password is valid.\n");
            return password;
        }
        else
        {
            printf("Please try again.\n");
        }
    }
}

// Machine-generated password function
char *machinegeneratedpassword()
{
    char *password;
    password = (char *)malloc(8);

    char *num = "0123456789";
    int num_length = strlen(num);

    char *lower_case = "abcdefghijklmnopqrstuwxyz";
    int lower_length = strlen(lower_case);

    char *upper_case = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int upper_length = strlen(upper_case);

    char *symbol = "!@#$%^&*()";
    int symbol_length = strlen(symbol);

    srand(time(NULL) * getpid());

    for (int i = 0; i < 7; i++)
    {
        int char_type = rand() % 4;

        if (char_type == 0)
            password[i] = num[rand() % num_length];
        else if (char_type == 1)
            password[i] = lower_case[rand() % lower_length];
        else if (char_type == 2)
            password[i] = upper_case[rand() % upper_length];
        else
            password[i] = symbol[rand() % symbol_length];
    }

    password[7] = '\0';
    return password;
}
// function to lok out the file
void countdownTimer(int seconds, const char *message)
{
    printf("%s", message);
    fflush(stdout);

    while (seconds > 0)
    {
        printf("%d ", seconds);
        fflush(stdout);
        sleep(1);
        seconds--;
    }

    printf("\n");
}

int main()
{
    printf("                                     >>> >>> >>> >>> >>> >>> >>> >>>>\n");
    printf("                                     |*|WELCOME TO \"%s\"|*| ", "THE FILE ARMOUR");
    printf("\n                                     >>> >>> >>> >>> >>> >>> >>> >>>>\n");

    int choice;
    printf("1) Create Account\n");
    printf("2) Sign In\n");
    printf("3) Sign Out\n");
    printf("4) Emergency access\n");
    printf("5) Exit\n");
    printf("\nSelect an option: ");
    scanf("%d", &choice);
    clearbuffer(); // Clear the input buffer

    while (choice == 1 || choice == 2 || choice == 3 || choice == 4)
    {
        switch (choice)
        {
        case 1:
            Userprofile();
            break;
        case 2:
            if (signIn())
            {
                printf("Successfully Signed in!\n");
                char filename[256];
                int ans;

                do
                {
                start:
                    printf("\nDo you want to encrpyt file(1 for yes/0 for no) : ");

                    scanf("%d", &ans);

                    if (ans == 1)
                    {
                        printf("Enter the name of the external file: ");
                        scanf("%s", filename);

                        // to set the password
                        char *password;
                        char *resetpassword;
                        printf("Set a password: \n");

                        int choice1;
                        printf("Password (1 for manually generated password, 2 for machine generated password): ");
                        scanf("%d", &choice1);

                        switch (choice1)
                        {
                        case 1:
                            password = passwordsetter();
                            break;
                        case 2:
                        {
                            printf("Machine-generated password\n");
                            password = machinegeneratedpassword();
                            printf("Password: %s\n", password);
                            break;
                        }
                        }

                        int str1 = strlen(password);

                        // encryption
                        encryption(filename, "encrypted.bin", password);

                        // reading the file
                        int ch;
                        int attempts = 0;
                        int maxattempts = 3;

                        printf("Do you want to read the file? (1 for Yes, 0 for No): ");
                        scanf("%d", &ch);

                        char enteredpassword[60];
                        int resetans;
                        do
                        {
                            if (ch == 1)
                            {
                                printf("password : ");
                                scanf("%s", enteredpassword);

                                if (strcmp(enteredpassword, password) == 0)
                                {
                                    printf("LOGIN SUCCESSFULL. WELCOME!\n");

                                    // Decryption
                                    encryption("encrypted.bin", "decrypted.txt", password);
                                    FILE *decryptedFile = fopen("decrypted.txt", "r");

                                    if (decryptedFile == NULL)
                                    {
                                        printf("Error opening decrypted file");
                                    }
                                    // decrypting file content
                                    printf("\nDecrypted File Contents:\n");
                                    char content;

                                    while ((content = fgetc(decryptedFile)) != EOF)
                                    {
                                        putchar(content);
                                    }

                                    fclose(decryptedFile);
                                    break;
                                }
                                else
                                {
                                    // incorrect password
                                    attempts++;
                                    printf("Incorrect password. Remaining attempts: %d\n", maxattempts - attempts);

                                    if (attempts >= maxattempts)
                                    {
                                        printf("Maximum attempts reached. Access denied.\n");
                                        // function for file to be locked
                                        countdownTimer(locktime, "FILE LOCKED...");
                                        attempts = 0;
                                        printf("Do you want to reset the password (1 for yes/0 for no) : ");
                                        scanf("%d", &resetans);
                                        if (resetans == 1)
                                        {
                                            FILE *file = fopen("userdata.txt", "r");
                                            if (file == NULL)
                                            {
                                                return 0;
                                            }

                                            char line[50];
                                            while (fgets(line, sizeof(line), file) != NULL)
                                            {
                                                char storedname[35];
                                                char storedPassword[35];
                                                char question[35];
                                                char answer[35];
                                                char username[35];
                                                char password[35];
                                                char answer1[35];
                                                char sample2[35];
                                                sscanf(line, "%s  %s  %s  %s", storedname, storedPassword, question, answer);
                                                printf("Username :");
                                                scanf("%s", username);
                                                printf("Password :");
                                                scanf("%s", password);
                                                if (strcmp(storedname, username) == 0 && strcmp(storedPassword, password) == 0)
                                                {
                                                    printf("Question : %s : ", question);
                                                    scanf("%s", answer1);
                                                    if (strcmp(answer, answer1) == 0)
                                                    {
                                                        resetpassword = passwordsetter2();
                                                        str1 = strlen(resetpassword);
                                                        // encryption
                                                        encryption(filename, "encrypted.bin", resetpassword);
                                                        FILE *fptr1;
                                                        char Filename[50];
                                                        sprintf(Filename, "%s.txt", username);
                                                        // Opening file in write mode
                                                        fptr1 = fopen(Filename, "a");
                                                        fprintf(fptr1, "THE PASSWORD OF ENCRYPTED FILE : %s IS CHANGED BY THE USER\n", filename);
                                                        fclose(fptr1);

                                                        break;
                                                        break;
                                                    }
                                                    else
                                                        printf("reset failed...");
                                                }
                                                else
                                                    printf("reset failed...");
                                                break;
                                            }

                                            fclose(file);
                                        }
                                    }
                                }
                            }
                            else break;
														
                            strcpy(password, resetpassword);
                            continue;
                        } while (1);
                    }
                    else
                    {
                        break;
                    }
                } while (ans != 0);
            }
            else
            {
                printf("Incorrect username or password\n");
            }
            break;
        case 3:
            signout();
            break;
        case 4:
        {
            FILE *file = fopen("userdata.txt", "r");
            if (file == NULL)
            {
                perror("Error opening file");
                return 0;
            }

            char line[50];
            while (fgets(line, sizeof(line), file) != NULL)
            {
                char storedname[35];
                char storedPassword[35];
                char question[35];
                char answer[35];
                int emergencycode;

                // Use %d for reading the integer emergencycode
                sscanf(line, "%s %s %s %s %d", storedname, storedPassword, question, answer, &emergencycode);

                int code;
                printf("Enter the emergency code : ");
                scanf("%d", &code);

                if (code == emergencycode)
                {
                    FILE *file1;
                    char filename[50];
                    time_t currentTime;
                    time(&currentTime);
                    sprintf(filename, "%s.txt", storedname);

                    file1 = fopen(filename, "a");
                    fprintf(file1, "Account login by emergency code on : %s ", ctime(&currentTime));
                    fclose(file1);

                    FILE *file = fopen("userdata.txt", "r");
                    if (file == NULL)
                    {
                        printf("Error opening file for reading.\n");
                        return;
                    }
                    goto start;
                }
                else
                    printf("Incorrect emergency code\n");
                break;
            }
            // Close the file after use
            fclose(file);
            break;
        }
        default:
            printf("\nSELECT FROM THE GIVEN OPTIONS.\n");
            break;
        }

        if (choice == 5)
        {
            break;
        }

        printf("\nSelect an option: ");
        scanf("%d", &choice);
        clearbuffer(); // Clear the input buffer
    }
    
    printf(">>> >>> >>> >>> >>> >>> >>> >>> >>> >>> >>>\n");
    printf("EXIT FROM THE PROGRAM........THANKYOU!!!!!!\n");
    printf(">>> >>> >>> >>> >>> >>> >>> >>> >>> >>> >>>\n");

    return 0;
}
