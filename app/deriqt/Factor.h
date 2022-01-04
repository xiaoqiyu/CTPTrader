#pragma once
#include<boost/circular_buffer.hpp>
#include<vector>

class Factor
{
public:
	Factor(int long_windows, int short_windows):long_windows(long_windows), short_windows(short_windows){
        last_price_circular_ptr.reset(new boost::circular_buffer<double>(long_windows));
    };
	~Factor();
    void update_factor();


private:
	int long_windows;
    int short_windows;
    std::vector<double> last_factor;
    std::unique_ptr<boost::circular_buffer<double>> last_price_circular_ptr;
};

