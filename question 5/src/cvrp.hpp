#include <string>
#include <vector>

class CVRP
{
public:
  CVRP(const std::string);
  ~CVRP();

private:
  class Node
  {
  private:
    const int id;
    const int x;
    const int y;
    const int service_time;

  public:
    Node(const int, const int, const int, const int);

    const int get_id();
    const int get_x();
    const int get_y();
    const int get_service_time();
  };

  Node* depot;
  std::vector<Node*> nodes;

  void parse_problem_file(const std::string);
};