/*2015-8-20 09:10 dyy*/

#include "MRMann.hpp"
#include "catch.h"
#include "../commonTool/init_data.hpp"
#include <iostream>

int main(int argc, char *argv[])
{
  int q_number = atoi(argv[1]);
  std::vector<std::vector<double> > points(100000);
  std::vector<std::vector<double> > qs(q_number);

  std::cout << "query number: " << q_number << std::endl;

  /*generate data points and query points*/
  //randinit(points,2,0,1);
  read_point_file(points, 2, "data/data2.ini");
  randinit(qs,2,atof(argv[2]),atof(argv[3]));

  /*init rtree*/
  bgi::rtree< Value, bgi::rstar<16> > rtree;
  init_rtree(rtree, points);

  CATCH mrmcost;
  mrmcost.catch_time();
  std::vector<std::vector<double> > mbr = get_mbr(qs);
  int NN_id = MRM_query(points, qs, rtree, 1);
  mrmcost.catch_time();

  std::vector<int> point_ids;
  for(int i = 0; i < points.size();i++)
    point_ids.push_back(i);
  
  CATCH naivecost;
  naivecost.catch_time();
  int NN_id_naive = naive_ann(point_ids, qs, points, 1);
  naivecost.catch_time();
    
  if(NN_id == NN_id_naive)
    std::cout << "yes!" << std::endl;
  else
    std::cout << "oh no!" << std::endl;

  //put_vector(result);
  std::cout << "MBR q: ";
  put_vector(mbr[0]);
  put_vector(mbr[1]);
  std::cout << "NN point id: " << NN_id << std::endl;
  std::cout << "NN point coordinates: ";
  put_vector(points[NN_id_naive]);
  std::cout << "MRM NN point coordinates: ";
  put_vector(points[NN_id]);

  std::cout << "MRM: cpu cost is " << mrmcost.get_cost(2) << " millisecond(s)" << std::endl;
  std::cout << "Nai: cpu cost is " << naivecost.get_cost(2) << " millisecond(s)" << std::endl;

}

