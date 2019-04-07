#include "Cell.h"

#include "Block.h"
#include "Row.h"
#include "Column.h"

Cell::Cell(
    int number,
    PII position
    ):
    mCandidates(0b111111111),
    mNumber(number),
    mPosition(position)
{
    // ���߂��琔�������܂��Ă���ꍇ�A��������݂̂ɂ���
    if (isSolved())
    {
        mCandidates = 0b1 << (mNumber - 1);
    }
}

Cell::~Cell()
{
}

// TODO:�Q�Ɠn�����Ƃ܂����H
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