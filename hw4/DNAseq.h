#ifndef DNASEQ_H
#define DNASEQ_H
#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

enum Nucleotide { A, C, G, T };


class DNAseq {
private:
    Nucleotide* sequence;
    int length;

public:
    // Constructors
    DNAseq();                              // Default constructor
    DNAseq(const string& str);        // Parametric constructor
    DNAseq(const DNAseq& other);           // Deep copy constructor

    // Destructor
    ~DNAseq();
    // Getter function to access the sequence and turn it to a string
    string getSequenceAsString() const;

    DNAseq& operator=(const DNAseq& rhs);

    // Operator overloads
    bool operator<=(const DNAseq& rhs) const;
    DNAseq operator*(int times) const;
    int operator%(Nucleotide nt) const;
    DNAseq operator!() const;
    DNAseq operator+(const DNAseq& rhs) const;

    DNAseq operator-(const DNAseq& rhs) const;
    DNAseq& operator+=(const DNAseq& rhs);



};

DNAseq operator+(Nucleotide lhs, const DNAseq& rhs);
ostream& operator<<(ostream& os, const DNAseq& dna) ;
#endif
