#include<iostream>
#include<vector>
#include <thread>
#include<cstring>
#include <stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include "gmtrade_def.h"
#include "gmtrade.h"
#include "GMSimTrader.h"
#include <fstream>
#include <glog/logging.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <unistd.h>

#include <boost/lockfree/spsc_queue.hpp> // ring buffer

#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/containers/string.hpp>


namespace bip = boost::interprocess;
namespace shm
{
    typedef bip::allocator<char, bip::managed_shared_memory::segment_manager> char_alloc;
    typedef bip::basic_string<char, std::char_traits<char>, char_alloc >      shared_string;

    typedef boost::lockfree::spsc_queue<
        shared_string, 
        boost::lockfree::capacity<200> 
    > ring_buffer;
}

int main(int argc, char *argv[])
{      
    if (argc < 2) return 0;
    if (argv[1] == "p")
    {
        // create segment and corresponding allocator
        bip::managed_shared_memory segment(bip::open_or_create, "MySharedMemory", 65536);
        shm::char_alloc char_alloc(segment.get_segment_manager());

        // Ringbuffer fully constructed in shared memory. The element strings are
        // also allocated from the same shared memory segment. This vector can be
        // safely accessed from other processes.
        shm::ring_buffer *queue = segment.find_or_construct<shm::ring_buffer>("queue")();

        const char* messages[] = { "hello world", "the answer is 42", "where is your towel", 0 };

        for (const char** msg_it = messages; *msg_it; ++msg_it)
        {
            sleep(1);
            queue->push(shm::shared_string(*msg_it, char_alloc));
        }
    }else if (argv[1] == "c"){
        // create segment and corresponding allocator
        bip::managed_shared_memory segment(bip::open_or_create, "MySharedMemory", 65536);
        shm::char_alloc char_alloc(segment.get_segment_manager());

        shm::ring_buffer *queue = segment.find_or_construct<shm::ring_buffer>("queue")();

        while (true)
        {
            shm::shared_string v(char_alloc);
            if (queue->pop(v))
            std::cout << "Processed: '" << v << "'\n";
        }
    }else{
        return 0;
    }


    return 0;
}
