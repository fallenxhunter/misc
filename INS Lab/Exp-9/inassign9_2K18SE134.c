#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#define ll long long int
// Modular Exponentiation Function to calculate (a^b) mod P
ll power(ll x, ll y, ll p)
{
    ll res = 1;    // Initialize result

    x = x % p; // Update x if it is more than or
                // equal to p

    if (x == 0) return 0; // In case x is divisible by p;

    while (y > 0)
    {
        // If y is odd, multiply x with result
        if (y & 1)
            res = (res*x) % p;

        // y must be even now
        y = y>>1; // y = y/2
        x = (x*x) % p;
    }
    return res;
}

//Main Program
int main()
{
	printf("Diffie Hellman Key Exchange\n");
	//variables used
	ll Public_Key_a, Public_Key_b, Generated_Key_x,Generated_Key_y;
	ll Private_Key_a, Private_Key_b, Secret_Key_a, Secret_Key_b;

	// Both the persons have agreed upon public keys Public_Key_a and Public_Key_b
	Public_Key_a = 23; // A prime number Public_Key_a is taken
	printf("The value of Public Key for a : %lld\n",Public_Key_a );

	Public_Key_b = 9; // A primitive root for Public_Key_a, Public_Key_b is taken
	printf("The value of Public Key for b : %lld\n\n", Public_Key_b);

	// A will choose the private key a
	Private_Key_a = 4; // a is the chosen private key+
	printf("The private key a for A : %lld\n", Private_Key_a);
	Generated_Key_x = power(Public_Key_b, Private_Key_a, Public_Key_a); // gets the generated key

	//B will choose the private key b
	Private_Key_b = 3; // b is the chosen private key
	printf("The private key b for B : %lld\n\n", Private_Key_b);
	Generated_Key_y = power(Public_Key_b, Private_Key_b, Public_Key_a); // gets the generated key

	// Generating the secret key after the exchange of keys
	Secret_Key_a = power(Generated_Key_y, Private_Key_a, Public_Key_a); // Secret key for A
	Secret_Key_b = power(Generated_Key_x, Private_Key_b, Public_Key_a); // Secret key for B

	printf("Secret key for the A is : %lld\n", Secret_Key_a);
	printf("Secret Key for the B is : %lld\n", Secret_Key_b);


	//Code for DES

	system("echo The plaintext is :");
	system("cat plaintext.txt");
	//system("\n cat /dev/urandom|head -1 >randombytes.bin");
	//system("xxd randombytes.bin |head -1");
	system("\n echo The Key used is 00000000000024c4");
	system("\n openssl enc -des-cbc -in plaintext.txt -out insassign9-134se-encrypted.enc -nosalt -iv 0000000000000000 -K 00000000000024c4 -a");
	system("\n echo Encrypted Text is : ");
	system("cat insassign9-134se-encrypted.enc");
	system("\n openssl enc -des-cbc -d -in insassign9-134se-encrypted.enc -out insassign9-134se-decrypted.txt -nosalt -iv 0000000000000000 -K 00000000000024c4 -a");
	system("\n echo Decrypted Text is :");
	system("cat insassign9-134se-decrypted.txt");
	return 0;
}