#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define LISTEN_PORT 9000
#define SERVER_IP "127.0.0.1"

int main( int argc, char *argv[] )
{
	int port = LISTEN_PORT;		/* set the port default value as LISTEN_PORT */
	char ip[16] = SERVER_IP;	/* set the ip default value as SERVER_IP */
	int conn_fd;			/* define connect fd */
	struct sockaddr_in server_addr;
	char buf[64];
	int n, ret;

	/* get the server ip from command line argv[1] */
	if( argc >= 2 ) {
		strncpy( ip, argv[1], 16 );
    }

	/* get the server port from command line argv[2] */
	if( argc >= 3 )
		port = atoi( argv[2] );

	printf( "client begin to connect server %s:%d \n", ip, port );
	
	/* create connect socket */
	conn_fd = socket( AF_INET,SOCK_STREAM, 0);

	/* fill in the struct */
	bzero( &server_addr, sizeof(server_addr) );
	server_addr.sin_family = AF_INET;
	inet_pton( AF_INET, ip, &server_addr.sin_addr );
	server_addr.sin_port = htons( port );

	/* connect to server listen port */
	ret = connect( conn_fd, (struct sockaddr *)&server_addr, sizeof(server_addr) );
	if( ret >= 0 )
    {
		printf( "server is connected! \n" );
    }
    else
	{
		printf( "server is NOT connected! \n" );
		exit( 0 );
	}

	while( 1 )
	{
		fgets( buf, 32, stdin );
		write( conn_fd, buf, strlen(buf) );
		
        sleep(3);
		
        n = read( conn_fd, buf, sizeof(buf) );
		if( n > 0 )
		{
			buf[n] = '\0';
			printf( "From Server: %s \n", buf );
		}
	}

#if 0
	/* server begin to listen */
	listen( listen_fd, 8 );
	printf( "server is listening at port: %d \n", port );
	
  	while( 1 )
	{
		client_addr_len = sizeof( client_addr );
		conn_fd = accept( listen_fd, (struct sockaddr *)&client_addr, &client_addr_len );

	}
#endif
	return 0;
}
