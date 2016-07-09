#include "qap.hpp"
#include <fstream> // std::ifstream, std::getline
#include <sstream> // std::stringstream
#include <climits> // INT_MAX

/*
 * Constructor
 */
QAP::QAP(std::string flow_table_file_path, std::string distance_table_file_path)
{
  parse_flow_distance_table_file(flow_table, flow_table_file_path);
  parse_flow_distance_table_file(distance_table, distance_table_file_path);
}

/*
 * Destructor
 */
QAP::~QAP()
{
}

/*
 * Parse the flow or distance table data given the file name.
 */
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

/*
 * Print given table.
 */
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

/*
 * Print the flow table.
 */
void QAP::print_flow_table()
{
  printf("\nFlow Table:\n");
  print_table(flow_table);
}

/*
 * Reset the distance table.
 */
void QAP::print_distance_table()
{
  printf("\nDistance Table:\n");
  print_table(distance_table);
}

/*
 * Given n objects, and the flows f(i,j) between objcet i and j and given n
 * sites with distance d(r, s) between the sites r and s, the total cost is
 * Σ(r = 1 to n)[Σ(s = 1 to n)[f(p(r), p(s)) * d(r, s)]], where p(r) is the
 * objcet at site r.
 */
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

/*
 * Solve the QAP given the flow and distance tables using TABU search.
 * If a non-tabu move is available, do the best non-tabu move.
 * If no non-tabu move is avalable, do the best tabu move.
 * On each move, add the move to the tabu table.
 * Keep trying to find moves until no better move has been found for
 * SEARCH_END_COUNT iterations.
 */
std::vector<int> QAP::solve()
{
  std::srand(time(NULL));

  // Below is just a random initial solution that will be improved on
  std::vector<int> solution;

  // Generate a random initial solution
  while (solution.size() != NUM_OBJECTS)
  {
    int val = ((int)rand()) % NUM_OBJECTS;

    if (std::find(solution.begin(), solution.end(), val) == solution.end())
    {
      // Value is not already in solution
      solution.push_back(val);
    }
  }

  // Print the initial solution
  printf("Initial solution:\n");
  print_solution(solution);

  std::vector<int> intermediate_solution = solution;
  int solution_cost = evaluate_cost(solution);
  int intermediate_solution_cost = solution_cost;
  unsigned int counter = 0;

  // Reset Tabu table
  tabu_reset();

  while (counter < SEARCH_END_COUNT)
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
        temp = intermediate_solution[i];
        intermediate_solution[i] = intermediate_solution[j];
        intermediate_solution[j] = temp;

        int temp_cost = evaluate_cost(intermediate_solution);

        if (tabu_check(i, j))
        {
          // TABU
          if (temp_cost < best_tabu_cost)
          {
            best_tabu_cost = temp_cost;
            best_tabu_i = i;
            best_tabu_j = j;
          }
        } else
        {
          if (temp_cost < best_cost)
          {
            best_cost = temp_cost;
            best_i = i;
            best_j = j;
          }
        }

        // Switch back
        temp = intermediate_solution[i];
        intermediate_solution[i] = intermediate_solution[j];
        intermediate_solution[j] = temp;
      }
    }

    if (best_i == -1)
    {
      // No non-tabu moves available
      temp = intermediate_solution[best_tabu_i];
      intermediate_solution[best_tabu_i] = intermediate_solution[best_tabu_j];
      intermediate_solution[best_tabu_j] = temp;
      intermediate_solution_cost = best_cost;

      tabu_add(best_tabu_i, best_tabu_j);
    } else
    {
      // Do a non-tabu move
      temp = intermediate_solution[best_i];
      intermediate_solution[best_i] = intermediate_solution[best_j];
      intermediate_solution[best_j] = temp;
      intermediate_solution_cost = best_tabu_cost;

      tabu_add(best_i, best_j);
    }

    if (intermediate_solution_cost < solution_cost) {
      solution = intermediate_solution;
      solution_cost = intermediate_solution_cost;
      counter = 0;
    } else
    {
      ++counter;
    }
  }

  return solution;
}

/*
 * Add a move to the tabu table. If TABU_DYNAMIC is set, then randomly choose
 * a tabu tenure value from 0 to TABU_TENURE.
 */
void QAP::tabu_add(int i, int j)
{
  if (i == j)
  {
    return;
  } else if (i > j)
  {
    if (TABU_DYNAMIC)
    {
      tabu_table[j][i - j - 1] = (((int)rand()) % MAX_DYNAMIC_TABU_TENURE) + 1;
    } else
    {
      tabu_table[j][i - j - 1] = TABU_TENURE + 1;
    }
  } else
  {
    if (TABU_DYNAMIC)
    {
      tabu_table[i][j - i - 1] = (((int)rand()) % MAX_DYNAMIC_TABU_TENURE) + 1;
    } else
    {
      tabu_table[i][j - i - 1] = TABU_TENURE + 1;
    }

  }
}

/*
 * Reset the tabu table
 */
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

/*
 * Check if a move is tabu.
 * Returns true if it is tabu; false otherwise.
 */
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

/*
 * Print a given solution.
 */
void QAP::print_solution(std::vector<int>& solution)
{
  printf("\nSolution:\n");

  for (int j = 0; j < NUM_OBJECTS; ++j){
    printf("Site%-3d: Object%-3d\n", j, solution[j]);
  }

  printf("Cost: %d\n", evaluate_cost(solution));
}

/*
 * Find the solution and print it.
 */
void QAP::find_solution()
{
  std::vector<int> solution = solve();
  print_solution(solution);
}
