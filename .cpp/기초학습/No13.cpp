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


//constexpr int NAME_MAXLEN = 6;
//constexpr int PATH_MAXLEN = 1999;
constexpr int MAX_CHILD_COUNT = 30;
constexpr int MAX_NODE_COUNT = 50000;

struct Node {
	char name[NAME_MAXLEN + 1];
	int count;
	Node* parent;
	Node* child[MAX_CHILD_COUNT];
};

Node node_pool[1 + MAX_NODE_COUNT];
int node_count;
Node* root;

int mstrcmp(const char* a, const char* b)
{
	int i;
	for (i = 0; a[i] != '\0'; i++)
	{
		if (a[i] != b[i])
			return a[i] - b[i];
	}
	return a[i] - b[i];
}

void mstrcpy(char* dest, const char* src)
{
	int i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = src[i];
}

Node* get_node(char name[NAME_MAXLEN + 1]) {
	mstrcpy(node_pool[node_count].name, name);
	node_pool[node_count].count = 0;
	node_pool[node_count].parent = nullptr;
	for (int i = 0; i < MAX_CHILD_COUNT; ++i) {
		node_pool[node_count].child[i] = nullptr;
	}

	return &node_pool[node_count++];
}

Node* find_node(char path[PATH_MAXLEN + 1]) {
	char name[NAME_MAXLEN + 1];
	int i, j;
	Node* node = root;

	for (i = 1; '\0' != path[i]; ++i) {
		for (j = 0; '/' != path[i]; ++i) {
			name[j++] = path[i];
		}
		name[j] = '\0';

		for (j = 0; j < MAX_CHILD_COUNT; ++j) {
			if (node->child[j] && !mstrcmp(node->child[j]->name, name)) {
				node = node->child[j];
				break;
			}
		}
	}

	return node;
}

void cp(Node* parent_node, Node* src_node) {
	Node* node = get_node(src_node->name);
	node->count = src_node->count;
	node->parent = parent_node;
	int i;

	for (i = 0; i < MAX_CHILD_COUNT; ++i) {
		if (!parent_node->child[i]) {
			parent_node->child[i] = node;
			break;
		}
	}

	for (i = 0; i < MAX_CHILD_COUNT; ++i) {
		if (src_node->child[i]) {
			cp(node, src_node->child[i]);
		}
	}

	return;
}

void init(int n) {
	node_pool[0].count = 0;
	node_pool[0].parent = nullptr;
	for (int i = 0; i < MAX_CHILD_COUNT; ++i) {
		node_pool[0].child[i] = nullptr;
	}
	root = &node_pool[0];
	node_count = 1;

	return;
}

void cmd_mkdir(char path[PATH_MAXLEN + 1], char name[NAME_MAXLEN + 1]) {
	Node* parent_node = find_node(path);
	Node* node = get_node(name);
	int i;

	node->parent = parent_node;
	for (i = 0; i < MAX_CHILD_COUNT; ++i) {
		if (!parent_node->child[i]) {
			parent_node->child[i] = node;
			break;
		}
	}

	do {
		++parent_node->count;
		parent_node = parent_node->parent;
	} while (parent_node);

	return;
}

void cmd_rm(char path[PATH_MAXLEN + 1]) {
	Node* node = find_node(path);
	Node* parent_node = node->parent;
	int i;

	for (i = 0; i < MAX_CHILD_COUNT; ++i) {
		if (node == parent_node->child[i]) {
			parent_node->child[i] = nullptr;
			break;
		}
	}

	do {
		parent_node->count -= node->count + 1;
		parent_node = parent_node->parent;
	} while (parent_node);

	return;
}

void cmd_cp(char srcPath[PATH_MAXLEN + 1], char dstPath[PATH_MAXLEN + 1]) {
	Node* src_node = find_node(srcPath);
	Node* dst_node = find_node(dstPath);
	int i;

	cp(dst_node, src_node);

	do {
		dst_node->count += src_node->count + 1;
		dst_node = dst_node->parent;
	} while (dst_node);

	return;
}

void cmd_mv(char srcPath[PATH_MAXLEN + 1], char dstPath[PATH_MAXLEN + 1]) {
	Node* src_node = find_node(srcPath);
	Node* dst_node = find_node(dstPath);
	Node* parent_node = src_node->parent;
	int i;

	for (i = 0; i < MAX_CHILD_COUNT; ++i) {
		if (src_node == parent_node->child[i]) {
			parent_node->child[i] = nullptr;
			break;
		}
	}

	do {
		parent_node->count -= src_node->count + 1;
		parent_node = parent_node->parent;
	} while (parent_node);

	src_node->parent = dst_node;
	for (i = 0; i < MAX_CHILD_COUNT; ++i) {
		if (!dst_node->child[i]) {
			dst_node->child[i] = src_node;
			break;
		}
	}

	do {
		dst_node->count += src_node->count + 1;
		dst_node = dst_node->parent;
	} while (dst_node);

	return;
}

int cmd_find(char path[PATH_MAXLEN + 1]) {
	return find_node(path)->count;
}