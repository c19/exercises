#include <stdio.h>
#include <stdlib.h>
/*2. 写几个函数：（1）输入 10 个职工的姓名和职工号；（2）按职工号由小到大顺序排序，
姓名顺序也随之调整；（3）要求输入一个职工号，用折半查找法找出该职工的姓名，从
主函数输入要查找的职工号，输出该职工姓名。*/

struct staff_type
{
	int id;
	char name[64];
};

int cmp(const void *staff1, const void *staff2){
	return ((staff_type *)staff1)->id - ((staff_type *)staff2)->id;
}

void* b_search(void *base, int total, int ele_size, void *target, int(*cmp)(const void *, const void *)){
	int head = 0;
	int tail = total - 1;
	int mid,result;
	while (head <= tail){
		mid = (head + tail)/2;
		result = cmp((char *)base + mid*ele_size, target); // force type cast to eliminate type warnings
		printf("head %d,mid %d, result %d, tail %d\n", head, mid, result, tail);
		if (result > 0)
		{
			tail = mid - 1;
		}
		else if (result < 0)
		{
			head = mid + 1;
		}else{
			return (char *)base + mid*ele_size;
		}
		printf("head %d,mid %d, result %d, tail %d\n", head, mid, result, tail);
		printf("\n");
	}
	return NULL;
}

void input_staff(staff_type *staff){
	scanf("%d %63s", &staff->id, (char *)&staff->name);
}

void output_staff(staff_type *staff, int length){
	for (int i = 0; i < length; ++i)
	{
		printf("&staff.id: %d, &staff.name: %s\n", staff[i].id, staff[i].name);
	}
}

staff_type* get_staff_by_id(staff_type *staff_array, int total, int id){
		staff_type target;
		target.id = id;
		void *result;
		result = (staff_type*)b_search(staff_array, total, sizeof(staff_type), &target, cmp);
		if (result)
			return (staff_type*)result;
		return NULL;
}

int main(int argc, char const *argv[])
{
	#define NUM 3
	staff_type staff[NUM];
	printf("input staff id and name like this:  32124 杨广\n press enter to input each staff\n");
	for (int i = 0; i < NUM; ++i)
	{
		input_staff(&staff[i]);
		printf("&staff.id: %d, &staff.name: %s\n", staff[i].id, staff[i].name);
	}
	qsort(staff, sizeof(staff)/sizeof(staff[0]), sizeof(staff[0]), cmp);
	output_staff(staff, sizeof(staff)/sizeof(staff[0]));
	int id;
	staff_type *target;
	printf("input id to lookup staff\n");
	scanf("%d", &id);
	target = get_staff_by_id(staff, NUM, id);
	if (target != NULL)
	{
		output_staff(target, 1);
	}else{
		printf("NOT FOUND\n");
	}
	return 0;
}

