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

// bip::managed_shared_memory segment(bip::open_or_create, "MySharedMemory", 65536);
// shm::char_alloc char_alloc(segment.get_segment_manager());

class Signal
{
public:
	Signal(const char* shared_memory_name, uint32_t size){
        segmet_ptr.reset(new bip::managed_shared_memory(bip::open_or_create, shared_memory_name, size));
        char_alloc_ptr.reset(new shm::char_alloc(segmet_ptr->get_segment_manager()));
        p_queue = segmet_ptr->find_or_construct<shm::ring_buffer>("queue")();
    }
	~Signal(){}
	void update_signal(){
        srand(time(0));
        char s[64];
        int offset = 0;
        // for(int i = 0; i < 10; i++) {
            //  offset += sprintf(s + offset, "%d,", rand() % 100);
        // }
        double d1 = 3.14;
        offset += sprintf(s+offset, "%f,", d1);
        int v1 = 100;
        offset += sprintf(s+offset, "%d,", v1);
        s[offset - 1] = '\n';//将最后一个逗号换成换行符。
        //  printf(s);
        std::cout<<s<<std::endl;
        p_queue->push(shm::shared_string(s, *char_alloc_ptr));
    };

private:
    std::unique_ptr<bip::managed_shared_memory> segmet_ptr;
    std::unique_ptr<shm::char_alloc> char_alloc_ptr;
    shm::ring_buffer* p_queue;
};


int main()
{
    Signal sig("MySharedMemory", 65536);
    sig.update_signal();
    
    return 0;
}
