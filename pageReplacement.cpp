#include <bits/stdc++.h>
using namespace std;

// 🔹 FIFO (First In First Out)
int fifo(vector<int> p, int f)
{
    queue<int> q;
    unordered_set<int> s;
    int pf = 0;

    for (int x : p)
    {
        // Page not in frame -> page fault
        if (!s.count(x))
        {
            // Frame full -> remove oldest page
            if (s.size() == f)
            {
                s.erase(q.front());
                q.pop();
            }
            s.insert(x);
            q.push(x);
            pf++;
        }
        // else it's a hit, do nothing
    }

    return pf;
}

// 🔹 LRU (Least Recently Used)
int lru(vector<int> p, int f)
{
    list<int> l; // front = most recent, back = least recent
    unordered_map<int, list<int>::iterator> pos;
    int pf = 0;

    for (int x : p)
    {
        // Page not found → page fault
        if (pos.find(x) == pos.end())
        {
            // Frame full → remove least recently used
            if (l.size() == f)
            {
                int last = l.back();
                l.pop_back();
                pos.erase(last);
            }
            // Insert at front (most recently used)
            l.push_front(x);
            pos[x] = l.begin();
            pf++;
        }
        else
        {
            // Page hit → move page to front (most recent)
            l.erase(pos[x]);
            l.push_front(x);
            pos[x] = l.begin();
        }
    }

    return pf;
}

// 🔹 OPTIMAL (Farthest Future Use)
int optimal(vector<int> p, int f)
{
    vector<int> fr;
    int pf = 0;

    for (int i = 0; i < p.size(); i++)
    {
        // Page not present → page fault
        if (find(fr.begin(), fr.end(), p[i]) == fr.end())
        {
            // Frame has empty space → just add
            if (fr.size() < f)
                fr.push_back(p[i]);
            else
            {
                int far = i + 1, idx = 0;
                for (int j = 0; j < f; j++)
                {
                    int k;
                    for (k = i + 1; k < p.size(); k++)
                        if (fr[j] == p[k])
                            break;

                    // if this page will be used farthest in future
                    if (k > far)
                    {
                        far = k;
                        idx = j;
                    }

                    // if page never used again
                    if (k == p.size())
                    {
                        idx = j;
                        break;
                    }
                }
                fr[idx] = p[i];
            }
            pf++;
        }
        // else it's a hit → do nothing
    }

    return pf;
}

// 🔹 MAIN FUNCTION
int main()
{
    int n, f, ch;
    cout << "Enter no. of pages: ";
    cin >> n;

    vector<int> p(n);
    cout << "Enter page references: ";
    for (int i = 0; i < n; i++)
        cin >> p[i];

    cout << "Enter frame size: ";
    cin >> f;

    do
    {
        cout << "\n1. FIFO  2. LRU  3. OPTIMAL  4. EXIT\nChoice: ";
        cin >> ch;

        int pf = 0;
        if (ch == 1)
            pf = fifo(p, f);
        else if (ch == 2)
            pf = lru(p, f);
        else if (ch == 3)
            pf = optimal(p, f);
        else
            break;

        cout << "Page Faults = " << pf << "  |  Hits = " << n - pf << "\n";
    } while (ch != 4);

    return 0;
}
