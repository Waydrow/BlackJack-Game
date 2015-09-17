#ifndef DECK_H_INCLUDED
#define DECK_H_INCLUDED

#include<iostream>
#include"Player.h"
#include"House.h"

using namespace std;
class Deck
{
public:
    Deck();
    void Populate();
    void Shuffle();
    void Deal(Player & player);
    void AdditionalCards(Player & player);
    void AdditionalCards(House & house);
private:
    Card CardDesk[52];
    int num;
};

Deck::Deck()
{
    num = 0;
}
void Deck::Populate()
{
    int j,k,num=0;
    char suit_code[4]= {'s','h','c','d'}; //初始化花色数组
    Card temp[4][13];   //一幅整齐的牌，未被打乱
    for(j=0; j<4; j++)
    {
        for(k=0; k<13; k++)
        {
            temp[j][k].setNum(k+1);
            temp[j][k].setColor(suit_code[j]);
            CardDesk[num]=temp[j][k];
            num++;
        }
    }
}
void Deck::Shuffle()
{
    Card OtherDesk[52];
    int num=0,key=0;
    for(; num<52; num++)
    {
        do
        {
            key = rand()%52;
        }
        while(CardDesk[key].getNum()==0);
		OtherDesk[num]=CardDesk[key];
        CardDesk[key].setNum(0);
    }
    for(num=0;num<52;num++)
        CardDesk[num]=OtherDesk[num];
}
void Deck::Deal(Player & player)
{
    if(num>51)
    {
        cout<<"The card has been used out!"<<endl;
        exit(0);
    }
    player.GetACard(CardDesk[num]);
    num++;
}
void Deck::AdditionalCards(Player & player)
{
    char choice;
    while(!player.IsBusted())
    {
        cout<<player.getName()<<",Do you want a hit?(Y/N)"<<endl;
        cin>>choice;
        if(choice=='N'||choice=='n')
            break;
        else
            Deal(player);
        cout<<player<<endl;
    }
	if(player.IsBusted())player.Busts();
}
void Deck::AdditionalCards(House & house)
{
    while((!house.IsBusted())&&(house.GetTotal()<16))
    {
        Deal(house);
        cout<<house<<endl;
    }
}

#endif // DECK_H_INCLUDED
