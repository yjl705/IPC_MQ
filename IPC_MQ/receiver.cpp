//
//  receiver.cpp
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
    Message msg;
    int size = sizeof(msg) - sizeof(long);
    int qid = stoi(argv[0]);
    
    msgrcv(qid, (struct msgbuf*)&msg, size, 1, 0);
    cout << "Receive message for " << getpid() << endl;
    cout << "Receive message: " << msg.content << endl;
    
    exit(0);
}
