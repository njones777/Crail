#include <stdio.h>
#include <string.h>
#include "RailFence.h"
#include "RailUtils.h"


int main(int argc, char *argv[]) {
    FILE *plain_text_file;
    FILE *encrypted_file;
    FILE *Key_File;

    if(argc < 2){
        printf("Usage: ./crail [OPTION] ... [INPUT_FILE] [OUTPUT_FILE]\n");
        printf("Rail fence block cipher with pseudo-random rail key generation\n");
        printf("\nMandatory Requirements\n");
        printf(" -m, --mode [e || d]\t\t specifies e for encryption or d for decryption\n");
        printf(" -i, --input\t\t\t specifies the input file for encryption or decryption\n");
        printf(" -o, --output\t\t\t specifies the outputf file of the resulting encryption or decryption\n");
    }
    
    for (int i=1; i<argc; i++){
        //Check for help menu
        if(strcmp(argv[i], "help")==0 || strcmp(argv[i], "-h")==0, strcmp(argv[i], "--help")==0){
            printf("Usage: ./crail [OPTION] ... [INPUT_FILE] [OUTPUT_FILE]\n");
            printf("Rail fence block cipher with pseudo-random rail key generation\n");
            printf("\nMandatory Requirements\n");
            printf(" -m, --mode [e || d]\t\t specifies e for encryption or d for decryption\n");
            printf(" -i, --input\t\t\t specifies the input file for encryption or decryption\n");
            printf(" -o, --output\t\t\t specifies the outputf file of the resulting encryption or decryption\n");
            break;
        }


        //Check mode(Decrypt or encrypt)
        if (strcmp(argv[i], "-m") == 0){
            if (strcmp(argv[i+1], "d") == 0)
            i++;
        }
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
   
}

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
