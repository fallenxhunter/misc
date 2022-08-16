#include<stdio.h>

int main()
{
	printf("DES USING OPEN SSL\n");

	// DES
    // Now we will implement the DES algorithm for the ecryption of the text.
	system("echo The plaintext is :");
	system("cat plaintext.txt");
    printf("\n");
	system("\n cat /dev/urandom|head -1 >randombytes.bin");
	system("xxd randombytes.bin |head -1");
	system("\n echo The Key used is 00000000000024c4");
    printf("\n");
	system("\n openssl enc -des-cbc -in plaintext.txt -out insassign7-134se-encrypted.enc -nosalt -iv 0000000000000000 -K 00000000000024c4 -a");
	system("\n echo Encrypted Text is : ");
	system("cat insassign7-134se-encrypted.enc");
    printf("\n");
	system("\n openssl enc -des-cbc -d -in insassign7-134se-encrypted.enc -out insassign7-134se-decrypted.txt -nosalt -iv 0000000000000000 -K 00000000000024c4 -a");
	system("\n echo Decrypted Text is :");
	system("cat insassign7-134se-decrypted.txt");
    printf("\n");

	return 0;
}