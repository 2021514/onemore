// #include <stdio.h>
// #include <pthread.h>
// #include <string.h>
// void *foo(void *str){
//     char *new = (char*)str;
//     printf("String is: %s",new);
//     // pthread_exit(NULL);
//     return 0;
// }
// int main(void){
//     pthread_t t;
//     char *s = "Akash Kushwaha";
//     pthread_create(&t, NULL, foo, (void*)s);
//     int* ptr;
//     pthread_join(t, NULL);
// }
#include <pthread.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>
#include <time.h>

void* thread(void* args){
    struct sched_param parameters;
    parameters.sched_priority = 0;
    int ret = pthread_setschedparam(pthread_self(), SCHED_OTHER, &parameters);
    printf("%d\n", ret);
    return NULL;
}


int main(){
    pthread_t t1;
    

    pthread_create(&t1, NULL, thread, NULL);
    pthread_join(t1, NULL);
}