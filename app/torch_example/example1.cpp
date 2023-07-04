#include <torch/torch.h>

int main()
{
    torch::Tensor a = torch::ones({ 2, 2 }, torch::requires_grad());
    torch::Tensor b = torch::randn({ 2, 2 });
    a.to(torch::kCUDA);
    b.to(torch::kCUDA);
    auto c = a + b;
    return 0;
}
