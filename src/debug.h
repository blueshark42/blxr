#ifndef BLXR_SRC_DEBUG_H_
#define BLXR_SRC_DEBUG_H_

//#define DEBUG_BUILD // Debug build or release build
#define DEBUG_FUNCT // Debug functions

#ifdef DEBUG_FUNCT
#define DEBN(x) std::cout << "[" << #x << " - " << x << "]" << std::endl;
#define DEB(x) std::cout << x << std::endl;
#define DEBA(x) for(auto &a : x) { DEB(a) }

#else // Here so if any debug functions are left the compiler will just ignore them
#define DEBN(x)
#define DEB(x)
#define DEBA(x)
#endif // DEBUG_FUNCT

#endif //BLXR_SRC_DEBUG_H_
