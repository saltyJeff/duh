#ifdef LOCAL_DBG
#include "local_utils.h"
#endif
int main() {
    #ifdef LOCAL_DBG
    testSuite();
    #endif
}