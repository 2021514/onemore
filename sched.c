#include <pthread.h>
#include <stdio.h>
int main(void){
int	pthread_attr_setschedpolicy(pthread_attr_t *tattr, int policy);

pthread_attr_t tattr;
int policy;
int ret;

/* set the scheduling policy to SCHED_OTHER */
ret = pthread_attr_setschedpolicy(&tattr, SCHED_OTHER);
printf("%d\n",ret);}
