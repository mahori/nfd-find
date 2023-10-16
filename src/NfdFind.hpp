#ifndef __NFD_FIND_HPP__
#define __NFD_FIND_HPP__

#include <string>
#include <unicode/normalizer2.h>

class NfdFind
{
    public:
        NfdFind( void );
        ~NfdFind( void );

        void run( bool verbose, const std::string &directory );

    private:
        const icu::Normalizer2 *normalizer_;
};

#endif
