#include<iostream>
#include<fstream>
#include<vector>

int CountDSU(const std::vector<int>& DSU)
{
    int count(0);
    for(int i: DSU)
       if(i<0)
           ++count; 
    return count;
}

void GoToLeader(const std::vector<int>& DSU,size_t& index)
{
    if(DSU[index]>0)
        while(DSU[index]>0)
            index=DSU[index];
    return;
}

int main()
{
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");

    size_t numOfTowns(0);
    size_t numOfRoads(0);

    in>>numOfTowns>>numOfRoads;
    
    std::vector<int > arrOfDSU(numOfTowns+1,-1);

    arrOfDSU[0]=0;
    for(size_t i(0);i < numOfRoads;++i)
    {
        if(CountDSU(arrOfDSU)==1)
        {
            out<<1;
            break;
        }
        size_t indexFisrtTown(0),indexSecondTown(0);

        in>>indexFisrtTown>>indexSecondTown;
        
        size_t leaderFirst(indexFisrtTown),leaderSecond(indexSecondTown);

        GoToLeader(arrOfDSU,leaderFirst);
        GoToLeader(arrOfDSU,leaderSecond);

        if(arrOfDSU[leaderFirst]>=arrOfDSU[leaderSecond])
        {
            arrOfDSU[leaderSecond]+=arrOfDSU[leaderFirst];
            arrOfDSU[leaderFirst]=leaderSecond;
        }
        else
        {
            arrOfDSU[leaderFirst]+=arrOfDSU[leaderSecond];
            arrOfDSU[leaderSecond]=leaderFirst;
        }
        out<<CountDSU(arrOfDSU)<<"\n";

    }

    in.close();
    out.close();
}
