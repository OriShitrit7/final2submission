#include "Obstacle.h"

bool Obstacle::isObBody(const Point& p) const
{                       
	for (const Point& cell : body)
	{
		if (cell == p)
			return true;
	}
	return false;
}

bool Obstacle::canBePushed(int force) const 
{
    if (force < getSize())        // Not enough force to move this obstacle
    {
        return false;
    }
    return true;       // All cells can move
}


void Obstacle::move(Direction dir)
{
    if (dir == STAY || dir == DISPOSE)
        return;

    for (Point& cell : body)
    {
        cell = cell.next(dir);
    }
}

std::vector<Point> Obstacle::getNextBody(Direction dir) const
{
    std::vector<Point> result;
    result.reserve(body.size());

    for (const Point& cell : body)
        result.push_back(cell.next(dir));

    return result;
}