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

#include <unistd.h>
#include<iostream>

class Signal
{
public:
	Signal(){
        bip::managed_shared_memory segment(bip::open_or_create, "SignalMemory", 65536);
        this->p_char_alloc = shm::char_alloc(segment.get_segment_manager());
        this->p_queue = segment.find_or_construct<shm::ring_buffer>("queue")();
    };
	~Signal();
	void update_signal(){};

private:
	// bip::managed_shared_memory segment(bip::open_or_create, "SignalMemory", 65536);
    shm::char_alloc * p_char_alloc;
    shm::ring_buffer *p_queue;
};


int main()
{
    // create segment and corresponding allocator
    bip::managed_shared_memory segment(bip::open_or_create, "MySharedMemory", 65536);
    shm::char_alloc char_alloc(segment.get_segment_manager());

    // Ringbuffer fully constructed in shared memory. The element strings are
    // also allocated from the same shared memory segment. This vector can be
    // safely accessed from other processes.
    shm::ring_buffer *queue = segment.find_or_construct<shm::ring_buffer>("queue")();

    const char* messages[] = { "hello world", "the answer is 42", "where is your towel", 0 };
    
     srand(time(0));
     char s[64];
     int offset = 0;
     for(int i = 0; i < 10; i++) {
          offset += sprintf(s + offset, "%d,", rand() % 100);
     }
     s[offset - 1] = '\n';//将最后一个逗号换成换行符。
    //  printf(s);
     std::cout<<s<<std::endl;

    for (const char** msg_it = messages; *msg_it; ++msg_it)
    {
        sleep(1);
        queue->push(shm::shared_string(*msg_it, char_alloc));
    }
       
    queue->push(shm::shared_string(s, char_alloc));
}
