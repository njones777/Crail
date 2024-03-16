#ifndef RailFence_H
#define RailFence_H

// Function to encrypt an array of integers using Rail Fence Cipher
void rfc(int *array, int size, int rails, int *encryptedArray) {
    if(rails == 1){
        for (int i=0; i<size; i++){
            *(encryptedArray+i) = *(array+i);
        }
    }
    else{
    
        int railFence[rails][size]; // 2D array representing the rails
        int row = 0;
        int dir = 0; // 0 for down, 1 for up

        // Initialize railFence array with 0s
        for (int i = 0; i < rails; i++) {
            for (int j = 0; j < size; j++) {
                railFence[i][j] = -1;
            }
        }

        // Fill the railFence array with the original array
        for (int i = 0; i < size; i++) {
            railFence[row][i] = *(array + i);

            if (row == 0) {
                dir = 0; // Move downwards
            } else if (row == rails - 1) {
                dir = 1; // Move upwards
            }

            // Update the row according to direction
            if (dir == 0) {
                row++;
            } else {
                row--;
            }
        }

        // Construct the encrypted array by reading the railFence array row-wise
        int k = 0;
        for (int i = 0; i < rails; i++) {
            for (int j = 0; j < size; j++) {
                if (railFence[i][j] != -1) {
                    *(encryptedArray + k++) = railFence[i][j];
                }
            }
        }
    }
}

// Function to decrypt an array of integers using Rail Fence Cipher
void rfc_decrypt(int *encryptedArray, int size, int rails, int *decryptedArray) {
    if (rails == 1) {
        for (int i = 0; i < size; i++) {
            *(decryptedArray + i) = *(encryptedArray + i);
        }
    } else {

        int railFence[rails][size]; // 2D array representing the rails
        int row = 0;
        int dir = 0; // 0 for down, 1 for up

        // Initialize railFence array with 0s
        for (int i = 0; i < rails; i++) {
            for (int j = 0; j < size; j++) {
                railFence[i][j] = -1;
            }
        }

        // Determine the rail pattern by filling the railFence array with sequential indices
        for (int i = 0; i < size; i++) {
            railFence[row][i] = i;

            if (row == 0) {
                dir = 0; // Move downwards
            } else if (row == rails - 1) {
                dir = 1; // Move upwards
            }

            // Update the row according to direction
            if (dir == 0) {
                row++;
            } else {
                row--;
            }
        }

        // Populate the decrypted array with the encrypted values based on the rail pattern
        int k = 0;
        for (int i = 0; i < rails; i++) {
            for (int j = 0; j < size; j++) {
                if (railFence[i][j] != -1) {
                    *(decryptedArray + railFence[i][j]) = *(encryptedArray + k++);
                }
            }
        }
    }
}

#endif