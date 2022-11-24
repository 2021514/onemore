#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/resource.h>
#include <math.h>
#include <sched.h>
void countA(){
    for(long long int i=0; i<429496729L; i+=1){
        continue;
    }
}
void countB(){
    for(long long int i=0; i<429496729L; i+=1){
        continue;
    }
}
void countC(){
    for(long long int i=0; i<429496729L; i+=1){
        continue;
    }
}
void* Thr_A(void*p){
    struct sched_param parameters;
    parameters.sched_priority = 0;
    int ret = pthread_setschedparam(pthread_self(), SCHED_OTHER, &parameters);
    printf("%d\n", ret);
    countA();
}
void* Thr_B(void*q){
    struct timespec start, stop;
    //double accum;
    struct sched_param parameters;
    // for(int i=0; i<10; i++){
    parameters.sched_priority = 1;
    int ret = pthread_setschedparam(pthread_self(), SCHED_FIFO, &parameters);
    printf("%d\n", ret);
    clock_gettime( CLOCK_REALTIME, &start );
    countB();
    clock_gettime( CLOCK_REALTIME, &stop );
    printf( "SCHED_FIFO--> %lf\n",((double) (stop.tv_sec - start.tv_sec) + (double) ((stop.tv_nsec - start.tv_nsec)/((double) 1000000000L))));
    clock_gettime( CLOCK_REALTIME, &start );
    
    //}
}
void* Thr_C(void*r){
    struct sched_param parameters;
    parameters.sched_priority = 1;
    int ret = pthread_setschedparam(pthread_self(), SCHED_RR, &parameters);
    printf("%d\n", ret);
    countC();
}
int main( int argc, char **argv ){
    pthread_t A;
    pthread_t B;
    pthread_t C;
    struct timespec start, stop;
    double accum;
    clock_gettime( CLOCK_REALTIME, &start );
    pthread_create(&A, NULL, Thr_A, NULL);
    pthread_join(A, NULL);
    clock_gettime( CLOCK_REALTIME, &stop );
    printf( "SCHED_OTHER--> %lf\n", ((double) (stop.tv_sec - start.tv_sec) + (double) ((stop.tv_nsec - start.tv_nsec)/(double) 1000000000L)) );
    //printf( "%lf\n", ((double) (stop.tv_sec - start.tv_sec))/((double) 100000) );
    //clock_gettime( CLOCK_REALTIME, &start );
    pthread_create(&B, NULL, Thr_B, NULL);
    pthread_join(B, NULL);
    // clock_gettime( CLOCK_REALTIME, &start );
    // sleep(1);
    // pthread_create(&B, NULL, Thr_B, NULL);
    // pthread_join(B, NULL);
    // clock_gettime( CLOCK_REALTIME, &stop );
    // printf( "Time for SCHED_FIFO: %lf\n", ((double) (stop.tv_sec - start.tv_sec))/((double) 100000) );
    // //printf( "%lf\n", ((double) (stop.tv_sec - start.tv_sec))/((double) 100000) );
    // clock_gettime( CLOCK_REALTIME, &start );
    clock_gettime( CLOCK_REALTIME, &start );
    pthread_create(&C, NULL, Thr_C, NULL);
    pthread_join(C, NULL);
    clock_gettime( CLOCK_REALTIME, &stop );
    printf( "SCHED_RR--> %lf\n", ((double) (stop.tv_sec - start.tv_sec) + (double) ((stop.tv_nsec - start.tv_nsec)/1000000000L)));
    //printf( "%lf\n", ((double) (stop.tv_sec - start.tv_sec))/((double) 100000) );
    clock_gettime( CLOCK_REALTIME, &start );
    return 0;
}
