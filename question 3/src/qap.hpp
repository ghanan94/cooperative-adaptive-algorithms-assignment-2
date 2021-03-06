// Prototype of QAP
//@file qap.hpp
#ifndef __QAP_HPP__
#define __QAP_HPP__

#define NUM_OBJECTS 20
#define TABU_TENURE 0
#define TABU_TENURE_MULT 2
#define SEARCH_END_COUNT 100
#define DYNAMIC_TABU_SIZE true
#define MAX_TABU_SIZE 1000
#define EXCLUDE_PERCENTAGE_NEIGHBOURS 0.5 // Only look at 0.5 of the neighbours

#include <string>
#include <vector>

class QAP
{
  typedef std::vector<std::vector<int>> Table;

public:
  QAP(std::string, std::string);
  ~QAP();
  void print_flow_table();
  void print_distance_table();
  void find_solution();

private:
  Table flow_table;
  Table distance_table;
  Table tabu_table;

  void parse_flow_distance_table_file(Table&, std::string);
  void print_table(Table&);
  int evaluate_cost(std::vector<int>&);
  void tabu_add(int, int);
  bool tabu_check(int, int);
  void tabu_reset();
  void print_solution(std::vector<int>&);
  std::vector<int> solve();
};

#endif // __QAP_HPP__
