#include "cvrp.hpp"
#include <fstream> // std::ifstream, std::getline
#include <sstream> // std::stringstream
#include <cmath>

CVRP::CVRP(const std::string file_name)
{
  max_capacity = 0;
  dimension = 0;
  parse_problem_file(file_name);
}

CVRP::~CVRP()
{
  for (int i = 0; i < nodes.size(); i++)
  {
    delete nodes[i];
  }
}

void CVRP::parse_problem_file(const std::string file_name)
{
  std::ifstream problem_file;
  std::string line;
  std::string data;

  problem_file.open(file_name);

  if (problem_file.is_open())
  {
    while (std::getline(problem_file, line))
    {
      std::stringstream linestream(line);
      std::getline(linestream, data, ':');

      if (data.find("CAPACITY") != std::string::npos)
      {
        std::getline(linestream, data, ':');
        max_capacity = std::stoi(data);
      } else if (data.find("DIMENSION") != std::string::npos)
      {
        std::getline(linestream, data, ':');
        dimension = std::stoi(data);
      } else if (data.find("NODE_COORD_SECTION") != std::string::npos)
      {
        int i = dimension;

        while (i-- != 0)
        {
          int id;
          int x;
          int y;

          std::getline(problem_file, line);
          std::stringstream node_coord_section_linestream(line);

          // Node info is formatted as follows: " <id> <x> <y>"
          // ***The space before <id> is taken care of using the first getline
          std::getline(node_coord_section_linestream, data, ' ');

          std::getline(node_coord_section_linestream, data, ' ');
          id = std::stoi(data);

          std::getline(node_coord_section_linestream, data, ' ');
          x = std::stoi(data);

          std::getline(node_coord_section_linestream, data, ' ');
          y = std::stoi(data);

          Node* node = new Node(id, x, y, 0);
          nodes.push_back(node);
        }
      } else if (data.find("DEMAND_SECTION") != std::string::npos)
      {
        int i = dimension;

        while (i-- != 0)
        {
          int id;
          int service_time;

          std::getline(problem_file, line);
          std::stringstream node_coord_section_linestream(line);

          // Node info is formatted as follows: "<id> <service_time>"
          // ***There is no space before <id> unlike NODE_COORD_SECTION
          std::getline(node_coord_section_linestream, data, ' ');
          id = std::stoi(data);

          std::getline(node_coord_section_linestream, data, ' ');
          service_time = std::stoi(data);

          nodes[id - 1]->set_service_time(service_time);

          // Check if depot
          if (service_time == 0)
          {
            depot = nodes[id - 1];
          }
        }
      }
    }

    problem_file.close();
  } else
  {
    printf("File error\n");
  }
}

void CVRP::print_nodes()
{
  for (int i = 0; i < dimension; i++)
  {
    printf("id: %-2d x: %-2d y: %-2d s: %-2d", nodes[i]->get_id(), nodes[i]->get_x(), nodes[i]->get_y(), nodes[i]->get_service_time());

    if (nodes[i] == depot)
    {
      printf(" [DEPOT]");
    }

    printf("\n");
  }
}

double CVRP::distance_between_nodes(Node* from_node, Node* to_node)
{
  // Calculate euclidean distance
  return sqrt(pow((int)(to_node->get_x() - from_node->get_x()), 2.0) + pow((int)(to_node->get_y() - from_node->get_y()), 2.0));
}

double CVRP::cost_function(std::vector<Node*>& solution)
{
  double cost = 0;

  for (int i = 1; i < solution.size(); ++i)
  {
    cost += distance_between_nodes(solution[i - 1], solution[i]);
  }

  return cost;
}

/*
 * Solution is represented as [d, R1, d, R2, ..., d, Rn]
 * d = depot id number, R1 is list of nodes in a route
 */
void CVRP::solve(const double intial_temperature, const double final_temperature, const double alpha, const unsigned int iterations_per_temperature)
{
  double temperature = intial_temperature;
  std::vector<Node*> solution;
  std::vector<Node*> temp_solution;
  std::vector<unsigned int> capacity;
  double solution_cost;
  double temp_solution_cost;

  initial_solution(solution, capacity);

  solution_cost = cost_function(solution);
  temp_solution = solution;
  temp_solution_cost = solution_cost;

  while (temperature > final_temperature)
  {
    for (int i = 0; i < iterations_per_temperature; ++i)
    {
      // TODO
    }

    temperature *= alpha;
  }

  print_solution(solution);
}

void CVRP::print_solution(std::vector<Node*>& solution)
{
  int route_num = 0;

  printf("\nSolution:  ");

  for (int i = 0; i < solution.size() - 1; ++i)
  {
    if (solution[i] == depot)
    {
      // Overwrite last 2 letters in console with spaces
      printf("\b\b  \n");

      printf("Route %2d: ", route_num++);
    } else
    {
      printf("[%d]->", solution[i]->get_id());
    }
  }

  // Overwrite last 2 letters in console with spaces
  printf("\b\b  \n");

  printf("Total cost: %f\n", cost_function(solution));
}

/*
 * Initial solution generated deterministically using a greedy algorithm
 * based on a first-fit approach. Look at each customer, and assign the first
 * customer in the list to a new route as long as its capcity doesnt violate
 * max_capacity and sets its status to visited. The algorithm then proceeds to
 * the next customer in the list. If it encounters a customer demand that violates
 * the max_capacity, the customer is skipped and the following customer in the
 * list is processed. If the route capacity is exceeded, then a new route is
 * allocated and the algorithm repeats until all customers have been assigned
 * to routes.
 */
void CVRP::initial_solution(std::vector<Node*>& solution, std::vector<unsigned int>& capacity)
{
  std::vector<bool> visited(dimension, false);
  int counter = 1;
  int route = 0;

  while (counter <dimension) {
    // Allocate a new route
    capacity.push_back(0);
    solution.push_back(depot);

    for (int j = 0; j < dimension; j++)
    {
      // If node is not visited, not depot, doesn't violate current route's
      // max_capcity, then add to route
      if (nodes[j] != depot && !visited[j])
      {
        if (capacity[route] + nodes[j]->get_service_time() < max_capacity)
        {
          solution.push_back(nodes[j]);
          visited[j] = true;
          capacity[route] += nodes[j]->get_service_time();
          ++counter;
        }
      }
    }

    ++route;
  }

  solution.push_back(depot);
}

/**********************************CVRP::Node**********************************/
CVRP::Node::Node(const unsigned int id, const unsigned int x, const unsigned int y, const unsigned int service_time):
id(id),
x(x),
y(y),
service_time(service_time) {}

const unsigned int CVRP::Node::get_id()
{
  return id;
}

const unsigned int CVRP::Node::get_x()
{
  return x;
}

const unsigned int CVRP::Node::get_y()
{
  return y;
}

const unsigned int CVRP::Node::get_service_time()
{
  return service_time;
}

void CVRP::Node::set_service_time(const unsigned int service_time)
{
  this->service_time = service_time;
}
