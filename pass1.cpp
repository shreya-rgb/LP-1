#include <bits/stdc++.h>
using namespace std;

struct MNT {
    string name;
    int pp, kp, mdtp, kpdptr, pntabptr;
};

int main() {
    ifstream fin("input.txt");
    if(!fin) { cout << "Error opening input.txt\n"; return 0; }

    vector<MNT> MNTTAB;
    vector<string> MDT, PNTAB, INTERMEDIATE;
    vector<pair<string,string>> KPDTAB;
    bool inMacro = false;
    MNT curr;
    string line;

    while(getline(fin, line)) {
        if(line == "MACRO") { inMacro = true; curr = MNT{}; continue; }
        if(!inMacro) { INTERMEDIATE.push_back(line); continue; }

        stringstream ss(line);
        vector<string> words;
        string w; while(ss >> w) words.push_back(w);

        if(curr.name.empty()) {
            curr.name = words[0];
            curr.mdtp = MDT.size() + 1;
            curr.kpdptr = KPDTAB.size() + 1;
            curr.pntabptr = PNTAB.size() + 1;
            curr.pp = curr.kp = 0;

            for(int i=1;i<words.size();i++) {
                string tok = words[i];
                if(tok[0]=='&') {
                    int eq = tok.find('=');
                    if(eq != string::npos) {
                        string pname = tok.substr(0, eq);
                        string def = tok.substr(eq+1);
                        KPDTAB.push_back({pname, def});
                        PNTAB.push_back(pname);
                        curr.kp++;
                    } else {
                        PNTAB.push_back(tok);
                        curr.pp++;
                    }
                }
            }
            continue;
        }

        if(words[0] == "MEND") {
            MDT.push_back("MEND");
            inMacro = false;
            MNTTAB.push_back(curr);
            continue;
        }

        string newline = "";
        for(string &t : words) {
            if(t[0]=='&') {
                int pos = find(PNTAB.begin(), PNTAB.end(), t) - PNTAB.begin() + 1;
                newline += "#" + to_string(pos) + " ";
            } else newline += t + " ";
        }
        MDT.push_back(newline);
    }

    // Write MNT
    ofstream mnt("mnt.txt");
    mnt << "Name\tPP\tKP\tMDTP\tKPDTP\tPNTABP\n";
    for(auto &e : MNTTAB)
        mnt << e.name << "\t" << e.pp << "\t" << e.kp << "\t"
            << e.mdtp << "\t" << e.kpdptr << "\t" << e.pntabptr << "\n";
    mnt.close();

    // Write PNTAB
    ofstream pnt("pntab.txt");
    for(int i=0;i<PNTAB.size();i++)
        pnt << i+1 << "\t" << PNTAB[i] << "\n";
    pnt.close();

    // Write KPDTAB
    ofstream kpd("kpdtab.txt");
    for(int i=0;i<KPDTAB.size();i++)
        kpd << i+1 << "\t" << KPDTAB[i].first << "\t" << KPDTAB[i].second << "\n";
    kpd.close();

    // Write MDT
    ofstream mdt("mdt.txt");
    for(int i=0;i<MDT.size();i++)
        mdt << i+1 << "\t" << MDT[i] << "\n";
    mdt.close();

    // Write INTERMEDIATE
    ofstream inter("intermediate.txt");
    for(auto &l : INTERMEDIATE)
        inter << l << "\n";
    inter.close();

    cout << "Pass 1 completed. Output files generated.\n";
    return 0;
}
