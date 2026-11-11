#include <iostream>
#include <fstream>
#include <string>
using namespace std;

char complement(char c)
{
    if (c == 'A') return 'T';
    if (c == 'T') return 'A';
    if (c == 'C') return 'G';
    return 'C';
}

int main()
{
    int K = 15;
    int MIN_DIST = 100;
    int MAX_DIST = 5000;

    ifstream f("sequence.fasta");
    if (!f.is_open())
    {
        cout << "Could not open file!" << endl;
        return 1;
    }

    string line, dna = "";
    while (getline(f, line))
    {
        if (line.empty() || line[0] == '>')
            continue;
        for (int i = 0; i < line.length(); i++)
        {
            char c = toupper(line[i]);
            if (c == 'A' || c == 'C' || c == 'G' || c == 'T')
                dna += c;
        }
    }
    f.close();

    int n = dna.length();
    cout << "Genome length: " << n << endl << endl;

    ofstream out("transposons.txt");
    int found = 0;

    for (int i = 0; i + K <= n; i++)
    {
        string rc = "";
        for (int t = K - 1; t >= 0; t--)
            rc += complement(dna[i + t]);

        int from = i + K + MIN_DIST;
        int to = i + K + MAX_DIST;
        if (to > n - K)
            to = n - K;

        for (int j = from; j <= to; j++)
        {
            if (dna[j] != rc[0])
                continue;

            int t = 1;
            while (t < K && dna[j + t] == rc[t])
                t++;
            if (t < K)
                continue;

            if (i > 0 && j + K < n && dna[i - 1] == complement(dna[j + K]))
                continue;

            int len = K;
            int s2 = j;
            while (i + len < s2 - 1 - MIN_DIST && dna[i + len] == complement(dna[s2 - 1]))
            {
                len++;
                s2--;
            }

            int tStart = i + 1;
            int tEnd = s2 + len;
            found++;

            out << found << ". " << tStart << " - " << tEnd << "  length " << tEnd - tStart + 1
                << "  IR " << len << ": " << dna.substr(i, len) << " ... " << dna.substr(s2, len) << endl;

            if (found <= 20)
                cout << found << ". " << tStart << " - " << tEnd << "  length " << tEnd - tStart + 1
                     << "  IR " << len << ": " << dna.substr(i, len) << " ... " << dna.substr(s2, len) << endl;
        }
    }
    out.close();

    cout << endl << "Possible transposons found: " << found << endl;
    cout << "All of them are saved in transposons.txt" << endl;

    return 0;
}
