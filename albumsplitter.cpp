#







include <iostream>
#include <fstream>
#include <vector>
// Include Essentia library (download and link accordingly)
#include <essentia/algorithm.h>
#include <essentia/standard/audio.h>

int main(int argc, char* argv[]) {
  if (argc < 3) {
    std::cerr << "Usage: " << argv[0] << " <audio_file> <silence_threshold>" << std::endl;
    return 1;
  }

  std::string filename = argv[1];
  double threshold = std::stod(argv[2]);

  // Load audio
  std::vector<double> samples = loadAudio(filename);

  // Find silent sections
  std::vector<int> splitPoints;
  for (int i = 0; i < samples.size(); ++i) {
    if (isSilent(samples, threshold, 500)) { // Adjust silence duration (500 = 5 seconds assuming 10ms intervals)
      splitPoints.push_back(i);
      i += 500; // Skip ahead after detecting silence
    }
  }

  // Split audio
  splitAudio(samples, splitPoints);

  std::cout << "Song division complete!" << std::endl;
  return 0;
}
