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
    // ��vector name����vector player
    vector<string>::const_iterator pName;
    for (pName = names.begin(); pName != names.end(); ++pName)
    {
        m_Players.push_back(Player(*pName));
    }
    // �������������
    srand(static_cast<unsigned int>(time(0)));
    m_Deck.Populate();
    m_Deck.Shuffle();
}

Game::~Game()
{}

void Game::Play()
{
    // Ϊÿ���˷�������
    vector<Player>::iterator pPlayer;
    for (int i = 0; i < 2; ++i)
    {
        for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
        {
            m_Deck.Deal(*pPlayer);
        }
        m_Deck.Deal(m_House);
    }

    // ����house�ĵ�һ����
    m_House.FlipFirstCard();

    // displayÿ��player����
    for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
    {
        cout << *pPlayer << endl;
    }
    cout << m_House << endl;

    // ÿ���������ƣ���addtionanl�����ж��Ƿ�Ҫ����hit��
    for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
    {
        m_Deck.AdditionalCards(*pPlayer);
    }

    // ����house�ĵ�һ����
    m_House.FlipFirstCard();
	cout << endl << m_House<<endl;

    // Ϊhouse��Ӷ�����
    m_Deck.AdditionalCards(m_House);

    // �ж���Ӯ#include <ctime>


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
    // �Ƴ�������ҵ���
    for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
    {
        pPlayer->Clear();
    }
    m_House.Clear();
}

#endif // GAME_H_INCLUDED
