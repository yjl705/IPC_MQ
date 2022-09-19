//
//  sender.cpp
//  IPC_MQ
//
//  Created by Jl Y on 9/18/22.
//

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <string>
#include <errno.h>
#include <iostream>


using namespace std;

//const string PATH = "";
const int ID = 1;

int main(int argc, char const *argv[]){
    key_t key = ftok("", ID);
    
    int shmid;
    if((shmid=shmget(key,1024,0666|IPC_CREAT))==-1) exit(1);
    
    void *shm = shmat(shmid, (void*)0, 0);
    if(shm == (void*)-1){
        fprintf(stderr, strerror(errno));
    }
    
    char data[] = "test";
    strcpy((char*)shm, data);
    
    shmdt(shm);
    
    
    
    return 0;
}
