#include <iostream>
constexpr size_t MAX_NODE = 99999;
using namespace std;

struct Node {
	int data;
	Node* next;
};

Node* head = 0;
Node* main_tmp = 0;
int node_cnt = 0;
int cop_node_cnt = 0;
Node node_pool[MAX_NODE];

Node* getNode(int data) {
	node_pool[node_cnt].data = data;
	node_pool[node_cnt].next = nullptr;
	return &node_pool[node_cnt++];
}

void add(int data)
{
	Node* newNode = getNode(data);
	cop_node_cnt = node_cnt;
	if (head == 0) {
		head = newNode;
		main_tmp = head;
		return;
	}
	else {
		main_tmp->next = newNode;
		main_tmp = newNode;
	}
}

void insert(int pos, int data) {
	Node* tmp = head;
	Node* newNode = getNode(data);
	cop_node_cnt++;

	int a = pos;

	if (pos == 0)
	{
		newNode->next = head;
		head = newNode;
		return;
	}

	while (a > 1) {
		tmp = tmp->next;
		a--;
	}

	newNode->next = tmp->next;
	tmp->next = newNode;
}

void del(int pos) {
	Node* tmp = head;
	int a = pos;
	
	if (pos == 0) {
		head = head->next;
		cop_node_cnt--;
		return;
	}

	while (a > 1) {
		tmp = tmp->next;
		a--;
	}

	if (tmp->next != 0) {
		tmp->next = tmp->next->next;
	}

	cop_node_cnt--;
}

void change(int pos, int data) {
	Node* tmp = head;
	int a = pos;
	
	while (a > 0) {
		tmp = tmp->next;
		a--;
	}
	tmp->data = data;
}

int main()
{
	int t, n, m, l, num, pos, data;
	char com;

	cin >> t;

	for (int test_case = 1; test_case <= t; test_case++) {
		cin >> n >> m >> l;
		for (int i = 0; i < n; i++) {
			cin >> num;
			add(num);
		}

		for (int i = 0; i < m; i++) {
			cin >> com;
			switch (com)
			{
			case 'I':
				cin >> pos >> data;
				if (pos + 1 <= cop_node_cnt) {
					insert(pos, data);
				}
				break;
			case 'D':
				cin >> pos;
				if (pos + 1 <= cop_node_cnt) {
					del(pos);
				}
				break;
			case 'C':
				cin >> pos >> data;
				if (pos + 1 <= cop_node_cnt) {
					change(pos, data);
				}
				break;
			default:
				break;
			}
		}

		Node* tmp = head;
		int a = l;
		while (a > 0) {
			if (tmp->next != 0) {
				tmp = tmp->next;
				a--;
			}
			else break;
		}

		if (cop_node_cnt < l + 1) {
			cout << "#" << test_case << ' ' << -1 << endl;
		}
		else
		{
			cout << "#" << test_case << ' ' << tmp->data << endl;
		}
		head = nullptr;
		cop_node_cnt = 0;
		node_cnt = 0;
		main_tmp = nullptr;
	}
	return 0;
}