#include <stdio.h>
#include <stdlib.h>

int main()
{
  system("echo The plaintext is :");        //the original taken plaintext
  system("cat insassign11-134se.txt");      //displaying the original message
  printf("\n"); 
  system("openssl aes-256-cbc -e -in insassign11-134se.txt -out insassign11-134se-encrypted.enc -iter 12345 -nosalt");
  printf("\n");                             //encrypting the message using the key entered by the user
  system("echo Encrypted Text is : ");
  system("cat insassign11-134se-encrypted.enc");  //displaying the encrypted msg
  printf("\n");
  system("openssl aes-256-cbc -d -in insassign11-134se-encrypted.enc -out insassign11-134se-decrypted.txt -iter 12345 -nosalt");
printf("\n");                                      //decrypting the message
  system("echo Decrypted Text is :");
  system("cat insassign11-134se-decrypted.txt");  //displaying the decrypted message
}