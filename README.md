# IPC_MQ
Using C++ to build a message queue for IPC

1. Use existed library to build message queue. Please use commands below to run the code.
g++ -std=c++11 -o receiver IPC_MQ/receiver.cpp 
g++ -std=c++11 -o sender IPC_MQ/sender.cpp 
g++ -std=c++11 -o test1 IPC_MQ/testForLibrary.cpp 
./test1

2. Manually build a simple message queue. Please use commands below to run the code.
g++ -std=c++11 -o test2 IPC_MQ/testForManualBuild.cpp
./test2
