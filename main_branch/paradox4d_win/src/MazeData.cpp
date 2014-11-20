#include "Maze4D.h"

//初始化某一关的所有迷宫地形数据
void EMaze4D::InitData(int level)
{
    // XYw型7x4立柱
    if (level==1)                                
    {
        size = CIndex4(8,4,1,'J');
        start = CIndex4(0,0,0,'A');
        end = CIndex4(1,3,0,'H');

        if (data) free(data);
        data = (char *)malloc(size.Capacity());
        if (!data) exit(0);

        strncpy_s( DataAt(0, 3,0,'A'), size.x, "..CCDEE", size.x-1 );
        strncpy_s( DataAt(0, 2,0,'A'), size.x, "AAA....", size.x-1 );
        strncpy_s( DataAt(0, 1,0,'A'), size.x, "A.BIII.", size.x-1 );
        strncpy_s( DataAt(0, 0,0,'A'), size.x, "A......", size.x-1 );

        strncpy_s( DataAt(0, 3,0,'B'), size.x, "..CC.I.", size.x-1 );
        strncpy_s( DataAt(0, 2,0,'B'), size.x, "AAA.II.", size.x-1 );
        strncpy_s( DataAt(0, 1,0,'B'), size.x, "..BIII.", size.x-1 );
        strncpy_s( DataAt(0, 0,0,'B'), size.x, ".......", size.x-1 );

        strncpy_s( DataAt(0, 3,0,'C'), size.x, "..CCDEE", size.x-1 );
        strncpy_s( DataAt(0, 2,0,'C'), size.x, "AAA.FFF", size.x-1 );
        strncpy_s( DataAt(0, 1,0,'C'), size.x, "A.BIGFF", size.x-1 );
        strncpy_s( DataAt(0, 0,0,'C'), size.x, "....HGG", size.x-1 );

        strncpy_s( DataAt(0, 3,0,'D'), size.x, "..CCDEE", size.x-1 );
        strncpy_s( DataAt(0, 2,0,'D'), size.x, "AAA.FFF", size.x-1 );
        strncpy_s( DataAt(0, 1,0,'D'), size.x, "A..HGFF", size.x-1 );
        strncpy_s( DataAt(0, 0,0,'D'), size.x, "..HHHGG", size.x-1 );

        strncpy_s( DataAt(0, 3,0,'E'), size.x, "..CCDEE", size.x-1 );
        strncpy_s( DataAt(0, 2,0,'E'), size.x, "AAA.FFF", size.x-1 );
        strncpy_s( DataAt(0, 1,0,'E'), size.x, "AHHHGFF", size.x-1 );
        strncpy_s( DataAt(0, 0,0,'E'), size.x, ".HHHHGG", size.x-1 );

        strncpy_s( DataAt(0, 3,0,'F'), size.x, "..CCDEE", size.x-1 );
        strncpy_s( DataAt(0, 2,0,'F'), size.x, ".HH.FFF", size.x-1 );
        strncpy_s( DataAt(0, 1,0,'F'), size.x, ".HHHGFF", size.x-1 );
        strncpy_s( DataAt(0, 0,0,'F'), size.x, ".HHHHGG", size.x-1 );

        strncpy_s( DataAt(0, 3,0,'G'), size.x, ".HCCDEE", size.x-1 );
        strncpy_s( DataAt(0, 2,0,'G'), size.x, ".HH.FFF", size.x-1 );
        strncpy_s( DataAt(0, 1,0,'G'), size.x, ".HHHGFF", size.x-1 );
        strncpy_s( DataAt(0, 0,0,'G'), size.x, ".HHHHGG", size.x-1 );

        strncpy_s( DataAt(0, 3,0,'H'), size.x, ".H.CDEE", size.x-1 );
        strncpy_s( DataAt(0, 2,0,'H'), size.x, ".HH.FFF", size.x-1 );
        strncpy_s( DataAt(0, 1,0,'H'), size.x, ".HHHGFF", size.x-1 );
        strncpy_s( DataAt(0, 0,0,'H'), size.x, ".HHHHGG", size.x-1 );

        strncpy_s( DataAt(0, 3,0,'I'), size.x, "..C.II.", size.x-1 );
        strncpy_s( DataAt(0, 2,0,'I'), size.x, "AAA.II.", size.x-1 );
        strncpy_s( DataAt(0, 1,0,'I'), size.x, "..BIII.", size.x-1 );
        strncpy_s( DataAt(0, 0,0,'I'), size.x, ".......", size.x-1 );

        return;
    }

    // XYw型5x5田字迷乱
    if (level==2)
    {
        size = CIndex4(6,5,1,'Z');
        start = CIndex4(3,1,0,'A');
        end = CIndex4(2,0,0,'T');

        if (data) free(data);
        data = (char *)malloc(size.Capacity());
        if (!data) exit(0);

        strncpy_s( DataAt(0,4,0,'A'), size.x, "BCDFH", size.x-1 );
        strncpy_s( DataAt(0,3,0,'A'), size.x, "A....", size.x-1 );
        strncpy_s( DataAt(0,2,0,'A'), size.x, "AAAA.", size.x-1 );
        strncpy_s( DataAt(0,1,0,'A'), size.x, "A..A.", size.x-1 );
        strncpy_s( DataAt(0,0,0,'A'), size.x, ".....", size.x-1 );

        strncpy_s( DataAt(0,4,0,'B'), size.x, "BCDFH", size.x-1 );
        strncpy_s( DataAt(0,3,0,'B'), size.x, "A.E.H", size.x-1 );
        strncpy_s( DataAt(0,2,0,'B'), size.x, "AA...", size.x-1 );
        strncpy_s( DataAt(0,1,0,'B'), size.x, "A....", size.x-1 );
        strncpy_s( DataAt(0,0,0,'B'), size.x, ".....", size.x-1 );

        strncpy_s( DataAt(0,4,0,'C'), size.x, "BCDFH", size.x-1 );
        strncpy_s( DataAt(0,3,0,'C'), size.x, "A.E.H", size.x-1 );
        strncpy_s( DataAt(0,2,0,'C'), size.x, "A.GJ.", size.x-1 );
        strncpy_s( DataAt(0,1,0,'C'), size.x, "A.M..", size.x-1 );
        strncpy_s( DataAt(0,0,0,'C'), size.x, "..OO.", size.x-1 );

        strncpy_s( DataAt(0,4,0,'D'), size.x, "BCDFH", size.x-1 );
        strncpy_s( DataAt(0,3,0,'D'), size.x, "A.E.H", size.x-1 );
        strncpy_s( DataAt(0,2,0,'D'), size.x, ".GGJ.", size.x-1 );
        strncpy_s( DataAt(0,1,0,'D'), size.x, "..M..", size.x-1 );
        strncpy_s( DataAt(0,0,0,'D'), size.x, ".NOO.", size.x-1 );

        strncpy_s( DataAt(0,4,0,'E'), size.x, "BCDFH", size.x-1 );
        strncpy_s( DataAt(0,3,0,'E'), size.x, "..E..", size.x-1 );
        strncpy_s( DataAt(0,2,0,'E'), size.x, "GGGJK", size.x-1 );
        strncpy_s( DataAt(0,1,0,'E'), size.x, "G.M.L", size.x-1 );
        strncpy_s( DataAt(0,0,0,'E'), size.x, ".NOO.", size.x-1 );

        strncpy_s( DataAt(0,4,0,'F'), size.x, "BCDFH", size.x-1 );
        strncpy_s( DataAt(0,3,0,'F'), size.x, "A.E.H", size.x-1 );
        strncpy_s( DataAt(0,2,0,'F'), size.x, ".GG.H", size.x-1 );
        strncpy_s( DataAt(0,1,0,'F'), size.x, "..M.H", size.x-1 );
        strncpy_s( DataAt(0,0,0,'F'), size.x, ".NO.I", size.x-1 );

        strncpy_s( DataAt(0,4,0,'G'), size.x, ".CDF.", size.x-1 );
        strncpy_s( DataAt(0,3,0,'G'), size.x, "G.E.V", size.x-1 );
        strncpy_s( DataAt(0,2,0,'G'), size.x, "GGGJK", size.x-1 );
        strncpy_s( DataAt(0,1,0,'G'), size.x, "G.M.L", size.x-1 );
        strncpy_s( DataAt(0,0,0,'G'), size.x, ".NOO.", size.x-1 );

        strncpy_s( DataAt(0,4,0,'H'), size.x, "BCDFH", size.x-1 );
        strncpy_s( DataAt(0,3,0,'H'), size.x, "A.E.H", size.x-1 );
        strncpy_s( DataAt(0,2,0,'H'), size.x, "...HH", size.x-1 );
        strncpy_s( DataAt(0,1,0,'H'), size.x, "....H", size.x-1 );
        strncpy_s( DataAt(0,0,0,'H'), size.x, "WWWUI", size.x-1 );

        strncpy_s( DataAt(0,4,0,'I'), size.x, "...FH", size.x-1 );
        strncpy_s( DataAt(0,3,0,'I'), size.x, "W...H", size.x-1 );
        strncpy_s( DataAt(0,2,0,'I'), size.x, "WW.HH", size.x-1 );
        strncpy_s( DataAt(0,1,0,'I'), size.x, "WWW.H", size.x-1 );
        strncpy_s( DataAt(0,0,0,'I'), size.x, "WWWUI", size.x-1 );

        strncpy_s( DataAt(0,4,0,'J'), size.x, ".CD.X", size.x-1 );
        strncpy_s( DataAt(0,3,0,'J'), size.x, "G.E.V", size.x-1 );
        strncpy_s( DataAt(0,2,0,'J'), size.x, "GGGJK", size.x-1 );
        strncpy_s( DataAt(0,1,0,'J'), size.x, "G.M.L", size.x-1 );
        strncpy_s( DataAt(0,0,0,'J'), size.x, ".NO.S", size.x-1 );

        strncpy_s( DataAt(0,4,0,'K'), size.x, "...YX", size.x-1 );
        strncpy_s( DataAt(0,3,0,'K'), size.x, "G.E.V", size.x-1 );
        strncpy_s( DataAt(0,2,0,'K'), size.x, "GGGJK", size.x-1 );
        strncpy_s( DataAt(0,1,0,'K'), size.x, "G.M.L", size.x-1 );
        strncpy_s( DataAt(0,0,0,'K'), size.x, "...SS", size.x-1 );

        strncpy_s( DataAt(0,4,0,'L'), size.x, "...YX", size.x-1 );
        strncpy_s( DataAt(0,3,0,'L'), size.x, "G.E.V", size.x-1 );
        strncpy_s( DataAt(0,2,0,'L'), size.x, "GGGJK", size.x-1 );
        strncpy_s( DataAt(0,1,0,'L'), size.x, "....L", size.x-1 );
        strncpy_s( DataAt(0,0,0,'L'), size.x, ".SSSS", size.x-1 );

        strncpy_s( DataAt(0,4,0,'M'), size.x, ".CDF.", size.x-1 );
        strncpy_s( DataAt(0,3,0,'M'), size.x, "G.E.V", size.x-1 );
        strncpy_s( DataAt(0,2,0,'M'), size.x, "GGGJK", size.x-1 );
        strncpy_s( DataAt(0,1,0,'M'), size.x, "..M..", size.x-1 );
        strncpy_s( DataAt(0,0,0,'M'), size.x, "PNOO.", size.x-1 );

        strncpy_s( DataAt(0,4,0,'N'), size.x, "R.DF.", size.x-1 );
        strncpy_s( DataAt(0,3,0,'N'), size.x, "R.E..", size.x-1 );
        strncpy_s( DataAt(0,2,0,'N'), size.x, "R.GJ.", size.x-1 );
        strncpy_s( DataAt(0,1,0,'N'), size.x, "Q.M..", size.x-1 );
        strncpy_s( DataAt(0,0,0,'N'), size.x, "PNOO.", size.x-1 );

        strncpy_s( DataAt(0,4,0,'O'), size.x, ".CDF.", size.x-1 );
        strncpy_s( DataAt(0,3,0,'O'), size.x, "..E..", size.x-1 );
        strncpy_s( DataAt(0,2,0,'O'), size.x, ".GGJ.", size.x-1 );
        strncpy_s( DataAt(0,1,0,'O'), size.x, "Q.M..", size.x-1 );
        strncpy_s( DataAt(0,0,0,'O'), size.x, "PNOO.", size.x-1 );

        strncpy_s( DataAt(0,4,0,'P'), size.x, "RTTT.", size.x-1 );
        strncpy_s( DataAt(0,3,0,'P'), size.x, "RTT..", size.x-1 );
        strncpy_s( DataAt(0,2,0,'P'), size.x, "RT...", size.x-1 );
        strncpy_s( DataAt(0,1,0,'P'), size.x, "Q.M..", size.x-1 );
        strncpy_s( DataAt(0,0,0,'P'), size.x, "PNOO.", size.x-1 );

        strncpy_s( DataAt(0,4,0,'Q'), size.x, "RTTTT", size.x-1 );
        strncpy_s( DataAt(0,3,0,'Q'), size.x, "RTTTT", size.x-1 );
        strncpy_s( DataAt(0,2,0,'Q'), size.x, "RTTTT", size.x-1 );
        strncpy_s( DataAt(0,1,0,'Q'), size.x, "Q....", size.x-1 );
        strncpy_s( DataAt(0,0,0,'Q'), size.x, "PNOO.", size.x-1 );

        strncpy_s( DataAt(0,4,0,'R'), size.x, "RTTTT", size.x-1 );
        strncpy_s( DataAt(0,3,0,'R'), size.x, "RTTTT", size.x-1 );
        strncpy_s( DataAt(0,2,0,'R'), size.x, "RTTTT", size.x-1 );
        strncpy_s( DataAt(0,1,0,'R'), size.x, "Q.TTT", size.x-1 );
        strncpy_s( DataAt(0,0,0,'R'), size.x, "PNTTT", size.x-1 );

        strncpy_s( DataAt(0,4,0,'S'), size.x, "...YX", size.x-1 );
        strncpy_s( DataAt(0,3,0,'S'), size.x, "....V", size.x-1 );
        strncpy_s( DataAt(0,2,0,'S'), size.x, "...JK", size.x-1 );
        strncpy_s( DataAt(0,1,0,'S'), size.x, ".SS.L", size.x-1 );
        strncpy_s( DataAt(0,0,0,'S'), size.x, ".SSSS", size.x-1 );

        strncpy_s( DataAt(0,4,0,'T'), size.x, "RTTTT", size.x-1 );
        strncpy_s( DataAt(0,3,0,'T'), size.x, "RTTTT", size.x-1 );
        strncpy_s( DataAt(0,2,0,'T'), size.x, "RTTTT", size.x-1 );
        strncpy_s( DataAt(0,1,0,'T'), size.x, "Q.TTT", size.x-1 );
        strncpy_s( DataAt(0,0,0,'T'), size.x, "P.TTT", size.x-1 );

        strncpy_s( DataAt(0,4,0,'U'), size.x, "WWW.H", size.x-1 );
        strncpy_s( DataAt(0,3,0,'U'), size.x, "WWW.H", size.x-1 );
        strncpy_s( DataAt(0,2,0,'U'), size.x, "WWW.H", size.x-1 );
        strncpy_s( DataAt(0,1,0,'U'), size.x, "WWW.H", size.x-1 );
        strncpy_s( DataAt(0,0,0,'U'), size.x, "WWWUI", size.x-1 );

        strncpy_s( DataAt(0,4,0,'V'), size.x, "WWWYX", size.x-1 );
        strncpy_s( DataAt(0,3,0,'V'), size.x, "....V", size.x-1 );
        strncpy_s( DataAt(0,2,0,'V'), size.x, "GGGJK", size.x-1 );
        strncpy_s( DataAt(0,1,0,'V'), size.x, "G.M.L", size.x-1 );
        strncpy_s( DataAt(0,0,0,'V'), size.x, "...SS", size.x-1 );

        strncpy_s( DataAt(0,4,0,'W'), size.x, "WWWYX", size.x-1 );
        strncpy_s( DataAt(0,3,0,'W'), size.x, "WWW.V", size.x-1 );
        strncpy_s( DataAt(0,2,0,'W'), size.x, "WWW..", size.x-1 );
        strncpy_s( DataAt(0,1,0,'W'), size.x, "WWW.H", size.x-1 );
        strncpy_s( DataAt(0,0,0,'W'), size.x, "WWWUI", size.x-1 );

        strncpy_s( DataAt(0,4,0,'X'), size.x, "WWWYX", size.x-1 );
        strncpy_s( DataAt(0,3,0,'X'), size.x, "WWW.V", size.x-1 );
        strncpy_s( DataAt(0,2,0,'X'), size.x, "WW.JK", size.x-1 );
        strncpy_s( DataAt(0,1,0,'X'), size.x, "W...L", size.x-1 );
        strncpy_s( DataAt(0,0,0,'X'), size.x, "...SS", size.x-1 );

        strncpy_s( DataAt(0,4,0,'Y'), size.x, "WWWYX", size.x-1 );
        strncpy_s( DataAt(0,3,0,'Y'), size.x, "WWW.V", size.x-1 );
        strncpy_s( DataAt(0,2,0,'Y'), size.x, "WWW.K", size.x-1 );
        strncpy_s( DataAt(0,1,0,'Y'), size.x, "WWW.L", size.x-1 );
        strncpy_s( DataAt(0,0,0,'Y'), size.x, "WWW.S", size.x-1 );

        return;
    }                                            
	
	// XYz型6x6x9层叠
    if (level==3)                                
    {
        size = CIndex4(7,6,9,'B');
        start = CIndex4(3,1,0,'A');
        end = CIndex4(5,5,8,'A');

        if (data) free(data);
        data = (char *)malloc(size.Capacity());
        if (!data) exit(0);

        strncpy_s( DataAt(0,5, 0,'A'), size.x, "......", size.x-1 );
        strncpy_s( DataAt(0,4, 0,'A'), size.x, ".AAA..", size.x-1 );
        strncpy_s( DataAt(0,3, 0,'A'), size.x, ".A.A..", size.x-1 );
        strncpy_s( DataAt(0,2, 0,'A'), size.x, ".A.A..", size.x-1 );
        strncpy_s( DataAt(0,1, 0,'A'), size.x, ".AAA..", size.x-1 );
        strncpy_s( DataAt(0,0, 0,'A'), size.x, "......", size.x-1 );

        strncpy_s( DataAt(0,5, 1,'A'), size.x, "......", size.x-1 );
        strncpy_s( DataAt(0,4, 1,'A'), size.x, ".AAAA.", size.x-1 );
        strncpy_s( DataAt(0,3, 1,'A'), size.x, "..A.A.", size.x-1 );
        strncpy_s( DataAt(0,2, 1,'A'), size.x, "..A.AA", size.x-1 );
        strncpy_s( DataAt(0,1, 1,'A'), size.x, "....AA", size.x-1 );
        strncpy_s( DataAt(0,0, 1,'A'), size.x, "....AA", size.x-1 );

        strncpy_s( DataAt(0,5, 2,'A'), size.x, "AAAAAA", size.x-1 );
        strncpy_s( DataAt(0,4, 2,'A'), size.x, "A....A", size.x-1 );
        strncpy_s( DataAt(0,3, 2,'A'), size.x, "A....A", size.x-1 );
        strncpy_s( DataAt(0,2, 2,'A'), size.x, "A.AA.A", size.x-1 );
        strncpy_s( DataAt(0,1, 2,'A'), size.x, "A..A.A", size.x-1 );
        strncpy_s( DataAt(0,0, 2,'A'), size.x, "AAAA..", size.x-1 );

        strncpy_s( DataAt(0,5, 3,'A'), size.x, "......", size.x-1 );
        strncpy_s( DataAt(0,4, 3,'A'), size.x, ".AAAA.", size.x-1 );
        strncpy_s( DataAt(0,3, 3,'A'), size.x, ".A.AA.", size.x-1 );
        strncpy_s( DataAt(0,2, 3,'A'), size.x, ".AA.A.", size.x-1 );
        strncpy_s( DataAt(0,1, 3,'A'), size.x, ".AA.AA", size.x-1 );
        strncpy_s( DataAt(0,0, 3,'A'), size.x, "....AA", size.x-1 );

        strncpy_s( DataAt(0,5, 4,'A'), size.x, "......", size.x-1 );
        strncpy_s( DataAt(0,4, 4,'A'), size.x, "......", size.x-1 );
        strncpy_s( DataAt(0,3, 4,'A'), size.x, "......", size.x-1 );
        strncpy_s( DataAt(0,2, 4,'A'), size.x, "..A...", size.x-1 );
        strncpy_s( DataAt(0,1, 4,'A'), size.x, ".....A", size.x-1 );
        strncpy_s( DataAt(0,0, 4,'A'), size.x, ".....A", size.x-1 );

        strncpy_s( DataAt(0,5, 5,'A'), size.x, "...AAA", size.x-1 );
        strncpy_s( DataAt(0,4, 5,'A'), size.x, ".....A", size.x-1 );
        strncpy_s( DataAt(0,3, 5,'A'), size.x, ".....A", size.x-1 );
        strncpy_s( DataAt(0,2, 5,'A'), size.x, "AAA..A", size.x-1 );
        strncpy_s( DataAt(0,1, 5,'A'), size.x, "AAA..A", size.x-1 );
        strncpy_s( DataAt(0,0, 5,'A'), size.x, "AAAAAA", size.x-1 );

        strncpy_s( DataAt(0,5, 6,'A'), size.x, "AAAAAA", size.x-1 );
        strncpy_s( DataAt(0,4, 6,'A'), size.x, "AAAA..", size.x-1 );
        strncpy_s( DataAt(0,3, 6,'A'), size.x, "AAAA..", size.x-1 );
        strncpy_s( DataAt(0,2, 6,'A'), size.x, "AAAA..", size.x-1 );
        strncpy_s( DataAt(0,1, 6,'A'), size.x, "......", size.x-1 );
        strncpy_s( DataAt(0,0, 6,'A'), size.x, "......", size.x-1 );

        strncpy_s( DataAt(0,5, 7,'A'), size.x, "......", size.x-1 );
        strncpy_s( DataAt(0,4, 7,'A'), size.x, "...AAA", size.x-1 );
        strncpy_s( DataAt(0,3, 7,'A'), size.x, "...AAA", size.x-1 );
        strncpy_s( DataAt(0,2, 7,'A'), size.x, "..AAAA", size.x-1 );
        strncpy_s( DataAt(0,1, 7,'A'), size.x, "AAAAAA", size.x-1 );
        strncpy_s( DataAt(0,0, 7,'A'), size.x, "AAAAAA", size.x-1 );

        strncpy_s( DataAt(0,5, 8,'A'), size.x, "AAAAAA", size.x-1 );
        strncpy_s( DataAt(0,4, 8,'A'), size.x, "A.A...", size.x-1 );
        strncpy_s( DataAt(0,3, 8,'A'), size.x, "AAA...", size.x-1 );
        strncpy_s( DataAt(0,2, 8,'A'), size.x, "AA....", size.x-1 );
        strncpy_s( DataAt(0,1, 8,'A'), size.x, "AA....", size.x-1 );
        strncpy_s( DataAt(0,0, 8,'A'), size.x, "AA....", size.x-1 );

        return;
    }
    
    // XYz型5x5x5管道纵横
    if (level==4)                                
    {
        size = CIndex4(6,5,5,'B');
        start = CIndex4(2,2,1,'A');
        end = CIndex4(0,1,4,'A');

        if (data) free(data);
        data = (char *)malloc(size.Capacity());
        if (!data) exit(0);

        strncpy_s( DataAt(0, 4,0,'A'), size.x, "AAAAA", size.x-1 );
        strncpy_s( DataAt(0, 3,0,'A'), size.x, "A....", size.x-1 );
        strncpy_s( DataAt(0, 2,0,'A'), size.x, "A....", size.x-1 );
        strncpy_s( DataAt(0, 1,0,'A'), size.x, "AAAAA", size.x-1 );
        strncpy_s( DataAt(0, 0,0,'A'), size.x, ".A..A", size.x-1 );

        strncpy_s( DataAt(0, 4,1,'A'), size.x, ".A..A", size.x-1 );
        strncpy_s( DataAt(0, 3,1,'A'), size.x, "..A.A", size.x-1 );
        strncpy_s( DataAt(0, 2,1,'A'), size.x, "A.AAA", size.x-1 );
        strncpy_s( DataAt(0, 1,1,'A'), size.x, ".....", size.x-1 );
        strncpy_s( DataAt(0, 0,1,'A'), size.x, ".A..A", size.x-1 );
                                           
        strncpy_s( DataAt(0, 4,2,'A'), size.x, ".A..A", size.x-1 );
        strncpy_s( DataAt(0, 3,2,'A'), size.x, ".....", size.x-1 );
        strncpy_s( DataAt(0, 2,2,'A'), size.x, "A..AA", size.x-1 );
        strncpy_s( DataAt(0, 1,2,'A'), size.x, "A..A.", size.x-1 );
        strncpy_s( DataAt(0, 0,2,'A'), size.x, "AAAAA", size.x-1 );
                                           
        strncpy_s( DataAt(0, 4,3,'A'), size.x, ".A..A", size.x-1 );
        strncpy_s( DataAt(0, 3,3,'A'), size.x, ".A..A", size.x-1 );
        strncpy_s( DataAt(0, 2,3,'A'), size.x, "AA..A", size.x-1 );
        strncpy_s( DataAt(0, 1,3,'A'), size.x, ".A..A", size.x-1 );
        strncpy_s( DataAt(0, 0,3,'A'), size.x, ".....", size.x-1 );
                                           
        strncpy_s( DataAt(0, 4,4,'A'), size.x, "AAAAA", size.x-1 );
        strncpy_s( DataAt(0, 3,4,'A'), size.x, "A.A..", size.x-1 );
        strncpy_s( DataAt(0, 2,4,'A'), size.x, "..AA.", size.x-1 );
        strncpy_s( DataAt(0, 1,4,'A'), size.x, "A..A.", size.x-1 );
        strncpy_s( DataAt(0, 0,4,'A'), size.x, "AAAA.", size.x-1 );

        return;
    }

    // XYZ型7x7x7平面交错
    if (level==5)                                
    {
        size = CIndex4(8,7,7,'B');
        start = CIndex4(2,3,0,'A');
        end = CIndex4(2,3,3,'A');

        if (data) free(data);
        data = (char *)malloc(size.Capacity());
        if (!data) exit(0);

        strncpy_s( DataAt(0, 6,0,'A'), size.x, "AAAA.AA", size.x-1 );
        strncpy_s( DataAt(0, 5,0,'A'), size.x, "A...A.A", size.x-1 );
        strncpy_s( DataAt(0, 4,0,'A'), size.x, ".AAAA.A", size.x-1 );
        strncpy_s( DataAt(0, 3,0,'A'), size.x, ".AAAA.A", size.x-1 );
        strncpy_s( DataAt(0, 2,0,'A'), size.x, ".AAAA.A", size.x-1 );
        strncpy_s( DataAt(0, 1,0,'A'), size.x, "A...A.A", size.x-1 );
        strncpy_s( DataAt(0, 0,0,'A'), size.x, "AAAA.AA", size.x-1 );

        strncpy_s( DataAt(0, 6,1,'A'), size.x, "AAAAA.A", size.x-1 );
        strncpy_s( DataAt(0, 5,1,'A'), size.x, "A.A.A.A", size.x-1 );
        strncpy_s( DataAt(0, 4,1,'A'), size.x, "A...A..", size.x-1 );
        strncpy_s( DataAt(0, 3,1,'A'), size.x, "A...AAA", size.x-1 );
        strncpy_s( DataAt(0, 2,1,'A'), size.x, "A...AAA", size.x-1 );
        strncpy_s( DataAt(0, 1,1,'A'), size.x, "A.AAA..", size.x-1 );
        strncpy_s( DataAt(0, 0,1,'A'), size.x, ".AA....", size.x-1 );

        strncpy_s( DataAt(0, 6,2,'A'), size.x, "AAAA..A", size.x-1 );
        strncpy_s( DataAt(0, 5,2,'A'), size.x, ".A.AA.A", size.x-1 );
        strncpy_s( DataAt(0, 4,2,'A'), size.x, "....A.A", size.x-1 );
        strncpy_s( DataAt(0, 3,2,'A'), size.x, "....A.A", size.x-1 );
        strncpy_s( DataAt(0, 2,2,'A'), size.x, "....AAA", size.x-1 );
        strncpy_s( DataAt(0, 1,2,'A'), size.x, "...AA..", size.x-1 );
        strncpy_s( DataAt(0, 0,2,'A'), size.x, "..A....", size.x-1 );

        strncpy_s( DataAt(0, 6,3,'A'), size.x, "AAAA...", size.x-1 );
        strncpy_s( DataAt(0, 5,3,'A'), size.x, "...AA.A", size.x-1 );
        strncpy_s( DataAt(0, 4,3,'A'), size.x, ".AA.A..", size.x-1 );
        strncpy_s( DataAt(0, 3,3,'A'), size.x, "AAA.A..", size.x-1 );
        strncpy_s( DataAt(0, 2,3,'A'), size.x, "A...AAA", size.x-1 );
        strncpy_s( DataAt(0, 1,3,'A'), size.x, "AAA....", size.x-1 );
        strncpy_s( DataAt(0, 0,3,'A'), size.x, "A...A..", size.x-1 );

        strncpy_s( DataAt(0, 6,4,'A'), size.x, "...A...", size.x-1 );
        strncpy_s( DataAt(0, 5,4,'A'), size.x, "......A", size.x-1 );
        strncpy_s( DataAt(0, 4,4,'A'), size.x, ".......", size.x-1 );
        strncpy_s( DataAt(0, 3,4,'A'), size.x, "A......", size.x-1 );
        strncpy_s( DataAt(0, 2,4,'A'), size.x, "A...AAA", size.x-1 );
        strncpy_s( DataAt(0, 1,4,'A'), size.x, "AAA.A.A", size.x-1 );
        strncpy_s( DataAt(0, 0,4,'A'), size.x, "A.AAAAA", size.x-1 );

        strncpy_s( DataAt(0, 6,5,'A'), size.x, "...AAAA", size.x-1 );
        strncpy_s( DataAt(0, 5,5,'A'), size.x, ".A.A..A", size.x-1 );
        strncpy_s( DataAt(0, 4,5,'A'), size.x, ".AAA...", size.x-1 );
        strncpy_s( DataAt(0, 3,5,'A'), size.x, "A.AA..A", size.x-1 );
        strncpy_s( DataAt(0, 2,5,'A'), size.x, "A.A...A", size.x-1 );
        strncpy_s( DataAt(0, 1,5,'A'), size.x, "AAA.AAA", size.x-1 );
        strncpy_s( DataAt(0, 0,5,'A'), size.x, "A.AAA.A", size.x-1 );

        strncpy_s( DataAt(0, 6,6,'A'), size.x, "AAAA..A", size.x-1 );
        strncpy_s( DataAt(0, 5,6,'A'), size.x, "A...AAA", size.x-1 );
        strncpy_s( DataAt(0, 4,6,'A'), size.x, "....AA.", size.x-1 );
        strncpy_s( DataAt(0, 3,6,'A'), size.x, "A.....A", size.x-1 );
        strncpy_s( DataAt(0, 2,6,'A'), size.x, "A.....A", size.x-1 );
        strncpy_s( DataAt(0, 1,6,'A'), size.x, "AAA.AAA", size.x-1 );
        strncpy_s( DataAt(0, 0,6,'A'), size.x, "A.AAA.A", size.x-1 );

        return;
    }

    // XY型9x9平坦
    if (false)                                
    {
        size = CIndex4(10,9,1,'B');
        start = CIndex4(6,1,0,'A');
        end = CIndex4(4,1,0,'A');

        if (data) free(data);
        data = (char *)malloc(size.Capacity());
        if (!data) exit(0);

        strncpy_s( DataAt(0, 8,0,'A'), size.x, "AAAA.AAAA", size.x-1 );
        strncpy_s( DataAt(0, 7,0,'A'), size.x, "AA.A.AA.A", size.x-1 );
        strncpy_s( DataAt(0, 6,0,'A'), size.x, "A.AA...AA", size.x-1 );
        strncpy_s( DataAt(0, 5,0,'A'), size.x, "AAAAAAAA.", size.x-1 );
        strncpy_s( DataAt(0, 4,0,'A'), size.x, "AA...A...", size.x-1 );
        strncpy_s( DataAt(0, 3,0,'A'), size.x, ".AAA.AAA.", size.x-1 );
        strncpy_s( DataAt(0, 2,0,'A'), size.x, "AA....A..", size.x-1 );
        strncpy_s( DataAt(0, 1,0,'A'), size.x, ".A.AA.A..", size.x-1 );
        strncpy_s( DataAt(0, 0,0,'A'), size.x, "AAAAA....", size.x-1 );

        return;
    }

    // XYZ型10x10x18电路板(UNDONE)
    if (false)                                
    {
        size = CIndex4(11,10,18,'B');
        start = CIndex4(3,0,0,'A');
        end = CIndex4(0,3,9,'A');

        if (data) free(data);
        data = (char *)malloc(size.Capacity());
        if (!data) exit(0);

        strncpy_s( DataAt(0,9, 0,'A'), size.x, "..........", size.x-1 );
        strncpy_s( DataAt(0,8, 0,'A'), size.x, "..........", size.x-1 );
        strncpy_s( DataAt(0,7, 0,'A'), size.x, "..........", size.x-1 );
        strncpy_s( DataAt(0,6, 0,'A'), size.x, "..........", size.x-1 );
        strncpy_s( DataAt(0,5, 0,'A'), size.x, "..........", size.x-1 );
        strncpy_s( DataAt(0,4, 0,'A'), size.x, "..........", size.x-1 );
        strncpy_s( DataAt(0,3, 0,'A'), size.x, "..........", size.x-1 );
        strncpy_s( DataAt(0,2, 0,'A'), size.x, "..........", size.x-1 );
        strncpy_s( DataAt(0,1, 0,'A'), size.x, "..........", size.x-1 );
        strncpy_s( DataAt(0,0, 0,'A'), size.x, "..........", size.x-1 );

        strncpy_s( DataAt(0,9, 1,'A'), size.x, "..........", size.x-1 );
        strncpy_s( DataAt(0,8, 1,'A'), size.x, "AAAAAAAAAA", size.x-1 );
        strncpy_s( DataAt(0,7, 1,'A'), size.x, "AAAAAAAAAA", size.x-1 );
        strncpy_s( DataAt(0,6, 1,'A'), size.x, "AAAAAAAAAA", size.x-1 );
        strncpy_s( DataAt(0,5, 1,'A'), size.x, "AAAAAAAAAA", size.x-1 );
        strncpy_s( DataAt(0,4, 1,'A'), size.x, "AAAAAAAAAA", size.x-1 );
        strncpy_s( DataAt(0,3, 1,'A'), size.x, "AAAAAAAAAA", size.x-1 );
        strncpy_s( DataAt(0,2, 1,'A'), size.x, "AAAAAAAAAA", size.x-1 );
        strncpy_s( DataAt(0,1, 1,'A'), size.x, "AAAAAAAAAA", size.x-1 );
        strncpy_s( DataAt(0,0, 1,'A'), size.x, "..........", size.x-1 );

        strncpy_s( DataAt(0,9, 2,'A'), size.x, "..........", size.x-1 );
        strncpy_s( DataAt(0,8, 2,'A'), size.x, "AAAAAAAAAA", size.x-1 );
        strncpy_s( DataAt(0,7, 2,'A'), size.x, "AAAAAAAAAA", size.x-1 );
        strncpy_s( DataAt(0,6, 2,'A'), size.x, "AAAAAAAAAA", size.x-1 );
        strncpy_s( DataAt(0,5, 2,'A'), size.x, "AAAAAAAAAA", size.x-1 );
        strncpy_s( DataAt(0,4, 2,'A'), size.x, "AAAAAAAAAA", size.x-1 );
        strncpy_s( DataAt(0,3, 2,'A'), size.x, "AAAAAAAAAA", size.x-1 );
        strncpy_s( DataAt(0,2, 2,'A'), size.x, "AAAAAAAAAA", size.x-1 );
        strncpy_s( DataAt(0,1, 2,'A'), size.x, "AAAAAAAAAA", size.x-1 );
        strncpy_s( DataAt(0,0, 2,'A'), size.x, "..........", size.x-1 );
        //////////////////////////////////////////////////////////////////////////


        //////////////////////////////////////////////////////////////////////////
        strncpy_s( DataAt(0,9,15,'A'), size.x, ".AAAAAAAA.", size.x-1 );
        strncpy_s( DataAt(0,8,15,'A'), size.x, ".AAAAAAAA.", size.x-1 );
        strncpy_s( DataAt(0,7,15,'A'), size.x, ".AAAAAAAA.", size.x-1 );
        strncpy_s( DataAt(0,6,15,'A'), size.x, ".AAAAAAAA.", size.x-1 );
        strncpy_s( DataAt(0,5,15,'A'), size.x, ".AAAAAAAA.", size.x-1 );
        strncpy_s( DataAt(0,4,15,'A'), size.x, ".AAAAAAAA.", size.x-1 );
        strncpy_s( DataAt(0,3,15,'A'), size.x, ".AAAAAAAA.", size.x-1 );
        strncpy_s( DataAt(0,2,15,'A'), size.x, ".AAAAAAAA.", size.x-1 );
        strncpy_s( DataAt(0,1,15,'A'), size.x, ".AAAAAAAA.", size.x-1 );
        strncpy_s( DataAt(0,0,15,'A'), size.x, ".AAAAAAAA.", size.x-1 );

        strncpy_s( DataAt(0,9,16,'A'), size.x, ".AAAAAAAA.", size.x-1 );
        strncpy_s( DataAt(0,8,16,'A'), size.x, ".AAAAAAAA.", size.x-1 );
        strncpy_s( DataAt(0,7,16,'A'), size.x, ".AAAAAAAA.", size.x-1 );
        strncpy_s( DataAt(0,6,16,'A'), size.x, ".AAAAAAAA.", size.x-1 );
        strncpy_s( DataAt(0,5,16,'A'), size.x, ".AAAAAAAA.", size.x-1 );
        strncpy_s( DataAt(0,4,16,'A'), size.x, ".AAAAAAAA.", size.x-1 );
        strncpy_s( DataAt(0,3,16,'A'), size.x, ".AAAAAAAA.", size.x-1 );
        strncpy_s( DataAt(0,2,16,'A'), size.x, ".AAAAAAAA.", size.x-1 );
        strncpy_s( DataAt(0,1,16,'A'), size.x, ".AAAAAAAA.", size.x-1 );
        strncpy_s( DataAt(0,0,16,'A'), size.x, ".AAAAAAAA.", size.x-1 );

        strncpy_s( DataAt(0,9,17,'A'), size.x, ".AAAAAAAA.", size.x-1 );
        strncpy_s( DataAt(0,8,17,'A'), size.x, ".A..A.AAA.", size.x-1 );
        strncpy_s( DataAt(0,7,17,'A'), size.x, ".A.A....A.", size.x-1 );
        strncpy_s( DataAt(0,6,17,'A'), size.x, ".AA.AAAAA.", size.x-1 );
        strncpy_s( DataAt(0,5,17,'A'), size.x, "..A.AAA.A.", size.x-1 );
        strncpy_s( DataAt(0,4,17,'A'), size.x, "..A.A.A.A.", size.x-1 );
        strncpy_s( DataAt(0,3,17,'A'), size.x, "..A.A.A.A.", size.x-1 );
        strncpy_s( DataAt(0,2,17,'A'), size.x, "..AAAAA.A.", size.x-1 );
        strncpy_s( DataAt(0,1,17,'A'), size.x, ".....AA.A.", size.x-1 );
        strncpy_s( DataAt(0,0,17,'A'), size.x, ".AAAAAAAA.", size.x-1 );

        return;
    }

}

