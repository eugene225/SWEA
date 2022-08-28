#ifndef _CRT_SECURE_NO_WARNINGS 
#define _CRT_SECURE_NO_WARNINGS 
#endif

#include<stdio.h>

#define CMD_MKDIR 1
#define CMD_RM 2
#define CMD_CP 3
#define CMD_MV 4
#define CMD_FIND 5

#define NAME_MAXLEN 6
#define PATH_MAXLEN 1999

extern void init(int n);
extern void cmd_mkdir(char path[PATH_MAXLEN + 1], char name[NAME_MAXLEN + 1]);
extern void cmd_rm(char path[PATH_MAXLEN + 1]);
extern void cmd_cp(char srcPath[PATH_MAXLEN + 1], char dstPath[PATH_MAXLEN + 1]);
extern void cmd_mv(char srcPath[PATH_MAXLEN + 1], char dstPath[PATH_MAXLEN + 1]);
extern int cmd_find(char path[PATH_MAXLEN + 1]);

static bool run(int m) {

	bool isAccepted = true;
	int cmd;
	char name[NAME_MAXLEN + 1];
	char path1[PATH_MAXLEN + 1], path2[PATH_MAXLEN + 1];

	while (m--) {

		scanf("%d", &cmd);

		if (cmd == CMD_MKDIR) {
			scanf("%s%s", path1, name);
			cmd_mkdir(path1, name);
		}
		else if (cmd == CMD_RM) {
			scanf("%s", path1);
			cmd_rm(path1);
		}
		else if (cmd == CMD_CP) {
			scanf("%s%s", path1, path2);
			cmd_cp(path1, path2);
		}
		else if (cmd == CMD_MV) {
			scanf("%s%s", path1, path2);
			cmd_mv(path1, path2);
		}
		else {
			int ret;
			int answer;

			scanf("%s", path1);
			ret = cmd_find(path1);
			scanf("%d", &answer);

			isAccepted &= (ret == answer);
		}
	}

	return isAccepted;
}

int main(void) {

	int test, T;
	int n, m;

	// freopen("sample_input.txt", "r", stdin);

	setbuf(stdout, NULL);

	scanf("%d", &T);

	for (test = 1; test <= T; ++test) {

		scanf("%d%d", &n, &m);

		init(n);

		if (run(m)) {
			printf("#%d 100\n", test);
		}
		else {
			printf("#%d 0\n", test);
		}
	}

	return 0;
}

#define NAME_MAXLEN 6
#define PATH_MAXLEN 1999

// The below commented functions are for your reference. If you want 
// to use it, uncomment these functions.

int mstrcmp(const char *a, const char *b)
{
	int i;
	for (i = 0; a[i] != '\0'; i++)
	{
		if (a[i] != b[i])
			return a[i] - b[i];
	}
	return a[i] - b[i];
}

int mstrncmp(const char *a, const char *b, int len)
{
	for (int i = 0; i < len; i++)
	{
		if (a[i] != b[i])
			return a[i] - b[i];
	}
	return 0;
}

int mstrlen(const char *a)
{
	int len = 0;

	while (a[len] != '\0')
		len++;

	return len;
}

void mstrcpy(char *dest, const char *src)
{
	int i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = src[i];
}

void mstrncpy(char *dest, const char *src, int len)
{
	for (int i = 0; i<len; i++)
	{
		dest[i] = src[i];
	}
	dest[len] = '\0';
}

typedef struct Node {
	char name[7];
	Node* low[30];
	Node* toparent;
	int num;
}Node;

Node pool[50000];
int cnt;

Node* getNode(char* name) {
	mstrncpy(pool[cnt].name, name, mstrlen(name));
	cnt++;
	return &pool[cnt-1];
}

void init(int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 30; j++) {
			pool[i].low[j] = nullptr;
		}
		pool[i].toparent = nullptr;
		pool[i].num = 0;
	}
	cnt = 1;
	mstrncpy(pool[0].name, "/", 2);
}

void updatecnt(Node* rt, int count) {

	while (rt != nullptr) {
		rt->num += count;
		rt = rt->toparent;
	}
}

Node* find(char path[], Node* root) {
	int count = 0;
	int len = mstrlen(path);

	for (int i = 1; i < mstrlen(path); i++) {
		count = 0;
		while (path[i] != '/') {
			i++;
			count++;
		}

		char name[7];
		mstrncpy(name, path + i - count, count);

		for (int k = 0; k < 30; k++) {
			if (root->low[k] == nullptr) continue;

			if (mstrncmp(root->low[k]->name, name, count) == 0)
			{
				root = root->low[k];
				break;
			}
		}
	}
	return root;
}

void cmd_mkdir(char path[PATH_MAXLEN + 1], char name[NAME_MAXLEN + 1]) {
	Node* root = &pool[0];
	root = find(path, root);
	int i = 0;
	while (root->low[i] != nullptr) {
		i++;
	}
	Node* p = getNode(name);
	root->low[i] = p;
	p->toparent = root;
	updatecnt(root, 1);
}

void cmd_rm(char path[PATH_MAXLEN + 1]) {
	Node* root = &pool[0];
	root = find(path, root);
	Node* p = root->toparent;

	updatecnt(p, -(root->num + 1));

	for (int i = 0; i < 30; i++) {
		if (p->low[i] == root) {
			p->low[i] = nullptr;
		}
	}
}

Node* deepcopy(Node* rt) {
	if (rt == nullptr) return nullptr;

	Node* copy = getNode(rt->name);
	if (rt->num == 0) return copy;

	for (int i = 0; i < 30; i++) {
		if (rt->low[i] == nullptr) continue;
		copy->low[i] = deepcopy(rt->low[i]);
		copy->low[i]->toparent = copy;
		updatecnt(copy, (copy->low[i]->num) + 1);
	}

	return copy;
}

void cmd_cp(char srcPath[PATH_MAXLEN + 1], char dstPath[PATH_MAXLEN + 1]) {
	Node* root = &pool[0];
	root = find(dstPath, root);

	Node* p = &pool[0];
	p = find(srcPath, p);

	Node* tmp = deepcopy(p);
	tmp->toparent = root;

	updatecnt(root, tmp->num + 1);

	for (int i = 0; i < 30; i++) {
		if (root->low[i] == nullptr) {
			root->low[i] = tmp;
			break;
		}
	}
}

void cmd_mv(char srcPath[PATH_MAXLEN + 1], char dstPath[PATH_MAXLEN + 1]) {
	Node* root = &pool[0];
	root = find(dstPath, root);

	Node* p = &pool[0];
	p = find(srcPath, p);
	Node* pp = p->toparent;

	updatecnt(pp, -(p->num + 1));
	updatecnt(root, p->num + 1);

	for (int i = 0; i < 30; i++) {
		if (pp->low[i] == p) {
			pp->low[i] = nullptr;
			break;
		}
	}

	for (int i = 0; i < 30; i++) {
		if (root->low[i] == nullptr) {
			root->low[i] = p;
			p->toparent = root;
			break;
		}
	}
}

int cmd_find(char path[PATH_MAXLEN + 1]) {
	Node* root = &pool[0];
	root = find(path, root);
	return root->num;
}