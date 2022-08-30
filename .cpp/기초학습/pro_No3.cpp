#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

extern void init(int N);
extern int allocate(int mSize);
extern int release(int mAddr);

/////////////////////////////////////////////////////////////////////////

#define CMD_INIT 1
#define CMD_ALLOCATE 2
#define CMD_RELEASE 3

static bool run() {
	int q;
	scanf("%d", &q);

	int n, addr, size;
	int cmd, ans, ret = 0;
	bool okay = false;

	for (int i = 0; i < q; ++i) {
		scanf("%d", &cmd);
		switch (cmd) {
		case CMD_INIT:
			scanf("%d", &n);
			init(n);
			okay = true;
			break;
		case CMD_ALLOCATE:
			scanf("%d %d", &size, &ans);
			ret = allocate(size);
			if (ans != ret)
				okay = false;
			break;
		case CMD_RELEASE:
			scanf("%d %d", &addr, &ans);
			ret = release(addr);
			if (ans != ret)
				okay = false;
			break;
		default:
			okay = false;
			break;
		}
	}
	return okay;
}

int main() {
	setbuf(stdout, NULL);
	//freopen("sample_input.txt", "r", stdin);

	int T, MARK;
	scanf("%d %d", &T, &MARK);

	for (int tc = 1; tc <= T; tc++) {
		int score = run() ? MARK : 0;
		printf("#%d %d\n", tc, score);
	}

	return 0;
}

//#include <bits/stdc++.h>
#include <map>
#include <set>

using namespace std;

int tot;
map<int, int> map_all;
set<pair<int, int>> mem;

void init(int N) {
	tot = N;
	map_all.clear();
	mem.clear();
	mem.emplace(N, 0);
}

int allocate(int mSize) {
	auto it = mem.lower_bound({ mSize, 0 });
	if (it == mem.end()) return -1;
	int size = it->first, addr = it->second;
	mem.erase(it);
	map_all[addr] = mSize;
	if (size > mSize) mem.emplace(size - mSize, addr + mSize);
	return addr;
}

int release(int mAddr) {
	auto it = map_all.find(mAddr);
	if (it == map_all.end()) return -1;
	int size = it->second;
	int res = size;
	it = map_all.erase(it);

	int after_size = 0;
	if (it != map_all.end()) {
		after_size = it->first - (mAddr + size);
	}
	else if (mAddr + size < tot) {
		after_size = tot - (mAddr + size);
	}

	if (after_size > 0) {
		mem.erase({ after_size, mAddr + size });
		size += after_size;
	}

	int before_size = 0;
	if (it != map_all.begin()) {
		--it;
		before_size = mAddr - (it->first + it->second);
	}
	else if (mAddr > 0) {
		before_size = mAddr;
	}

	if (before_size > 0) {
		mem.erase({ before_size, mAddr - before_size });
		size += before_size;
		mAddr -= before_size;
	}

	mem.emplace(size, mAddr);
	return res;
}