#include <torch/torch.h>
#include <torch/script.h>
#include <vector>
#include <algorithm>
#include <ctime>
#include <iostream>
#include <random>
#include <vector>
#include <chrono>
#include <algorithm>

constexpr auto low_bound = 0;
constexpr auto up_bound = 100;

int main()
{
//     std::cout<<"cuda avaiable=>"<<torch::cuda::is_available()<<std::endl;
//     // torch::DeviceType  device_type = torch::kCUDA;
//     torch::DeviceType  device_type = torch::kCPU;

    	torch::DeviceType device_type;
 
		if (torch::cuda::is_available()){
			device_type = torch::kCUDA;
		}else{
			device_type = torch::kCPU;
		}
    torch::Device device(device_type);
    torch::Tensor a = torch::ones({ 2, 2 }, torch::requires_grad());
    torch::Tensor b = torch::randn({ 2, 2 });
    a.to(torch::kCUDA);
    b.to(torch::kCUDA);
    auto c = a + b;
    std::vector<float> test;
    for (int i=0; i<10;i++){test.push_back(i);}
    std::cout<<test<<std::endl;
    auto opts = torch::TensorOptions().dtype(torch::kFloat32);
    auto t_test = torch::from_blob(test.data(),{int64_t(test.size())}, opts).clone().reshape({2,5}).to(device_type);
    std::cout<<"t_test:"<<t_test<<","<<t_test.dim()<<","<<t_test.device()<<std::endl;

    

    // std::cout<<c<<std::endl;
    // std::cout<<c.device()<<","<<a.device()<<","<<std::endl;
    std::unique_ptr< torch::jit::script::Module> module_ptr = std::make_unique< torch::jit::script::Module>(torch::jit::load("/home/kiki/workspace/CTPTrader/app/torch_example/rnn_rb.pt",device));
    std::cout<<"ok\n"<<std::endl;

    std::vector<torch::jit::IValue> inputs;
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();//seed
    std::default_random_engine dre(seed);//engine
    std::uniform_int_distribution<int> di(low_bound,up_bound);//distribution



    std::vector<double> v(720);
    std::generate(v.begin(), v.end(), [&]{ return di(dre);});
    torch::Tensor x = torch::from_blob(v.data(),{2, 120, 6}).to(torch::kCUDA);

    inputs.push_back(x);
    at::Tensor output = module_ptr->forward(inputs).toTensor();
    auto prediction = torch::softmax(static_cast<at::Tensor>(output), 1);
    // auto prediction = torch::softmax(output,1);
    at::Tensor class_id = prediction.argmax(1);
    // long* _p = class_id.data_ptr<long>();
    // std::cout<<"class id=>"<<*_p<<std::endl;
    // auto _class_id = class_id.item<long>();
    
    std::cout << "output:"<<output << '\n';
    std::cout<<"device:"<<output.device()<<std::endl;;

    std::cout << "prediction:"<<prediction << '\n';
    std::cout << "class id:"<<class_id <<","<<class_id.dtype()<<",dim=>"<<class_id.dim()<<'\n';
    int _clf = class_id[0].item().toInt();
    std::cout<<"class output=>"<<_clf<<","<<std::endl;


std::fstream newfile;
char c = ',';
// std::stringstream sstr(config_ptr->Get("strategy","strategy_name","ma"));
std::string token;

    std::vector<double> v_bins;
std::vector<double> v_var;
std::vector<double> v_means;
newfile.open("/home/kiki/workspace/CTPTrader/app/torch_example/tsmodels_rb.txt", std::ios::in);
int line_num = 0; 
if (newfile.is_open()){
  std::string tp;
  while(getline(newfile, tp)){
    std::stringstream sstr(tp);
    while(getline(sstr, token, c)){
      if(line_num==0){
			  v_bins.push_back(std::stod(token));
      }else if (line_num == 1){
        v_means.push_back(std::stod(token));
      }else if (line_num == 2){
        v_var.push_back(std::stod(token));
      }
		}
    line_num ++;
    std::cout<<"\n";
  }
  newfile.close();
}

std::cout<<"all values in v_bins"<<std::endl;
for (auto it =v_bins.begin(); it!=v_bins.end(); ++it ){
  std::cout<<(*it)<<", ";
}
std::cout<<"\n";
std::cout<<"all values in v_var"<<std::endl;
for (auto it =v_var.begin(); it!=v_var.end(); ++it ){
  std::cout<<(*it)<<", ";
}
std::cout<<"\n";
std::cout<<"all values in v_means"<<std::endl;
for (auto it =v_means.begin(); it!=v_means.end(); ++it ){
  std::cout<<(*it)<<", ";
}
std::cout<<"\n";
    return 0;
}
