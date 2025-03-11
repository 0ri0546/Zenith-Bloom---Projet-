#include "../systems/pathfinfing.hpp"

bool CompareNodePtr::operator()(const Node* a, const Node* b) const
{

	return a->fCost > b->fCost;

}
	
std::size_t Vector2iHash::operator()(const sf::Vector2i& v) const
{
	return std::hash<float>()(v.x) ^ std::hash<float>()(v.y);
}


std::vector<sf::Vector2i> Pathfinding::findPath(Grid& grid, sf::Vector2i start, sf::Vector2i end)
{
    std::priority_queue<Node*, std::vector<Node*>, CompareNodePtr> openQueue;
    std::unordered_map<sf::Vector2i, Node*, Vector2iHash> allNodes;
    std::vector<sf::Vector2i> directions = {
        {0, 1}, {1, 0}, {0, -1}, {-1, 0},
        {-1, -1}, {1, -1}, {1, 1}, {-1, 1}

    };

    Node* startNode = new Node(start);
    startNode->gCost = 0;
    startNode->hCost = startNode->calculateHeuristic(end);
    startNode->fCost = startNode->gCost + startNode->hCost;

    openQueue.push(startNode);
    allNodes[start] = startNode;

    while (!openQueue.empty()) {
        Node* current = openQueue.top();
        openQueue.pop();

        if (current->position == end) {
            std::vector<sf::Vector2i> path;
            while (current) {
                path.push_back(current->position);
                current = current->parent;
            }
            std::reverse(path.begin(), path.end());

            for (auto& pair : allNodes) delete pair.second;
            return path;
        }

        for (auto& dir : directions) {
           sf::Vector2i neighborPos = current->position + dir;

            if (neighborPos.x < 0 || neighborPos.x >= grid.largeur || neighborPos.y < 0 || neighborPos.y >= grid.hauteur)
                continue;
            if (grid.gridList[neighborPos.y][neighborPos.x])
                continue;

            if ((dir.x != 0 && dir.y != 0) &&
                (grid.gridList[current->position.y][neighborPos.x] || grid.gridList[neighborPos.y][current->position.x]))
                continue;

            int newGCost = current->gCost + ((dir.x != 0 && dir.y != 0) ? 14 : 10); // 10 for straight, 14 for diagonal

            Node* neighbor;
            if (allNodes.find(neighborPos) != allNodes.end()) {
                neighbor = allNodes[neighborPos];
                if (newGCost < neighbor->gCost) {
                    neighbor->gCost = newGCost;
                    neighbor->fCost = newGCost + neighbor->hCost;
                    neighbor->parent = current;
                    openQueue.push(neighbor);
                }
            }
            else {
                neighbor = new Node(neighborPos);
                neighbor->gCost = newGCost;
                neighbor->hCost = neighbor->calculateHeuristic(end);
                neighbor->fCost = neighbor->gCost + neighbor->hCost;
                neighbor->parent = current;
                openQueue.push(neighbor);
                allNodes[neighborPos] = neighbor;
            }
        }
    }

    for (auto& pair : allNodes) delete pair.second;
    return {};



}