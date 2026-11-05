#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;

int main()
{
    cout << "EXERCISE 1" << endl << endl;
    ifstream f("sequence.fasta");
    if (!f.is_open())
    {
        cout << "Could not open the file!" << endl;
        return 1;
    }

    string line, dna = "";
    while (getline(f, line))
    {
        if (line[0] == '>')
            continue;
        for (int i = 0; i < line.length(); i++)
            if (line[i] == 'A' || line[i] == 'C' || line[i] == 'G' || line[i] == 'T')
                dna += line[i];
    }
    f.close();

    int n = dna.length();
    cout << "DNA sequence length: " << n << endl << endl;


    srand(time(0));
    string samples[10];
    int maxLen = n;
    if (maxLen > 3000)
        maxLen = 3000;

    for (int i = 0; i < 10; i++)
    {
        int len = 100 + rand() % (maxLen - 100 + 1);
        int start = rand() % (n - len + 1);
        samples[i] = dna.substr(start, len);
        cout << "Sample " << i + 1 << ": " << len << " bp (starts at position " << start << ")" << endl;
    }

    int rows = 25;
    int pos[10];
    for (int i = 0; i < 10; i++)
    {
        double d = (log10(3000.0) - log10(samples[i].length())) / (log10(3000.0) - log10(100.0));
        pos[i] = 1 + (int)(d * (rows - 2));
    }

    cout << endl << "Electrophoresis gel:" << endl << endl;
    cout << "     ";
    for (int i = 0; i < 10; i++)
    {
        cout << "S" << i + 1;
        if (i < 9) cout << "   ";
        else cout << "  ";
    }
    cout << endl;

    cout << "(-)  ";
    for (int i = 0; i < 10; i++)
        cout << "|_|  ";
    cout << " <- wells" << endl;

    for (int r = 1; r < rows; r++)
    {
        cout << "     ";
        for (int i = 0; i < 10; i++)
        {
            if (pos[i] == r)
                cout << "===  ";
            else
                cout << "     ";
        }

        for (int i = 0; i < 10; i++)
            if (pos[i] == r)
                cout << " S" << i + 1 << "=" << samples[i].length() << "bp";
        cout << endl;
    }
    cout << "(+)" << endl << endl;


    int idx[10];
    for (int i = 0; i < 10; i++)
        idx[i] = i;

    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9 - i; j++)
            if (samples[idx[j]].length() > samples[idx[j + 1]].length())
            {
                int aux = idx[j];
                idx[j] = idx[j + 1];
                idx[j + 1] = aux;
            }

    cout << "From the fastest to the slowest fragment:" << endl;
    for (int i = 0; i < 10; i++)
        cout << i + 1 << ". Sample " << idx[i] + 1 << " - " << samples[idx[i]].length() << " bp" << endl;


    cout << endl << " EXERCISE 2" << endl << endl;

    int count = 0;
    cout << "Pos\tUnit\tCopies\tLength\tRepeat" << endl;

    for (int u = 3; u <= 5; u++)
    {
        int i = 0;
        while (i + 2 * u <= n)
        {
            string unit = dna.substr(i, u);

            int copies = 1;
            while (i + (copies + 1) * u <= n && dna.substr(i + copies * u, u) == unit)
                copies++;

            int total = copies * u;

            if (copies >= 2 && total >= 6 && total <= 10)
            {
                count++;
                cout << i + 1 << "\t" << unit << "\t" << copies << "\t" << total << "\t" << dna.substr(i, total) << endl;
                i = i + total;
            }
            else if (copies >= 2)
                i = i + total;
            else
                i++;
        }
    }

    cout << endl << "Repeats found: " << count << endl;

    return 0;
}
