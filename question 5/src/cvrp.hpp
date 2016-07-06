#include <string>
#include <vector>

class CVRP
{
private:
  class Node
  {
  private:
    const unsigned int id;
    const unsigned int x;
    const unsigned int y;
    unsigned int service_time;

  public:
    Node(const unsigned int, const unsigned int, const unsigned int, const unsigned int);

    const unsigned int get_id();
    const unsigned int get_x();
    const unsigned int get_y();
    const unsigned int get_service_time();

    void set_service_time(const unsigned int);
  };

  unsigned int max_capacity;
  unsigned int dimension;
  Node* depot;
  std::vector<Node*> nodes;

  void parse_problem_file(const std::string);
  double distance_between_nodes(Node*, Node*);
  double cost_function(std::vector<Node*>&);
  void print_solution(std::vector<Node*>&);

public:
  CVRP(const std::string);
  ~CVRP();
  void print_nodes();
  void solve(const double, const double, const double, const unsigned int);
  void initial_solution(std::vector<Node*>&, std::vector<unsigned int>&);
};
