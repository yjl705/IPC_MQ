//
//  message.h
//  IPC_MQ
//
//  Created by Jl Y on 9/12/22.
//
// Information type
#include <string>
#include <cstring>

using namespace std;


struct Message
{
    long msgType; // messsage type
    string content; // message content
    
};

class MsgQ
{
public:
    void send(int qid, Message msg){
        MsgBlock& header = blk[written_idx];
        header.qid = qid;
        header.msg.msgType = msg.msgType;
        swap(header.msg.content, msg.content);
        written_idx += 1;
    }
    
    int receive(int qid, Message& msg, int readed_idx){
        for (int idx = readed_idx; idx < maxSize; idx++){
            MsgBlock& header = blk[idx];
            if (header.qid == qid){
                msg.content = header.msg.content;
                return idx + 1;
            }
        }
        return readed_idx;
    }
    
    bool isEmpty(int readed_idx){
        return written_idx <= readed_idx;
    }

private:
    struct MsgBlock
    {
        int qid;
        Message msg;
    };
    const static int maxSize = 10000;
    MsgBlock blk[maxSize]; // Assume needs at most 10000 blocks
    alignas(64) int written_idx = 0;
    
};
