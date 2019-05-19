#include "vivid/conversion.h"
#include "vivid/table.h"

namespace vivid::name {


////////////////////////////////////////////////////////////////////////////////
const std::string& fromRgb( const col_t& rgb ) {
    return name::fromIndex( index::fromRgb( rgb ) );
}


////////////////////////////////////////////////////////////////////////////////
const std::string& fromIndex( const uint8_t index ) {
    return table::xterm.at( index ).name;
}


}   //  ::vivid::name
