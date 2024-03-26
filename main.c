#include "RailFence.h"
#include "RailUtils.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>


int main(int argc, char *argv[]) {
    
    FILE *plain_text_file;              //Acts as input file for encryption and for decryption it acts as an output file
    FILE *encrypted_file;               //Acts as output file for encryption and for encryption it acts as the input file
    FILE *Key_File;                     //Key file is only provided for decryption, the file is generated for the user in encryption
    char *plain_text_file_name=NULL;    //Name of plain text file
    char *encrypted_file_name=NULL;     //Name of encrypted file
    char *Key_File_name=NULL;           //Name of key file
    int slice_size = 1;                 //Upper bound for byte generation
    char mode='\0';                     //Encryption or Decryption
    
    if(argc < 2){
        menu();
        }
    
    for (int i=1; i<argc; i++){
        //Check for help menu option(s)
        if(strcmp(argv[i], "help")==0 || strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help")==0){
            menu();
            exit(0);
        }
        //Check Decrypt or Encrypt mode
        if (mode == '\0') {
            if (strcmp(argv[i], "e") == 0) {
                mode = 'e';
                continue; // Skip to next iteration in loop
            } else if (strcmp(argv[i], "d") == 0) {
                mode = 'd';
                continue; // Skip to next iteration in loop
            }
        }

        // Check for input file
        if (strcmp(argv[i], "-i") == 0 || strcmp(argv[i], "--input") == 0) {
            if (i + 1 < argc) {
                if(mode=='d'){
                    encrypted_file_name = argv[i + 1];
                }
                if(mode=='e'){
                    plain_text_file_name = argv[i + 1];
                }
                else if (mode=='\0'){
                    printf("Mode not Defined\n");
                    exit(1);
                }
                i+=1;  // Skip next argument as it's the input file name
            } else {
                printf("Missing input file argument.\n");
                return 1;
            }
            continue;   //Skip to next iteration in loop
        }
       // Check for output file
        if (strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--output") == 0) {
            if (i + 1 < argc) {
                if(mode=='d'){
                    plain_text_file_name = argv[i + 1];
                }
                if(mode=='e'){
                    encrypted_file_name = argv[i + 1];
                }
                else if (mode=='\0'){
                    printf("Mode not Defined\n");
                    exit(1);
                }
                i+=1;  // Skip next argument as it's the output file name
            } else {
                printf("Missing output file argument.\n");
                return 1;
            }
            continue;   //Skip to next iteration in loop
        }
       // Check for key file
        if (strcmp(argv[i], "-k") == 0 || strcmp(argv[i], "--keyfile") == 0) {
            if (i + 1 < argc) {
                Key_File_name = argv[i + 1];
                i+=1;  // Skip next argument as it's the key file name
            } else {
                printf("Missing key file argument.\n");
                return 1;
            }
            continue;   //Skip to next iteration in loop
        }

        // Check for slice size
        if (strcmp(argv[i], "-s") == 0 || strcmp(argv[i], "--slice") == 0) {
            if (i + 1 < argc) {
                slice_size = atoi(argv[i + 1]);
                i+=1;  // Skip next argument as it's the key file name
            } else {
                printf("Missing slice size.\n");
                return 1;
            }
            continue;   //Skip to next iteration in loop
        }
        //Unrecognized command was found
        else {
            printf("crail: unrecognized argument: %s, ", argv[i]);
            printf("Try 'crail --help' for more information\n");
            return 1;
        }
    }
        //Open provided Files
        if(mode == 'd'){
            //Verification Before decryption
            char input[10];

            //Check if user wants slice mode enabled
            printf("Enable slice mode (Y/N):");
            fgets(input, sizeof(input), stdin);

            for(int i =0; input[i]; i++){
                input[i] = tolower(input[i]);
            }

            //Exit if unrecognized command was given for slice mode
            if (strcmp(input, "y\n") == 0 || strcmp(input, "yes\n")==0 || strcmp(input, "Y\n")==0){slice_size=2;}
            else if (strcmp(input, "n\n") == 0 || strcmp(input, "no\n") == 0){slice_size=1;}
            else {printf("Invalid slice mode set\nExiting\n");exit(0);}

            memset(input, '\0', sizeof(input));

            //Final verification before decryption process
            printf("Decrypting %s into %s using key file %s", encrypted_file_name, plain_text_file_name, Key_File_name);
            printf("Do you want to proceed (Y/N):");
            fgets(input, sizeof(input), stdin);

            for(int i =0; input[i]; i++){
                input[i] = tolower(input[i]);
            }

            //Check for yes or no in input
            if (strcmp(input, "y\n") == 0 || strcmp(input, "yes\n")==0 || strcmp(input, "Y\n")==0){printf("Proceeding...\n");}
            else if (strcmp(input, "n\n") == 0 || strcmp(input, "no\n") == 0){printf("Exiting...\n"); exit(0);}
            else {printf("Invalid confirmation input, Exiting...\n");exit(0);}

            //Open encryped/input file in read binary mode 
            encrypted_file = fopen(encrypted_file_name, "rb");
            if (encrypted_file == NULL){printf("Unable to open input file: %s, Check permission and or current directory\n", encrypted_file_name); return 1;}

            //Open plain text/output file in write binary mode
            plain_text_file = fopen(plain_text_file_name, "wb");
            if (encrypted_file == NULL){printf("Unable to open output file: %s, Check permission and or current directory\n", plain_text_file_name); return 1;}

            //Open Key file in read mode to peform decryption
            Key_File = fopen(Key_File_name, "r");
            if (encrypted_file == NULL){printf("Unable to open %s, Check permission and or current directory\n", Key_File_name); return 1;}

            //Start File Decryption
            //Check for slice size
            if (slice_size != 1){
            DecryptBytes(encrypted_file, plain_text_file, Key_File, 2);
            }
            else{DecryptBytes(encrypted_file, plain_text_file, Key_File, 1);}

            //Close open files
            fclose(encrypted_file); fclose(plain_text_file); fclose(Key_File);
 
            return 0;
        }

        if (mode == 'e'){
            char input[10];
            printf("Encrypting %s into %s using key file %s with a slice size of %d\n",plain_text_file_name, encrypted_file_name, Key_File_name, slice_size);
            printf("Do you want to proceed (Y/N):");
            fgets(input, sizeof(input), stdin);

            for(int i =0; input[i]; i++){
                input[i] = tolower(input[i]);
            }

            //Check for yes or no in input
            if (strcmp(input, "y\n") == 0 || strcmp(input, "yes\n")==0 || strcmp(input, "Y\n")==0){printf("Proceeding...\n");}
            else if (strcmp(input, "n\n") == 0 || strcmp(input, "no\n") == 0){printf("Exiting...\n"); exit(0);}
            else {printf("Invalid confirmation input, Exiting...\n");exit(0);}

            //Open encryped/output file in write binary mode 
            encrypted_file = fopen(encrypted_file_name, "wb");
            if (encrypted_file == NULL){printf("Unable to open output file: %s, Check permission and or current directory\n", encrypted_file_name); return 1;}
            //Open plain text/input file in read binary mode
            plain_text_file = fopen(plain_text_file_name, "rb");
            if (encrypted_file == NULL){printf("Unable to open input file: %s, Check permission and or current directory\n", plain_text_file_name); return 1;}
  

            //Start File Encryption
            //Check if a slice size grater than 1 was specified to change Byte mode
            if(slice_size > 1){
                EncryptBytes(plain_text_file, encrypted_file, 2, slice_size);
            }
            else if (slice_size == 1){EncryptBytes(plain_text_file, encrypted_file, 1, 1);}

            //Close Open Files
            fclose(encrypted_file); fclose(plain_text_file);
        }        
    return 0;
}

    

