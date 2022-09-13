//
//  testForManualBuild.cpp
//  IPC_MQ
//
//  Created by Jl Y on 9/13/22.
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
#include "message.h"

using namespace std;

MsgQ q;
pthread_mutex_t msgmutex = PTHREAD_MUTEX_INITIALIZER;

void *test_sender(void *arg)
{
    Message msg; // message buffer
//    int size = sizeof(msg);
    string inputMsg = "";
    msg.msgType = 1;
    int qid = 1333;
    
    while (true)
    {
//        cout << "PID of sender is " << getpid() <<endl;
        cout << "Enter a message: " << endl;
        cin >> msg.content;
        pthread_mutex_lock( & msgmutex);
        q.send(qid, msg);
        pthread_mutex_unlock( & msgmutex);
        usleep(2000000);
    }
}

void *test_receiver(void *arg)
{
    Message msg;
    int qid = 1333;
    int readed_idx = 0;
    while (true){
        if (q.isEmpty(readed_idx)) {
            usleep(2000000);
            continue;
        }
        pthread_mutex_lock( & msgmutex);
        readed_idx = q.receive(qid, msg, readed_idx);
//        cout << "Receive message for " << getpid() << endl;
        cout << "Receive message: " << msg.content << endl;
        pthread_mutex_unlock( & msgmutex);
        usleep(2000000);
    }
}

int main()
{
    pthread_t thr;
     
    // Create threads
    if (pthread_create( & thr, NULL, test_sender, NULL) ||
            pthread_create( & thr, NULL, test_receiver, NULL))
        {
            cout << " cannot make thread\n";
            exit(1);
        }
     
    cout << "** Main thread ends **\n";
    pthread_exit((void * )0);
}
