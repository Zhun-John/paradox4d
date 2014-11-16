#pragma once

class CProgression
{
public:
	int currentLevel, levelSum;     //��ǰ�ؿ����ؿ�����
	//int reachedLevel;		// ��ҽ���
	int itemLocked[10];		// ÿ��������Ʒ��״̬��0Ϊ�����á�1Ϊ�״νӴ���2Ϊ����
		//ÿ����Ʒ�����״νӴ�����������״νӴ�ʱӦ������ʾHud̨��ֱ���뿪
	char prevItem;		// ��ҽӴ�����һ�����壬������Ϊ�ƶ����·��񣬻��ڵ�ǰ���Ӱڷ�����
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
	// ���ݵ�ǰλ�õ����壬�������Ƚ����߼�
	void OnItem(char item){
		//�����ޱ仯������
		if(item==prevItem) return;
		//���״νӴ����ɽ��������壬����״̬Ϊ ������
		if( IsUnlockableItem(item) && itemLocked[item-'0']==0){
			itemLocked[item-'0'] = 1;//�޸�״̬Ϊ �״νӴ�
			if (item=='3'){
				itemLocked[1] = itemLocked[2] = 2;
			}
		}
		//���뿪�ɽ��������壬����״̬Ϊ �״νӴ�
		if( IsUnlockableItem(prevItem) && itemLocked[prevItem-'0']==1 ){
			itemLocked[prevItem-'0'] = 2;//�޸�״̬Ϊ ����
		}
		prevItem = item;
	}

private:
	bool IsUnlockableItem(char item){
		return item>='3' && item<='9';
	}
};

