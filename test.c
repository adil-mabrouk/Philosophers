#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t	mtx;
int x = 0;

void*	routine()
{
	int i = 0;
	pthread_mutex_lock(&mtx);
	while (i++ < 1000000)
	{
		x++;
	}
	// printf("test from Threads\n");
	// sleep(3);
	// printf("Ending Thread\n");
	pthread_mutex_unlock(&mtx);
	return (NULL);
}

int main()
{
	pthread_t	t1, t2;
	pthread_create(&t1, NULL, &routine, NULL);
	pthread_create(&t2, NULL, &routine, NULL);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	printf("%d", x);
	return 0;
}