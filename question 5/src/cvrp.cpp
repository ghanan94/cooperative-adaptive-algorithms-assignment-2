#include "cvrp.hpp"
#include <fstream> // std::ifstream, std::getline
#include <sstream> // std::stringstream

CVRP::CVRP(const std::string file_name)
{
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
    int capacity = 0;
    int dimension = 0;

    while (std::getline(problem_file, line))
    {
      std::stringstream linestream(line);
      std::getline(linestream, data, ':');

      printf("Data: %s\n", data.c_str());

      if (data.find("CAPACITY") != std::string::npos)
      {
        std::getline(linestream, data, ':');
        capacity = std::stoi(data);
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
      }
    }

    problem_file.close();
  } else
  {
    printf("File error\n");
  }
}


/**********************************CVRP::Node**********************************/
CVRP::Node::Node(const int id, const int x, const int y, const int service_time):
id(id),
x(x),
y(y),
service_time(service_time) {}

const int CVRP::Node::get_id()
{
  return id;
}

const int CVRP::Node::get_x()
{
  return x;
}

const int CVRP::Node::get_y()
{
  return y;
}

const int CVRP::Node::get_service_time()
{
  return service_time;
}
