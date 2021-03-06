#include "Cell.h"

#include "Block.h"
#include "Row.h"
#include "Column.h"
#include "BitTools.h"

#include <cassert>

Cell::Cell(
    int number,
    PII position
    ):
    mCandidates(0b111111111),
    mNumber(number),
    mPosition(position)
{
    // 初めから数字が埋まっている場合、数字決定処理を行う
    if (isSolved())
    {
        setNumber(number);
    }
}

Cell::~Cell()
{
}

void Cell::setNumber(int number)
{
    mNumber = number;
    mCandidates = BitTools::numToBit(number);

    //更新通知
    notifyUpdate();
}

void Cell::notifyUpdate()
{
    // まだグループがセットされてないなら通知しない
    if (mBlock.expired() || mColumn.expired() || mRow.expired())
    {
        return;
    }

    std::shared_ptr<Group> block = mBlock.lock();
    std::shared_ptr<Group> column = mColumn.lock();
    std::shared_ptr<Group> row = mRow.lock();
    if (block)
    {
        block->addFoundNumber(mNumber);
    }
    if (column)
    {
        column->addFoundNumber(mNumber);
    }
    if (row)
    {
        row->addFoundNumber(mNumber);
    }
}

void Cell::setGroup(const std::shared_ptr<Group>& group, Group::GroupType type)
{
    switch (type)
    {
    case Group::GroupType::BLOCK:
        mBlock = group;
        break;
    case Group::GroupType::COLUMN:
        mColumn = group;
        break;
    case Group::GroupType::ROW:
        mRow = group;
        break;
    }

    // 数字が決まっているなら更新通知
    if (isSolved())
    {
        notifyUpdate();
    }
}

void Cell::removeCandidate(int num)
{
    unsigned short candidateBit = BitTools::numToBit(num);
    mCandidates &= ~candidateBit;

    if (countCandidate() == 1)
    {
        int number = BitTools::bitToNum(mCandidates);
        setNumber(number);
    }
}


// 候補中の1の数を数える
int Cell::countCandidate() const
{
    unsigned short c = mCandidates - ((mCandidates >> 1) & 0x0055);
    c = (c & 0x0333) + ((c >> 2) & 0x0033);
    c = (c + (c >> 4)) & 0x0f0f;
    c = c + (c >> 8);
    
    return c & 0xf;
}

bool Cell::isSolved() const
{
    return mNumber != 0;
}

int Cell::getNumber() const
{
    return mNumber;
}

Cell::PII Cell::getPosition() const
{
    return mPosition;
}

unsigned short Cell::getCandidateBit() const
{
    return mCandidates;
}

std::shared_ptr<Group> Cell::getRow() const
{
    return mRow.lock();
}

std::shared_ptr<Group> Cell::getColumn() const
{
    return mColumn.lock();
}