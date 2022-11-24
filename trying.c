#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/resource.h>
#include <math.h>
#include <sched.h>
double time_FIFO[10];
int priorities_FIFO[10];
double time_RR[10];
int priorities_RR[10];
void countA(){
    for(long long int i=1; i<429496729L; i+=1){
        //continue;
    }
}
void countB(){
    for(long long int i=1; i<429496729L; i+=1){
        //continue;
    }
}
void countC(){
    for(long long int i=1; i<429496729L; i+=1){
        //continue;
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
    struct sched_param parameters;
    parameters.sched_priority=0;
    for(int i=0; i<10; i++){
    struct timespec start, stop;
    parameters.sched_priority+=6;
    priorities_FIFO[i] = parameters.sched_priority;
    int ret = pthread_setschedparam(pthread_self(), SCHED_FIFO, &parameters);
    printf("%d\n", ret);
    clock_gettime( CLOCK_REALTIME, &start );
    countB();
    clock_gettime( CLOCK_REALTIME, &stop );
    time_FIFO[i] = (double) (stop.tv_sec - start.tv_sec) + (double) ((stop.tv_nsec - start.tv_nsec)/(double) 1000000000L);
    printf( "SCHED_FIFO for priority[%d]--> %lf\n", parameters.sched_priority,((double) (stop.tv_sec - start.tv_sec) + (double) ((stop.tv_nsec - start.tv_nsec)/(double) 1000000000L)) );
    }
    printf("\n");
}
void* Thr_C(void*r){
    struct sched_param parameters;
    parameters.sched_priority=0;
    for(int i=0; i<10; i++){
    struct timespec start, stop;
    parameters.sched_priority+=8;
    priorities_RR[i] = parameters.sched_priority;
    int ret = pthread_setschedparam(pthread_self(), SCHED_RR, &parameters);
    printf("%d\n", ret);
    clock_gettime( CLOCK_REALTIME, &start );
    countC();
    clock_gettime( CLOCK_REALTIME, &stop );
    time_RR[i] = ((double) (stop.tv_sec - start.tv_sec) + (double) ((stop.tv_nsec - start.tv_nsec)/(double) 1000000000L));
    printf( "SCHED_RR for priority[%d]--> %lf\n", parameters.sched_priority,((double) (stop.tv_sec - start.tv_sec) + (double) ((stop.tv_nsec - start.tv_nsec)/(double) 1000000000L)) );
    }
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
    
    
    pthread_create(&B, NULL, Thr_B, NULL);
    pthread_join(B, NULL);


    pthread_create(&C, NULL, Thr_C, NULL);
    pthread_join(C, NULL);
    
    
    printf("---------------VALUES----------------\n");
    for (int i=0; i<10; i++){
        printf("%d--->%lf\n",priorities_FIFO[i],time_FIFO[i]);
    }
    printf("\n");
    // for (int i=0; i<10; i++){
    //     printf("%d\n",priorities_FIFO[i]);
    // }
    // printf("\n");
    for (int i=0; i<10; i++){
        printf("%d--->%lf\n",priorities_RR[i],time_RR[i]);
    }
    printf("\n");
    // for (int i=0; i<10; i++){
    //     printf("%d\n",priorities_RR[i]);
    // }
    FILE *fp;
    FILE *ptr;
    fp = fopen("FIFO.txt", "w");
    ptr = fopen("RR.txt","w");
    for (int i=0; i<10; i++){
        fprintf(fp,"%d %lf\n",priorities_FIFO[i],time_FIFO[i]);
    }
    printf("\n");
    for (int i=0; i<10; i++){
        fprintf(ptr,"%d %lf\n",priorities_RR[i],time_RR[i]);
    }
    fclose(fp);
    fclose(ptr);
    return 0;
}