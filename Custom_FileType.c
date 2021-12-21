/*Samnang San
Project 3: Custom File type
This program will will provide a menu for user to encode and decode file type. The file type created is MKP. For encoding, program will ask user for file name.
file that is entered is copied to the memory. To decode the file, if the file is not an mkp file,it will be rejected. If it is an mkp file, it will read the text that was given by user.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LENGTH 1024
#define FILELENGTH 64

//struct given
struct mkpFile {
    char first;
    char second;
    unsigned int textSize;
    unsigned long int checksum;
    char* text;
};

// Define prototype
unsigned long int getSumCharacters(char *text, unsigned int size);
void encodeMKP();
void decodeMKP();

int main() {
    int option = 1;
    while (option != 3) {
        printf("1. Encode a MKP file\n");
        printf("2. Decode a MKP file\n");
        printf("3. Quit\n");
        scanf("%d", &option);
        while (option < 1 || option > 3) {
            printf("Invalid option. Please try again (1-3)\n");
            scanf("%d", &option);
        }
        getchar();
        if (option == 1) {
            printf("Encode a MKP file\n");
            encodeMKP();
        } else if (option == 2) {
            printf("Decode a MKP file\n");
            decodeMKP();
        }
        printf("\n");
    }
    return 0;
}

unsigned long int getSumCharacters(char *text, unsigned int size) {//function to get sum of characters
    unsigned long int total = 0;
    for (unsigned int i = 0; i < size; i++) {
      total += (unsigned long int) text[i];
    }
    return total;
}

void encodeMKP() {//function to encode
    char input[LENGTH]; //sizes
    char fileName[FILELENGTH];
    FILE *fp = NULL;
    unsigned int len;
    unsigned long int value;
    struct mkpFile *mkp;

    printf("Enter a filename: ");
    fgets(fileName, FILELENGTH, stdin);
    fileName[strlen(fileName) - 1] = '\0';
    fp = fopen(fileName, "w");
    if (fp == NULL) {
      printf("%s not found\n", fileName);
      return;
    }

    printf("Enter input string: ");
    fgets(input, sizeof(input), stdin);
    input[strlen(input) - 1] = '\0';  // Remove new line

    // Get length of input string
    len = (unsigned int) strlen(input);
    // Calculate the sum of the ascii integer value for all characters
    value = getSumCharacters(input, len);

    // Dynamically allocate memory mkp struct
    mkp = malloc(sizeof(struct mkpFile));
    // The first two bytes of mkp struct are letters M and P
    mkp->first = 'M';
    mkp->second = 'P';
    // Update textSize field based on len
    mkp->textSize = len;
    // Update checksum field based on value
    mkp->checksum = value;
    // Allocate memory, and copy text of input into mkp struct
    mkp->text = malloc((len+1) *sizeof(char));
    strcpy(mkp->text, input);




    // Write to mkp file from struct mkp
    // 1 byte for 'M'
    fwrite(&(mkp->first), sizeof(char), 1, fp);
    // 1 byte for 'P'
    fwrite(&(mkp->second), sizeof(char), 1, fp);
    // 4 bytes for number of characters
    fwrite(&(mkp->textSize), sizeof(unsigned int), 1, fp);
    // 8 bytes for sum of the ascii integer value
    fwrite(&(mkp->checksum), sizeof(unsigned long int),1, fp);
    // Write the actual text of the file
    fwrite(mkp->text, sizeof(char), (size_t) len, fp);

    fclose(fp);
}

void decodeMKP() {//function to decode
    char fileName[FILELENGTH];
    printf("Enter a filename: ");
    char *p, *text;
    char c;
    FILE * fp;
    unsigned int len;
    unsigned long int checksum, value;


    fgets(fileName, FILELENGTH, stdin);
    fileName[strlen(fileName) - 1] = '\0';
    p = strrchr(fileName, '.');

    // Valide mkp file
    while (strcmp(p, ".mkp")) {
        printf("Error file. It does not end with the extension mkp. Please try again!\n");
        fgets(fileName, FILELENGTH, stdin);
        fileName[strlen(fileName) - 1] = '\0';
        p = strrchr(fileName, '.');
    }

    fp = fopen(fileName, "r");
    if (fp == NULL) {
        printf("%s not found\n", fileName);
        return;
    }
    // Check 1st byte is 'M'
    fread(&c, sizeof(char), 1, fp);
    if (c != 'M') {
        printf("Error! First byte does not contain M character\n");
        return;
    }
    // Check 2nd byte is 'P'
    fread(&c, sizeof(char), 1, fp);
    if (c != 'P') {
        printf("Error! Second byte does not contain P character\n");
        return;
    }
    // Read the file size
    fread(&len, sizeof(unsigned int), 1, fp);
    // Read 8 bytes check sum
    fread(&checksum, sizeof(unsigned long int), 1, fp);

    // Allocate memory for text
    text = malloc((len+1) * sizeof(char));
    // Read the remain text file
    fread(text, sizeof(char), (size_t)len, fp);
    value = getSumCharacters(text, len);

    if (checksum != value) {
        printf("Error! Checksum does not match\n");
    } else {
        printf("\nDecode text: %s\n", text);
        printf("Number of characters: %u\n", len);
    }

    fclose(fp);

}