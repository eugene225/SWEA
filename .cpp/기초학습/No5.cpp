#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MAX_NODE 10000

enum { ADD_HEAD = 1, ADD_TAIL, ADD_NUM, FIND, REMOVE, PRINT, PRINT_REVERSE, END = 99 };

extern void init();
extern void addNode2Head(int data);
extern void addNode2Tail(int data);
extern void addNode2Num(int data, int num);
extern int findNode(int data);
extern void removeNode(int data);
extern int getList(int output[MAX_NODE]);
extern int getReversedList(int output[MAX_NODE]);

static void run() {
	while (1) {
		int cmd, data, num, cnt, i = 0;
		int output[MAX_NODE] = { 0 };

		scanf("%d", &cmd);
		switch (cmd) {
		case ADD_HEAD: // 1
			scanf("%d", &data);
			addNode2Head(data);
			break;
		case ADD_TAIL: // 2
			scanf("%d", &data);
			addNode2Tail(data);
			break;
		case ADD_NUM: // 3
			scanf("%d %d", &data, &num);
			addNode2Num(data, num);
			break;
		case FIND: // 4
			scanf("%d", &data);
			num = findNode(data);
			printf("%d\n", num);
			break;
		case REMOVE: // 5
			scanf("%d", &data);
			removeNode(data);
			break;
		case PRINT: // 6
			cnt = getList(output);
			while (cnt--)
				printf("%d ", output[i++]);
			printf("\n");
			break;
		case PRINT_REVERSE: // 7
			cnt = getReversedList(output);
			while (cnt--)
				printf("%d ", output[i++]);
			printf("\n");
			break;
		case END:
			return;
		}
	}
}

int main(void) {
	//setbuf(stdout, NULL);
	//freopen("dll_input.txt", "r", stdin);

	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		printf("#%d\n", t);
		init();
		run();
		printf("\n");
	}

	return 0;
}

#define MAX_NODE 10000

struct Node {
	int data;
	Node* prev;
	Node* next;
};

Node node[MAX_NODE];
int nodeCnt;
Node* head;
Node* tail;

Node* getNode(int data) {
	node[nodeCnt].data = data;
	node[nodeCnt].prev = nullptr;
	node[nodeCnt].next = nullptr;
	return &node[nodeCnt++];
}

void init()
{
	nodeCnt = 0;
	head = getNode(-1);
	tail = getNode(-1);
	head->next = tail;
	tail->prev = head;
}

void addNode2Head(int data)
{
	Node* newNode = getNode(data);

	newNode->next = head->next;
	head->next->prev = newNode;
	newNode->prev = head;
	head->next = newNode;
}

void addNode2Tail(int data)
{
	Node* newNode = getNode(data);
	newNode->next = tail;
	newNode->prev = tail->prev;
	tail->prev->next = newNode;
	tail->prev = newNode;
}

void addNode2Num(int data, int num)
{
	Node* ptr = head;

	int idx = 1;
	Node* newNode = getNode(data);
	if (num == 1) {
		newNode->next = head->next;
		head->next->prev = newNode;
		newNode->prev = head;
		head->next = newNode;

	}
	else {
		while (1) {
			if (idx == num) {
				newNode->next = ptr->next;
				newNode->prev = ptr;
				ptr->next->prev = newNode;
				ptr->next = newNode;
				break;
			}
			ptr = ptr->next;
			idx++;
		}
	}
}

int findNode(int data)
{
	Node* ptr = head->next;
	int cnt = 1;
	while (ptr != tail) {
		if (ptr->data == data)
			return cnt;
		cnt++;
		ptr = ptr->next;
	}
	return cnt;
}

void removeNode(int data)
{
	Node* ptr = head->next;
	while (ptr != tail) {
		if (ptr->data == data) {
			break;
		}
		ptr = ptr->next;
	}
	if (ptr == tail) return;

	if (ptr->prev == head) {
		head->next = ptr->next;
		ptr->next->prev = head;
	}
	else if (ptr->next == tail) {
		tail->prev = ptr->prev;
		ptr->prev->next = tail;
	}
	else {
		ptr->prev->next = ptr->next;
		ptr->next->prev = ptr->prev;
	}
}

int getList(int output[MAX_NODE])
{
	Node* ptr = head->next;
	int cnt = 0;
	while (ptr != tail) {
		output[cnt++] = ptr->data;
		ptr = ptr->next;
	}
	return cnt;
}

int getReversedList(int output[MAX_NODE])
{
	Node* ptr = tail->prev;
	int cnt = 0;

	while (ptr != head) {
		output[cnt++] = ptr->data;
		ptr = ptr->prev;
	}
	return cnt;
}