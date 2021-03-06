#include "qap.hpp"
#include <fstream> // std::ifstream, std::getline
#include <sstream> // std::stringstream
#include <climits> // INT_MAX
#include <unordered_map>

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
        if (((double)(int)rand())/RAND_MAX < EXCLUDE_PERCENTAGE_NEIGHBOURS)
        {
          // ignore this neighbor
          continue;
        }

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

    // If a tabu exists, but it is the global solution so far or no non-tabu
    // exists, accept it.
    if (best_tabu_i != -1 && (best_i == -1 || best_tabu_cost < solution_cost))
    {
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
  static std::unordered_map<std::string, int> tabu_freq_check;
  std::string key;

  int a;
  int b;

  if (i == j)
  {
    return;
  } else if (i > j)
  {
    a = j;
    b = i - j - 1;
  } else
  {
    a = i;
    b = j - i - 1;
  }

  char buff[6];
  sprintf(buff, "%02d_%02d", a, b);
  key = buff;

  std::unordered_map<std::string, int>::const_iterator it = tabu_freq_check.find(key);
  int mult = 1;

  // Check if key exists in map, if it does, get frequency count and
  // remove from table so it can be readded with new value
  if (it != tabu_freq_check.end())
  {
    mult = it->second + 1;
    tabu_freq_check.erase(key);
  }

  tabu_freq_check.insert(std::pair<std::string, int>(key, mult));
  tabu_table[a][b] = TABU_TENURE + mult * TABU_TENURE_MULT;


  int tabu_size = MAX_TABU_SIZE;

  if (DYNAMIC_TABU_SIZE)
  {
    tabu_size = (((int)rand()) % MAX_TABU_SIZE) + 1;
  }

  // Make sure size of tabu is less than or equal to tabu_size
  while(true)
  {
    int min_tabu_val = INT_MAX;
    int min_a = -1;
    int min_b = -1;
    int num_tabu = 0;

    for (int a = 0; a < tabu_table.size(); ++a)
    {
      for (int b = 0; b < tabu_table[a].size(); ++b)
      {
        if (tabu_table[a][b] > 0)
        {
          ++num_tabu;

          if (min_tabu_val > tabu_table[a][b])
          {
            min_tabu_val = tabu_table[a][b];
            min_a = a;
            min_b = b;
          }
        }
      }
    }

    if (num_tabu > tabu_size)
    {
      // It is only possible to have a current tabu size at max 1 greater than
      // MAX_TABU_SIZE so we only need to set the item closest to expiring to 0
      tabu_table[min_a][min_b] = 0;
    } else
    {
      // num_tabu is less than or equal to MAX_TABU_SIZE
      break;
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
