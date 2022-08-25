#include <iostream>
using namespace std;

struct Node {
	int data;
	Node* Llink;
	Node* Rlink;
};

struct HeadNode {
	Node* Lhead; // 원래 리스트의 반대쪽으로
	Node* Rhead; // 원래 연결리스트 방향으로
};

class doubleList {

public:
	/* 이중연결리스트 생성 */
	HeadNode* createList() {
		HeadNode* H = new HeadNode;
		H->Lhead = NULL;
		H->Rhead = NULL;
		return H;
	}

	/* 이중연결리스트 끝에 노드 삽입*/
	void addEndNode(HeadNode* H, int adddata) {
		Node* prevNode;
		Node* newNode = new Node;
		newNode->data = adddata;
		newNode->Llink = NULL;
		newNode->Rlink = NULL;

		if (H->Rhead == NULL) { // 리스트가 비어있을 때
			H->Rhead = newNode;
			H->Lhead = newNode;
		}
		else { // 리스트에 노드가 있을 때
			prevNode = H->Lhead;  // 리스트의 마지막노드는 Lhead가 가리키고 있을 것이므로 이걸 prevNode로 
			prevNode->Rlink = newNode;
			newNode->Llink = prevNode;
			H->Lhead = newNode; // 새 노드가 마지막 노드가 된다.
		}
	}

	/* 이중연결리스트 특정 노드 삽입*/
	void addThisNode(HeadNode* H, int afterthisdata, int adddata) {
		Node* prevNode;
		Node* newNode = new Node;
		newNode->data = adddata;
		newNode->Llink = NULL;
		newNode->Rlink = NULL;

		prevNode = H->Rhead;

		while (prevNode->data != afterthisdata) {
			prevNode = prevNode->Rlink;
		}

		newNode->Rlink = prevNode->Rlink; //새 노드가 이전노드가 가리키던 노드를 가리키게
		newNode->Llink = prevNode;  // 새노드의 Llink가 이전노드를 가리키게
		prevNode->Rlink = newNode;  // 이전노드의 Rlink가 새노드를 가리키게
		newNode->Rlink->Llink = newNode; // 새노드의 다음 노드의 Llink가 이전노드가 아닌 새노드를 가리키게
	}

	/* 이중연결리스트 특정 노드 삭제*/
	void deleteNode(HeadNode* H, int deldata) {
		Node* delNode;
		delNode = H->Rhead;

		if (delNode == NULL) return; // 리스트가 빈 경우

		while (delNode->data != deldata) {
			delNode = delNode->Rlink;
		}

		if (delNode == H->Lhead) { //삭제할 노드가 리스트의 마지막 노드일 때
			if (delNode == H->Rhead) { // 삭제할 노드가 유일한 노드일 때 
				H->Rhead = NULL;
				H->Lhead = NULL;
			}
			else {
				delNode->Llink->Rlink = NULL; //삭제할노드 바로 앞 노드의 Rlink가 NULL
				H->Lhead = delNode->Llink;  // 헤드의 Lhead가 삭제할노드 바로 앞 노드를 가리키게
			}
		}
		else if (delNode == H->Rhead) { //삭제할 노드가 리스트의 첫 노드일 때
			H->Rhead = delNode->Rlink;
			delNode->Rlink->Llink = NULL;
		}
		else {
			delNode->Llink->Rlink = delNode->Rlink;
			delNode->Rlink->Llink = delNode->Llink;
		}
		delete delNode;
		cout << deldata << "를 가지는 노드를 삭제했습니다." << endl;
	}

	/* 이중연결리스트 출력*/
	void printList(HeadNode* L) {

		//노드 순서대로 리스트 출력
		Node* p;

		p = L->Rhead;

		if (p == NULL) { // 리스트가 빈 경우
			cout << endl << "연결 리스트가 비어있습니다." << endl << endl;
			return;
		}

		cout << "연결리스트 목록 = ( ";

		while (p != NULL) {
			cout << p->data;
			p = p->Rlink;
			if (p != NULL) cout << " --> ";
		}
		cout << " )" << endl << endl;
	}

};