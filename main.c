#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

struct word { // define the struct
       char word[11];
} words[100]; // define array of struct as global

/**
 * void drawTheMan (int i, int nOfLives)
 *
 * Prints the i-th line of the drawing in respect to
 * number of lives (nOfLives).
 *
 * @param int i The number of the line that is wanted to be printed
 * @param int nOfLives The number of lives the user lost
 * @return void This functions just uses printfs.
 *
 **/
void drawTheMan(int i,int nOfLives);

/**
 * int iAi(int a, int arr[])
 *
 * Searchs int a in integer array arr[]. This function will return true (1)
 * in the first occur. It just checks the array arr for at least one occureance of a.
 *
 * @param int a The integer that will be looked for
 * @param int arr[] The array that may contain the int a
 * @return int 1|0 Returns 1 if a is in arr, zero otherwise
 *
 **/
int iAi(int a, int arr[]);

/**
 * void writeletters(int i,char *word,int used[])
 *
 * Prints i-th line of the letters section. Calls the other
 * function writeCurrentWord() in a certain line with parameters
 * char *word and int used[]. This function checks the array used[] with help
 * of the function iAi(), and doesn't print the used letters again.
 *
 * @param int i The number of the line to be printed
 * @param char *word The word for calling the function writeCurrentWord
 * @param int used[] The array that contains used letters' numbers
 * @depends int iAi()
 * @return void This functions just uses printfs.
 *
 **/
void writeletters(int i,char *word,int used[]);

/**
 * void writeCurrentWord(char *word,int used[])
 *
 * Prints the word that is being searched during the game. Checks the every character for occureance in the array used[]
 * and prints "--- " for a letter that hasn't been found yet and "-A- " for example, for a found letter. It performs this
 * by the help of the global array char *letters[27] which contains letter numbers. This function also
 * changes the global variable int finished and gives the signal that the game finished (the user has won).
 *
 * @param char *word The word that is being searched
 * @param int used[] The array
 * @depends isalpha() (in header ctype.h)
 * @depends char *letters[27]
 * @depends int finished
 * @return void  This functions just uses printfs.
 *
 **/
void writeCurrentWord(char *word,int used[]);

/**
 * void readWords()
 *
 * This function read words into an array of structs. It uses the global scope because of
 * the performance issues. Reads the predefined binary file and copies the structs to the struct word words[100].
 * This function is called in the beginning of the program. Hence, it can break the program if any error occurs while
 * file opening.
 *
 * @return void This function just fills the structs.
 *
 **/
void readWords();

char *letters[27] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', // array that contains letters with respect to the numbers
    'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', //   aside while they are written in the right side of the screen
    'V', 'W', 'X', 'Y', 'Z'};
int sizeOfArr,finished=0; // size of array defined as a global here. So that When we use #define it will be global.
                        //   sentinel to mark the game as finished
int main(){
    readWords(); // fill the structs first
    char word[10]; // maximum word length is also 10 in the words.dat
    srand(time(NULL)); // randomize the value start point of rand()
    int select = rand()%100; // select a random number from 0 to 99
    strcpy(word,words[select].word); // select that random struct and copy the word from there

    sizeOfArr = strlen(word)+6; // determine the size of used[]. We added +6, because the user may finish the word in the last try
    int used[sizeOfArr]; // initialize the array that will hold the number of letters used
    int i=0,j=0,k=0,where=0,flagWC=0,flagLF=0,lastJ; // sentinels for loops and flags for checks
    for(i=0;i<=sizeOfArr;i++){ used[i] = 99;} // initialize the array with values 99, so that make it possible to count the lives etc.
    #define SOFAR sizeOfArr // define a constant to make it possible for functions to loop till the end of the array
    int nOfLines = 19; // number of lines of the drawing area
    int run = 1; // sentinel for the while loop. To make it possible to end the program.
    int nOfLives=0; // number of lives that user FAILED so far
    while((run=1)){
        system("cls"); // clear the screen at FIRST
        //printf("%s\n",word); // we write the word here for DEMONSTRATION PURPOSES
        nOfLives = 0; // first make it zero, since we will check again and will use '++' operator, this is necessary
        for(i=0;(used[i]>=0&&used[i]<=26);i++){ // for each character in the array
            for(k=0;word[k]!='\0';k++){ // for each character in the word
                if(letters[used[i]]!=word[k]){ // check the array element if it's in the word or not
                    flagLF = 1; // if not raise the flag,
                               //  the flag will remain raised to the end of the loop if will not be found till the end
                }else{
                    flagLF = 0; // drop the flag, we found the array element in the word
                    break; // we found already
                }
            }
            if(flagLF == 1) { nOfLives++; } // we couldn't find the element of the array, the user failed once
        }

        for(i=0;i<nOfLines;i++){ // print the drawing area line by line
            //printf("%2d:",i); // for debugging purposes
            drawTheMan(i,nOfLives);
            writeletters(i,word,used);
        }
        if(nOfLives == 6){ // if user failed 6 times, end the game
            printf("Game over. The word was: %s\n",word);
            system("pause");
            run=0; // end the while loop
            break; // don't execute the rest
        }
        if(finished == 1){ // if the function writeCurrentWord marked the game as finished, end the game
            printf("Congrulations! You have won the game!\n");
            system("pause");
            run=0; // end the while loop
            break; // don't execute the rest
        }
        printf("Used letters so far: ");
        for(i=0;i<SOFAR;i++) // print the letters in the array used
            if(used[i]!=99) // if it's a used number
                printf("%c ",letters[used[i]]);
        puts(""); // new line
        if( ((j>=1) && (j<=26)) || where >= 0 && flagWC != 1 ){ // check the last input given
                                                                // check that it's not the first step with int where
                                                                // check that there wasn't an error in the last run
            printf("Enter word number: ");
            fflush(stdin);
            lastJ = j; // to check that the user entered the same with last number or not
            scanf("%d",&j); // get a user input
            if((j>=1) && (j<=26) && j!=lastJ ){ // the user entered a correct number
                used[where] = j-1; // since the arrays start with 0, fix the user input
                where++; // the next run
            }else{
                flagWC = 1; // wrong selection flag
            }
        }else if(flagWC == 1){ // the last was finished with an error
            puts("You entered a wrong selection. Make a selection between 1 and 26."); // warn the user
            system("pause");
            flagWC = 0; // drop the flag
        }
    }

return 0; // finish the program
}

void drawTheMan(int i,int nOfLives){
    switch(i){
    case 0:
        printf(" ___________.._______");
        break;
    case 1:
        printf("| .__________))______|             ");
        break;
    case 2:
        printf("| | / /      ||                    ");
        break;
    case 3:
        printf("| |/ /       ||                    ");
        break;
    case 4:
        printf("| | /        ||");
        if(nOfLives>=1){
            printf(".-''.               ");
        }else{
            printf("                    ");
        }
        break;
    case 5:
        printf("| |/         ");
        if(nOfLives>=1){
            printf("|/  _  \\ ");
        }else{
            printf("         ");
        }
        printf("             ");
        break;
    case 6:
        printf("| |          ");
        if(nOfLives>=1){
            printf("||  `/,|");
        }else{
            printf("        ");
        }
        printf("              ");
        break;
    case 7:
        printf("| |          ");
        if(nOfLives>=1){
            printf("(\\\\`_.'         ");
        }else{
            printf("                ");
        }
        printf("      ");
        break;
    case 8:
        printf("| |         ");
        if(nOfLives>=2){
            printf(".-`--'.        ");
        }else{
            printf("               ");
        }
        printf("        ");
        break;
    case 9:
        printf("| |     ");
        if(nOfLives>=3){
            printf("   /Y");
        }else{
            printf("     ");
        }
        printf(" ");
        if(nOfLives>=2){
            printf(". .");
        }else{
            printf("   ");
        }
        if(nOfLives>=4){
            printf(" Y\\             ");
        }else{
            printf("                ");
        }
        printf("  ");
        break;
    case 10:
        printf("| |    ");
        if(nOfLives>=3){
            printf("   //");
        }else{
            printf("     ");
        }
        printf(" ");
        if(nOfLives>=2){
            printf("|   |");
        }else{
            printf("     ");
        }
        printf("");
        if(nOfLives>=4){
            printf(" \\\\             ");
        }else{
            printf("                ");
        }
        break;
    case 11:
        printf("| |    ");
        if(nOfLives>=3){
            printf("  // ");
        }else{
            printf("     ");
        }
        printf(" ");
        if(nOfLives>=2){
            printf("| . | ");
        }else{
            printf("      ");
        }
        if(nOfLives>=4){
            printf(" \\\\            ");
        }else{
            printf("               ");
        }
        break;
    case 12:
        printf("| |   ");
        if(nOfLives>=3){
            printf("  ')  ");
        }else{
            printf("      ");
        }
        if(nOfLives>=2){
            printf(" |   | ");
        }else{
            printf("       ");
        }
        if(nOfLives>=4){
            printf(" (`              ");
        }else{
            printf("                 ");
        }
        break;
    case 13:
        printf("| |        ");
        if(nOfLives>=5){
            printf("  || ");
        }else{
            printf("     ");
        }
        if(nOfLives>=6){
            printf("||        ");
        }else{
            printf("          ");
        }
        printf(" The word:  ");
        break;
    case 14:
         printf("| |        ");
        if(nOfLives>=5){
            printf("  || ");
        }else{
            printf("     ");
        }
        if(nOfLives>=6){
            printf("||           ");
        }else{
            printf("             ");
        }
        break;
    case 15:
        printf("| |        ");
        if(nOfLives>=5){
            printf("  || ");
        }else{
            printf("     ");
        }
        if(nOfLives>=6){
            printf("||          ");
        }else{
            printf("          ");
        }
        break;
    case 16:
        printf("| |        ");
        if(nOfLives>=5){
            printf("  || ");
        }else{
            printf("     ");
        }
        if(nOfLives>=6){
            printf("||           ");
        }else{
            printf("             ");
        }
        break;
    case 17:
        printf("| |       ");
        if(nOfLives>=5){
            printf("  / |");
        }else{
            printf("     ");
        }
        printf(" ");
        if(nOfLives>=6){
            printf("| \\           ");
        }else{
            printf("              ");
        }
        break;
    case 18:
        printf("|\"|\"\"\"\"\"\"   ");
        if(nOfLives>=5){
            printf("`-'");
        }else{
            printf("    ");
        }
        printf(" ");
        if(nOfLives>=6){
            printf("`-'           ");
        }else{
            printf("             ");
        }
        break;
    }
}

void writeletters(int i,char *word,int used[]){
    char *sp = "      ";char *c1;char *c2;char *c3;
    switch(i){
    case 0:
        printf("\n");
        break;
    case 1:
        c1 = (!iAi( 0,used)) ? "1) A" : "    ";
        c2 = (!iAi(11,used)) ? "12) L" : "     ";
        c3 = (!iAi(22,used)) ? "23) W" : "     ";
        printf("%s%s%s%s%s\n",c1,sp,c2,sp,c3);
        break;
    case 2:
        c1 = (!iAi( 1,used)) ? "2) B" : "    ";
        c2 = (!iAi(12,used)) ? "13) M" : "     ";
        c3 = (!iAi(23,used)) ? "24) X" : "     ";
        printf("%s%s%s%s%s\n",c1,sp,c2,sp,c3);
        break;
    case 3:
        c1 = (!iAi( 2,used)) ? "3) C" : "    ";
        c2 = (!iAi(13,used)) ? "14) N" : "     ";
        c3 = (!iAi(24,used)) ? "25) Y" : "     ";
        printf("%s%s%s%s%s\n",c1,sp,c2,sp,c3);
        break;
    case 4:
        c1 = (!iAi( 3,used)) ? "4) D" : "    ";
        c2 = (!iAi(14,used)) ? "15) O" : "     ";
        c3 = (!iAi(25,used)) ? "26) Z" : "     ";
        printf("%s%s%s%s%s\n",c1,sp,c2,sp,c3);
        break;
    case 5:
        c1 = (!iAi( 4,used)) ? "5) E" : "    ";
        c2 = (!iAi(15,used)) ? "16) P" : "     ";
        printf("%s%s%s\n",c1,sp,c2);
        break;
    case 6:
        c1 = (!iAi( 5,used)) ? "6) F" : "    ";
        c2 = (!iAi(16,used)) ? "17) Q" : "     ";
        printf("%s%s%s\n",c1,sp,c2);
        break;
    case 7:
        c1 = (!iAi( 6,used)) ? "7) G" : "    ";
        c2 = (!iAi(17,used)) ? "18) R" : "     ";
        printf("%s%s%s\n",c1,sp,c2);
        break;
    case 8:
        c1 = (!iAi( 7,used)) ? "8) H" : "    ";
        c2 = (!iAi(18,used)) ? "19) S" : "     ";
        printf("%s%s%s\n",c1,sp,c2);
        break;
    case 9:
        c1 = (!iAi( 8,used)) ? "9) I" : "    ";
        c2 = (!iAi(19,used)) ? "20) T" : "     ";
        printf("%s%s%s\n",c1,sp,c2);
        break;
    case 10:
        c1 = (!iAi( 9,used)) ? "10) J" : "     ";
        c2 = (!iAi(20,used)) ? "21) U" : "     ";
        printf("%s%s%s\n",c1,sp,c2);
        break;
    case 11:
        c1 = (!iAi(10,used)) ? "11) K" : "     ";
        c2 = (!iAi(21,used)) ? "22) V" : "     ";
        printf("%s%s%s\n",c1,sp,c2);
        break;
    case 12:
        printf("\n");
        break;
    case 13:
        printf("\n");
        break;
    case 14:
        printf("\n");
        break;
    case 15:
        //printf("-C- -A- -R- -A- -M- -E- -L- -A-\n");
        writeCurrentWord(word,used);
        break;
    case 16:
        printf("\n");
        break;
    case 17:
        printf("\n");
        break;
    case 18:
        printf("\n");
        break;
    }
}


void writeCurrentWord(char *word,int used[]){
    int i=0,k=0;
    int flag = 0,flagFinished = 1;
    for(i=0;word[i]!='\0';i++){ // for each character in the word
        flag=0;
        for(k=0;k<SOFAR;k++){ // for each character in the array
            if(word[i]==letters[used[k]]){
                printf("-%c- ",letters[used[k]]);
                flag = 1;
                break;
            }
        }
        if(flag == 0 && isalpha(word[i])){
            printf("--- ");
            flagFinished = 0;
        }
    }
    if(flagFinished == 1){
        finished = 1;
    }
    printf("\n");
}
FILE *fptr;
void readWords(){
    fptr = fopen("words.dat","rb");
    if (!fptr){
        printf("Unable to open file!");
        exit(0);
    }
    int counter = 0;
    for ( counter=1; counter <= 100; counter++){
        fread(&words[counter],sizeof(struct word),1,fptr);
    }
}

int iAi(int a, int arr[]){
    int n = SOFAR;
    int i = 0;
    for(i=0;i<n;i++)
        if(arr[i] == a)
            return 1;
    return 0;
}
