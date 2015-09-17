#ifndef CARD_H_INCLUDED
#define CARD_H_INCLUDED

class Card
{
public:
    Card(int num_=0,char color_=0)
    {
        num=num_;
        color=color_;
    }
    int getNum()
    {
        return num;
    }
    char getColor()
    {
        return color;
    }
    void setNum(int temp)
    {
        num=temp;
    }
    void setColor(char temp)
    {
        color=temp;
    }
private:
    int num;
    char color;
};


#endif // CARD_H_INCLUDED
