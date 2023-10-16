#include <iostream>
#include <string>
#include <boost/program_options.hpp>
#include "NfdFind.hpp"

using namespace std;

namespace po = boost::program_options;

static const char * const OPTION_HELP      = "help";
static const char * const OPTION_VERBOSE   = "verbose";
static const char * const OPTION_DIRECTORY = "directory";

int main( int argc, char *argv[] )
{
    po::options_description options( "options" );
    options.add_options()
        ( OPTION_HELP,                           "show help" )
        ( OPTION_VERBOSE,                        "verbose"   )
        ( OPTION_DIRECTORY, po::value<string>(), "directory" );

    po::variables_map variables;
    try {
        po::command_line_parser parser( argc, argv );
        parser.options( options );
        po::store( parser.run(), variables );
        po::notify( variables );
    }
    catch ( po::error &e ) {
        cerr << e.what() << endl;
        return -1;
    }

    if ( variables.count( OPTION_HELP ) > 0 ) {
        cerr << options << endl;
        return 1;
    }

    bool verbose = ( variables.count( OPTION_VERBOSE ) > 0 ) ? true : false;

    if ( variables.count( OPTION_DIRECTORY ) == 0 ) {
        cerr << "no directory specified" << endl;
        return -1;
    }
    string directory = variables[OPTION_DIRECTORY].as<string>();

    NfdFind nfd_find;
    nfd_find.run( verbose, directory );

    return 0;
}
