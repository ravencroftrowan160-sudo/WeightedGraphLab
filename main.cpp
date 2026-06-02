//
//  main.cpp
//  CS 260 Lab 9
//
//  Created by Jim Bailey on June 2, 2020.
//  Licensed under a Creative Commons Attribution 4.0 International License.
//

#include "WGraph.hpp"
#include <iostream>

#define BASE_LAB
#define MIN_COST_PATHS
#define MIN_COST_TREE

int main() {
  std::cout << "Creating a weighted graph, adding nodes and edges\n\n";

  // create the graph
  WGraph graph;

  // Add nodes to the graph
  graph.addNode('A');
  graph.addNode('B');
  graph.addNode('C');
  graph.addNode('D');
  graph.addNode('E');
  graph.addNode('F');
  graph.addNode('G');
  graph.addNode('H');
  graph.addNode('I');
  graph.addNode('J');

  // add edges to the graph
  graph.addEdge('A', 'B', 4);
  graph.addEdge('A', 'H', 8);
  graph.addEdge('B', 'C', 8);
  graph.addEdge('B', 'H', 11);
  graph.addEdge('C', 'D', 7);
  graph.addEdge('C', 'F', 4);
  graph.addEdge('C', 'I', 2);
  graph.addEdge('D', 'F', 14);
  graph.addEdge('D', 'E', 9);
  graph.addEdge('E', 'F', 10);
  graph.addEdge('F', 'G', 2);
  graph.addEdge('H', 'I', 7);
  graph.addEdge('G', 'H', 1);
  graph.addEdge('G', 'I', 6);

#ifdef BASE_LAB
  std::cout << "Now testing base lab functionality\n\n";
  std::cout << "The list of nodes " << std::endl;
  std::cout << " expected A B C D E F G H I J" << std::endl;
  std::cout << " actually " << graph.listNodes() << std::endl << std::endl;

  std::cout << "The adjacency list is: " << std::endl;
  std::cout << graph.displayAdjacency() << std::endl;

  std::cout << "The adjacency matrix is (printing . for 0):" << std::endl;
  std::cout << graph.displayMatrix() << std::endl << std::endl;

  std::cout << "The breadth first traversal starting at A" << std::endl;
  std::cout << " expected A B H C I G D F E Unreached: J" << std::endl;
  std::cout << " actually " << graph.breadthFirst('A') << std::endl;

  std::cout << "The depth first traversal starting at A" << std::endl;
  std::cout << " expected A B C D F E G H I Unreached: J" << std::endl;
  std::cout << " actually " << graph.depthFirst('A') << std::endl << std::endl;
#endif // BASE_LAB

#ifdef MIN_COST_PATHS
  std::cout << "The minimum cost paths starting at A " << std::endl;
  std::cout << " Expected B(4) H(8) G(9) F(11) C(12) I(14) D(19) E(21) J(inf) "
            << std::endl;
  std::cout << " Actually " << graph.minCostPaths('A') << std::endl
            << std::endl;

  std::cout << "The minimum cost paths starting at D " << std::endl;
  std::cout << " Expected C(7) E(9) I(9) F(11) G(13) H(14) B(15) A(19) J(inf) "
            << std::endl;
  std::cout << " Actually " << graph.minCostPaths('D') << std::endl
            << std::endl;

  std::cout << "Done testing min cost paths " << std::endl
            << std::endl
            << std::endl;
#endif // MIN_COST_PATHS

#ifdef MIN_COST_TREE
  std::cout << "The min cost tree starting at A " << std::endl;
  std::cout << " Expected A: A-B A-H H-G G-F F-C C-I C-D D-E Unreached: J"
            << std::endl;
  std::cout << " Actually " << graph.minCostTree('A') << std::endl;

  std::cout << "The min cost tree starting at D " << std::endl;
  std::cout << " Expected D: D-C C-I C-F F-G G-H C-B B-A D-E Unreached: J"
            << std::endl;
  std::cout << " Actually " << graph.minCostTree('D') << std::endl;

  std::cout << "Done testing min cost spanning tree " << std::endl
            << std::endl
            << std::endl;
#endif // MIN_COST_TREE

  return 0;
}
