#include "NfdFind.hpp"
#include <algorithm>
#include <filesystem>
#include <iostream>
#include <string>
#include <unicode/normalizer2.h>
#include <unicode/uclean.h>

using namespace std;

namespace fs = std::filesystem;

NfdFind::NfdFind( void )
{
    UErrorCode error = U_ZERO_ERROR;

    u_init( &error );

    normalizer_ = icu::Normalizer2::getNFCInstance( error );
}

NfdFind::~NfdFind( void )
{
    u_cleanup();
}

void NfdFind::run( bool verbose, const string &directory )
{
    if ( !fs::exists( directory ) ) {
        return;
    }

    fs::directory_iterator it( directory );
    for_each( fs::begin( it ), fs::end( it ), [&]( const auto &entry ) {
        fs::path path = entry.path();

        if ( fs::is_directory( entry ) ) {
            run( verbose, path.native() );
        }

        if ( verbose ) {
            cerr << path.native() << endl;
        }

        fs::path filename = path.filename();

        UErrorCode error = U_ZERO_ERROR;
        UBool normalized = normalizer_->isNormalized( filename.c_str(), error );
        if ( !normalized ) {
            cout << path.native() << endl;
        }
    } );
}
