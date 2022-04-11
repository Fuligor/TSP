#include "MoveState.h"

#include "InnerEdgeSwap.h"
#include "OuterVertexSwap.h"

MoveState::MoveState()
    :_move(0, 0, 0, 0), _cost(100), _direction(true), _state(nullptr)
{
}

MoveState::MoveState(std::shared_ptr <SearchState> state, Move move)
    :_state(state), _move(move)
{
    if (move.type == Move::Type::INNER)
    {
        _cost = InnerEdgeSwap::calculateCost(state, move.node);
        _direction = InnerEdgeSwap::getDirection(state, move.node);
    }
    else
    {
        _cost = OuterVertexSwap::calculateCost(state, move.node);
        _direction = OuterVertexSwap::getDirection(state, move.node);
    }
}

bool MoveState::operator<(const MoveState& other) const
{
    return _cost > other._cost;
}

bool MoveState::isOutdated()
{
    return _move.type == Move::Type::INNER ? InnerEdgeSwap::isInvalid(_state, _move.node) : OuterVertexSwap::isInvalid(_state, _move.node);
}

bool MoveState::isInvalidated()
{
    bool actualDirection = _move.type == Move::Type::INNER ? InnerEdgeSwap::getDirection(_state, _move.node) : OuterVertexSwap::getDirection(_state, _move.node);

    return _direction != actualDirection;
}

distance MoveState::getCost() const
{
    return _cost;
}

void MoveState::makeMove()
{
    if (_move.type == Move::Type::INNER)
    {
        InnerEdgeSwap::makeMove(_state, _move.node);
    }
    else
    {
        OuterVertexSwap::makeMove(_state, _move.node);
    }
}

std::string MoveState::getName() const
{
    int len = _move.type == Move::Type::INNER ? 4 : 2;

    std::string result = _move.type == Move::Type::INNER ? std::to_string(_state->getNodeCycle(_move.node[0])) + " " : "";

    for(int i = 0; i < len; ++i)
    {
        result += std::to_string(_state->getNodePosition(_move.node[i])) + " ";
    }

    return  result + (_move.type == Move::Type::INNER ? "INNER" : "OUTER") + " ";
}
