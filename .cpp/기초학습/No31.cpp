#include <iostream>
using namespace std;

#define parent  (i >> 1)
#define left	(i << 1)
#define right   (i << 1 | 1)

class User {
public:
	int id;
	int data;

	friend bool operator< (const User& c1, const User& c2)
	{
		if (c1.data < c2.data) return true;
		else if (c1.data == c2.data) {
			if (c1.id > c2.id) return true;
			else return false;
		}
		else return false;
	}
};

int cnt = 0;
User arr[11];

void init()
{
	cnt = 0;
}

void push(int id, int data) {
	arr[++cnt].data = data;
	arr[cnt].id = id;
	for (int i = cnt; parent != 0 && arr[parent].data >= arr[i].data; i >>= 1) {
		if (arr[parent].data == arr[i].data) {
			if (arr[parent].id > arr[i].id) {
				break;
			}
		}
		//swap
		User tmp = arr[parent];
		arr[parent] = arr[i];
		arr[i] = tmp;
	}
}

void pop() {
	arr[1] = arr[cnt--];

	for (int i = 1; left <= cnt;) {
		int child = left == cnt || arr[left] < arr[right] ? left : right;

		if (arr[child] < arr[i]) {
			// swap
			User tmp = arr[child];
			arr[child] = arr[i];
			arr[i] = tmp;
			i = child;
		}
		else {
			break;
		}
	}
}

void addUser(int uID, int income)
{
	if (cnt < 10) push(uID, income);
	else {
		if (arr[1].data < income) {
			pop(); push(uID, income);
		}
		else if (arr[1].data == income) {
			if (arr[1].id > uID) {
				pop(); push(uID, income);
			}
		}
	}
}

int getTop10(int result[10])
{
	User temp[11];

	if (cnt == 1) {
		result[0] = arr[1].id;
		return cnt;
	}

	for (int i = 1; i <= cnt; i++) {
		temp[i - 1].data = arr[i].data;
		temp[i - 1].id = arr[i].id;
	}

	for (int i = 1; i < cnt - 1; i++) {
		User tmp = temp[i];
		int j;
		for (j = i - 1; j >= 0 && temp[j].data <= tmp.data; j--) {
			temp[j + 1] = temp[j];
		}
		temp[j + 1] = tmp;
	}
	for (int i = 0; i < cnt; i++) result[i] = temp[i].id;

	return cnt;
}