#include "qap.hpp"
#include <fstream> // std::ifstream, std::getline
#include <sstream> // std::stringstream
#include <climits>

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
  int solution_cost = 0;
  unsigned int counter = 0;

  // Initial solution
  for (int i = 0; i < NUM_OBJECTS; ++i)
  {
    solution.push_back(i);
  }

  solution_cost = evaluate_cost(solution);

  // Reset Tabu table
  tabu_reset();

  while (counter < SEARCH_END_COUNT)
  {
    std::vector<int> temp_solution = find_best_move(solution);
    int temp_solution_cost = evaluate_cost(temp_solution);

    if (temp_solution_cost < solution_cost)
    {
      solution_cost = temp_solution_cost;
      solution = temp_solution;
      counter = 0;
    } else {
      ++counter;
    }
  }

  print_solution(solution);

  return solution;
}

void QAP::tabu_add(int i, int j)
{
  if (i == j)
  {
    return;
  } else if (i > j)
  {
    tabu_table[j][i - j - 1] = TABU_TENURE;
  } else
  {
    tabu_table[i][j - i - 1] = TABU_TENURE;
  }
}

void QAP::tabu_reset()
{
  tabu_table.clear();

  for (int i = 0; i < NUM_OBJECTS; ++i)
  {
    std::vector<int> row;

    for (int j = i + 1; j < NUM_OBJECTS; ++j)
    {
      row.push_back(0);
    }

    tabu_table.push_back(row);
  }
}

bool QAP::tabu_check(int i, int j)
{
  if (i == j)
  {
    // should never do this swap since same positions
    return true;
  } else if (i > j)
  {
    return tabu_table[j][i - j - i] > 0;
  } else
  {
    return tabu_table[i][j - i - 1] > 0;
  }
}

void QAP::print_solution(std::vector<int>& solution)
{
  printf("\nSolution:\n");

  for (int j = 0; j < NUM_OBJECTS; ++j){
    printf("Site%-3d: Object%-3d\n", j, solution[j]);
  }

  printf("Cost: %d\n", evaluate_cost(solution));
}

std::vector<int> QAP::find_best_move(std::vector<int> solution)
{
  int temp;
  int best_i = -1;
  int best_j = -1;
  int best_tabu_i = -1;
  int best_tabu_j = -1;
  int best_cost = INT_MAX;
  int best_tabu_cost = INT_MAX;

  for (int i = 0; i < NUM_OBJECTS; ++i)
  {
    for (int j = i + 1; j < NUM_OBJECTS; ++j)
    {
      // Do a swap
      temp = solution[i];
      solution[i] = solution[j];
      solution[j] = temp;

      int temp_cost = evaluate_cost(solution);

      if (tabu_check(i, j))
      {
        // TABU
        if (temp_cost < best_cost)
        {
          best_cost = temp_cost;
          best_i = i;
          best_j = j;
        }
      } else
      {
        if (temp_cost < best_tabu_cost)
        {
          best_tabu_cost = temp_cost;
          best_tabu_i = i;
          best_tabu_j = j;
        }
      }

      // Switch back
      temp = solution[i];
      solution[i] = solution[j];
      solution[j] = temp;
    }
  }

  if (best_i == -1)
  {
    temp = solution[best_tabu_i];
    solution[best_tabu_i] = solution[best_tabu_j];
    solution[best_tabu_j] = temp;
  } else {
    temp = solution[best_i];
    solution[best_i] = solution[best_j];
    solution[best_j] = temp;
  }

  return solution;
}
