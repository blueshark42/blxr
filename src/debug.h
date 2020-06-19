#ifndef BLXR_SRC_DEBUG_H_
#define BLXR_SRC_DEBUG_H_

#define DEBUG_BUILD // Debug, Release
#define DEBUG_FUNCT // Debug functions

#ifdef DEBUG_FUNCT
#define DEBN(x) std::cout << "[" << #x << " - " << x << "]" << std::endl;
#define DEB(x) std::cout << x << std::endl;
#endif // DEBUG_FUNCT

#endif //BLXR_SRC_DEBUG_H_
