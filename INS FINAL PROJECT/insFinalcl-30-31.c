#include <stdio.h>          /*IMPORTING THE STDIO LIBRARY*/
#include <unistd.h>         /*IMPORTING THE UNISTD LIBRARY. it will be used for the fork to send/recieve text*/
#include <malloc.h>         /*IMPORTING THE MALLOC FOR MEMORY ALLOCATION */
#include <string.h>         /*IMPORTING THE STRING.h FOR using fgets funtion. It will get the input from user*/
#include <sys/socket.h>     /*IMPORTING IT as it will be used for creating sockets*/
#include <resolv.h>         /*IMPORTING IT TO FIND THE IP address*/
#include <netdb.h>          /*USEFULL for network operations */
#include <openssl/ssl.h>    /*USING openssl function's and certificates and configuring them*/
#include <openssl/err.h>    /*helps in finding out openssl errors*/

#define WORD_SIZE 1024         /*WORD_SIZE for reading messages*/

int Open_Connection(const char *Host_Name, int Port_NUM)

{
    int SocketD;

    struct hostent *Host_D;

    struct sockaddr_in S_ADDRESS;           /*HERE WE ARE CREATING SOCKETS*/

    if ((Host_D = gethostbyname(Host_Name)) == NULL)

    {

        perror(Host_Name);

        abort();
    }

    SocketD = socket(PF_INET, SOCK_STREAM, 0); /*HERE WE ARE SETTING A TCP CONNECTION*/

    bzero(&S_ADDRESS, sizeof(S_ADDRESS));

    S_ADDRESS.sin_family = AF_INET;

    S_ADDRESS.sin_port = htons(Port_NUM);

    S_ADDRESS.sin_addr.s_addr = *(long *)(Host_D->h_addr);

    if (connect(SocketD, (struct sockaddr *)&S_ADDRESS, sizeof(S_ADDRESS)) != 0) /*ON A SOCKET, WE ARE INITIATING A CONNECTION*/

    {

        close(SocketD);

        perror(Host_Name);

        abort();
    }

    return SocketD;
}

SSL_CTX *Init_CTX(void)              /*SSL CONTEXT STRUCTURE IS SET UP*/
{
    SSL_METHOD *Method_var;

    SSL_CTX *CTX_var;

    OpenSSL_add_all_algorithms();   /* Loading SLL ALGORITHMS*/

    SSL_load_error_strings();       /* CHECKING FOR ANY ERRORS */

    Method_var = TLSv1_2_client_method(); /*A NEW INSTANCE OF CLIENT IS CREATED */

    CTX_var = SSL_CTX_new(Method_var);      /* NEW  */

    if (CTX_var == NULL)

    {

        ERR_print_errors_fp(stderr);

        abort();
    }

    return CTX_var;
}

void Show_Certs(SSL *ssl) /*THE zFICATE IS SHOWN AND MATCHED*/
{
    X509 *SSL_CERTIFICATE;

    char *temp_line;

    SSL_CERTIFICATE = SSL_get_peer_certificate(ssl); /* TAKING THE CERTIFICATE AS INPUT */

    if (SSL_CERTIFICATE != NULL)
    {

        printf("Server certificates:n");

        temp_line = X509_NAME_oneline(X509_get_subject_name(SSL_CERTIFICATE), 0, 0);

        printf("Subject: %sn", temp_line);

        free(temp_line);            

        temp_line = X509_NAME_oneline(X509_get_issuer_name(SSL_CERTIFICATE), 0, 0);

        printf("Issuer: %sn", temp_line);

        free(temp_line);           

        X509_free(SSL_CERTIFICATE);       
    }

    else

        printf("Info: No client certificates configured.n");
}

int main(int count, char *strings[]) /* WHEN STARTING WE TAKE PORT AND IP AS INPUT*/

{
    SSL_CTX *CTX_var;

    int Server_var;

    SSL *SSL_var;

    char buff[1024];

    char input[WORD_SIZE];

    int bytes;

    char *Host_Name, *Port_Num;

    pid_t cpid; /* fork variable*/

    if (count != 3)

    {

        printf("usage: %s n", strings[0]);

        exit(0);
    }

    SSL_library_init();         /*load encryption and hash algo's in ssl*/

    Host_Name = strings[1];

    Port_Num = strings[2];

    CTX_var = Init_CTX();

    Server_var = Open_Connection(Host_Name, atoi(Port_Num));   /*converting ascii port to interger */

    SSL_var = SSL_new(CTX_var);         /* create new SSL connection state */

    SSL_set_fd(SSL_var, Server_var);    /* attach the socket descriptor */

    if (SSL_connect(SSL_var) == -1) /* perform the connection */

        ERR_print_errors_fp(stderr);

    else

    {

        printf("Connected with %s encryptionn", SSL_get_cipher(SSL_var));

        Show_Certs(SSL_var);

        /* get any certs */

        cpid = fork();

        /*Fork system call is used to create a new process*/

        if (cpid == 0)

        {

            while (1)
            {

                printf("\nENTER YOUR MESSAGE:");

                fgets(input, WORD_SIZE, stdin);

                SSL_write(SSL_var, input, strlen(input)); /* encrypt & send message */
            }
        }

        else
        {

            while (1)

            {

                bytes = SSL_read(SSL_var, buff, sizeof(buff)); /* get request */

                if (bytes > 0)

                {

                    buff[bytes] = 0;

                    printf("\nMESSAGE RECEIVED: %s\n", buff);
                }
            }
        }

        SSL_free(SSL_var); /* release connection state */
    }
    close(Server_var); /* close socket */

    SSL_CTX_free(CTX_var); /* release context */

    return 0;
}
