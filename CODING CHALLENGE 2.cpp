#include <iostream>
using namespace std;

class Candidate
{
public:
    string name;
    int totalVotes;
};

class Election
{
public:
    static int regions;

    void process()
    {
        int c;
        cout << "Enter number of candidates: ";
        cin >> c;

        Candidate cand[50];
        int votes[50][50];

        for(int i = 0; i < c; i++)
        {
            cout << "Enter candidate name: ";
            cin >> cand[i].name;
            cand[i].totalVotes = 0;
        }

        for(int i = 0; i < regions; i++)
        {
            cout << "\nRegion " << i + 1 << endl;

            for(int j = 0; j < c; j++)
            {
                cout << "Votes for " << cand[j].name << ": ";
                cin >> votes[i][j];
            }
        }

        for(int i = 0; i < regions; i++)
        {
            int maxVotes = votes[i][0];
            string winner = cand[0].name;

            for(int j = 0; j < c; j++)
            {
                cand[j].totalVotes += votes[i][j];

                if(votes[i][j] > maxVotes)
                {
                    maxVotes = votes[i][j];
                    winner = cand[j].name;
                }
            }

            cout << "Region " << i + 1 << " Winner: " << winner << endl;
        }

        int maxTotal = cand[0].totalVotes;
        string overall = cand[0].name;

        for(int i = 1; i < c; i++)
        {
            if(cand[i].totalVotes > maxTotal)
            {
                maxTotal = cand[i].totalVotes;
                overall = cand[i].name;
            }
        }

        cout << "Overall Winner: " << overall << endl;
    }
};

int Election::regions = 0;

int main()
{
    cout << "Enter number of regions: ";
    cin >> Election::regions;

    Election e;
    e.process();

    return 0;
}
