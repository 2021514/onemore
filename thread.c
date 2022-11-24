#include <pthread.h>
#include <stdio.h>
void *threadA(void *arg){
    char *arr = (char*)arg;
    printf("%s",arr);
}
int main(){
    pthread_t A;
    char[] *s = "Akash";
    pthread_create(&A, NULL, threadA, (void*) s);
    pthread_join(A,NULL);
}