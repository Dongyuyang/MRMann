#include "../commonTool/common_tool.hpp"
#include "Rtree.h"
#include <cmath>

std::vector<std::vector<double> > get_outer_square_mbr_sqrt_eight(const std::vector<std::vector<double> > &mbr)
{
  double factor = 1 / std::sqrt(8);
  double edge = std::abs(mbr[1][0] - mbr[0][0]);
  double delta = 0.5*edge - 0.5*factor*edge;
  std::vector<double> new_low;
  std::vector<double> new_up;
  for(int i = 0; i < mbr[0].size();i++){
    new_low.push_back(mbr[0][i] - delta);
    new_up.push_back(mbr[1][i] + delta);
  }
  return {new_low,new_up};
}
  
std::vector<std::vector<double> > get_inner_square_mbr_sqrt_eight(const std::vector<std::vector<double> > &mbr)
{
  double factor = 1 / std::sqrt(8);
  double edge = std::abs(mbr[1][0] - mbr[0][0]);

  double delta = 0.5*edge - 0.5*factor*edge;

  std::vector<double> new_low;
  std::vector<double> new_up;

  for(int i = 0; i < mbr[0].size();i++){
    new_low.push_back(mbr[0][i] + delta);
    new_up.push_back(mbr[1][i] - delta);
  }
  return {new_low,new_up};
}

bool is_point_in_mbr(const std::vector<double> &p, const std::vector<std::vector<double> > &mbr)
{
  for(int i = 0 ;i < p.size();i++){
    if(!( p[i] >= mbr[0][i] && p[i] <= mbr[1][i]) )
      return false;
  }
  return true;
}

std::vector<int> expend(const std::vector<std::vector<double> > &mbr, bgi::rtree<Value, bgi::rstar<16> &rtree>, int counter)
{
  int times = 0;
  std::vector<std::vector<double> > current_mbr = mbr;
  while(counter < 2){
    std::vector<std::vector<double> > expanded_mbr = get_outer_square_mbr_sqrt_eight(current_mbr);
    std::vector<int> result_s = range_search(rtree,expended_mbr);
    if(!result_s.empty())
      counter++;
    if(counter == 2)
      return result_s;
    current_mbr = expanded_mbr;
    times++;
  }
  std::cout << "expand " << times << " times!" << std::endl;
}

std::vector<int> shrink(const std::vector<std::vector<double> > &mbr, bgi::rtree<Value, bgi::rstar<16> &rtree>, const std::vector<int> &query_result, const std::vector<std::vector<double> > &points)
{
  int counter = 0;
  std::vector<int> current_result = query_result;
  auto current_mbr = get_inner_square_mbr_sqrt_eight(mbr);
  for(auto node_id : current_result){
    if(is_point_in_mbr(points[node_id],current_mbr)){
      
    }
  }
}

int MRM_query(const std::vector<std::vector<double> > &points, std::vector<std::vector<double> > qs, bgi::rtree<Value, bgi::rstar<16> > &rtree)
{
  std::vector<std::vector<double> > mbr = get_mbr(qs);
  std::vector<int> query_result;
  query_result = range_search(rtree,mbr);
  if(query_result.empty()){ /*expand*/
      
      
  }else{ /*shrink*/
    
  }
    
  }
}
