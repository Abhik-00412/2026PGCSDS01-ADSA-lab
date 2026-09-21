//15 puzzle using bunch and bound
#include <stdio.h>
#include <stdlib.h>

#define N 4
#define MAXN 100000

typedef struct {
    int board[N][N];
    int x, y;
    int level;
    int cost;
} Node;

int goal[N][N] = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12},
    {13, 14, 15, 0}
};

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

int manhattan(int board[N][N]) {
    int cost = 0;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i][j] != 0) {
                int value = board[i][j] - 1;
                int x = value / N;
                int y = value % N;
                cost += abs(i - x) + abs(j - y);
            }
        }
    }

    return cost;
}

Node createNode(int board[N][N], int x, int y, int nx, int ny, int level) {
    Node node;

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            node.board[i][j] = board[i][j];

    int temp = node.board[x][y];
    node.board[x][y] = node.board[nx][ny];
    node.board[nx][ny] = temp;

    node.x = nx;
    node.y = ny;
    node.level = level;
    node.cost = level + manhattan(node.board);

    return node;
}

int isGoal(int board[N][N]) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (board[i][j] != goal[i][j])
                return 0;

    return 1;
}

void printBoard(int board[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            printf("%d ", board[i][j]);
        printf("\n");
    }
    printf("\n");
}

int main() {
    int board[N][N];
    int x, y;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &board[i][j]);
            if (board[i][j] == 0) {
                x = i;
                y = j;
            }
        }
    }

    Node *queue = malloc(MAXN * sizeof(Node));
    int front = 0, rear = 0;

    Node root;

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            root.board[i][j] = board[i][j];

    root.x = x;
    root.y = y;
    root.level = 0;
    root.cost = manhattan(board);

    queue[rear++] = root;

    while (front < rear) {
        int best = front;

        for (int i = front + 1; i < rear; i++) {
            if (queue[i].cost < queue[best].cost)
                best = i;
        }

        Node current = queue[best];

        Node temp = queue[front];
        queue[front] = queue[best];
        queue[best] = temp;

        front++;

        if (isGoal(current.board)) {
            printf("Minimum moves: %d\n", current.level);
            printBoard(current.board);
            free(queue);
            return 0;
        }

        for (int i = 0; i < 4; i++) {
            int nx = current.x + dx[i];
            int ny = current.y + dy[i];

            if (nx >= 0 && nx < N && ny >= 0 && ny < N) {
                Node child = createNode(
                    current.board,
                    current.x,
                    current.y,
                    nx,
                    ny,
                    current.level + 1
                );

                if (rear < MAXN)
                    queue[rear++] = child;
            }
        }
    }

    printf("Solution not found\n");

    free(queue);

    return 0;
}