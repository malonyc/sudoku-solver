#pragma once

#include <memory>
#include "Group.h"

class Cell
{
public:
    using PII = std::pair<int, int>;

    // 初期値不明ならnumber=0
    Cell(int number, PII position);
    ~Cell();

    // 所属グループの設定
    void setGroup(const std::shared_ptr<Group>& group, Group::GroupType type);

    bool isSolved() const;
    int getNumber() const;
    PII getPosition() const;

private:
	unsigned short mCandidates; //987654321
    
    int mNumber;
    PII mPosition;

    std::weak_ptr<Group> mBlock;
    std::weak_ptr<Group> mRow;
    std::weak_ptr<Group> mColumn;
};

