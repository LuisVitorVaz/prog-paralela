#include <omp.h>
#include <sys/queue.h>
#include <omp.h>
#include <math.h>
#include <time.h>
#include <iostream>

class omp_q : public queue<int> {
public:
typedef queue<int> base;
omp_q( ) {
omp_init_lock(&lock);
}
~omp_q() {
omp_destroy_lock(&lock);
}
bool push(const int& value) {
omp_set_lock(&lock);
bool result = this->base::push(value);
omp_unset_lock(&lock);
return result;
}
bool trypush(const int& value)
{
bool result = omp_test_lock(&lock);
if (result) {
result = result && this->base::push(value);
omp_unset_lock(&lock);
}
return result;
}
// likewise for pop
private:
omp_lock_t lock;
};
