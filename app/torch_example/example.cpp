#include <torch/torch.h>
#include <torch/script.h>
#include <iostream>
#include <memory>
#include <fstream>
#include <string>

int main() {
  // torch::Tensor tensor = torch::rand({2, 3});
  // tensor = tensor.cuda();
  // std::cout << tensor << std::endl;
  // std::shared_ptr<torch::jit::script::Module> module = torch::jit::load("model.pt");
  // torch::jit::script::Module module = torch::jit::load("/home/kiki/workspace/CTPTrader/app/torch_example/rnn_rb.pt");
  
  // assert(module != nullptr);
  
  
  std::unique_ptr< torch::jit::script::Module> module_ptr = std::make_unique< torch::jit::script::Module>(torch::jit::load("/home/kiki/workspace/CTPTrader/app/torch_example/rnn_rb.pt"));
  std::cout<<"ok\n"<<std::endl;
  std::vector<torch::jit::IValue> inputs;
  inputs.push_back(torch::rand({2, 120, 6}));
  at::Tensor output = module_ptr->forward(inputs).toTensor();
  std::cout << output << '\n';
  // at::Tensor _pred = module.predict(inputs).toTensor();
  // std::cout << _pred << '\n';
  std::cout<<"device:"<<output.device();


  /*
  // Create a vector of inputs(model.pt)
std::vector<torch::jit::IValue> inputs;
inputs.push_back(torch::ones({20}));
// Execute the model and turn its output into a tensor.model.pt
at::Tensor output = module.forward(inputs).toTensor();
std::cout << output << '\n';
*/
std::fstream newfile;
char c = ',';
// std::stringstream sstr(config_ptr->Get("strategy","strategy_name","ma"));
std::string token;
		// while(getline(sstr, token, c)){
		// 	v_strategy_name.push_back(token);
		// }
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