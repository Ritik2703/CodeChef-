
/*    
 
  December Challenge 2019 Division 2
  problem 8 --  CUBICAL VIRUS
  solution by -- RITIK DAGAR
                 SRM IST NCR CAMPUS
                 contact -- 9958152151
        
*/




#include <bits/stdc++.h>
#include <random>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;
typedef pair<double, double> pt;

const int N = 100;

string g[N][N];

int n, a[N], p[N], q[N], r[N], pp[N], qq[N], rr[N], prp[N], prq[N], prr[N];

bool compare(int i, int j) {
    return a[i] < a[j];
}

void print_perm(int p[]) {
    for(int i = 0; i < n; i++) {
        cout << p[i] + 1 << " ";
    }
    cout << endl;
}

void print_perms() {
    print_perm(p);
    print_perm(q);
    print_perm(r);
}

int min_x[N];

int compute_score() {
    for(int i = 0; i < n; i++) {
        min_x[i] = n;
    }
    int score = 0;
    for(int k = 0; k < n; k++) {
        for(int j = 0; j < n; j++) {
            if (j && min_x[j - 1] < min_x[j]) {
                min_x[j] = min_x[j - 1];
            }
            for(int i = 0; i < n; i++) {
                if (g[r[k]][q[j]][p[i]] == '1') {
                    if (i < min_x[j]) {
                        min_x[j] = i;
                    }
                    break;
                }
            }
            score += min_x[j];
        }
    }
    return score;
}

void copy_perm(int pp[], int p[]) {
    for(int i = 0; i < n; i++) {
        pp[i] = p[i];
    }
}

void copy_perms() {
    copy_perm(pp, p);
    copy_perm(rr, r);
    copy_perm(qq, q);
}

void restore_perms() {
    copy_perm(p, pp);
    copy_perm(r, rr);
    copy_perm(q, qq);
}

void apply_change(int d, int i, int j) {
    int* pp;
    if (d == 0) pp = p;
    else if (d == 1) pp = q;
    else pp = r;
    swap(pp[i], pp[j]);
}

int main() {

#ifndef ONLINE_JUDGE
    freopen("testcase.in", "r", stdin);
    freopen("testcase.out", "w", stdout);
#endif

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int tt = 1;
    while(tt--) {
        clock_t begin_time = clock();
        cin >> n;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                cin >> g[i][j];
            }
        }
        for(int i = 0; i < n; i++) {
            p[i] = r[i] = q[i] = pp[i] = qq[i] = rr[i] = prp[i] = prq[i] = prr[i] = i;
        }
        int same_score_count = 0;
        int best_score = compute_score();
        int prev_score = best_score;
        for(int iter = 0; iter < 100; iter++) {
            for(int i = 0; i < n; i++) {
                a[i] = n * n * n;
                int xm = n;
                for(int j = 0; j < n; j++) {
                    for(int k = 0; k < n; k++) {
                        if (g[r[j]][q[k]][i] == '1') {
                            if (k < xm) {
                                xm = k;
                            }
                            break;
                        }
                    }
                    a[i] -= xm * (n - j);
                }
            }
            sort(p, p + n, compare);
            for(int i = 0; i < n; i++) {
                a[i] = n * n * n;
                int xm = n;
                for(int j = 0; j < n; j++) {
                    for(int k = 0; k < n; k++) {
                        if (g[r[j]][i][p[k]] == '1') {
                            if (k < xm) {
                                xm = k;
                            }
                            break;
                        }
                    }
                    a[i] -= xm * (n - j);
                }
            }
            sort(q, q + n, compare);
            for(int i = 0; i < n; i++) {
                a[i] = n * n * n;
                int xm = n;
                for(int j = 0; j < n; j++) {
                    for(int k = 0; k < n; k++) {
                        if (g[i][q[j]][p[k]] == '1') {
                            if (k < xm) {
                                xm = k;
                            }
                            break;
                        }
                    }
                    a[i] -= xm * (n - j);
                }
            }
            sort(r, r + n, compare);

            bool changed = false;
            for(int i = 0; i < n && !changed; i++) {
                if (p[i] != prp[i] || q[i] != prq[i] || r[i] != prr[i]) {
                    changed = true;
                }
            }
            if (changed) {
                for(int i = 0; i < n; i++) {
                    prp[i] = p[i];
                    prq[i] = q[i];
                    prr[i] = r[i];
                }
            } else {
                break;
            }

            int new_score = compute_score();
            if (prev_score == new_score) {
                same_score_count++;
                if (same_score_count == 3) break;
            } else {
                same_score_count = 0;
                if (best_score < new_score) {
                    best_score = new_score;
                    copy_perms();
                }
            }
            prev_score = new_score;
        }

        restore_perms();

        int ii = 0;
        while(float(clock() - begin_time) / CLOCKS_PER_SEC < 2.98) {
            int d = ii % 3, f = rand() % (n - 1) + 1, s = rand() % f;
            apply_change(d, s, f);
            int new_score = compute_score();
            if (new_score > best_score) {
                best_score = new_score;
            } else {
                apply_change(d, s, f);
            }
            ii++;
        }

        print_perms();

        /*int c = 0;
        for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) for(int k = 0; k < n; k++)
            c += g[i][j][k] - '0';
        double cc_score = best_score * pow(float(c) / pow(n, 3), 1.5);
        cout << cc_score << endl;*/
    }

    return 0;
}

