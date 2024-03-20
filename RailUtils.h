#ifndef RailUtils_H
#define RailUtils_H
#include "RailFence.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <unistd.h>

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
void byteToBitArray(char byte, int *bitArray, int bitsize) {
    for (int i = 0; i < bitsize; i++) {
        bitArray[i] = (byte >> i) & 1;
    }
}

//bit array to byte
char bitArrayToByte(int *bitArray, int bitsize) {
    char byte = 0;
    for (int i = 0; i < bitsize; i++) {
        byte |= (bitArray[i] & 1) << i;
    }
    return byte;
}

char *multiBitArrayToByte(int *bitArray, int bitsize){
    char byte = 0;
    for (int i = 0; i < bitsize; i++) {
        byte |= (bitArray[i] & 1) << i;
    }
    return byte;
}

char* bitArrayToByteArray(int *bitArray, int bitsize) {
    int numBytes = (bitsize + 7) / 8; // Calculate the number of bytes needed
    char *byteArray = (char*)malloc(numBytes * sizeof(char)); // Allocate memory for the byte array

    if (byteArray == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    for (int byteIndex = 0; byteIndex < numBytes; byteIndex++) {
        byteArray[byteIndex] = 0; // Initialize the byte to 0

        // Iterate through each bit of the current byte
        for (int bitIndex = 0; bitIndex < 8; bitIndex++) {
            int bitPosition = byteIndex * 8 + bitIndex;

            // Set the corresponding bit in the byte
            if (bitPosition < bitsize) {
                byteArray[byteIndex] |= (bitArray[bitPosition] & 1) << (7 - bitIndex);
            } else {
                break; // Exit the loop if we've processed all bits
            }
        }
    }

    return byteArray;
}

// byte to bit array (expects in hex format for the byte)
void bytesToBitArray(char *bytes, int bytesize, int *bitArray, int bitsize) {
    // Iterate through each byte
    for (int byteIndex = 0; byteIndex < bytesize; byteIndex++) {
        char byte = bytes[byteIndex];

        // Convert the byte into a bit array
        for (int bitIndex = 0; bitIndex < 8; bitIndex++) { // Assuming 8 bits per byte
            int bitPosition = byteIndex * 8 + bitIndex;
            if (bitPosition < bitsize) {
                bitArray[bitPosition] = (byte >> (7 - bitIndex)) & 1;
            } else {
                break; // Exit the loop if we've reached the end of the bit array
            }
        }
    }
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
//1 for single byte mode 2-20 for multi-byte mode
char* Generate_Rail_Key(long ByteCount, int range, int mode){
    //printf("Range is %d\nMode is %d\n", range, mode);
    FILE *Key_File = fopen("Key.crfc", "w+");
    if (Key_File == NULL){
        fprintf(stderr, "File not found or cannot open\n");
    }
    int RandomByteSlice;

    //Set set for random generation
    srand(time(NULL));
    

    if (mode == 1){
        for(long i=0; i<ByteCount; i++){
            fprintf(Key_File, "%d ", (1 + rand() % (8 - 1 + 1)));
        }
    }
    else if (mode == 2){
        printf("Starting Byte Count %ld\n", ByteCount);
        for(long i=0; i<=ByteCount;){
            //printf("Byte Count: %ld\n", i);
            //Generate the Byte Slice number
            if(i + range > ByteCount){
                //printf("I + %d is more than remaining bytes\n", range);
                //printf("I: %ld\n", i);
                //printf("Byte Count: %ld\n", ByteCount);
                int rest = (int)(ByteCount - i);
                //printf("Rest is %d\n", rest);
                //RandomByteSlice = (int)(ByteCount-i);
                RandomByteSlice = rest;
                fprintf(Key_File, "%d %d\n",RandomByteSlice, (1 + rand() % ((8 * RandomByteSlice) - 1 + 1)) );
                break;

            }
            else{RandomByteSlice = (1 + rand() % (range - 1 + 1));}
            //Format (Byte count, Rail Number )
            //Has the upper bound of the Rail number as the number of bits within the random number of bytes
            fprintf(Key_File, "%d %d\n",RandomByteSlice, (1 + rand() % ((8 * RandomByteSlice) - 1 + 1)) );
            i+=RandomByteSlice;
            if (ByteCount == i){
                printf("They are Equal\n See:\ni: %ld\nByte count: %ld\n", i, ByteCount);
            }
        }
    
    }
    else{
        printf("Byte mode Error Exiting\n");
    }

    fclose(Key_File);
    return "Key.crfc";

}

// Goes through process of encrypting each byte from file
void EncryptBytes(FILE *input_file, FILE* output_file, int ByteMode, int Slice_Size) {
   
    const char* Key_File_Name;      //File name holding rail key numbers
    FILE *Key_File;                 //File Pointer to rail key file
    int Rail_Key_Number;            //Rail number to encrypt current bit array
   
    long test = numBytes(input_file);
    //Generate Key from number of bytes
    printf("bytes: %ld\nByte Mode: %d\nSlice Size: %d\n", test, ByteMode, Slice_Size);
    //Key_File_Name = Generate_Rail_Key(numBytes(input_file), Slice_Size, 2);
    Key_File_Name = Generate_Rail_Key(test, Slice_Size, ByteMode);

    //Open Key file
    Key_File = fopen(Key_File_Name, "r");
    if (Key_File == NULL){perror("Error opening key file for encryption\n");}

    if (ByteMode == 1){
        char Plain_Text_Byte;  //Plain text byte from input file
        char Encrypted_Byte;   //Encrypted Byte to write to output file
        int Plain_Text_Bit_Array[8];    //Plain text bits
        int Encrypted_Bit_Array[8];     //Encrypted bits
        
        
        //Loop through input file to encrypt 
        while(1){

            //Grab current plain text byte
            Plain_Text_Byte = fgetc(input_file);

            //check for end of file
            if(feof(input_file)){break;}

            //Retrieve Rail number from Key File
            if(fscanf(Key_File, "%d", &Rail_Key_Number) != 1){
            perror("Error reading key file for encryption\n");
            }

            // Convert the byte to a bit array
            byteToBitArray(Plain_Text_Byte, Plain_Text_Bit_Array, 8);

            //Encrypt bit array
            rfc(Plain_Text_Bit_Array, 8, Rail_Key_Number, Encrypted_Bit_Array);

            //Convert and write encrypted byte to array
            Encrypted_Byte = bitArrayToByte(Encrypted_Bit_Array, 8);
            fputc(Encrypted_Byte, output_file);
            //writeByteToFile(output_file, Encrypted_Byte);
        }
    }
    //multi-byte mode
    if (ByteMode == 2){
        int Random_Byte_Slice_Size;
        int *Plain_Text_Bit_Array;
        int *Encrypted_Bit_Array;
        char *Plain_Text_Bytes;
        char *Encrypted_Bytes;
        //int Bcount=0;                 //Byte counter variable for trouble shooting
        
        
        //Loop through input file to encrypt 
        while(fscanf(Key_File, "%d %d",&Random_Byte_Slice_Size, &Rail_Key_Number) == 2){
            //Byte counter for trouble shooting and testing purposes
            //Bcount+=Random_Byte_Slice_Size; 

            
            Plain_Text_Bytes = (char *)malloc(Random_Byte_Slice_Size * sizeof(char));
            Encrypted_Bytes = (char *)malloc(Random_Byte_Slice_Size * sizeof(char));
            if (Plain_Text_Bytes == NULL || Encrypted_Bytes == NULL){
                perror("Byte memory allocation failed");
                break;
            }

            size_t bytesRead = fread(Plain_Text_Bytes, sizeof(char), Random_Byte_Slice_Size, input_file);
            if (bytesRead != Random_Byte_Slice_Size){
                perror("Error reading input file");
                free(Plain_Text_Bytes);
                break;
            }

            //Allocate bit arrays based on number of bytes read from file
            Plain_Text_Bit_Array = (int *)malloc((Random_Byte_Slice_Size*8) * sizeof(int));
            Encrypted_Bit_Array = (int *)malloc((Random_Byte_Slice_Size*8) * sizeof(int));

            // convert the bytes to a bit array
            bytesToBitArray(Plain_Text_Bytes, Random_Byte_Slice_Size, Plain_Text_Bit_Array, (Random_Byte_Slice_Size * 8));

            //Encrypt bit array
            rfc(Plain_Text_Bit_Array, (Random_Byte_Slice_Size * 8), Rail_Key_Number, Encrypted_Bit_Array);

            //Convert and write encrypted byte to array
            Encrypted_Bytes = bitArrayToByteArray(Encrypted_Bit_Array, (Random_Byte_Slice_Size * 8));
            for(int i=0; i < Random_Byte_Slice_Size; i++){
                fputc(Encrypted_Bytes[i], output_file);
                //fputc(Plain_Text_Bytes[i], output_file);
            }
            
            free(Plain_Text_Bytes); free(Encrypted_Bytes);
            free(Plain_Text_Bit_Array); free(Encrypted_Bit_Array);
            //printf("Writing %d Bytes, %d Bytes written\n", Random_Byte_Slice_Size, Bcount);
        }
    }
    else{printf("Invalid Byte Mode\n"); exit(1);}

}

//Decrypt encrypted file
void DecryptBytes(FILE *input_file, FILE* output_file, FILE* Key_File, int mode){
    unsigned char Encrypted_byte;
    int Encrypted_BitArray[8];
    unsigned char byte;
    int Rail_Key_Number;
    int bitArray[8];

    if(mode == 1){
        while(1){
            //Retrieve Byte to decrypt
            unsigned char Encrypted_byte = fgetc(input_file);
            
            //Check if we are at the end of the file
            if(feof(input_file)){break;}

            //Retrieve number of rails from key file
            if(fscanf(Key_File, "%d", &Rail_Key_Number) != 1){
                perror("Error reading key file for decryption");
                break;
            }

            //convert the byte to a bit array
            byteToBitArray(Encrypted_byte, Encrypted_BitArray, 8);

            //encrypt bit array
            rfc_decrypt(Encrypted_BitArray, 8, Rail_Key_Number, bitArray);

            //Convert and write encyrpted byte to array
            byte = bitArrayToByte(bitArray, 8);
            fputc(byte, output_file);
            //writeByteToFile(output_file, byte);
            
        }
    }
    if(mode == 2){
        int Random_Byte_Slice_Size;
        int *Plain_Text_Bit_Array;
        int *Encrypted_Bit_Array;
        char *Plain_Text_Bytes;
        char *Encrypted_Bytes;
        size_t bytesRead;


        while(fscanf(Key_File, "%d %d",&Random_Byte_Slice_Size, &Rail_Key_Number) == 2){
            
            //Allocate Plain and Encrypte byte arrays size of the current Byte slice
            Plain_Text_Bytes = (char *)malloc(Random_Byte_Slice_Size * sizeof(char));
            Encrypted_Bytes = (char *)malloc(Random_Byte_Slice_Size * sizeof(char));
            if (Plain_Text_Bytes == NULL || Encrypted_Bytes == NULL){
                perror("Byte memory allocation failed");
                break;
            }
            //Read X amount of bytes from the encrypted file
            //With X being the Byte slice size
            bytesRead = fread(Encrypted_Bytes, sizeof(char), Random_Byte_Slice_Size, input_file);
            if (bytesRead != Random_Byte_Slice_Size){
                perror("Error reading input file");
                free(Plain_Text_Bytes);
                break;
            }

            //Allocate bit arrays based on number of bytes read from file
            Plain_Text_Bit_Array = (int *)malloc((Random_Byte_Slice_Size*8) * sizeof(int));
            Encrypted_Bit_Array = (int *)malloc((Random_Byte_Slice_Size*8) * sizeof(int));

            // convert the bytes to a bit array
            bytesToBitArray(Encrypted_Bytes, Random_Byte_Slice_Size, Encrypted_Bit_Array, (Random_Byte_Slice_Size * 8));

            //Decrypt bit array
            rfc_decrypt(Encrypted_Bit_Array, (Random_Byte_Slice_Size * 8), Rail_Key_Number, Plain_Text_Bit_Array);

             //Convert and write encrypted byte to array
            Plain_Text_Bytes = bitArrayToByteArray(Plain_Text_Bit_Array, (Random_Byte_Slice_Size * 8));
            for(int i=0; i < Random_Byte_Slice_Size; i++){
                fputc(Plain_Text_Bytes[i], output_file);
            }
                //Free dynamically allocated blocks of memeory
                free(Plain_Text_Bytes); free(Encrypted_Bytes);
                free(Plain_Text_Bit_Array); free(Encrypted_Bit_Array);
        }
    }
    else{printf("Invalid Byte Mode\n"); exit(1);}  
}
#endif