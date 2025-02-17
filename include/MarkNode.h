#pragma once
class MNode {
public:
    MNode(int val);
    void    setVal(const int& val),
            setLeft(MNode* left),
            setRight(MNode* right);
    bool getVal(int& out);
private:
    int     m_val     = 0;
    MNode   *left   = 0,
            *right  = 0;
    bool    isGet   = false;
};