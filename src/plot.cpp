#include "plot.hpp"

namespace plt = matplotlibcpp;

void render_plot() {
  plt::plot({1, 3, 2, 4});
  plt::show();
}
