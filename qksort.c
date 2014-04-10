#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int partition(void *data, int esize,
		int i, int k, int (*compare)(void *key1, void *key2))
{
	int ret = -1;
	int j = 0;
	void *med = NULL;
	void *tmp = NULL;
	char *ele = (char *)data;

	if((NULL == data)||(0 == esize)||(0 > i)||(0 > k)||(NULL == compare)) {
		ret = -1;
		goto LBL_RET;
	}

	if(i == k) {
		ret = i;
		goto LBL_RET;
	}

	tmp = malloc(esize);
	if(NULL == tmp) {
		ret = -2;
		goto LBL_RET;
	}

	med = malloc(esize);
	if(NULL == med) {
		ret = -3;
		goto LBL_RET;
	}

	j = (i + k)/ 2;
	memcpy(med, &ele[j*esize], esize);

	while(1) {
		while(compare(med, &ele[i*esize]) < 0)
			++i;

		while(compare(med, &ele[k*esize]) > 0)
			--k;

		if(i >= k)
			break;
		else {
			memcpy(tmp, &ele[i*esize], esize);
			memcpy(&ele[i*esize], &ele[k*esize], esize);
			memcpy(&ele[k*esize], tmp, esize);
			++i;
			--k;
		}
	}

	free(med);
	free(tmp);
	ret = k;

LBL_RET:
	return ret;
}

int qksort(void *data, int size, int esize,
		int (*compare)(void *key1, void *key2))
{
	int i = 0;
	int j = 0;
	int k = size - 1;
	int ret = -1;
	char *ele = (char *)data;
	int new_size = 0;

	if((NULL == data)||(0 == size)||(0 == esize)||(NULL == compare)) {
		ret = -1;
		goto LBL_RET;
	}

	while(i < k) {
		j = partition(data, esize, i, k, compare);
		if(j < 0)
			break;

		new_size = j - i + 1;
		qksort(&ele[i*esize], new_size, esize, compare);
		i = j + 1;
	}

	ret = 0;
LBL_RET:
	return ret;
}

int compare_char(void *key1, void *key2)
{
	if(*(char *)key1 > *(char *)key2)
		return 1;
	else if(*(char *)key1 < *(char *)key2)
		return -1;
	else
		return 0;
}

int main(int argc, char *argv[])
{
	int i = 1;
	while(i < argc) {
		printf("%s\n",argv[i]);
		qksort(argv[i], strlen(argv[i]), sizeof(*argv[0]), compare_char);
		printf("%s\n",argv[i]);
      i++;
	}

	return 0;
}
