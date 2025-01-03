#include "ghost.h"
#include "mario.h"
#include "game.h"

void Ghost::checkMove(GameConfig& board, Mario& mario, bool& flag, std::vector<Ghost>& ghosts)
{
    Point p(location.x, location.y);
    Game::setCharCheck(this->location, board, DELETE_CH, mario, flag);
    char originalChar = board.GetChar(location.x, location.y);
    Game::setCharCheck(location, board, originalChar, mario, flag);
    p.draw(originalChar, location);

    location.diff_x = direction ? 1 : -1;

    checkCollision(ghosts);

    if (board.GetChar(p.x + location.diff_x, p.y + 1) == '<' || board.GetChar(p.x + location.diff_x, p.y + 1) == '>' || board.GetChar(p.x + location.diff_x, p.y + 1) == '-')
    {
        if (board.GetChar(this->location.x + location.diff_x, this->location.y) == GHOST_CH)
        {
            direction = !direction;
            location.diff_x = direction ? 1 : -1;
            if (board.GetChar(p.x + location.diff_x, p.y) == '|')
                location.diff_x = 0;
        }
        else if (board.GetChar(p.x + location.diff_x, p.y) != '|')
        {
            randomDirection();
        }
        else
            direction = !direction;
    }
    else
    {
        direction = !direction;
        location.diff_x = direction ? 1 : -1;
        if (board.GetChar(this->location.x + location.diff_x, this->location.y) == GHOST_CH)
            location.diff_x = 0;
    }

    moveGhosts();
    Game::setCharCheck(location, board, GHOST_CH, mario, flag);
    p.draw(GHOST_CH, location);
}

void Ghost::checkCollision(std::vector<Ghost>& ghosts)
{
    for (Ghost& otherGhost : ghosts)
    {
        if (this != &otherGhost && otherGhost.location.x == this->location.x + location.diff_x && otherGhost.location.y == this->location.y)
        {
            // Swap directions when two ghosts meet
            direction = !direction;
            otherGhost.direction = !otherGhost.direction;
            location.diff_x = direction ? 1 : -1;
            otherGhost.location.diff_x = otherGhost.direction ? 1 : -1;
        }
    }
}

void Ghost::moveGhosts()
{
	if(location.diff_x != 0)
		location.x += direction ? 1 : -1;
}

void Ghost::randomDirection()
{
    int randomNum = (std::rand() % 100) + 1;
    if (randomNum > 95)
        direction = !direction;
}

