//
//  sender.cpp
//  IPC_MQ
//
//  Created by Jl Y on 9/12/22.
//

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "message.h"

using namespace std;

int main(int argc, char **argv)
{
    Message msg; // message buffer
    int size = sizeof(msg) - sizeof(long); // size of contenr
    string inputMsg = "";
    msg.msgType = 1;
    int qid = stoi(argv[0]);
    
    cout << "PID of sender is " << getpid() <<endl;
    cout << "ENter a message: " << endl;
    cin >> msg.content;
    
//    strcpy(msg.content, inputMsg.c_str()); // copy input to message contenr
    msgsnd(qid, (struct msgbuf*)&msg, size, 0); // send message
    cout << "A message has been sent from " << getpid() << endl;
    
    exit(0);
}

