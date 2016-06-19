// Prototype of QAP
//@file qap.hpp
#ifndef __QAP_HPP__
#define __QAP_HPP__

#define NUM_OBJECTS 20
#define TABU_TENURE 3

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
  std::vector<int> solve();

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
};

#endif // __QAP_HPP__
