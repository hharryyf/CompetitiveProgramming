#include <bits/stdc++.h>
#define MAX_SIZE 55
using namespace std;

char alice[MAX_SIZE], bob[MAX_SIZE];
int N, K, L, M;

int playscore(char a, char b) {
    if (a == 'R' && b == 'S') return 1;
    if (a == 'R' && b == 'P') return -1;
    if (a == 'S' && b == 'R') return -1;
    if (a == 'S' && b == 'P') return 1;
    if (a == 'P' && b == 'R') return 1;
    if (a == 'P' && b == 'S') return -1;
    return 0;
}

int main() {
    int i, j, k, l, m;
    scanf("%d%d%d%d", &N, &K, &L, &M);
    scanf("%s", alice);
    scanf("%s", bob);
    int score = -1, scoreu = 1, scoree = -1;
    for (i = 0; i <= N - K; ++i) {
        // save (i, i + K - 1)
        vector<char> existential_1;
        for (j = i ; j <= i + K - 1; ++j) existential_1.push_back(alice[j]);
        scoreu = 1;
        for (j = 0; j <= N - K; ++j) {
            vector<char> universal;
            for (k = j; k <= j + K - 1; ++k) universal.push_back(bob[k]);
            // morph [k, k + L - 1]
            scoree = -1;
            for (k = 0; k <= K - L; ++k) {
                vector<char> existential = existential_1;
                for (l = k; l <= k + L - 1; ++l) {
                    if (existential[l] == 'R') {
                        existential[l] = 'P';
                    } else if (existential[l] == 'S') {
                        existential[l] = 'R';
                    } else {
                        existential[l] = 'S';
                    }
                }

                int a = 0, b = 0,  gamepoint = 0;
                for (m = 0; m < K; ++m) {
                    int s = playscore(existential[m], universal[m]);
                    if (s == 1) {
                        a++;
                    } else if (s == -1) {
                        b++;
                    }
                    if (a >= M) {
                        gamepoint = 1;
                        break;
                    }

                    if (b >= M) {
                        gamepoint = -1;
                        break;
                    }
                }
                scoree = max(scoree, gamepoint);
            }
            scoreu = min(scoreu, scoree);
        }
        score = max(score, scoreu);
    }

    

    if (score > 0) {
        printf("Alice\n");
    } else if (score == 0) {
        printf("Draw\n");
    } else {
        printf("Bob\n");
    }
    return 0;
}