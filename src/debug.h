#ifndef BLXR_SRC_DEBUG_H_
#define BLXR_SRC_DEBUG_H_

#define DEBUG_BUILD // Debug, Release
#define DEBUG_FUNCT // Debug functions

#ifdef DEBUG_FUNCT
#define DEBN(x) std::cout << "[" << #x << " - " << x << "]" << std::endl;    // Debug Name - print value with name
#define DEB(x) std::cout << x << std::endl;    // Debug - print value
#define DEBA(x) for(auto &a : x) { DEB(a) }    // Debug All - print each value in 'x' vector
#endif // DEBUG_FUNCT

#endif //BLXR_SRC_DEBUG_H_
