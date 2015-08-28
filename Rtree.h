#include <vector>
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/index/rtree.hpp>
#include <iostream>

namespace bg = boost::geometry;
namespace bgi = boost::geometry::index;

typedef bg::model::point<float, 2, bg::cs::cartesian> Point;
typedef bg::model::box<Point> box;
typedef std::pair<Point, int> Value;

void init_rtree(bgi::rtree< Value, bgi::rstar<100> > &rtree, const std::vector<std::vector<double> > &points)
{
  int count = 0;
  for(int i = 0; i < points.size();i++){
    Point p1;
    bg::set<0>(p1, points[i][0]);
    bg::set<1>(p1, points[i][1]);
    rtree.insert(std::make_pair(p1,i));
    count++;
  }
}

std::vector<int> range_search(const bgi::rtree< Value, bgi::rstar<100> > &rtree, const std::vector<std::vector<double> > &mbr)
{
  Point low,up;
  bg::set<0>(low, mbr[0][0]);
  bg::set<1>(low, mbr[0][1]);
  
  bg::set<0>(up, mbr[1][0]);
  bg::set<1>(up, mbr[1][1]);
  

  box query_box(low,up);
  std::vector<Value> result_s;
  rtree.query(bgi::intersects(query_box), std::back_inserter(result_s));

  std::vector<int> query_result_node_ids;
  for(auto value : result_s){
    query_result_node_ids.push_back(value.second);
  }

  return query_result_node_ids;

}
