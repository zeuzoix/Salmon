#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int mgsort(void *data, int size, int esize,
		int (*compare)(void *key1, void *key2))
{
	int ret = -1;
	int mid = 0;
	int ret_left = -1;
	int ret_right = -1;
	char *tmp = NULL;
	char *data_ptr = (char *)data;
	int i = 0;
	int j = 0;
	int k = 0;

	if((NULL == data)||(0 >= size)||(0 >= esize)||(NULL == compare)) {
		ret = -1;
		goto LBL_RET;
	}

	if(1 == size) {
		ret = 0;
		goto LBL_RET;
	}

	mid = size / 2;
	ret_left = mgsort(data, mid, esize, compare);
	if(0 != ret_left) {
		ret = -2;
		goto LBL_RET;
	}

	ret_right = mgsort(((char *)data + mid*esize), (size - mid), esize,
				compare);
	if(0 != ret_right) {
		ret = -2;
		goto LBL_RET;
	}

	tmp = (char *)malloc(size * esize);
	if(NULL == tmp) {
		ret = -3;
		goto LBL_RET;
	}

	i = 0;
	j = mid;
	k =0;

	while((i < mid) && (j < size)) {

		if(0 < compare(&data_ptr[i * esize], &data_ptr[j * esize])) {
			memcpy(&tmp[k * esize], &data_ptr[i * esize], esize);
			++i;
		}
		else {
			memcpy(&tmp[k * esize], &data_ptr[j * esize], esize);
			++j;
		}
		++k;
	}

	if(i >= mid) {
		while(j < size) {
			memcpy(&tmp[k * esize], &data_ptr[j * esize], esize);
			++j;
			++k;
		}
	}

	if(j >= size) {
		while(i < mid) {
			memcpy(&tmp[k * esize], &data_ptr[i * esize], esize);
			++i;
			++k;
		}
	}

	memcpy(data_ptr, tmp, (size * esize));

	free(tmp);
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
		mgsort(argv[i], strlen(argv[i]), sizeof(*argv[0]),
				compare_char);
		printf("%s\n",argv[i]);
      i++;
	}

	return 0;
}
