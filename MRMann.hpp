#include "Rtree.h"
#include "ann.h"
#include <cmath>

std::vector<std::vector<double> > get_outer_square_mbr_sqrt_eight(const std::vector<std::vector<double> > &mbr)
{
  //double factor = 1 / std::sqrt(8);
  double factor = std::sqrt(8);
  double edge = std::abs(mbr[1][0] - mbr[0][0]);
  //double delta = 0.5*edge - 0.5*factor*edge;
  double delta = 0.5 * edge * ( factor - 1);
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


std::vector<int> expand(const std::vector<std::vector<double> > &mbr, bgi::rtree<Value, bgi::rstar<16> > &rtree, int counter)
{
  int times = 1;
  std::vector<std::vector<double> > current_mbr = mbr;
  std::vector<int> result_s;
  while(counter < 2){
    std::vector<std::vector<double> > expanded_mbr = get_outer_square_mbr_sqrt_eight(current_mbr);
    result_s = range_search(rtree,expanded_mbr);
    if(!result_s.empty())
      counter++;
    if(counter == 2){
      std::cout << "expand " << times << " times!" << std::endl;
      return result_s;
    }
    current_mbr = expanded_mbr;
    times++;
  }
  
  return result_s;
}

static double get_edge_c(double a, double b)
{
  double f1 = a / std::sqrt(a+b);
  return pow(f1 - 1, 2) * a;
}

static double get_edge_d(double a, double b, double c)
{
  return (c/a)*b;
}

std::vector<int> shrink(const std::vector<std::vector<double> > &mbr, bgi::rtree<Value, bgi::rstar<16> > &rtree, const std::vector<int> &query_result)
{
  std::vector<int> result = query_result;
  std::vector<std::vector<double> > current_mbr = mbr;
  auto next_inner_mbr = get_inner_square_mbr_sqrt_eight(current_mbr);
  std::vector<int> next_query_result = range_search(rtree,next_inner_mbr);

  int time = 0;
  if(!next_query_result.empty()){
    while(true){
      time++;
      auto next_next_inner_mbr = get_inner_square_mbr_sqrt_eight(next_inner_mbr);
      auto next_next_query_result = range_search(rtree,next_next_inner_mbr);
      if(!next_next_query_result.empty()){
	result = next_query_result;
	next_query_result = next_next_query_result;
	next_inner_mbr = next_next_inner_mbr;
      }
      else{
	std::cout << "shrink time: " << time << std::endl;
	return result;
      }
    }
  }else{ /*expand 1 time*/
    return expand(mbr,rtree,1);    
  }
}

int MRM_query(const std::vector<std::vector<double> > &points, std::vector<std::vector<double> > qs, bgi::rtree<Value, bgi::rstar<16> > &rtree, int function)
{
  //std::vector<std::vector<double> > mbr = get_square_mbr(qs);
  std::vector<std::vector<double> > mbr = get_mbr(qs);
  std::vector<int> query_result;
  query_result = range_search(rtree,mbr);
  std::cout << "result number: " << query_result.size() << std::endl;
  
  if(query_result.empty()){ /*expand at least 2 time*/
    std::cout << "empty! expand" << std::endl;
    query_result = expand(mbr,rtree,0);
  }else{ /*shrink*/
    std::cout << "not empty! shrink" << std::endl;
    //query_result = shrink(mbr,rtree,query_result);
    query_result = expand(mbr,rtree,1);
  }

  std::cout << "naive size: " << query_result.size() << std::endl;
  int NN_id = naive_ann(query_result, qs, points, function);
  return NN_id;
}
