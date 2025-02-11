#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <iomanip>

int main(int argc, char* argv[]) {
    // Ensure a FASTA file is provided
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <fasta_file>\n";
        return 1;
    }

    std::ifstream fastaFile(argv[1]);
    if (!fastaFile) {
        std::cerr << "Error: Unable to open file " << argv[1] << "\n";
        return 1;
    }

    std::string line;
    int currentSeqLength = 0;
    int minSeqLength = std::numeric_limits<int>::max(); // Initialize to a large value
    int maxSeqLength = 0; // Initialize to a large value
    int sumSeqLength = 0; // Sum of all sequence lengths
    int totalSequences = 0; // Counter for number of sequences
    int totalA = 0; // Counter for the number of A's
    int totalC = 0; // Counter for the number of C's
    int totalG = 0; // Counter for the number of G's
    int totalT = 0; // Counter for the number of T's
    bool hasSequence = false; // Track if we have at least one sequence

    while (std::getline(fastaFile, line)) {
        if (line.empty()) continue; // Skip empty lines

        if (line[0] == '>') { // Header line
            // Check if there's an existing sequence and update min length
            if (currentSeqLength > 0) {
                minSeqLength = std::min(minSeqLength, currentSeqLength);
                maxSeqLength = std::max(maxSeqLength, currentSeqLength);
                sumSeqLength += currentSeqLength;
                totalSequences++;
                hasSequence = true;
            }
            currentSeqLength = 0; // Reset for the next sequence
        } else {
            currentSeqLength += line.length(); // Accumulate sequence length

            // Count the occurance of each nucleotide
            for (char c : line) {
                if (c == 'A') {
                    totalA++;
                }
                else if (c == 'C') {
                    totalC++;
                }
                else if (c == 'G') {
                    totalG++;
                }
                else if (c == 'T') {
                    totalT++;
                }
            }
        }
    }

    // Final check for the last sequence in the file
    if (currentSeqLength > 0) {
        minSeqLength = std::min(minSeqLength, currentSeqLength);
        maxSeqLength = std::max(maxSeqLength, currentSeqLength);
        sumSeqLength += currentSeqLength;
        totalSequences++;
        hasSequence = true;
    }

    fastaFile.close();

    if (hasSequence) {
        double avgSeqLength = static_cast<double>(sumSeqLength) / totalSequences;

        // std::cout << "Shortest sequence length: " << minSeqLength << std::endl;
        std::cout << "{ \"min_len\": " << minSeqLength 
                  << ", \"max_len\": " << maxSeqLength 
                  << ", \"mean_len\": " << avgSeqLength
                  << ", \"tot_len\": " << sumSeqLength
                  << ", \"num_records\": " << totalSequences 
                  << ", \"count_a\": " << totalA 
                  << ", \"count_c\": " << totalC 
                  << ", \"count_g\": " << totalG 
                  << ", \"count_t\": " << totalT << " }" 
                  << std::endl;
    } else {
        std::cerr << "Error: No sequences found in the FASTA file.\n";
        return 1;
    }



    return 0;
}
