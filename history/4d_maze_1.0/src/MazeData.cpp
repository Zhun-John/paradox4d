#include "Maze4D.h"

void EMaze4D::Init(int level)
{
    if (level==1)
    {
        mx=5; my=5; mz=1; md='Z';
        sx=3; sy=1; sz=0; sd='A';

        if (data)
        {
            free(data);
        }
        data = (char *)malloc((mx+1)*my*mz*(md-'A'));
        if (!data) exit(0);

        strncpy_s( Data(0,4,0,'A'), mx+1, "BCDFH", mx );
        strncpy_s( Data(0,3,0,'A'), mx+1, "A....", mx );
        strncpy_s( Data(0,2,0,'A'), mx+1, "AAAA.", mx );
        strncpy_s( Data(0,1,0,'A'), mx+1, "A..A.", mx );
        strncpy_s( Data(0,0,0,'A'), mx+1, ".....", mx );

        strncpy_s( Data(0,4,0,'B'), mx+1, "BCDFH", mx );
        strncpy_s( Data(0,3,0,'B'), mx+1, "A.E.H", mx );
        strncpy_s( Data(0,2,0,'B'), mx+1, "AA...", mx );
        strncpy_s( Data(0,1,0,'B'), mx+1, "A....", mx );
        strncpy_s( Data(0,0,0,'B'), mx+1, ".....", mx );

        strncpy_s( Data(0,4,0,'C'), mx+1, "BCDFH", mx );
        strncpy_s( Data(0,3,0,'C'), mx+1, "A.E.H", mx );
        strncpy_s( Data(0,2,0,'C'), mx+1, "A.GJ.", mx );
        strncpy_s( Data(0,1,0,'C'), mx+1, "A.M..", mx );
        strncpy_s( Data(0,0,0,'C'), mx+1, "..OO.", mx );

        strncpy_s( Data(0,4,0,'D'), mx+1, "BCDFH", mx );
        strncpy_s( Data(0,3,0,'D'), mx+1, "A.E.H", mx );
        strncpy_s( Data(0,2,0,'D'), mx+1, ".GGJ.", mx );
        strncpy_s( Data(0,1,0,'D'), mx+1, "..M..", mx );
        strncpy_s( Data(0,0,0,'D'), mx+1, ".NOO.", mx );

        strncpy_s( Data(0,4,0,'E'), mx+1, "BCDFH", mx );
        strncpy_s( Data(0,3,0,'E'), mx+1, "..E..", mx );
        strncpy_s( Data(0,2,0,'E'), mx+1, "GGGJK", mx );
        strncpy_s( Data(0,1,0,'E'), mx+1, "G.M.L", mx );
        strncpy_s( Data(0,0,0,'E'), mx+1, ".NOO.", mx );

        strncpy_s( Data(0,4,0,'F'), mx+1, "BCDFH", mx );
        strncpy_s( Data(0,3,0,'F'), mx+1, "A.E.H", mx );
        strncpy_s( Data(0,2,0,'F'), mx+1, ".GG.H", mx );
        strncpy_s( Data(0,1,0,'F'), mx+1, "..M.H", mx );
        strncpy_s( Data(0,0,0,'F'), mx+1, ".NO.I", mx );

        strncpy_s( Data(0,4,0,'G'), mx+1, ".CDF.", mx );
        strncpy_s( Data(0,3,0,'G'), mx+1, "G.E.V", mx );
        strncpy_s( Data(0,2,0,'G'), mx+1, "GGGJK", mx );
        strncpy_s( Data(0,1,0,'G'), mx+1, "G.M.L", mx );
        strncpy_s( Data(0,0,0,'G'), mx+1, ".NOO.", mx );

        strncpy_s( Data(0,4,0,'H'), mx+1, "BCDFH", mx );
        strncpy_s( Data(0,3,0,'H'), mx+1, "A.E.H", mx );
        strncpy_s( Data(0,2,0,'H'), mx+1, "...HH", mx );
        strncpy_s( Data(0,1,0,'H'), mx+1, "....H", mx );
        strncpy_s( Data(0,0,0,'H'), mx+1, "WWWUI", mx );

        strncpy_s( Data(0,4,0,'I'), mx+1, "...FH", mx );
        strncpy_s( Data(0,3,0,'I'), mx+1, "W...H", mx );
        strncpy_s( Data(0,2,0,'I'), mx+1, "W..HH", mx );
        strncpy_s( Data(0,1,0,'I'), mx+1, "WWW.H", mx );
        strncpy_s( Data(0,0,0,'I'), mx+1, "WWWUI", mx );

        strncpy_s( Data(0,4,0,'J'), mx+1, ".CD.X", mx );
        strncpy_s( Data(0,3,0,'J'), mx+1, "G.E.V", mx );
        strncpy_s( Data(0,2,0,'J'), mx+1, "GGGJK", mx );
        strncpy_s( Data(0,1,0,'J'), mx+1, "G.M.L", mx );
        strncpy_s( Data(0,0,0,'J'), mx+1, ".NO.S", mx );

        strncpy_s( Data(0,4,0,'K'), mx+1, "...YX", mx );
        strncpy_s( Data(0,3,0,'K'), mx+1, "G.E.V", mx );
        strncpy_s( Data(0,2,0,'K'), mx+1, "GGGJK", mx );
        strncpy_s( Data(0,1,0,'K'), mx+1, "G.M.L", mx );
        strncpy_s( Data(0,0,0,'K'), mx+1, "...SS", mx );

        strncpy_s( Data(0,4,0,'L'), mx+1, "...YX", mx );
        strncpy_s( Data(0,3,0,'L'), mx+1, "G.E.V", mx );
        strncpy_s( Data(0,2,0,'L'), mx+1, "GGGJK", mx );
        strncpy_s( Data(0,1,0,'L'), mx+1, "....L", mx );
        strncpy_s( Data(0,0,0,'L'), mx+1, ".SSSS", mx );

        strncpy_s( Data(0,4,0,'M'), mx+1, ".CDF.", mx );
        strncpy_s( Data(0,3,0,'M'), mx+1, "G.E.V", mx );
        strncpy_s( Data(0,2,0,'M'), mx+1, "GGGJK", mx );
        strncpy_s( Data(0,1,0,'M'), mx+1, "..M..", mx );
        strncpy_s( Data(0,0,0,'M'), mx+1, "PNOO.", mx );

        strncpy_s( Data(0,4,0,'N'), mx+1, "R.DF.", mx );
        strncpy_s( Data(0,3,0,'N'), mx+1, "R.E..", mx );
        strncpy_s( Data(0,2,0,'N'), mx+1, "R.GJ.", mx );
        strncpy_s( Data(0,1,0,'N'), mx+1, "Q.M..", mx );
        strncpy_s( Data(0,0,0,'N'), mx+1, "PNOO.", mx );

        strncpy_s( Data(0,4,0,'O'), mx+1, ".CDF.", mx );
        strncpy_s( Data(0,3,0,'O'), mx+1, "..E..", mx );
        strncpy_s( Data(0,2,0,'O'), mx+1, ".GGJ.", mx );
        strncpy_s( Data(0,1,0,'O'), mx+1, "Q.M..", mx );
        strncpy_s( Data(0,0,0,'O'), mx+1, "PNOO.", mx );

        strncpy_s( Data(0,4,0,'P'), mx+1, "RTTT.", mx );
        strncpy_s( Data(0,3,0,'P'), mx+1, "RTT..", mx );
        strncpy_s( Data(0,2,0,'P'), mx+1, "RT...", mx );
        strncpy_s( Data(0,1,0,'P'), mx+1, "Q.M..", mx );
        strncpy_s( Data(0,0,0,'P'), mx+1, "PNOO.", mx );

        strncpy_s( Data(0,4,0,'Q'), mx+1, "RTTTT", mx );
        strncpy_s( Data(0,3,0,'Q'), mx+1, "RTTTT", mx );
        strncpy_s( Data(0,2,0,'Q'), mx+1, "RTTTT", mx );
        strncpy_s( Data(0,1,0,'Q'), mx+1, "Q....", mx );
        strncpy_s( Data(0,0,0,'Q'), mx+1, "PNOO.", mx );

        strncpy_s( Data(0,4,0,'R'), mx+1, "RTTTT", mx );
        strncpy_s( Data(0,3,0,'R'), mx+1, "RTTTT", mx );
        strncpy_s( Data(0,2,0,'R'), mx+1, "RTTTT", mx );
        strncpy_s( Data(0,1,0,'R'), mx+1, "Q.TTT", mx );
        strncpy_s( Data(0,0,0,'R'), mx+1, "PNTTT", mx );

        strncpy_s( Data(0,4,0,'S'), mx+1, "...YX", mx );
        strncpy_s( Data(0,3,0,'S'), mx+1, "....V", mx );
        strncpy_s( Data(0,2,0,'S'), mx+1, "...JK", mx );
        strncpy_s( Data(0,1,0,'S'), mx+1, ".SS.L", mx );
        strncpy_s( Data(0,0,0,'S'), mx+1, ".SSSS", mx );

        strncpy_s( Data(0,4,0,'T'), mx+1, "RTTTT", mx );
        strncpy_s( Data(0,3,0,'T'), mx+1, "RTTTT", mx );
        strncpy_s( Data(0,2,0,'T'), mx+1, "RTTTT", mx );
        strncpy_s( Data(0,1,0,'T'), mx+1, "Q.TTT", mx );
        strncpy_s( Data(0,0,0,'T'), mx+1, "P.TTT", mx );

        strncpy_s( Data(0,4,0,'U'), mx+1, "WWW.H", mx );
        strncpy_s( Data(0,3,0,'U'), mx+1, "WWW.H", mx );
        strncpy_s( Data(0,2,0,'U'), mx+1, "W.W.H", mx );
        strncpy_s( Data(0,1,0,'U'), mx+1, "WWW.H", mx );
        strncpy_s( Data(0,0,0,'U'), mx+1, "WWWUI", mx );

        strncpy_s( Data(0,4,0,'V'), mx+1, "WWWYX", mx );
        strncpy_s( Data(0,3,0,'V'), mx+1, "....V", mx );
        strncpy_s( Data(0,2,0,'V'), mx+1, "GGGJK", mx );
        strncpy_s( Data(0,1,0,'V'), mx+1, "G.M.L", mx );
        strncpy_s( Data(0,0,0,'V'), mx+1, "...SS", mx );

        strncpy_s( Data(0,4,0,'W'), mx+1, "WWWYX", mx );
        strncpy_s( Data(0,3,0,'W'), mx+1, "WWW.V", mx );
        strncpy_s( Data(0,2,0,'W'), mx+1, "W.W..", mx );
        strncpy_s( Data(0,1,0,'W'), mx+1, "WWW.H", mx );
        strncpy_s( Data(0,0,0,'W'), mx+1, "WWWUI", mx );

        strncpy_s( Data(0,4,0,'X'), mx+1, "WWWYX", mx );
        strncpy_s( Data(0,3,0,'X'), mx+1, "WWW.V", mx );
        strncpy_s( Data(0,2,0,'X'), mx+1, "W..JK", mx );
        strncpy_s( Data(0,1,0,'X'), mx+1, "W...L", mx );
        strncpy_s( Data(0,0,0,'X'), mx+1, "...SS", mx );

        strncpy_s( Data(0,4,0,'Y'), mx+1, "WWWYX", mx );
        strncpy_s( Data(0,3,0,'Y'), mx+1, "WWW.V", mx );
        strncpy_s( Data(0,2,0,'Y'), mx+1, "W.W.K", mx );
        strncpy_s( Data(0,1,0,'Y'), mx+1, "WWW.L", mx );
        strncpy_s( Data(0,0,0,'Y'), mx+1, "WWW.S", mx );

    }                                            
    if (level==2)                                
    {                                            
    }                                            
    if (level==3)                                
    {
    }
}

