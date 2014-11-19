#include "Tips.h"
#include "glResouce.h"

extern class CglResouce glRes;

//存储所有文字数据，包括解说词和3D字体
void ETips::Init(int level)
{
    static bool isFirstCall=true;
    if (isFirstCall)    // 首次调用，构造通用信息
    {
        isFirstCall = false;

        // list_font3D索引0-3为通用
        list_font3D.clear();
        list_font3D.push_back( glRes.Build3DText((unsigned char*)" 壹二三四五六七八九") );
        list_font3D.push_back( glRes.Build3DText((unsigned char*)"终点") );
        list_font3D.push_back( glRes.Build3DText((unsigned char*)"起点") );
        list_font3D.push_back( glRes.Build3DText((unsigned char*)"Tips") );
    }
    else        // 非首次调用，清除上一关的资源
    {
        while (list_font3D.size() >4 )
        {
            vector<int>::iterator i = list_font3D.back().begin();
            while (i!=list_font3D.back().end())
            {
                glDeleteLists(*i, 1); // 删除显示列表
                ++i;
            }
            list_font3D.pop_back();
        }
    }
//////////////////////////////////////////////////////////////////////////
    std::pair<char,vector<string>> temp;
    font2D.clear();

    if (level==1)
    {
        temp.first = '=';
        temp.second.clear();
        temp.second.push_back("第1关：平坦");
        temp.second.push_back("迷宫维度：XY");
        temp.second.push_back("摄影机类型：plain2D");
        font2D.insert(temp);

        temp.first = '[';
        temp.second.clear();
        temp.second.push_back("你将体验真正自由的3D空间，");
        temp.second.push_back("以及作者设想的4D空间。");
        temp.second.push_back("在那之前，我们先复习一下2D的平面");
        font2D.insert(temp);

        temp.first = 'a';
        temp.second.clear();
        temp.second.push_back("鼠标右键，平移、升降");
        temp.second.push_back("鼠标双键同按，后退");
        font2D.insert(temp);

        temp.first = ']';
        temp.second.clear();
        temp.second.push_back("扩张XY方向很容易，但那不是我们的目的");
        temp.second.push_back("我们要扩张另外的维度");
        temp.second.push_back("按Enter去下一关");
        font2D.insert(temp);
    }

    if (level==2)
    {
        temp.first = '=';
        temp.second.clear();
        temp.second.push_back("第2关：层叠");
        temp.second.push_back("迷宫维度：XYz");
        temp.second.push_back("摄影机类型：plain2D");
        font2D.insert(temp);

        temp.first = '[';
        temp.second.clear();
        temp.second.push_back("这是常人理解的3D空间，相当于一座大楼的多个楼层");
        font2D.insert(temp);

        temp.first = 'a';
        temp.second.clear();
        temp.second.push_back("有否感觉，这种3D仅仅是多个2D的简单叠加？");
        font2D.insert(temp);

        temp.first = 'b';
        temp.second.clear();
        temp.second.push_back("2D叠加在一起就是3D吗？");
        temp.second.push_back("我们在Z方向上自由吗？Z轴可以和XY轴任意互换吗？");
        font2D.insert(temp);

        temp.first = 'c';
        temp.second.clear();
        temp.second.push_back("不能。因为我们始终是站立着的，头顶永远朝上。");
        temp.second.push_back("受重力的影响，我们习惯了这种姿势。");
        font2D.insert(temp);

        temp.first = 'd';
        temp.second.clear();
        temp.second.push_back("重力束缚了我们的头顶，更束缚了我们的思维方式。");
        temp.second.push_back("即使我们能在三个维度上任意移动，我们依然以2D的");
        temp.second.push_back("姿态，将其划分为多个等高面，重叠在一起来理解3D");
        font2D.insert(temp);

        temp.first = ']';
        temp.second.clear();
        temp.second.push_back("这种迷宫不会翻转，其Z轴与XY不能互换，因此z用小写");
        temp.second.push_back("下一关，我们将解锁这个“头顶”");
        font2D.insert(temp);
    }

    if (level==3)
    {
        temp.first = '=';
        temp.second.clear();
        temp.second.push_back("第3关：管道纵横");
        temp.second.push_back("迷宫维度：XYZ");
        temp.second.push_back("摄影机类型：free3D");
        font2D.insert(temp);

        temp.first = '[';
        temp.second.clear();
        temp.second.push_back("你不是风筝。不再有绳索束缚你　指引你");
        temp.second.push_back("去吧！");
        font2D.insert(temp);

        temp.first = 'b';
        temp.second.clear();
        temp.second.push_back("没有重力。你就是自己的重力。");
        font2D.insert(temp);

        temp.first = 'c';
        temp.second.clear();
        temp.second.push_back("试试顺时针移动鼠标，用准星连续画圈");
        temp.second.push_back("这个小技巧能帮你把世界转回来");
        font2D.insert(temp);

        temp.first = 'd';
        temp.second.clear();
        temp.second.push_back("把鼠标一直上移，你会后空翻");
        temp.second.push_back("你可以向任意方向无限翻转");
        temp.second.push_back("自由的3D摄影机");
        font2D.insert(temp);

        temp.first = ']';
        temp.second.clear();
        temp.second.push_back("摄影机是我们的眼睛，");
        temp.second.push_back("上方向就是我们头顶的方向。");
        temp.second.push_back("下一关，我们使用另一种更智能的3D摄影机");
        font2D.insert(temp);
    }

    if (level==4)
    {
        temp.first = '=';
        temp.second.clear();
        temp.second.push_back("第4关：平面交错");
        temp.second.push_back("迷宫维度：XYZ");
        temp.second.push_back("摄影机类型：auto3D");
        font2D.insert(temp);

        temp.first = '[';
        temp.second.clear();
        temp.second.push_back("自归位摄影机，其上方向会自动匹配最近的坐标轴");
        font2D.insert(temp);

        temp.first = 'a';
        temp.second.clear();
        temp.second.push_back("站在方块中央，看向竖直的棱，持续抬头或低头");
        temp.second.push_back("请欣赏自归位过程");
        font2D.insert(temp);

        temp.first = 'b';
        temp.second.clear();
        temp.second.push_back("你应该发现了，X方向的墙都是一样的，Y方向也是");
        temp.second.push_back("仅Z轴的天花板和地板不同。这能帮你确认方向");
        temp.second.push_back("。。。有点像古人们看星星找方向是吗⊙﹏⊙b汗");
        temp.second.push_back("因为我们是探索者 是勇士 是先驱");
        font2D.insert(temp);

        temp.first = ']';
        temp.second.clear();
        temp.second.push_back("下一关，我们将探索用迷宫表现4D的可能性");
        font2D.insert(temp);
    }

    if (level==5)
    {
        temp.first = '=';
        temp.second.clear();
        temp.second.push_back("第5关：立柱");
        temp.second.push_back("迷宫维度：XYw");
        temp.second.push_back("摄影机类型：plain2D");
        font2D.insert(temp);

        temp.first = '[';
        temp.second.clear();
        temp.second.push_back("我们先在二维的基础上，把第四个维度投影下来");
        font2D.insert(temp);

        temp.first = 'a';
        temp.second.clear();
        temp.second.push_back("你能想象，柱子左右两侧是不同的空间吗？走走看");
        font2D.insert(temp);

        temp.first = 'b';
        temp.second.clear();
        temp.second.push_back("在绕柱子旋转的过程中，第四个维度W上的“高度”持续增加，");
        temp.second.push_back("绕一圈会使W坐标增加1，即到达另一个平行的三维空间");
        font2D.insert(temp);

        temp.first = 'c';
        temp.second.clear();
        temp.second.push_back("就像沿着螺旋形楼梯走，提升了竖直的高度，");
        temp.second.push_back("到达大楼的另一层一样，绕这个柱子转使我们");
        temp.second.push_back("提升了第四维上的高度，到达另一个三维空间");
        font2D.insert(temp);

        temp.first = 'd';
        temp.second.clear();
        temp.second.push_back("这与XYz型的空间很相似，把高维分成了很多个");
        temp.second.push_back("低维的层，然后重叠这些层，来构造高维空间。");
        temp.second.push_back("因此w也用小写");
        font2D.insert(temp);

        temp.first = 'e';
        temp.second.clear();
        temp.second.push_back("而且这片空间是连续的，和现实世界一样，不存在割裂。");
        temp.second.push_back("在立柱旁按数字1-9，0为擦除，它们可以帮你调试这片空间。");
        font2D.insert(temp);

        temp.first = ']';
        temp.second.clear();
        temp.second.push_back("这种4D并不严格，仅作为一种表达方式。可参考维基百科");
        temp.second.push_back("至此，5个教学关卡结束。");
        temp.second.push_back("未来，拭目以待……");
        font2D.insert(temp);

    }

    if (level==6)
    {
        temp.first = '=';
        temp.second.clear();
        temp.second.push_back("第6关：田字迷乱");
        temp.second.push_back("迷宫维度：XYw");
        temp.second.push_back("摄影机类型：plain2D");
        font2D.insert(temp);
        
        // 3D字体索引4-7
        list_font3D.push_back( glRes.Build3DText((unsigned char*)"有时你会发现") );
        list_font3D.push_back( glRes.Build3DText((unsigned char*)"你会突然跳出这世界") );
        list_font3D.push_back( glRes.Build3DText((unsigned char*)"发现原来，曾经的一切") );
        list_font3D.push_back( glRes.Build3DText((unsigned char*)"不过就这么大点地方") );
    }

//////////////////////////////////////////////////////////////////////////
}
