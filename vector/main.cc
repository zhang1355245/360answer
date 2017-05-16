#include <stdlib.h>
#include "qh_vector.h"


int main(int argc, char* argv[])
{
    //TODO ��������ӵ�Ԫ���ԣ�Խ��Խ�ã�����·��������ԽȫԽ��
    //TODO ��Ԫ����д����ο�INIParser�Ǹ���Ŀ����Ҫдһ��printf��Ҫ��assert���ж����жϡ�

	qh::vector<int> num_vect(3,5);
	num_vect.push_back(10);
	num_vect.push_back(12);
	num_vect.push_back(14);
	num_vect.pop_back();
	assert(num_vect[num_vect.size()-1]==12);
	num_vect.reserve(42);
	assert(num_vect[num_vect.size() - 1] == 12);
	assert(num_vect[num_vect.size() - 3] == 5);
	num_vect.resize(4);
	assert(num_vect[num_vect.size()-1]==10);

#ifdef WIN32
    system("pause");
#endif

	return 0;
}

