//
//  reader.cpp
//  IPC_MQ
//
//  Created by Jl Y on 9/18/22.
//

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <string.h>
#include <errno.h>
#include <iostream>

using namespace std;

const int ID = 1;

int main(int argc, char const *argv[]){
    key_t key = ftok("", ID);
    
    int shmid;
    if((shmid=shmget(key,1024,0666|IPC_CREAT))==-1) exit(1);
    
    char* shm = (char*)shmat(shmid, (void*)0, 0);
    cout << shm << endl;
    
    // disconnect
    shmdt(shm);
    // remove shared memory
    shmctl(shmid,IPC_RMID,NULL);
    
    
    return 0;
}
