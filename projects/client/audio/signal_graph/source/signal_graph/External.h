#pragma once

namespace signal_graph {


    class External {
        int index;

    public:
        External(int index) : index(index) {}

        int get_index()const {
          return index;
        }
    };
}