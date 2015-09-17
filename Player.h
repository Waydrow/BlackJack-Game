#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include<iostream>
#include<vector>
#include<iomanip>
#include"Card.h"

using namespace std;

class Player
{

public:
    Player(string name_,int numTemp=0){
        name = name_;
        num = numTemp;
		total=0;
    }
    bool IsBusted();
    void Win();
    void Lose();
	void Busts();
    int GetTotal();
    void Push(){
        cout<<name<<" Push!"<<endl;
    }
    void Clear();
    void GetACard(Card tempCard);
    Card GetMyCard()
    {
        return m_Cards[0];
    }
    void SetFirstCard(Card card)
    {
        m_Cards[0]=card;
    }
    friend ostream & operator<<(ostream & os,Player & player)
    {
        cout.setf(ios::left);
        vector<Card>::iterator pCard;
        char rank_code[13]= {'A','2','3','4','5','6','7','8','9','T','J','Q','K'};
        os<<setw(10)<<player.name<<":";
        for (pCard = player.m_Cards.begin(); pCard != player.m_Cards.end(); ++pCard)
            os<<rank_code[pCard->getNum()-1]<<pCard->getColor()<<'\t';
        os<<"<"<<player.GetTotal()<<">";
        return os;
    }
    string getName()
    {
        return name;
    }
    vector<Card>  getM_Cards(){
        return m_Cards;         //返回私有成员m_Cards的地址
    }

private:
    vector<Card> m_Cards;
    string name;
    int num;
	int total;
};


bool Player::IsBusted()
{
    int sum=GetTotal();
    if(sum>21)
        return true;
    else
        return false;
}
void Player::Win()
{
    cout<<name<<" wins!"<<endl;
}
void Player::Busts()
{
	cout<<name<<" busts!"<<endl;
}

void Player::Lose()
{
    cout<<name<<" loses!"<<endl;
}
int Player::GetTotal()
{
	return total;
}
void Player::Clear()
{
	m_Cards.clear();
	num=total=0;
}
void Player::GetACard(Card tempCard)
{
    //cout<<m_Cards.size();
    //m_Cards[num]=tempCard;
    m_Cards.push_back(tempCard);
    num++;
	//在每摸一张牌后即加和到total
	if(tempCard.getNum()==11||tempCard.getNum()==12||tempCard.getNum()==13)		//摸牌为J.Q.K，牌数算为10
		total+=10;
	else if(tempCard.getNum()==1)	//判断为A的情况
	{
		if(total+11>21)total+=1;
		else total+=11;
	}
	else total+=tempCard.getNum();
}


#endif // PLAYER_H_INCLUDED
