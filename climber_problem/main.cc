#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define H_ARRAYSIZE(a) \
    ((sizeof(a) / sizeof(*(a))) / \
    static_cast<size_t>(!(sizeof(a) % sizeof(*(a)))))

struct node {
	int start;
	int end;
	int height;
};  // the decription of a single trangle

int compare(const int &a, const int &b)
{
	return a >= b ? a : b;
}

int resolve(const char* input)
{
	int count = atoi(input);
	struct node tab[20];
	for (int i = 0; *input != '\0'; ++input)
	{
		if (i < count&&*input == '\n')
		{
			tab[i].start =atoi(input+1);
			tab[i].end = atoi(input + 3);
			tab[i].height = atoi(input + 5);
			++i;
		}
	}
	
	int sum = 0;  // The Result
	int maxend = tab[0].end;

	sum += tab[0].height* 2;

	for (int j = 0; j < count-1;++j)
	{
		if (maxend >= tab[j + 1].start)
		{
			if (tab[j].height<tab[j+1].height)
			{
				sum += (tab[j + 1].height - tab[j].height) * 2;
			}
			maxend = compare(maxend, tab[j + 1].end);
		}
		else {
			sum += tab[j+1].height*2;
			maxend = tab[j + 1].end;
		}
	}

	sum+=tab[count-1].end;
	// printf("This is the element %d + sum: %d \n",tab[count - 1].end,sum);
	return sum;
}

int main(int argc, char* argv[])
{
	const char* input[] = {
		"3\n1,3,2\n2,4,4\n6,7,5\n", //The giving example
		"1\n1,2,1\n",
		"2\n1,2,1\n2,3,2",
		"3\n1,2,1\n2,3,2\n3,6,1",
		"4\n1,2,1\n2,3,2\n3,6,1\n5,8,2",
		"5\n1,2,1\n2,3,2\n3,6,1\n5,8,2\n7,9,1",
		"1\n0,1,1",
		"2\n0,1,1\n2,4,3",
		"3\n0,1,1\n2,4,3\n3,5,1",
		"4\n0,1,1\n2,4,3\n3,5,1\n5,6,1",
		"5\n0,1,1\n2,4,3\n3,5,1\n5,6,1\n6,8,3",
		//TODO please add more test case here
	};
	
	int expectedSteps[] = { 25, 4, 7, 10, 14, 15, 3, 12, 13, 14, 20 };
	for (size_t i = 0; i < H_ARRAYSIZE(input); ++i)
	{
		// resolve(input[i]);
		assert(resolve(input[i]) == expectedSteps[i]);
	}
	printf("Hello");
	// system("pause");
	return 0;
}