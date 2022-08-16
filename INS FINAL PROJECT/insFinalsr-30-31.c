#include <stdio.h>          /*IMPORTING THE STDIO LIBRARY*/
#include <unistd.h>         /*IMPORTING THE UNISTD LIBRARY. it will be used for the fork to send/recieve text*/
#include <malloc.h>         /*IMPORTING THE MALLOC FOR MEMORY ALLOCATION */
#include <string.h>         /*IMPORTING THE STRING.h FOR using fgets funtion. It will get the input from user*/
#include <sys/socket.h>     /*IMPORTING IT as it will be used for creating sockets*/
#include <resolv.h>         /*IMPORTING IT TO FIND THE IP address*/
#include <netdb.h>          /*USEFULL for network operations */
#include <openssl/ssl.h>    /*USING openssl function's and certificates and configuring them*/
#include <openssl/err.h>    /*helps in finding out openssl errors*/
#include <arpa/inet.h>      /*IMPORTING FOR converting ascii to network bit*/
#include <sys/types.h>      /*IMPORTING FOR for using sockets*/
#include <netinet/in.h>     /*IMPORTING FOR converting network to asii bit */

#define WORD_SIZE 1024      /*WORD_SIZE for reading messages*/


int Open_Listener(int Port_Num)
{
    int Socket_D;

    struct sockaddr_in Socket_Address;              /*CREATING THE SOCKETS WITH ADDR*/

    Socket_D = socket(PF_INET, SOCK_STREAM, 0);

    bzero(&Socket_Address, sizeof(Socket_Address)); /*free output the garbage space in memory*/

    Socket_Address.sin_family = AF_INET;            /*HERE WE GET IP ADDRESS */

    Socket_Address.sin_port = htons(Port_Num);      /* CONVERSION OF hst bit to n/w bit */

    Socket_Address.sin_addr.s_addr = INADDR_ANY;

    if (bind(Socket_D, (struct sockaddr *)&Socket_Address, sizeof(Socket_Address)) != 0) /* assinging ip with port*/

    {

        perror("can't bind port");                  /* checking for error*/

        abort();                                    /* abort the process if theres is error */
    }

    if (listen(Socket_D, 10) != 0)                  /* Max of 10 clients*/

    {

        perror("Can't configure listening port");   /* checking for error*/

        abort();                                    /*bort the process if theres is error */
    }

    return Socket_D;
}

int is_Root()                                        /*check if root is accesed*/

{

    if (getuid() != 0)

    {

        return 0;
    }

    else

    {

        return 1;                                   /*  */
    }
}

SSL_CTX *Init_ServerCTX(void)                 /*creating and setting up ssl context structure*/

{
    SSL_METHOD *Method_v;

    SSL_CTX *CTX_var;

    OpenSSL_add_all_algorithms();           /* load all SLL ALGO */

    SSL_load_error_strings();               /* load all error messages */

    Method_v = TLSv1_2_server_method();     /* server-method instance new */

    CTX_var = SSL_CTX_new(Method_v);        /* context from method new*/

    if (CTX_var == NULL)

    {

        ERR_print_errors_fp(stderr);

        abort();
    }

    return CTX_var;
}

void Load_Certificates(SSL_CTX *CTX_var, char *Cert_File, char *KeyFile) /* to load a certificate into an SSL_CTX structure*/

{

    /* set the local certificate from Cert_File */

    if (SSL_CTX_use_certificate_file(CTX_var, Cert_File, SSL_FILETYPE_PEM) <= 0)

    {

        ERR_print_errors_fp(stderr);

        abort();
    }

    /* set the private key from KeyFile (may be the same as Cert_File) */

    if (SSL_CTX_use_PrivateKey_file(CTX_var, KeyFile, SSL_FILETYPE_PEM) <= 0)

    {

        ERR_print_errors_fp(stderr);

        abort();
    }

    /* verify private key */

    if (!SSL_CTX_check_private_key(CTX_var))

    {

        fprintf(stderr, "Private key does not match the public certificaten");

        abort();
    }
}

void ShowCerts(SSL *SSL_var) /*show the ceritficates to client and match them*/

{
    X509 *SSL_Certificate;

    char *line;

    SSL_Certificate = SSL_get_peer_certificate(SSL_var); /* Get certificates (if available) */

    if (SSL_Certificate != NULL)

    {

        printf("Server certificates:n");

        line = X509_NAME_oneline(X509_get_subject_name(SSL_Certificate), 0, 0);

        printf("Server: %sn", line); /*server certifcates*/

        free(line);

        line = X509_NAME_oneline(X509_get_issuer_name(SSL_Certificate), 0, 0);

        printf("client: %sn", line); /*client certificates*/

        free(line);

        X509_free(SSL_Certificate);
    }

    else

        printf("No certificates.n");
}

void Serv_let(SSL *SSL_var) /* Serve the connection -- threadable */

{
    char buff[1024];

    int Socket_D, bytes;

    char input[WORD_SIZE];

    pid_t cpid;

    SSL_CTX_set_verify(SSL_get_SSL_CTX(SSL_var), SSL_VERIFY_PEER, NULL);

    if (SSL_accept(SSL_var) == -1) /* do SSL-protocol accept */

        ERR_print_errors_fp(stderr);

    else

    {

        ShowCerts(SSL_var); /* get any certificates */

        /*Fork system call is used to create a new process*/

        cpid = fork();

        if (cpid == 0)

        {

            while (1)
            {

                bytes = SSL_read(SSL_var, buff, sizeof(buff)); /* get request and read message from server*/

                if (bytes > 0)

                {

                    buff[bytes] = 0;

                    printf("\nMESSAGE RECEIVED:%s\n", buff);
                }

                else

                    ERR_print_errors_fp(stderr);
            }
        }

        else
        {

            while (1)
            {

                printf("\nENTER YOUR MESSAGE:");

                fgets(input, WORD_SIZE, stdin); /* get request and reply to client*/

                SSL_write(SSL_var, input, strlen(input));
            }
        }
    }

    Socket_D = SSL_get_fd(SSL_var); /* get socket connection */

    SSL_free(SSL_var); /* release SSL state */

    close(Socket_D); /* close connection */
}

int main(int count, char *strings[]) /* getting port as a argument*/

{
    SSL_CTX *CTX_var;

    int server;

    char *Port_Num;

    if (!is_Root()) /* if root user is not executing server report must be root user */

    {

        printf("This program must be run as root/sudo user!!");

        exit(0);
    }

    if (count != 2)

    {

        printf("Usage: %s n", strings[0]); /*send the usage guide if syntax of setting port is different*/

        exit(0);
    }

    SSL_library_init(); /*load encryption and hash algo's in ssl*/

    Port_Num = strings[1];

    CTX_var = Init_ServerCTX(); /* initialize SSL */

    Load_Certificates(CTX_var, "SSL_Certificate.pem", "SSL_Certificate.pem"); /* load certs */

    server = Open_Listener(atoi(Port_Num)); /* create server socket */

    struct sockaddr_in Socket_Address; /*socket for server*/

    socklen_t len = sizeof(Socket_Address);

    SSL *SSL_var;

    listen(server, 5); /*setting 5 clients at a time to queue*/

    int client = accept(server, (struct sockaddr *)&Socket_Address, &len); /* accept connection as usual */

    printf("Connection: %s:%dn", inet_ntoa(Socket_Address.sin_addr), ntohs(Socket_Address.sin_port)); /*printing connected client information*/

    SSL_var = SSL_new(CTX_var); /* get new SSL state with context */

    SSL_set_fd(SSL_var, client); /* set connection socket to SSL state */

    Serv_let(SSL_var); /* service connection */

    close(server); /* close server socket */

    SSL_CTX_free(CTX_var); /* release context */
}
