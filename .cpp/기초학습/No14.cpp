#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <queue>
using namespace std;

extern void bfs_init(int N, int map[10][10]);
extern int bfs(int x1, int y1, int x2, int y2);

static int test_bfs() {
	int N;
	int map[10][10];
	scanf("%d", &N);

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			scanf("%d", &map[i][j]);
		}
	}

	bfs_init(N, map);

	int M;
	int score = 100;
	scanf("%d", &M);

	for (int i = 0; i < M; ++i) {
		int x1, y1, x2, y2;
		scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
		int result = bfs(x1, y1, x2, y2);
        printf("result : %d\n", result);

		int dist;
		scanf("%d", &dist);
        printf("dist : %d\n", dist);

		if (result != dist) score = 0;
	}

	return score;
}

int main() {
	setbuf(stdout, NULL);

	printf("#total score : %d\n", test_bfs());

	return 0;
}

int Map[11][11];
int road[11][11];
int Map_size;
int q[100001][2];
bool visited[11][11];

int dx[4] = { -1, 1, 0, 0 };   // ��ȭ�¿� x�� ����
int dy[4] = { 0, 0, -1, 1 };   // ��ȭ�¿� y�� ����

void bfs_init(int map_size, int map[10][10]) {
    Map_size = map_size;

    for (int i = 1; i <= Map_size; i++) {
        for (int j = 1; j <= Map_size; j++) {
            Map[i][j] = map[i-1][j-1];
        }
    }
}

void init_road() {
    for (int i = 1; i <= 10; i++) {
        for (int j = 1; j <= 10; j++) {
            road[i][j] = -1;
            visited[i][j] = false;
        }
    }
}

int bfs(int x1, int y1, int x2, int y2) {
    init_road();

    // ť front, rear
    int front = 0, rear = 0;

    // ť�� ó�� (x1, y1) ��ǥ ����
    q[front][0] = x1;
    q[front][1] = y1;
    rear++;

    road[y1][x1] = 0;
    visited[y1][x1] = true;

    // ť�� �� �� ����
    while (front < rear) {
        int x = q[front][0]; // x ��ǥ
        int y = q[front][1]; // y ��ǥ 
        front++; // front �̵�
        //printf("x : %d, y : %d \n", x, y);

        // ���� ĭ(�����¿�) �̵�
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            // ������ ����� ���
            if (nx < 1 || ny < 1 || nx > Map_size || ny > Map_size)
                continue;

            // ���� �ƴ� ���
            if (Map[ny][nx] != 0 || visited[ny][nx]) {
                continue;
            }

            // ���� ĭ���� �̵��� ĭ �� + 1
            road[ny][nx] = road[y][x] + 1;
            //printf("nx : %d, ny : %d, road[nx][ny]:%d\n", nx, ny, road[ny][nx]);
            //if (nx == x2 && ny == y2) return road[nx][ny];

            // ť�� (nx, ny) ����
            q[rear][0] = nx;
            q[rear][1] = ny;
            rear++;
            visited[ny][nx] = true;
        }
    }

    return road[y2][x2];
}