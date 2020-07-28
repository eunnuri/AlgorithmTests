/*백준 구슬탈출2 190721*/
#include<queue>
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
#define MAXX 10
int dr[4] = { -1,0,1,0 }; // 0위 2아래
int dc[4] = { 0,1,0,-1 }; //   1오  3왼 
int	map[MAXX][MAXX] = { 0 };
bool visited[MAXX][MAXX][MAXX][MAXX];
class Point {	// 공 좌표
public:
	int rr, rc, br, bc;
	int cnt;
	Point(int rr, int rc, int br, int bc, int cnt) {
		this->rr = rr;
		this->rc = rc;
		this->br = br;
		this->bc = bc;
		this->cnt = cnt;
	}
};
int main() {
	//ios::sync_with_stdio(false); cin.tie(0);
	//memset(map, 1, sizeof(map));
	queue<Point> q;
	int n, m; //상 우 하 좌
	int redr, redc, bluer, bluec;
	int result = -1;
	char str[11];
	//입력
	cin >> n >> m;
	for (int i = 0; i < n; ++i) {
		scanf("%s", str);
		for (int j = 0; j < m; ++j) {
			switch (str[j]) {
			case '.':
				map[i][j] = 1;
				break;
			case '#':
				map[i][j] = 2;
				break;
			case 'O':
				map[i][j] = 3;
				break;
			case 'R':
				redr = i; redc = j;
				break;
			case 'B':
				bluer = i; bluec = j;
				break;
			}
		}
	}


	q.push({ redr, redc, bluer, bluec, 0 });
	visited[redr][redc][bluer][bluec] = true;
	int nrr, nrc, nbr, nbc;
	int rr, rc, br, bc, c, temp;
	//Start (2)
	while (!q.empty()) {
		rr = q.front().rr;		 rc = q.front().rc;
		br = q.front().br;		 bc = q.front().bc;
		c = q.front().cnt;
		q.pop();
		if (c > 10)
			break;
		if (map[rr][rc] == 3) {
			result = c;
			break;
		}

		for (int i = 0; i < 4; i++) {
			nrr = rr; nrc = rc;
			nbr = br; nbc = bc;


			//빨간공 먼저 이동
			while (1) {
				nrr = nrr + dr[i]; nrc = nrc + dc[i];
				if (map[nrr][nrc] == 2) {
					nrr = nrr - dr[i]; nrc = nrc - dc[i];
					break;
				}
				else if (map[nrr][nrc] == 3) {
					break;
				}
			}
			//파란공 이동
			while (1) {
				nbr = nbr + dr[i]; nbc = nbc + dc[i];
				if (map[nbr][nbc] == 2) {
					nbr = nbr - dr[i]; nbc = nbc - dc[i];
					break;
				}
				else if (map[nbr][nbc] == 3) {
					break;
				}
			}

			if (map[nbr][nbc] == 3)
				continue;

			//공들끼리 겹쳤을때 
			if (nrr == nbr && nrc == nbc) {
				switch (i) {
				case 2:
					rr < br ? nrr-- : nbr--; break;
				case 0:
					rr < br ? nbr++ : nrr++; break;
				case 1:
					rc < bc ? nrc-- : nbc--; break;
				case 3:
					rc < bc ? nbc++ : nrc++; break;
				}
			}
			if (!visited[nrr][nrc][nbr][nbc]) {
				temp = c + 1;
				q.push({ nrr,nrc,nbr,nbc,temp });
				visited[nrr][nrc][nbr][nbc] = true;
			}
		}
	}
	cout << result;
	return 0;
}
