#include "global.h"
#include "Maze4D.h"

void EMaze4D::Init(int level)
{
    // XY型9x9平坦（DONE）
    if (level==1)                                
    {
        mx=9; my=9; mz=1; md='B';
        sx=6; sy=1; sz=0; sd='A';
        ex=4; ey=1; ez=0; ed='A';

        if (data) free(data);
        data = (char *)malloc((mx+1)*my*mz*(md-'A'));
        if (!data) exit(0);

        strncpy_s( Data(0, 8,0,'A'), mx+1, "AAAA.AAAA", mx );
        strncpy_s( Data(0, 7,0,'A'), mx+1, "AA.A.AA.A", mx );
        strncpy_s( Data(0, 6,0,'A'), mx+1, "A.AA...AA", mx );
        strncpy_s( Data(0, 5,0,'A'), mx+1, "AAAAAAAA.", mx );
        strncpy_s( Data(0, 4,0,'A'), mx+1, "AA...A...", mx );
        strncpy_s( Data(0, 3,0,'A'), mx+1, ".AAA.AAA.", mx );
        strncpy_s( Data(0, 2,0,'A'), mx+1, "AA....A..", mx );
        strncpy_s( Data(0, 1,0,'A'), mx+1, ".A.AA.A..", mx );
        strncpy_s( Data(0, 0,0,'A'), mx+1, "AAAAA....", mx );

        return;
    }

    // XYz型6x6x9层叠（DONE）
    if (level==2)                                
    {
        mx=6; my=6; mz=9;  md='B';
        sx=3; sy=1; sz=0;  sd='A';
        ex=5; ey=5; ez=8;  ed='A';

        if (data) free(data);
        data = (char *)malloc((mx+1)*my*mz*(md-'A'));
        if (!data) exit(0);

        strncpy_s( Data(0,5, 0,'A'), mx+1, "......", mx );
        strncpy_s( Data(0,4, 0,'A'), mx+1, ".AAA..", mx );
        strncpy_s( Data(0,3, 0,'A'), mx+1, ".A.A..", mx );
        strncpy_s( Data(0,2, 0,'A'), mx+1, ".A.A..", mx );
        strncpy_s( Data(0,1, 0,'A'), mx+1, ".AAA..", mx );
        strncpy_s( Data(0,0, 0,'A'), mx+1, "......", mx );

        strncpy_s( Data(0,5, 1,'A'), mx+1, "......", mx );
        strncpy_s( Data(0,4, 1,'A'), mx+1, ".AAAA.", mx );
        strncpy_s( Data(0,3, 1,'A'), mx+1, "..A.A.", mx );
        strncpy_s( Data(0,2, 1,'A'), mx+1, "..A.AA", mx );
        strncpy_s( Data(0,1, 1,'A'), mx+1, "....AA", mx );
        strncpy_s( Data(0,0, 1,'A'), mx+1, "....AA", mx );

        strncpy_s( Data(0,5, 2,'A'), mx+1, "AAAAAA", mx );
        strncpy_s( Data(0,4, 2,'A'), mx+1, "A....A", mx );
        strncpy_s( Data(0,3, 2,'A'), mx+1, "A....A", mx );
        strncpy_s( Data(0,2, 2,'A'), mx+1, "A.AA.A", mx );
        strncpy_s( Data(0,1, 2,'A'), mx+1, "A..A.A", mx );
        strncpy_s( Data(0,0, 2,'A'), mx+1, "AAAA..", mx );

        strncpy_s( Data(0,5, 3,'A'), mx+1, "......", mx );
        strncpy_s( Data(0,4, 3,'A'), mx+1, ".AAAA.", mx );
        strncpy_s( Data(0,3, 3,'A'), mx+1, ".A.AA.", mx );
        strncpy_s( Data(0,2, 3,'A'), mx+1, ".AA.A.", mx );
        strncpy_s( Data(0,1, 3,'A'), mx+1, ".AA.AA", mx );
        strncpy_s( Data(0,0, 3,'A'), mx+1, "....AA", mx );

        strncpy_s( Data(0,5, 4,'A'), mx+1, "......", mx );
        strncpy_s( Data(0,4, 4,'A'), mx+1, "......", mx );
        strncpy_s( Data(0,3, 4,'A'), mx+1, "......", mx );
        strncpy_s( Data(0,2, 4,'A'), mx+1, "..A...", mx );
        strncpy_s( Data(0,1, 4,'A'), mx+1, ".....A", mx );
        strncpy_s( Data(0,0, 4,'A'), mx+1, ".....A", mx );

        strncpy_s( Data(0,5, 5,'A'), mx+1, "...AAA", mx );
        strncpy_s( Data(0,4, 5,'A'), mx+1, ".....A", mx );
        strncpy_s( Data(0,3, 5,'A'), mx+1, ".....A", mx );
        strncpy_s( Data(0,2, 5,'A'), mx+1, "AAA..A", mx );
        strncpy_s( Data(0,1, 5,'A'), mx+1, "AAA..A", mx );
        strncpy_s( Data(0,0, 5,'A'), mx+1, "AAAAAA", mx );

        strncpy_s( Data(0,5, 6,'A'), mx+1, "AAAAAA", mx );
        strncpy_s( Data(0,4, 6,'A'), mx+1, "AAAA..", mx );
        strncpy_s( Data(0,3, 6,'A'), mx+1, "AAAA..", mx );
        strncpy_s( Data(0,2, 6,'A'), mx+1, "AAAA..", mx );
        strncpy_s( Data(0,1, 6,'A'), mx+1, "......", mx );
        strncpy_s( Data(0,0, 6,'A'), mx+1, "......", mx );

        strncpy_s( Data(0,5, 7,'A'), mx+1, "......", mx );
        strncpy_s( Data(0,4, 7,'A'), mx+1, "...AAA", mx );
        strncpy_s( Data(0,3, 7,'A'), mx+1, "...AAA", mx );
        strncpy_s( Data(0,2, 7,'A'), mx+1, "..AAAA", mx );
        strncpy_s( Data(0,1, 7,'A'), mx+1, "AAAAAA", mx );
        strncpy_s( Data(0,0, 7,'A'), mx+1, "AAAAAA", mx );

        strncpy_s( Data(0,5, 8,'A'), mx+1, "AAAAAA", mx );
        strncpy_s( Data(0,4, 8,'A'), mx+1, "A.A...", mx );
        strncpy_s( Data(0,3, 8,'A'), mx+1, "AAA...", mx );
        strncpy_s( Data(0,2, 8,'A'), mx+1, "AA....", mx );
        strncpy_s( Data(0,1, 8,'A'), mx+1, "AA....", mx );
        strncpy_s( Data(0,0, 8,'A'), mx+1, "AA....", mx );

        return;
    }
    
    // XYz型5x5x5管道纵横（DONE）
    if (level==3)                                
    {
        mx=5; my=5; mz=5; md='B';
        sx=2; sy=2; sz=1; sd='A';
        ex=0; ey=1; ez=4; ed='A';

        if (data) free(data);
        data = (char *)malloc((mx+1)*my*mz*(md-'A'));
        if (!data) exit(0);

        strncpy_s( Data(0, 4,0,'A'), mx+1, "AAAAA", mx );
        strncpy_s( Data(0, 3,0,'A'), mx+1, "A....", mx );
        strncpy_s( Data(0, 2,0,'A'), mx+1, "A....", mx );
        strncpy_s( Data(0, 1,0,'A'), mx+1, "AAAAA", mx );
        strncpy_s( Data(0, 0,0,'A'), mx+1, ".A..A", mx );

        strncpy_s( Data(0, 4,1,'A'), mx+1, ".A..A", mx );
        strncpy_s( Data(0, 3,1,'A'), mx+1, "..A.A", mx );
        strncpy_s( Data(0, 2,1,'A'), mx+1, "A.AAA", mx );
        strncpy_s( Data(0, 1,1,'A'), mx+1, ".....", mx );
        strncpy_s( Data(0, 0,1,'A'), mx+1, ".A..A", mx );
                                           
        strncpy_s( Data(0, 4,2,'A'), mx+1, ".A..A", mx );
        strncpy_s( Data(0, 3,2,'A'), mx+1, ".....", mx );
        strncpy_s( Data(0, 2,2,'A'), mx+1, "A..AA", mx );
        strncpy_s( Data(0, 1,2,'A'), mx+1, "A..A.", mx );
        strncpy_s( Data(0, 0,2,'A'), mx+1, "AAAAA", mx );
                                           
        strncpy_s( Data(0, 4,3,'A'), mx+1, ".A..A", mx );
        strncpy_s( Data(0, 3,3,'A'), mx+1, ".A..A", mx );
        strncpy_s( Data(0, 2,3,'A'), mx+1, "AA..A", mx );
        strncpy_s( Data(0, 1,3,'A'), mx+1, ".A..A", mx );
        strncpy_s( Data(0, 0,3,'A'), mx+1, ".....", mx );
                                           
        strncpy_s( Data(0, 4,4,'A'), mx+1, "AAAAA", mx );
        strncpy_s( Data(0, 3,4,'A'), mx+1, "A.A..", mx );
        strncpy_s( Data(0, 2,4,'A'), mx+1, "..AA.", mx );
        strncpy_s( Data(0, 1,4,'A'), mx+1, "A..A.", mx );
        strncpy_s( Data(0, 0,4,'A'), mx+1, "AAAA.", mx );

        return;
    }

    // XYZ型7x7x7平面交错（DONE）
    if (level==4)                                
    {
        mx=7; my=7; mz=7; md='B';
        sx=2; sy=3; sz=0; sd='A';
        ex=2; ey=3; ez=3; ed='A';

        if (data) free(data);
        data = (char *)malloc((mx+1)*my*mz*(md-'A'));
        if (!data) exit(0);

        strncpy_s( Data(0, 6,0,'A'), mx+1, "AAAA.AA", mx );
        strncpy_s( Data(0, 5,0,'A'), mx+1, "A...A.A", mx );
        strncpy_s( Data(0, 4,0,'A'), mx+1, ".AAAA.A", mx );
        strncpy_s( Data(0, 3,0,'A'), mx+1, ".AAAA.A", mx );
        strncpy_s( Data(0, 2,0,'A'), mx+1, ".AAAA.A", mx );
        strncpy_s( Data(0, 1,0,'A'), mx+1, "A...A.A", mx );
        strncpy_s( Data(0, 0,0,'A'), mx+1, "AAAA.AA", mx );

        strncpy_s( Data(0, 6,1,'A'), mx+1, "AAAAA.A", mx );
        strncpy_s( Data(0, 5,1,'A'), mx+1, "A.A.A.A", mx );
        strncpy_s( Data(0, 4,1,'A'), mx+1, "A...A..", mx );
        strncpy_s( Data(0, 3,1,'A'), mx+1, "A...AAA", mx );
        strncpy_s( Data(0, 2,1,'A'), mx+1, "A...AAA", mx );
        strncpy_s( Data(0, 1,1,'A'), mx+1, "A.AAA..", mx );
        strncpy_s( Data(0, 0,1,'A'), mx+1, ".AA....", mx );

        strncpy_s( Data(0, 6,2,'A'), mx+1, "AAAA..A", mx );
        strncpy_s( Data(0, 5,2,'A'), mx+1, ".A.AA.A", mx );
        strncpy_s( Data(0, 4,2,'A'), mx+1, "....A.A", mx );
        strncpy_s( Data(0, 3,2,'A'), mx+1, "....A.A", mx );
        strncpy_s( Data(0, 2,2,'A'), mx+1, "....AAA", mx );
        strncpy_s( Data(0, 1,2,'A'), mx+1, "...AA..", mx );
        strncpy_s( Data(0, 0,2,'A'), mx+1, "..A....", mx );

        strncpy_s( Data(0, 6,3,'A'), mx+1, "AAAA...", mx );
        strncpy_s( Data(0, 5,3,'A'), mx+1, "...AA.A", mx );
        strncpy_s( Data(0, 4,3,'A'), mx+1, ".AA.A..", mx );
        strncpy_s( Data(0, 3,3,'A'), mx+1, "AAA.A..", mx );
        strncpy_s( Data(0, 2,3,'A'), mx+1, "A...AAA", mx );
        strncpy_s( Data(0, 1,3,'A'), mx+1, "AAA....", mx );
        strncpy_s( Data(0, 0,3,'A'), mx+1, "A...A..", mx );

        strncpy_s( Data(0, 6,4,'A'), mx+1, "...A...", mx );
        strncpy_s( Data(0, 5,4,'A'), mx+1, "......A", mx );
        strncpy_s( Data(0, 4,4,'A'), mx+1, ".......", mx );
        strncpy_s( Data(0, 3,4,'A'), mx+1, "A......", mx );
        strncpy_s( Data(0, 2,4,'A'), mx+1, "A...AAA", mx );
        strncpy_s( Data(0, 1,4,'A'), mx+1, "AAA.A.A", mx );
        strncpy_s( Data(0, 0,4,'A'), mx+1, "A.AAAAA", mx );

        strncpy_s( Data(0, 6,5,'A'), mx+1, "...AAAA", mx );
        strncpy_s( Data(0, 5,5,'A'), mx+1, ".A.A..A", mx );
        strncpy_s( Data(0, 4,5,'A'), mx+1, ".AAA...", mx );
        strncpy_s( Data(0, 3,5,'A'), mx+1, "A.AA..A", mx );
        strncpy_s( Data(0, 2,5,'A'), mx+1, "A.A...A", mx );
        strncpy_s( Data(0, 1,5,'A'), mx+1, "AAA.AAA", mx );
        strncpy_s( Data(0, 0,5,'A'), mx+1, "A.AAA.A", mx );

        strncpy_s( Data(0, 6,6,'A'), mx+1, "AAAA..A", mx );
        strncpy_s( Data(0, 5,6,'A'), mx+1, "A...AAA", mx );
        strncpy_s( Data(0, 4,6,'A'), mx+1, "....AA.", mx );
        strncpy_s( Data(0, 3,6,'A'), mx+1, "A.....A", mx );
        strncpy_s( Data(0, 2,6,'A'), mx+1, "A.....A", mx );
        strncpy_s( Data(0, 1,6,'A'), mx+1, "AAA.AAA", mx );
        strncpy_s( Data(0, 0,6,'A'), mx+1, "A.AAA.A", mx );

        return;
    }

    // XYw型7x4立柱（DONE）
    if (level==5)                                
    {
        mx=7; my=4; mz=1; md='J';
        sx=0; sy=0; sz=0; sd='A';
        ex=1; ey=3; ez=0; ed='H';

        if (data) free(data);
        data = (char *)malloc((mx+1)*my*mz*(md-'A'));
        if (!data) exit(0);

        strncpy_s( Data(0, 3,0,'A'), mx+1, "..CCDEE", mx );
        strncpy_s( Data(0, 2,0,'A'), mx+1, "AAA....", mx );
        strncpy_s( Data(0, 1,0,'A'), mx+1, "A.BIII.", mx );
        strncpy_s( Data(0, 0,0,'A'), mx+1, "A......", mx );

        strncpy_s( Data(0, 3,0,'B'), mx+1, "..CC.I.", mx );
        strncpy_s( Data(0, 2,0,'B'), mx+1, "AAA.II.", mx );
        strncpy_s( Data(0, 1,0,'B'), mx+1, "..BIII.", mx );
        strncpy_s( Data(0, 0,0,'B'), mx+1, ".......", mx );

        strncpy_s( Data(0, 3,0,'C'), mx+1, "..CCDEE", mx );
        strncpy_s( Data(0, 2,0,'C'), mx+1, "AAA.FFF", mx );
        strncpy_s( Data(0, 1,0,'C'), mx+1, "A.BBGFF", mx );
        strncpy_s( Data(0, 0,0,'C'), mx+1, "....HGG", mx );

        strncpy_s( Data(0, 3,0,'D'), mx+1, "..CCDEE", mx );
        strncpy_s( Data(0, 2,0,'D'), mx+1, "AAA.FFF", mx );
        strncpy_s( Data(0, 1,0,'D'), mx+1, "A..HGFF", mx );
        strncpy_s( Data(0, 0,0,'D'), mx+1, "..HHHGG", mx );

        strncpy_s( Data(0, 3,0,'E'), mx+1, "..CCDEE", mx );
        strncpy_s( Data(0, 2,0,'E'), mx+1, "AAA.FFF", mx );
        strncpy_s( Data(0, 1,0,'E'), mx+1, "AHHHGFF", mx );
        strncpy_s( Data(0, 0,0,'E'), mx+1, ".HHHHGG", mx );

        strncpy_s( Data(0, 3,0,'F'), mx+1, "..CCDEE", mx );
        strncpy_s( Data(0, 2,0,'F'), mx+1, ".HH.FFF", mx );
        strncpy_s( Data(0, 1,0,'F'), mx+1, ".HHHGFF", mx );
        strncpy_s( Data(0, 0,0,'F'), mx+1, ".HHHHGG", mx );

        strncpy_s( Data(0, 3,0,'G'), mx+1, ".HCCDEE", mx );
        strncpy_s( Data(0, 2,0,'G'), mx+1, ".HH.FFF", mx );
        strncpy_s( Data(0, 1,0,'G'), mx+1, ".HHHGFF", mx );
        strncpy_s( Data(0, 0,0,'G'), mx+1, ".HHHHGG", mx );

        strncpy_s( Data(0, 3,0,'H'), mx+1, ".H.CDEE", mx );
        strncpy_s( Data(0, 2,0,'H'), mx+1, ".HH.FFF", mx );
        strncpy_s( Data(0, 1,0,'H'), mx+1, ".HHHGFF", mx );
        strncpy_s( Data(0, 0,0,'H'), mx+1, ".HHHHGG", mx );

        strncpy_s( Data(0, 3,0,'I'), mx+1, "..C.II.", mx );
        strncpy_s( Data(0, 2,0,'I'), mx+1, "AAA.II.", mx );
        strncpy_s( Data(0, 1,0,'I'), mx+1, "..BIII.", mx );
        strncpy_s( Data(0, 0,0,'I'), mx+1, ".......", mx );

        return;
    }

    // XYw型5x5田字迷乱
    if (level==6)
    {
        mx=5; my=5; mz=1; md='Z';
        sx=3; sy=1; sz=0; sd='A';
        ex=2; ey=0; ez=0; ed='T';

        if (data) free(data);
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

        return;
    }                                            


//////////////////////////////////////////////////////////////////////////

    // XYZ型10x10x18电路板
    if (level==99)                                
    {
        mx=10; my=10; mz=18; md='B';
        sx=3; sy=0; sz=0;  sd='A';
        ex=0; ey=3; ez=9;  ed='A';

        if (data) free(data);
        data = (char *)malloc((mx+1)*my*mz*(md-'A'));
        if (!data) exit(0);

        strncpy_s( Data(0,9, 0,'A'), mx+1, "..........", mx );
        strncpy_s( Data(0,8, 0,'A'), mx+1, "..........", mx );
        strncpy_s( Data(0,7, 0,'A'), mx+1, "..........", mx );
        strncpy_s( Data(0,6, 0,'A'), mx+1, "..........", mx );
        strncpy_s( Data(0,5, 0,'A'), mx+1, "..........", mx );
        strncpy_s( Data(0,4, 0,'A'), mx+1, "..........", mx );
        strncpy_s( Data(0,3, 0,'A'), mx+1, "..........", mx );
        strncpy_s( Data(0,2, 0,'A'), mx+1, "..........", mx );
        strncpy_s( Data(0,1, 0,'A'), mx+1, "..........", mx );
        strncpy_s( Data(0,0, 0,'A'), mx+1, "..........", mx );

        strncpy_s( Data(0,9, 1,'A'), mx+1, "..........", mx );
        strncpy_s( Data(0,8, 1,'A'), mx+1, "AAAAAAAAAA", mx );
        strncpy_s( Data(0,7, 1,'A'), mx+1, "AAAAAAAAAA", mx );
        strncpy_s( Data(0,6, 1,'A'), mx+1, "AAAAAAAAAA", mx );
        strncpy_s( Data(0,5, 1,'A'), mx+1, "AAAAAAAAAA", mx );
        strncpy_s( Data(0,4, 1,'A'), mx+1, "AAAAAAAAAA", mx );
        strncpy_s( Data(0,3, 1,'A'), mx+1, "AAAAAAAAAA", mx );
        strncpy_s( Data(0,2, 1,'A'), mx+1, "AAAAAAAAAA", mx );
        strncpy_s( Data(0,1, 1,'A'), mx+1, "AAAAAAAAAA", mx );
        strncpy_s( Data(0,0, 1,'A'), mx+1, "..........", mx );

        strncpy_s( Data(0,9, 2,'A'), mx+1, "..........", mx );
        strncpy_s( Data(0,8, 2,'A'), mx+1, "AAAAAAAAAA", mx );
        strncpy_s( Data(0,7, 2,'A'), mx+1, "AAAAAAAAAA", mx );
        strncpy_s( Data(0,6, 2,'A'), mx+1, "AAAAAAAAAA", mx );
        strncpy_s( Data(0,5, 2,'A'), mx+1, "AAAAAAAAAA", mx );
        strncpy_s( Data(0,4, 2,'A'), mx+1, "AAAAAAAAAA", mx );
        strncpy_s( Data(0,3, 2,'A'), mx+1, "AAAAAAAAAA", mx );
        strncpy_s( Data(0,2, 2,'A'), mx+1, "AAAAAAAAAA", mx );
        strncpy_s( Data(0,1, 2,'A'), mx+1, "AAAAAAAAAA", mx );
        strncpy_s( Data(0,0, 2,'A'), mx+1, "..........", mx );
        //////////////////////////////////////////////////////////////////////////


        //////////////////////////////////////////////////////////////////////////
        strncpy_s( Data(0,9,15,'A'), mx+1, ".AAAAAAAA.", mx );
        strncpy_s( Data(0,8,15,'A'), mx+1, ".AAAAAAAA.", mx );
        strncpy_s( Data(0,7,15,'A'), mx+1, ".AAAAAAAA.", mx );
        strncpy_s( Data(0,6,15,'A'), mx+1, ".AAAAAAAA.", mx );
        strncpy_s( Data(0,5,15,'A'), mx+1, ".AAAAAAAA.", mx );
        strncpy_s( Data(0,4,15,'A'), mx+1, ".AAAAAAAA.", mx );
        strncpy_s( Data(0,3,15,'A'), mx+1, ".AAAAAAAA.", mx );
        strncpy_s( Data(0,2,15,'A'), mx+1, ".AAAAAAAA.", mx );
        strncpy_s( Data(0,1,15,'A'), mx+1, ".AAAAAAAA.", mx );
        strncpy_s( Data(0,0,15,'A'), mx+1, ".AAAAAAAA.", mx );

        strncpy_s( Data(0,9,16,'A'), mx+1, ".AAAAAAAA.", mx );
        strncpy_s( Data(0,8,16,'A'), mx+1, ".AAAAAAAA.", mx );
        strncpy_s( Data(0,7,16,'A'), mx+1, ".AAAAAAAA.", mx );
        strncpy_s( Data(0,6,16,'A'), mx+1, ".AAAAAAAA.", mx );
        strncpy_s( Data(0,5,16,'A'), mx+1, ".AAAAAAAA.", mx );
        strncpy_s( Data(0,4,16,'A'), mx+1, ".AAAAAAAA.", mx );
        strncpy_s( Data(0,3,16,'A'), mx+1, ".AAAAAAAA.", mx );
        strncpy_s( Data(0,2,16,'A'), mx+1, ".AAAAAAAA.", mx );
        strncpy_s( Data(0,1,16,'A'), mx+1, ".AAAAAAAA.", mx );
        strncpy_s( Data(0,0,16,'A'), mx+1, ".AAAAAAAA.", mx );

        strncpy_s( Data(0,9,17,'A'), mx+1, ".AAAAAAAA.", mx );
        strncpy_s( Data(0,8,17,'A'), mx+1, ".A..A.AAA.", mx );
        strncpy_s( Data(0,7,17,'A'), mx+1, ".A.A....A.", mx );
        strncpy_s( Data(0,6,17,'A'), mx+1, ".AA.AAAAA.", mx );
        strncpy_s( Data(0,5,17,'A'), mx+1, "..A.AAA.A.", mx );
        strncpy_s( Data(0,4,17,'A'), mx+1, "..A.A.A.A.", mx );
        strncpy_s( Data(0,3,17,'A'), mx+1, "..A.A.A.A.", mx );
        strncpy_s( Data(0,2,17,'A'), mx+1, "..AAAAA.A.", mx );
        strncpy_s( Data(0,1,17,'A'), mx+1, ".....AA.A.", mx );
        strncpy_s( Data(0,0,17,'A'), mx+1, ".AAAAAAAA.", mx );

        return;
    }

}

