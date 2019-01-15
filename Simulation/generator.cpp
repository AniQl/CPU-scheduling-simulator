#include "generator.h"
#include <cmath>

UniformGenerator::UniformGenerator(int kernel): kernel_(kernel)
{
   M = 2147483647.0;
   A = 16807;
   Q = 127773;
   R = 2836;
}

UniformGenerator::~UniformGenerator()
{

}

double UniformGenerator::Rand()
{
   int h = kernel_/Q;
   kernel_ = A*(kernel_-Q*h)-R*h;
   if (kernel_ < 0)
      kernel_ = kernel_ + static_cast<int>(M);
   return kernel_/M;
}

int UniformGenerator::Rand(int start, int end)
{
   return static_cast<int>( ceil( Rand()*(end-start) + start ) );
}

ExpGenerator::ExpGenerator(double lambda, UniformGenerator *ug): lambda_(lambda), uniform_(ug)
{

}

ExpGenerator::~ExpGenerator()
{
   if (uniform_ != nullptr)
      delete uniform_;
}

int ExpGenerator::Rand()
{
   double k = uniform_->Rand();
   return static_cast<int>( ceil( -(1.0/lambda_)*log(k) ) );
}
