#include <stdio.h>
#include <sys/time.h>

int binsearch(int x, int v[], int n);
int binsearchUpgrade(int x, int v[], int n);

int binsearch(int x, int v[], int n) {
	int low, high, mid;

	low = 0;
	high = n - 1;
	while(low <= high) {
		mid = (low + high) / 2;
		if(x < v[mid])
			high = mid - 1;
		else if(x > v[mid])
			low = mid + 1;
		else
			return mid;
	}
	return -1;
}

int binsearchUpgrade(int x, int v[], int n) {
	int low, high, mid;

	low = 0;
	high = n - 1;
	while(low <= high) {
		mid = (low + high) / 2;
		if(x < v[mid])
			high = mid - 1;
		else
			low = mid + 1;
	}
	if(v[mid] == x)
		return mid;
	else if(v[low] == x)
		return low;
	else if(v[high] == x)
		return high;
	return -1;
}

int main() {
	int v[1000000];
	int n = 1000000;
	int x = 436281;
	struct timeval stop, start;

	for(int i=0; i < n; i++)
		v[i] = i+1;

	gettimeofday(&start, NULL);
	printf("%d's location is %d\n", x, binsearch(x, v, n));
	gettimeofday(&stop, NULL);
	printf("time 1:%lu\n", (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec);

	gettimeofday(&start, NULL);
	printf("%d's location is %d\n", x, binsearchUpgrade(x, v, n));
	gettimeofday(&stop, NULL);
	printf("time 2:%lu\n", (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec);
	
	return 0;
}
