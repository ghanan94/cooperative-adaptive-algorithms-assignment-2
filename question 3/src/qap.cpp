#include "qap.hpp"
#include <fstream> // std::ifstream, std::getline
#include <sstream> // std::stringstream

QAP::QAP(std::string flow_table_file_path, std::string distance_table_file_path)
{
  parse_flow_distance_table_file(flow_table, flow_table_file_path);
  parse_flow_distance_table_file(distance_table, distance_table_file_path);
}

QAP::~QAP()
{
}

void QAP::parse_flow_distance_table_file(Table& table, std::string file_name)
{
  std::ifstream file;
  std::string line;
  std::string data;

  if (table.size())
  {
    table.clear();
  }

  file.open(file_name);

  if (file.is_open())
  {
    for (int y = 0; y < NUM_OBJECTS; ++y)
    {
      std::vector<int> row;
      std::getline(file, line);
      std::stringstream linestream(line);

      for (int x = 0; x < NUM_OBJECTS; ++x)
      {
        std::getline(linestream, data, ',');
        int value = std::stoi(data);

        row.push_back(value);
      }

      table.push_back(row);
    }

    file.close();
  } else
  {
    printf("File error\n");
  }
}

void QAP::print_table(Table& table)
{
  for (int i = 0; i < table.size(); ++i)
  {
    for (int j = 0; j < table[i].size(); ++j)
    {
      printf("%-2d, ", table[i][j]);
    }

    printf("\n");
  }
}

void QAP::print_flow_table()
{
  printf("\nFlow Table:\n");
  print_table(flow_table);
}

void QAP::print_distance_table()
{
  printf("\nDistance Table:\n");
  print_table(distance_table);
}

int QAP::evaluate_cost(std::vector<int> &assignment)
{
  int cost = 0;

  for (int i = 0; i < NUM_OBJECTS; ++i){
    for (int j = i + 1; j < NUM_OBJECTS; ++j){
      cost += flow_table[assignment[i]][assignment[j]] * distance_table[i][j];
    }
  }

  return cost;
}

std::vector<int> QAP::solve()
{
  std::vector<int> solution;

  for (int i = 0; i < NUM_OBJECTS; ++i)
  {
    solution.push_back(i);
  }

    printf("cost: %d\n", evaluate_cost(solution));

  return solution;
}
