#ifndef MENU_HPP
#define MENU_HPP

#include "Graph.hpp"
#include "Graph_Analyzer.hpp"

class Menu {
 public:
  Menu(const std::string& csvFile);
  void run();

 private:
  Graph graph;
  GraphAnalyzer analyzer;
  void displayOptions();
  void processOption(int option);
};

#endif
