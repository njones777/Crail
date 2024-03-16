#include <stdio.h>
#include <string.h>
#include "RailFence.h"
#include "RailUtils.h"


int main(int argc, char *argv[]) {
    /*
    FILE *plain_text_file;          //Acts as input file for encryption and for decryption it acts as an output file
    FILE *encrypted_file;           //Acts as output file for encryption and for encryption it acts as the input file
    FILE *Key_File;                 //Key file is only provided for decryption, the file is generated for the user in encryption
    char *plain_text_file_name;     //Name of plain text file
    char *encrypted_file_name;      //Name of encrypted file
    char *Key_File_name;            //Name of key file
    char *mode;                     //Holds mode for program

    if(argc < 2){
        printf("Usage: ./crail [OPTION] ... [INPUT_FILE] [OUTPUT_FILE]\n");
        printf("Rail fence block cipher with pseudo-random rail key generation\n");
        printf("\nMandatory Requirements\n");
        printf(" -m, --mode [e || d]\t\t specifies e for encryption or d for decryption\n");
        printf(" -i, --input\t\t\t specifies the input file for encryption or decryption\n");
        printf(" -o, --output\t\t\t specifies the output file of the resulting encryption or decryption\n");
        printf(" -k, --keyfile\t\t\t specifies key file for decryption, and can also optionally be used to specify key file name to output from encryption ");
    }
    
    for (int i=1; i<argc; i++){
        //Check for help menu option(s)
        if(strcmp(argv[i], "help")==0 || strcmp(argv[i], "-h")==0, strcmp(argv[i], "--help")==0){
            printf("Usage: ./crail [OPTION] ... [INPUT_FILE] [OUTPUT_FILE]\n");
            printf("Rail fence block cipher with pseudo-random rail key generation\n");
            printf("\nMandatory Requirements\n");
            printf(" -m, --mode [e || d]\t\t specifies e for encryption or d for decryption\n");
            printf(" -i, --input\t\t\t specifies the input file for encryption or decryption\n");
            printf(" -o, --output\t\t\t specifies the outputf file of the resulting encryption or decryption\n");
            printf(" -k, --keyfile\t\t\t specifies key file for decryption, and can also optionally be used to specify key file name to output from encryption ");

            break;
        }
        //Check mode(Decrypt or encrypt)
        if (strcmp(argv[i], "-m") == 0){
            if (strcmp(argv[i+1], "d") == 0){
                mode="d";
            }
            if (strcmp(argv[i+1], "e") == 0){
                mode="e";
            }
            i++;    //Skip next argument as we expect the next argument to be the modes flag option
        }
        //Check for input file
        if (strcmp(argv[i], "-i"==0) || strcmp(argv[i], "--input") ==0){
            //For decrypt mode input file will be encrypted file
            if(mode == "d"){
                encrypted_file_name = argv[i+1];
            }
            //For encyrpt mode input file will be the plaintext file 
            if(mode == "e"){
                plain_text_file_name = argv[i+1];
                
            }
            //increment i as the next value should be the input file name 
            i++;
        }

        //Check for output file 
        if (strcmp(argv[i], "-o"==0)|| strcmp(argv[i], "--output") ==0){
             //For decrypt mode output file will be plaintext file
            if(mode == "d"){
                plain_text_file = argv[i+1];

            }
            //For encyrpt mode output file will be the encrypted file 
            if(mode == "e"){
                encrypted_file_name = argv[i+1];
                
            }
            //increment i as the next value should be the output file name 
            i++;
        }
        //Unrecognized command was found
        else{
            printf("crail: unrecognized %s",argv[i]);
            printf("Try 'crail --help' for more information");
        }
        

        //Open provided Files

        if(mode == "d"){
            //Open encryped/input file in read binary mode 
            encrypted_file = fopen(encrypted_file_name, "rb");
            if (encrypted_file == NULL){printf("Unable to open %s, Check permission and or current directory\n", encrypted_file_name); return 1;}

            //Open plain text/output file in write binary mode
            plain_text_file = fopen(plain_text_file_name, "wb");
            if (encrypted_file == NULL){printf("Unable to open %s, Check permission and or current directory\n", plain_text_file_name); return 1;}

            //Open Key file in read mode to peform decryption
            Key_File = fopen(Key_File_name, "r");
            if (encrypted_file == NULL){printf("Unable to open %s, Check permission and or current directory\n", Key_File_name); return 1;}



        }
        if (mode == "e"){
              //Open encryped/output file in write binary mode 
            encrypted_file = fopen(encrypted_file_name, "wb");
            if (encrypted_file == NULL){printf("Unable to open %s, Check permission and or current directory\n", encrypted_file_name); return 1;}

            //Open plain text/input file in read binary mode
            plain_text_file = fopen(plain_text_file_name, "rb");
            if (encrypted_file == NULL){printf("Unable to open %s, Check permission and or current directory\n", plain_text_file_name); return 1;}

            //Open Key file in write mode
            Key_File = fopen(Key_File_name, "w");
            if (encrypted_file == NULL){printf("Unable to open %s, Check permission and or current directory\n", Key_File_name); return 1;}

        }



        //Cleanup open files
        fclose(encrypted_file); fclose(plain_text_file); fclose(Key_File);
        */
        
        //Decrypt Image Test
        FILE *output_file = fopen("plain.png", "wb");
        FILE *input_file = fopen("encrypted_image.png", "rb");
        FILE *key_file = fopen("Key.crfc", "r");
        if (key_file == NULL){
            perror("Error opening file");
        }
        int status = DecryptBytes(input_file, output_file, key_file);
        
        //Encrypt Image Test
        //FILE *input_file = fopen("image_test.png", "rb");
        //FILE *output_file = fopen("encrypted_image.png", "wb");
        //int status = EncryptBytes(input_file, output_file);
        
       
       
       
       
       
        return 0;



    }




    /*
    FILE *input_file = fopen("test.txt", "r");
    FILE *output_file = fopen("e2test.txt", "w");
    int status = EncryptBytes(input_file, output_file);
    */

    //attempt decrypt
    /*
    FILE *input_file = fopen("e2test.txt", "r");
    FILE *output_file = fopen("plaintext.txt", "w");
    FILE *key = fopen("Key.crfc", "r");
    unsigned char Encrypted_byte;
    int EncryptedBitArray[8];
    unsigned char byte;
    int Key_Rail_Num;
    int bitArray[8];

    while(1){
        //Retrieve Byte to encrypt
        unsigned char Encrypted_byte = fgetc(input_file);
        
        //Check if we are at the end of the file
        if(feof(input_file)){break;}

        //Retrieve number of rails from key file
        if(fscanf(key, "%d", &Key_Rail_Num) != 1){
            printf("Error Reading %s\n",key);
            break;
        }

        //convert the byte to a bit array
        byteToBitArray(Encrypted_byte, EncryptedBitArray);

        //encrypt bit array
        rfc_decrypt(EncryptedBitArray, 8, Key_Rail_Num, bitArray);

        //Convert and write encyrpted byte to array
        byte = bitArrayToByte(bitArray);
        writeByteToFile(output_file, byte);
        
        //Print Arrays for trouble shooting
        //printDualArray(bitArray, EncryptedBitArray, 8);
    }
    */
   

/*
 FILE *output = fopen("encrypted_test.txt", "wb");
    FILE *input = fopen("test.txt", "rb");
    FILE *key = fopen("Key.crfc", "r");
    unsigned char Encrypted_byte;
    int EncryptedBitArray[8];
    unsigned char byte;
    int Key_Rail_Num;
    int bitArray[8];

    while(1){
        //Retrieve Byte to encrypt
        unsigned char byte = fgetc(input);
        
        //Check if we are at the end of the file
        if(feof(input)){break;}

        //Retrieve number of rails from key file
        if(fscanf(key, "%d", &Key_Rail_Num) != 1){
            printf("Error Reading %s\n",key);
            break;
        }

        //convert the byte to a bit array
        byteToBitArray(byte, bitArray);

        //encrypt bit array
        rfc(bitArray, 8, Key_Rail_Num, EncryptedBitArray);

        //Convert and write encyrpted byte to array
        Encrypted_byte = bitArrayToByte(EncryptedBitArray);
        writeByteToFile(output, Encrypted_byte);
        
        //Print Arrays for trouble shooting
        //printDualArray(bitArray, EncryptedBitArray, 8);
    }
    return 0;
*/
