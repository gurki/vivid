#include "vivid/conversion.h"
#include "vivid/colortable.h"

namespace vivid::name {


////////////////////////////////////////////////////////////////////////////////
std::string fromRgb( const col_t& rgb ) {
    return name::fromIndex( index::fromRgb( rgb ) );
}


////////////////////////////////////////////////////////////////////////////////
std::string fromIndex( const uint8_t index ) {
    return ColorTable::name( index );
}


}   //  ::vivid::name
