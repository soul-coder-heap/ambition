#include "simple_socket_server.h"
//#include "simple_socket_block_server.h"
//#include "simple_socket_noblock_server.h"
//#include "signal.h"
//#include "muti_thread_signal.h"
//#include "async_signal.h"
//#include "threadpool_signal.h"
int main(){
    simple_run(0, nullptr);
    //select_run();
    //block_server();
    //noblock_server();
    //apollo::cyber::base::run_signal();
    //apollo::cyber::base::muti_signal_run();
    //apollo::cyber::base::async_run_signal();
    //apollo::cyber::base::threadpool_run_signal();
    return 0;
}
