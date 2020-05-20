#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
//this function converts lowercase letters to uppercase
void upperMaker(char input[])
{
    int i = 0;
    while (input[i] != '\0') {
        input[i] = toupper(input[i]);
        i++;
    }
}
//this function prints the array to the console
void printMatrix(int row, int col, int matrix[row][col]){
    int i, j;
    for (i = 0; i < row; i++) {
        for(j = 0; j < col; j++)
            printf("%3c", matrix[i][j]);
        printf("\n");
    }
}

int main()
{
    setvbuf(stdout, NULL, _IONBF, 0);
    //creating the matrix;
    int matrix[8][5] = {' ', '0', '1', '2', '3',
                        '0', 'A', 'B', 'C', 'D',
                        '1', 'E', 'F', 'G', 'H',
                        '2', 'I', 'J', 'K', 'L',
                        '3', 'M', 'N', 'O', 'P',
                        '4', 'Q', 'R', 'S', 'T',
                        '5', 'U', 'V', 'W', 'X',
                        '6', 'Y', 'Z', 32, 32
                        };

    //printing the matrix to the console
    printMatrix(8, 5, matrix);

    //prompting the user to input the message to encrypt
    //receiving only letters and spaces
    printf("Enter the input message: ");
    char *text = malloc(1000 * sizeof(char));
    int i = 0;
    char c;
    do {
        c = getchar();
        if (isalpha(c) > 0)
            text[i++] = c;
        else if (c == ' ')
            text[i++] = ' ';
    } while(c != '\n');

    //converting lowercase to uppercase
    upperMaker(text);

    //counting the letter number in message (ignoring spaces)
    i = 0;
    int size_text = 0;
    while (text[i] != '\0') {
        if (isalpha(text[i++]) > 0)
            size_text++;
    }

    /* as one letter stands for two numbers (row, column),
     the encryption will contain 2 times larger elements
     */
    int size_encrypt = 2 * size_text;

    //encoding the message using the matrix
    int encryption[size_encrypt];
    int enc = 0, y = 0, j;
    while (text[y] != '\0') {
        for (i = 1; i < 8; i++) {
            for (j = 1; j < 5; j++) {
                if (text[y] == matrix[i][j]) {
                    if (isalpha(text[y]) > 0) {
                        encryption[enc++] = i - 1;
                        encryption[enc++] = j - 1;
                    }
                    y++;
                    break;
                }
            }
        }
    }

    //prompting the user to input the keyword
    char *keyword = (char*)malloc(sizeof(char));
    _Bool ok = 0;
    while (ok == 0) {
        printf("Enter a keyword without duplicate letters: ");
        scanf("%s", keyword);

        //converting lowercase to uppercase
        upperMaker(keyword);

        //counting duplicates and printing warning is case duplicates detected
        int cnt = 0;
        for (i = 0; i < strlen(keyword); i++) {
            for (j = i + 1; j < strlen(keyword); j++) {
                if (keyword[i] == keyword[j]) {
                    cnt++;
                    break;
                }
            }
        }
        if (cnt > 0)
            printf("Illegal word: it contains duplicate letters!\n");
        else
            ok = 1;
    }

    /* rearranging the encrypt using the keyword's length as column size
    and assigning this structure to a new matrix (key_matrix)*/
    int size_key = (int)strlen(keyword);
    double row = size_encrypt / (float)size_key;
    if (row > size_encrypt / size_key)
        row++;
    row++;

    int key_matrix[(int)row][size_key];

    for (j = 0; j < size_key; j++)
        key_matrix[0][j] = keyword[j];
        
    int l = 0;
    for(i = 1; i < (int)row; i++){
        for(j = 0; j < size_key; j++){
            key_matrix[i][j] = encryption[l++] + '0';
            if(l == size_encrypt){
                for(j += 1; j < size_key; j++){
                    key_matrix[i][j] = '-';
                }
            }
        }
    }
    
    //printing the message to be encoded
    printf("\nMessage to be encoded:\n");
    printf("%s\n", text);

    /*printing the preliminary encryption
     without arranging using the keyword */
    for (i = 0; i < size_encrypt; i++)
        printf("%i", encryption[i]);
    printf("\n");

    /*printing the preliminary encryption using the
     keyword (without alphabetic order) */
    printMatrix((int)row, size_key, key_matrix);
    printf("\n");

    //new matrix reorganized in alphabetic order
    int new_key_matrix[(int)row][size_key];
    int k, a, n, uzhe = 0;
    while (uzhe < size_key) {
        for (a = 'A'; a <= 'Z'; a++) {
            for (k = 0; k < size_key; k++) {
                if (key_matrix[0][k] == a) {
                    for (n = 0; n < (int)row; n++)
                        new_key_matrix[n][uzhe] = key_matrix[n][k];
                    uzhe++;
                }
            }
        }
    }
    //printing the new matrix reorganized in alphabetic order
    printMatrix((int)row, size_key, new_key_matrix);

    //printing the final encrypt
    for(j = 0; j < size_key; j++){
        for(i = 1; i < (int)row; i++){
            if(new_key_matrix[i][j] != '-')
                printf("%c", new_key_matrix[i][j]);
        printf(" ");
        }
    }
    printf("\n");
    return 0;
}
