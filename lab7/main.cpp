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

string invertedComplement(string p)
{
    string r = "";
    for (int i = p.length() - 1; i >= 0; i--)
        r += complement(p[i]);
    return r;
}

int main()
{
    int MIN_GAP = 10;
    int MAX_GAP = 50;
    ifstream f("sequence.fasta");
    if (!f.is_open())
    {
        cout << "Could not open sequence.fasta!" << endl;
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

    ofstream out("results.txt");
    int found = 0;

    for (int len = 4; len <= 5; len++)
    {
        for (int i = 0; i + len <= n; i++)
        {
            string pattern = dna.substr(i, len);
            string ic = invertedComplement(pattern);


            int start = i + len + MIN_GAP;
            int stop = i + len + MAX_GAP;
            if (stop > n - len)
                stop = n - len;

            for (int j = start; j <= stop; j++)
            {
                if (dna.substr(j, len) == ic)
                {
                    found++;
                    int gap = j - (i + len);
                    out << found << ". " << pattern << " at " << i + 1 << "-" << i + len
                        << "   " << ic << " at " << j + 1 << "-" << j + len
                        << "   gap " << gap << endl;
                    if (found <= 30)
                        cout << found << ". " << pattern << " at " << i + 1 << "-" << i + len
                             << "   " << ic << " at " << j + 1 << "-" << j + len
                             << "   gap " << gap << endl;
                }
            }
        }
    }
    out.close();

    cout << endl << "Total found: " << found << endl;
    cout << "All results are in results.txt" << endl;

    return 0;
}
