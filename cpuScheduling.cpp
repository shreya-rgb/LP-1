#include <bits/stdc++.h>
using namespace std;
struct P
{
    int id, at, bt, pr, ct, tat, wt, rem;
};

void print(vector<P> &p, bool prio = false)
{
    double ttat = 0, twt = 0;
    cout << (prio ? "PID\tAT\tBT\tPR\tCT\tTAT\tWT\n" : "PID\tAT\tBT\tCT\tTAT\tWT\n");
    for (auto &x : p)
    {
        if (prio)
            cout << x.id << "\t" << x.at << "\t" << x.bt << "\t" << x.pr << "\t" << x.ct << "\t" << x.tat << "\t" << x.wt << "\n";
        else
            cout << x.id << "\t" << x.at << "\t" << x.bt << "\t" << x.ct << "\t" << x.tat << "\t" << x.wt << "\n";
        ttat += x.tat;
        twt += x.wt;
    }
    cout << "Avg WT=" << twt / p.size() << "  Avg TAT=" << ttat / p.size() << "\n";
}

void fcfs(vector<P> p)
{
    sort(p.begin(), p.end(), [](auto &a, auto &b)
         { return a.at < b.at; });
    int t = 0;
    for (auto &x : p)
    {
        if (t < x.at)
            t = x.at;
        t += x.bt;
        x.ct = t;
        x.tat = x.ct - x.at;
        x.wt = x.tat - x.bt;
    }
    cout << "\n[FCFS]\n";
    print(p);
}

void sjf(vector<P> p)
{
    int n = p.size(), done = 0, t = 0;
    for (auto &x : p)
        x.rem = x.bt;
    while (done < n)
    {
        int idx = -1, mn = 1e9;
        for (int i = 0; i < n; i++)
            if (p[i].at <= t && p[i].rem > 0 && p[i].rem < mn)
                mn = p[i].rem, idx = i;
        if (idx == -1)
        {
            t++;
            continue;
        }
        p[idx].rem--;
        t++;
        if (!p[idx].rem)
        {
            done++;
            p[idx].ct = t;
            p[idx].tat = t - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
        }
    }
    cout << "\n[SJF Preemptive]\n";
    print(p);
}

void priority(vector<P> p)
{
    int n = p.size(), done = 0, t = 0;
    vector<int> vis(n);
    while (done < n)
    {
        int idx = -1, mn = 1e9;
        for (int i = 0; i < n; i++)
            if (!vis[i] && p[i].at <= t && p[i].pr < mn)
                mn = p[i].pr, idx = i;
        if (idx == -1)
        {
            t++;
            continue;
        }
        t += p[idx].bt;
        p[idx].ct = t;
        p[idx].tat = t - p[idx].at;
        p[idx].wt = p[idx].tat - p[idx].bt;
        vis[idx] = 1;
        done++;
    }
    cout << "\n[Priority Non-Preemptive]\n";
    print(p, true);
}

void rr(vector<P> &p, int q) {
    sort(p.begin(), p.end(), [](auto &a, auto &b){ return a.at < b.at; });
    for (auto &x : p) x.rem = x.bt;

    queue<int> Q;
    int t = p[0].at, i = 0, n = p.size(), done = 0;
    Q.push(0);
    i = 1; // ✅ Important: move index forward

    while (done < n) {
        if (Q.empty()) {
            if (i < n) {
                t = max(t, p[i].at);
                while (i < n && p[i].at <= t)
                    Q.push(i++);
            }
            continue;
        }

        int k = Q.front(); Q.pop();
        int run = min(q, p[k].rem);
        p[k].rem -= run;
        t += run;

        while (i < n && p[i].at <= t)
            Q.push(i++);

        if (p[k].rem)
            Q.push(k);
        else {
            done++;
            p[k].ct = t;
            p[k].tat = t - p[k].at;
            p[k].wt = p[k].tat - p[k].bt;
        }
    }

    cout << "\n[Round Robin]\n";
    print(p);
}


int main()
{
    int n;
    cout << "Enter no. of processes: ";
    cin >> n;
    vector<P> p(n);
    cout << "Enter AT BT PR for each:\n";
    for (int i = 0; i < n; i++)
    {
        p[i].id = i + 1;
        cin >> p[i].at >> p[i].bt >> p[i].pr;
    }
    int c, q;
    do
    {
        cout << "\n1.FCFS 2.SJF 3.Priority 4.RR 5.Exit\nChoice: ";
        cin >> c;
        if (c == 1)
            fcfs(p);
        else if (c == 2)
            sjf(p);
        else if (c == 3)
            priority(p);
        else if (c == 4)
        {
            cout << "Enter Quantum: ";
            cin >> q;
            rr(p, q);
        }
    } while (c != 5);
}
