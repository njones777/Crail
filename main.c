#include "RailFence.h"
#include "RailUtils.h"
#include <string.h>
#include <stdio.h>
#include <ctype.h>


int main(int argc, char *argv[]) {



    /*FILE *input = fopen("test_files/text_test.txt", "r");
    FILE *output = fopen("test_files/text_encrypt_test.txt", "w");
    EncryptBytes(input, output, 2);*/

    
    FILE *output = fopen("test_files/decrypt_text_test.txt", "w");
    FILE *input = fopen("test_files/text_encrypt_test.txt", "r");
    FILE *key = fopen("Key.crfc", "r");
    DecryptBytes(input, output, key, 2);

    

    /*
    FILE *plain_text_file;          //Acts as input file for encryption and for decryption it acts as an output file
    FILE *encrypted_file;           //Acts as output file for encryption and for encryption it acts as the input file
    FILE *Key_File;                 //Key file is only provided for decryption, the file is generated for the user in encryption
    char *plain_text_file_name=NULL;     //Name of plain text file
    char *encrypted_file_name=NULL;      //Name of encrypted file
    char *Key_File_name=NULL;            //Name of key file
    char mode='\0';                     //Holds mode for program

    if(argc < 2){
        printf("Usage: ./crail [OPTION] ... [INPUT_FILE] [OUTPUT_FILE]\n");
        printf("Rail fence block cipher with pseudo-random rail key generation\n");
        printf("\nMandatory Requirements\n");
        printf(" -i, --input\t\t\t specifies the input file for encryption or decryption\n");
        printf(" -o, --output\t\t\t specifies the output file of the resulting encryption or decryption\n");
        printf(" -k, --keyfile\t\t\t specifies key file for decryption, and can also optionally be used to specify key file name to output from encryption\n\n");
    }
    
    for (int i=1; i<argc; i++){
        //Check for help menu option(s)
        if(strcmp(argv[i], "help")==0 || strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help")==0){
            printf("Usage: ./crail [OPTION] ... [INPUT_FILE] [OUTPUT_FILE]\n");
            printf("Rail fence block cipher with pseudo-random rail key generation\n");
            printf("\nMandatory Requirements\n");

            printf(" -i, --input\t\t\t specifies the input file for encryption or decryption\n");
            printf(" -o, --output\t\t\t specifies the outputf file of the resulting encryption or decryption\n");
            printf(" -k, --keyfile\t\t\t specifies key file for decryption, and can also optionally be used to specify key file name to output from encryption\n\n");
            break;
        }
        //Check Decrypt or Encrypt mode
        //if (mode == NULL && (strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--decrypt") ==0 || strcmp(argv[i], "e") == 0 || strcmp(argv[i], "--encrypt")==0)){
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
        //Unrecognized command was found
        else {
            printf("crail: unrecognized argument: %s, ", argv[i]);
            printf("Try 'crail --help' for more information\n");
            //return 1;
        }
    }
        
        //Open provided Files
        if(mode == 'd'){
            char input[10];
            printf("Decrypting %s into %s using key file %s\n", encrypted_file_name, plain_text_file_name, Key_File_name);
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
            DecryptBytes(encrypted_file, plain_text_file, Key_File);

            //Close open files
            fclose(encrypted_file); fclose(plain_text_file); fclose(Key_File);

            
            return 0;

        }

        if (mode == 'e'){
              //Open encryped/output file in write binary mode 
            encrypted_file = fopen(encrypted_file_name, "wb");
            if (encrypted_file == NULL){printf("Unable to open output file: %s, Check permission and or current directory\n", encrypted_file_name); return 1;}

            //Open plain text/input file in read binary mode
            plain_text_file = fopen(plain_text_file_name, "rb");
            if (encrypted_file == NULL){printf("Unable to open input file: %s, Check permission and or current directory\n", plain_text_file_name); return 1;}

            //Check if a key file name was passed
            
            COMMENT OUT
            CUSTOM KEY OUTPUT, MAYBE IMPLEMENT LATER
            if(Key_File_name == NULL){
                //If user did not provide a key file name then it will be given the default name "Key.crfc"
                EncryptBytes(plain_text_file, encrypted_file, NULL);
            }
            else{
                Key_File = fopen(Key_File_name, "w");
                EncryptBytes(plain_text_file, encrypted_file, Key_File_name);
            }
            END COMMENT
            

            //Start File Encryption
            EncryptBytes(plain_text_file, encrypted_file);

            //Close Open Files
            fclose(encrypted_file); fclose(plain_text_file);
        
        }
        */
            
    return 0;
}

    

