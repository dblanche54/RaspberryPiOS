unsigned int printA(){
	for (;;){
		osc_print_string("A", 2);
		osc_sleep(1000);
	}
	return 0;
}


unsigned int printB(){
	for(;;){
		osc_print_string("B", 2);
		osc_sleep(1000);
	}
	return 0;
}

unsigned int pidTalk(){
	unsigned int childPid;
	char sending[] = "Sending Message";
	char recieved[] = "Recieved Message";
	char message[] = "Parent Message";
	char *recievedMessage;
	int *recievedSize;
	
	childPid = osc_create_process(pidTalkChild);
	
	osc_send(childPid, (void*)message, 15, recievedMessage, recievedSize);

}

unsigned int pidTalkChild(){
	unsigned int parentPid;
	char sending[] = "Sending Message";
	char recieved[] = "Recieved Message";
	char message[] = "Child Message";
	char *recievedMessage;
	int *recievedSize;
	
	parentPid = osc_getppid();
	
	osc_recieve(parentPid, recievedMessage, recievedSize);
	osc_reply(parentPid, message, 14)

}
