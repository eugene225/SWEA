#include <iostream>
using namespace std;

struct Node {
	int data;
	Node* next;
};

Node memPool[10000];
Node* head;
int N, M, num, cnt, x, y, s;
char order;

Node* getNode(int num) {
	memPool[cnt].data = num;
	memPool[cnt].next = nullptr;
	return &memPool[cnt++];
}

int main()
{
	for (int t = 1; t <= 10; t++) {
		cin >> N;
		cnt = 0;
		head = nullptr;
		int tmp = 0;
		Node* ptr = nullptr;

		for (int i = 0; i < N; i++) {
			cin >> num;

			Node* newNode = getNode(num);
			if (head == nullptr) {
				head = newNode;
				ptr = head;
			}
			else {
				ptr->next = newNode;
				ptr = ptr->next;
				tmp++;
			}
		}

		cin >> M;

		for (int i = 0; i < M; i++) {
			cin >> order;
			switch (order) {
			case 'I':
			{
				cin >> x >> y;
				Node* ptr = head;
				int cnt = x;

				while (cnt > 1) {
					ptr = ptr->next; // x��° ��ġ ã��
					cnt--;
				}

				for (int i = 0; i < y; i++) {
					cin >> s;
					Node* newNode = getNode(s);
					if (i == 0 && x == 0) { // x�� 0�̸� �� �տ� ���� ����
						newNode->next = head;
						head = newNode;
						ptr = head;
						continue;
					}
					newNode->next = ptr->next; // �� ����� next�� ���� ����� next
					ptr->next = newNode; // ���� ����� next�� �� ���
					ptr = ptr->next;
				}
			}
			break;

			case 'D':
			{
				cin >> x >> y;

				Node* ptr = head;
				int cnt = x;

				while (cnt > 1) {
					ptr = ptr->next; // x��° ��ġ ã��
					cnt--;
				}

				for (int i = 0; i < y; i++) {
					if (ptr->next == nullptr) {
						ptr = nullptr; // ���� ��尡 ������ ���� ��带 nullptr�� ����
						break;
					}
					if (x == 0) {
						head = head->next;
						ptr = head;
						continue;
					}
					ptr->next = ptr->next->next; // ���� ����� next�� ���� ����� next�� ����
				}
			}
			break;

			case 'A':
			{
				cin >> y;
				Node* ptr = head;
				while (ptr->next) ptr = ptr->next; // �� �� ��� ã��
				for (int i = 0; i < y; i++) {
					cin >> s;
					Node* newNode = getNode(s);
					ptr->next = newNode; // �� �� ��忡 �� ��� �߰�
					ptr = ptr->next; // ���� ��带 ����Ŵ
				}
			}
			break;
			}
		}
		cout << "#" << t << " ";
		for (int i = 0; i < 10; i++) {
			cout << head->data << " ";
			head = head->next;
		}
		cout << "\n";
	}
}