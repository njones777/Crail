#ifndef RailUtils_H
#define RailUtils_H
#include "RailFence.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>



// Trouble Shooting Print Functions
void printArray(int *array, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", *(array + i));
    }
    printf("\n");
}

void printDualArray(int *array1, int *array2, int size){
    int i=0;
    printf("Original Array:\n");
    for (i; i<size; i++){
        printf("%d ", *(array1 +i));
    }
   printf("\nModified Array: \n");
    for (i=0; i<size; i++){
        printf("%d ", *(array2 +i));
    }
    printf("\n\n");
}

//byte to bit array (expects in hex format for the byte)
void byteToBitArray(unsigned char byte, int *bitArray) {
    for (int i = 0; i < 8; i++) {
        bitArray[i] = (byte >> i) & 1;
    }
}

//bit array to byte
unsigned char bitArrayToByte(int *bitArray) {
    unsigned char byte = 0;
    for (int i = 0; i < 8; i++) {
        byte |= (bitArray[i] & 1) << i;
    }
    return byte;
}

//write byte to file
void writeByteToFile(FILE *file, unsigned char byte) {
    fputc(byte, file);
}

long numBytes(FILE *file){
    
    long numBytes;

    // Seek to the end of the file
    if (fseek(file, 0, SEEK_END) != 0) {
        perror("Error seeking to end of file");
        return -1;
    }

    // Get the current position, which is the number of bytes
    numBytes = ftell(file);

    if (numBytes == -1) {
        perror("Error getting file size");
        return -1;
    }

    // Seek back to the beginning of the file
    if (fseek(file, 0, SEEK_SET) != 0) {
        perror("Error seeking to beginning of file");
        return -1;
    }
    return numBytes;
}

//Generate Key file from the number of bytes within the file to encrypt
unsigned char* Generate_Rail_Key(long ByteCount){
    int RandNum;

    srand(time(NULL));
    FILE *Key_File = fopen("Key.crfc", "w");
    if (Key_File == NULL){
        fprintf(stderr, "File not found or cannot open\n");
    }
    for(long i=0; i<ByteCount; i++){
        fprintf(Key_File, "%ld ", (1 + rand() % (8 - 1 + 1)));
    }
    fclose(Key_File);
    return "Key.crfc";

}

// Goes through process of encrypting each byte from file
int EncryptBytes(FILE *input_file, FILE* output_file) {
    unsigned char Plain_Text_Byte;  //Plain text byte from input file
    unsigned char Encrypted_Byte;   //Encrypted Byte to write to output file
    const char* Key_File_Name;      //File name holding rail key numbers
    FILE *Key_File;                 //File Pointer to rail key file
    int Plain_Text_Bit_Array[8];    //Plain text bits
    int Encrypted_Bit_Array[8];     //Encrypted bits
    int Rail_Key_Number;            //Rail number to encrypt current bit array
    //long ByteCount;               //Number of bytes from plain text file

    //Retrieve number of bytes from input file
    //ByteCount = numBytes(input_file);

    //Generate Key from number of bytes
    Key_File_Name = Generate_Rail_Key(numBytes(input_file));

    //Open Key file
    Key_File = fopen(Key_File_Name, "r");
    if (Key_File == NULL){printf("Unable to open %s\n",Key_File_Name); return -1;}

    //Loop through input file to encrypt 
    while(1){

        //Grab current plain text byte
        Plain_Text_Byte = fgetc(input_file);

        //check for end of file
        if(feof(input_file)){break;}

        //Retrieve Rail number from Key File
         if(fscanf(Key_File, "%d", &Rail_Key_Number) != 1){
            printf("Error Reading %s\n",Key_File);
            return -1;
        }

        // Convert the byte to a bit array
        byteToBitArray(Plain_Text_Byte, Plain_Text_Bit_Array);

        //Encrypt bit array
        rfc(Plain_Text_Bit_Array, 8, Rail_Key_Number, Encrypted_Bit_Array);

        //Convert and write encrypted byte to array
        Encrypted_Byte = bitArrayToByte(Encrypted_Bit_Array);
        writeByteToFile(output_file, Encrypted_Byte);
    }
    return 0;
}

//Decrypt encrypted file







#endif