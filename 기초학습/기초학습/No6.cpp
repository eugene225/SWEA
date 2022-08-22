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
					ptr = ptr->next; // x번째 위치 찾음
					cnt--;
				}

				for (int i = 0; i < y; i++) {
					cin >> s;
					Node* newNode = getNode(s);
					if (i == 0 && x == 0) { // x가 0이면 맨 앞에 집어 넣음
						newNode->next = head;
						head = newNode;
						ptr = head;
						continue;
					}
					newNode->next = ptr->next; // 새 노드의 next는 현재 노드의 next
					ptr->next = newNode; // 현재 노드의 next는 새 노드
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
					ptr = ptr->next; // x번째 위치 찾음
					cnt--;
				}

				for (int i = 0; i < y; i++) {
					if (ptr->next == nullptr) {
						ptr = nullptr; // 다음 노드가 없으면 현재 노드를 nullptr로 만듦
						break;
					}
					if (x == 0) {
						head = head->next;
						ptr = head;
						continue;
					}
					ptr->next = ptr->next->next; // 현재 노드의 next를 다음 노드의 next로 지정
				}
			}
			break;

			case 'A':
			{
				cin >> y;
				Node* ptr = head;
				while (ptr->next) ptr = ptr->next; // 맨 뒤 노드 찾음
				for (int i = 0; i < y; i++) {
					cin >> s;
					Node* newNode = getNode(s);
					ptr->next = newNode; // 맨 뒤 노드에 새 노드 추가
					ptr = ptr->next; // 다음 노드를 가리킴
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