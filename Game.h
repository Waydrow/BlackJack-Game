#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include"Card.h"
#include"House.h"
#include"Player.h"
#include"Deck.h"
#include<iostream>

using namespace std;
class Game
{
public:
    Game(const vector<string>& names);
    ~Game();
    void Play();
private:
    Deck m_Deck;
    House m_House;
    vector<Player> m_Players;
};

Game::Game(const vector<string>& names)
{
    // 由vector name创建vector player
    vector<string>::const_iterator pName;
    for (pName = names.begin(); pName != names.end(); ++pName)
    {
        m_Players.push_back(Player(*pName));
    }
    // 设置随机数种子
    srand(static_cast<unsigned int>(time(0)));
    m_Deck.Populate();
    m_Deck.Shuffle();
}

Game::~Game()
{}

void Game::Play()
{
    // 为每个人发两张牌
    vector<Player>::iterator pPlayer;
    for (int i = 0; i < 2; ++i)
    {
        for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
        {
            m_Deck.Deal(*pPlayer);
        }
        m_Deck.Deal(m_House);
    }

    // 隐藏house的第一张牌
    m_House.FlipFirstCard();

    // display每个player的牌
    for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
    {
        cout << *pPlayer << endl;
    }
    cout << m_House << endl;

    // 每个玩家添加牌（在addtionanl里面判断是否要进行hit）
    for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
    {
        m_Deck.AdditionalCards(*pPlayer);
    }

    // 亮出house的第一张牌
    m_House.FlipFirstCard();
	cout << endl << m_House<<endl;

    // 为house添加额外牌
    m_Deck.AdditionalCards(m_House);

    // 判断输赢#include <ctime>


    if (m_House.IsBusted())
    {
        for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
        {
            if (!(pPlayer->IsBusted()))
            {
                pPlayer->Win();
            }
        }
    }
    else
    {
        for (pPlayer = m_Players.begin(); pPlayer != m_Players.end();++pPlayer)
        {
            if (!(pPlayer->IsBusted()))
            {
                if (pPlayer->GetTotal() > m_House.GetTotal())
                {
                    pPlayer->Win();
                }
                else if (pPlayer->GetTotal() < m_House.GetTotal())
                {
                    pPlayer->Lose();
                }
                else
                {
                    pPlayer->Push();
                }
            }
        }
    }
    // 移除所有玩家的牌
    for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
    {
        pPlayer->Clear();
    }
    m_House.Clear();
}

#endif // GAME_H_INCLUDED
