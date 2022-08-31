#include <vcruntime_string.h>
using namespace std;

int array_pool[2'000'000];
int array_cnt = 0;

inline int* make_array(const int* a, int l) {
	int* tmp = array_pool + array_cnt;
	memcpy(tmp, a, l << 2);
	array_cnt += l;
	return tmp;
}

struct parray_inner {
	int* data = nullptr;
	parray_inner* parent = nullptr;
	int idx = 0;
	int value = 0;
};

struct parray {
	parray_inner* inner = nullptr;
};

parray_inner parray_inner_pool[100'100];
parray parray_pool[5'050];
int parray_inner_cnt = 0;
int parray_cnt = 0;

inline parray* new_parray(parray_inner* pi) {
	parray* tmp = &parray_pool[parray_cnt++];
	tmp->inner = pi;
	return tmp;
}

struct trie_node {
	trie_node* children[26] = { nullptr, };
	parray* value = nullptr;
};

trie_node trie[100'500];
int trie_cnt = 0;

trie_node* new_trie_node() {
	trie_node* tmp = &trie[trie_cnt++];
	tmp->children[0] = nullptr;
	tmp->children[1] = nullptr;
	tmp->children[2] = nullptr;
	tmp->children[3] = nullptr;
	tmp->children[4] = nullptr;
	tmp->children[5] = nullptr;
	tmp->children[6] = nullptr;
	tmp->children[7] = nullptr;
	tmp->children[8] = nullptr;
	tmp->children[9] = nullptr;
	tmp->children[10] = nullptr;
	tmp->children[11] = nullptr;
	tmp->children[12] = nullptr;
	tmp->children[13] = nullptr;
	tmp->children[14] = nullptr;
	tmp->children[15] = nullptr;
	tmp->children[16] = nullptr;
	tmp->children[17] = nullptr;
	tmp->children[18] = nullptr;
	tmp->children[19] = nullptr;
	tmp->children[20] = nullptr;
	tmp->children[21] = nullptr;
	tmp->children[22] = nullptr;
	tmp->children[23] = nullptr;
	tmp->children[24] = nullptr;
	tmp->children[25] = nullptr;
	tmp->value = nullptr;
	return tmp;
}

inline void set_trie(char* name, parray* pa) {
	trie_node* t = trie;

	for (; *name; name++) {
		trie_node** a = t->children + *name - 'a';
		if (*a == nullptr) *a = new_trie_node();
		t = *a;
	}

	t->value = pa;
}

inline parray* get_trie(char* name) {
	trie_node* t = trie;
	for (; *name; name++) t = t->children[*name - 'a'];
	return t->value;
}

void init() {
	array_cnt = 0;
	parray_inner_cnt = 0;
	parray_cnt = 0;
	trie_cnt = 0;
	new_trie_node();
}

void makeList(char mName[], int mLength, int mListValue[]) {
	parray_inner* tmp = &parray_inner_pool[parray_inner_cnt++];
	tmp->parent = nullptr;
	tmp->data = make_array(mListValue, mLength);
	set_trie(mName, new_parray(tmp));
}

void copyList(char mDest[], char mSrc[], bool mCopy) {
	if (mCopy) {
		set_trie(mDest, new_parray(get_trie(mSrc)->inner));
	}
	else {
		set_trie(mDest, get_trie(mSrc));
	}
}

void updateElement(char mName[], int mIndex, int mValue) {
	parray* parent = get_trie(mName);
	parray_inner* tmp = &parray_inner_pool[parray_inner_cnt++];
	tmp->parent = parent->inner;
	tmp->idx = mIndex;
	tmp->value = mValue;
	parent->inner = tmp;
}

int element(char mName[], int mIndex) {
	parray_inner* t = get_trie(mName)->inner;

	for (; t->parent; t = t->parent) {
		if (mIndex == t->idx) return t->value;
	}

	return t->data[mIndex];
}