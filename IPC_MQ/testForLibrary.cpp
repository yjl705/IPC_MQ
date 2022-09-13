//
//  queueControl.cpp
//  IPC_MQ
//
//  Created by Jl Y on 9/12/22.
//

#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

using namespace std;

int main()
{
    /*
             IPC_PRIVATE = new message queue
             IPC_EXCL, CREAT = error if existing message queue with same key
             0666 = permissions
     */
    int status = -1;
    
    int qid = msgget(IPC_PRIVATE, IPC_EXCL | IPC_CREAT | 0666);
    string qid_str = to_string(qid);
    static char *arg[] = {(char*)qid_str.c_str(), NULL};
    
    cout << "Message queue id is " << qid << endl;
    
    // Sender
    pid_t sender_pid = fork();
    if (sender_pid == 0)
    {
        cout << "Sender PID: " << getpid() << endl;
        execv("sender", arg);
        exit(0);
    }
    
    // Receiver
    pid_t receiver_pid = fork();
    if (receiver_pid == 0)
    {
        cout << "Receiver PID: " << getpid() << endl;
        execv("receiver", arg);
        exit(0);
    }
    
    wait(&status);
    msgctl(qid, IPC_RMID, NULL); // remove message queue
    exit(0);
}
