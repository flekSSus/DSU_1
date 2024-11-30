#include<iostream>
#include<fstream>
#include<vector>


size_t GoToLeader(std::vector<int>& DSU,size_t index)
{
    if(DSU[index]>=0)
    {
        DSU[index]=GoToLeader(DSU,DSU[index]);
        return DSU[index];
    }

    return index;
}

bool MergeTowns(std::vector<int>& dsu, size_t el_1,size_t el_2)
{
    size_t rootEl_1(GoToLeader(dsu,el_1));
    size_t rootEl_2(GoToLeader(dsu,el_2));
   
    if(rootEl_1!=rootEl_2)
    {
        if(dsu[rootEl_1]>=dsu[rootEl_2]) 
        {
            dsu[rootEl_1]=rootEl_2;
            --dsu[rootEl_2];
        }
        else
        {
            dsu[rootEl_2]=rootEl_1;
            --dsu[rootEl_1];
        }
        return true;
    }
    else
        return false;
}



int main()
{
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");

    size_t numOfTowns(0);
    size_t numOfRoads(0);
    size_t numOfComponents(0);

    in>>numOfTowns>>numOfRoads;
    
    std::vector<int> arrOfDSU(numOfTowns+1);
    for(size_t i(1);i<arrOfDSU.size();++i)
        arrOfDSU[i]=-1;

    numOfComponents=numOfTowns;

    for(size_t i(0);i<numOfRoads;++i)
    {
        size_t el_1(0),el_2(0);
        in>>el_1>>el_2;
    
        if(MergeTowns(arrOfDSU,el_1,el_2))
            --numOfComponents;

        out<<numOfComponents<<'\n';
    }

    in.close();
    out.close();
}
