// #include<boost/circular_buffer.hpp>
#include <iostream>
#include <vector>
#include<memory>
#include <vector>
#include <string>
#include <sstream>
#include <cstring>
#include <unordered_map>
#include <fstream>
#include <stdio.h>
#include <unistd.h>


int main()
{
    // std::vector<double> v_factor;
    // v_factor.push_back(1.2);

    // std::vector<double> v_factor1;
    // v_factor1.push_back(2.1);
    // v_factor1.push_back(3.4);
    // std::cout<<v_factor[0]<<std::endl;
    // std::cout<<"After:"<<std::endl;
    // v_factor.clear();
    // v_factor.assign(v_factor1.begin(),v_factor1.end());
    // v_factor = v_factor1;
    // std::cout<<v_factor[0]<<","<<v_factor[1]<<std::endl;
    // boost::circular_buffer<int> cb(3);
    // cb.push_back(1);
    // cb.push_back(2);
    // cb.push_back(3);
    // cb.push_back(4);

    // assert(cb[0]==1);
    // assert(cb[1]==2);
    // std::cout<<cb[0]<<","<<cb[1]<<","<<cb[2]<<std::endl;
    // std::cout<<cb.front()<<","<<cb.back()<<std::endl;
    // std::cout<<cb[0]<<","<<cb[1]<<","<<cb[2]<<std::endl;
    // int sum = std::accumulate(cb.begin(), cb.end(), 0);

    // assert(cb.full());
    // std::cout<<cb.capacity()<<std::endl;
    // char *rr = get_chars();
    // std::cout<<rr<<std::endl;

    //share_ptr demo
    std::shared_ptr<int> p1 = std::make_shared<int>();
    *p1 = 78;
    std::cout<< "*p1="<<*p1<<std::endl;

    std::cout<<"p1 reference count="<<p1.use_count()<<std::endl;
    std::shared_ptr<int> p2(p1);
    std::cout<<"p2 ref count="<<p2.use_count()<<std::endl;
    std::cout<<"p1 ref count="<<p1.use_count()<<std::endl;
//  

    void * p3 = reinterpret_cast<void*>(p1.get());
    std::shared_ptr<int> p4(reinterpret_cast<std::shared_ptr<int>(p3));
    

    if(p1==p2){
        std::cout<<"p1 and p2 pnt to same pointer\n";
    }
    // std::cout<<"p3:p1"<<p3<<","<<p1<<","<<p3.use_count()<<std::endl;
//  
    // std::cout<<"reset p1"<<std::endl;
    // p1.reset();
    // std::cout<<"p1 ref cnt="<<p1.use_count()<<std::endl;
// 
    // p1.reset(new int(11));
    // std::cout<<"p1 ref cnt="<<p1.use_count()<<std::endl;
// 
    p1 = nullptr;
    std::cout<<"p1 ref cnt="<<p1.use_count()<<","<<p1<<std::endl;
// 
    if(!p1){
        std::cout<<"p1 is null"<<std::endl;
    }
// 
    std::cout<<*p2<<","<<p2<<p2.use_count()<<std::endl;
    p2 = nullptr;
    std::cout<<p2<<p2.use_count()<<std::endl;
    return 0;
}


