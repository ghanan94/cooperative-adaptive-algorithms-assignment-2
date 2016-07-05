#include <string>
#include <vector>

class CVRP
{
public:
  CVRP(const std::string);
  ~CVRP();
  void print_nodes();

private:
  class Node
  {
  private:
    const int id;
    const int x;
    const int y;
    int service_time;

  public:
    Node(const int, const int, const int, const int);

    const int get_id();
    const int get_x();
    const int get_y();
    const int get_service_time();

    void set_service_time(const int);
  };

  Node* depot;
  std::vector<Node*> nodes;

  void parse_problem_file(const std::string);
  double distance_between_nodes(Node*, Node*);
  double cost_function(std::vector<Node*>&);
};
