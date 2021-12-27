
#include <boost/interprocess/mapped_region.hpp>
#include <cstring>
#include <cstdlib>
#include <string>
#include <iostream>
#include <stdio.h>
#include <string.h>
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

class Signal
{
public:
	Signal(const char* shared_memory_name, uint32_t size){
        segmet_ptr.reset(new bip::managed_shared_memory(bip::open_or_create, shared_memory_name, size));

        char_alloc_ptr.reset(new shm::char_alloc(segmet_ptr->get_segment_manager()));
        p_queue = segmet_ptr->find_or_construct<shm::ring_buffer>("queue")();
        std::cout<<"after init------------------------"<<std::endl;
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
// 
   
int main(){

   if (fork() == 0)//child
   {
      // create segment and corresponding allocator
      bip::managed_shared_memory segment(bip::open_or_create, "mem", 65536);
      shm::char_alloc char_alloc(segment.get_segment_manager());

      shm::ring_buffer *queue = segment.find_or_construct<shm::ring_buffer>("queue")();

      while (true)
      {
          shm::shared_string v(char_alloc);
          if (queue->pop(v))
              std::cout << "Processed: '" << v << "'\n";
              std::cout<<v.find(',')<<std::endl;

      }
   }else//parent
   {
      Signal sig("mem", 65536);
      sig.update_signal();
   }
   return 0;
}