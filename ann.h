#include "../commonTool/common_tool.hpp"
#include <vector>

double get_agg_dist(const std::vector<double> &point, const std::vector<std::vector<double> > &qs, int function)
{
  double result = 0;
  switch(function){
  case 1: /*f = max*/
    {
      for(int i = 0; i < qs.size(); i++)
	result = std::max(result, distance_no_sqrt(point,qs[i]) );
      break;
    }
  case 2: /* f = sum*/
    {
      break;
    }
  case 3: /* f = min */
    {
      break;
    }
  default:
    break;
  }

  return result;
}

/*return the NN point id*/
int naive_ann(const std::vector<int> &point_ids, const std::vector<std::vector<double> > &qs, const std::vector<std::vector<double> > &points, int function)
{
  int NN_id = 0;
  double distance = std::numeric_limits<double>::max();
  for(auto node_id : point_ids){
    double current_distance = get_agg_dist(points[node_id], qs, function);
    if(distance > current_distance){
      distance = current_distance;
      NN_id = node_id;
    }
  }
  return NN_id;
}
