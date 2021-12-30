#include<boost/circular_buffer.hpp>
#include <iostream>
int main()
{
    boost::circular_buffer<int> cb(3);
    cb.push_back(1);
    cb.push_back(2);
    cb.push_back(3);
    cb.push_back(4);

    // assert(cb[0]==1);
    // assert(cb[1]==2);
    std::cout<<cb[0]<<","<<cb[1]<<","<<cb[2]<<std::endl;
    
    // int sum = std::accumulate(cb.begin(), cb.end(), 0);

    // assert(cb.full());
    // std::cout<<cb.capacity()<<std::endl;
    return 0;
}


