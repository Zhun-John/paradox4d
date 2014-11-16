#pragma once

class CProgression
{
public:
	int currentLevel, levelSum;     //当前关卡、关卡总数
	//int reachedLevel;		// 玩家进度
	int itemLocked[10];		// 每个数字物品的状态。0为不可用。1为首次接触。2为可用
		//每个物品会在首次接触后解锁，但首次接触时应持续显示Hud台词直到离开
	char prevItem;		// 玩家接触的上一个物体，可能因为移动到新方格，或在当前格子摆放物体
public:
	CProgression(void):currentLevel(1),levelSum(5){
		memset(itemLocked,0,sizeof(itemLocked));
	}

	~CProgression(void)
	{};
public:
	void ChangeLevel(int portal){
		currentLevel += portal;
		if (currentLevel<=0 || currentLevel>levelSum)
		{
			currentLevel=levelSum/2;
		}
	}
	// 根据当前位置的物体，触发进度解锁逻辑
	void OnItem(char item){
		//物体无变化，返回
		if(item==prevItem) return;
		//若首次接触到可解锁的物体，且其状态为 不可用
		if( IsUnlockableItem(item) && itemLocked[item-'0']==0){
			itemLocked[item-'0'] = 1;//修改状态为 首次接触
			if (item=='3'){
				itemLocked[1] = itemLocked[2] = 2;
			}
		}
		//若离开可解锁的物体，且其状态为 首次接触
		if( IsUnlockableItem(prevItem) && itemLocked[prevItem-'0']==1 ){
			itemLocked[prevItem-'0'] = 2;//修改状态为 可用
		}
		prevItem = item;
	}

private:
	bool IsUnlockableItem(char item){
		return item>='3' && item<='9';
	}
};

