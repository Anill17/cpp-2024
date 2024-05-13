//
// Created by Anıl Sümer Topaloglu on 21.04.2024.
//
#include "DNAseq.h"

using namespace std;

DNAseq::DNAseq() : sequence(nullptr), length(0) {
    // Initially empty
}
DNAseq::DNAseq(const string& str) {
    length = str.size();
    sequence = new Nucleotide[length];
    for (int i = 0; i < length; ++i) {
        char ch = str[i];  // Get the character at position i
        if (ch == 'A') {
            sequence[i] = A;
        } else if (ch == 'C') {
            sequence[i] = C;
        } else if (ch == 'G') {
            sequence[i] = G;
        } else if (ch == 'T') {
            sequence[i] = T;
        } else {
            // for handling unexpected characters

        }
    }
}
DNAseq::DNAseq(const DNAseq& other) {
    length = other.length;
    sequence = new Nucleotide[length];
    for (int i = 0; i < length; ++i) {
        sequence[i] = other.sequence[i];
    }
}
DNAseq::~DNAseq() {
    delete[] sequence;
}
DNAseq& DNAseq::operator=(const DNAseq& rhs) {
    if (this != &rhs) {
        Nucleotide* newSequence = new Nucleotide[rhs.length];
        for (int i = 0; i < rhs.length; ++i) {
            newSequence[i] = rhs.sequence[i];
        }
        delete[] sequence;
        sequence = newSequence;
        length = rhs.length;
    }
    return *this;
}
bool DNAseq::operator<=(const DNAseq& rhs) const {
    if (length > rhs.length) return false;
    int j = 0; // Index for rhs
    for (int i = 0; i < length; ++i) {
        while (j < rhs.length && sequence[i] != rhs.sequence[j]) {
            j++;
        }
        if (j == rhs.length) return false;
        j++; // move to the next character in rhs
    }
    return true;
}
DNAseq DNAseq::operator*(int times) const {
    int newLength = length * times;
    DNAseq result;
    result.sequence = new Nucleotide[newLength];
    result.length = newLength;
    for (int i = 0; i < newLength; ++i) {
        result.sequence[i] = sequence[i % length];
    }
    return result;
}
int DNAseq::operator%(Nucleotide nt) const {
    int count = 0;
    for (int i = 0; i < length; ++i) {
        if (sequence[i] == nt) count++;
    }
    return count;
}

DNAseq DNAseq::operator!() const {
    DNAseq result(*this); // Start with a copy of the current object
    for (int i = 0; i < length; ++i) {
        if (result.sequence[i] == A) {
            result.sequence[i] = T;
        } else if (result.sequence[i] == T) {
            result.sequence[i] = A;
        } else if (result.sequence[i] == G) {
            result.sequence[i] = C;
        } else if (result.sequence[i] == C) {
            result.sequence[i] = G;
        }

    }
    return result;
}


DNAseq DNAseq::operator+(const DNAseq& rhs) const {
    int insertionIndex = -1;
    for (int i = 0; i < length; ++i) {
        if (sequence[i] == rhs.sequence[0]) {
            insertionIndex = i + 1;
            break;
        }
    }

    DNAseq result;
    result.length = length + rhs.length;
    result.sequence = new Nucleotide[result.length];

    if (insertionIndex != -1) {
        // Copy elements up to the insertion index from the lhs (this)
        for (int i = 0; i < insertionIndex; ++i) {
            result.sequence[i] = sequence[i];
        }
        // Insert the rhs sequence starting at the insertion index
        for (int i = 0; i < rhs.length; ++i) {
            result.sequence[insertionIndex + i] = rhs.sequence[i];
        }
        // Continue copying the rest of lhs after the inserted rhs part
        for (int i = insertionIndex; i < length; ++i) {
            result.sequence[rhs.length + i] = sequence[i];
        }
    } else {
        // If no insertion index is found, simply concatenate rhs to lhs
        for (int i = 0; i < length; ++i) {
            result.sequence[i] = sequence[i];
        }
        for (int i = 0; i < rhs.length; ++i) {
            result.sequence[length + i] = rhs.sequence[i];
        }
    }
    return result;
}


DNAseq DNAseq::operator-(const DNAseq& rhs) const {
    int startIndex = -1;
    for (int i = 0; i <= length - rhs.length; ++i) {
        bool match = true;
        for (int j = 0; j < rhs.length; ++j) {
            if (sequence[i + j] != rhs.sequence[j]) {
                match = false;
                break;
            }
        }
        if (match) {
            startIndex = i;
            break;
        }
    }

    if (startIndex == -1) {
        return *this; // No match found, return the original
    } else {
        DNAseq result;
        result.length = length - rhs.length;
        result.sequence = new Nucleotide[result.length];
        for (int i = 0; i < startIndex; ++i) {
            result.sequence[i] = sequence[i];
        }
        for (int i = startIndex + rhs.length; i < length; ++i) {
            result.sequence[i - rhs.length] = sequence[i];
        }
        return result;
    }
}
DNAseq& DNAseq::operator+=(const DNAseq& rhs) {
    DNAseq result = *this + rhs;
    delete [] this->sequence; // Deallocate current sequence
    this->sequence = result.sequence;
    this->length = result.length;
    result.sequence = nullptr;
    return *this;
}
string DNAseq::getSequenceAsString() const {
    string result;
    for (int i = 0; i < length; ++i) {
        if (sequence[i] == A) {
            result += 'A';
        } else if (sequence[i] == C) {
            result += 'C';
        } else if (sequence[i] == G) {
            result += 'G';
        } else if (sequence[i] == T) {
            result += 'T';
        }
    }
    return result;
}


ostream& operator<<(ostream& os, const DNAseq& dna) {
    // Use the public interface to access DNA sequence data
    os << dna.getSequenceAsString();
    return os;
}
DNAseq operator+(Nucleotide lhs, const DNAseq& rhs) {
        char lhs_c = 'x'; // default x for error handling purposes
        if (lhs == A) {
            lhs_c = 'A';
        } else if (lhs == C) {
            lhs_c = 'C';
        } else if (lhs == G) {
            lhs_c = 'G';
        } else if (lhs == T) {
            lhs_c = 'T';
        }


    return DNAseq(string(1, lhs_c) + rhs.getSequenceAsString());
}


