#ifndef BLXR_SRC_DEBUG_H_
#define BLXR_SRC_DEBUG_H_

#define DEBUG_BUILD // Debug build or release build
#define DEBUG_FUNCT // Debug functions

#ifdef DEBUG_FUNCT
#define debn(...) std::cout << "[" << #__VA_ARGS__ << " - " << __VA_ARGS__ << "]" << std::endl;
#define deb(...) std::cout << __VA_ARGS__ << std::endl;
#define deba(x) for(auto &a : x) { deb(a) }

#define exit return 0;

#else // Here so if any debug functions are left the compiler will just ignore them
#define debn(x)
#define deb(x)
#define deba(x)



#endif // DEBUG_FUNCT

#endif //BLXR_SRC_DEBUG_H_
