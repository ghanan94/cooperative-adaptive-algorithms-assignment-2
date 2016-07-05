#include "cvrp.hpp"

CVRP::CVRP(const std::string file_name)
{
  // TODO: parse contents within <file_name> and populate 'nodes'
}

CVRP::~CVRP()
{
  for (int i = 0; i < nodes.size(); i++)
  {
    delete nodes[i];
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
