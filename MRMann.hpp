#include "../commonTool/common_tool.hpp"
#include <cmath>

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

bool if_point_in_mbr(const std::vector<double> &p, const std::vector<std::vector<double> > &mbr)
{
  for(int i = 0 ;i < p.size();i++){
    if(!( p[i] >= mbr[0][i] && p[i] <= mbr[1][i]) )
      return false;
  }
  return true;
}
