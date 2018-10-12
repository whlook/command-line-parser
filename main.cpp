
#include <fstream>
#include <iostream>
#include "command_line_parser.hpp"

int main(int argc, char *argv[]) {
  CommandLineParser parser("cat", "show text file context");
  parser.AddArgument("file", "text file path");
  parser.AddOption("--lines", 1, "-l", "line count to show", true);
  parser.AddOption("--back", 0, "-b", "from the back");
  parser.Parse(argc, argv);

  std::ifstream file(parser["file"]);
  if (!file.is_open()) {
    std::cerr << "failed to open file: " << parser["file"] << std::endl;
    std::cout << parser.UsageInfo() << std::endl;
    std::cerr << "Try '" << argv[0] << " --help' for more information."
              << std::endl;
    return -1;
  }

  if (file.is_open()) {
    int line_count = -1;
    if (parser["--lines"]) {
      line_count = std::max(0, parser["-l"][0].ToInt());
    }
    std::string line;
    std::vector<std::string> all_lines;
    if (!parser["--back"]) {
      while (std::getline(file, line)) {
        if (line_count != -1 && --line_count == -1) {
          break;
        }
        all_lines.push_back(line);
      }
    } else {
      while (std::getline(file, line)) {
        all_lines.push_back(line);
      }
      std::vector<std::string> last_lines;
      if (line_count != -1 && line_count < all_lines.size()) {
        last_lines.insert(last_lines.end(), all_lines.end() - line_count,
                          all_lines.end());
        last_lines.swap(all_lines);
      }
    }
    for (const auto &line_text : all_lines) {
      std::cout << line_text << std::endl;
    }
  }
  return 0;
}