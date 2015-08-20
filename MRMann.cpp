/*2015-8-20 09:10 dyy*/

#include "MRMann.hpp"
#include "catch.h"
#include <iostream>

int main()
{
  // bgi::rtree< Value, bgi::rstar<16> > rtree;

  std::vector<std::vector<double> > points(1000);

  for(int i = 0; i < points.size(); i++){
    points[i].push_back(i);
    points[i].push_back(i+1);
  }

  std::vector<std::vector<double> > qs;
  //qs.push_back(points[5]);
  //qs.push_back(points[3]);
  qs.push_back({1.2,0});
  qs.push_back({1,2.2});
  qs.push_back({0,1.9});
  //init_rtree(rtree, points);

  //CATCH mbmcost;
  
  //mbmcost.catch_time();
  std::vector<std::vector<double> > mbr = get_mbr(qs);
  std::vector<std::vector<double> > mbr_square = get_square_mbr(qs);
  std::vector<std::vector<double> > inner_square_mbr = get_inner_square_mbr_sqrt_eight(mbr_square);

  std::cout << "d: " << (double)distance_no_sqrt(mbr[0],mbr[1]) << std::endl;
  std::cout << "d: " << (double)distance_no_sqrt(mbr_square[0],mbr_square[1]) << std::endl;
  std::cout << "d: " << (double)distance_no_sqrt(inner_square_mbr[0],inner_square_mbr[1]) << std::endl;
  
  //std::vector<int> result = range_search(rtree,mbr);
  //mbmcost.catch_time();

  //put_vector(result);
  
  //std::cout << "MBM: cpu cost is " << mbmcost.get_cost(2) << " millisecond(s)" << std::endl;

}

