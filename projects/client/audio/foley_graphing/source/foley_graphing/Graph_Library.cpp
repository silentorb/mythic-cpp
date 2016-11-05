#include "Graph_Library.h"
#include "Graph_Sound.h"
#include <signal_graph/Graph_Generator.h>
#include <signal_graph/Graph_Instance.h>

using namespace std;
using namespace foley;
using namespace signal_graph;

namespace foley_graphing {

//  unique_ptr<Graph_Instance> Graph_Library::get_sound(int id) const {
//    if (id >= instruments.size())
//      throw runtime_error("Invalid sound/instrument id: " + to_string(id) + ".");
//
//    return unique_ptr<Graph_Instance>(new Graph_Instance(*instruments[id], externals));
//  }
}