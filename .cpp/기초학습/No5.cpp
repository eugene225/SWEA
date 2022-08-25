#include <iostream>
using namespace std;

struct Node {
	int data;
	Node* Llink;
	Node* Rlink;
};

struct HeadNode {
	Node* Lhead; // ���� ����Ʈ�� �ݴ�������
	Node* Rhead; // ���� ���Ḯ��Ʈ ��������
};

class doubleList {

public:
	/* ���߿��Ḯ��Ʈ ���� */
	HeadNode* createList() {
		HeadNode* H = new HeadNode;
		H->Lhead = NULL;
		H->Rhead = NULL;
		return H;
	}

	/* ���߿��Ḯ��Ʈ ���� ��� ����*/
	void addEndNode(HeadNode* H, int adddata) {
		Node* prevNode;
		Node* newNode = new Node;
		newNode->data = adddata;
		newNode->Llink = NULL;
		newNode->Rlink = NULL;

		if (H->Rhead == NULL) { // ����Ʈ�� ������� ��
			H->Rhead = newNode;
			H->Lhead = newNode;
		}
		else { // ����Ʈ�� ��尡 ���� ��
			prevNode = H->Lhead;  // ����Ʈ�� ���������� Lhead�� ����Ű�� ���� ���̹Ƿ� �̰� prevNode�� 
			prevNode->Rlink = newNode;
			newNode->Llink = prevNode;
			H->Lhead = newNode; // �� ��尡 ������ ��尡 �ȴ�.
		}
	}

	/* ���߿��Ḯ��Ʈ Ư�� ��� ����*/
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

		newNode->Rlink = prevNode->Rlink; //�� ��尡 ������尡 ����Ű�� ��带 ����Ű��
		newNode->Llink = prevNode;  // ������� Llink�� ������带 ����Ű��
		prevNode->Rlink = newNode;  // ��������� Rlink�� ����带 ����Ű��
		newNode->Rlink->Llink = newNode; // ������� ���� ����� Llink�� ������尡 �ƴ� ����带 ����Ű��
	}

	/* ���߿��Ḯ��Ʈ Ư�� ��� ����*/
	void deleteNode(HeadNode* H, int deldata) {
		Node* delNode;
		delNode = H->Rhead;

		if (delNode == NULL) return; // ����Ʈ�� �� ���

		while (delNode->data != deldata) {
			delNode = delNode->Rlink;
		}

		if (delNode == H->Lhead) { //������ ��尡 ����Ʈ�� ������ ����� ��
			if (delNode == H->Rhead) { // ������ ��尡 ������ ����� �� 
				H->Rhead = NULL;
				H->Lhead = NULL;
			}
			else {
				delNode->Llink->Rlink = NULL; //�����ҳ�� �ٷ� �� ����� Rlink�� NULL
				H->Lhead = delNode->Llink;  // ����� Lhead�� �����ҳ�� �ٷ� �� ��带 ����Ű��
			}
		}
		else if (delNode == H->Rhead) { //������ ��尡 ����Ʈ�� ù ����� ��
			H->Rhead = delNode->Rlink;
			delNode->Rlink->Llink = NULL;
		}
		else {
			delNode->Llink->Rlink = delNode->Rlink;
			delNode->Rlink->Llink = delNode->Llink;
		}
		delete delNode;
		cout << deldata << "�� ������ ��带 �����߽��ϴ�." << endl;
	}

	/* ���߿��Ḯ��Ʈ ���*/
	void printList(HeadNode* L) {

		//��� ������� ����Ʈ ���
		Node* p;

		p = L->Rhead;

		if (p == NULL) { // ����Ʈ�� �� ���
			cout << endl << "���� ����Ʈ�� ����ֽ��ϴ�." << endl << endl;
			return;
		}

		cout << "���Ḯ��Ʈ ��� = ( ";

		while (p != NULL) {
			cout << p->data;
			p = p->Rlink;
			if (p != NULL) cout << " --> ";
		}
		cout << " )" << endl << endl;
	}

};