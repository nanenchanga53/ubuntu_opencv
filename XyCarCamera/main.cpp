#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

#include <opencv2/opencv.hpp>
#include <iostream>

#define PORT 9005
#define BUF_LEN 1024

int serverFd;
int clientFd;

using namespace cv;
using namespace std;


int main()
{
	char buf[BUF_LEN];
	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;
	int ret=0, count;
	socklen_t len;	
	    
	/***************** socket ***********************/
	if((serverFd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("server socket error\n");
		return -1;
	}

	/******************** bind ************************/
	int opt = 1;
	setsockopt(serverFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)); 

	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(PORT);

	if(bind(serverFd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
	{
		printf("server bind error\n");
		return -1;
	}

	/******************** listen **********************/
	if(listen(serverFd,1) < 0)
	{
		printf("server listen error\n");
		return -1;
	}
        
	printf("ready\n");
	
	/*************** accept ******************/
	len = sizeof(client_addr);
	clientFd = accept(serverFd, (struct sockaddr*)&client_addr, &len);
	if(clientFd < 0)
	{
		printf("accept fail\n");
		return -1;
	}
	else
	{		
		printf("done\n");		
	}
	sleep(1);
	
	Mat img_color;

	VideoCapture cap(0);
	if (!cap.isOpened()) {
		cerr << "error cam";
		return -1;
	}

	
	while(1)
	{
		cap.read(img_color);
		if (img_color.empty()) {
			cerr << "capt empty";
			break;
		}
		printf("%d,%d,%d,%d\n", img_color.size().width, img_color.size().height, img_color.total(), img_color.elemSize());
						
		if((write(clientFd, img_color.data, img_color.total()*img_color.elemSize())) < 0)
		{	
			printf("#client stop\n");
			exit(-1);
		}
		
		imshow("Color", img_color);
		
		if (waitKey(25) >= 0)
			break;
	}
	

	return 0;
}