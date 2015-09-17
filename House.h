#ifndef HOUSE_H_INCLUDED
#define HOUSE_H_INCLUDED

#include"Player.h"
#include<iostream>

using namespace std;

class House:public Player
{
public:
    House(string name="House",int num=0,int Flag=0):Player(name,num),Flag(Flag)
    {}
    void FlipFirstCard();
    friend ostream & operator<<(ostream & os,House & house)
    {
        vector<Card>::iterator pCard;
        cout.setf(ios::left);
        char rank_code[14]= {'A','2','3','4','5','6','7','8','9','T','J','Q','K','X'};
        os<<setw(10)<<"House"<<":";
        vector<Card> tempM_Cards=house.getM_Cards();    //定义临时变量得到house继承player的m_Cards的地址
        for(pCard=tempM_Cards.begin(); pCard !=tempM_Cards.end(); ++pCard)
            os<<rank_code[pCard->getNum()-1]<<pCard->getColor()<<'\t';
        if(house.Flag==0)os<<"<"<<house.GetTotal()<<">";
		return os;
    }
private:
    //vector<Card> m_Cards;
    Card FirstCard;
    int Flag;
};

void House::FlipFirstCard()
{
    if(Flag==0)
    {
        FirstCard = GetMyCard();
        Card card(14,'X');
        SetFirstCard(card);
        Flag=1;
    }
    else
    {
        SetFirstCard(FirstCard);
        Flag=0;
    }
}

#endif // HOUSE_H_INCLUDED
